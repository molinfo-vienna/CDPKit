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

#ifndef CDPL_BIOMOL_ATOMFUNCTIONS_HPP
#define CDPL_BIOMOL_ATOMFUNCTIONS_HPP

#include <cstddef>
#include <string>

#include "CDPL/Biomol/APIPrefix.hpp"
#include "CDPL/Biomol/ProcessingFlags.hpp"
#include "CDPL/Biomol/AtomPropertyFlag.hpp"


namespace CDPL
{

    namespace Chem
    {

        class Atom;
        class MolecularGraph;
        class Fragment;
    } // namespace Chem

    namespace Biomol
    {

        /**
         * \brief Returns the value of the Biomol::AtomProperty::RESIDUE_ATOM_NAME property of the atom \a atom.
         * \param atom The atom for which to return the property value.
         * \return A \c const reference to the residue atom name.
         */
        CDPL_BIOMOL_API const std::string& getResidueAtomName(const Chem::Atom& atom);

        /**
         * \brief Sets the value of the Biomol::AtomProperty::RESIDUE_ATOM_NAME property of the atom \a atom to \a name.
         * \param atom The atom for which to set the property value.
         * \param name The new residuel atom name.
         */
        CDPL_BIOMOL_API void setResidueAtomName(Chem::Atom& atom, const std::string& name);

        /**
         * \brief Clears the value of the Biomol::AtomProperty::RESIDUE_ATOM_NAME property of the atom \a atom.
         * \param atom The atom for which to clear the property value.
         */
        CDPL_BIOMOL_API void clearResidueAtomName(Chem::Atom& atom);

        /**
         * \brief Tells whether the Biomol::AtomProperty::RESIDUE_ATOM_NAME property of the atom \a atom is set.
         * \param atom The atom for which to query the property value.
         * \return \c true if the residue atom name is set, and \c false otherwise.
         */
        CDPL_BIOMOL_API bool hasResidueAtomName(const Chem::Atom& atom);


        /**
         * \brief Returns the value of the Biomol::AtomProperty::RESIDUE_ALT_ATOM_NAME property of the atom \a atom.
         * \param atom The atom for which to return the property value.
         * \return A \c const reference to the alternative residue atom name.
         */
        CDPL_BIOMOL_API const std::string& getResidueAltAtomName(const Chem::Atom& atom);

        /**
         * \brief Sets the value of the Biomol::AtomProperty::RESIDUE_ALT_ATOM_NAME property of the atom \a atom to \a name.
         * \param atom The atom for which to set the property value.
         * \param name The new alternative residue atom name.
         */
        CDPL_BIOMOL_API void setResidueAltAtomName(Chem::Atom& atom, const std::string& name);

        /**
         * \brief Clears the value of the Biomol::AtomProperty::RESIDUE_ALT_ATOM_NAME property of the atom \a atom.
         * \param atom The atom for which to clear the property value.
         */
        CDPL_BIOMOL_API void clearResidueAltAtomName(Chem::Atom& atom);

        /**
         * \brief Tells whether the Biomol::AtomProperty::RESIDUE_ALT_ATOM_NAME property of the atom \a atom is set.
         * \param atom The atom for which to query the property value.
         * \return \c true if the alternative residue atom name is set, and \c false otherwise.
         */
        CDPL_BIOMOL_API bool hasResidueAltAtomName(const Chem::Atom& atom);


        /**
         * \brief Returns the value of the Biomol::AtomProperty::RESIDUE_LEAVING_ATOM_FLAG property of the atom \a atom.
         * \param atom The atom for which to return the property value.
         * \return \c true if the atom is a leaving atom in its parent residue, and \c false otherwise.
         */
        CDPL_BIOMOL_API bool getResidueLeavingAtomFlag(const Chem::Atom& atom);

        /**
         * \brief Sets the value of the Biomol::AtomProperty::RESIDUE_LEAVING_ATOM_FLAG property of the atom \a atom to \a leaving.
         * \param atom The atom for which to set the property value.
         * \param leaving \c true to mark the atom as a leaving atom, and \c false otherwise.
         */
        CDPL_BIOMOL_API void setResidueLeavingAtomFlag(Chem::Atom& atom, bool leaving);

        /**
         * \brief Clears the value of the Biomol::AtomProperty::RESIDUE_LEAVING_ATOM_FLAG property of the atom \a atom.
         * \param atom The atom for which to clear the property value.
         */
        CDPL_BIOMOL_API void clearResidueLeavingAtomFlag(Chem::Atom& atom);

        /**
         * \brief Tells whether the Biomol::AtomProperty::RESIDUE_LEAVING_ATOM_FLAG property of the atom \a atom is set.
         * \param atom The atom for which to query the property value.
         * \return \c true if the leaving atom flag is set, and \c false otherwise.
         */
        CDPL_BIOMOL_API bool hasResidueLeavingAtomFlag(const Chem::Atom& atom);


        /**
         * \brief Returns the value of the Biomol::AtomProperty::RESIDUE_LINKING_ATOM_FLAG property of the atom \a atom.
         * \param atom The atom for which to return the property value.
         * \return \c true if the atom is a linking atom between residues, and \c false otherwise.
         */
        CDPL_BIOMOL_API bool getResidueLinkingAtomFlag(const Chem::Atom& atom);

        /**
         * \brief Sets the value of the Biomol::AtomProperty::RESIDUE_LINKING_ATOM_FLAG property of the atom \a atom to \a linking.
         * \param atom The atom for which to set the property value.
         * \param linking \c true to mark the atom as a linking atom, and \c false otherwise.
         */
        CDPL_BIOMOL_API void setResidueLinkingAtomFlag(Chem::Atom& atom, bool linking);

        /**
         * \brief Clears the value of the Biomol::AtomProperty::RESIDUE_LINKING_ATOM_FLAG property of the atom \a atom.
         * \param atom The atom for which to clear the property value.
         */
        CDPL_BIOMOL_API void clearResidueLinkingAtomFlag(Chem::Atom& atom);

        /**
         * \brief Tells whether the Biomol::AtomProperty::RESIDUE_LINKING_ATOM_FLAG property of the atom \a atom is set.
         * \param atom The atom for which to query the property value.
         * \return \c true if the linking atom flag is set, and \c false otherwise.
         */
        CDPL_BIOMOL_API bool hasResidueLinkingAtomFlag(const Chem::Atom& atom);


        /**
         * \brief Returns the value of the Biomol::AtomProperty::RESIDUE_CODE property of the atom \a atom.
         * \param atom The atom for which to return the property value.
         * \return A \c const reference to the residue three-letter code.
         */
        CDPL_BIOMOL_API const std::string& getResidueCode(const Chem::Atom& atom);

        /**
         * \brief Sets the value of the Biomol::AtomProperty::RESIDUE_CODE property of the atom \a atom to \a code.
         * \param atom The atom for which to set the property value.
         * \param code The new residue three-letter code.
         */
        CDPL_BIOMOL_API void setResidueCode(Chem::Atom& atom, const std::string& code);

        /**
         * \brief Clears the value of the Biomol::AtomProperty::RESIDUE_CODE property of the atom \a atom.
         * \param atom The atom for which to clear the property value.
         */
        CDPL_BIOMOL_API void clearResidueCode(Chem::Atom& atom);

        /**
         * \brief Tells whether the Biomol::AtomProperty::RESIDUE_CODE property of the atom \a atom is set.
         * \param atom The atom for which to query the property value.
         * \return \c true if the residue code is set, and \c false otherwise.
         */
        CDPL_BIOMOL_API bool hasResidueCode(const Chem::Atom& atom);


        /**
         * \brief Returns the value of the Biomol::AtomProperty::RESIDUE_SEQUENCE_NUMBER property of the atom \a atom.
         * \param atom The atom for which to return the property value.
         * \return The residue sequence number.
         */
        CDPL_BIOMOL_API long getResidueSequenceNumber(const Chem::Atom& atom);

        /**
         * \brief Sets the value of the Biomol::AtomProperty::RESIDUE_SEQUENCE_NUMBER property of the atom \a atom to \a seq_no.
         * \param atom The atom for which to set the property value.
         * \param seq_no The new residue sequence number.
         */
        CDPL_BIOMOL_API void setResidueSequenceNumber(Chem::Atom& atom, long seq_no);

        /**
         * \brief Clears the value of the Biomol::AtomProperty::RESIDUE_SEQUENCE_NUMBER property of the atom \a atom.
         * \param atom The atom for which to clear the property value.
         */
        CDPL_BIOMOL_API void clearResidueSequenceNumber(Chem::Atom& atom);

        /**
         * \brief Tells whether the Biomol::AtomProperty::RESIDUE_SEQUENCE_NUMBER property of the atom \a atom is set.
         * \param atom The atom for which to query the property value.
         * \return \c true if the residue sequence number is set, and \c false otherwise.
         */
        CDPL_BIOMOL_API bool hasResidueSequenceNumber(const Chem::Atom& atom);


        /**
         * \brief Returns the value of the Biomol::AtomProperty::RESIDUE_INSERTION_CODE property of the atom \a atom.
         * \param atom The atom for which to return the property value.
         * \return The residue insertion code.
         */
        CDPL_BIOMOL_API char getResidueInsertionCode(const Chem::Atom& atom);

        /**
         * \brief Sets the value of the Biomol::AtomProperty::RESIDUE_INSERTION_CODE property of the atom \a atom to \a code.
         * \param atom The atom for which to set the property value.
         * \param code The new residue insertion code.
         */
        CDPL_BIOMOL_API void setResidueInsertionCode(Chem::Atom& atom, char code);

        /**
         * \brief Clears the value of the Biomol::AtomProperty::RESIDUE_INSERTION_CODE property of the atom \a atom.
         * \param atom The atom for which to clear the property value.
         */
        CDPL_BIOMOL_API void clearResidueInsertionCode(Chem::Atom& atom);

        /**
         * \brief Tells whether the Biomol::AtomProperty::RESIDUE_INSERTION_CODE property of the atom \a atom is set.
         * \param atom The atom for which to query the property value.
         * \return \c true if the residue insertion code is set, and \c false otherwise.
         */
        CDPL_BIOMOL_API bool hasResidueInsertionCode(const Chem::Atom& atom);


        /**
         * \brief Returns the value of the Biomol::AtomProperty::HETERO_ATOM_FLAG property of the atom \a atom.
         * \param atom The atom for which to return the property value.
         * \return \c true if the atom is flagged as a heteroatom (\e PDB \c HETATM record), and \c false otherwise.
         */
        CDPL_BIOMOL_API bool getHeteroAtomFlag(const Chem::Atom& atom);

        /**
         * \brief Sets the value of the Biomol::AtomProperty::HETERO_ATOM_FLAG property of the atom \a atom to \a is_het.
         * \param atom The atom for which to set the property value.
         * \param is_het \c true to mark the atom as a heteroatom, and \c false otherwise.
         */
        CDPL_BIOMOL_API void setHeteroAtomFlag(Chem::Atom& atom, bool is_het);

        /**
         * \brief Clears the value of the Biomol::AtomProperty::HETERO_ATOM_FLAG property of the atom \a atom.
         * \param atom The atom for which to clear the property value.
         */
        CDPL_BIOMOL_API void clearHeteroAtomFlag(Chem::Atom& atom);

        /**
         * \brief Tells whether the Biomol::AtomProperty::HETERO_ATOM_FLAG property of the atom \a atom is set.
         * \param atom The atom for which to query the property value.
         * \return \c true if the heteroatom flag is set, and \c false otherwise.
         */
        CDPL_BIOMOL_API bool hasHeteroAtomFlag(const Chem::Atom& atom);


        /**
         * \brief Returns the value of the Biomol::AtomProperty::CHAIN_ID property of the atom \a atom.
         * \param atom The atom for which to return the property value.
         * \return A \c const reference to the chain ID.
         */
        CDPL_BIOMOL_API const std::string& getChainID(const Chem::Atom& atom);

        /**
         * \brief Sets the value of the Biomol::AtomProperty::CHAIN_ID property of the atom \a atom to \a id.
         * \param atom The atom for which to set the property value.
         * \param id The new chain ID.
         */
        CDPL_BIOMOL_API void setChainID(Chem::Atom& atom, const std::string& id);

        /**
         * \brief Clears the value of the Biomol::AtomProperty::CHAIN_ID property of the atom \a atom.
         * \param atom The atom for which to clear the property value.
         */
        CDPL_BIOMOL_API void clearChainID(Chem::Atom& atom);

        /**
         * \brief Tells whether the Biomol::AtomProperty::CHAIN_ID property of the atom \a atom is set.
         * \param atom The atom for which to query the property value.
         * \return \c true if the chain ID is set, and \c false otherwise.
         */
        CDPL_BIOMOL_API bool hasChainID(const Chem::Atom& atom);


        /**
         * \brief Returns the value of the Biomol::AtomProperty::ALT_LOCATION_ID property of the atom \a atom.
         * \param atom The atom for which to return the property value.
         * \return The alternate location identifier.
         */
        CDPL_BIOMOL_API char getAltLocationID(const Chem::Atom& atom);

        /**
         * \brief Sets the value of the Biomol::AtomProperty::ALT_LOCATION_ID property of the atom \a atom to \a id.
         * \param atom The atom for which to set the property value.
         * \param id The new alternate location identifier.
         */
        CDPL_BIOMOL_API void setAltLocationID(Chem::Atom& atom, char id);

        /**
         * \brief Clears the value of the Biomol::AtomProperty::ALT_LOCATION_ID property of the atom \a atom.
         * \param atom The atom for which to clear the property value.
         */
        CDPL_BIOMOL_API void clearAltLocationID(Chem::Atom& atom);

        /**
         * \brief Tells whether the Biomol::AtomProperty::ALT_LOCATION_ID property of the atom \a atom is set.
         * \param atom The atom for which to query the property value.
         * \return \c true if the alternate location identifier is set, and \c false otherwise.
         */
        CDPL_BIOMOL_API bool hasAltLocationID(const Chem::Atom& atom);

        /**
         * \brief Returns the value of the Biomol::AtomProperty::ENTITY_ID property of the atom \a atom.
         * \param atom The atom for which to return the property value.
         * \return A \c const reference to the entity ID.
         * \since 1.2
         */
        CDPL_BIOMOL_API const std::string& getEntityID(const Chem::Atom& atom);

        /**
         * \brief Sets the value of the Biomol::AtomProperty::ENTITY_ID property of the atom \a atom to \a id.
         * \param atom The atom for which to set the property value.
         * \param id The new entity ID.
         */
        CDPL_BIOMOL_API void setEntityID(Chem::Atom& atom, const std::string& id);

        /**
         * \brief Clears the value of the Biomol::AtomProperty::ENTITY_ID property of the atom \a atom.
         * \param atom The atom for which to clear the property value.
         */
        CDPL_BIOMOL_API void clearEntityID(Chem::Atom& atom);

        /**
         * \brief Tells whether the Biomol::AtomProperty::ENTITY_ID property of the atom \a atom is set.
         * \param atom The atom for which to query the property value.
         * \return \c true if the entity ID is set, and \c false otherwise.
         */
        CDPL_BIOMOL_API bool hasEntityID(const Chem::Atom& atom);


        /**
         * \brief Returns the value of the Biomol::AtomProperty::MODEL_NUMBER property of the atom \a atom.
         * \param atom The atom for which to return the property value.
         * \return The model number.
         */
        CDPL_BIOMOL_API std::size_t getModelNumber(const Chem::Atom& atom);

        /**
         * \brief Sets the value of the Biomol::AtomProperty::MODEL_NUMBER property of the atom \a atom to \a model_no.
         * \param atom The atom for which to set the property value.
         * \param model_no The new model number.
         */
        CDPL_BIOMOL_API void setModelNumber(Chem::Atom& atom, std::size_t model_no);

        /**
         * \brief Clears the value of the Biomol::AtomProperty::MODEL_NUMBER property of the atom \a atom.
         * \param atom The atom for which to clear the property value.
         */
        CDPL_BIOMOL_API void clearModelNumber(Chem::Atom& atom);

        /**
         * \brief Tells whether the Biomol::AtomProperty::MODEL_NUMBER property of the atom \a atom is set.
         * \param atom The atom for which to query the property value.
         * \return \c true if the model number is set, and \c false otherwise.
         */
        CDPL_BIOMOL_API bool hasModelNumber(const Chem::Atom& atom);


        /**
         * \brief Returns the value of the Biomol::AtomProperty::SERIAL_NUMBER property of the atom \a atom.
         * \param atom The atom for which to return the property value.
         * \return The atom serial number.
         */
        CDPL_BIOMOL_API long getSerialNumber(const Chem::Atom& atom);

        /**
         * \brief Sets the value of the Biomol::AtomProperty::SERIAL_NUMBER property of the atom \a atom to \a serial_no.
         * \param atom The atom for which to set the property value.
         * \param serial_no The new atom serial number.
         */
        CDPL_BIOMOL_API void setSerialNumber(Chem::Atom& atom, long serial_no);

        /**
         * \brief Clears the value of the Biomol::AtomProperty::SERIAL_NUMBER property of the atom \a atom.
         * \param atom The atom for which to clear the property value.
         */
        CDPL_BIOMOL_API void clearSerialNumber(Chem::Atom& atom);

        /**
         * \brief Tells whether the Biomol::AtomProperty::SERIAL_NUMBER property of the atom \a atom is set.
         * \param atom The atom for which to query the property value.
         * \return \c true if the atom serial number is set, and \c false otherwise.
         */
        CDPL_BIOMOL_API bool hasSerialNumber(const Chem::Atom& atom);


        /**
         * \brief Returns the value of the Biomol::AtomProperty::OCCUPANCY property of the atom \a atom.
         * \param atom The atom for which to return the property value.
         * \return The occupancy value.
         */
        CDPL_BIOMOL_API double getOccupancy(const Chem::Atom& atom);

        /**
         * \brief Sets the value of the Biomol::AtomProperty::OCCUPANCY property of the atom \a atom to \a occupancy.
         * \param atom The atom for which to set the property value.
         * \param occupancy The new occupancy value.
         */
        CDPL_BIOMOL_API void setOccupancy(Chem::Atom& atom, double occupancy);

        /**
         * \brief Clears the value of the Biomol::AtomProperty::OCCUPANCY property of the atom \a atom.
         * \param atom The atom for which to clear the property value.
         */
        CDPL_BIOMOL_API void clearOccupancy(Chem::Atom& atom);

        /**
         * \brief Tells whether the Biomol::AtomProperty::OCCUPANCY property of the atom \a atom is set.
         * \param atom The atom for which to query the property value.
         * \return \c true if the occupancy is set, and \c false otherwise.
         */
        CDPL_BIOMOL_API bool hasOccupancy(const Chem::Atom& atom);


        /**
         * \brief Returns the value of the Biomol::AtomProperty::B_FACTOR property of the atom \a atom.
         * \param atom The atom for which to return the property value.
         * \return The temperature (B) factor.
         */
        CDPL_BIOMOL_API double getBFactor(const Chem::Atom& atom);

        /**
         * \brief Sets the value of the Biomol::AtomProperty::B_FACTOR property of the atom \a atom to \a factor.
         * \param atom The atom for which to set the property value.
         * \param factor The new temperature (B) factor.
         */
        CDPL_BIOMOL_API void setBFactor(Chem::Atom& atom, double factor);

        /**
         * \brief Clears the value of the Biomol::AtomProperty::B_FACTOR property of the atom \a atom.
         * \param atom The atom for which to clear the property value.
         */
        CDPL_BIOMOL_API void clearBFactor(Chem::Atom& atom);

        /**
         * \brief Tells whether the Biomol::AtomProperty::B_FACTOR property of the atom \a atom is set.
         * \param atom The atom for which to query the property value.
         * \return \c true if the temperature factor is set, and \c false otherwise.
         */
        CDPL_BIOMOL_API bool hasBFactor(const Chem::Atom& atom);


        /**
         * \brief Tells whether the atom \a atom is a backbone atom of an amino acid or nucleotide residue.
         * \param atom The atom to test.
         * \return \c true if the atom is a backbone atom, and \c false otherwise.
         */
        CDPL_BIOMOL_API bool isPDBBackboneAtom(const Chem::Atom& atom);

        /**
         * \brief Tells whether the residue attributes of the atom \a atom match the given filter values.
         *
         * Each filter argument is ignored when set to its sentinel value (\c nullptr / \e 0 / Biomol::IGNORE_SEQUENCE_NO /
         * Biomol::IGNORE_SERIAL_NO). All supplied filters must match for the function to return \c true.
         *
         * \param atom The atom to test.
         * \param res_code The \e PDB three-letter residue code to match (or \c nullptr to ignore).
         * \param chain_id The \e PDB chain ID to match (or \c nullptr to ignore).
         * \param res_seq_no The \e PDB residue sequence number to match (or Biomol::IGNORE_SEQUENCE_NO to ignore).
         * \param ins_code The \e PDB insertion code to match (or \e 0 to ignore).
         * \param model_no The \e PDB model number to match (or \e 0 to ignore).
         * \param atom_name The \e PDB atom name to match (or \c nullptr to ignore).
         * \param serial_no The \e PDB atom serial number to match (or Biomol::IGNORE_SERIAL_NO to ignore).
         * \return \c true if all supplied filters match, and \c false otherwise.
         */
        CDPL_BIOMOL_API bool matchesResidueInfo(const Chem::Atom& atom, const char* res_code = 0, const char* chain_id = 0, long res_seq_no = IGNORE_SEQUENCE_NO,
                                                char ins_code = 0, std::size_t model_no = 0, const char* atom_name = 0, long serial_no = IGNORE_SERIAL_NO);

        /**
         * \brief Tells whether the atoms \a atom1 and \a atom2 belong to the same residue, comparing the atom properties selected by \a flags.
         * \param atom1 The first atom.
         * \param atom2 The second atom.
         * \param flags The bitwise-OR combination of Biomol::AtomPropertyFlag values selecting the residue identifying properties to compare.
         * \return \c true if both atoms agree on all selected properties, and \c false otherwise.
         */
        CDPL_BIOMOL_API bool areInSameResidue(const Chem::Atom& atom1, const Chem::Atom& atom2, unsigned int flags = AtomPropertyFlag::DEFAULT);

        /**
         * \brief Extracts the substructure of the residue the atom \a atom belongs to into \a res_substruct.
         * \param atom The query atom whose residue substructure is to be extracted.
         * \param molgraph The molecular graph providing the structural context.
         * \param res_substruct The output fragment receiving the extracted residue substructure.
         * \param cnctd_only If \c true, only atoms in the connected component of the atom \a atom within the residue are extracted.
         * \param flags The bitwise-OR combination of Biomol::AtomPropertyFlag values selecting the residue identifying properties.
         * \param append If \c true, the extracted atoms and bonds are appended to \a res_substruct. If \c false, \a res_substruct is cleared first.
         */
        CDPL_BIOMOL_API void extractResidueSubstructure(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, Chem::Fragment& res_substruct,
                                                        bool cnctd_only = false, unsigned int flags = AtomPropertyFlag::DEFAULT, bool append = false);
    } // namespace Biomol
} // namespace CDPL

#endif // CDPL_BIOMOL_ATOMFUNCTIONS_HPP
