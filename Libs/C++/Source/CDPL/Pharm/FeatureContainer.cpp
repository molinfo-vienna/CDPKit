/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FeatureContainer.cpp 
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

#include "CDPL/Pharm/FeatureContainer.hpp"
#include "CDPL/Pharm/Feature.hpp"


using namespace CDPL;


Pharm::FeatureContainer::ConstFeatureIterator Pharm::FeatureContainer::getFeaturesBegin() const
{
    return ConstFeatureIterator(*this, 0);
}

Pharm::FeatureContainer::ConstFeatureIterator Pharm::FeatureContainer::getFeaturesEnd() const
{
    return ConstFeatureIterator(*this, getNumFeatures());
}

Pharm::FeatureContainer::FeatureIterator Pharm::FeatureContainer::getFeaturesBegin()
{
    return FeatureIterator(*this, 0);
}

Pharm::FeatureContainer::FeatureIterator Pharm::FeatureContainer::getFeaturesEnd()
{
    return FeatureIterator(*this, getNumFeatures());
}

Pharm::FeatureContainer& Pharm::FeatureContainer::operator=(const FeatureContainer& cntnr) 
{
    if (this == &cntnr)
	return *this;

    Base::PropertyContainer::operator=(cntnr);
    Chem::Entity3DContainer::operator=(cntnr);

    return *this;
}

std::size_t Pharm::FeatureContainer::getNumEntities() const
{
	return getNumFeatures();
}

const Chem::Entity3D& Pharm::FeatureContainer::getEntity(std::size_t idx) const
{
	return getFeature(idx);
}

Chem::Entity3D& Pharm::FeatureContainer::getEntity(std::size_t idx)
{
	return getFeature(idx);
}


const Pharm::Feature& Pharm::FeatureContainer::ConstFeatureAccessor::operator()(std::size_t idx) const
{
    return container.get().getFeature(idx);
}

bool Pharm::FeatureContainer::ConstFeatureAccessor::operator==(const ConstFeatureAccessor& accessor) const 
{
    return (container.get_pointer() == accessor.container.get_pointer());
}

Pharm::FeatureContainer::ConstFeatureAccessor& Pharm::FeatureContainer::ConstFeatureAccessor::operator=(const FeatureAccessor& accessor) 
{
    container = boost::reference_wrapper<const FeatureContainer>(accessor.container);
    return *this;
}


Pharm::Feature& Pharm::FeatureContainer::FeatureAccessor::operator()(std::size_t idx) const
{
    return container.get().getFeature(idx);
}

bool Pharm::FeatureContainer::FeatureAccessor::operator==(const FeatureAccessor& accessor) const 
{
    return (container.get_pointer() == accessor.container.get_pointer());
}
