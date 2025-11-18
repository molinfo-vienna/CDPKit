/* 
 * PharmacophoreBuildInteractionPharmFunction.cpp 
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

#include <unordered_set>

#include "CDPL/Pharm/PharmacophoreFunctions.hpp"
#include "CDPL/Pharm/FeatureFunctions.hpp"
#include "CDPL/Pharm/Pharmacophore.hpp"
#include "CDPL/Pharm/Feature.hpp"
#include "CDPL/Pharm/FeatureType.hpp"
#include "CDPL/Pharm/FeatureGeometry.hpp"
#include "CDPL/Pharm/FeatureMapping.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"
#include "CDPL/Biomol/AtomFunctions.hpp"


using namespace CDPL; 


namespace
{

    typedef std::unordered_set<std::string> StringSet;
    
    void addResidueInfo(const Pharm::Feature& ftr, StringSet& env_res_list, bool clear = false)
    {
        if (clear)
            env_res_list.clear();

        auto& ftr_substr = getSubstructure(ftr);
        
        if (ftr_substr->getNumAtoms() == 0)
            return;

        auto& atom = ftr_substr->getAtom(0);
        std::string res_id;
        
        if (Biomol::hasResidueCode(atom))
            res_id.append(Biomol::getResidueCode(atom));
        else
            res_id.push_back('?');

        res_id.push_back('_');

        if (Biomol::hasResidueSequenceNumber(atom))
            res_id.append(std::to_string(Biomol::getResidueSequenceNumber(atom)));
        else
            res_id.push_back('?');

        res_id.push_back('_');

        if (Biomol::hasChainID(atom))
            res_id.append(Biomol::getChainID(atom));
        else
            res_id.push_back('?');

        env_res_list.insert(res_id);
    }

    void setEnvironmentResidueInfoProp(Pharm::Feature& ftr, const StringSet& env_res_list)
    {
        if (env_res_list.empty())
            return;

        std::string info_str;

        for (auto& res_id : env_res_list) {
            if (!info_str.empty()) {
                info_str.push_back(',');
                info_str.push_back(' ');
            }

            info_str.append(res_id);
        }

        setEnvironmentResidueInfo(ftr, info_str);
    }
}


void Pharm::generateInteractionPharmacophore(Pharmacophore& pharm, const FeatureMapping& iactions, bool append)
{
    if (!append)
        pharm.clear();

    StringSet env_res_list;
    
    for (FeatureMapping::ConstEntryIterator it = iactions.getEntriesBegin(), end = iactions.getEntriesEnd(); it != end; ) {
        if (!it->first || !it->second) {
            ++it;
            continue;
        }

        const Feature& ftr1 = *it->first;

        if (has3DCoordinates(ftr1)) {
            double dir_factor = 0.0;

            switch (getType(ftr1)) {

                case FeatureType::H_BOND_ACCEPTOR:
                case FeatureType::HALOGEN_BOND_ACCEPTOR:
                    dir_factor = -1.0;
                    break;

                case FeatureType::H_BOND_DONOR:
                case FeatureType::HALOGEN_BOND_DONOR:
                    dir_factor = 1.0;

                default:
                    break;
            }

            if (dir_factor != 0.0) {
                bool created_ftrs = false;
                const Math::Vector3D& ftr1_pos = get3DCoordinates(ftr1);

                env_res_list.clear();
                
                for ( ; it != end && &ftr1 == it->first; ++it) {
                    if (!it->second)
                        continue;

                    const Feature& ftr2 = *it->second;

                    if (!has3DCoordinates(ftr2)) {
                        addResidueInfo(ftr2, env_res_list);
                        continue;
                    }
                    
                    Feature& new_ftr = (pharm.addFeature() = ftr1);
                    Math::Vector3D orient = get3DCoordinates(ftr2);
                    
                    orient.minusAssign(ftr1_pos);

                    double len = length(orient);

                    orient *= dir_factor / len; 

                    setOrientation(new_ftr, orient);
                    setGeometry(new_ftr, FeatureGeometry::VECTOR);
                    setLength(new_ftr, len);

                    addResidueInfo(ftr2, env_res_list, true);
                    setEnvironmentResidueInfoProp(new_ftr, env_res_list);
       
                    created_ftrs = true;
                }

                if (!created_ftrs)
                    setEnvironmentResidueInfoProp(pharm.addFeature() = ftr1, env_res_list);
                
                continue;
            }
        }

        auto& new_ftr = (pharm.addFeature() = ftr1);

        addResidueInfo(*it->second, env_res_list, true);
            
        for (++it; it != end && &ftr1 == it->first; ++it)
            addResidueInfo(*it->second, env_res_list);

        setEnvironmentResidueInfoProp(new_ftr, env_res_list);
    }
}
