/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * StaticInit.hpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2020 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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


#ifndef CDPL_CHEM_STATICINIT_HPP
#define CDPL_CHEM_STATICINIT_HPP

#ifdef CDPL_CHEM_STATIC_LINK


namespace CDPL
{

	namespace Chem
	{

		void initAtomProperties();
		void initBondProperties();
		void initMolecularGraphProperties();
		void initReactionProperties();
		void initEntity3DProperties();
		void initAtomPropertyDefaults();
		void initBondPropertyDefaults();
		void initMolecularGraphPropertyDefaults();
		void initReactionPropertyDefaults();
		void initControlParameters();
		void initControlParameterDefaults();
		void initDataFormats();
	}
}

namespace
{

	struct CDPLChemInit
	{

		CDPLChemInit() {
			CDPL::Chem::initAtomProperties();
			CDPL::Chem::initBondProperties();
			CDPL::Chem::initMolecularGraphProperties();
			CDPL::Chem::initReactionProperties();
			CDPL::Chem::initEntity3DProperties();
			CDPL::Chem::initAtomPropertyDefaults();
			CDPL::Chem::initBondPropertyDefaults();
			CDPL::Chem::initMolecularGraphPropertyDefaults();
			CDPL::Chem::initReactionPropertyDefaults();
			CDPL::Chem::initControlParameters();
			CDPL::Chem::initControlParameterDefaults();
			CDPL::Chem::initDataFormats();
		}

	} cdplChemInit;
}

#endif // CDPL_CHEM_STATIC_LINK

#endif // CDPL_CHEM_STATICINIT_HPP
