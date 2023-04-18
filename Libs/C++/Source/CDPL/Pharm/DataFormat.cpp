/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * DataFormat.cpp 
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


#include "StaticInit.hpp"

#include "CDPL/Config.hpp"
#include "CDPL/Base/DataIOManager.hpp"
#include "CDPL/Base/DataFormat.hpp"
#include "CDPL/Pharm/DataFormat.hpp"
#include "CDPL/Pharm/CDFPharmacophoreInputHandler.hpp"
#include "CDPL/Pharm/CDFFeatureContainerOutputHandler.hpp"
#include "CDPL/Pharm/PMLPharmacophoreInputHandler.hpp"
#include "CDPL/Pharm/PMLFeatureContainerOutputHandler.hpp"

#if defined(HAVE_BOOST_FILESYSTEM) && defined(HAVE_BOOST_IOSTREAMS)
#ifdef HAVE_SQLITE3

#include "CDPL/Pharm/PSDPharmacophoreInputHandler.hpp"
#include "CDPL/Pharm/PSDMoleculeInputHandler.hpp"
#include "CDPL/Pharm/PSDMolecularGraphOutputHandler.hpp"

#endif // HAVE_SQLITE3

#include "CDPL/Pharm/CDFGZPharmacophoreInputHandler.hpp"
#include "CDPL/Pharm/CDFGZFeatureContainerOutputHandler.hpp"
#include "CDPL/Pharm/CDFBZ2PharmacophoreInputHandler.hpp"
#include "CDPL/Pharm/CDFBZ2FeatureContainerOutputHandler.hpp"

#endif // defined(HAVE_BOOST_FILESYSTEM) && defined(HAVE_BOOST_IOSTREAMS)


namespace
{

	const char* cdfFileExtensions[]    = { "cdf" };
	const char* cdfGzFileExtensions[]  = { "cdf.gz" };
	const char* cdfBz2FileExtensions[] = { "cdf.bz2" };
	const char* pmlFileExtensions[]    = { "pml" };
	const char* psdFileExtensions[]    = { "psd" };
}


using namespace CDPL;


const Base::DataFormat Pharm::DataFormat::CDF("CDF", "Native CDPL-Format", "", 
											  cdfFileExtensions, cdfFileExtensions + 1, true);
const Base::DataFormat Pharm::DataFormat::CDF_GZ("CDF_GZ", "GZip-Compressed Native CDPL-Format", "", 
											  cdfGzFileExtensions, cdfGzFileExtensions + 1, true);
const Base::DataFormat Pharm::DataFormat::CDF_BZ2("CDF_BZ2", "BZip2-Compressed Native CDPL-Format", "", 
											  cdfBz2FileExtensions, cdfBz2FileExtensions + 1, true);
const Base::DataFormat Pharm::DataFormat::PML("PML", "LigandScout Pharmaceutical Markup Language", "", 
											  pmlFileExtensions, pmlFileExtensions + 1, true);
const Base::DataFormat Pharm::DataFormat::PSD("PSD", "Pharmacophore Screening Database", "", 
											  psdFileExtensions, psdFileExtensions + 1, true);

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
			using namespace Chem;

			DataIOManager<Pharmacophore>::registerInputHandler(DataIOManager<Pharmacophore>::InputHandlerPointer(new CDFPharmacophoreInputHandler()));
			DataIOManager<Pharmacophore>::registerInputHandler(DataIOManager<Pharmacophore>::InputHandlerPointer(new PMLPharmacophoreInputHandler()));
		
			DataIOManager<FeatureContainer>::registerOutputHandler(DataIOManager<FeatureContainer>::OutputHandlerPointer(new CDFFeatureContainerOutputHandler()));
			DataIOManager<FeatureContainer>::registerOutputHandler(DataIOManager<FeatureContainer>::OutputHandlerPointer(new PMLFeatureContainerOutputHandler()));
		
#if defined(HAVE_BOOST_FILESYSTEM) && defined(HAVE_BOOST_IOSTREAMS)
#ifdef HAVE_SQLITE3

			DataIOManager<Pharmacophore>::registerInputHandler(DataIOManager<Pharmacophore>::InputHandlerPointer(new PSDPharmacophoreInputHandler()));
			DataIOManager<Molecule>::registerInputHandler(DataIOManager<Molecule>::InputHandlerPointer(new PSDMoleculeInputHandler()));
			DataIOManager<MolecularGraph>::registerOutputHandler(DataIOManager<MolecularGraph>::OutputHandlerPointer(new PSDMolecularGraphOutputHandler()));

#endif // HAVE_SQLITE3

			DataIOManager<Pharmacophore>::registerInputHandler(DataIOManager<Pharmacophore>::InputHandlerPointer(new CDFGZPharmacophoreInputHandler()));
			DataIOManager<Pharmacophore>::registerInputHandler(DataIOManager<Pharmacophore>::InputHandlerPointer(new CDFBZ2PharmacophoreInputHandler()));
	
			DataIOManager<FeatureContainer>::registerOutputHandler(DataIOManager<FeatureContainer>::OutputHandlerPointer(new CDFGZFeatureContainerOutputHandler()));
			DataIOManager<FeatureContainer>::registerOutputHandler(DataIOManager<FeatureContainer>::OutputHandlerPointer(new CDFBZ2FeatureContainerOutputHandler()));
	
#endif // defined(HAVE_BOOST_FILESYSTEM) && defined(HAVE_BOOST_IOSTREAMS)
		}

	} init;
}
