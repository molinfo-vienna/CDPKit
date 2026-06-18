/* 
 * TorsionLibrary.hpp 
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
 * \brief Definition of class CDPL::ConfGen::TorsionLibrary.
 */

#ifndef CDPL_CONFGEN_TORSIONLIBRARY_HPP
#define CDPL_CONFGEN_TORSIONLIBRARY_HPP

#include <iosfwd>
#include <memory>

#include "CDPL/ConfGen/APIPrefix.hpp"
#include "CDPL/ConfGen/TorsionCategory.hpp"


namespace CDPL
{

    namespace ConfGen
    {

        /**
         * \brief Data structure representing a hierarchical library of torsion rules organized into categories.
         *
         * \c %TorsionLibrary extends ConfGen::TorsionCategory with XML load/save methods and provides
         * static set()/get() accessors for a process-wide default torsion library.
         */
        class CDPL_CONFGEN_API TorsionLibrary : public TorsionCategory
        {

          public:
            /**
             * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %TorsionLibrary instances.
             */
            typedef std::shared_ptr<TorsionLibrary> SharedPointer;

            /**
             * \brief Reads the library content from the input stream \a is in the XML-based \e %CDPL torsion library format.
             * \param is The input stream to read from.
             */
            void load(std::istream& is);

            /**
             * \brief Writes the library content to the output stream \a os in the XML-based \e %CDPL torsion library format.
             * \param os The output stream to write to.
             */
            void save(std::ostream& os) const;

            /**
             * \brief Loads the built-in \e %CDPL default torsion library.
             */
            void loadDefaults();

            /**
             * \brief Sets the globally accessible default torsion library.
             * \param lib The new default library.
             */
            static void set(const SharedPointer& lib);

            /**
             * \brief Returns the globally accessible default torsion library (created on first access).
             * \return A \c const reference to the default torsion library shared pointer.
             */
            static const SharedPointer& get();

          private:
            static SharedPointer defaultLib;
        };
    } // namespace ConfGen
} // namespace CDPL

#endif // CDPL_CONFGEN_TORSIONLIBRARY_HPP
