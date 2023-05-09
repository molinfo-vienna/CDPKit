/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * SizeSpecification.cpp 
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

#include "CDPL/Vis/SizeSpecification.hpp"


using namespace CDPL;

		
void Vis::SizeSpecification::setValue(double value)
{
	this->value = value;
}

double Vis::SizeSpecification::getValue() const
{
	return value;
}

void Vis::SizeSpecification::setRelative(bool relative)
{
	this->relative = relative;
}

bool Vis::SizeSpecification::isRelative() const
{
	return relative;
}

void Vis::SizeSpecification::followInputScaling(bool follow)
{
	inputScaling = follow;
}

bool Vis::SizeSpecification::followsInputScaling() const
{
	return inputScaling;
}

void Vis::SizeSpecification::followOutputScaling(bool follow)
{
	outputScaling = follow;
}

bool Vis::SizeSpecification::followsOutputScaling() const
{
	return outputScaling;
}

bool Vis::SizeSpecification::operator==(const SizeSpecification& spec) const
{
	return (value == spec.value && relative == spec.relative 
			&& inputScaling == spec.inputScaling && outputScaling == spec.outputScaling);
}

bool Vis::SizeSpecification::operator!=(const SizeSpecification& spec) const
{
	return !operator==(spec);
}
