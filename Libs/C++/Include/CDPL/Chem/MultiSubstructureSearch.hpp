/* 
 * MultiSubstructureSearch.hpp 
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

/**
 * \file
 * \brief Definition of class CDPL::Chem::MultiSubstructureSearch.
 */

#ifndef CDPL_CHEM_MULTISUBSTRUCTURESEARCH_HPP
#define CDPL_CHEM_MULTISUBSTRUCTURESEARCH_HPP

#include <memory>
#include <string>
#include <cstddef>
#include <vector>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"


namespace CDPL
{

    namespace Chem
    {
   
        /**
         * \brief Evaluates a boolean expression over multiple substructure queries against a target molecular graph.
         *
         * Substructure query molecular graphs are added via addSubstructure() and referenced in the boolean
         * expression by their 1-based insertion order (e.g. \c "1 AND (2 OR NOT 3)"). The expression is parsed
         * by setup() and subsequently evaluated for each target molecular graph passed to matches().
         *
         * \since 1.2
         */
        class CDPL_CHEM_API MultiSubstructureSearch
        {

          public:
            /**
             * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %MultiSubstructureSearch instances.
             */
            typedef std::shared_ptr<MultiSubstructureSearch> SharedPointer;

            /**
             * \brief Constructs and initializes a \c %MultiSubstructureSearch instance.
             */
            MultiSubstructureSearch();

            MultiSubstructureSearch(const MultiSubstructureSearch&) = delete;

            /**
             * \brief Destructor.
             *
             * Destroys the \c %MultiSubstructureSearch instance and frees all allocated resources.
             */
            ~MultiSubstructureSearch();

            MultiSubstructureSearch& operator=(const MultiSubstructureSearch&) = delete;

            /**
             * \brief Evaluates the configured boolean substructure expression against the target molecular graph \a molgraph.
             * \param molgraph The target molecular graph.
             * \return \c true if the boolean expression evaluates to true for \a molgraph, and \c false otherwise
             *         (also \c false when no expression has been compiled by setup() yet).
             */
            bool matches(const MolecularGraph& molgraph);

            /**
             * \brief Appends a substructure query to the internal substructure list.
             *
             * The query receives the 1-based ID equal to the new value of getNumSubstructures(),
             * which is how it is referenced in the boolean expression.
             *
             * \param molgraph A smart pointer to the substructure query molecular graph.
             */
            void addSubstructure(const MolecularGraph::SharedPointer& molgraph);

            /**
             * \brief Returns the number of stored substructure queries.
             * \return The number of stored substructure queries.
             */
            std::size_t getNumSubstructures() const;

            /**
             * \brief Removes all stored substructure queries and clears the compiled expression.
             */
            void clear();

            /**
             * \brief Compiles the boolean substructure expression \a qry_expr.
             *
             * Substructure IDs in the expression are 1-based and refer to the order in which queries
             * were added via addSubstructure(). Supported operators are \c AND, \c OR, \c XOR and \c NOT.
             *
             * \param qry_expr The boolean expression to compile (an empty string clears the compiled expression).
             */
            void setup(const std::string& qry_expr = "");

            /**
             * \brief Validates the syntax of \a qry_expr without compiling it for evaluation.
             * \param qry_expr The expression to validate.
             * \param max_substr_id Largest accepted substructure ID; expressions referencing larger IDs are rejected.
             * \return An empty string if \a qry_expr is well-formed, otherwise an error message describing the failure.
             */
            std::string validate(const std::string& qry_expr, std::size_t max_substr_id);
            
          private:
            enum Token : int;
            class ExprTreeNode;

            typedef std::unique_ptr<ExprTreeNode>              ExprTreeNodePtr;
            typedef std::vector<MolecularGraph::SharedPointer> MolGraphPtrArray;
  
            Token nextToken(const std::string& expr);

            ExprTreeNodePtr parseExpression(const std::string& expr);
            ExprTreeNodePtr parseTerm(const std::string& expr);
            ExprTreeNodePtr parseFactor(const std::string& expr);
   
            void validateExpression(const std::string& expr, std::size_t max_substr_id);
            void validateTerm(const std::string& expr, std::size_t max_substr_id);
            void validateFactor(const std::string& expr, std::size_t max_substr_id);

            MolGraphPtrArray substructures;
            std::size_t      nextTokenStart;
            Token            currToken;
            std::size_t      substrID;
            ExprTreeNodePtr  exprTree;
        };
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_MULTISUBSTRUCTURESEARCH_HPP
