/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * TautomerizationRule.hpp 
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
 * \brief Definition of the class CDPL::Chem::TautomerizationRule.
 */

#ifndef CDPL_CHEM_TAUTOMERIZATIONRULE_HPP
#define CDPL_CHEM_TAUTOMERIZATIONRULE_HPP

#include <boost/shared_ptr.hpp>

#include "CDPL/Chem/APIPrefix.hpp"


namespace CDPL 
{

    namespace Chem
    {

		class MolecularGraph;
		class Molecule;
	
		/**
		 * \addtogroup CDPL_CHEM_TAUTOMER_GENERATION_RULES
		 * @{
		 */

		/**
		 * \brief TautomerizationRule.
		 */
		class CDPL_CHEM_API TautomerizationRule 
		{

		  public:
			typedef boost::shared_ptr<TautomerizationRule> SharedPointer;

			virtual ~TautomerizationRule() {}

			virtual bool setup(MolecularGraph& parent_molgraph) = 0;

			virtual unsigned int getID() const = 0;

			/**
			 * \brief Generates the next tautomer.
			 * \param tautomer The tautomer output molecule object.
			 * \return \c true if a tautomer was generated, \c false if no more tautomers are available.
			 */
			virtual bool generate(Molecule& tautomer) = 0;

			virtual SharedPointer clone() const = 0;
		};

		/**
		 * @}
		 */
    }
}

#endif // CDPL_CHEM_TAUTOMERIZATIONRULE_HPP
