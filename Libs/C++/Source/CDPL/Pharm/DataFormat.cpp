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

#include "CDPL/Config.hpp"
#include "CDPL/Base/DataIOManager.hpp"
#include "CDPL/Base/DataFormat.hpp"
#include "CDPL/Pharm/DataFormat.hpp"
#include "CDPL/Pharm/CDFPharmacophoreInputHandler.hpp"
#include "CDPL/Pharm/CDFFeatureContainerOutputHandler.hpp"
#include "CDPL/Pharm/PMLPharmacophoreInputHandler.hpp"
#include "CDPL/Pharm/PMLFeatureContainerOutputHandler.hpp"
#include "CDPL/Pharm/CDFInteractionScoreGridInputHandler.hpp"
#include "CDPL/Pharm/CDFInteractionScoreGridOutputHandler.hpp"
#include "CDPL/Pharm/CDFInteractionScoreGridSetInputHandler.hpp"
#include "CDPL/Pharm/CDFInteractionScoreGridSetOutputHandler.hpp"

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
#include "CDPL/Pharm/CDFGZInteractionScoreGridInputHandler.hpp"
#include "CDPL/Pharm/CDFGZInteractionScoreGridOutputHandler.hpp"
#include "CDPL/Pharm/CDFBZ2InteractionScoreGridInputHandler.hpp"
#include "CDPL/Pharm/CDFBZ2InteractionScoreGridOutputHandler.hpp"
#include "CDPL/Pharm/CDFGZInteractionScoreGridSetInputHandler.hpp"
#include "CDPL/Pharm/CDFGZInteractionScoreGridSetOutputHandler.hpp"
#include "CDPL/Pharm/CDFBZ2InteractionScoreGridSetInputHandler.hpp"
#include "CDPL/Pharm/CDFBZ2InteractionScoreGridSetOutputHandler.hpp"

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

			static const CDFPharmacophoreInputHandler           cdfPharmInputHandler;
			static const PMLPharmacophoreInputHandler           pmlPharmInputHandler;
			static const CDFInteractionScoreGridInputHandler    cdfIntScoreGridInputHandler;
			static const CDFInteractionScoreGridSetInputHandler cdfIntScoreGridSetInputHandler;

			static const CDFFeatureContainerOutputHandler        cdfFtrContOutputHandler;
			static const PMLFeatureContainerOutputHandler        pmlFtrContOutputHandler;
			static const CDFInteractionScoreGridOutputHandler    cdfIntScoreGridOutputHandler;
			static const CDFInteractionScoreGridSetOutputHandler cdfIntScoreGridSetOutputHandler;

			DataIOManager<Pharmacophore>::registerInputHandler(cdfPharmInputHandler);
			DataIOManager<Pharmacophore>::registerInputHandler(pmlPharmInputHandler);
			DataIOManager<InteractionScoreGrid>::registerInputHandler(cdfIntScoreGridInputHandler);
			DataIOManager<InteractionScoreGridSet>::registerInputHandler(cdfIntScoreGridSetInputHandler);

			DataIOManager<FeatureContainer>::registerOutputHandler(cdfFtrContOutputHandler);
			DataIOManager<FeatureContainer>::registerOutputHandler(pmlFtrContOutputHandler);
			DataIOManager<InteractionScoreGrid>::registerOutputHandler(cdfIntScoreGridOutputHandler);
			DataIOManager<InteractionScoreGridSet>::registerOutputHandler(cdfIntScoreGridSetOutputHandler);

#if defined(HAVE_BOOST_FILESYSTEM) && defined(HAVE_BOOST_IOSTREAMS)
#ifdef HAVE_SQLITE3

			static const PSDPharmacophoreInputHandler     psdPharmInputHandler;
			static const PSDMoleculeInputHandler          psdMolInputHandler;
			static const PSDMolecularGraphOutputHandler   psdMolGraphOutputHandler;

			DataIOManager<Pharmacophore>::registerInputHandler(psdPharmInputHandler);
			DataIOManager<Molecule>::registerInputHandler(psdMolInputHandler);
			DataIOManager<MolecularGraph>::registerOutputHandler(psdMolGraphOutputHandler);

#endif // HAVE_SQLITE3

			static const CDFGZPharmacophoreInputHandler            cdfGzPharmInputHandler;
			static const CDFBZ2PharmacophoreInputHandler           cdfBz2PharmInputHandler;
			static const CDFGZInteractionScoreGridInputHandler     cdfGzIntScoreGridInputHandler;
			static const CDFGZInteractionScoreGridSetInputHandler  cdfGzIntScoreGridSetInputHandler;
			static const CDFBZ2InteractionScoreGridInputHandler    cdfBz2IntScoreGridInputHandler;
			static const CDFBZ2InteractionScoreGridSetInputHandler cdfBz2IntScoreGridSetInputHandler;

			static const CDFGZFeatureContainerOutputHandler         cdfGzFtrContOutputHandler;
			static const CDFBZ2FeatureContainerOutputHandler        cdfBz2FtrContOutputHandler;
			static const CDFGZInteractionScoreGridOutputHandler     cdfGzIntScoreGridOutputHandler;
			static const CDFGZInteractionScoreGridSetOutputHandler  cdfGzIntScoreGridSetOutputHandler;
			static const CDFBZ2InteractionScoreGridOutputHandler    cdfBz2IntScoreGridOutputHandler;
			static const CDFBZ2InteractionScoreGridSetOutputHandler cdfBz2IntScoreGridSetOutputHandler;

			DataIOManager<Pharmacophore>::registerInputHandler(cdfGzPharmInputHandler);
			DataIOManager<Pharmacophore>::registerInputHandler(cdfBz2PharmInputHandler);
			DataIOManager<InteractionScoreGrid>::registerInputHandler(cdfGzIntScoreGridInputHandler);
			DataIOManager<InteractionScoreGridSet>::registerInputHandler(cdfGzIntScoreGridSetInputHandler);
			DataIOManager<InteractionScoreGrid>::registerInputHandler(cdfBz2IntScoreGridInputHandler);
			DataIOManager<InteractionScoreGridSet>::registerInputHandler(cdfBz2IntScoreGridSetInputHandler);

			DataIOManager<FeatureContainer>::registerOutputHandler(cdfGzFtrContOutputHandler);
			DataIOManager<FeatureContainer>::registerOutputHandler(cdfBz2FtrContOutputHandler);
			DataIOManager<InteractionScoreGrid>::registerOutputHandler(cdfGzIntScoreGridOutputHandler);
			DataIOManager<InteractionScoreGridSet>::registerOutputHandler(cdfGzIntScoreGridSetOutputHandler);
			DataIOManager<InteractionScoreGrid>::registerOutputHandler(cdfBz2IntScoreGridOutputHandler);
			DataIOManager<InteractionScoreGridSet>::registerOutputHandler(cdfBz2IntScoreGridSetOutputHandler);

#endif // defined(HAVE_BOOST_FILESYSTEM) && defined(HAVE_BOOST_IOSTREAMS)
		}

	} init;
}
