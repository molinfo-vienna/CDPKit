/* 
 * CDFBZ2FeatureContainerOutputHandler.hpp 
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
 * \brief Declaration of type CDPL::Pharm::CDFBZ2FeatureContainerOutputHandler.
 */

#ifndef CDPL_PHARM_CDFBZ2FEATURECONTAINEROUTPUTHANDLER_HPP
#define CDPL_PHARM_CDFBZ2FEATURECONTAINEROUTPUTHANDLER_HPP

#include "CDPL/Pharm/DataFormat.hpp"
#include "CDPL/Pharm/CDFBZ2FeatureContainerWriter.hpp"
#include "CDPL/Util/DefaultDataOutputHandler.hpp"


namespace CDPL
{

    namespace Pharm
    {

        /**
         * \brief A handler for the output of bzip2-compressed feature container data in the native I/O format of the <em>CDPL</em>.
         */
        typedef Util::DefaultDataOutputHandler<CDFBZ2FeatureContainerWriter, DataFormat::CDF_BZ2> CDFBZ2FeatureContainerOutputHandler;
    } // namespace Pharm
} // namespace CDPL

#endif // CDPL_PHARM_CDFBZ2FEATURECONTAINEROUTPUTHANDLER_HPP
