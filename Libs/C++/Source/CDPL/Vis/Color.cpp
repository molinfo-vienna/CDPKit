/* 
 * Color.cpp 
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

#include "CDPL/Vis/Color.hpp"


using namespace CDPL; 


const Vis::Color Vis::Color::BLACK(0.0, 0.0, 0.0);
const Vis::Color Vis::Color::WHITE(1.0, 1.0, 1.0);
const Vis::Color Vis::Color::RED(1.0, 0.0, 0.0);
const Vis::Color Vis::Color::DARK_RED(0.5, 0.0, 0.0);
const Vis::Color Vis::Color::GREEN(0.0, 1.0, 0.0);
const Vis::Color Vis::Color::DARK_GREEN(0.0, 0.5, 0.0);
const Vis::Color Vis::Color::BLUE(0.00, 0.0, 1.0);
const Vis::Color Vis::Color::DARK_BLUE(0.0, 0.0, 0.5);
const Vis::Color Vis::Color::CYAN(0.0, 1.0, 1.0);
const Vis::Color Vis::Color::DARK_CYAN(0.0, 0.5, 0.5);
const Vis::Color Vis::Color::MAGENTA(1.0, 0.0, 1.0);
const Vis::Color Vis::Color::DARK_MAGENTA(0.5, 0.0, 0.5);
const Vis::Color Vis::Color::YELLOW(1.0, 1.0, 0.0);
const Vis::Color Vis::Color::DARK_YELLOW(0.5, 0.5, 0.0);
const Vis::Color Vis::Color::GRAY(0.625, 0.625, 0.625);
const Vis::Color Vis::Color::LIGHT_GRAY(0.75, 0.75, 0.75);
const Vis::Color Vis::Color::DARK_GRAY(0.5, 0.5, 0.5);
const Vis::Color Vis::Color::TRANSPARENT(0.0, 0.0, 0.0, 0.0);


Vis::Color::Color(): red(0.0), green(0.0), blue(0.0), alpha(0.0) {}

Vis::Color::Color(double red, double green, double blue, double alpha)
{
	setRed(red);
	setGreen(green);
	setBlue(blue);
	setAlpha(alpha);
} 

void Vis::Color::setRed(double red)
{
	this->red = (red < 0.0 ? 0.0 : red > 1.0 ? 1.0 : red);
}

double Vis::Color::getRed() const
{
	return red;
}

void Vis::Color::setGreen(double green)
{
	this->green = (green < 0.0 ? 0.0 : green > 1.0 ? 1.0 : green);
}

double Vis::Color::getGreen() const
{
	return green;
}

void Vis::Color::setBlue(double blue)
{
	this->blue = (blue < 0.0 ? 0.0 : blue > 1.0 ? 1.0 : blue);
}

double Vis::Color::getBlue() const
{
	return blue;
}

void Vis::Color::setAlpha(double alpha)
{
	this->alpha = (alpha < 0.0 ? 0.0 : alpha > 1.0 ? 1.0 : alpha);
}

double Vis::Color::getAlpha() const
{
	return alpha;
}

void Vis::Color::setRGBA(double red, double green, double blue, double alpha)
{
	this->red = (red < 0.0 ? 0.0 : red > 1.0 ? 1.0 : red);
	this->green = (green < 0.0 ? 0.0 : green > 1.0 ? 1.0 : green);
	this->blue = (blue < 0.0 ? 0.0 : blue > 1.0 ? 1.0 : blue);
	this->alpha = (alpha < 0.0 ? 0.0 : alpha > 1.0 ? 1.0 : alpha);
}

bool Vis::Color::operator==(const Color& color) const
{
	return (red == color.red && blue == color.blue && green == color.green && alpha == color.alpha);
}

bool Vis::Color::operator!=(const Color& color) const
{
	return !operator==(color);
}
