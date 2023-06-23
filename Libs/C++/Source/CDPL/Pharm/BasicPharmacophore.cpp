/* 
 * BasicPharmacophore.cpp 
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

#include <cassert>
#include <functional>

#include "CDPL/Pharm/BasicPharmacophore.hpp"
#include "CDPL/Base/Exceptions.hpp"


namespace
{

	const std::size_t MAX_FEATURE_CACHE_SIZE = 1000;
}


using namespace CDPL;


Pharm::BasicPharmacophore::BasicPharmacophore(): 
	featureCache(std::bind(&BasicPharmacophore::createFeature, this), &destroyFeature, MAX_FEATURE_CACHE_SIZE)
{
	featureCache.setCleanupFunction(&BasicPharmacophore::clearFeature);
}

Pharm::BasicPharmacophore::BasicPharmacophore(const BasicPharmacophore& pharm): 
	Pharmacophore(pharm), 
	featureCache(std::bind(&BasicPharmacophore::createFeature, this), &destroyFeature, MAX_FEATURE_CACHE_SIZE)
{
	featureCache.setCleanupFunction(&BasicPharmacophore::clearFeature);

    append(pharm);
}

Pharm::BasicPharmacophore::BasicPharmacophore(const Pharmacophore& pharm): 
	Pharmacophore(pharm),
	featureCache(std::bind(&BasicPharmacophore::createFeature, this), &destroyFeature, MAX_FEATURE_CACHE_SIZE)
{
	featureCache.setCleanupFunction(&BasicPharmacophore::clearFeature);

    append(pharm);
}

Pharm::BasicPharmacophore::BasicPharmacophore(const FeatureContainer& cntnr):
	featureCache(std::bind(&BasicPharmacophore::createFeature, this), &destroyFeature, MAX_FEATURE_CACHE_SIZE)
{
	featureCache.setCleanupFunction(&BasicPharmacophore::clearFeature);

    append(cntnr);
	copyProperties(cntnr);
}

Pharm::BasicPharmacophore::~BasicPharmacophore() {}

void Pharm::BasicPharmacophore::clear()
{
    clearFeatures();
    clearProperties();
}

std::size_t Pharm::BasicPharmacophore::getNumFeatures() const
{
    return features.size();
}

Pharm::BasicPharmacophore::ConstFeatureIterator Pharm::BasicPharmacophore::getFeaturesBegin() const
{
    return features.begin();
}

Pharm::BasicPharmacophore::ConstFeatureIterator Pharm::BasicPharmacophore::getFeaturesEnd() const
{
    return features.end();
}

Pharm::BasicPharmacophore::FeatureIterator Pharm::BasicPharmacophore::getFeaturesBegin() 
{
    return features.begin();
}

Pharm::BasicPharmacophore::FeatureIterator Pharm::BasicPharmacophore::getFeaturesEnd() 
{
    return features.end();
}

const Pharm::BasicFeature& Pharm::BasicPharmacophore::getFeature(std::size_t idx) const
{
    if (idx >= features.size())
		throw Base::IndexError("BasicPharmacophore: feature index out of bounds");

    return *features[idx];
}

Pharm::BasicFeature& Pharm::BasicPharmacophore::getFeature(std::size_t idx)
{
    if (idx >= features.size())
		throw Base::IndexError("BasicPharmacophore: feature index out of bounds");

    return *features[idx];
}

Pharm::BasicFeature& Pharm::BasicPharmacophore::addFeature()
{
	FeaturePointer feature = featureCache.get();

    feature->setIndex(features.size());

    features.push_back(feature);

    return *feature;
}

void Pharm::BasicPharmacophore::removeFeature(std::size_t idx)
{
    if (idx >= features.size())
		throw Base::IndexError("BasicPharmacophore: feature index out of bounds");

    features.erase(features.begin() + idx);

    renumberFeatures(idx);
}

Pharm::BasicPharmacophore::FeatureIterator Pharm::BasicPharmacophore::removeFeature(const FeatureIterator& it)
{
    const FeatureList::iterator& base = it.base();

    if (base < features.begin() || base >= features.end())
		throw Base::RangeError("BasicPharmacophore: feature iterator out of valid range");

    FeatureList::iterator rit = features.erase(base);

    renumberFeatures(rit - features.begin());

    return rit;
}

bool Pharm::BasicPharmacophore::containsFeature(const Feature& feature) const
{
    if (this != &feature.getPharmacophore())
		return false;

    return (feature.getIndex() < features.size());
}

std::size_t Pharm::BasicPharmacophore::getFeatureIndex(const Feature& feature) const
{
    if (this != &feature.getPharmacophore() || feature.getIndex() >= features.size())
		throw Base::ItemNotFound("BasicPharmacophore: argument feature not part of the pharmacophore");

    return feature.getIndex();
}

Pharm::Pharmacophore::SharedPointer Pharm::BasicPharmacophore::clone() const
{
    return Pharmacophore::SharedPointer(new BasicPharmacophore(*this));
}

Pharm::BasicPharmacophore& Pharm::BasicPharmacophore::operator=(const BasicPharmacophore& pharm)
{
    if (this == &pharm)
		return *this;

    copy(pharm);

    return *this;
}

Pharm::BasicPharmacophore& Pharm::BasicPharmacophore::operator+=(const BasicPharmacophore& pharm)
{
    append(pharm);

    return *this;
}

void Pharm::BasicPharmacophore::copy(const BasicPharmacophore& pharm)
{
    if (this == &pharm)
		return;

    clearFeatures();
    copyProperties(pharm);

    if (pharm.features.size() == 0)
		return;

    features.reserve(pharm.features.size());
	
    FeatureList::const_iterator pharm_features_end = pharm.features.end();

    for (FeatureList::const_iterator it = pharm.features.begin(); it != pharm_features_end; ++it) 
		addFeature().copyProperties(**it); 
}

void Pharm::BasicPharmacophore::copy(const Pharmacophore& pharm)
{   
    if (this == &pharm)
		return;

    doCopy(pharm);
    copyProperties(pharm);
}

void Pharm::BasicPharmacophore::copy(const FeatureContainer& cntnr)
{   
    if (this == &cntnr)
		return;

    doCopy(cntnr);
    copyProperties(cntnr);
}

template <typename T>
void Pharm::BasicPharmacophore::doCopy(const T& pharm)
{   
    clearFeatures();

    if (pharm.getNumFeatures() == 0)
		return;

    features.reserve(pharm.getNumFeatures());
 
    typename T::ConstFeatureIterator pharm_features_end = pharm.getFeaturesEnd();

    for (typename T::ConstFeatureIterator it = pharm.getFeaturesBegin(); it != pharm_features_end; ++it)  
		addFeature().copyProperties(*it);
}

void Pharm::BasicPharmacophore::append(const BasicPharmacophore& pharm)
{
    std::size_t pharm_num_features = pharm.features.size();

    if (pharm_num_features == 0)
		return;

    features.reserve(features.size() + pharm_num_features);
 
    FeatureList::const_iterator pharm_features_end = pharm.features.end();

    for (FeatureList::const_iterator it = pharm.features.begin(); it != pharm_features_end; ++it) 
		addFeature().copyProperties(**it); 
}

void Pharm::BasicPharmacophore::append(const Pharmacophore& pharm)
{   
    doAppend(pharm);
}

void Pharm::BasicPharmacophore::append(const FeatureContainer& cntnr)
{   
    doAppend(cntnr);
}

void Pharm::BasicPharmacophore::remove(const FeatureContainer& cntnr)
{   
	if (this == &cntnr) {
		clear();
		return;
	}

	for (FeatureContainer::ConstFeatureIterator it = cntnr.getFeaturesBegin(), end = cntnr.getFeaturesEnd(); it != end; ++it) {
		const Feature& feature = *it;

		if (!containsFeature(feature))
			continue;

		removeFeature(feature.getIndex());
	}
}

template <typename T>
void Pharm::BasicPharmacophore::doAppend(const T& pharm)
{   
    std::size_t pharm_num_features = pharm.getNumFeatures();

    if (pharm_num_features == 0)
		return;

    features.reserve(features.size() + pharm_num_features);
 
    typename T::ConstFeatureIterator pharm_features_end = pharm.getFeaturesEnd();

    for (typename T::ConstFeatureIterator it = pharm.getFeaturesBegin(); it != pharm_features_end; ++it) 
		addFeature().copyProperties(*it);
}

void Pharm::BasicPharmacophore::clearFeatures()
{
    features.clear();
}
		
void Pharm::BasicPharmacophore::renumberFeatures(std::size_t idx)
{
    assert(idx <= features.size());

    FeatureList::iterator features_end = features.end();

    for (FeatureList::iterator it = features.begin() + idx; it != features_end; ++it, idx++)
		(*it)->setIndex(idx);
}

Pharm::BasicFeature* Pharm::BasicPharmacophore::createFeature()
{
    return new BasicFeature(this);
}

void Pharm::BasicPharmacophore::destroyFeature(BasicFeature* feature)
{
    delete feature;
}

void Pharm::BasicPharmacophore::clearFeature(BasicFeature& feature)
{
	feature.clearProperties();
	feature.setIndex(~std::size_t(0));
}
