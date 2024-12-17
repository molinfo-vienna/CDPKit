/* 
 * FeatureContainerRemovePositionalDuplicatesFunction.cpp 
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

#include "CDPL/Pharm/FeatureContainer.hpp"
#include "CDPL/Pharm/FeatureSet.hpp"
#include "CDPL/Pharm/Feature.hpp"
#include "CDPL/Pharm/FeatureContainerFunctions.hpp"
#include "CDPL/Pharm/FeatureFunctions.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"
#include "CDPL/Math/Vector.hpp"


using namespace CDPL; 


void Pharm::removePositionalDuplicates(const FeatureContainer& cntnr, FeatureSet& tgt_set, double pos_tol, bool append)
{
    if (!append)
        tgt_set.clear();
    
    for (auto& src_ftr : cntnr) {
        auto& pos = get3DCoordinates(src_ftr);
        auto type = getType(src_ftr);
        const Feature* dup_tgt_ftr = nullptr;
        
        for (auto& tgt_ftr : tgt_set) {
            if (getType(tgt_ftr) != type)
                continue;

            if (pos_tol <= 0.0) {
                if (pos != get3DCoordinates(tgt_ftr))
                    continue;
            } else {
                if (length(pos - get3DCoordinates(tgt_ftr)) > pos_tol)
                    continue;
            }

            dup_tgt_ftr = &tgt_ftr;
            break;
        }

        if (dup_tgt_ftr) {
            if (getTolerance(src_ftr) <= getTolerance(*dup_tgt_ftr))
                continue;

            tgt_set.removeFeature(*dup_tgt_ftr);
        }
        
        tgt_set.addFeature(src_ftr);
    }
}
