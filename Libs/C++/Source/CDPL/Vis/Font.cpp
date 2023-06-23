/* 
 * Font.cpp 
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

#include "CDPL/Vis/Font.hpp"


using namespace CDPL; 


Vis::Font::Font(): 
    family(), size(12.0), bold(false), italic(false), underlined(false), 
    overlined(false), strikedOut(false), fixedPitch(false) {}

Vis::Font::Font(const std::string& family, double size):
    family(family), size(size < 0.0 ? 0.0 : size), bold(false), italic(false), underlined(false), 
    overlined(false), strikedOut(false), fixedPitch(false) {}

void Vis::Font::setFamily(const std::string& family)
{
    this->family = family;
} 

const std::string& Vis::Font::getFamily() const
{
    return family;
} 

void Vis::Font::setSize(double size)
{
    this->size = (size < 0.0 ? 0.0 : size);
} 

double Vis::Font::getSize() const
{
    return size;
} 

void Vis::Font::setBold(bool flag)
{
    bold = flag;
} 

bool Vis::Font::isBold() const
{
    return bold;
} 

void Vis::Font::setItalic(bool flag)
{
    italic = flag;
} 

bool Vis::Font::isItalic() const
{
    return italic;
}

void Vis::Font::setUnderlined(bool flag)
{
    underlined = flag;
} 

bool Vis::Font::isUnderlined() const
{
    return underlined;
} 

void Vis::Font::setOverlined(bool flag)
{
    overlined = flag;
} 

bool Vis::Font::isOverlined() const
{
    return overlined;
} 

void Vis::Font::setStrikedOut(bool flag)
{
    strikedOut = flag;
} 

bool Vis::Font::isStrikedOut() const
{
    return strikedOut;
} 

void Vis::Font::setFixedPitch(bool flag)
{
    fixedPitch = flag;
} 

bool Vis::Font::hasFixedPitch() const
{
    return fixedPitch;
} 

bool Vis::Font::operator==(const Font& font) const
{
    return (family == font.family && size == font.size
            && bold == font.bold && italic == font.italic
            && underlined == font.underlined && overlined == font.overlined
            && strikedOut == font.strikedOut && fixedPitch == font.fixedPitch);
}

bool Vis::Font::operator!=(const Font& font) const
{
    return !operator==(font);
}
