/* 
 * Entity3DContainerGeomDiameterAndRadiusFunctions.cpp 
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
#include <limits>

#include "CDPL/Descr/Entity3DContainerFunctions.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"
#include "CDPL/Chem/Entity3DContainer.hpp"
#include "CDPL/Chem/Entity3D.hpp"


using namespace CDPL; 


double Descr::calcGeometricalRadius(const Chem::Entity3DContainer& cntnr)
{
    using namespace Chem;
    
    if (cntnr.getNumEntities() <= 1)
        return 0.0;

    double radius = std::numeric_limits<double>::max();

    Entity3DContainer::ConstEntityIterator entities_end = cntnr.getEntitiesEnd();
    Entity3DContainer::ConstEntityIterator entities_beg = cntnr.getEntitiesBegin();

    for (Entity3DContainer::ConstEntityIterator it1 = entities_beg; it1 != entities_end; ++it1) {
        const Entity3D& entity1 = *it1;
        const Math::Vector3D& coords1 = get3DCoordinates(entity1);

        double max_entity_dist = 0.0;

        for (Entity3DContainer::ConstEntityIterator it2 = entities_beg; it2 != entities_end; ++it2) {
            const Entity3D& entity2 = *it2;

            if (&entity1 == &entity2)
                continue;

            const Math::Vector3D& coords2 = get3DCoordinates(entity2);

            max_entity_dist = std::max(max_entity_dist, norm2(coords1 - coords2));
        }

        radius = std::min(max_entity_dist, radius);
    }

    return radius;
}

double Descr::calcGeometricalDiameter(const Chem::Entity3DContainer& cntnr)
{
    using namespace Chem;

    double diameter = 0.0;

    Entity3DContainer::ConstEntityIterator entities_end = cntnr.getEntitiesEnd();

    for (Entity3DContainer::ConstEntityIterator it1 = cntnr.getEntitiesBegin(); it1 != entities_end; ) {
        const Entity3D& entity1 = *it1;
        const Math::Vector3D& coords1 = get3DCoordinates(entity1);

        for (Entity3DContainer::ConstEntityIterator it2 = ++it1; it2 != entities_end; ++it2) {
            const Entity3D& entity2 = *it2;
            const Math::Vector3D& coords2 = get3DCoordinates(entity2);

            diameter = std::max(diameter, norm2(coords1 - coords2));
        }
    }

    return diameter;
}
