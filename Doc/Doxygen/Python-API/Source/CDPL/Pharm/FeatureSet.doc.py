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
# \brief Concrete implementation of the Pharm.FeatureContainer interface that stores references to selectable Pharm.Feature instances.
# 
# Unlike a Pharm.Pharmacophore instance, a <tt>FeatureSet</tt> object does not own its features. It is typically used to represent subsets/selections of features that live elsewhere.
# 
# \note Since <tt>FeatureSet</tt> does not own the stored features they must outlive any <tt>FeatureSet</tt> instance that references them!
# 
class FeatureSet(FeatureContainer):

    ##
    # \brief Constructs an empty <tt>FeatureSet</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Constructs a copy of the <tt>FeatureSet</tt> instance <em>ftr_set</em>.
    # 
    # \param ftr_set The other <tt>FeatureSet</tt> instance to copy.
    # 
    def __init__(ftr_set: FeatureSet) -> None: pass

    ##
    # \brief Constructs a <tt>FeatureSet</tt> instance storing the features and properties of the feature container <em>cntnr</em>.
    # 
    # \param cntnr The feature container providing the features and properties to store.
    # 
    def __init__(cntnr: FeatureContainer) -> None: pass

    ##
    # \brief Replaces the current set of features and properties by the features and properties of the feature set <em>ftr_set</em>.
    # 
    # \param ftr_set The feature set to copy.
    # 
    # \return \a self
    # 
    def assign(ftr_set: FeatureSet) -> FeatureSet: pass

    ##
    # \brief Replaces the current set of features and properties by the features and properties of the feature container <em>cntnr</em>.
    # 
    # \param cntnr The feature container providing the features and properties to copy.
    # 
    # \return \a self
    # 
    def assign(cntnr: FeatureContainer) -> FeatureSet: pass

    ##
    # \brief Extends the feature set by the specified feature.
    # 
    # \param feature The feature to add.
    # 
    # \return <tt>True</tt> if the feature was not already a part of the feature set, and <tt>False</tt> otherwise.
    # 
    def addFeature(feature: Feature) -> bool: pass

    ##
    # \brief Removes the feature at the specified index.
    # 
    # \param idx The zero-based index of the feature to remove.
    # 
    # \throw Base.IndexError if <em>idx</em> is not in the range [0, getNumFeatures()).
    # 
    def removeFeature(idx: int) -> None: pass

    ##
    # \brief Removes the specified feature.
    # 
    # \param feature The feature to remove.
    # 
    # \return <tt>True</tt> if the feature was part of the feature set and has been removed, and <tt>False</tt> otherwise.
    # 
    def removeFeature(feature: Feature) -> bool: pass

    ##
    # \brief Removes all features and properties.
    # 
    def clear() -> None: pass

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

    ##
    # \brief Extends the current set of features by the features in the feature container <em>cntnr</em>.
    # 
    # \param cntnr The feature container providing the features to append.
    # 
    # \return \a self 
    # 
    # \note Does not affect any properties.
    # 
    def __iadd__(cntnr: FeatureContainer) -> FeatureSet: pass

    ##
    # \brief Removes the pharmacophore features referenced by the feature container <em>cntnr</em> from this <tt>FeatureSet</tt> instance.
    # 
    # \param cntnr The feature container providing the features to remove.
    # 
    # \return \a self 
    # 
    # \note Equivalent to clear() if <tt>this == &cntr</tt>.
    # 
    def __isub__(cntnr: FeatureContainer) -> FeatureSet: pass
