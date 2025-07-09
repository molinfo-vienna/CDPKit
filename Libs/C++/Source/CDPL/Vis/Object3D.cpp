/* 
 * Object3D.cpp 
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

#include "CDPL/Vis/Object3D.hpp"
#include "CDPL/Base/Exceptions.hpp"


using namespace CDPL;


Vis::Object3D::Object3D() {}

Vis::Object3D::Object3D(const Object3D& obj): Base::PropertyContainer(obj)
{
    subObjects = obj.subObjects;
}

Vis::Object3D& Vis::Object3D::operator=(const Object3D& obj) 
{
    if (this == &obj)
        return *this;

    PropertyContainer::operator=(obj);

    subObjects = obj.subObjects;
    
    return *this;
}

void Vis::Object3D::clear()
{
    PropertyContainer::clearProperties();
    subObjects.clear();
}

std::size_t Vis::Object3D::getNumSubObjects() const
{
    return subObjects.size();
}

Vis::Object3D::ConstObject3DIterator Vis::Object3D::getSubObjectsBegin() const
{
    return subObjects.begin();
}

Vis::Object3D::Object3DIterator Vis::Object3D::getSubObjectsBegin()
{
    return subObjects.begin();
}

Vis::Object3D::ConstObject3DIterator Vis::Object3D::getSubObjectsEnd() const
{
    return subObjects.end();
}

Vis::Object3D::Object3DIterator Vis::Object3D::getSubObjectsEnd()
{
    return subObjects.end();
}

Vis::Object3D::ConstObject3DIterator Vis::Object3D::begin() const
{
    return subObjects.begin();
}

Vis::Object3D::Object3DIterator Vis::Object3D::begin()
{
    return subObjects.begin();
}

Vis::Object3D::ConstObject3DIterator Vis::Object3D::end() const
{
    return subObjects.end();
}

Vis::Object3D::Object3DIterator Vis::Object3D::end()
{
    return subObjects.end();
}

const Vis::Object3D& Vis::Object3D::getSubObject(std::size_t idx) const
{
    if (idx >= subObjects.size())
        throw Base::IndexError("Object3D: sub-object index out of bounds");

    return *subObjects[idx];
}

Vis::Object3D& Vis::Object3D::getSubObject(std::size_t idx)
{
    if (idx >= subObjects.size())
        throw Base::IndexError("Object3D: sub-object index out of bounds");

    return *subObjects[idx];
}

Vis::Object3D& Vis::Object3D::addSubObject()
{
    subObjects.emplace_back(SharedPointer(new Object3D()));

    return *subObjects.back();
}

Vis::Object3D& Vis::Object3D::addSubObject(const SharedPointer& object)
{
    subObjects.emplace_back(object);

    return *object;
}

void Vis::Object3D::removeSubObject(std::size_t idx)
{
    if (idx >= subObjects.size())
        throw Base::IndexError("Object3D: sub-object index out of bounds");

    subObjects.erase(subObjects.begin() + idx);
}

Vis::Object3D::Object3DIterator Vis::Object3D::removeSubObject(const Object3DIterator& it)
{
    auto& base = it.base();

    if ((base < subObjects.begin()) || (base >= subObjects.end()))
        throw Base::RangeError("Object3D: sub-object iterator out of valid range");

    return subObjects.erase(base);
}
