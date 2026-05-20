/* 
 * FileFunctions.hpp 
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
 * \brief Declaration of filesystem-related functions
 */

#ifndef CDPL_UTIL_FILEFUNCTIONS_HPP
#define CDPL_UTIL_FILEFUNCTIONS_HPP

#include <string>

#include "CDPL/Util/APIPrefix.hpp"


namespace CDPL
{

    namespace Util
    {

        /**
         * \brief Generates a temporary file path inside \a dir whose basename matches the supplied randomization \a ptn
         *        and that is guaranteed not to collide with any existing file.
         * \param dir The directory in which to place the file (an empty string selects the platform's temporary directory).
         * \param ptn The Boost-filesystem-style randomization pattern for the basename (\c % characters are replaced with random hex digits).
         * \return The generated unique file-system path.
         */
        CDPL_UTIL_API std::string genCheckedTempFilePath(const std::string& dir = "",
                                                         const std::string& ptn = "%%%%-%%%%-%%%%-%%%%");

        /**
         * \brief Tells whether \a path1 and \a path2 refer to the same file (after resolving symlinks and case-insensitivity rules of the underlying file system).
         * \param path1 The first file-system path.
         * \param path2 The second file-system path.
         * \return \c true if both paths resolve to the same file, and \c false otherwise.
         */
        CDPL_UTIL_API bool checkIfSameFile(const std::string& path1, const std::string& path2);

        /**
         * \brief Tells whether the file at \a path exists.
         * \param path The file-system path to test.
         * \return \c true if the file exists, and \c false otherwise.
         */
        CDPL_UTIL_API bool fileExists(const std::string& path);
    } // namespace Util
} // namespace CDPL

#endif // CDPL_UTIL_FILEFUNCTIONS_HPP
