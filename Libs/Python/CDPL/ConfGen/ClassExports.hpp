/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ClassExports.hpp 
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


#ifndef CDPL_PYTHON_CONFGEN_CLASSEXPORTS_HPP
#define CDPL_PYTHON_CONFGEN_CLASSEXPORTS_HPP

#include "CDPL/Config.hpp"


namespace CDPLPythonConfGen
{

	void exportDGConstraintGenerator();
	void exportDGConstraintGeneratorSettings();
	void exportDGStructureGenerator();
	void exportDGStructureGeneratorSettings();
	void exportFragmentLibraryEntry();
	void exportFragmentLibrary();
	void exportConformerData();
	void exportTorsionRule();
	void exportTorsionCategory();
	void exportTorsionLibrary();
	void exportTorsionRuleMatch();
	void exportTorsionRuleMatcher();
	void exportTorsionDriverSettings();
	void exportTorsionDriver();
	void exportRMSDConformerSelector();

	void exportBoostFunctionWrappers();

#if defined(HAVE_BOOST_TIMER) && defined(HAVE_BOOST_CHRONO)

	void exportStructureGenerator();
	void exportStructureGeneratorSettings();
	void exportConformerGenerator();
	void exportConformerGeneratorSettings();
	void exportFragmentConformerGenerator();
	void exportFragmentConformerGeneratorSettings();
	void exportFragmentLibraryGenerator();
	void exportFragmentAssemblerSettings();
	void exportFragmentAssembler();

#endif // defined(HAVE_BOOST_TIMER) && defined(HAVE_BOOST_CHRONO)
}

#endif // CDPL_PYTHON_CONFGEN_CLASSEXPORTS_HPP
