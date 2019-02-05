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

#include "CDPL/Config.hpp"

#include "CDPL/Biomol/PDBData.hpp"

#include "CDPL/Biomol/AtomProperty.hpp"
#include "CDPL/Biomol/MolecularGraphProperty.hpp"
#include "CDPL/Biomol/AtomPropertyDefault.hpp"
#include "CDPL/Biomol/MolecularGraphPropertyDefault.hpp"
#include "CDPL/Biomol/AtomPropertyFlag.hpp"
#include "CDPL/Biomol/PDBFormatVersion.hpp"
#include "CDPL/Biomol/ResidueType.hpp"
#include "CDPL/Biomol/DataFormat.hpp"
#include "CDPL/Biomol/ControlParameter.hpp"
#include "CDPL/Biomol/ControlParameterDefault.hpp"
#include "CDPL/Biomol/ControlParameterFunctions.hpp"

#include "CDPL/Biomol/PDBMoleculeInputHandler.hpp"
#include "CDPL/Biomol/PDBMolecularGraphOutputHandler.hpp"
#include "CDPL/Biomol/MMTFMoleculeInputHandler.hpp"
#include "CDPL/Biomol/MMTFMolecularGraphOutputHandler.hpp"

#include "CDPL/Biomol/PDBMoleculeReader.hpp"
#include "CDPL/Biomol/PDBMolecularGraphWriter.hpp"
#include "CDPL/Biomol/MMTFMoleculeReader.hpp"
#include "CDPL/Biomol/MMTFMolecularGraphWriter.hpp"

#include "CDPL/Biomol/HierarchyViewNode.hpp"
#include "CDPL/Biomol/HierarchyViewModel.hpp"
#include "CDPL/Biomol/HierarchyViewChain.hpp"
#include "CDPL/Biomol/HierarchyViewFragment.hpp"
#include "CDPL/Biomol/HierarchyView.hpp"

#include "CDPL/Biomol/ResidueList.hpp"
#include "CDPL/Biomol/ResidueDictionary.hpp"

#include "CDPL/Biomol/AtomFunctions.hpp"
#include "CDPL/Biomol/MolecularGraphFunctions.hpp"
#include "CDPL/Biomol/UtilityFunctions.hpp"

#if defined(HAVE_BOOST_FILESYSTEM) && defined(HAVE_BOOST_IOSTREAMS)

#include "CDPL/Biomol/PDBGZMoleculeInputHandler.hpp"
#include "CDPL/Biomol/PDBGZMolecularGraphOutputHandler.hpp"
#include "CDPL/Biomol/MMTFGZMoleculeInputHandler.hpp"
#include "CDPL/Biomol/MMTFGZMolecularGraphOutputHandler.hpp"

#include "CDPL/Biomol/PDBBZ2MoleculeInputHandler.hpp"
#include "CDPL/Biomol/PDBBZ2MolecularGraphOutputHandler.hpp"
#include "CDPL/Biomol/MMTFBZ2MoleculeInputHandler.hpp"
#include "CDPL/Biomol/MMTFBZ2MolecularGraphOutputHandler.hpp"

#include "CDPL/Biomol/PDBGZMoleculeReader.hpp"
#include "CDPL/Biomol/PDBGZMolecularGraphWriter.hpp"
#include "CDPL/Biomol/MMTFGZMoleculeReader.hpp"
#include "CDPL/Biomol/MMTFGZMolecularGraphWriter.hpp"

#include "CDPL/Biomol/PDBBZ2MoleculeReader.hpp"
#include "CDPL/Biomol/PDBBZ2MolecularGraphWriter.hpp"
#include "CDPL/Biomol/MMTFBZ2MoleculeReader.hpp"
#include "CDPL/Biomol/MMTFBZ2MolecularGraphWriter.hpp"

#endif // defined(HAVE_BOOST_FILESYSTEM) && defined(HAVE_BOOST_IOSTREAMS)
#endif // CDPL_BIOMOL_HPP
