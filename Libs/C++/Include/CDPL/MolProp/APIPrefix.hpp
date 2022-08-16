/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * APIPrefix.hpp 
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
 * \brief Definition of the preprocessor macro \ref CDPL_MOLPROP_API.
 */

#ifndef CDPL_MOLPROP_APIPREFIX_HPP
#define CDPL_MOLPROP_APIPREFIX_HPP

#ifdef CDPL_MOLPROP_STATIC_LINK
#  define CDPL_MOLPROP_API
#else // CDPL_MOLPROP_STATIC_LINK
#  include "CDPL/APIPrefix.hpp"
#  ifdef cdpl_molprop_shared_EXPORTS
#    define CDPL_MOLPROP_API CDPL_API_EXPORT
#  else // cdpl_molprop_shared_EXPORTS
#    define CDPL_MOLPROP_API CDPL_API_IMPORT
#  endif // cdpl_molprop_shared_EXPORTS
#endif // CDPL_MOLPROP_STATIC_LINK

/**
 * \def CDPL_MOLPROP_API
 * \brief Tells the compiler/linker which classes, functions and variables are part of the library API.
 */

#endif // CDPL_MOLPROP_APIPREFIX_HPP

