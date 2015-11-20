/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * VersionInfoExport.cpp 
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


#include <boost/python.hpp>

#include "CDPL/Version.hpp"

#include "Exports.hpp"


void CDPLPython::exportVersionInfo()
{
	using namespace boost;

	python::scope module;

    module.attr("MAJOR_VERSION") = CDPL_MAJOR_VERSION;
    module.attr("MINOR_VERSION") = CDPL_MINOR_VERSION;
    module.attr("PATCH_VERSION") = CDPL_PATCH_VERSION;
    module.attr("VERSION") = CDPL_VERSION;
    module.attr("VERSION_STRING") = CDPL_VERSION_STRING;
    module.attr("BUILD_DATE") = CDPL_BUILD_DATE;
}
