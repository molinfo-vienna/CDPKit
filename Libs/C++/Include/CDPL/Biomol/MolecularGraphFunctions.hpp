/* 
 * MolecularGraphFunctions.hpp 
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
 * \brief Declaration of functions that operate on Chem::MolecularGraph instances.
 */

#ifndef CDPL_BIOMOL_MOLECULARGRAPHFUNCTIONS_HPP
#define CDPL_BIOMOL_MOLECULARGRAPHFUNCTIONS_HPP

#include <string>
#include <cstddef>

#include "CDPL/Biomol/APIPrefix.hpp"
#include "CDPL/Biomol/PDBData.hpp"
#include "CDPL/Biomol/MMCIFData.hpp"
#include "CDPL/Biomol/ProcessingFlags.hpp"
#include "CDPL/Chem/Atom3DCoordinatesFunction.hpp"
#include "CDPL/Biomol/AtomPropertyFlag.hpp"


namespace CDPL
{

    namespace Chem
    {

        class MolecularGraph;
        class Fragment;
    } // namespace Chem

    namespace Biomol
    {

        /**
         * \brief Returns the value of the Biomol::MolecularGraphProperty::RESIDUE_CODE property of \a molgraph.
         * \param molgraph The molecular graph.
         * \return A \c const reference to the residue three-letter code.
         */
        CDPL_BIOMOL_API const std::string& getResidueCode(const Chem::MolecularGraph& molgraph);

        /**
         * \brief Sets the value of the Biomol::MolecularGraphProperty::RESIDUE_CODE property of \a molgraph to \a code.
         * \param molgraph The molecular graph.
         * \param code The new residue three-letter code.
         */
        CDPL_BIOMOL_API void setResidueCode(Chem::MolecularGraph& molgraph, const std::string& code);

        /**
         * \brief Removes the Biomol::MolecularGraphProperty::RESIDUE_CODE property from \a molgraph.
         * \param molgraph The molecular graph.
         */
        CDPL_BIOMOL_API void clearResidueCode(Chem::MolecularGraph& molgraph);

        /**
         * \brief Tells whether \a molgraph carries an explicit Biomol::MolecularGraphProperty::RESIDUE_CODE property.
         * \param molgraph The molecular graph.
         * \return \c true if the residue code is set, and \c false otherwise.
         */
        CDPL_BIOMOL_API bool hasResidueCode(const Chem::MolecularGraph& molgraph);


        /**
         * \brief Returns the value of the Biomol::MolecularGraphProperty::RESIDUE_SEQUENCE_NUMBER property of \a molgraph.
         * \param molgraph The molecular graph.
         * \return The residue sequence number.
         */
        CDPL_BIOMOL_API long getResidueSequenceNumber(const Chem::MolecularGraph& molgraph);

        /**
         * \brief Sets the value of the Biomol::MolecularGraphProperty::RESIDUE_SEQUENCE_NUMBER property of \a molgraph to \a seq_no.
         * \param molgraph The molecular graph.
         * \param seq_no The new residue sequence number.
         */
        CDPL_BIOMOL_API void setResidueSequenceNumber(Chem::MolecularGraph& molgraph, long seq_no);

        /**
         * \brief Removes the Biomol::MolecularGraphProperty::RESIDUE_SEQUENCE_NUMBER property from \a molgraph.
         * \param molgraph The molecular graph.
         */
        CDPL_BIOMOL_API void clearResidueSequenceNumber(Chem::MolecularGraph& molgraph);

        /**
         * \brief Tells whether \a molgraph carries an explicit Biomol::MolecularGraphProperty::RESIDUE_SEQUENCE_NUMBER property.
         * \param molgraph The molecular graph.
         * \return \c true if the residue sequence number is set, and \c false otherwise.
         */
        CDPL_BIOMOL_API bool hasResidueSequenceNumber(const Chem::MolecularGraph& molgraph);


        /**
         * \brief Returns the value of the Biomol::MolecularGraphProperty::RESIDUE_INSERTION_CODE property of \a molgraph.
         * \param molgraph The molecular graph.
         * \return The residue insertion code.
         */
        CDPL_BIOMOL_API char getResidueInsertionCode(const Chem::MolecularGraph& molgraph);

        /**
         * \brief Sets the value of the Biomol::MolecularGraphProperty::RESIDUE_INSERTION_CODE property of \a molgraph to \a code.
         * \param molgraph The molecular graph.
         * \param code The new residue insertion code.
         */
        CDPL_BIOMOL_API void setResidueInsertionCode(Chem::MolecularGraph& molgraph, char code);

        /**
         * \brief Removes the Biomol::MolecularGraphProperty::RESIDUE_INSERTION_CODE property from \a molgraph.
         * \param molgraph The molecular graph.
         */
        CDPL_BIOMOL_API void clearResidueInsertionCode(Chem::MolecularGraph& molgraph);

        /**
         * \brief Tells whether \a molgraph carries an explicit Biomol::MolecularGraphProperty::RESIDUE_INSERTION_CODE property.
         * \param molgraph The molecular graph.
         * \return \c true if the residue insertion code is set, and \c false otherwise.
         */
        CDPL_BIOMOL_API bool hasResidueInsertionCode(const Chem::MolecularGraph& molgraph);


        /**
         * \brief Returns the value of the Biomol::MolecularGraphProperty::CHAIN_ID property of \a molgraph.
         * \param molgraph The molecular graph.
         * \return A \c const reference to the chain ID.
         */
        CDPL_BIOMOL_API const std::string& getChainID(const Chem::MolecularGraph& molgraph);

        /**
         * \brief Sets the value of the Biomol::MolecularGraphProperty::CHAIN_ID property of \a molgraph to \a id.
         * \param molgraph The molecular graph.
         * \param id The new chain ID.
         */
        CDPL_BIOMOL_API void setChainID(Chem::MolecularGraph& molgraph, const std::string& id);

        /**
         * \brief Removes the Biomol::MolecularGraphProperty::CHAIN_ID property from \a molgraph.
         * \param molgraph The molecular graph.
         */
        CDPL_BIOMOL_API void clearChainID(Chem::MolecularGraph& molgraph);

        /**
         * \brief Tells whether \a molgraph carries an explicit Biomol::MolecularGraphProperty::CHAIN_ID property.
         * \param molgraph The molecular graph.
         * \return \c true if the chain ID is set, and \c false otherwise.
         */
        CDPL_BIOMOL_API bool hasChainID(const Chem::MolecularGraph& molgraph);


        /**
         * \brief Returns the value of the Biomol::MolecularGraphProperty::MODEL_NUMBER property of \a molgraph.
         * \param molgraph The molecular graph.
         * \return The model number.
         */
        CDPL_BIOMOL_API std::size_t getModelNumber(const Chem::MolecularGraph& molgraph);

        /**
         * \brief Sets the value of the Biomol::MolecularGraphProperty::MODEL_NUMBER property of \a molgraph to \a model_no.
         * \param molgraph The molecular graph.
         * \param model_no The new model number.
         */
        CDPL_BIOMOL_API void setModelNumber(Chem::MolecularGraph& molgraph, std::size_t model_no);

        /**
         * \brief Removes the Biomol::MolecularGraphProperty::MODEL_NUMBER property from \a molgraph.
         * \param molgraph The molecular graph.
         */
        CDPL_BIOMOL_API void clearModelNumber(Chem::MolecularGraph& molgraph);

        /**
         * \brief Tells whether \a molgraph carries an explicit Biomol::MolecularGraphProperty::MODEL_NUMBER property.
         * \param molgraph The molecular graph.
         * \return \c true if the model number is set, and \c false otherwise.
         */
        CDPL_BIOMOL_API bool hasModelNumber(const Chem::MolecularGraph& molgraph);


        /**
         * \brief Returns the value of the Biomol::MolecularGraphProperty::PDB_DATA property of \a molgraph.
         * \param molgraph The molecular graph.
         * \return A \c const reference to the PDB data record shared pointer.
         */
        CDPL_BIOMOL_API const PDBData::SharedPointer& getPDBData(const Chem::MolecularGraph& molgraph);

        /**
         * \brief Sets the value of the Biomol::MolecularGraphProperty::PDB_DATA property of \a molgraph to \a data.
         * \param molgraph The molecular graph.
         * \param data The new PDB data record.
         */
        CDPL_BIOMOL_API void setPDBData(Chem::MolecularGraph& molgraph, const PDBData::SharedPointer& data);

        /**
         * \brief Removes the Biomol::MolecularGraphProperty::PDB_DATA property from \a molgraph.
         * \param molgraph The molecular graph.
         */
        CDPL_BIOMOL_API void clearPDBData(Chem::MolecularGraph& molgraph);

        /**
         * \brief Tells whether \a molgraph carries an explicit Biomol::MolecularGraphProperty::PDB_DATA property.
         * \param molgraph The molecular graph.
         * \return \c true if the PDB data record is set, and \c false otherwise.
         */
        CDPL_BIOMOL_API bool hasPDBData(const Chem::MolecularGraph& molgraph);

        /**
         * \brief Returns the value of the Biomol::MolecularGraphProperty::MMCIF_DATA property of \a molgraph.
         * \param molgraph The molecular graph.
         * \return A \c const reference to the mmCIF data record shared pointer.
         * \since 1.2
         */
        CDPL_BIOMOL_API const MMCIFData::SharedPointer& getMMCIFData(const Chem::MolecularGraph& molgraph);

        /**
         * \brief Sets the value of the Biomol::MolecularGraphProperty::MMCIF_DATA property of \a molgraph to \a data.
         * \param molgraph The molecular graph.
         * \param data The new mmCIF data record.
         */
        CDPL_BIOMOL_API void setMMCIFData(Chem::MolecularGraph& molgraph, const MMCIFData::SharedPointer& data);

        /**
         * \brief Removes the Biomol::MolecularGraphProperty::MMCIF_DATA property from \a molgraph.
         * \param molgraph The molecular graph.
         */
        CDPL_BIOMOL_API void clearMMCIFData(Chem::MolecularGraph& molgraph);

        /**
         * \brief Tells whether \a molgraph carries an explicit Biomol::MolecularGraphProperty::MMCIF_DATA property.
         * \param molgraph The molecular graph.
         * \return \c true if the mmCIF data record is set, and \c false otherwise.
         */
        CDPL_BIOMOL_API bool hasMMCIFData(const Chem::MolecularGraph& molgraph);


        /**
         * \brief Extracts the substructures of all residues represented in \a molgraph from the parent macromolecular graph \a parent_molgraph.
         * \param molgraph The molecular graph providing the residue selection.
         * \param parent_molgraph The macromolecular graph from which to extract the residue substructures.
         * \param res_substructs The output fragment receiving the extracted residue substructures.
         * \param cnctd_only If \c true, only atoms in the connected component of each residue's representative atom are extracted.
         * \param flags The bitwise-OR combination of Biomol::AtomPropertyFlag values selecting the residue-identifying properties.
         * \param append If \c true, the extracted atoms and bonds are appended to \a res_substructs; if \c false, \a res_substructs is cleared first.
         */
        CDPL_BIOMOL_API void extractResidueSubstructures(const Chem::MolecularGraph& molgraph, const Chem::MolecularGraph& parent_molgraph, Chem::Fragment& res_substructs,
                                                         bool cnctd_only = false, unsigned int flags = AtomPropertyFlag::DEFAULT, bool append = false);

        /**
         * \brief Extracts the atoms of \a macromol that lie within \a max_dist of any atom of \a core.
         * \param core The core molecular graph defining the reference atom positions.
         * \param macromol The macromolecular graph providing the candidate atoms.
         * \param env_atoms The output fragment receiving the extracted environment atoms.
         * \param max_dist The maximum allowed distance between an environment atom and the nearest core atom.
         * \param inc_core_atoms If \c true, the atoms of \a core are also added to \a env_atoms.
         * \param append If \c true, the extracted atoms are appended to \a env_atoms; if \c false, \a env_atoms is cleared first.
         */
        CDPL_BIOMOL_API void extractProximalAtoms(const Chem::MolecularGraph& core, const Chem::MolecularGraph& macromol, Chem::Fragment& env_atoms,
                                                  double max_dist, bool inc_core_atoms = false, bool append = false);

        /**
         * \brief Extracts the atoms of \a macromol that lie within \a max_dist of any atom of \a core, using \a coords_func to obtain atom positions.
         * \param core The core molecular graph defining the reference atom positions.
         * \param macromol The macromolecular graph providing the candidate atoms.
         * \param env_atoms The output fragment receiving the extracted environment atoms.
         * \param coords_func The function used to retrieve the 3D coordinates of an atom.
         * \param max_dist The maximum allowed distance between an environment atom and the nearest core atom.
         * \param inc_core_atoms If \c true, the atoms of \a core are also added to \a env_atoms.
         * \param append If \c true, the extracted atoms are appended to \a env_atoms; if \c false, \a env_atoms is cleared first.
         */
        CDPL_BIOMOL_API void extractProximalAtoms(const Chem::MolecularGraph& core, const Chem::MolecularGraph& macromol, Chem::Fragment& env_atoms,
                                                  const Chem::Atom3DCoordinatesFunction& coords_func, double max_dist, bool inc_core_atoms = false, bool append = false);

        /**
         * \brief Extracts the residues of \a macromol that contain at least one atom within \a max_dist of any atom of \a core.
         * \param core The core molecular graph defining the reference atom positions.
         * \param macromol The macromolecular graph providing the candidate residues.
         * \param env_residues The output fragment receiving the extracted environment residues.
         * \param max_dist The maximum allowed distance between any atom of the environment residue and the nearest core atom.
         * \param append If \c true, the extracted residue atoms and bonds are appended to \a env_residues; if \c false, \a env_residues is cleared first.
         */
        CDPL_BIOMOL_API void extractEnvironmentResidues(const Chem::MolecularGraph& core, const Chem::MolecularGraph& macromol, Chem::Fragment& env_residues,
                                                        double max_dist, bool append = false);

        /**
         * \brief Extracts the residues of \a macromol that contain at least one atom within \a max_dist of any atom of \a core, using \a coords_func to obtain atom positions.
         * \param core The core molecular graph defining the reference atom positions.
         * \param macromol The macromolecular graph providing the candidate residues.
         * \param env_residues The output fragment receiving the extracted environment residues.
         * \param coords_func The function used to retrieve the 3D coordinates of an atom.
         * \param max_dist The maximum allowed distance between any atom of the environment residue and the nearest core atom.
         * \param append If \c true, the extracted residue atoms and bonds are appended to \a env_residues; if \c false, \a env_residues is cleared first.
         */
        CDPL_BIOMOL_API void extractEnvironmentResidues(const Chem::MolecularGraph& core, const Chem::MolecularGraph& macromol, Chem::Fragment& env_residues,
                                                        const Chem::Atom3DCoordinatesFunction& coords_func, double max_dist, bool append = false);

        /**
         * \brief Copies residue-identifying properties from heavy atoms to their attached hydrogen atoms in \a molgraph.
         * \param molgraph The molecular graph whose hydrogen atoms shall receive residue-identifying properties.
         * \param overwrite If \c true, existing residue-identifying properties of hydrogen atoms are overwritten.
         * \param flags The bitwise-OR combination of Biomol::AtomPropertyFlag values selecting the residue-identifying properties to propagate.
         */
        CDPL_BIOMOL_API void setHydrogenResidueSequenceInfo(Chem::MolecularGraph& molgraph, bool overwrite, unsigned int flags = AtomPropertyFlag::DEFAULT);

        /**
         * \brief Tells whether the residue-identity attributes of \a molgraph match the given filter values.
         *
         * Each filter argument is ignored when set to its sentinel value (\c nullptr / \c 0 / IGNORE_SEQUENCE_NO).
         * All supplied filters must match for the function to return \c true.
         *
         * \param molgraph The molecular graph to test.
         * \param res_code The PDB three-letter residue code to match (or \c nullptr to ignore).
         * \param chain_id The PDB chain ID to match (or \c nullptr to ignore).
         * \param res_seq_no The PDB residue sequence number to match (or IGNORE_SEQUENCE_NO to ignore).
         * \param ins_code The PDB insertion code to match (or \c 0 to ignore).
         * \param model_no The PDB model number to match (or \c 0 to ignore).
         * \return \c true if all supplied filters match, and \c false otherwise.
         */
        CDPL_BIOMOL_API bool matchesResidueInfo(const Chem::MolecularGraph& molgraph, const char* res_code = 0, const char* chain_id = 0, long res_seq_no = IGNORE_SEQUENCE_NO,
                                                char ins_code = 0, std::size_t model_no = 0);
    } // namespace Biomol
} // namespace CDPL

#endif // CDPL_BIOMOL_MOLECULARGRAPHFUNCTIONS_HPP
