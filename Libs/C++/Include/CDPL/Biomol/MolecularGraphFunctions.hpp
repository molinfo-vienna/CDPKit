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
#include "CDPL/Biomol/ProcessingFlags.hpp"
#include "CDPL/Chem/Atom3DCoordinatesFunction.hpp"
#include "CDPL/Biomol/AtomPropertyFlag.hpp"


namespace CDPL 
{

    namespace Chem
    {
    
        class MolecularGraph;
        class Fragment;
    }

    namespace Biomol 
    {

        CDPL_BIOMOL_API const std::string& getResidueCode(const Chem::MolecularGraph& molgraph);

        CDPL_BIOMOL_API void setResidueCode(Chem::MolecularGraph& molgraph, const std::string& code);

        CDPL_BIOMOL_API void clearResidueCode(Chem::MolecularGraph& molgraph);

        CDPL_BIOMOL_API bool hasResidueCode(const Chem::MolecularGraph& molgraph);


        CDPL_BIOMOL_API long getResidueSequenceNumber(const Chem::MolecularGraph& molgraph);

        CDPL_BIOMOL_API void setResidueSequenceNumber(Chem::MolecularGraph& molgraph, long seq_no);

        CDPL_BIOMOL_API void clearResidueSequenceNumber(Chem::MolecularGraph& molgraph);

        CDPL_BIOMOL_API bool hasResidueSequenceNumber(const Chem::MolecularGraph& molgraph);


        CDPL_BIOMOL_API char getResidueInsertionCode(const Chem::MolecularGraph& molgraph);

        CDPL_BIOMOL_API void setResidueInsertionCode(Chem::MolecularGraph& molgraph, char code);

        CDPL_BIOMOL_API void clearResidueInsertionCode(Chem::MolecularGraph& molgraph);

        CDPL_BIOMOL_API bool hasResidueInsertionCode(const Chem::MolecularGraph& molgraph);


        CDPL_BIOMOL_API const std::string& getChainID(const Chem::MolecularGraph& molgraph);

        CDPL_BIOMOL_API void setChainID(Chem::MolecularGraph& molgraph, const std::string& id);

        CDPL_BIOMOL_API void clearChainID(Chem::MolecularGraph& molgraph);

        CDPL_BIOMOL_API bool hasChainID(const Chem::MolecularGraph& molgraph);


        CDPL_BIOMOL_API std::size_t getModelNumber(const Chem::MolecularGraph& molgraph);

        CDPL_BIOMOL_API void setModelNumber(Chem::MolecularGraph& molgraph, std::size_t model_no);

        CDPL_BIOMOL_API void clearModelNumber(Chem::MolecularGraph& molgraph);

        CDPL_BIOMOL_API bool hasModelNumber(const Chem::MolecularGraph& molgraph);
    

        CDPL_BIOMOL_API const PDBData::SharedPointer& getPDBData(const Chem::MolecularGraph& molgraph);

        CDPL_BIOMOL_API void setPDBData(Chem::MolecularGraph& molgraph, const PDBData::SharedPointer& data);

        CDPL_BIOMOL_API void clearPDBData(Chem::MolecularGraph& molgraph);
    
        CDPL_BIOMOL_API bool hasPDBData(const Chem::MolecularGraph& molgraph);


        CDPL_BIOMOL_API void convertMOL2ToPDBResidueInfo(Chem::MolecularGraph& molgraph, bool overwrite);

        CDPL_BIOMOL_API void extractResidueSubstructures(const Chem::MolecularGraph& molgraph, const Chem::MolecularGraph& parent_molgraph, Chem::Fragment& res_substructs, 
                                                         bool cnctd_only = false, unsigned int flags = AtomPropertyFlag::DEFAULT, bool append = false);
        
        CDPL_BIOMOL_API void extractProximalAtoms(const Chem::MolecularGraph& core, const Chem::MolecularGraph& macromol, Chem::Fragment& env_atoms, 
                                                  double max_dist, bool inc_core_atoms = false, bool append = false);

        CDPL_BIOMOL_API void extractProximalAtoms(const Chem::MolecularGraph& core, const Chem::MolecularGraph& macromol, Chem::Fragment& env_atoms, 
                                                  const Chem::Atom3DCoordinatesFunction& coords_func, double max_dist, bool inc_core_atoms = false, bool append = false);

        CDPL_BIOMOL_API void extractEnvironmentResidues(const Chem::MolecularGraph& core, const Chem::MolecularGraph& macromol, Chem::Fragment& env_residues, 
                                                        double max_dist, bool append = false);

        CDPL_BIOMOL_API void extractEnvironmentResidues(const Chem::MolecularGraph& core, const Chem::MolecularGraph& macromol, Chem::Fragment& env_residues, 
                                                        const Chem::Atom3DCoordinatesFunction& coords_func, double max_dist, bool append = false);

        CDPL_BIOMOL_API void setHydrogenResidueSequenceInfo(Chem::MolecularGraph& molgraph, bool overwrite, unsigned int flags = AtomPropertyFlag::DEFAULT);

        CDPL_BIOMOL_API bool matchesResidueInfo(const Chem::MolecularGraph& molgraph, const char* res_code = 0, const char* chain_id = 0, long res_seq_no = IGNORE_SEQUENCE_NO,
                                                char ins_code = 0, std::size_t model_no = 0);
    }
}

#endif // CDPL_BIOMOL_MOLECULARGRAPHFUNCTIONS_HPP
 
