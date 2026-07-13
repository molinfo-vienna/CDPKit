/* 
 * MoleculeFunctions.hpp 
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
 * \brief Declaration of functions that operate on Chem::Molecule instances.
 */

#ifndef CDPL_CHEM_MOLECULEFUNCTIONS_HPP
#define CDPL_CHEM_MOLECULEFUNCTIONS_HPP

#include <cstddef>
#include <string>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/AtomPredicate.hpp"
#include "CDPL/Chem/Atom3DCoordinatesFunction.hpp"


namespace CDPL
{

    namespace Chem
    {

        class Molecule;
        class MolecularGraph;

        /**
         * \brief Removes all explicit hydrogen atoms from the molecule \a mol.
         * \param mol The molecule for which to remove all explicit hydrogen atoms.
         * \param corr_impl_h_count \c true if the implicit hydrogen count property of the affected remaining atoms shall be corrected,
         *                          \c false if the property shall be left unchanged.
         * \return \c false if \a mol was not altered, \c true otherwise.
         */
        CDPL_CHEM_API bool makeHydrogenDeplete(Molecule& mol, bool corr_impl_h_count = true);

        /**
         * \brief Removes all explicit ordinary hydrogen atoms from the molecule \a mol.
         * \param mol The molecule for which to remove all explicit ordinary hydrogen atoms.
         * \param flags Specifies the set of atom properties to check (see namespace Chem::AtomPropertyFlag).
         * \param corr_impl_h_count \c true if the implicit hydrogen count property of the affected remaining atoms shall be corrected,
         *                          \c false if the property shall be left unchanged.
         * \return \c false if \a mol was not altered, \c true otherwise.
         * \see MolProp::isOrdinaryHydrogen
         */
        CDPL_CHEM_API bool makeOrdinaryHydrogenDeplete(Molecule& mol, unsigned int flags, bool corr_impl_h_count = true);

        /**
         * \brief Converts all implicit hydrogens of the molecule \a mol to explicit hydrogen atoms.
         * \param mol The molecule that has to be made hydrogen complete.
         * \param corr_impl_h_count \c true if the implicit hydrogen count property of the hydrogen completed shall be set to zero,
         *                          \c false if the property shall be left unchanged.
         * \return \c false if \a mol was not altered, \c true otherwise.
         */
        CDPL_CHEM_API bool makeHydrogenComplete(Molecule& mol, bool corr_impl_h_count = true);

        /**
         * \brief Adds bonds between atoms of the molecule \a mol whose 3D distance falls within the covalent-radii sum plus \a dist_tol.
         * \param mol The molecule whose atoms shall be connected.
         * \param dist_tol The tolerance added to the sum of the two atoms' covalent radii.
         * \param atom_idx_offs Bonds are only added when at least one of the two atom indices is greater than or equal to \a atom_idx_offs.
         * \note The minimum atom pair distance is \e 0.5 &Aring;.
         */
        CDPL_CHEM_API void connectAtoms(Molecule& mol, double dist_tol = 0.3, std::size_t atom_idx_offs = 0);

        /**
         * \brief Adds bonds between atoms of the molecule \a mol whose 3D distance (obtained via \a coords_func) falls within the covalent-radii sum plus \a dist_tol.
         * \param mol The molecule whose atoms are to be connected.
         * \param coords_func The function used to retrieve the 3D coordinates of an atom.
         * \param dist_tol The tolerance added to the sum of the two atoms' covalent radii.
         * \param atom_idx_offs Bonds are only added when at least one of the two atom indices is greater than or equal to \a atom_idx_offs.
         * \note The minimum atom pair distance is \e 0.5 &Aring;.
         */
        CDPL_CHEM_API void connectAtoms(Molecule& mol, const Atom3DCoordinatesFunction& coords_func,
                                        double dist_tol = 0.3, std::size_t atom_idx_offs = 0);

        /**
         * \brief Removes all atoms of the molecule \a mol for which the predicate \a pred returns \c true.
         * \param mol The molecule to filter in place.
         * \param pred The atom predicate to evaluate.
         */
        CDPL_CHEM_API void removeAtomsIf(Molecule& mol, const AtomPredicate& pred);

        /**
         * \brief Removes all atoms of the molecule \a mol for which the predicate \a pred returns \c false.
         * \param mol The molecule to filter in place.
         * \param pred The atom predicate to evaluate.
         */
        CDPL_CHEM_API void removeAtomsIfNot(Molecule& mol, const AtomPredicate& pred);

        /**
         * \brief Edits the molecule \a mol by replacing all substructures matching the \e SMARTS search patterns in \a search_ptns
         *        with the \e SMILES replacement pattern \a result_ptn, optionally skipping matches that also match \a exclude_ptns.
         *
         * A molecule editing operation is specified via a string of one or more \e SMARTS patterns (\a search_ptns)
         * describing the substructures to edit, optional substructure exclude patterns (\a exclude_ptns) and a \e SMILES
         * string (\a result_ptn) encoding the specific atom and bond modifications to perform. If multiple search and/or exclude patterns
         * are specified then they need to be separated by a whitespace character.
         *
         * In the substructure search pattern(s), any atoms to be edited and/or atoms connected by bonds to be modified must be labeled
         * by a unique non-zero integer number (by means of a colon followed the integer number at the end of the \e SMARTS atom specification).
         * These numeric ids are used to establish an unambiguous mapping between the atoms/bonds of the search pattern
         * and the \e SMILES string encoding the editing instructions.
         * As mentioned above, the atom/bond editing operations are all specified by means of a simple \e SMILES string. For the purpose of
         * substructure editing, the \e SMILES format has been extended by additional atom type and bond order symbols that allow to mark atom/bonds
         * for deletion or act as a 'do not change' marker for atom type or bond order.
         *
         * Editing result \e SMILES strings have to be composed according to the following rules:
         * - Atoms of the molecule matching labeled search pattern atoms are referenced by their numeric id (likewise specified by means of a colon followed
         *   by the integer number at the end of the \e SMILES atom specification)
         * - A bond between two labeled atoms in the result \e SMILES string will be mapped to the bond of the molecule that matched the corresponding bond of the search pattern
         * - If such a bond of the molecule does not exist it will be created with the specified bond order
         * - A molecule bond connecting two atoms that match labeled search pattern atoms which is not occurring in the result \e SMILES string will be left unchanged
         * - A molecule atom matching a labeled search pattern atom which is not occurring in the result \e SMILES string will be left unchanged
         * - A labeled atom in the result \e SMILES string with a numeric id that does not occur in the search pattern will be created with specified
         *   properties (symbol, form. charge, isotope, chirality, ...)
         * - Any unlabeled atoms in the result \e SMILES string will be created with the specified properties (symbol, form. charge, isotope, chirality, ...)
         * - Bonds to/between unlabeled result \e SMILES string atoms will be created with the specified bond order
         * - For a mapped molecule atom only those properties (symbol, form. charge, isotope, chirality, ...) that were specified for the corresponding result
         *   \e SMILES string atom will be modified
         * - The special result \e SMILES string atom type symbol <tt>x</tt> (only valid in brackets) results in the removal of the mapped molecule atom including any incident bonds
         * - The special result \e SMILES string atom type symbol <tt>~</tt> (only valid in brackets) indicates that the type of the mapped molecule atom shall be left unchanged
         * - The special result \e SMILES string bond order symbol <tt>x</tt> results in the removal of the mapped molecule bond
         * - The special result \e SMILES string bond order symbol <tt>~</tt> indicates that the order of the mapped molecule bond shall be left unchanged
         *
         * \param mol The molecule to edit in place.
         * \param search_ptns A whitespace-separated list of \e SMARTS patterns matching the substructures to replace.
         * \param result_ptn The \e SMARTS replacement pattern.
         * \param exclude_ptns A whitespace-separated list of \e SMARTS patterns matching substructures that shall be retained even if they match \a search_ptns.
         * \return The number of replaced substructures.
         * \since 1.3
         */
        CDPL_CHEM_API std::size_t editSubstructures(Molecule& mol, const std::string& search_ptns,
                                                    const std::string& result_ptn, const std::string& exclude_ptns = std::string());

    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_MOLECULEFUNCTIONS_HPP
