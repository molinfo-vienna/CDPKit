/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * DataFormat.hpp 
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
 * \brief Provides the contents of namespace CDPL::Pharm::DataFormat.
 */

#ifndef CDPL_PHARM_DATAFORMAT_HPP
#define CDPL_PHARM_DATAFORMAT_HPP

#include "CDPL/Pharm/APIPrefix.hpp"


namespace CDPL
{

	namespace Base
	{

		class DataFormat;
	}

	namespace Pharm
	{

		/**
		 * \brief Provides preinitialized Base::DataFormat objects for all supported data formats.
		 */
		namespace DataFormat
		{
	
			/**
			 * \brief Provides meta-information about the native binary <em>CDPL</em> format.
			 */
			extern CDPL_PHARM_API const Base::DataFormat CDF;

			/**
			 * \brief Provides meta-information about the gzip-compressed native <em>CDPL</em> format.
			 */
			extern CDPL_PHARM_API const Base::DataFormat CDF_GZ;

			/**
			 * \brief Provides meta-information about the bzip2-compressed native <em>CDPL</em> format.
			 */
			extern CDPL_PHARM_API const Base::DataFormat CDF_BZ2;

			/**
			 * \brief Provides meta-information about the native pharmacophore <em>LigandScout</em> format.
			 */
			extern CDPL_PHARM_API const Base::DataFormat PML;

			/**
			 * \brief Provides meta-information about the pharmacophore screening database <em>PSD</em> format.
			 */
			extern CDPL_PHARM_API const Base::DataFormat PSD;
		}
	}
}

#endif // CDPL_PHARM_DATAFORMAT_HPP
