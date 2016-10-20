/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * Biomol.hpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
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
 * \brief A convenience header including everything that is defined in namespace CDPL::Biomol.
 */

#ifndef CDPL_BIOMOL_HPP
#define CDPL_BIOMOL_HPP

#include "CDPL/Biomol/PDBData.hpp"

#include "CDPL/Biomol/AtomProperty.hpp"
#include "CDPL/Biomol/MolecularGraphProperty.hpp"
#include "CDPL/Biomol/AtomPropertyFlag.hpp"
#include "CDPL/Biomol/ResidueType.hpp"
#include "CDPL/Biomol/DataFormat.hpp"
#include "CDPL/Biomol/ControlParameter.hpp"
#include "CDPL/Biomol/ControlParameterDefault.hpp"
#include "CDPL/Biomol/ControlParameterFunctions.hpp"

#include "CDPL/Biomol/PDBMoleculeInputHandler.hpp"
#include "CDPL/Biomol/PDBMolecularGraphOutputHandler.hpp"

#include "CDPL/Biomol/PDBMoleculeReader.hpp"
#include "CDPL/Biomol/PDBMolecularGraphWriter.hpp"

#include "CDPL/Biomol/ResidueDictionary.hpp"

#include "CDPL/Biomol/AtomFunctions.hpp"
#include "CDPL/Biomol/MolecularGraphFunctions.hpp"

#endif // CDPL_BIOMOL_HPP
