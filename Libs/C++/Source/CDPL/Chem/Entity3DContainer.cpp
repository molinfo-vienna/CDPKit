/* 
 * Entity3DContainer.cpp 
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

#include "CDPL/Chem/Entity3DContainer.hpp"
#include "CDPL/Chem/Entity3D.hpp"


using namespace CDPL;


Chem::Entity3DContainer::ConstEntityIterator Chem::Entity3DContainer::getEntitiesBegin() const
{
    return ConstEntityIterator(this, 0);
}

Chem::Entity3DContainer::ConstEntityIterator Chem::Entity3DContainer::getEntitiesEnd() const
{
    return ConstEntityIterator(this, getNumEntities());
}

Chem::Entity3DContainer::EntityIterator Chem::Entity3DContainer::getEntitiesBegin()
{
    return EntityIterator(this, 0);
}

Chem::Entity3DContainer::EntityIterator Chem::Entity3DContainer::getEntitiesEnd()
{
    return EntityIterator(this, getNumEntities());
}

Chem::Entity3DContainer::ConstEntityIterator Chem::Entity3DContainer::begin() const
{
    return ConstEntityIterator(this, 0);
}

Chem::Entity3DContainer::ConstEntityIterator Chem::Entity3DContainer::end() const
{
    return ConstEntityIterator(this, getNumEntities());
}

Chem::Entity3DContainer::EntityIterator Chem::Entity3DContainer::begin()
{
    return EntityIterator(this, 0);
}

Chem::Entity3DContainer::EntityIterator Chem::Entity3DContainer::end()
{
    return EntityIterator(this, getNumEntities());
}

Chem::Entity3DContainer& Chem::Entity3DContainer::operator=(const Entity3DContainer& cntnr) 
{
    return *this;
}
