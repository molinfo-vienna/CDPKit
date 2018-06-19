/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * Grid.hpp 
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
 * \brief A convenience header including everything that is defined in namespace CDPL::Grid.
 */

#ifndef CDPL_GRID_HPP
#define CDPL_GRID_HPP

#include "CDPL/Config.hpp"      

#include "CDPL/Grid/AttributedGrid.hpp"
#include "CDPL/Grid/SpatialGrid.hpp"
#include "CDPL/Grid/RegularGrid.hpp"
#include "CDPL/Grid/RegularGridSet.hpp"

#include "CDPL/Grid/AttributedGridProperty.hpp"
#include "CDPL/Grid/AttributedGridPropertyDefault.hpp"
#include "CDPL/Grid/ControlParameter.hpp"  
#include "CDPL/Grid/ControlParameterDefault.hpp"  
#include "CDPL/Grid/DataFormat.hpp"

#if defined(HAVE_BOOST_FILESYSTEM) && defined(HAVE_BOOST_IOSTREAMS)

#include "CDPL/Grid/CDFGZDRegularGridWriter.hpp"
#include "CDPL/Grid/CDFDRegularGridOutputHandler.hpp"
#include "CDPL/Grid/CDFBZ2DRegularGridWriter.hpp"
#include "CDPL/Grid/CDFGZDRegularGridSetInputHandler.hpp"
#include "CDPL/Grid/CDFBZ2DRegularGridSetOutputHandler.hpp"
#include "CDPL/Grid/CDFDRegularGridSetReader.hpp"
#include "CDPL/Grid/CDFBZ2DRegularGridOutputHandler.hpp"
#include "CDPL/Grid/CDFBZ2DRegularGridSetInputHandler.hpp"
#include "CDPL/Grid/CDFDRegularGridWriter.hpp"
#include "CDPL/Grid/CDFBZ2DRegularGridInputHandler.hpp"
#include "CDPL/Grid/CDFGZDRegularGridSetOutputHandler.hpp"
#include "CDPL/Grid/CDFDRegularGridSetInputHandler.hpp"
#include "CDPL/Grid/CDFGZDRegularGridReader.hpp"
#include "CDPL/Grid/CDFDRegularGridSetOutputHandler.hpp"
#include "CDPL/Grid/CDFDRegularGridSetWriter.hpp"
#include "CDPL/Grid/CDFBZ2DRegularGridSetWriter.hpp"
#include "CDPL/Grid/CDFGZDRegularGridSetWriter.hpp"
#include "CDPL/Grid/CDFGZDRegularGridOutputHandler.hpp"
#include "CDPL/Grid/CDFDRegularGridInputHandler.hpp"
#include "CDPL/Grid/CDFGZDRegularGridSetReader.hpp"
#include "CDPL/Grid/CDFBZ2DRegularGridSetReader.hpp"
#include "CDPL/Grid/CDFBZ2DRegularGridReader.hpp"
#include "CDPL/Grid/CDFDRegularGridReader.hpp"
#include "CDPL/Grid/CDFGZDRegularGridInputHandler.hpp"

#endif // defined(HAVE_BOOST_FILESYSTEM) && defined(HAVE_BOOST_IOSTREAMS)

#include "CDPL/Grid/AttributedGridFunctions.hpp"
#include "CDPL/Grid/ControlParameterFunctions.hpp"

#endif // CDPL_GRID_HPP
