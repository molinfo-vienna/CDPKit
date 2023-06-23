/* 
 * FeatureContainerGetFeatureAtomsFunction.cpp 
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

#include <algorithm>
#include <functional>

#include "CDPL/Pharm/FeatureContainerFunctions.hpp"
#include "CDPL/Pharm/FeatureContainer.hpp"
#include "CDPL/Pharm/Feature.hpp"
#include "CDPL/Pharm/FeatureFunctions.hpp"
#include "CDPL/Chem/Fragment.hpp"
#include "CDPL/Chem/Atom.hpp"


using namespace CDPL; 


void Pharm::getFeatureAtoms(const FeatureContainer& cntnr, Chem::Fragment& atoms, bool append)
{
    if (!append)
        atoms.clear();

    for (FeatureContainer::ConstFeatureIterator it = cntnr.getFeaturesBegin(), end = cntnr.getFeaturesEnd(); it != end; ++it) {
        const Feature& ftr = *it;

        if (!hasSubstructure(ftr))
            continue;

        const Chem::Fragment::SharedPointer substruct = getSubstructure(ftr);

        std::for_each(substruct->getAtomsBegin(), substruct->getAtomsEnd(), 
                      std::bind(&Chem::Fragment::addAtom, std::ref(atoms), std::placeholders::_1));
    }
}
