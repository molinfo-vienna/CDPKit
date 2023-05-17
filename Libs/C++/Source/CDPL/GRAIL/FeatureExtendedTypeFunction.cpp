/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FeatureExtendedTypeFunction.cpp 
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

#include "CDPL/GRAIL/FeatureFunctions.hpp"
#include "CDPL/GRAIL/FeatureType.hpp"
#include "CDPL/Pharm/FeatureFunctions.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Chem/SybylAtomType.hpp"


using namespace CDPL; 


namespace
{

    const Chem::Atom* getFeatureAtom(const Pharm::Feature& ftr)
    {
		using namespace Chem;
	
		if (!hasSubstructure(ftr))
			return 0;

		const Fragment::SharedPointer& substruct = getSubstructure(ftr);

		if (!substruct)
			return 0;

		for (Fragment::ConstAtomIterator it = substruct->getAtomsBegin(), end = substruct->getAtomsEnd(); it != end; ++it)
			if (getType(*it) != AtomType::H)
				return &*it;

		return 0;
    }
}


unsigned int GRAIL::perceiveExtendedType(const Pharm::Feature& feature, bool lig_side)
{
    using namespace Chem;
		
    unsigned int ftr_type = getType(feature);

    if (ftr_type != FeatureType::H_BOND_ACCEPTOR && ftr_type != FeatureType::H_BOND_DONOR)
		return ftr_type;

    const Atom* ftr_atom = getFeatureAtom(feature);

    if (!ftr_atom)
		return ftr_type;
    
    if (lig_side) {
		switch (getSybylType(*ftr_atom)) {

			case SybylAtomType::N_4:
				return (ftr_type == FeatureType::H_BOND_ACCEPTOR ? ftr_type : FeatureType::H_BOND_DONOR_N4);

			case SybylAtomType::N_3:
				return (ftr_type == FeatureType::H_BOND_ACCEPTOR ? FeatureType::H_BOND_ACCEPTOR_N3 : FeatureType::H_BOND_DONOR_N3);
		
			case SybylAtomType::N_2:
				return (ftr_type == FeatureType::H_BOND_ACCEPTOR ? FeatureType::H_BOND_ACCEPTOR_N2 : FeatureType::H_BOND_DONOR_N2);
		
			case SybylAtomType::N_1:
				return (ftr_type == FeatureType::H_BOND_ACCEPTOR ? FeatureType::H_BOND_ACCEPTOR_N1 : ftr_type);
		
			case SybylAtomType::N_ar:
				return (ftr_type == FeatureType::H_BOND_ACCEPTOR ? FeatureType::H_BOND_ACCEPTOR_Nar : FeatureType::H_BOND_DONOR_Nar);
		
			case SybylAtomType::N_pl3:
				return (ftr_type == FeatureType::H_BOND_ACCEPTOR ? FeatureType::H_BOND_ACCEPTOR_Npl3 : FeatureType::H_BOND_DONOR_Npl3);

			case SybylAtomType::N_am:
				return (ftr_type == FeatureType::H_BOND_ACCEPTOR ? ftr_type : FeatureType::H_BOND_DONOR_Nam);

			case SybylAtomType::O_3:
				return (ftr_type == FeatureType::H_BOND_ACCEPTOR ? FeatureType::H_BOND_ACCEPTOR_O3 : FeatureType::H_BOND_DONOR_O3);
		
			case SybylAtomType::O_2:
				return (ftr_type == FeatureType::H_BOND_ACCEPTOR ? FeatureType::H_BOND_ACCEPTOR_O2 : ftr_type);
		
			case SybylAtomType::O_co2:
				return (ftr_type == FeatureType::H_BOND_ACCEPTOR ? FeatureType::H_BOND_ACCEPTOR_Oco2 : ftr_type);
		
			case SybylAtomType::S_3:
				return (ftr_type == FeatureType::H_BOND_ACCEPTOR ? FeatureType::H_BOND_ACCEPTOR_S3 : FeatureType::H_BOND_DONOR_S3);
		
			case SybylAtomType::S_2:
				return (ftr_type == FeatureType::H_BOND_ACCEPTOR ? FeatureType::H_BOND_ACCEPTOR_S2 : ftr_type);
	    
			default:
				return ftr_type;
		}
    }

    switch (getType(*ftr_atom)) {

		case AtomType::N:
			return (ftr_type == FeatureType::H_BOND_ACCEPTOR ? FeatureType::H_BOND_ACCEPTOR_N : FeatureType::H_BOND_DONOR_N);
	    
		case AtomType::O:
			return (ftr_type == FeatureType::H_BOND_ACCEPTOR ? FeatureType::H_BOND_ACCEPTOR_O : FeatureType::H_BOND_DONOR_O);

		case AtomType::S:
			return (ftr_type == FeatureType::H_BOND_ACCEPTOR ? FeatureType::H_BOND_ACCEPTOR_S : FeatureType::H_BOND_DONOR_S);

		default:
			return ftr_type;
    }
}
