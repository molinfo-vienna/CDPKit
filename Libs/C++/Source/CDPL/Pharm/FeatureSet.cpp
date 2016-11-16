/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FeatureSet.cpp 
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

#include <algorithm>

#include <boost/bind.hpp>

#include "CDPL/Pharm/FeatureSet.hpp"
#include "CDPL/Pharm/Feature.hpp"
#include "CDPL/Base/Exceptions.hpp"


using namespace CDPL;


Pharm::FeatureSet::FeatureSet() {}

Pharm::FeatureSet::FeatureSet(const FeatureSet& ftr_set): 
    FeatureContainer(ftr_set), features(ftr_set.features),
    featureIndices(ftr_set.featureIndices) 
{}

Pharm::FeatureSet::FeatureSet(const FeatureContainer& cntnr): 
    FeatureContainer(cntnr)
{
    std::for_each(cntnr.getFeaturesBegin(), cntnr.getFeaturesEnd(), 
		  boost::bind(&FeatureSet::addFeature, this, _1));
}

Pharm::FeatureSet::~FeatureSet() {} 

std::size_t Pharm::FeatureSet::getNumFeatures() const
{
    return features.size();
}

std::size_t Pharm::FeatureSet::getFeatureIndex(const Feature& feature) const
{
    FeatureIndexMap::const_iterator it = featureIndices.find(&feature);

    if (it != featureIndices.end())
	return it->second;

    throw Base::ItemNotFound("FeatureSet: argument feature not part of the feature set");
}

bool Pharm::FeatureSet::containsFeature(const Feature& feature) const 
{
    return (featureIndices.find(&feature) != featureIndices.end());
}

Pharm::FeatureSet::ConstFeatureIterator Pharm::FeatureSet::getFeaturesBegin() const 
{
    return features.begin();
}

Pharm::FeatureSet::ConstFeatureIterator Pharm::FeatureSet::getFeaturesEnd() const 
{
    return features.end();
}

Pharm::FeatureSet::FeatureIterator Pharm::FeatureSet::getFeaturesBegin() 
{
    return features.begin();
}

Pharm::FeatureSet::FeatureIterator Pharm::FeatureSet::getFeaturesEnd() 
{
    return features.end();
}

const Pharm::Feature& Pharm::FeatureSet::getFeature(std::size_t idx) const 
{
    if (idx >= features.size())
	throw Base::IndexError("FeatureSet: feature index out of bounds");

    return *features[idx];
}

Pharm::Feature& Pharm::FeatureSet::getFeature(std::size_t idx)
{
    if (idx >= features.size())
	throw Base::IndexError("FeatureSet: feature index out of bounds");

    return *features[idx];
}

bool Pharm::FeatureSet::addFeature(const Feature& feature) 
{
    features.reserve(features.size() + 1);

    if (!featureIndices.insert(FeatureIndexMap::value_type(&feature, features.size())).second)
	return false;

    features.push_back(const_cast<Feature*>(&feature));

    return true;
}

void Pharm::FeatureSet::removeFeature(std::size_t idx) 
{
    std::size_t num_features = features.size();

    if (idx >= num_features)
	throw Base::IndexError("FeatureSet: feature index out of bounds");

    FeatureList::iterator it = features.begin() + idx;

    featureIndices.erase(*it);
	
    it = features.erase(it);
	
    for (num_features--; idx < num_features; idx++, ++it)
	featureIndices[*it] = idx;
}

Pharm::FeatureSet::FeatureIterator Pharm::FeatureSet::removeFeature(const FeatureIterator& it) 
{
    const FeatureList::iterator& base = it.base();

    if (base < features.begin() || base >= features.end())
	throw Base::RangeError("FeatureSet: feature iterator out of valid range");

    const Feature* feature = *base;

    featureIndices.erase(feature);

    FeatureList::iterator rit = features.erase(base);
		
    for (std::size_t num_features = features.size(), i = rit - features.begin(); i < num_features; i++)
	featureIndices[features[i]] = i;

    return rit;
}

bool Pharm::FeatureSet::removeFeature(const Feature& feature) 
{
    FeatureIndexMap::iterator idx_it = featureIndices.find(&feature);

    if (idx_it == featureIndices.end())
	return false;

    std::size_t idx = idx_it->second;

    FeatureList::iterator it = features.begin() + idx;

    featureIndices.erase(idx_it);
	
    it = features.erase(it);
	
    for (std::size_t num_features = features.size(); idx < num_features; idx++, ++it)
	featureIndices[*it] = idx;

    return true;
}

void Pharm::FeatureSet::clear()
{
    clearProperties();

    features.clear();
    featureIndices.clear();
}

Pharm::FeatureSet& Pharm::FeatureSet::operator=(const FeatureSet& ftr_set)
{
    if (this == &ftr_set)
	return *this;

    featureIndices = ftr_set.featureIndices;
    features = ftr_set.features;

    copyProperties(ftr_set);

    return *this;
}

Pharm::FeatureSet& Pharm::FeatureSet::operator=(const FeatureContainer& cntnr)
{
    features.clear();
    featureIndices.clear();

    std::for_each(cntnr.getFeaturesBegin(), cntnr.getFeaturesEnd(), 
		  boost::bind(&FeatureSet::addFeature, this, _1));

    copyProperties(cntnr);

    return *this;
}

Pharm::FeatureSet& Pharm::FeatureSet::operator+=(const FeatureContainer& cntnr)
{
    features.reserve(features.size() + cntnr.getNumFeatures());

    std::for_each(cntnr.getFeaturesBegin(), cntnr.getFeaturesEnd(), 
		  boost::bind(&FeatureSet::addFeature, this, _1));

    return *this;
}
