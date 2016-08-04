/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * Pharmacophore.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2010 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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

#include "CDPL/Pharm/Pharmacophore.hpp"
#include "CDPL/Pharm/Feature.hpp"
#include "CDPL/Base/Exceptions.hpp"


using namespace CDPL;


Pharm::Pharmacophore::ConstFeatureIterator Pharm::Pharmacophore::getFeaturesBegin() const
{
    return ConstFeatureIterator(*this, 0);
}

Pharm::Pharmacophore::ConstFeatureIterator Pharm::Pharmacophore::getFeaturesEnd() const
{
    return ConstFeatureIterator(*this, getNumFeatures());
}

Pharm::Pharmacophore::FeatureIterator Pharm::Pharmacophore::getFeaturesBegin()
{
    return FeatureIterator(*this, 0);
}

Pharm::Pharmacophore::FeatureIterator Pharm::Pharmacophore::getFeaturesEnd()
{
    return FeatureIterator(*this, getNumFeatures());
}

Pharm::Pharmacophore::FeatureIterator Pharm::Pharmacophore::removeFeature(const FeatureIterator& it)
{
    if (it.getIndex() >= getNumFeatures())
		throw Base::RangeError("Pharmacophore: feature iterator out of valid range");

    removeFeature(it.getIndex());

    return it;
}

Pharm::Pharmacophore& Pharm::Pharmacophore::operator=(const Pharmacophore& pharm) 
{
    if (this == &pharm)
		return *this;

    copy(pharm);

    return *this;
}

Pharm::Pharmacophore& Pharm::Pharmacophore::operator+=(const Pharmacophore& pharm) 
{
    append(pharm);

    return *this;
}

std::size_t Pharm::Pharmacophore::getNumEntities() const
{
	return getNumFeatures();
}

const Chem::Entity3D& Pharm::Pharmacophore::getEntity(std::size_t idx) const
{
	return getFeature(idx);
}

Chem::Entity3D& Pharm::Pharmacophore::getEntity(std::size_t idx)
{
	return getFeature(idx);
}


const Pharm::Feature& Pharm::Pharmacophore::ConstFeatureAccessor::operator()(std::size_t idx) const
{
    return container.get().getFeature(idx);
}

bool Pharm::Pharmacophore::ConstFeatureAccessor::operator==(const ConstFeatureAccessor& accessor) const 
{
    return (container.get_pointer() == accessor.container.get_pointer());
}

Pharm::Pharmacophore::ConstFeatureAccessor& Pharm::Pharmacophore::ConstFeatureAccessor::operator=(const FeatureAccessor& accessor) 
{
    container = boost::reference_wrapper<const Pharmacophore>(accessor.container);
    return *this;
}


Pharm::Feature& Pharm::Pharmacophore::FeatureAccessor::operator()(std::size_t idx) const
{
    return container.get().getFeature(idx);
}

bool Pharm::Pharmacophore::FeatureAccessor::operator==(const FeatureAccessor& accessor) const 
{
    return (container.get_pointer() == accessor.container.get_pointer());
}
