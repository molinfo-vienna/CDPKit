#
# This file is part of the Chemical Data Processing Toolkit
#
# Copyright (C) Thomas Seidel <thomas.seidel@univie.ac.at>
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2 of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program; see the file COPYING. If not, write to
# the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
# Boston, MA 02111-1307, USA.
#

##
# \brief Common interface for data structures that support a random access to stored Pharm.Feature instances.
# 
# Implementations have to guarantee that a given Pharm.Feature object is stored only once and its index is unique amongst all contained Pharm.Feature instances. Otherwise algorithms that rely on this behaviour may not work correctly!
# 
class FeatureContainer(Chem.Entity3DContainer, Base.PropertyContainer):

    ##
    # \brief Initializes the \c %FeatureContainer instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Returns a reference to the feature at index <em>idx</em>.
    # 
    # \param idx The zero-based index of the feature to return.
    # 
    # \return A reference to the feature at the specified index. 
    # 
    # \throw Base.IndexError if <em>idx</em> is not in the range [0, getNumFeatures()).
    # 
    def getFeature(idx: int) -> Feature: pass

    ##
    # \brief Tells whether the specified feature is part of the feature set.
    # 
    # \param feature The feature to look for.
    # 
    # \return <tt>True</tt> if <em>feature</em> is part of the set, and <tt>False</tt> otherwise.
    # 
    def containsFeature(feature: Feature) -> bool: pass

    ##
    # \brief Returns the index of the specified feature.
    # 
    # \param feature The feature for which to return the index.
    # 
    # \return The zero-based index of the specified feature. 
    # 
    # \throw Base.ItemNotFound if the specified feature could not be found.
    # 
    def getFeatureIndex(feature: Feature) -> int: pass

    ##
    # \brief Returns the number of features.
    # 
    # \return The number of features.
    # 
    def getNumFeatures() -> int: pass

    ##
    # \brief Orders the features according to criteria implemented by the provided feature comparison function.
    # 
    # \param func The feature comparison function implementing the applied ordering criteria.
    # 
    def orderFeatures(func: BoolFeature2Functor) -> None: pass

    ##
    # \brief Returns a reference to the entity at index <em>idx</em>.
    # 
    # Forwards to getFeature() and exists to satisfy the Chem.Entity3DContainer interface.
    # 
    # \param idx The zero-based entity index.
    # 
    # \return A reference to the entity at the specified index. 
    # 
    # \throw Base.IndexError if <em>idx</em> is not in the range [0, getNumFeatures()).
    # 
    def getEntity(idx: int) -> Chem.Entity3D: pass

    ##
    # \brief Returns the number of entities.
    # 
    # Forwards to getNumFeatures() and exists to satisfy the Chem.Entity3DContainer interface.
    # 
    # \return The number of contained features.
    # 
    def getNumEntities() -> int: pass

    def __getitem__(key: Base.LookupKey) -> Base.Any: pass

    def __getitem__(idx: int) -> Feature: pass

    ##
    # \brief Returns the result of the membership test operation <tt>key in self</tt>.
    # \param key The value to test for membership.
    # \return The result of the membership test operation.
    # 
    def __contains__(key: Base.LookupKey) -> bool: pass

    ##
    # \brief Returns the result of the membership test operation <tt>feature in self</tt>.
    # \param feature The value to test for membership.
    # \return The result of the membership test operation.
    # 
    def __contains__(feature: Feature) -> bool: pass

    def __setitem__(key: Base.LookupKey, value: Base.Any) -> None: pass

    def __delitem__(key: Base.LookupKey) -> bool: pass

    def __len__() -> int: pass

    numFeatures = property(getNumFeatures)
