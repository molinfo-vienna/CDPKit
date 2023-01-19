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

#include <vector>
#include <utility>

#include <boost/shared_ptr.hpp>
#include <boost/unordered_set.hpp>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/BasicMolecule.hpp"
#include "CDPL/Chem/Fragment.hpp"
#include "CDPL/Chem/KekuleStructureCalculator.hpp"
#include "CDPL/Chem/SubstructureSearch.hpp"
#include "CDPL/Chem/CanonicalNumberingCalculator.hpp"
#include "CDPL/Chem/HashCodeCalculator.hpp"
#include "CDPL/Util/BitSet.hpp"
#include "CDPL/Math/VectorArray.hpp"


namespace CDPL 
{

    namespace Chem
    {
		
		/**
		 * \brief Implementation of the ChEMBL structure preprocessing pipeline.
		 * \see [\ref CSCP]
		 */
		class CDPL_CHEM_API ChEMBLStandardizer 
		{

		  public:
			typedef boost::shared_ptr<ChEMBLStandardizer> SharedPointer;

			enum ChangeFlags {
			
			    NONE                         = 0x0,
				EXCLUDED                     = 0x1,
				EXPLICIT_H_REMOVED           = 0x2,
				UNKNOWN_STEREO_STANDARDIZED  = 0x4,
				BONDS_KEKULIZED              = 0x8,
				STRUCTURE_NORMALIZED         = 0x10,
				CHARGES_REMOVED              = 0x20,
				TARTRATE_STEREO_CLEARED      = 0x40,
				STRUCTURE_2D_CORRECTED       = 0x80,
				ISOTOPE_INFO_CLEARED         = 0x100,
				SALT_COMPONENTS_REMOVED      = 0x200,
				SOLVENT_COMPONENTS_REMOVED   = 0x400
			};

			ChEMBLStandardizer();

			ChEMBLStandardizer(const ChEMBLStandardizer& standardizer);
		
			ChangeFlags standardize(Molecule& mol, bool proc_excld = false);

			ChangeFlags standardize(const Molecule& mol, Molecule& std_mol, bool proc_excluded = false);

			ChangeFlags getParent(Molecule& mol, bool neutralize = true, bool check_exclusion = true);

			ChangeFlags getParent(const Molecule& mol, Molecule& parent_mol, bool neutralize = true, bool check_exclusion = true);
			
			ChEMBLStandardizer& operator=(const ChEMBLStandardizer& standardizer);
	    
		  private:
			typedef std::vector<Atom*> AtomList;

			void copyMolecule(const Molecule& mol, Molecule& mol_copy) const;

			bool checkExclusionCriterions(const Molecule& mol) const;

			bool standardizeUnknownStereochemistry(Molecule& mol) const;

			bool kekulizeBonds(Molecule& mol);

			bool removeExplicitHydrogens(Molecule& mol) const;			
			bool isRemovableHydrogen(const Atom& atom) const;

			bool normalizeStructure(Molecule& mol);
			const Chem::Atom* getAtomWithMappingID(const Molecule& ptn, std::size_t id) const;

			bool removeCharges(Molecule& mol);
			std::size_t getMatches(const Molecule& ptn, const Molecule& mol, AtomList& matches);
			bool cmpCanonicalNumber(const Atom* atom1, const Atom* atom2) const;
			bool incrementCharge(Atom& atom, bool checked) const;

			bool removeTartrateStereochemistry(Molecule& mol);

			bool cleanup2DStructure(Molecule& mol);
			double calc2DBondAngle(const Molecule& mol, const Atom& ctr_atom, const Atom& nbr_atom1, const Atom& nbr_atom2);
			void rotateSubstituent(const Molecule& mol, const Atom& ctr_atom, const Atom& subst_atom, double rot_ang);

			typedef std::pair<Base::uint64, Base::uint64> StructureID;
			typedef std::pair<const Fragment*, StructureID> MoleculeComponent;
			typedef std::vector<MoleculeComponent> MoleculeComponentList;
			typedef boost::unordered_set<StructureID> MoleculeComponentSet;

			HashCodeCalculator           hashCodeCalc;
			KekuleStructureCalculator    kekuleStructureCalc;
			Util::STArray                kekulizedBondOrders;
			SubstructureSearch           substructSearch;
			CanonicalNumberingCalculator canonNumberingCalc;
			Util::STArray                canonAtomNumbering;
			AtomList                     posChargedAtoms;
			AtomList                     posChargedNoHAtoms;
			AtomList                     negChargedAtoms;
			AtomList                     negChargedAcidAtoms;
			Math::Vector2DArray          atom2DCoords;
			Util::BitSet                 markedAtomSet;
			Fragment                     tmpFragment;
			BasicMolecule                tmpMolecule;
			MoleculeComponentList        molCompList1;
			MoleculeComponentList        molCompList2;
			MoleculeComponentSet         molCompSet;
		};
    }
}

#endif // CDPL_CHEM_CHEMBLSTANDARDIZER_HPP
