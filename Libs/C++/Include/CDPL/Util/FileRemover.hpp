/* 
 * FileRemover.hpp 
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
 * \brief Definition of class CDPL::Util::FileRemover
 */

#ifndef CDPL_UTIL_FILEREMOVER_HPP
#define CDPL_UTIL_FILEREMOVER_HPP

#include <string>

#include "CDPL/Util/APIPrefix.hpp"


namespace CDPL
{

    namespace Util
    {

        /**
         * \brief RAII helper that deletes a file when the \c %FileRemover instance goes out of scope (unless released
         *        beforehand). Useful for guaranteeing the cleanup of temporary files.
         */
        class CDPL_UTIL_API FileRemover
        {

          public:
            /**
             * \brief Constructs a \c %FileRemover guarding the file at \a path.
             * \param path The file-system path of the file to remove on destruction.
             */
            FileRemover(const std::string& path):
                path(path) {}

            /**
             * \brief Destructor. Removes the file at the currently held path unless release() has been called.
             */
            ~FileRemover();

            /**
             * \brief Returns the file-system path currently guarded by the \c %FileRemover.
             * \return A \c const reference to the file-system path.
             */
            const std::string& getPath() const;

            /**
             * \brief Replaces the currently held path with \a new_path; the previously held file is removed immediately.
             * \param new_path The new file-system path to guard.
             */
            void reset(const std::string& new_path);

            /**
             * \brief Releases the \c %FileRemover from its current path so that the file will not be removed on destruction.
             */
            void release();

            /**
             * \brief Move-style assignment: takes over the path held by \a rhs and releases \a rhs.
             * \param rhs The \c %FileRemover to take over from.
             * \return A reference to itself.
             */
            FileRemover& operator=(FileRemover& rhs);

          private:
            void removeFile();

            std::string path;
        };
    } // namespace Util
} // namespace CDPL

#endif // CDPL_UTIL_FILEREMOVER_HPP
