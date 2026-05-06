/* 
 * FeatureEnvironmentResidueInfoFunctions.cpp 
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


#include "StaticInit.hpp"

#include <set>

#include "CDPL/Pharm/FeatureFunctions.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Biomol/AtomFunctions.hpp"


using namespace CDPL; 


namespace
{

    std::string& buildEnvironmentResidueInfoString(const Pharm::Feature& ftr, std::string& info_str, bool atom_info)
    {
        std::set<std::string> id_set;
        
        auto& env_substr = getEnvironmentSubstructure(ftr);
       
        for (auto& atom : env_substr->getAtoms()) {
            info_str.clear();
        
            if (Biomol::hasResidueCode(atom))
                info_str.append(Biomol::getResidueCode(atom));
            else
                info_str.push_back('?');

            info_str.push_back('_');
            
            if (Biomol::hasResidueSequenceNumber(atom))
                info_str.append(std::to_string(Biomol::getResidueSequenceNumber(atom)));
            else
                info_str.push_back('?');
            
            info_str.push_back('_');

            if (Biomol::hasChainID(atom))
                info_str.append(Biomol::getChainID(atom));
            else
                info_str.push_back('?');

            if (atom_info) {
                info_str.push_back('_');

                if (Biomol::hasSerialNumber(atom))
                    info_str.append(std::to_string(Biomol::getSerialNumber(atom)));
                else
                    info_str.push_back('?');
            }

            id_set.insert(info_str);
        }

        info_str.clear();

        for (auto& elem : id_set) {
            if (!info_str.empty()) {
                info_str.push_back(',');
                info_str.push_back(' ');
            }

            info_str.append(elem);
        }

        return info_str;
    }
}

std::string Pharm::getEnvironmentResidueInfo(const Feature& feature)
{
    std::string tmp;

    return buildEnvironmentResidueInfoString(feature, tmp, false);
}

std::string& Pharm::getEnvironmentResidueInfo(const Feature& feature, std::string& info)
{
    return buildEnvironmentResidueInfoString(feature, info, false);
}

std::string Pharm::getEnvironmentResidueAtomInfo(const Feature& feature)
{
    std::string tmp;

    return buildEnvironmentResidueInfoString(feature, tmp, true);
}

std::string& Pharm::getEnvironmentResidueAtomInfo(const Feature& feature, std::string& info)
{
    return buildEnvironmentResidueInfoString(feature, info, true);
}
