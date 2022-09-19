/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * Util.hpp 
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

/**
 * \file
 * \brief A convenience header including everything that is defined in namespace CDPL::Util.
 */

#ifndef CDPL_UTIL_HPP
#define CDPL_UTIL_HPP

#include "CDPL/Config.hpp"

#include "CDPL/Util/Array.hpp"
#include "CDPL/Util/BitSet.hpp"
#include "CDPL/Util/BronKerboschAlgorithm.hpp"
#include "CDPL/Util/DGCoordinatesGenerator.hpp"
#include "CDPL/Util/Dereferencer.hpp"
#include "CDPL/Util/IndexedElementIterator.hpp"
#include "CDPL/Util/IndirectArray.hpp"
#include "CDPL/Util/Map.hpp"
#include "CDPL/Util/MultiMap.hpp"
#include "CDPL/Util/PropertyValue.hpp"
#include "CDPL/Util/PropertyValueProduct.hpp"
#include "CDPL/Util/StreamDataReader.hpp"
#include "CDPL/Util/CompoundDataReader.hpp"
#include "CDPL/Util/FileDataReader.hpp"
#include "CDPL/Util/FileDataWriter.hpp"
#include "CDPL/Util/DefaultDataInputHandler.hpp"
#include "CDPL/Util/ObjectPool.hpp"
#include "CDPL/Util/ObjectStack.hpp"
#include "CDPL/Util/SequenceFunctions.hpp"

#if defined(HAVE_BOOST_FILESYSTEM)

#include "CDPL/Util/FileRemover.hpp"
#include "CDPL/Util/FileFunctions.hpp"

#if defined(HAVE_BOOST_IOSTREAMS)

#include "CDPL/Util/CompressionStreams.hpp"
#include "CDPL/Util/CompressedDataReader.hpp"
#include "CDPL/Util/CompressedDataWriter.hpp"

#endif // defined(HAVE_BOOST_IOSTREAMS)
#endif // defined(HAVE_BOOST_FILESYSTEM)
#endif // CDPL_UTIL_HPP
