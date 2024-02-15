/* 
 * FileFunctions.cpp
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


#if defined(unix) || defined(__unix__) || defined(__unix)
# include <stdlib.h>
#endif

#include <random>
#include <mutex>

#ifdef HAVE_CXX17_FILESYSTEM_SUPPORT
# include <filesystem>
# define FILESYSTEM_NS std::filesystem
#else
# include <boost/filesystem.hpp>
# define FILESYSTEM_NS boost::filesystem
#endif

#include "CDPL/Util/FileFunctions.hpp"


#if defined(unix) || defined(__unix__) || defined(__unix)
namespace
{

    struct Init {
        
        Init() {
            setenv("LC_ALL", "C", 0);  // prevent the throwing of an exception if LC_ALL is not set!
        }
    } init;
}
#endif

namespace
{

    std::random_device::result_type getRandomSeed()
    {
        static std::random_device rand_dev;
        static std::mutex rand_dev_mtx;

        std::lock_guard<std::mutex> lock(rand_dev_mtx);
        
        return rand_dev();
    }
    
    std::string generateRandomName(const std::string& ptn)
    {
        static const char alphabet[] = "0123456789abcdefghijklmnopqrstuvwxyz";

        std::mt19937 rand_gen(getRandomSeed());
        std::uniform_int_distribution<std::size_t> rand_dist(0, sizeof(alphabet) - 2);        
        std::string name;
        
        for (char c : ptn)
            if (c == '%')
                name.push_back(alphabet[rand_dist(rand_gen)]);
            else
                name.push_back(c);
        
        return name;
    }
}


using namespace CDPL;


std::string Util::genCheckedTempFilePath(const std::string& dir, const std::string& ptn)
{
    namespace fsns = FILESYSTEM_NS;

    while (true) {
        fsns::path tmp_file_path = (dir.empty() ? fsns::temp_directory_path() : fsns::path(dir)) / generateRandomName(ptn);

        tmp_file_path /= generateRandomName(ptn);

        if (!fsns::exists(tmp_file_path))
            return tmp_file_path.string();
    }
}

bool Util::checkIfSameFile(const std::string& path1, const std::string& path2) 
{
    namespace fsns = FILESYSTEM_NS;

    if (fsns::exists(path1) && fsns::exists(path2))
        return fsns::equivalent(path1, path2);

    return (fsns::absolute(path1) == fsns::absolute(path2));
}

bool Util::fileExists(const std::string& path) 
{
    return FILESYSTEM_NS::exists(path);
}
