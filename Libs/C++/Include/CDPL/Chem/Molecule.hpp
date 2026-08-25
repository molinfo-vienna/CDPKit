/* 
 * Molecule.hpp 
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
 * \brief Definition of class CDPL::Chem::Molecule.
 */

#ifndef CDPL_CHEM_MOLECULE_HPP
#define CDPL_CHEM_MOLECULE_HPP

#include <memory>
#include <functional>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"


namespace CDPL
{

    namespace Chem
    {

        /**
         * \brief Abstract base class representing a mutable molecular graph that owns and manages its atoms and bonds.
         *
         * Extends the Chem::MolecularGraph interface with editing methods (addAtom(), addBond(), removeAtom(), removeBond(),
         * copy(), append(), remove()) and supports a global registry of copy postprocessing functions invoked after copying/append
         * operations to properly transform properties referencing atoms and bonds of the source molecular graph.
         */
        class CDPL_CHEM_API Molecule : public MolecularGraph
        {

          public:
            /**    
             * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %Molecule instances.
             */
            typedef std::shared_ptr<Molecule> SharedPointer;

            /**
             * \brief A constant random access iterator used to iterate over the stored \c const Chem::Atom objects.
             */
            typedef AtomContainer::ConstAtomIterator ConstAtomIterator;

            /**
             * \brief A mutable random access iterator used to iterate over the stored Chem::Atom objects.
             */
            typedef AtomContainer::AtomIterator AtomIterator;

            /**
             * \brief A constant random access iterator used to iterate over the stored \c const Chem::Bond objects.
             */
            typedef BondContainer::ConstBondIterator ConstBondIterator;

            /**
             * \brief A mutable random access iterator used to iterate over the stored Chem::Bond objects.
             */
            typedef BondContainer::BondIterator BondIterator;

            /**
             * \brief Type of function invoked after a molecule has been altered due to copying/appending a source molecular graph.
             *
             * First argument: the modified destination molecule, second argument: the source molecular graph.
             */
            typedef std::function<void(Molecule&, const MolecularGraph&)> CopyPostprocessingFunction;

            /**
             * \brief Virtual destructor.
             *
             * Destroys the \c %Molecule instance and frees all allocated resources.
             */
            virtual ~Molecule() {}

            using AtomContainer::getAtomsBegin;
            using AtomContainer::getAtomsEnd;

            using BondContainer::getBondsBegin;
            using BondContainer::getBondsEnd;

            /**
             * \brief Removes all atoms and bonds and clears all properties of the molecule.
             */
            virtual void clear() = 0;

            /**
             * \brief Creates a new atom and adds it to the molecule.
             *
             * Note that this method does not create any bonds - the returned atom is always unconnected.
             *
             * \return A reference to the newly created atom.
             */
            virtual Atom& addAtom() = 0;

            /**
             * \brief Removes the atom at the specified index.
             *
             * If the specified atom is connected to any other atoms of the molecule then the connecting bonds
             * will also be removed.
             *
             * \param idx The index of the atom to remove.
             * \throw Base::IndexError if \a idx is not in the range [0, getNumAtoms()).
             */
            virtual void removeAtom(std::size_t idx) = 0;

            /**
             * \brief Removes the atom specified by the iterator \a it.
             *
             * If the specified atom is connected to any other atoms of the molecule then the connecting bonds
             * will also be removed.
             *
             * \param it An iterator that specifies the atom to remove.
             * \return A mutable iterator pointing to the next atom in the list.
             * \throw Base::RangeError if \a it is not in the range [getAtomsBegin(), getAtomsEnd()).
             */
            AtomIterator removeAtom(const AtomIterator& it);

            /**
             * \brief Creates a new or returns an already existing bond between the atoms specified by
             *        \a atom1_idx and \a atom2_idx.
             *
             * If a bond between the specified atoms already exists then the existing bond will be returned. If a bond
             * does not yet exist, a new bond will be created. The atom specified by \a atom1_idx becomes the start atom
             * and the atom specified by \a atom2_idx the end atom of the newly created bond. 
             *
             * \param atom1_idx The zero-based index of the first atom of the bond.
             * \param atom2_idx The zero-based index of the second atom of the bond.
             * \return A reference to the newly created or already existing bond between the specified atoms.
             * \throw Base::IndexError if \a atom1_idx and/or \a atom2_idx is not in the range [0, getNumAtoms()).
             */
            virtual Bond& addBond(std::size_t atom1_idx, std::size_t atom2_idx) = 0;

            /**
             * \brief Removes the bond at the specified index.
             * \param idx The zero-based index of the bond to remove.
             * \throw Base::IndexError if \a idx is not in the range [0, getNumBonds()).
             */
            virtual void removeBond(std::size_t idx) = 0;

            /**
             * \brief Removes the bond specified by the iterator \a it.
             * \param it An iterator that specifies the bond to remove.
             * \return A mutable iterator pointing to the next bond in the list.
             * \throw Base::RangeError if \a it is not in the range [getBondsBegin(), getBondsEnd()).
             */
            BondIterator removeBond(const BondIterator& it);

            /**
             * \brief Replaces the current set of atoms, bonds and properties by a copy of the
             *        atoms, bonds and properties of the molecule \a mol.
             * \param mol The molecule to copy.
             */
            virtual void copy(const Molecule& mol) = 0;

            /**
             * \brief Replaces the current set of atoms, bonds and properties by a copy of the
             *        atoms, bonds and properties of the molecular graph \a molgraph.
             * \param molgraph The molecular graph providing the atoms, bonds and properties to copy.
             */
            virtual void copy(const MolecularGraph& molgraph) = 0;

            /**
             * \brief Extends the current set of atoms and bonds by a copy of the atoms and bonds in the
             *        molecule \a mol.
             * \param mol The molecule providing the atoms and bonds to append.
             * \note Does not affect any properties.
             */
            virtual void append(const Molecule& mol) = 0;

            /**
             * \brief Extends the current set of atoms and bonds by a copy of the atoms and bonds in the
             *        molecular graph \a molgraph.
             * \param molgraph The molecular graph providing the atoms and bonds to append.
             * \note Does not affect any properties.
             */
            virtual void append(const MolecularGraph& molgraph) = 0;

            /**
             * \brief Removes atoms and bonds referenced by the molecular graph \a molgraph that are part of this \c %Molecule instance.
             * \param molgraph The molecular graph specifying the atoms and bonds to remove.
             * \note Does not affect any properties if <tt>this != &molgraph</tt>.
             */
            virtual void remove(const MolecularGraph& molgraph) = 0;

            /**
             * \brief Reserves memory for \a num_atoms atoms.
             *
             * Allows implementors to speed up the creation of molecules with a known large number of atoms.
             * 
             * \param num_atoms The expected number of atoms for which memory shall be allocated in advance.
             */
            virtual void reserveMemoryForAtoms(std::size_t num_atoms) {}

            /**
             * \brief Reserves memory for \a num_bonds bonds.
             *
             * Allows implementors to speed up the creation of molecules with a known large number of bonds.
             * 
             * \param num_bonds The expected number of bonds for which memory shall be allocated in advance.
             */
            virtual void reserveMemoryForBonds(std::size_t num_bonds) {}

            /**
             * \brief Replaces the current set of atoms, bonds and properties by a copy of the
             *        atoms, bonds and properties of the molecule \a mol.
             *
             * Internally calls copy() to perform the actual work.
             *
             * \param mol The molecule to copy.
             * \return A reference to itself.
             */
            Molecule& operator=(const Molecule& mol);

            /**
             * \brief Replaces the current set of atoms, bonds and properties by a copy of the
             *        atoms, bonds and properties of the molecular graph \a molgraph.
             *
             * Internally calls copy() to perform the actual work.
             *
             * \param molgraph The Chem::MolecularGraph instance providing the atoms and bonds to copy.
             * \return A reference to itself.
             */
            Molecule& operator=(const MolecularGraph& molgraph);

            /**
             * \brief Extends the current set of atoms and bonds by a copy of the atoms and bonds in the
             *        molecule \a mol.
             *
             * Internally calls append() to perform the actual work.
             *
             * \param mol The molecule providing the atoms and bonds to append.
             * \return A reference to itself.
             */
            Molecule& operator+=(const Molecule& mol);

            /**
             * \brief Extends the current set of atoms and bonds by a copy of the atoms and bonds in the
             *        molecular graph \a molgraph.
             *
             * Internally calls append() to perform the actual work.
             *
             * \param molgraph The Chem::MolecularGraph instance providing the atoms and bonds to append.
             * \return A reference to itself.
             */
            Molecule& operator+=(const MolecularGraph& molgraph);

            /**
             * \brief Removes atoms and bonds referenced by the molecular graph \a molgraph that are part of this \c %Molecule instance.
             *
             * Internally calls remove() to perform the actual work.
             *
             * \param molgraph The Chem::MolecularGraph instance specifying the atoms and bonds to remove.
             * \return A reference to itself.
             */
            Molecule& operator-=(const MolecularGraph& molgraph);

            /**
             * \brief Registers a new copy postprocessing function in the global registry.
             *
             * Registered functions are invoked in registration order typically after copy/append operations that
             * populate a Chem::Molecule instance with atoms and bonds from a source Chem::MolecularGraph instance.
             *
             * \param func The callback function to register.
             */
            static void registerCopyPostprocessingFunction(const CopyPostprocessingFunction& func);

          protected:
            /**
             * \brief Invokes all registered copy postprocessing functions on this molecule with \a src_molgraph as
             *        the source molecular graph.
             * \param src_molgraph The source molecular graph that provided the copied atoms and bonds.
             */
            void invokeCopyPostprocessingFunctions(const MolecularGraph& src_molgraph);
        };
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_MOLECULE_HPP
