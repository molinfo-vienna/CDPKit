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

#include <set>

#include "CDPL/Pharm/PharmacophoreFunctions.hpp"
#include "CDPL/Pharm/FeatureFunctions.hpp"
#include "CDPL/Pharm/Pharmacophore.hpp"
#include "CDPL/Pharm/Feature.hpp"
#include "CDPL/Pharm/FeatureType.hpp"
#include "CDPL/Pharm/FeatureGeometry.hpp"
#include "CDPL/Pharm/FeatureMapping.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"
#include "CDPL/Chem/Fragment.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Biomol/AtomFunctions.hpp"


using namespace CDPL; 


namespace
{

    typedef std::set<std::string> StringSet;

    void stringSetToStr(const StringSet& str_set, std::string& out_str)
    {
        out_str.clear();

        for (auto& elem : str_set) {
            if (!out_str.empty()) {
                out_str.push_back(',');
                out_str.push_back(' ');
            }

            out_str.append(elem);
        }
    }
    
    void setEnvResidueAndAtomInfoProps(Pharm::Feature& ftr)
    {
        StringSet env_res_list;
        StringSet env_atom_list;
        std::string tmp;
        
        auto& ftr_substr = getEnvironmentSubstructure(ftr);
       
        for (auto& atom : ftr_substr->getAtoms()) {
            tmp.clear();
        
            if (Biomol::hasResidueCode(atom))
                tmp.append(Biomol::getResidueCode(atom));
            else
                tmp.push_back('?');

            tmp.push_back('_');
            
            if (Biomol::hasResidueSequenceNumber(atom))
                tmp.append(std::to_string(Biomol::getResidueSequenceNumber(atom)));
            else
                tmp.push_back('?');
            
            tmp.push_back('_');

            if (Biomol::hasChainID(atom))
                tmp.append(Biomol::getChainID(atom));
            else
                tmp.push_back('?');

            env_res_list.insert(tmp);

            tmp.push_back('_');

            if (Biomol::hasSerialNumber(atom))
                tmp.append(std::to_string(Biomol::hasSerialNumber(atom)));
            else
                tmp.push_back('?');
              
            env_atom_list.insert(tmp);
        }

        stringSetToStr(env_res_list, tmp);
        setEnvironmentResidueInfo(ftr, tmp);

        stringSetToStr(env_atom_list, tmp);
        setEnvironmentResidueAtomInfo(ftr, tmp);
    }
}


void Pharm::generateInteractionPharmacophore(Pharmacophore& pharm, const FeatureMapping& iactions, bool append)
{
    if (!append)
        pharm.clear();
   
    for (FeatureMapping::ConstEntryIterator it = iactions.getEntriesBegin(), end = iactions.getEntriesEnd(); it != end; ) {
        if (!it->first || !it->second) {
            ++it;
            continue;
        }

        const Feature& ftr1 = *it->first;
        Chem::Fragment::SharedPointer env_substr(new Chem::Fragment());
 
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
  
                for ( ; it != end && &ftr1 == it->first; ++it) {
                    if (!it->second)
                        continue;

                    const Feature& ftr2 = *it->second;

                    if (!has3DCoordinates(ftr2)) {
                        *env_substr += *getSubstructure(ftr2);
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
                    setEnvironmentSubstructure(new_ftr, getSubstructure(ftr2));
                    setEnvResidueAndAtomInfoProps(new_ftr);
                    
                    created_ftrs = true;
                }

                if (!created_ftrs) {
                    auto& new_ftr = (pharm.addFeature() = ftr1);

                    setEnvironmentSubstructure(new_ftr, env_substr);
                    setEnvResidueAndAtomInfoProps(new_ftr);
                }
                
                continue;
            }
        }

        auto& new_ftr = (pharm.addFeature() = ftr1);

        *env_substr += *getSubstructure(*it->second);
            
        for (++it; it != end && &ftr1 == it->first; ++it)
            *env_substr += *getSubstructure(*it->second);

        setEnvironmentSubstructure(new_ftr, env_substr);
        setEnvResidueAndAtomInfoProps(new_ftr);
    }
}
