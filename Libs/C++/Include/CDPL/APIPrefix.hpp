/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * APIPrefix.hpp 
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
 * \brief Definition of the preprocessor macros \ref CDPL_API_IMPORT and \ref CDPL_API_EXPORT.
 */

#ifndef CDPL_APIPREFIX_HPP
#define CDPL_APIPREFIX_HPP

#if (defined(_WIN32) || defined(__CYGWIN__))
#  define CDPL_API_EXPORT __declspec(dllexport)
#  define CDPL_API_IMPORT __declspec(dllimport)
#else
#  if __GNUC__ >= 4
#    define CDPL_API_EXPORT __attribute__ ((visibility ("default")))
#    define CDPL_API_IMPORT __attribute__ ((visibility ("default")))
#  else
#    define CDPL_API_EXPORT
#    define CDPL_API_IMPORT
#  endif // __GNUC__ >= 4
#endif // (defined(_WIN32) || defined(__CYGWIN__))

#ifdef _MSC_VER
#  pragma warning (disable : 4251) // disable exported dll function
#endif // _MSC_VER

#endif // CDPL_APIPREFIX_HPP

/**
 * \def CDPL_API_IMPORT
 * \brief A platform dependent attribute which tells the compiler/linker that 
 *        a class, function or variable is defined in an external library and
 *        has to be imported.
 */

/**
 * \def CDPL_API_EXPORT
 * \brief A platform dependent attribute which tells the compiler/linker that a
 *        particular class, function or variable is part of the library API and
 *        has to be exported for use in client code.
 */
