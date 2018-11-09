/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FragmentLibraryEntry.hpp 
 *
 * This file is part of the ConfGenical Data Processing Toolkit
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
 * \brief Definition of the class CDPL::ConfGen::FragmentLibraryEntry.
 */

#ifndef CDPL_CONFGEN_BUILDFRAGMENTMOLECULE_HPP
#define CDPL_CONFGEN_BUILDFRAGMENTMOLECULE_HPP

#include <boost/shared_ptr.hpp>

#include "CDPL/ConfGen/APIPrefix.hpp"
#include "CDPL/Chem/BasicMolecule.hpp"
#include "CDPL/Chem/HashCodeCalculator.hpp"
#include "CDPL/Chem/CIPPriorityCalculator.hpp"
#include "CDPL/Util/Array.hpp"
#include "CDPL/Base/IntegerTypes.hpp"


namespace CDPL 
{

    namespace ConfGen
    {

		/**
		 * \addtogroup CDPL_CONFGEN_HELPERS
		 * @{
		 */

		/**
		 * \brief FragmentLibraryEntry.
		 */
		class CDPL_CONFGEN_API FragmentLibraryEntry : public Chem::MolecularGraph
		{

		  public:
			/**	
			 * \brief A reference-counted smart pointer [\ref BSHPTR] for dynamically allocated \c %FragmentLibraryEntry instances.
			 */
			typedef boost::shared_ptr<FragmentLibraryEntry> SharedPointer;
		
			typedef Chem::BasicMolecule::AtomIterator AtomIterator;
			typedef Chem::BasicMolecule::ConstAtomIterator ConstAtomIterator;
			typedef Chem::BasicMolecule::BondIterator BondIterator;
			typedef Chem::BasicMolecule::ConstBondIterator ConstBondIterator;

			/**
			 * \brief Constructs an empty \c %FragmentLibraryEntry instance.
			 */
			FragmentLibraryEntry();

			/**
			 * \brief Constructs a \c %FragmentLibraryEntry instance that contains the relevant atoms and bonds of the molecular graph \a molgraph.
			 * \param molgraph The molecular graph for which to generate the fragments.
			 */
			FragmentLibraryEntry(const Chem::MolecularGraph& molgraph);
		
			FragmentLibraryEntry(const FragmentLibraryEntry& entry);

			void clear();
	
			std::size_t getNumAtoms() const;

			const Chem::Atom& getAtom(std::size_t idx) const;
		
			Chem::Atom& getAtom(std::size_t idx);

			ConstAtomIterator getAtomsBegin() const;

			ConstAtomIterator getAtomsEnd() const;

			AtomIterator getAtomsBegin();

			AtomIterator getAtomsEnd();

			bool containsAtom(const Chem::Atom& atom) const;

			std::size_t getAtomIndex(const Chem::Atom& atom) const;

			std::size_t getNumEntities() const;

			const Chem::Entity3D& getEntity(std::size_t idx) const;

			Chem::Entity3D& getEntity(std::size_t idx);

			std::size_t getNumBonds() const;
	    
			const Chem::Bond& getBond(std::size_t idx) const;

			Chem::Bond& getBond(std::size_t idx);

			ConstBondIterator getBondsBegin() const;

			ConstBondIterator getBondsEnd() const;

			BondIterator getBondsBegin();

			BondIterator getBondsEnd();

			bool containsBond(const Chem::Bond& bond) const;

			std::size_t getBondIndex(const Chem::Bond& bond) const;

			const Base::uint64& getHashCode() const;

			FragmentLibraryEntry& operator=(const FragmentLibraryEntry& entry);

			void create(const Chem::MolecularGraph& molgraph);
	
		  private:
			void copyAtoms(const Chem::MolecularGraph& molgraph);
			bool copyBonds(const Chem::MolecularGraph& molgraph);

			void fixStereoDescriptors(const Chem::MolecularGraph& molgraph);
			void hydrogenize();
			void calcHashCode(bool stereo);

			bool hasSymTerminalNeighbors(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph) const;

			Chem::BasicMolecule         molecule;
			Base::uint64                hashCode;
			Chem::HashCodeCalculator    hashCodeCalc;
			Chem::CIPPriorityCalculator cipPriorityCalc;
			Util::STArray               cipPriorities;
		};

		/**
		 * @}
		 */
    }
}

#endif // CDPL_CONFGEN_BUILDFRAGMENTMOLECULE_HPP
