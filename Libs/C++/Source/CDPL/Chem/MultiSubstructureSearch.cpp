/* 
 * MultiSubstructureSearch.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; see the file COPYING. If not, write to
 * the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */


#include "StaticInit.hpp"

#include <locale>

#include "CDPL/Chem/MultiSubstructureSearch.hpp"
#include "CDPL/Chem/SubstructureSearch.hpp"
#include "CDPL/Base/Exceptions.hpp"


using namespace CDPL;


enum Chem::MultiSubstructureSearch::Token : int
{
    EOI,
    AND,
    OR,
    XOR,
    NOT,
    LP,
    RP,
    SSID
};

class Chem::MultiSubstructureSearch::ExprTreeNode
{

  public:
    ExprTreeNode(const MolecularGraph::SharedPointer& qry_molgraph):
        token(SSID), queryMolgraph(qry_molgraph) {}

    ExprTreeNode(ExprTreeNodePtr&& child):
        token(NOT), child1(std::move(child)) {}

    ExprTreeNode(Token token, ExprTreeNodePtr&& child1, ExprTreeNodePtr&& child2):
        token(token), child1(std::move(child1)), child2(std::move(child2)) {}

    bool matches(const MolecularGraph& molgraph) {
        switch (token) {

            case SSID:
                if (!subSearch)
                    subSearch.reset(new SubstructureSearch(*queryMolgraph));

                return subSearch->mappingExists(molgraph);
                
            case OR:
                return (child1->matches(molgraph) || child2->matches(molgraph));
                
            case XOR:
                return (child1->matches(molgraph) != child2->matches(molgraph));
                
            case AND:
                return (child1->matches(molgraph) && child2->matches(molgraph));
                 
            case NOT:
                return !child1->matches(molgraph);
                
            default:
                return false;
        }
    }
    
  private:
    typedef MolecularGraph::SharedPointer       MolGraphPtr;
    typedef std::unique_ptr<SubstructureSearch> SubSearchPtr;

    Token           token;
    ExprTreeNodePtr child1;
    ExprTreeNodePtr child2;
    SubSearchPtr    subSearch;
    MolGraphPtr     queryMolgraph;
};


Chem::MultiSubstructureSearch::MultiSubstructureSearch() {}

Chem::MultiSubstructureSearch::~MultiSubstructureSearch() {}

void Chem::MultiSubstructureSearch::addSubstructure(const MolecularGraph::SharedPointer& molgraph)
{
    substructures.push_back(molgraph);
}

std::size_t Chem::MultiSubstructureSearch::getNumSubstructures() const
{
    return substructures.size();
}

void Chem::MultiSubstructureSearch::clear()
{
    substructures.clear();
}

void Chem::MultiSubstructureSearch::setup(const std::string& expr)
{
    nextTokenStart = 0;

    try {
        if (nextToken(expr) == EOI) {
            if (substructures.empty()) {
                exprTree.reset();
                return;
            }

            exprTree.reset(new ExprTreeNode(substructures[0]));

            for (auto it = ++substructures.begin(), end = substructures.end(); it != end; ++it)
                exprTree.reset(new ExprTreeNode(OR, ExprTreeNodePtr(exprTree.release()), ExprTreeNodePtr(new ExprTreeNode(*it))));
        
            return;
        }

        exprTree = parseExpression(expr);
        
    } catch (const Base::ValueError& e) {
        throw Base::ValueError(std::string("MultiSubstructureSearch: ") + e.what());
    }
    
    if (currToken != EOI)
        throw Base::ValueError("MultiSubstructureSearch: garbage at end of expression");
}

std::string Chem::MultiSubstructureSearch::validate(const std::string& expr, std::size_t max_substr_id)
{
    try {
        nextTokenStart = 0;

        if (nextToken(expr) == EOI)
            return std::string();

        validateExpression(expr, max_substr_id);

        if (currToken != EOI)
            return "garbage at end of expression";

        return std::string();

    } catch (const Base::ValueError& e) {
        return e.what();
    }
}

bool Chem::MultiSubstructureSearch::matches(const MolecularGraph& molgraph)
{
    if (!exprTree)
        return false;
    
    return exprTree->matches(molgraph);
}

Chem::MultiSubstructureSearch::Token Chem::MultiSubstructureSearch::nextToken(const std::string& expr)
{
    substrID = 0;
    
    for (std::size_t expr_end = expr.size(); nextTokenStart < expr_end; nextTokenStart++) {
        char c = std::tolower(expr[nextTokenStart], std::locale::classic());
        
        if (std::isspace(c, std::locale::classic()))
            continue;

        switch (c) {

            case '!':
                nextTokenStart++;
                return (currToken = NOT);
                
            case '|':
                nextTokenStart++;
                return (currToken = OR);

            case '^':
                nextTokenStart++;
                return (currToken = XOR);
                
            case '&':
                nextTokenStart++;
                return (currToken = AND);

            case '(':
                nextTokenStart++;
                return (currToken = LP);

            case ')':
                nextTokenStart++;
                return (currToken = RP);
                
            case 'n':
                if ((nextTokenStart + 3) <= expr_end &&
                    std::tolower(expr[nextTokenStart + 1], std::locale::classic()) == 'o' &&
                    std::tolower(expr[nextTokenStart + 2], std::locale::classic()) == 't') {

                    nextTokenStart += 3;
                    return (currToken = NOT);
                }
                    
                break;

            case 'o':
                if ((nextTokenStart + 2) <= expr_end &&
                    std::tolower(expr[nextTokenStart + 1], std::locale::classic()) == 'r') {

                    nextTokenStart += 2;
                    return (currToken = OR);
                }
                    
                break;

                
            case 'x':
                if ((nextTokenStart + 3) <= expr_end &&
                    std::tolower(expr[nextTokenStart + 1], std::locale::classic()) == 'o' &&
                    std::tolower(expr[nextTokenStart + 2], std::locale::classic()) == 'r') {

                    nextTokenStart += 3;
                    return (currToken = XOR);
                }
                    
                break;

            case 'a':
                if ((nextTokenStart + 3) <= expr_end &&
                    std::tolower(expr[nextTokenStart + 1], std::locale::classic()) == 'n' &&
                    std::tolower(expr[nextTokenStart + 2], std::locale::classic()) == 'd') {

                    nextTokenStart += 3;
                    return (currToken = AND);
                }
                
                break;

            default:
                if (!std::isdigit(c, std::locale::classic()))
                    break;

                substrID = c - '0';
    
                for (nextTokenStart++; nextTokenStart < expr_end; nextTokenStart++) {
                    c = expr[nextTokenStart];

                    if (!std::isdigit(c, std::locale::classic()))
                        break;
                    
                    substrID = substrID * 10 + c - '0';
                }

                return (currToken = SSID);
        }

        throw Base::ValueError("invalid expression element");
    }

    return (currToken = EOI);
}

/*
 * Grammar:
 * exp -> term {OR term};
 * exp -> term {XOR term};
 * term -> factor {AND factor};
 * factor -> SSID;
 * factor -> NOT factor;
 * factor -> LP exp RP;
 */

Chem::MultiSubstructureSearch::ExprTreeNodePtr
Chem::MultiSubstructureSearch::parseExpression(const std::string& expr)
{
    auto term = parseTerm(expr);

    while (currToken == OR || currToken == XOR) {
        Token prev_token = currToken;
        
        nextToken(expr);

        term.reset(new ExprTreeNode(prev_token, ExprTreeNodePtr(term.release()), parseTerm(expr)));
    }

    return term;
}

Chem::MultiSubstructureSearch::ExprTreeNodePtr
Chem::MultiSubstructureSearch::parseTerm(const std::string& expr)
{
    auto factor = parseFactor(expr);

    while (currToken == AND) {
        nextToken(expr);

        factor.reset(new ExprTreeNode(AND, ExprTreeNodePtr(factor.release()), parseFactor(expr)));
    }

    return factor;
}

Chem::MultiSubstructureSearch::ExprTreeNodePtr
Chem::MultiSubstructureSearch::parseFactor(const std::string& expr)
{
    switch (currToken) {

        case SSID: {
            if (substrID == 0)
                 throw Base::ValueError("invalid substructure ID");

            if (substrID > substructures.size())
                 throw Base::ValueError("substructure ID out of allowed range");

            std::size_t substr_idx = substrID - 1;
                        
            nextToken(expr);

            return ExprTreeNodePtr(new ExprTreeNode(substructures[substr_idx]));
        }
            
        case LP: {
            nextToken(expr);
            
            auto exp = parseExpression(expr);

            if (currToken != RP)
                throw Base::ValueError("expected right parenthesis");

            nextToken(expr);
            return exp;
        }
            
        case NOT:
            nextToken(expr);
            return ExprTreeNodePtr(new ExprTreeNode(parseFactor(expr)));
            
        case EOI:
            throw Base::ValueError("unexpected end of expression");

        default:
            throw Base::ValueError("expression syntax error");
    }
}

void Chem::MultiSubstructureSearch::validateExpression(const std::string& expr, std::size_t max_substr_id)
{
    validateTerm(expr, max_substr_id);

    while (currToken == OR || currToken == XOR) {
        nextToken(expr);
        validateTerm(expr, max_substr_id);
    }
}

void Chem::MultiSubstructureSearch::validateTerm(const std::string& expr, std::size_t max_substr_id)
{
    validateFactor(expr, max_substr_id);

    while (currToken == AND) {
        nextToken(expr);
        validateFactor(expr, max_substr_id);
    }
}

void Chem::MultiSubstructureSearch::validateFactor(const std::string& expr, std::size_t max_substr_id)
{
    switch (currToken) {

        case SSID:
            if (substrID == 0)
                 throw Base::ValueError("invalid substructure ID");

            if (substrID > max_substr_id)
                 throw Base::ValueError("substructure ID out of allowed range");

            nextToken(expr);
            return;
            
        case LP:
            nextToken(expr);
            validateExpression(expr, max_substr_id);

            if (currToken != RP)
                throw Base::ValueError("expected right parenthesis");

            nextToken(expr);
            return;
            
        case NOT:
            nextToken(expr);
            validateFactor(expr, max_substr_id);
            return;
            
        case EOI:
            throw Base::ValueError("unexpected end of expression");

        default:
            throw Base::ValueError("expression syntax error");
    }
}
