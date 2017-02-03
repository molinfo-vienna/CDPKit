/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FileFunctions.cpp
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


#include <boost/filesystem.hpp>

#include "CDPL/Util/FileFunctions.hpp"


using namespace CDPL;


std::string Util::genCheckedTempFilePath(const std::string& dir, const std::string& ptn)
{
    namespace bfs = boost::filesystem;

    bfs::path prefix(dir);

    if (prefix.empty())
		prefix = bfs::temp_directory_path();

    while (true) {
		bfs::path tmp_file_path = prefix;

		tmp_file_path /= bfs::unique_path(ptn);

		if (!bfs::exists(tmp_file_path))
			return tmp_file_path.native();
    }
}

bool Util::checkIfSameFile(const std::string& path1, const std::string& path2) 
{
    namespace bfs = boost::filesystem;

    if (bfs::exists(path1) && bfs::exists(path2))
		return bfs::equivalent(path1, path2);

    return (bfs::absolute(path1) == bfs::absolute(path2));
}

bool Util::fileExists(const std::string& path) 
{
    return boost::filesystem::exists(path);
}

