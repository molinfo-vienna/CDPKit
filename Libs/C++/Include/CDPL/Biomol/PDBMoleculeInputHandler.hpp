/* 
 * PDBMoleculeInputHandler.hpp 
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
 * \brief Declaration of type CDPL::Biomol::PDBMoleculeInputHandler.
 */

#ifndef CDPL_BIOMOL_PDBMOLECULEINPUTHANDLER_HPP
#define CDPL_BIOMOL_PDBMOLECULEINPUTHANDLER_HPP

#include "CDPL/Biomol/DataFormat.hpp"
#include "CDPL/Biomol/PDBMoleculeReader.hpp"
#include "CDPL/Util/DefaultDataInputHandler.hpp"


namespace CDPL
{

    namespace Biomol
    {

        /**
         * \brief A handler for the input of molecule data in the <em>Brookhaven Protein Data Bank (PDB)</em>
         *        [\ref PDB] format.
         */
        typedef Util::DefaultDataInputHandler<PDBMoleculeReader, DataFormat::PDB> PDBMoleculeInputHandler;
    } // namespace Biomol
} // namespace CDPL

#endif // CDPL_BIOMOL_PDBMOLECULEINPUTHANDLER_HPP
