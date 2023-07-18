/* 
 * HelperFunctions.hpp
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


#ifndef CMDLINE_LIB_HELPERFUNCTIONS_HPP
#define CMDLINE_LIB_HELPERFUNCTIONS_HPP

#include <string>
#include <cstddef>

#include "CDPL/Base/DataIOManager.hpp"


namespace CmdLineLib
{

    template <typename T, typename OutIter>
    void getSupportedInputFormats(OutIter out)
    {
        using namespace CDPL;

        std::string format_str;

        for (auto it  = Base::DataIOManager<T>::getInputHandlersBegin(),
                  end = Base::DataIOManager<T>::getInputHandlersEnd();
             it != end; ++it, ++out) {

            const Base::DataFormat& fmt_desc = (*it)->getDataFormat();

            format_str.clear();
            format_str.append(fmt_desc.getDescription());
            format_str.append(" (");

            for (std::size_t i = 0; i < fmt_desc.getNumFileExtensions(); i++) {
                if (i > 0)
                    format_str.append(", ");

                format_str.append("*.").append(fmt_desc.getFileExtension(i));
            }

            format_str.push_back(')');

            *out = format_str;
        }
    }

    template <typename T, typename OutIter>
    void getSupportedOutputFormats(OutIter out)
    {
        using namespace CDPL;

        std::string format_str;

        for (auto it  = Base::DataIOManager<T>::getOutputHandlersBegin(),
                  end = Base::DataIOManager<T>::getOutputHandlersEnd();
             it != end; ++it, ++out) {

            const Base::DataFormat& fmt_desc = (*it)->getDataFormat();

            format_str.clear();
            format_str.append(fmt_desc.getDescription());
            format_str.append(" (");

            for (std::size_t i = 0; i < fmt_desc.getNumFileExtensions(); i++) {
                if (i > 0)
                    format_str.append(", ");

                format_str.append("*.").append(fmt_desc.getFileExtension(i));
            }

            format_str.push_back(')');

            *out = format_str;
        }
    }

    std::string formatTimeDuration(std::size_t secs);

} // namespace CmdLineLib

#endif // CMDLINE_LIB_HELPERFUNCTIONS_HPP
