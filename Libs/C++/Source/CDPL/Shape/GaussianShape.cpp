/* 
 * GaussianShape.cpp 
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

#include "CDPL/Shape/GaussianShape.hpp"
#include "CDPL/Base/Exceptions.hpp"


using namespace CDPL;


void Shape::GaussianShape::clear()
{
    elements.clear();
}

void Shape::GaussianShape::addElement(const Math::Vector3D& pos, double radius, std::size_t color, double hardness)
{
    elements.push_back(Element(pos, radius, color, hardness));
}

void Shape::GaussianShape::addElement(const Element& elem)
{
    elements.push_back(elem);
}

void Shape::GaussianShape::removeElement(std::size_t idx)
{
    if (idx >= elements.size())
        throw Base::IndexError("GaussianShape: element index out of bounds");

    elements.erase(elements.begin() + idx);
}

std::size_t Shape::GaussianShape::getNumElements() const
{
    return elements.size();
}

const Shape::GaussianShape::Element& Shape::GaussianShape::getElement(std::size_t idx) const
{
    if (idx >= elements.size())
        throw Base::IndexError("GaussianShape: element index out of bounds");

    return elements[idx];
}

Shape::GaussianShape::Element& Shape::GaussianShape::getElement(std::size_t idx)
{
    if (idx >= elements.size())
        throw Base::IndexError("GaussianShape: element index out of bounds");

    return elements[idx];
}

Shape::GaussianShape::ConstElementIterator Shape::GaussianShape::getElementsBegin() const
{
    return elements.begin();
}

Shape::GaussianShape::ConstElementIterator Shape::GaussianShape::getElementsEnd() const
{
    return elements.end();
}

Shape::GaussianShape::ElementIterator Shape::GaussianShape::getElementsBegin()
{
    return elements.begin();
}

Shape::GaussianShape::ElementIterator Shape::GaussianShape::getElementsEnd()
{
    return elements.end();
}

Shape::GaussianShape::ConstElementIterator Shape::GaussianShape::begin() const
{
    return elements.begin();
}

Shape::GaussianShape::ConstElementIterator Shape::GaussianShape::end() const
{
    return elements.end();
}

Shape::GaussianShape::ElementIterator Shape::GaussianShape::begin()
{
    return elements.begin();
}

Shape::GaussianShape::ElementIterator Shape::GaussianShape::end()
{
    return elements.end();
}
