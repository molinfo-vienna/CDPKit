/* 
 * AtomFunctions.hpp 
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
 * \brief Declaration of functions that operate on Chem::Atom instances.
 */

#ifndef CDPL_CHEM_ATOMFUNCTIONS_HPP
#define CDPL_CHEM_ATOMFUNCTIONS_HPP

#include <cstddef>
#include <string>
#include <type_traits>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/MatchExpression.hpp"
#include "CDPL/Chem/MatchConstraintList.hpp"
#include "CDPL/Chem/FragmentList.hpp"
#include "CDPL/Chem/AtomPropertyFlag.hpp"
#include "CDPL/Chem/AtomPriorityFunction.hpp"
#include "CDPL/Math/Vector.hpp"
#include "CDPL/Math/VectorArray.hpp"
#include "CDPL/Util/BitSet.hpp"


namespace CDPL
{

    namespace Chem
    {

        class StereoDescriptor;

        /**
         * \brief Returns the value of the Chem::AtomProperty::NAME property of the atom \a atom.
         * \param atom The atom for which to return the property value.
         * \return The stored atom name.
         */
        CDPL_CHEM_API const std::string& getName(const Atom& atom);

        /**
         * \brief Sets the value of the Chem::AtomProperty::NAME property of the atom \a atom to \a name.
         * \param atom The atom for which to set the property value.
         * \param name The new atom name.
         */
        CDPL_CHEM_API void setName(Atom& atom, const std::string& name);

        /**
         * \brief Clears the value of the Chem::AtomProperty::NAME property of the atom \a atom.
         * \param atom The atom for which to clear the property value.
         */
        CDPL_CHEM_API void clearName(Atom& atom);

        /**
         * \brief Tells whether the Chem::AtomProperty::NAME property of the atom \a atom is set.
         * \param atom The atom for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_CHEM_API bool hasName(const Atom& atom);


        /**
         * \brief Returns the value of the Chem::AtomProperty::SYMBOL property of the atom \a atom.
         * \param atom The atom for which to return the property value.
         * \return The stored element symbol.
         */
        CDPL_CHEM_API const std::string& getSymbol(const Atom& atom);

        /**
         * \brief Sets the value of the Chem::AtomProperty::SYMBOL property of the atom \a atom to \a symbol.
         * \param atom The atom for which to set the property value.
         * \param symbol The new element symbol.
         */
        CDPL_CHEM_API void setSymbol(Atom& atom, const std::string& symbol);

        /**
         * \brief Clears the value of the Chem::AtomProperty::SYMBOL property of the atom \a atom.
         * \param atom The atom for which to clear the property value.
         */
        CDPL_CHEM_API void clearSymbol(Atom& atom);

        /**
         * \brief Tells whether the Chem::AtomProperty::SYMBOL property of the atom \a atom is set.
         * \param atom The atom for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_CHEM_API bool hasSymbol(const Atom& atom);

        /**
         * \brief Returns the element symbol that corresponds to the Chem::AtomProperty::TYPE property of the atom \a atom.
         * \param atom The atom to query.
         * \return The element symbol mapped from the atom's type (see namespace Chem::AtomType).
         */
        CDPL_CHEM_API const std::string& getSymbolForType(const Atom& atom);


        /**
         * \brief Returns the value of the Chem::AtomProperty::TYPE property of the atom \a atom.
         * \param atom The atom for which to return the property value.
         * \return The stored atom type (see namespace Chem::AtomType).
         */
        CDPL_CHEM_API unsigned int getType(const Atom& atom);

        /**
         * \brief Sets the value of the Chem::AtomProperty::TYPE property of the atom \a atom to \a type.
         * \param atom The atom for which to set the property value.
         * \param type The new atom type (see namespace Chem::AtomType).
         */
        CDPL_CHEM_API void setType(Atom& atom, unsigned int type);

        /**
         * \brief Clears the value of the Chem::AtomProperty::TYPE property of the atom \a atom.
         * \param atom The atom for which to clear the property value.
         */
        CDPL_CHEM_API void clearType(Atom& atom);

        /**
         * \brief Tells whether the Chem::AtomProperty::TYPE property of the atom \a atom is set.
         * \param atom The atom for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_CHEM_API bool hasType(const Atom& atom);

        /**
         * \brief Returns the atom type that corresponds to the Chem::AtomProperty::SYMBOL property of the atom \a atom.
         * \param atom The atom to query.
         * \return The atom type mapped from the element symbol.
         */
        CDPL_CHEM_API unsigned int getTypeForSymbol(const Atom& atom);

        /**
         * \brief Returns the generic atom type that the atom's Chem::AtomProperty::TYPE property value belongs to.
         * \param atom The atom to query.
         * \return The generic atom type.
         */
        CDPL_CHEM_API unsigned int getGenericType(const Atom& atom); //move


        /**
         * \brief Returns the value of the Chem::AtomProperty::FORMAL_CHARGE property of the atom \a atom.
         * \param atom The atom for which to return the property value.
         * \return The stored formal charge.
         */
        CDPL_CHEM_API long getFormalCharge(const Atom& atom);

        /**
         * \brief Sets the value of the Chem::AtomProperty::FORMAL_CHARGE property of the atom \a atom to \a charge.
         * \param atom The atom for which to set the property value.
         * \param charge The new formal charge.
         */
        CDPL_CHEM_API void setFormalCharge(Atom& atom, long charge);

        /**
         * \brief Clears the value of the Chem::AtomProperty::FORMAL_CHARGE property of the atom \a atom.
         * \param atom The atom for which to clear the property value.
         */
        CDPL_CHEM_API void clearFormalCharge(Atom& atom);

        /**
         * \brief Tells whether the Chem::AtomProperty::FORMAL_CHARGE property of the atom \a atom is set.
         * \param atom The atom for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_CHEM_API bool hasFormalCharge(const Atom& atom);

        /**
         * \brief Computes the formal charge of the atom \a atom from its valence environment in the molecular graph \a molgraph.
         * \param atom The atom for which to calculate the charge.
         * \param molgraph The molecular graph providing the structural context.
         * \return The computed formal charge.
         */
        CDPL_CHEM_API long calcFormalCharge(const Atom& atom, const MolecularGraph& molgraph);


        /**
         * \brief Returns the value of the Chem::AtomProperty::ISOTOPE property of the atom \a atom.
         * \param atom The atom for which to return the property value.
         * \return The stored mass number, or zero for the natural isotope mixture.
         */
        CDPL_CHEM_API std::size_t getIsotope(const Atom& atom);

        /**
         * \brief Sets the value of the Chem::AtomProperty::ISOTOPE property of the atom \a atom to \a isotope.
         * \param atom The atom for which to set the property value.
         * \param isotope The new mass number (zero for the natural isotope mixture).
         */
        CDPL_CHEM_API void setIsotope(Atom& atom, std::size_t isotope);

        /**
         * \brief Clears the value of the Chem::AtomProperty::ISOTOPE property of the atom \a atom.
         * \param atom The atom for which to clear the property value.
         */
        CDPL_CHEM_API void clearIsotope(Atom& atom);

        /**
         * \brief Tells whether the Chem::AtomProperty::ISOTOPE property of the atom \a atom is set.
         * \param atom The atom for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_CHEM_API bool hasIsotope(const Atom& atom);


        /**
         * \brief Returns the value of the Chem::AtomProperty::RADICAL_TYPE property of the atom \a atom.
         * \param atom The atom for which to return the property value.
         * \return The stored radical type (see namespace Chem::RadicalType).
         */
        CDPL_CHEM_API unsigned int getRadicalType(const Atom& atom);

        /**
         * \brief Sets the value of the Chem::AtomProperty::RADICAL_TYPE property of the atom \a atom to \a type.
         * \param atom The atom for which to set the property value.
         * \param type The new radical type (see namespace Chem::RadicalType).
         */
        CDPL_CHEM_API void setRadicalType(Atom& atom, unsigned int type);

        /**
         * \brief Clears the value of the Chem::AtomProperty::RADICAL_TYPE property of the atom \a atom.
         * \param atom The atom for which to clear the property value.
         */
        CDPL_CHEM_API void clearRadicalType(Atom& atom);

        /**
         * \brief Tells whether the Chem::AtomProperty::RADICAL_TYPE property of the atom \a atom is set.
         * \param atom The atom for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_CHEM_API bool hasRadicalType(const Atom& atom);


        /**
         * \brief Returns the value of the Chem::AtomProperty::HYBRIDIZATION property of the atom \a atom.
         * \param atom The atom for which to return the property value.
         * \return The stored hybridization state (see namespace Chem::HybridizationState).
         */
        CDPL_CHEM_API unsigned int getHybridizationState(const Atom& atom);

        /**
         * \brief Sets the value of the Chem::AtomProperty::HYBRIDIZATION property of the atom \a atom to \a state.
         * \param atom The atom for which to set the property value.
         * \param state The new hybridization state (see namespace Chem::HybridizationState).
         */
        CDPL_CHEM_API void setHybridizationState(Atom& atom, unsigned int state);

        /**
         * \brief Clears the value of the Chem::AtomProperty::HYBRIDIZATION property of the atom \a atom.
         * \param atom The atom for which to clear the property value.
         */
        CDPL_CHEM_API void clearHybridizationState(Atom& atom);

        /**
         * \brief Tells whether the Chem::AtomProperty::HYBRIDIZATION property of the atom \a atom is set.
         * \param atom The atom for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_CHEM_API bool hasHybridizationState(const Atom& atom);

        /**
         * \brief Derives the hybridization state of the atom \a atom from its valence environment in the molecular graph \a molgraph.
         * \param atom The atom for which to perceive the hybridzation state.
         * \param molgraph The molecular graph providing the structural context.
         * \return The perceived hybridization state (see namespace Chem::HybridizationState).
         */
        CDPL_CHEM_API unsigned int perceiveHybridizationState(const Atom& atom, const MolecularGraph& molgraph);


        /**
         * \brief Returns the value of the Chem::AtomProperty::RING_FLAG property of the atom \a atom.
         * \param atom The atom for which to return the property value.
         * \return \c true if the atom is flagged as part of any ring, and \c false otherwise.
         */
        CDPL_CHEM_API bool getRingFlag(const Atom& atom);

        /**
         * \brief Sets the value of the Chem::AtomProperty::RING_FLAG property of the atom \a atom to \a in_ring.
         * \param atom The atom for which to set the property value.
         * \param in_ring \c true to flag the atom as part of a ring, and \c false to flag it as acyclic.
         */
        CDPL_CHEM_API void setRingFlag(Atom& atom, bool in_ring);

        /**
         * \brief Clears the value of the Chem::AtomProperty::RING_FLAG property of the atom \a atom.
         * \param atom The atom for which to clear the property value.
         */
        CDPL_CHEM_API void clearRingFlag(Atom& atom);

        /**
         * \brief Tells whether the Chem::AtomProperty::RING_FLAG property of the atom \a atom is set.
         * \param atom The atom for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_CHEM_API bool hasRingFlag(const Atom& atom);


        /**
         * \brief Tells whether the atom \a atom is a member of any fragment in \a frag_list whose size matches \a size.
         * \param atom The atom to query.
         * \param frag_list The list of fragments to search.
         * \param size The required fragment size (in number of atoms).
         * \return \c true if at least one matching fragment contains \a atom, and \c false otherwise.
         */
        CDPL_CHEM_API bool isInFragmentOfSize(const Atom& atom, const FragmentList& frag_list, std::size_t size);

        /**
         * \brief Returns the size (in atoms) of the smallest fragment in \a frag_list that contains the atom \a atom.
         * \param atom The atom to query.
         * \param frag_list The list of fragments to search.
         * \return The smallest containing fragment's size, or zero if no fragment contains \a atom.
         */
        CDPL_CHEM_API std::size_t getSizeOfSmallestContainingFragment(const Atom& atom, const FragmentList& frag_list);

        /**
         * \brief Returns the size (in atoms) of the largest fragment in \a frag_list that contains the atom \a atom.
         * \param atom The atom to query.
         * \param frag_list The list of fragments to search.
         * \return The largest containing fragment's size, or zero if no fragment contains \a atom.
         */
        CDPL_CHEM_API std::size_t getSizeOfLargestContainingFragment(const Atom& atom, const FragmentList& frag_list);

        /**
         * \brief Returns the number of fragments in \a frag_list that contain the atom \a atom.
         * \param atom The atom to query.
         * \param frag_list The list of fragments to search.
         * \return The number of containing fragments.
         */
        CDPL_CHEM_API std::size_t getNumContainingFragments(const Atom& atom, const FragmentList& frag_list);

        /**
         * \brief Collects the fragments in \a frag_list that contain the atom \a atom into \a cont_frag_list.
         * \param atom The atom to query.
         * \param frag_list The list of fragments to search.
         * \param cont_frag_list The output fragment list receiving the matches.
         * \param append If \c true, matches are appended to \a cont_frag_list. Otherwise, it is cleared first.
         */
        CDPL_CHEM_API void getContainingFragments(const Atom& atom, const FragmentList& frag_list, FragmentList& cont_frag_list, bool append = false);


        /**
         * \brief Returns the value of the Chem::AtomProperty::AROMATICITY_FLAG property of the atom \a atom.
         * \param atom The atom for which to return the property value.
         * \return \c true if the atom is flagged as aromatic, and \c false otherwise.
         */
        CDPL_CHEM_API bool getAromaticityFlag(const Atom& atom);

        /**
         * \brief Sets the value of the Chem::AtomProperty::AROMATICITY_FLAG property of the atom \a atom to \a aromatic.
         * \param atom The atom for which to set the property value.
         * \param aromatic \c true to flag the atom as aromatic, and \c false to flag it as non-aromatic.
         */
        CDPL_CHEM_API void setAromaticityFlag(Atom& atom, bool aromatic);

        /**
         * \brief Clears the value of the Chem::AtomProperty::AROMATICITY_FLAG property of the atom \a atom.
         * \param atom The atom for which to clear the property value.
         */
        CDPL_CHEM_API void clearAromaticityFlag(Atom& atom);

        /**
         * \brief Tells whether the Chem::AtomProperty::AROMATICITY_FLAG property of the atom \a atom is set.
         * \param atom The atom for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_CHEM_API bool hasAromaticityFlag(const Atom& atom);


        /**
         * \brief Returns the value of the Chem::AtomProperty::UNPAIRED_ELECTRON_COUNT property of the atom \a atom.
         * \param atom The atom for which to return the property value.
         * \return The stored unpaired electron count.
         */
        CDPL_CHEM_API std::size_t getUnpairedElectronCount(const Atom& atom);

        /**
         * \brief Sets the value of the Chem::AtomProperty::UNPAIRED_ELECTRON_COUNT property of the atom \a atom to \a count.
         * \param atom The atom for which to set the property value.
         * \param count The new unpaired electron count.
         */
        CDPL_CHEM_API void setUnpairedElectronCount(Atom& atom, std::size_t count);

        /**
         * \brief Clears the value of the Chem::AtomProperty::UNPAIRED_ELECTRON_COUNT property of the atom \a atom.
         * \param atom The atom for which to clear the property value.
         */
        CDPL_CHEM_API void clearUnpairedElectronCount(Atom& atom);

        /**
         * \brief Tells whether the Chem::AtomProperty::UNPAIRED_ELECTRON_COUNT property of the atom \a atom is set.
         * \param atom The atom for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_CHEM_API bool hasUnpairedElectronCount(const Atom& atom);


        /**
         * \brief Returns the value of the Chem::AtomProperty::IMPLICIT_HYDROGEN_COUNT property of the atom \a atom.
         * \param atom The atom for which to return the property value.
         * \return The stored implicit-hydrogen count.
         */
        CDPL_CHEM_API std::size_t getImplicitHydrogenCount(const Atom& atom);

        /**
         * \brief Sets the value of the Chem::AtomProperty::IMPLICIT_HYDROGEN_COUNT property of the atom \a atom to \a count.
         * \param atom The atom for which to set the property value.
         * \param count The new implicit-hydrogen count.
         */
        CDPL_CHEM_API void setImplicitHydrogenCount(Atom& atom, std::size_t count);

        /**
         * \brief Clears the value of the Chem::AtomProperty::IMPLICIT_HYDROGEN_COUNT property of the atom \a atom.
         * \param atom The atom for which to clear the property value.
         */
        CDPL_CHEM_API void clearImplicitHydrogenCount(Atom& atom);

        /**
         * \brief Tells whether the Chem::AtomProperty::IMPLICIT_HYDROGEN_COUNT property of the atom \a atom is set.
         * \param atom The atom for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_CHEM_API bool hasImplicitHydrogenCount(const Atom& atom);

        /**
         * \brief Computes the implicit hydrogen count of the atom \a atom from its valence environment in the molecular graph \a molgraph.
         * \param atom The atom for which to calculate the hydrogen count.
         * \param molgraph The molecular graph providing the structural context.
         * \return The computed implicit-hydrogen count.
         */
        CDPL_CHEM_API std::size_t calcImplicitHydrogenCount(const Atom& atom, const MolecularGraph& molgraph);


        /**
         * \brief Returns the value of the Chem::AtomProperty::COORDINATES_2D property of the atom \a atom.
         * \param atom The atom for which to return the property value.
         * \return The stored 2D coordinates.
         */
        CDPL_CHEM_API const Math::Vector2D& get2DCoordinates(const Atom& atom);

        /**
         * \brief Sets the value of the Chem::AtomProperty::COORDINATES_2D property of the atom \a atom to \a coords.
         * \param atom The atom for which to set the property value.
         * \param coords The new 2D coordinates.
         */
        CDPL_CHEM_API void set2DCoordinates(Atom& atom, const Math::Vector2D& coords);

        /**
         * \brief Clears the value of the Chem::AtomProperty::COORDINATES_2D property of the atom \a atom.
         * \param atom The atom for which to clear the property value.
         */
        CDPL_CHEM_API void clear2DCoordinates(Atom& atom);

        /**
         * \brief Tells whether the Chem::AtomProperty::COORDINATES_2D property of the atom \a atom is set.
         * \param atom The atom for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_CHEM_API bool has2DCoordinates(const Atom& atom);


        /**
         * \brief Returns the 3D coordinates of the atom \a atom for conformer \a conf_idx (from the Chem::AtomProperty::COORDINATES_3D_ARRAY property).
         * \param atom The atom for which to return the conformer 3D coordinates.
         * \param conf_idx The zero-based conformer index.
         * \return The 3D coordinates of the specified conformer.
         */
        CDPL_CHEM_API const Math::Vector3D& getConformer3DCoordinates(const Atom& atom, std::size_t conf_idx);


        /**
         * \brief Returns the value of the Chem::AtomProperty::COORDINATES_3D_ARRAY property of the atom \a atom.
         * \param atom The atom for which to return the property value.
         * \return The stored 3D conformer-coordinates array.
         */
        CDPL_CHEM_API const Math::Vector3DArray::SharedPointer& get3DCoordinatesArray(const Atom& atom);

        /**
         * \brief Sets the value of the Chem::AtomProperty::COORDINATES_3D_ARRAY property of the atom \a atom to \a coords_array.
         * \param atom The atom for which to set the property value.
         * \param coords_array The new 3D conformer-coordinates array.
         */
        CDPL_CHEM_API void set3DCoordinatesArray(Atom& atom, const Math::Vector3DArray::SharedPointer& coords_array);

        /**
         * \brief Clears the value of the Chem::AtomProperty::COORDINATES_3D_ARRAY property of the atom \a atom.
         * \param atom The atom for which to clear the property value.
         */
        CDPL_CHEM_API void clear3DCoordinatesArray(Atom& atom);

        /**
         * \brief Tells whether the Chem::AtomProperty::COORDINATES_3D_ARRAY property of the atom \a atom is set.
         * \param atom The atom for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_CHEM_API bool has3DCoordinatesArray(const Atom& atom);


        /**
         * \brief Returns the value of the Chem::AtomProperty::MORGAN_NUMBER property of the atom \a atom.
         * \param atom The atom for which to return the property value.
         * \return The stored Morgan number.
         */
        CDPL_CHEM_API std::size_t getMorganNumber(const Atom& atom);

        /**
         * \brief Sets the value of the Chem::AtomProperty::MORGAN_NUMBER property of the atom \a atom to \a num.
         * \param atom The atom for which to set the property value.
         * \param num The new Morgan number.
         */
        CDPL_CHEM_API void setMorganNumber(Atom& atom, std::size_t num);

        /**
         * \brief Clears the value of the Chem::AtomProperty::MORGAN_NUMBER property of the atom \a atom.
         * \param atom The atom for which to clear the property value.
         */
        CDPL_CHEM_API void clearMorganNumber(Atom& atom);

        /**
         * \brief Tells whether the Chem::AtomProperty::MORGAN_NUMBER property of the atom \a atom is set.
         * \param atom The atom for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_CHEM_API bool hasMorganNumber(const Atom& atom);


        /**
         * \brief Returns the value of the Chem::AtomProperty::CANONICAL_NUMBER property of the atom \a atom.
         * \param atom The atom for which to return the property value.
         * \return The stored canonical number.
         */
        CDPL_CHEM_API std::size_t getCanonicalNumber(const Atom& atom);

        /**
         * \brief Sets the value of the Chem::AtomProperty::CANONICAL_NUMBER property of the atom \a atom to \a num.
         * \param atom The atom for which to set the property value.
         * \param num The new canonical number.
         */
        CDPL_CHEM_API void setCanonicalNumber(Atom& atom, std::size_t num);

        /**
         * \brief Clears the value of the Chem::AtomProperty::CANONICAL_NUMBER property of the atom \a atom.
         * \param atom The atom for which to clear the property value.
         */
        CDPL_CHEM_API void clearCanonicalNumber(Atom& atom);

        /**
         * \brief Tells whether the Chem::AtomProperty::CANONICAL_NUMBER property of the atom \a atom is set.
         * \param atom The atom for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_CHEM_API bool hasCanonicalNumber(const Atom& atom);


        /**
         * \brief Returns the value of the Chem::AtomProperty::CIP_PRIORITY property of the atom \a atom.
         * \param atom The atom for which to return the property value.
         * \return The stored CIP priority.
         */
        CDPL_CHEM_API std::size_t getCIPPriority(const Atom& atom);

        /**
         * \brief Sets the value of the Chem::AtomProperty::CIP_PRIORITY property of the atom \a atom to \a priority.
         * \param atom The atom for which to set the property value.
         * \param priority The new CIP priority.
         */
        CDPL_CHEM_API void setCIPPriority(Atom& atom, std::size_t priority);

        /**
         * \brief Clears the value of the Chem::AtomProperty::CIP_PRIORITY property of the atom \a atom.
         * \param atom The atom for which to clear the property value.
         */
        CDPL_CHEM_API void clearCIPPriority(Atom& atom);

        /**
         * \brief Tells whether the Chem::AtomProperty::CIP_PRIORITY property of the atom \a atom is set.
         * \param atom The atom for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_CHEM_API bool hasCIPPriority(const Atom& atom);


        /**
         * \brief Returns the value of the Chem::AtomProperty::SYMMETRY_CLASS property of the atom \a atom.
         * \param atom The atom for which to return the property value.
         * \return The stored topological-symmetry class ID.
         */
        CDPL_CHEM_API std::size_t getSymmetryClass(const Atom& atom);

        /**
         * \brief Sets the value of the Chem::AtomProperty::SYMMETRY_CLASS property of the atom \a atom to \a class_id.
         * \param atom The atom for which to set the property value.
         * \param class_id The new topological-symmetry class ID.
         */
        CDPL_CHEM_API void setSymmetryClass(Atom& atom, std::size_t class_id);

        /**
         * \brief Clears the value of the Chem::AtomProperty::SYMMETRY_CLASS property of the atom \a atom.
         * \param atom The atom for which to clear the property value.
         */
        CDPL_CHEM_API void clearSymmetryClass(Atom& atom);

        /**
         * \brief Tells whether the Chem::AtomProperty::SYMMETRY_CLASS property of the atom \a atom is set.
         * \param atom The atom for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_CHEM_API bool hasSymmetryClass(const Atom& atom);


        /**
         * \brief Returns the value of the Chem::AtomProperty::CIP_CONFIGURATION property of the atom \a atom.
         * \param atom The atom for which to return the property value.
         * \return The stored CIP configuration label (see namespace Chem::CIPDescriptor).
         */
        CDPL_CHEM_API unsigned int getCIPConfiguration(const Atom& atom);

        /**
         * \brief Sets the value of the Chem::AtomProperty::CIP_CONFIGURATION property of the atom \a atom to \a config.
         * \param atom The atom for which to set the property value.
         * \param config The new CIP configuration label (see namespace Chem::CIPDescriptor).
         */
        CDPL_CHEM_API void setCIPConfiguration(Atom& atom, unsigned int config);

        /**
         * \brief Clears the value of the Chem::AtomProperty::CIP_CONFIGURATION property of the atom \a atom.
         * \param atom The atom for which to clear the property value.
         */
        CDPL_CHEM_API void clearCIPConfiguration(Atom& atom);

        /**
         * \brief Tells whether the Chem::AtomProperty::CIP_CONFIGURATION property of the atom \a atom is set.
         * \param atom The atom for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_CHEM_API bool hasCIPConfiguration(const Atom& atom);


        /**
         * \brief Returns the value of the Chem::AtomProperty::STEREO_DESCRIPTOR property of the atom \a atom.
         * \param atom The atom for which to return the property value.
         * \return The stored stereo descriptor.
         */
        CDPL_CHEM_API const StereoDescriptor& getStereoDescriptor(const Atom& atom);

        /**
         * \brief Sets the value of the Chem::AtomProperty::STEREO_DESCRIPTOR property of the atom \a atom to \a descr.
         * \param atom The atom for which to set the property value.
         * \param descr The new stereo descriptor.
         */
        CDPL_CHEM_API void setStereoDescriptor(Atom& atom, const StereoDescriptor& descr);

        /**
         * \brief Clears the value of the Chem::AtomProperty::STEREO_DESCRIPTOR property of the atom \a atom.
         * \param atom The atom for which to clear the property value.
         */
        CDPL_CHEM_API void clearStereoDescriptor(Atom& atom);

        /**
         * \brief Tells whether the Chem::AtomProperty::STEREO_DESCRIPTOR property of the atom \a atom is set.
         * \param atom The atom for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_CHEM_API bool hasStereoDescriptor(const Atom& atom);

        /**
         * \brief Computes the stereo descriptor for the atom \a atom based on the geometry of the molecular graph \a molgraph.
         * \param atom The atom for which to calculate the stereo descriptor.
         * \param molgraph The molecular graph providing the structural context.
         * \param dim The dimensionality of the atomic coordinates to use (\e 2 or \e 3).
         * \return The computed stereo descriptor.
         */
        CDPL_CHEM_API StereoDescriptor calcStereoDescriptor(const Atom& atom, const MolecularGraph& molgraph, std::size_t dim = 1);

        /**
         * \brief Derives the stereo descriptor of the atom \a atom from its MDL parity in the molecular graph \a molgraph.
         * \param atom The atom for which to calculate the stereo descriptor.
         * \param molgraph The molecular graph providing the structural context.
         * \return The derived stereo descriptor.
         */
        CDPL_CHEM_API StereoDescriptor calcStereoDescriptorFromMDLParity(const Atom& atom, const MolecularGraph& molgraph);

        /**
         * \brief Derives the atom configuration label from the supplied descriptor and 3D coordinates.
         * \param atom The atom for which to calculate the configuration.
         * \param molgraph The molecular graph providing the structural context.
         * \param descr The stereo descriptor whose configuration is to be evaluated.
         * \param coords The 3D atomic coordinates used by the evaluation.
         * \return The derived configuration label (see namespace Chem::AtomConfiguration).
         */
        CDPL_CHEM_API unsigned int calcConfiguration(const Atom& atom, const MolecularGraph& molgraph, const StereoDescriptor& descr,
                                                     const Math::Vector3DArray& coords);


        /**
         * \brief Returns the value of the Chem::AtomProperty::STEREO_CENTER_FLAG property of the atom \a atom.
         * \param atom The atom for which to return the property value.
         * \return \c true if the atom is flagged as a stereo center, and \c false otherwise.
         */
        CDPL_CHEM_API bool getStereoCenterFlag(const Atom& atom);

        /**
         * \brief Sets the value of the Chem::AtomProperty::STEREO_CENTER_FLAG property of the atom \a atom to \a is_center.
         * \param atom The atom for which to set the property value.
         * \param is_center \c true to flag the atom as a stereo center, and \c false otherwise.
         */
        CDPL_CHEM_API void setStereoCenterFlag(Atom& atom, bool is_center);

        /**
         * \brief Clears the value of the Chem::AtomProperty::STEREO_CENTER_FLAG property of the atom \a atom.
         * \param atom The atom for which to clear the property value.
         */
        CDPL_CHEM_API void clearStereoCenterFlag(Atom& atom);

        /**
         * \brief Tells whether the Chem::AtomProperty::STEREO_CENTER_FLAG property of the atom \a atom is set.
         * \param atom The atom for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_CHEM_API bool hasStereoCenterFlag(const Atom& atom);

        /**
         * \brief Tells whether the atom \a atom qualifies as a stereo center in the context of the molecular graph \a molgraph.
         * \param atom The atom to evaluate.
         * \param molgraph The molecular graph providing the structural context.
         * \param check_asym \c true to enforce non-equivalent ligand environments.
         * \param check_inv_n \c true to reject inversion-prone nitrogen centers (umbrella inversion).
         * \param check_quart_n \c true to accept positively charged quaternary nitrogen centers.
         * \param check_plan_n \c true to reject planar nitrogen centers.
         * \param check_amide_n \c true to reject amide-nitrogen centers.
         * \param check_res_ctrs \c true to reject centers participating in resonance.
         * \return \c true if the atom qualifies as a stereo center under the given conditions, and \c false otherwise.
         */
        CDPL_CHEM_API bool isStereoCenter(const Atom& atom, const MolecularGraph& molgraph, bool check_asym = true,
                                          bool check_inv_n = true, bool check_quart_n = true, bool check_plan_n = true,
                                          bool check_amide_n = true, bool check_res_ctrs = true);


        /**
         * \brief Returns the value of the Chem::AtomProperty::SYBYL_TYPE property of the atom \a atom.
         * \param atom The atom for which to return the property value.
         * \return The stored <em>Sybyl MOL2</em> atom type (see namespace Chem::SybylAtomType).
         */
        CDPL_CHEM_API unsigned int getSybylType(const Atom& atom);

        /**
         * \brief Sets the value of the Chem::AtomProperty::SYBYL_TYPE property of the atom \a atom to \a type.
         * \param atom The atom for which to set the property value.
         * \param type The new <em>Sybyl MOL2</em> atom type (see namespace Chem::SybylAtomType).
         */
        CDPL_CHEM_API void setSybylType(Atom& atom, unsigned int type);

        /**
         * \brief Clears the value of the Chem::AtomProperty::SYBYL_TYPE property of the atom \a atom.
         * \param atom The atom for which to clear the property value.
         */
        CDPL_CHEM_API void clearSybylType(Atom& atom);

        /**
         * \brief Tells whether the Chem::AtomProperty::SYBYL_TYPE property of the atom \a atom is set.
         * \param atom The atom for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_CHEM_API bool hasSybylType(const Atom& atom);

        /**
         * \brief Derives the <em>Sybyl MOL2</em> atom type of the atom \a atom from its valence environment in the molecular graph \a molgraph.
         * \param atom The atom for which to perceive the type.
         * \param molgraph The molecular graph providing the structural context.
         * \return The perceived <em>Sybyl MOL2</em> atom type (see namespace Chem::SybylAtomType).
         */
        CDPL_CHEM_API unsigned int perceiveSybylType(const Atom& atom, const MolecularGraph& molgraph);


        /**
         * \brief Returns the value of the Chem::AtomProperty::MOL2_NAME property of the atom \a atom.
         * \param atom The atom for which to return the property value.
         * \return The stored <em>Sybyl MOL2</em> atom name.
         */
        CDPL_CHEM_API const std::string& getMOL2Name(const Atom& atom);

        /**
         * \brief Sets the value of the Chem::AtomProperty::MOL2_NAME property of the atom \a atom to \a name.
         * \param atom The atom for which to set the property value.
         * \param name The new <em>Sybyl MOL2</em> atom name.
         */
        CDPL_CHEM_API void setMOL2Name(Atom& atom, const std::string& name);

        /**
         * \brief Clears the value of the Chem::AtomProperty::MOL2_NAME property of the atom \a atom.
         * \param atom The atom for which to clear the property value.
         */
        CDPL_CHEM_API void clearMOL2Name(Atom& atom);

        /**
         * \brief Tells whether the Chem::AtomProperty::MOL2_NAME property of the atom \a atom is set.
         * \param atom The atom for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_CHEM_API bool hasMOL2Name(const Atom& atom);


        /**
         * \brief Returns the value of the Chem::AtomProperty::MOL2_CHARGE property of the atom \a atom.
         * \param atom The atom for which to return the property value.
         * \return The stored <em>Sybyl MOL2</em> partial charge.
         */
        CDPL_CHEM_API double getMOL2Charge(const Atom& atom);

        /**
         * \brief Sets the value of the Chem::AtomProperty::MOL2_CHARGE property of the atom \a atom to \a charge.
         * \param atom The atom for which to set the property value.
         * \param charge The new <em>Sybyl MOL2</em> partial charge.
         */
        CDPL_CHEM_API void setMOL2Charge(Atom& atom, double charge);

        /**
         * \brief Clears the value of the Chem::AtomProperty::MOL2_CHARGE property of the atom \a atom.
         * \param atom The atom for which to clear the property value.
         */
        CDPL_CHEM_API void clearMOL2Charge(Atom& atom);

        /**
         * \brief Tells whether the Chem::AtomProperty::MOL2_CHARGE property of the atom \a atom is set.
         * \param atom The atom for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_CHEM_API bool hasMOL2Charge(const Atom& atom);


        /**
         * \brief Returns the value of the Chem::AtomProperty::MOL2_SUBSTRUCTURE_ID property of the atom \a atom.
         * \param atom The atom for which to return the property value.
         * \return The stored <em>Sybyl MOL2</em> substructure ID.
         */
        CDPL_CHEM_API std::size_t getMOL2SubstructureID(const Atom& atom);

        /**
         * \brief Sets the value of the Chem::AtomProperty::MOL2_SUBSTRUCTURE_ID property of the atom \a atom to \a id.
         * \param atom The atom for which to set the property value.
         * \param id The new <em>Sybyl MOL2</em> substructure ID.
         */
        CDPL_CHEM_API void setMOL2SubstructureID(Atom& atom, std::size_t id);

        /**
         * \brief Clears the value of the Chem::AtomProperty::MOL2_SUBSTRUCTURE_ID property of the atom \a atom.
         * \param atom The atom for which to clear the property value.
         */
        CDPL_CHEM_API void clearMOL2SubstructureID(Atom& atom);

        /**
         * \brief Tells whether the Chem::AtomProperty::MOL2_SUBSTRUCTURE_ID property of the atom \a atom is set.
         * \param atom The atom for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_CHEM_API bool hasMOL2SubstructureID(const Atom& atom);


        /**
         * \brief Returns the value of the Chem::AtomProperty::MOL2_SUBSTRUCTURE_NAME property of the atom \a atom.
         * \param atom The atom for which to return the property value.
         * \return The stored <em>Sybyl MOL2</em> substructure name.
         */
        CDPL_CHEM_API const std::string& getMOL2SubstructureName(const Atom& atom);

        /**
         * \brief Sets the value of the Chem::AtomProperty::MOL2_SUBSTRUCTURE_NAME property of the atom \a atom to \a id.
         * \param atom The atom for which to set the property value.
         * \param id The new <em>Sybyl MOL2</em> substructure name.
         */
        CDPL_CHEM_API void setMOL2SubstructureName(Atom& atom, const std::string& id);

        /**
         * \brief Clears the value of the Chem::AtomProperty::MOL2_SUBSTRUCTURE_NAME property of the atom \a atom.
         * \param atom The atom for which to clear the property value.
         */
        CDPL_CHEM_API void clearMOL2SubstructureName(Atom& atom);

        /**
         * \brief Tells whether the Chem::AtomProperty::MOL2_SUBSTRUCTURE_NAME property of the atom \a atom is set.
         * \param atom The atom for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_CHEM_API bool hasMOL2SubstructureName(const Atom& atom);


        /**
         * \brief Returns the value of the Chem::AtomProperty::MOL2_SUBSTRUCTURE_SUBTYPE property of the atom \a atom.
         * \param atom The atom for which to return the property value.
         * \return The stored <em>Sybyl MOL2</em> substructure subtype string.
         */
        CDPL_CHEM_API const std::string& getMOL2SubstructureSubtype(const Atom& atom);

        /**
         * \brief Sets the value of the Chem::AtomProperty::MOL2_SUBSTRUCTURE_SUBTYPE property of the atom \a atom to \a subtype.
         * \param atom The atom for which to set the property value.
         * \param subtype The new <em>Sybyl MOL2</em> substructure subtype string.
         */
        CDPL_CHEM_API void setMOL2SubstructureSubtype(Atom& atom, const std::string& subtype);

        /**
         * \brief Clears the value of the Chem::AtomProperty::MOL2_SUBSTRUCTURE_SUBTYPE property of the atom \a atom.
         * \param atom The atom for which to clear the property value.
         */
        CDPL_CHEM_API void clearMOL2SubstructureSubtype(Atom& atom);

        /**
         * \brief Tells whether the Chem::AtomProperty::MOL2_SUBSTRUCTURE_SUBTYPE property of the atom \a atom is set.
         * \param atom The atom for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_CHEM_API bool hasMOL2SubstructureSubtype(const Atom& atom);


        /**
         * \brief Returns the value of the Chem::AtomProperty::MOL2_SUBSTRUCTURE_CHAIN property of the atom \a atom.
         * \param atom The atom for which to return the property value.
         * \return The stored <em>Sybyl MOL2</em> substructure chain identifier.
         */
        CDPL_CHEM_API const std::string& getMOL2SubstructureChain(const Atom& atom);

        /**
         * \brief Sets the value of the Chem::AtomProperty::MOL2_SUBSTRUCTURE_CHAIN property of the atom \a atom to \a chain.
         * \param atom The atom for which to set the property value.
         * \param chain The new <em>Sybyl MOL2</em> substructure chain identifier.
         */
        CDPL_CHEM_API void setMOL2SubstructureChain(Atom& atom, const std::string& chain);

        /**
         * \brief Clears the value of the Chem::AtomProperty::MOL2_SUBSTRUCTURE_CHAIN property of the atom \a atom.
         * \param atom The atom for which to clear the property value.
         */
        CDPL_CHEM_API void clearMOL2SubstructureChain(Atom& atom);

        /**
         * \brief Tells whether the Chem::AtomProperty::MOL2_SUBSTRUCTURE_CHAIN property of the atom \a atom is set.
         * \param atom The atom for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_CHEM_API bool hasMOL2SubstructureChain(const Atom& atom);


        /**
         * \brief Returns the value of the Chem::AtomProperty::MDL_PARITY property of the atom \a atom.
         * \param atom The atom for which to return the property value.
         * \return The stored MDL stereo parity (see namespace Chem::MDLParity).
         */
        CDPL_CHEM_API unsigned int getMDLParity(const Atom& atom);

        /**
         * \brief Sets the value of the Chem::AtomProperty::MDL_PARITY property of the atom \a atom to \a parity.
         * \param atom The atom for which to set the property value.
         * \param parity The new MDL stereo parity (see namespace Chem::MDLParity).
         */
        CDPL_CHEM_API void setMDLParity(Atom& atom, unsigned int parity);

        /**
         * \brief Clears the value of the Chem::AtomProperty::MDL_PARITY property of the atom \a atom.
         * \param atom The atom for which to clear the property value.
         */
        CDPL_CHEM_API void clearMDLParity(Atom& atom);

        /**
         * \brief Tells whether the Chem::AtomProperty::MDL_PARITY property of the atom \a atom is set.
         * \param atom The atom for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_CHEM_API bool hasMDLParity(const Atom& atom);

        /**
         * \brief Computes the MDL parity of the atom \a atom from its 2D layout and stereo flags in the molecular graph \a molgraph.
         * \param atom The atom for which to calculate the parity.
         * \param molgraph The molecular graph providing the structural context.
         * \return The computed MDL parity (see namespace Chem::MDLParity).
         */
        CDPL_CHEM_API unsigned int calcMDLParity(const Atom& atom, const MolecularGraph& molgraph);


        /**
         * \brief Returns the value of the Chem::AtomProperty::MDL_DB_STEREO_CARE_FLAG property of the atom \a atom.
         * \param atom The atom for which to return the property value.
         * \return The stored MDL stereo-care flag.
         */
        CDPL_CHEM_API bool getMDLStereoCareFlag(const Atom& atom);

        /**
         * \brief Sets the value of the Chem::AtomProperty::MDL_DB_STEREO_CARE_FLAG property of the atom \a atom to \a flag.
         * \param atom The atom for which to set the property value.
         * \param flag The new MDL stereo-care flag.
         */
        CDPL_CHEM_API void setMDLStereoCareFlag(Atom& atom, bool flag);

        /**
         * \brief Clears the value of the Chem::AtomProperty::MDL_DB_STEREO_CARE_FLAG property of the atom \a atom.
         * \param atom The atom for which to clear the property value.
         */
        CDPL_CHEM_API void clearMDLStereoCareFlag(Atom& atom);

        /**
         * \brief Tells whether the Chem::AtomProperty::MDL_DB_STEREO_CARE_FLAG property of the atom \a atom is set.
         * \param atom The atom for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_CHEM_API bool hasMDLStereoCareFlag(const Atom& atom);


        /**
         * \brief Returns the value of the Chem::AtomProperty::REACTION_CENTER_STATUS property of the atom \a atom.
         * \param atom The atom for which to return the property value.
         * \return The stored reaction-center status (see namespace Chem::ReactionCenterStatus).
         */
        CDPL_CHEM_API unsigned int getReactionCenterStatus(const Atom& atom);

        /**
         * \brief Sets the value of the Chem::AtomProperty::REACTION_CENTER_STATUS property of the atom \a atom to \a status.
         * \param atom The atom for which to set the property value.
         * \param status The new reaction-center status (see namespace Chem::ReactionCenterStatus).
         */
        CDPL_CHEM_API void setReactionCenterStatus(Atom& atom, unsigned int status);

        /**
         * \brief Clears the value of the Chem::AtomProperty::REACTION_CENTER_STATUS property of the atom \a atom.
         * \param atom The atom for which to clear the property value.
         */
        CDPL_CHEM_API void clearReactionCenterStatus(Atom& atom);

        /**
         * \brief Tells whether the Chem::AtomProperty::REACTION_CENTER_STATUS property of the atom \a atom is set.
         * \param atom The atom for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_CHEM_API bool hasReactionCenterStatus(const Atom& atom);


        /**
         * \brief Returns the value of the Chem::AtomProperty::ATOM_MAPPING_ID property of the atom \a atom.
         * \param atom The atom for which to return the property value.
         * \return The stored reactant-to-product atom-mapping ID.
         */
        CDPL_CHEM_API std::size_t getAtomMappingID(const Atom& atom);

        /**
         * \brief Sets the value of the Chem::AtomProperty::ATOM_MAPPING_ID property of the atom \a atom to \a id.
         * \param atom The atom for which to set the property value.
         * \param id The new reactant-to-product atom-mapping ID.
         */
        CDPL_CHEM_API void setAtomMappingID(Atom& atom, std::size_t id);

        /**
         * \brief Clears the value of the Chem::AtomProperty::ATOM_MAPPING_ID property of the atom \a atom.
         * \param atom The atom for which to clear the property value.
         */
        CDPL_CHEM_API void clearAtomMappingID(Atom& atom);

        /**
         * \brief Tells whether the Chem::AtomProperty::ATOM_MAPPING_ID property of the atom \a atom is set.
         * \param atom The atom for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_CHEM_API bool hasAtomMappingID(const Atom& atom);


        /**
         * \brief Returns the value of the Chem::AtomProperty::COMPONENT_GROUP_ID property of the atom \a atom.
         * \param atom The atom for which to return the property value.
         * \return The stored component-group ID.
         */
        CDPL_CHEM_API std::size_t getComponentGroupID(const Atom& atom);

        /**
         * \brief Sets the value of the Chem::AtomProperty::COMPONENT_GROUP_ID property of the atom \a atom to \a id.
         * \param atom The atom for which to set the property value.
         * \param id The new component-group ID.
         */
        CDPL_CHEM_API void setComponentGroupID(Atom& atom, std::size_t id);

        /**
         * \brief Clears the value of the Chem::AtomProperty::COMPONENT_GROUP_ID property of the atom \a atom.
         * \param atom The atom for which to clear the property value.
         */
        CDPL_CHEM_API void clearComponentGroupID(Atom& atom);

        /**
         * \brief Tells whether the Chem::AtomProperty::COMPONENT_GROUP_ID property of the atom \a atom is set.
         * \param atom The atom for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_CHEM_API bool hasComponentGroupID(const Atom& atom);


        /**
         * \brief Returns the value of the Chem::AtomProperty::MATCH_CONSTRAINTS property of the atom \a atom.
         * \param atom The atom for which to return the property value.
         * \return The stored match constraint list.
         */
        CDPL_CHEM_API const MatchConstraintList::SharedPointer& getMatchConstraints(const Atom& atom);

        /**
         * \brief Sets the value of the Chem::AtomProperty::MATCH_CONSTRAINTS property of the atom \a atom to \a constr.
         * \param atom The atom for which to set the property value.
         * \param constr The new match constraint list.
         */
        CDPL_CHEM_API void setMatchConstraints(Atom& atom, const MatchConstraintList::SharedPointer& constr);

        /**
         * \brief Clears the value of the Chem::AtomProperty::MATCH_CONSTRAINTS property of the atom \a atom.
         * \param atom The atom for which to clear the property value.
         */
        CDPL_CHEM_API void clearMatchConstraints(Atom& atom);

        /**
         * \brief Tells whether the Chem::AtomProperty::MATCH_CONSTRAINTS property of the atom \a atom is set.
         * \param atom The atom for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_CHEM_API bool hasMatchConstraints(const Atom& atom);


        /**
         * \brief Returns the value of the Chem::AtomProperty::MATCH_EXPRESSION property of the atom \a atom.
         * \param atom The atom for which to return the property value.
         * \return The stored atom-level match expression.
         */
        CDPL_CHEM_API const MatchExpression<Atom, MolecularGraph>::SharedPointer& getMatchExpression(const Atom& atom);

        /**
         * \brief Sets the value of the Chem::AtomProperty::MATCH_EXPRESSION property of the atom \a atom to \a expr.
         * \param atom The atom for which to set the property value.
         * \param expr The new atom-level match expression.
         */
        CDPL_CHEM_API void setMatchExpression(Atom& atom, const MatchExpression<Atom, MolecularGraph>::SharedPointer& expr);

        /**
         * \brief Clears the value of the Chem::AtomProperty::MATCH_EXPRESSION property of the atom \a atom.
         * \param atom The atom for which to clear the property value.
         */
        CDPL_CHEM_API void clearMatchExpression(Atom& atom);

        /**
         * \brief Tells whether the Chem::AtomProperty::MATCH_EXPRESSION property of the atom \a atom is set.
         * \param atom The atom for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_CHEM_API bool hasMatchExpression(const Atom& atom);

        /**
         * \brief Builds an atom-level match expression from the match constraint list attached to the atom \a atom.
         * \param atom The atom for which to generate the expression.
         * \param molgraph The molecular graph providing the structural context.
         * \return The generated match expression.
         */
        CDPL_CHEM_API MatchExpression<Atom, MolecularGraph>::SharedPointer generateMatchExpression(const Atom& atom, const MolecularGraph& molgraph);


        /**
         * \brief Returns the value of the Chem::AtomProperty::MATCH_EXPRESSION_STRING property of the atom \a atom.
         * \param atom The atom for which to return the property value.
         * \return The stored match expression string.
         */
        CDPL_CHEM_API const std::string& getMatchExpressionString(const Atom& atom);

        /**
         * \brief Sets the value of the Chem::AtomProperty::MATCH_EXPRESSION_STRING property of the atom \a atom to \a expr_str.
         * \param atom The atom for which to set the property value.
         * \param expr_str The new match expression string.
         */
        CDPL_CHEM_API void setMatchExpressionString(Atom& atom, const std::string& expr_str);

        /**
         * \brief Clears the value of the Chem::AtomProperty::MATCH_EXPRESSION_STRING property of the atom \a atom.
         * \param atom The atom for which to clear the property value.
         */
        CDPL_CHEM_API void clearMatchExpressionString(Atom& atom);

        /**
         * \brief Tells whether the Chem::AtomProperty::MATCH_EXPRESSION_STRING property of the atom \a atom is set.
         * \param atom The atom for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_CHEM_API bool hasMatchExpressionString(const Atom& atom);

        /**
         * \brief Writes a textual representation of the atom-level match expression of the atom \a atom into \a expr_str.
         * \param atom The atom for which to generate the expression string.
         * \param molgraph The molecular graph providing the structural context.
         * \param expr_str The output string receiving the match expression text.
         */
        CDPL_CHEM_API void generateMatchExpressionString(const Atom& atom, const MolecularGraph& molgraph, std::string& expr_str);


        /**
         * \brief Sets bits in \a atom_mask for every atom of the molecular graph \a molgraph that is reachable from the atom \a atom through the bonds of \a molgraph.
         * \param atom The seed atom.
         * \param molgraph The molecular graph providing the bonding context.
         * \param atom_mask The output bit mask.
         * \param reset If \c true, \a atom_mask is cleared first. Otherwise, existing bits are preserved.
         */
        CDPL_CHEM_API void markReachableAtoms(const Atom& atom, const MolecularGraph& molgraph,
                                              Util::BitSet& atom_mask, bool reset = true);

        /**
         * \brief Returns the topological distance between two atoms of the molecular graph \a molgraph.
         * \param atom1 The first atom.
         * \param atom2 The second atom.
         * \param molgraph The molecular graph providing the bonding context.
         * \return The topological distance between \a atom1 and \a atom2.
         */
        CDPL_CHEM_API std::size_t getTopologicalDistance(const Atom& atom1, const Atom& atom2, const MolecularGraph& molgraph);

        /**
         * \brief Collects every atom of the molecular graph \a molgraph that is within \a max_dist bonds of the atom \a atom into the fragment \a env.
         * \param atom The seed atom.
         * \param molgraph The molecular graph providing the bonding context.
         * \param max_dist The maximum topological distance.
         * \param env The output fragment receiving the environment atoms and the bonds between them.
         * \param append If \c true, atoms/bonds are appended to \a env. Otherwise, it is cleared first.
         * \return The number of atoms appended to \a env.
         */
        CDPL_CHEM_API std::size_t getEnvironment(const Atom& atom, const MolecularGraph& molgraph, std::size_t max_dist, Fragment& env, bool append = false);


        /**
         * \brief Writes every neighbor of the atom \a atom (with bonds belonging to the molecular graph \a molgraph) into \a it, skipping \a excl_atom.
         * \tparam AtomType The atom type (\c Atom or <tt>const Atom</tt>); the constness selects between AtomIterator and ConstAtomIterator.
         * \tparam OutputIterator The output iterator type receiving pointers to the neighbor atoms.
         * \param atom The atom whose neighbors are to be enumerated.
         * \param molgraph The molecular graph used to filter the atom/bond membership.
         * \param it The output iterator receiving the neighbor pointers.
         * \param excl_atom If non-null, a neighbor matching this pointer is skipped.
         * \return The number of neighbors written to \a it.
         */
        template <typename AtomType, typename OutputIterator>
        std::size_t getConnectedAtoms(AtomType& atom, const MolecularGraph& molgraph, OutputIterator it, AtomType* excl_atom = 0)
        {
            typedef typename std::conditional<std::is_const<AtomType>::value, typename AtomType::ConstAtomIterator, typename AtomType::AtomIterator>::type AtomIterator;

            AtomIterator                         atoms_end = atom.getAtomsEnd();
            typename AtomType::ConstBondIterator b_it      = atom.getBondsBegin();
            std::size_t                          count     = 0;

            for (AtomIterator a_it = atom.getAtomsBegin(); a_it != atoms_end; ++a_it, ++b_it) {
                if (&(*a_it) == excl_atom)
                    continue;

                if (molgraph.containsAtom(*a_it) && molgraph.containsBond(*b_it)) {
                    *it = &(*a_it);
                    ++it;
                    count++;
                }
            }

            return count;
        }

        /**
         * \brief Writes every bond incident to the atom \a atom (with both endpoints belonging to the molecular graph \a molgraph) into \a it, skipping bonds to \a excl_atom.
         * \tparam AtomType The atom type (\c Atom or <tt>const Atom</tt>).
         * \tparam OutputIterator The output iterator type receiving pointers to the incident bonds.
         * \param atom The atom whose incident bonds are to be enumerated.
         * \param molgraph The molecular graph used to filter the atom/bond membership.
         * \param it The output iterator receiving the bond pointers.
         * \param excl_atom If non-null, bonds whose neighbor matches this pointer are skipped.
         * \return The number of bonds written to \a it.
         */
        template <typename AtomType, typename OutputIterator>
        std::size_t getIncidentBonds(AtomType& atom, const MolecularGraph& molgraph, OutputIterator it, AtomType* excl_atom = 0)
        {
            typedef typename std::conditional<std::is_const<AtomType>::value, typename AtomType::ConstBondIterator, typename AtomType::BondIterator>::type BondIterator;

            BondIterator                         bonds_end = atom.getBondsEnd();
            typename AtomType::ConstAtomIterator a_it      = atom.getAtomsBegin();
            std::size_t                          count     = 0;

            for (BondIterator b_it = atom.getBondsBegin(); b_it != bonds_end; ++a_it, ++b_it) {
                if (&(*a_it) == excl_atom)
                    continue;

                if (molgraph.containsAtom(*a_it) && molgraph.containsBond(*b_it)) {
                    *it = &(*b_it);
                    ++it;
                    count++;
                }
            }

            return count;
        }

        /**
         * \brief Writes every neighbor of the atom \a atom and the corresponding incident bond (both filtered by the molecular graph \a molgraph) into the supplied output iterators.
         * \tparam AtomType The atom type (\c Atom or <tt>const Atom</tt>).
         * \tparam AtomOutputIterator The output iterator type receiving neighbor-atom pointers.
         * \tparam BondOutputIterator The output iterator type receiving incident-bond pointers.
         * \param atom The atom whose neighborhood is to be enumerated.
         * \param molgraph The molecular graph used to filter the atom/bond membership.
         * \param ao_it The output iterator receiving the neighbor-atom pointers.
         * \param bo_it The output iterator receiving the corresponding incident-bond pointers.
         * \param excl_atom If non-null, a neighbor matching this pointer (and its bond) is skipped.
         * \return The number of atom/bond pairs written to the iterators.
         */
        template <typename AtomType, typename AtomOutputIterator, typename BondOutputIterator>
        std::size_t getConnectedAtomsAndBonds(AtomType& atom, const MolecularGraph& molgraph, AtomOutputIterator ao_it, BondOutputIterator bo_it, AtomType* excl_atom = 0)
        {
            typedef typename std::conditional<std::is_const<AtomType>::value, typename AtomType::ConstAtomIterator, typename AtomType::AtomIterator>::type AtomIterator;
            typedef typename std::conditional<std::is_const<AtomType>::value, typename AtomType::ConstBondIterator, typename AtomType::BondIterator>::type BondIterator;

            BondIterator bonds_end = atom.getBondsEnd();
            AtomIterator a_it      = atom.getAtomsBegin();
            std::size_t  count     = 0;

            for (BondIterator b_it = atom.getBondsBegin(); b_it != bonds_end; ++a_it, ++b_it) {
                if (&(*a_it) == excl_atom)
                    continue;

                if (molgraph.containsAtom(*a_it) && molgraph.containsBond(*b_it)) {
                    *ao_it = &(*a_it);
                    *bo_it = &(*b_it);
                    ++ao_it;
                    ++bo_it;
                    count++;
                }
            }

            return count;
        }
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_ATOMFUNCTIONS_HPP
