/* 
 * Material.cpp 
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

#include "CDPL/Vis/Material.hpp"


using namespace CDPL;


Vis::Material::Material(const Color& amb_color, double amb_factor, const Color& diff_color, const Color& spec_color, double shininess, double transp):
    ambient(amb_color), diffuse(diff_color), specular(spec_color)
{
    setAmbientFactor(amb_factor);
    setShininess(shininess);
    setTransparency(transp);
}

Vis::Material::Material(double amb_factor, const Color& diff_color, const Color& spec_color, double shininess, double transp):
    ambient(diff_color.getRed() * amb_factor, diff_color.getGreen() * amb_factor, diff_color.getBlue() * amb_factor, diff_color.getAlpha()),
    diffuse(diff_color), specular(spec_color)
{
    setAmbientFactor(amb_factor);
    setShininess(shininess);
    setTransparency(transp);
}

void Vis::Material::setAmbientColor(const Color& color)
{
    ambient = color;
}

const Vis::Color& Vis::Material::getAmbientColor() const
{
    return ambient;
}

void Vis::Material::setAmbientFactor(double factor)
{
    ambientFactor = (factor < 0.0 ? 0.0 : factor > 1.0 ? 1.0 : factor);
}

double Vis::Material::getAmbientFactor() const
{
    return ambientFactor;
}

void Vis::Material::setDiffuseColor(const Color& color)
{
    diffuse = color;
}

const Vis::Color& Vis::Material::getDiffuseColor() const
{
    return diffuse;
}

void Vis::Material::setSpecularColor(const Color& color)
{
    specular = color;
}

const Vis::Color& Vis::Material::getSpecularColor() const
{
    return specular;
}

void Vis::Material::setShininess(double shininess)
{
    this->shininess = (shininess < 0.0 ? 0.0 : shininess > 1.0 ? 1.0 : shininess);
}

double Vis::Material::getShininess() const
{
    return shininess;
}

void Vis::Material::setTransparency(double transp)
{
    transparency = (transp < 0.0 ? 0.0 : transp > 1.0 ? 1.0 : transp);
}

double Vis::Material::getTransparency() const
{
    return transparency;
}

bool Vis::Material::operator==(const Material& material) const
{
    return (ambient == material.ambient && ambientFactor == material.ambientFactor && diffuse == material.diffuse &&
            specular == material.specular && shininess == material.shininess && transparency == material.transparency);
}

bool Vis::Material::operator!=(const Material& material) const
{
    return !operator==(material);
}
