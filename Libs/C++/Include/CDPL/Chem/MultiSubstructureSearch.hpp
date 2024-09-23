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
 * \brief Definition of the class CDPL::Chem::MultiSubstructureSearch.
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
         * \brief MultiSubstructureSearch.
         * \since 1.2
         */
        class CDPL_CHEM_API MultiSubstructureSearch
        {

          public:
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
          
            bool matches(const MolecularGraph& molgraph);

            void addSubstructure(const MolecularGraph::SharedPointer& molgraph);

            std::size_t getNumSubstructures() const;

            void clear();

            void setup(const std::string& qry_expr = "");

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
