/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * BasicPharmacophore.cpp 
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

#include <cassert>

#include <boost/bind.hpp>

#include "CDPL/Chem/BasicPharmacophore.hpp"
#include "CDPL/Base/Exceptions.hpp"


using namespace CDPL;


Chem::BasicPharmacophore::BasicPharmacophore() {}

Chem::BasicPharmacophore::BasicPharmacophore(const BasicPharmacophore& pharm): Pharmacophore(pharm)
{
    append(pharm);
}

Chem::BasicPharmacophore::BasicPharmacophore(const Pharmacophore& pharm): Pharmacophore(pharm)
{
    append(pharm);
}

Chem::BasicPharmacophore::~BasicPharmacophore() {}

void Chem::BasicPharmacophore::clear()
{
    clearFeatures();
    clearProperties();
}

std::size_t Chem::BasicPharmacophore::getNumFeatures() const
{
    return features.size();
}

Chem::BasicPharmacophore::ConstFeatureIterator Chem::BasicPharmacophore::getFeaturesBegin() const
{
    return features.begin();
}

Chem::BasicPharmacophore::ConstFeatureIterator Chem::BasicPharmacophore::getFeaturesEnd() const
{
    return features.end();
}

Chem::BasicPharmacophore::FeatureIterator Chem::BasicPharmacophore::getFeaturesBegin() 
{
    return features.begin();
}

Chem::BasicPharmacophore::FeatureIterator Chem::BasicPharmacophore::getFeaturesEnd() 
{
    return features.end();
}

const Chem::BasicFeature& Chem::BasicPharmacophore::getFeature(std::size_t idx) const
{
    if (idx >= features.size())
		throw Base::IndexError("BasicPharmacophore: feature index out of bounds");

    return *features[idx];
}

Chem::BasicFeature& Chem::BasicPharmacophore::getFeature(std::size_t idx)
{
    if (idx >= features.size())
		throw Base::IndexError("BasicPharmacophore: feature index out of bounds");

    return *features[idx];
}

Chem::BasicFeature& Chem::BasicPharmacophore::addFeature()
{
    features.reserve(features.size() + 1);
    allocFeatures.reserve(allocFeatures.size() + 1);

    BasicFeature* feature = allocFeature();

    feature->setIndex(features.size());

    features.push_back(feature);

    return *feature;
}

void Chem::BasicPharmacophore::removeFeature(std::size_t idx)
{
    if (idx >= features.size())
		throw Base::IndexError("BasicPharmacophore: feature index out of bounds");

    BasicFeature* feature = features[idx];

    freeFeatures.reserve(freeFeatures.size() + 1);

    freeFeature(feature);

    features.erase(features.begin() + idx);

    renumberFeatures(idx);
}

Chem::BasicPharmacophore::FeatureIterator Chem::BasicPharmacophore::removeFeature(const FeatureIterator& it)
{
    const FeaturePtrList::iterator& base = it.base();

    if (base < features.begin() || base >= features.end())
		throw Base::RangeError("BasicPharmacophore: feature iterator out of valid range");

    BasicFeature* feature = *base;

    freeFeatures.reserve(freeFeatures.size() + 1);

    freeFeature(feature);

    FeaturePtrList::iterator rit = features.erase(base);

    renumberFeatures(rit - features.begin());

    return rit;
}

bool Chem::BasicPharmacophore::containsFeature(const Feature& feature) const
{
    if (this != &feature.getPharmacophore())
		return false;

    return (feature.getIndex() < features.size());
}

std::size_t Chem::BasicPharmacophore::getFeatureIndex(const Feature& feature) const
{
    if (this != &feature.getPharmacophore() || feature.getIndex() >= features.size())
		throw Base::ItemNotFound("BasicPharmacophore: argument feature not part of the pharmacophore");

    return feature.getIndex();
}

Chem::Pharmacophore::SharedPointer Chem::BasicPharmacophore::clone() const
{
    return Pharmacophore::SharedPointer(new BasicPharmacophore(*this));
}

Chem::BasicPharmacophore& Chem::BasicPharmacophore::operator=(const BasicPharmacophore& pharm)
{
    if (this == &pharm)
		return *this;

    copy(pharm);

    return *this;
}

Chem::BasicPharmacophore& Chem::BasicPharmacophore::operator+=(const BasicPharmacophore& pharm)
{
    append(pharm);

    return *this;
}

void Chem::BasicPharmacophore::copy(const BasicPharmacophore& pharm)
{
    if (this == &pharm)
		return;

    clearFeatures();
    copyProperties(pharm);

    if (pharm.features.size() == 0)
		return;

    features.reserve(pharm.features.size());
    allocFeatures.reserve(pharm.features.size());
	
    FeaturePtrList::const_iterator pharm_features_end = pharm.features.end();

    for (FeaturePtrList::const_iterator it = pharm.features.begin(); it != pharm_features_end; ++it) {
		const BasicFeature* feature = *it;

		addFeature().copyProperties(*feature); 
    }
}

void Chem::BasicPharmacophore::copy(const Pharmacophore& pharm)
{   
    if (this == &pharm)
		return;

    doCopy(pharm);
    copyProperties(pharm);
}

template <typename T>
void Chem::BasicPharmacophore::doCopy(const T& pharm)
{   
    clearFeatures();

    if (pharm.getNumFeatures() == 0)
		return;

    features.reserve(pharm.getNumFeatures());
    allocFeatures.reserve(pharm.getNumFeatures());

    typename T::ConstFeatureIterator pharm_features_end = pharm.getFeaturesEnd();

    for (typename T::ConstFeatureIterator it = pharm.getFeaturesBegin(); it != pharm_features_end; ++it) { 
		const Feature& feature = *it;

		addFeature().copyProperties(feature);
    }
}

void Chem::BasicPharmacophore::append(const BasicPharmacophore& pharm)
{
    std::size_t pharm_num_features = pharm.features.size();

    if (pharm_num_features == 0)
		return;

    std::size_t old_num_features = features.size();

    features.reserve(old_num_features + pharm_num_features);
    allocFeatures.reserve(allocFeatures.size() + pharm_num_features);

    FeaturePtrList::const_iterator pharm_features_end = pharm.features.end();

    for (FeaturePtrList::const_iterator it = pharm.features.begin(); it != pharm_features_end; ++it) {
		const BasicFeature* feature = *it;

		addFeature().copyProperties(*feature); 
    }
}

void Chem::BasicPharmacophore::append(const Pharmacophore& pharm)
{   
    doAppend(pharm);
}

template <typename T>
void Chem::BasicPharmacophore::doAppend(const T& pharm)
{   
    std::size_t pharm_num_features = pharm.getNumFeatures();

    if (pharm_num_features == 0)
		return;

    std::size_t old_num_features = features.size();

    features.reserve(old_num_features + pharm_num_features);
    allocFeatures.reserve(allocFeatures.size() + pharm_num_features);

    typename T::ConstFeatureIterator pharm_features_end = pharm.getFeaturesEnd();

    for (typename T::ConstFeatureIterator it = pharm.getFeaturesBegin(); it != pharm_features_end; ++it) {
		const Feature& feature = *it;
	
		addFeature().copyProperties(feature);
    }
}

void Chem::BasicPharmacophore::clearFeatures()
{
    freeFeatures.reserve(freeFeatures.size() + features.size());

    std::for_each(features.begin(), features.end(), boost::bind(&BasicPharmacophore::freeFeature, this, _1));

    features.clear();
}
		
void Chem::BasicPharmacophore::renumberFeatures(std::size_t idx)
{
    assert(idx <= features.size());

    FeaturePtrList::iterator features_end = features.end();

    for (FeaturePtrList::iterator it = features.begin() + idx; it != features_end; ++it, idx++)
		(*it)->setIndex(idx);
}

void Chem::BasicPharmacophore::destroyFeature(BasicFeature* feature)
{
    delete feature;
}

Chem::BasicFeature* Chem::BasicPharmacophore::allocFeature()
{
    if (freeFeatures.empty()) {
		SharedFeaturePointer feature_ptr(new BasicFeature(this), &BasicPharmacophore::destroyFeature);
		allocFeatures.push_back(feature_ptr);

		return feature_ptr.get();
    }

    BasicFeature* feature = freeFeatures.back();

    feature->clearProperties();

    freeFeatures.pop_back();

    return feature;
}

void Chem::BasicPharmacophore::freeFeature(BasicFeature* feature)
{
    assert(feature != 0);

    freeFeatures.push_back(feature);

    feature->setIndex(features.max_size());
}
