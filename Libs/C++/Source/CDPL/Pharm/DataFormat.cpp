/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * DataFormat.cpp 
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


#include "StaticInit.hpp"

#include "CDPL/Base/DataIOManager.hpp"
#include "CDPL/Base/DataFormat.hpp"
#include "CDPL/Pharm/DataFormat.hpp"
#include "CDPL/Pharm/CDFPharmacophoreInputHandler.hpp"
#include "CDPL/Pharm/CDFPharmacophoreOutputHandler.hpp"
#include "CDPL/Pharm/PMLPharmacophoreInputHandler.hpp"
#include "CDPL/Pharm/PMLPharmacophoreOutputHandler.hpp"


namespace
{

	const char* cdfFileExtensions[]    = { "cdf" };
	const char* pmlFileExtensions[]    = { "pml" };
}


using namespace CDPL;


const Base::DataFormat Pharm::DataFormat::CDF("CDF", "Native CDPL-Format", "", 
											  cdfFileExtensions, cdfFileExtensions + 1, true);
const Base::DataFormat Pharm::DataFormat::PML("PML", "Native LigandScout PML-Format", "", 
											  pmlFileExtensions, pmlFileExtensions + 1, true);

namespace CDPL
{

	namespace Pharm
	{

		void initDataFormats() {}
	}
}


namespace
{

	struct Init 
	{

		Init() {
			using namespace Base;
			using namespace Pharm;

			static const CDFPharmacophoreInputHandler  cdfPharmInputHandler;
			static const PMLPharmacophoreInputHandler  pmlPharmInputHandler;

			static const CDFPharmacophoreOutputHandler cdfPharmOutputHandler;
			static const PMLPharmacophoreOutputHandler pmlPharmOutputHandler;

			DataIOManager<Pharmacophore>::registerInputHandler(cdfPharmInputHandler);
			DataIOManager<Pharmacophore>::registerInputHandler(pmlPharmInputHandler);

			DataIOManager<Pharmacophore>::registerOutputHandler(cdfPharmOutputHandler);
			DataIOManager<Pharmacophore>::registerOutputHandler(pmlPharmOutputHandler);
		}

	} init;
}
