/* 
 * DataFormat.cpp 
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


#include "StaticInit.hpp"

#include "CDPL/Base/DataIOManager.hpp"
#include "CDPL/Base/DataFormat.hpp"
#include "CDPL/Grid/DataFormat.hpp"
#include "CDPL/Grid/CDFDRegularGridInputHandler.hpp"
#include "CDPL/Grid/CDFDRegularGridOutputHandler.hpp"
#include "CDPL/Grid/CDFDRegularGridSetInputHandler.hpp"
#include "CDPL/Grid/CDFDRegularGridSetOutputHandler.hpp"
#include "CDPL/Grid/CDFGZDRegularGridInputHandler.hpp"
#include "CDPL/Grid/CDFGZDRegularGridOutputHandler.hpp"
#include "CDPL/Grid/CDFBZ2DRegularGridInputHandler.hpp"
#include "CDPL/Grid/CDFBZ2DRegularGridOutputHandler.hpp"
#include "CDPL/Grid/CDFGZDRegularGridSetInputHandler.hpp"
#include "CDPL/Grid/CDFGZDRegularGridSetOutputHandler.hpp"
#include "CDPL/Grid/CDFBZ2DRegularGridSetInputHandler.hpp"
#include "CDPL/Grid/CDFBZ2DRegularGridSetOutputHandler.hpp"


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

            DataIOManager<DRegularGrid>::registerInputHandler(DataIOManager<DRegularGrid>::InputHandlerPointer(new CDFDRegularGridInputHandler()));
            DataIOManager<DRegularGridSet>::registerInputHandler(DataIOManager<DRegularGridSet>::InputHandlerPointer(new CDFDRegularGridSetInputHandler()));

            DataIOManager<DRegularGrid>::registerOutputHandler(DataIOManager<DRegularGrid>::OutputHandlerPointer(new CDFDRegularGridOutputHandler()));
            DataIOManager<DRegularGridSet>::registerOutputHandler(DataIOManager<DRegularGridSet>::OutputHandlerPointer(new CDFDRegularGridSetOutputHandler()));
    
            DataIOManager<DRegularGrid>::registerInputHandler(DataIOManager<DRegularGrid>::InputHandlerPointer(new CDFGZDRegularGridInputHandler()));
            DataIOManager<DRegularGridSet>::registerInputHandler(DataIOManager<DRegularGridSet>::InputHandlerPointer(new CDFGZDRegularGridSetInputHandler()));
            DataIOManager<DRegularGrid>::registerInputHandler(DataIOManager<DRegularGrid>::InputHandlerPointer(new CDFBZ2DRegularGridInputHandler()));
            DataIOManager<DRegularGridSet>::registerInputHandler(DataIOManager<DRegularGridSet>::InputHandlerPointer(new CDFBZ2DRegularGridSetInputHandler()));
            
            DataIOManager<DRegularGrid>::registerOutputHandler(DataIOManager<DRegularGrid>::OutputHandlerPointer(new CDFGZDRegularGridOutputHandler()));
            DataIOManager<DRegularGridSet>::registerOutputHandler(DataIOManager<DRegularGridSet>::OutputHandlerPointer(new CDFGZDRegularGridSetOutputHandler()));
            DataIOManager<DRegularGrid>::registerOutputHandler(DataIOManager<DRegularGrid>::OutputHandlerPointer(new CDFBZ2DRegularGridOutputHandler()));
            DataIOManager<DRegularGridSet>::registerOutputHandler(DataIOManager<DRegularGridSet>::OutputHandlerPointer(new CDFBZ2DRegularGridSetOutputHandler()));
        }

    } init;
}
