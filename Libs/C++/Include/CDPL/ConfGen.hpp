/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ConfGen.hpp 
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
 * \brief A convenience header including everything that is defined in namespace CDPL::ConfGen.
 */

#ifndef CDPL_CONFGEN_HPP
#define CDPL_CONFGEN_HPP

#include "CDPL/Config.hpp"

#include "CDPL/ConfGen/DGConstraintGenerator.hpp"
#include "CDPL/ConfGen/DGStructureGenerator.hpp"
#include "CDPL/ConfGen/ConformerData.hpp"
#include "CDPL/ConfGen/ConformerDataArray.hpp"
#include "CDPL/ConfGen/CanonicalFragment.hpp"
#include "CDPL/ConfGen/FragmentLibrary.hpp"
#include "CDPL/ConfGen/FragmentLibraryEntry.hpp"
#include "CDPL/ConfGen/TorsionRule.hpp"
#include "CDPL/ConfGen/TorsionCategory.hpp"
#include "CDPL/ConfGen/TorsionLibrary.hpp"
#include "CDPL/ConfGen/TorsionRuleMatch.hpp"
#include "CDPL/ConfGen/TorsionRuleMatcher.hpp"
#include "CDPL/ConfGen/RMSDConformerSelector.hpp"
#include "CDPL/ConfGen/TorsionDriver.hpp"
#include "CDPL/ConfGen/BondFunctions.hpp"
#include "CDPL/ConfGen/MoleculeFunctions.hpp"
#include "CDPL/ConfGen/MolecularGraphFunctions.hpp"
#include "CDPL/ConfGen/ControlParameterFunctions.hpp"
#include "CDPL/ConfGen/CallbackFunction.hpp"
#include "CDPL/ConfGen/LogMessageCallbackFunction.hpp"
#include "CDPL/ConfGen/FragmentType.hpp"
#include "CDPL/ConfGen/ForceFieldType.hpp"
#include "CDPL/ConfGen/ConformerSamplingMode.hpp"
#include "CDPL/ConfGen/StructureGenerationMode.hpp"
#include "CDPL/ConfGen/ReturnCode.hpp"
#include "CDPL/ConfGen/NitrogenEnumerationMode.hpp"
#include "CDPL/ConfGen/DataFormat.hpp"
#include "CDPL/ConfGen/ControlParameter.hpp"
#include "CDPL/ConfGen/ControlParameterDefault.hpp"
#include "CDPL/ConfGen/TorsionDriverSettings.hpp"
#include "CDPL/ConfGen/DGConstraintGeneratorSettings.hpp"
#include "CDPL/ConfGen/DGStructureGeneratorSettings.hpp"
#include "CDPL/ConfGen/StructureGeneratorSettings.hpp"
#include "CDPL/ConfGen/ConformerGeneratorSettings.hpp"
#include "CDPL/ConfGen/FragmentConformerGeneratorSettings.hpp"
#include "CDPL/ConfGen/FragmentAssemblerSettings.hpp"

#include "CDPL/ConfGen/CFLMoleculeInputHandler.hpp"
#include "CDPL/ConfGen/CFLMoleculeReader.hpp"

#if defined(HAVE_BOOST_TIMER) && defined(HAVE_BOOST_CHRONO)

#include "CDPL/ConfGen/StructureGenerator.hpp"
#include "CDPL/ConfGen/ConformerGenerator.hpp"
#include "CDPL/ConfGen/FragmentConformerGenerator.hpp"
#include "CDPL/ConfGen/FragmentLibraryGenerator.hpp"
#include "CDPL/ConfGen/FragmentAssembler.hpp"

#endif // defined(HAVE_BOOST_TIMER) && defined(HAVE_BOOST_CHRONO)
#endif // CDPL_CONFGEN_HPP
