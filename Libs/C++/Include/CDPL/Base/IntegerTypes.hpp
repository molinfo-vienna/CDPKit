/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * IntegerTypes.hpp 
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
 * \brief Definition of exact-width integer types.
 */

#ifndef CDPL_BASE_INTEGERTYPES_HPP
#define CDPL_BASE_INTEGERTYPES_HPP

#include <boost/cstdint.hpp>

#include "CDPL/Config.hpp"


namespace CDPL 
{ 

	namespace Base
	{

		/**
		 * \brief A 8-bit wide signed integer.
		 */
		typedef boost::int8_t int8;			 

		/**
		 * \brief A 8-bit wide unsigned integer.
		 */
		typedef boost::uint8_t uint8;			
	
		/**
		 * \brief A 16-bit wide signed integer.
		 */
		typedef boost::int16_t int16;			

		/**
		 * \brief A 16-bit wide unsigned integer.
		 */
		typedef boost::uint16_t uint16;		   
		
		/**
		 * \brief A 32-bit wide signed integer.
		 */			 
		typedef boost::int32_t int32;			

		/**
		 * \brief A 32-bit wide unsigned integer.
		 */
		typedef boost::uint32_t uint32;		   

#if	SIZEOF_LONG_INT == 8	

		/**
		 * \brief A 64-bit wide signed integer.
		 */	
		typedef signed long int64;			

		/**
		 * \brief A 64-bit wide unsigned integer.
		 */
		typedef unsigned long uint64;		   
#else
		/**
		 * \brief A 64-bit wide signed integer.
		 */	
		typedef boost::int64_t int64;			

		/**
		 * \brief A 64-bit wide unsigned integer.
		 */
		typedef boost::uint64_t uint64;		   

#endif // SIZEOF_LONG_INT == 8		
	}
}

#endif // CDPL_BASE_INTEGERTYPES_HPP
