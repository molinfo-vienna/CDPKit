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
#include "CDPL/Grid/DataFormat.hpp"
#include "CDPL/Grid/CDFDRegularGridInputHandler.hpp"
#include "CDPL/Grid/CDFDRegularGridOutputHandler.hpp"
#include "CDPL/Grid/CDFDRegularGridSetInputHandler.hpp"
#include "CDPL/Grid/CDFDRegularGridSetOutputHandler.hpp"

#if defined(HAVE_BOOST_FILESYSTEM) && defined(HAVE_BOOST_IOSTREAMS)

#include "CDPL/Grid/CDFGZDRegularGridInputHandler.hpp"
#include "CDPL/Grid/CDFGZDRegularGridOutputHandler.hpp"
#include "CDPL/Grid/CDFBZ2DRegularGridInputHandler.hpp"
#include "CDPL/Grid/CDFBZ2DRegularGridOutputHandler.hpp"
#include "CDPL/Grid/CDFGZDRegularGridSetInputHandler.hpp"
#include "CDPL/Grid/CDFGZDRegularGridSetOutputHandler.hpp"
#include "CDPL/Grid/CDFBZ2DRegularGridSetInputHandler.hpp"
#include "CDPL/Grid/CDFBZ2DRegularGridSetOutputHandler.hpp"

#endif // defined(HAVE_BOOST_FILESYSTEM) && defined(HAVE_BOOST_IOSTREAMS)


namespace
{

	const char* cdfFileExtensions[]    = { "cdf" };
	const char* cdfGzFileExtensions[]  = { "cdf.gz" };
	const char* cdfBz2FileExtensions[] = { "cdf.bz2" };

}


using namespace CDPL;


const Base::DataFormat Grid::DataFormat::CDF("CDF", "Native CDPL-Format", "", 
											 cdfFileExtensions, cdfFileExtensions + 1, true);
const Base::DataFormat Grid::DataFormat::CDF_GZ("CDF_GZ", "GZip-Compressed Native CDPL-Format", "", 
												cdfGzFileExtensions, cdfGzFileExtensions + 1, true);
const Base::DataFormat Grid::DataFormat::CDF_BZ2("CDF_BZ2", "BZip2-Compressed Native CDPL-Format", "", 
												 cdfBz2FileExtensions, cdfBz2FileExtensions + 1, true);

namespace CDPL
{

	namespace Grid
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
			using namespace Grid;
			using namespace Chem;

		
			static const CDFDRegularGridInputHandler    cdfDRegularGridInputHandler;
			static const CDFDRegularGridSetInputHandler cdfDRegularGridSetInputHandler;

			static const CDFDRegularGridOutputHandler    cdfDRegularGridOutputHandler;
			static const CDFDRegularGridSetOutputHandler cdfDRegularGridSetOutputHandler;

			DataIOManager<DRegularGrid>::registerInputHandler(cdfDRegularGridInputHandler);
			DataIOManager<DRegularGridSet>::registerInputHandler(cdfDRegularGridSetInputHandler);

			DataIOManager<DRegularGrid>::registerOutputHandler(cdfDRegularGridOutputHandler);
			DataIOManager<DRegularGridSet>::registerOutputHandler(cdfDRegularGridSetOutputHandler);

#if defined(HAVE_BOOST_FILESYSTEM) && defined(HAVE_BOOST_IOSTREAMS)
	
			static const CDFGZDRegularGridInputHandler     cdfGzDRegularGridInputHandler;
			static const CDFGZDRegularGridSetInputHandler  cdfGzDRegularGridSetInputHandler;
			static const CDFBZ2DRegularGridInputHandler    cdfBz2DRegularGridInputHandler;
			static const CDFBZ2DRegularGridSetInputHandler cdfBz2DRegularGridSetInputHandler;

			static const CDFGZDRegularGridOutputHandler     cdfGzDRegularGridOutputHandler;
			static const CDFGZDRegularGridSetOutputHandler  cdfGzDRegularGridSetOutputHandler;
			static const CDFBZ2DRegularGridOutputHandler    cdfBz2DRegularGridOutputHandler;
			static const CDFBZ2DRegularGridSetOutputHandler cdfBz2DRegularGridSetOutputHandler;

			DataIOManager<DRegularGrid>::registerInputHandler(cdfGzDRegularGridInputHandler);
			DataIOManager<DRegularGridSet>::registerInputHandler(cdfGzDRegularGridSetInputHandler);
			DataIOManager<DRegularGrid>::registerInputHandler(cdfBz2DRegularGridInputHandler);
			DataIOManager<DRegularGridSet>::registerInputHandler(cdfBz2DRegularGridSetInputHandler);
			
			DataIOManager<DRegularGrid>::registerOutputHandler(cdfGzDRegularGridOutputHandler);
			DataIOManager<DRegularGridSet>::registerOutputHandler(cdfGzDRegularGridSetOutputHandler);
			DataIOManager<DRegularGrid>::registerOutputHandler(cdfBz2DRegularGridOutputHandler);
			DataIOManager<DRegularGridSet>::registerOutputHandler(cdfBz2DRegularGridSetOutputHandler);

#endif // defined(HAVE_BOOST_FILESYSTEM) && defined(HAVE_BOOST_IOSTREAMS)
		}

	} init;
}
