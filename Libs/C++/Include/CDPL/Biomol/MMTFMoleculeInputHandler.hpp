/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MMTFMoleculeInputHandler.hpp 
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
 * \brief Definition of the class CDPL::Biomol::MMTFMoleculeInputHandler.
 */

#ifndef CDPL_BIOMOL_MMTFMOLECULEINPUTHANDLER_HPP
#define CDPL_BIOMOL_MMTFMOLECULEINPUTHANDLER_HPP

#include "CDPL/Biomol/DataFormat.hpp"
#include "CDPL/Biomol/MMTFMoleculeReader.hpp"
#include "CDPL/Util/DefaultDataInputHandler.hpp"


namespace CDPL 
{

	namespace Biomol
	{

		/**
		 * \addtogroup CDPL_BIOMOL_MMTF_IO
		 * @{
		 */

		/**
		 * \brief A handler for the input of molecule data in the <em>Macromolecular Transmission Format (MMTF)y</em>
		 *        [\ref MMTF].
		 */
		typedef Util::DefaultDataInputHandler<MMTFMoleculeReader, DataFormat::MMTF> MMTFMoleculeInputHandler;

		/**
		 * @}
		 */
	}
}

#endif // CDPL_BIOMOL_MMTFMOLECULEINPUTHANDLER_HPP
