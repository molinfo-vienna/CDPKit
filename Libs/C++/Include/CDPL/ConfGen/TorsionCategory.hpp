/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * TorsionCategory.hpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2010 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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
 * \brief Definition of the class CDPL::ConfGen::TorsionCategory.
 */

#ifndef CDPL_CONFGEN_TORSIONCATEGORY_HPP
#define CDPL_CONFGEN_TORSIONCATEGORY_HPP

#include <vector>
#include <string>
#include <cstddef>

#include "CDPL/ConfGen/APIPrefix.hpp"
#include "CDPL/ConfGen/TorsionRule.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"


namespace CDPL 
{

	namespace ConfGen 
	{

		/**
		 * \addtogroup CDPL_CONFGEN_DATA_STRUCTURES
		 * @{
		 */
		
		class CDPL_CONFGEN_API TorsionCategory
		{

			typedef std::vector<TorsionCategory> CategoryList;
			typedef std::vector<TorsionRule> RuleList;

		  public:
			TorsionCategory(const std::string& name);

			virtual ~TorsionCategory() {}

			const std::string& getName() const;

			void setName(const std::string& name);

			const Chem::MolecularGraph::SharedPointer& getBondMatchPattern() const;

			void setBondMatchPattern(const Chem::MolecularGraph::SharedPointer& ptn);
			
			unsigned int getBondAtom1Type() const;

			void setBondAtom1Type(unsigned int type);

			unsigned int getBondAtom2Type() const;

			void setBondAtom2Type(unsigned int type);

			TorsionCategory& addCategory(const std::string& name);

			TorsionRule& addRule();

		  private:
			std::string                         name;      
			Chem::MolecularGraph::SharedPointer bondPattern;
			unsigned int                        bondAtom1Type;
			unsigned int                        bondAtom2Type;
			RuleList                            rules;
			CategoryList                        categories;
		};
   
		/**
		 * @}
		 */
	}
}

#endif // CDPL_CONFGEN_TORSIONCATEGORY_HPP
