/* 
 * Version.hpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2008 Thomas A. Seidel <thomas.seidel@chemit.at>
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
 * \brief The header to include for \e %CDPL version and build time information.
 */

#ifndef CDPL_VERSION_HPP
#define CDPL_VERSION_HPP

/**
 * \brief The \e %CDPL major version number. 
 */
#define CDPL_MAJOR_VERSION 1

/**
 * \brief The \e %CDPL minor version number. 
 */
#define CDPL_MINOR_VERSION 0

/**
 * \brief The \e %CDPL patch-level. 
 */
#define CDPL_PATCH_VERSION 0

/**
 * \brief The \e %CDPL version as a string. 
 */
#define CDPL_VERSION_STRING "1.0.0"

/**
 * \brief The \e %CDPL build date in the format \e YYYYMMDD. 
 */
#define CDPL_BUILD_DATE 20181003


/** 
 * \brief The full \e %CDPL version number. 
 */
#define CDPL_VERSION (CDPL_MAJOR_VERSION * 10000 + CDPL_MINOR_VERSION * 100 + CDPL_PATCH_VERSION)

#endif // CDPL_VERSION_HPP
