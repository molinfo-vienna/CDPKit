/* 
 * CommonFunctions.hpp
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


#ifndef CONFGEN_COMMONFUNCTIONS_HPP
#define CONFGEN_COMMONFUNCTIONS_HPP

#include <string>

#include <boost/program_options/errors.hpp>
#include <boost/algorithm/string.hpp>

#include "CDPL/ConfGen/ForceFieldType.hpp"


namespace ConfGen
{

    unsigned int stringToForceFieldType(const std::string& type_str, const char* opt)
    {
        namespace po = boost::program_options;
        using namespace CDPL::ConfGen;

        std::string uc_type = type_str;
        boost::to_upper(uc_type);

        if (uc_type == "MMFF94")
            return ForceFieldType::MMFF94;

        if (uc_type == "MMFF94_NO_ESTAT")
            return ForceFieldType::MMFF94_NO_ESTAT;

        if (uc_type == "MMFF94S")
            return ForceFieldType::MMFF94S;

        if (uc_type == "MMFF94S_XOOP")
            return ForceFieldType::MMFF94S_XOOP;

        if (uc_type == "MMFF94S_RTOR")
            return ForceFieldType::MMFF94S_RTOR;

        if (uc_type == "MMFF94S_RTOR_XOOP")
            return ForceFieldType::MMFF94S_RTOR_XOOP;

        if (uc_type == "MMFF94S_NO_ESTAT")
            return ForceFieldType::MMFF94S_NO_ESTAT;

        if (uc_type == "MMFF94S_XOOP_NO_ESTAT")
            return ForceFieldType::MMFF94S_XOOP_NO_ESTAT;

        if (uc_type == "MMFF94S_RTOR_NO_ESTAT")
            return ForceFieldType::MMFF94S_RTOR_NO_ESTAT;

        if (uc_type == "MMFF94S_RTOR_XOOP_NO_ESTAT")
            return ForceFieldType::MMFF94S_RTOR_XOOP_NO_ESTAT;

        throw po::validation_error(po::validation_error::invalid_option_value, opt);
    }

    std::string getForceFieldTypeString(unsigned int ff_type)
    {
        using namespace CDPL::ConfGen;

        switch (ff_type) {

            case ForceFieldType::MMFF94:
                return "MMFF94";

            case ForceFieldType::MMFF94_NO_ESTAT:
                return "MMFF94_NO_ESTAT";

            case ForceFieldType::MMFF94S:
                return "MMFF94S";

            case ForceFieldType::MMFF94S_XOOP:
                return "MMFF94S_XOOP";

            case ForceFieldType::MMFF94S_RTOR:
                return "MMFF94S_RTOR";

            case ForceFieldType::MMFF94S_RTOR_XOOP:
                return "MMFF94S_RTOR_XOOP";

            case ForceFieldType::MMFF94S_NO_ESTAT:
                return "MMFF94S_NO_ESTAT";

            case ForceFieldType::MMFF94S_XOOP_NO_ESTAT:
                return "MMFF94S_XOOP_NO_ESTAT";

            case ForceFieldType::MMFF94S_RTOR_NO_ESTAT:
                return "MMFF94S_RTOR_NO_ESTAT";

            case ForceFieldType::MMFF94S_RTOR_XOOP_NO_ESTAT:
                return "MMFF94S_RTOR_XOOP_NO_ESTAT";

            default:
                break;
        }

        return "UNKNOWN";
    }
} // namespace ConfGen

#endif // CONFGEN_COMMONFUNCTIONS_HPP
