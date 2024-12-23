/* 
 * PharmacophoreRemovePositionalDuplicatesFunction.cpp 
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
#include "CDPL/Pharm/Pharmacophore.hpp"
#include "CDPL/Pharm/Feature.hpp"
#include "CDPL/Pharm/FeatureFunctions.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"
#include "CDPL/Math/Vector.hpp"


using namespace CDPL; 


bool Pharm::removePositionalDuplicates(Pharmacophore& pharm, double pos_tol)
{
    std::unordered_set<const Feature*> kept_ftrs;
 
    for (auto& ftr : pharm) {
        auto& pos = get3DCoordinates(ftr);
        auto type = getType(ftr);
        auto dup_ftr_it = kept_ftrs.end();
        
        for (auto it = kept_ftrs.begin(), end = kept_ftrs.end(); it != end; ++it) {
            auto& kept_ftr = *it;
            
            if (getType(*kept_ftr) != type)
                continue;

            if (pos_tol <= 0.0) {
                if (pos != get3DCoordinates(*kept_ftr))
                    continue;
                
            } else {
                if (length(pos - get3DCoordinates(*kept_ftr)) > pos_tol)
                    continue;
            }

            dup_ftr_it = it;
            break;
        }

        if (dup_ftr_it != kept_ftrs.end()) {
            if (getTolerance(ftr) <= getTolerance(**dup_ftr_it))
                continue;
            
            kept_ftrs.erase(dup_ftr_it);
        }
        
        kept_ftrs.insert(&ftr);
    }

    auto rem = false;
    
    for (std::size_t i = 0, num_ftrs = pharm.getNumFeatures(); i < num_ftrs; ) {
        if (kept_ftrs.find(&pharm.getFeature(i)) != kept_ftrs.end()) {
            i++;
            continue;
        }

        pharm.removeFeature(i);
        num_ftrs--;
        rem = true;
    }

    return rem;
}
