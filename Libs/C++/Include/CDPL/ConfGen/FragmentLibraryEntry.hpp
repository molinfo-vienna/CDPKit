/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FragmentLibraryEntry.hpp 
 *
 * This file is part of the ConfGenical Data Processing Toolkit
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
 * \brief Definition of the class CDPL::ConfGen::FragmentLibraryEntry.
 */

#ifndef CDPL_CONFGEN_FRAGMENTLIBRARYENTRY_HPP
#define CDPL_CONFGEN_FRAGMENTLIBRARYENTRY_HPP

#include <vector>
#include <cstddef>

#include <boost/shared_ptr.hpp>

#include "CDPL/ConfGen/APIPrefix.hpp"
#include "CDPL/Chem/BasicMolecule.hpp"
#include "CDPL/Chem/CanonicalNumberingGenerator.hpp"
#include "CDPL/Chem/SmallestSetOfSmallestRings.hpp"
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

			typedef std::vector<const Chem::Atom*> AtomMapping;

			/**
			 * \brief Constructs an empty \c %FragmentLibraryEntry instance.
			 */
			FragmentLibraryEntry();

			/**
			 * \brief Constructs a \c %FragmentLibraryEntry instance that contains the relevant atoms and bonds of the molecular graph \a molgraph.
			 * \param molgraph The molecular graph for which to generate the fragments.
			 * \param parent The parent molecular graph the fragment is coming from.
			 */
			FragmentLibraryEntry(const Chem::MolecularGraph& molgraph, const Chem::MolecularGraph& parent);
		
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

			void orderAtoms(const Chem::AtomCompareFunction& func);

			void orderBonds(const Chem::BondCompareFunction& func);

			const Base::uint64& getHashCode() const;

			Chem::MolecularGraph::SharedPointer clone() const;

			FragmentLibraryEntry& operator=(const FragmentLibraryEntry& entry);

			void create(const Chem::MolecularGraph& molgraph, const Chem::MolecularGraph& parent);

			const AtomMapping& getAtomMapping() const;

			void perceiveSSSR();

		  private:
			void copyAtoms(const Chem::MolecularGraph& molgraph, const Chem::MolecularGraph& parent);
			bool copyBonds(const Chem::MolecularGraph& molgraph);

			void fixStereoDescriptors(const Chem::MolecularGraph& molgraph);
			void hydrogenize();
			void canonicalize(bool stereo);
			void calcHashCode(bool stereo);

			bool compareCanonNumber(const Chem::Atom& atom1, const Chem::Atom& atom2) const;
		
			typedef std::vector<Base::uint32> HashInputData;
			typedef Chem::SmallestSetOfSmallestRings::SharedPointer SmallestSetOfSmallestRingsPtr;

			Chem::BasicMolecule               molecule;
			Base::uint64                      hashCode;
			Chem::CanonicalNumberingGenerator canonNumGen;
			SmallestSetOfSmallestRingsPtr     sssr;
			Util::STArray                     canonNumbers;
			HashInputData                     hashInputData;
			AtomMapping                       atomMapping;
		};

		/**
		 * @}
		 */
    }
}

#endif // CDPL_CONFGEN_FRAGMENTLIBRARYENTRY_HPP
