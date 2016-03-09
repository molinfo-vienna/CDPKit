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

#include "CDPL/Chem/Pharmacophore.hpp"
#include "CDPL/Chem/PharmacophoreFeature.hpp"
#include "CDPL/Base/Exceptions.hpp"


using namespace CDPL;


Chem::Pharmacophore::ConstFeatureIterator Chem::Pharmacophore::getFeaturesBegin() const
{
    return ConstFeatureIterator(*this, 0);
}

Chem::Pharmacophore::ConstFeatureIterator Chem::Pharmacophore::getFeaturesEnd() const
{
    return ConstFeatureIterator(*this, getNumFeatures());
}

Chem::Pharmacophore::FeatureIterator Chem::Pharmacophore::getFeaturesBegin()
{
    return FeatureIterator(*this, 0);
}

Chem::Pharmacophore::FeatureIterator Chem::Pharmacophore::getFeaturesEnd()
{
    return FeatureIterator(*this, getNumFeatures());
}

Chem::Pharmacophore::FeatureIterator Chem::Pharmacophore::removeFeature(const FeatureIterator& it)
{
    if (it.getIndex() >= getNumFeatures())
	throw Base::RangeError("Pharmacophore: feature iterator out of valid range");

    removeFeature(it.getIndex());

    return it;
}

Chem::Pharmacophore& Chem::Pharmacophore::operator=(const Pharmacophore& pharm) 
{
    if (this == &pharm)
	return *this;

    copy(pharm);

    return *this;
}

Chem::Pharmacophore& Chem::Pharmacophore::operator+=(const Pharmacophore& pharm) 
{
    append(pharm);

    return *this;
}


const Chem::PharmacophoreFeature& Chem::Pharmacophore::ConstFeatureAccessor::operator()(std::size_t idx) const
{
    return container.get().getFeature(idx);
}

bool Chem::Pharmacophore::ConstFeatureAccessor::operator==(const ConstFeatureAccessor& accessor) const 
{
    return (container.get_pointer() == accessor.container.get_pointer());
}

Chem::Pharmacophore::ConstFeatureAccessor& Chem::Pharmacophore::ConstFeatureAccessor::operator=(const FeatureAccessor& accessor) 
{
    container = boost::reference_wrapper<const Pharmacophore>(accessor.container);
    return *this;
}


Chem::PharmacophoreFeature& Chem::Pharmacophore::FeatureAccessor::operator()(std::size_t idx) const
{
    return container.get().getFeature(idx);
}

bool Chem::Pharmacophore::FeatureAccessor::operator==(const FeatureAccessor& accessor) const 
{
    return (container.get_pointer() == accessor.container.get_pointer());
}
