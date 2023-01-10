/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ChEMBLStandardizer.hpp 
 *
 * Implementation of the ChEMBL molecule standardization and parent compound extraction procedure
 * (A. P. Bento et al., An open source chemical structure curation pipeline using RDKit, J. Cheminformatics 2020, 12, 51) 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2020 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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
 * \brief Definition of the class CDPL::Chem::ChEMBLStandardizer.
 */

#ifndef CDPL_CHEM_CHEMBLSTANDARDIZER_HPP
#define CDPL_CHEM_CHEMBLSTANDARDIZER_HPP

#include <boost/shared_ptr.hpp>

#include "CDPL/Chem/APIPrefix.hpp"


namespace CDPL 
{

    namespace Chem
    {

		class Molecule;
		
		/**
		 * \brief ChEMBLStandardizer.
		 * \see [\ref CSCP]
		 */
		class CDPL_CHEM_API ChEMBLStandardizer 
		{

		  public:
			typedef boost::shared_ptr<ChEMBLStandardizer> SharedPointer;

			enum Result	{
			
			    NO_CHANGES = 0x0,
				EXCLUDED   = 0x1,
				H_REMOVED  = 0x2
			};

			ChEMBLStandardizer();

			ChEMBLStandardizer(const ChEMBLStandardizer& standardizer);

			void ignoreExcludedFlag(bool ignore);

			bool excludedFlagIgnored() const;
			
			Result standardize(Molecule& mol);

			Result standardize(const Molecule& mol, Molecule& std_mol);

			bool getParent(Molecule& mol);

			bool getParent(const Molecule& mol, Molecule& parent_mol);
			
			ChEMBLStandardizer& operator=(const ChEMBLStandardizer& standardizer);
	    
		  private:
			bool checkIfExcluded(const Molecule& mol) const;
			void copyMolecule(const Molecule& mol, Molecule& mol_copy) const;

			bool ignoreExcldFlag;
		};
    }
}

#endif // CDPL_CHEM_CHEMBLSTANDARDIZER_HPP
