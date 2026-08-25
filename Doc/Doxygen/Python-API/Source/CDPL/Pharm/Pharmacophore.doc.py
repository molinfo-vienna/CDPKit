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
# \brief Abstract base class for mutable containers of Pharm.Feature instances representing a pharmacophore model.
# 
# <tt>Pharmacophore</tt> extends the read-only Pharm.FeatureContainer interface with feature creation/removal, content replacement (copy, append, remove) and a cloning facility for polymorphic deep copies.
# 
class Pharmacophore(FeatureContainer):

    ##
    # \brief Initializes the \c %Pharmacophore instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Removes all features and clears all properties of the pharmacophore.
    # 
    def clear() -> None: pass

    ##
    # \brief Creates a new pharmacophore feature and adds it to the pharmacophore.
    # 
    # \return A reference to the newly created features.
    # 
    def addFeature() -> Feature: pass

    ##
    # \brief Removes the pharmacophore feature at the specified index.
    # 
    # \param idx The index of the feature to remove.
    # 
    # \throw Base.IndexError if <em>idx</em> is not in the range [0, getNumFeatures()).
    # 
    def removeFeature(idx: int) -> None: pass

    ##
    # \brief Replaces the current set of pharmacophore features and properties by a copy of the features and properties of the pharmacophore <em>pharm</em>.
    # 
    # \param pharm The pharmacophore to copy.
    # 
    def copy(pharm: Pharmacophore) -> None: pass

    ##
    # \brief Replaces the current set of pharmacophore features and properties by a copy of the features and properties of the feature container <em>cntnr</em>.
    # 
    # \param cntnr The feature container providing the features and properties to copy.
    # 
    def copy(cntnr: FeatureContainer) -> None: pass

    ##
    # \brief Extends the current set of features by a copy of the features in the pharmacophore <em>pharm</em>.
    # 
    # \param pharm The pharmacophore providing the features to append.
    # 
    # \note Does not affect any properties.
    # 
    def append(pharm: Pharmacophore) -> None: pass

    ##
    # \brief Extends the current set of pharmacophore features by a copy of the features in the feature container <em>cntnr</em>.
    # 
    # \param cntnr The feature container providing the features to append.
    # 
    # \note Does not affect any properties.
    # 
    def append(cntnr: FeatureContainer) -> None: pass

    ##
    # \brief Removes the pharmacophore features referenced by the feature container <em>cntnr</em> from this instance.
    # 
    # \param cntnr The feature container providing the features to remove.
    # 
    # \note Equivalent to clear() if <tt>this == &cntr</tt>.
    # 
    def remove(cntnr: FeatureContainer) -> None: pass

    ##
    # \brief Replaces the current set of pharmacophore features and properties by a copy of the features and properties of the pharmacophore <em>pharm</em>.
    # 
    # Internally calls copy() to perform the actual work.
    # 
    # \param pharm The pharmacophore to copy.
    # 
    # \return \a self
    # 
    def assign(pharm: Pharmacophore) -> Pharmacophore: pass

    ##
    # \brief Replaces the current set of pharmacophore features and properties by a copy of the features and properties of the feature container <em>cntnr</em>.
    # 
    # Internally calls copy() to perform the actual work.
    # 
    # \param cntnr The feature container providing the features and properties to copy.
    # 
    # \return \a self
    # 
    def assign(cntnr: FeatureContainer) -> Pharmacophore: pass

    ##
    # \brief Creates a deep copy of the current pharmacophore state.
    # 
    # \return A smart reference to the copy of the pharmacophore.
    # 
    def clone() -> Pharmacophore: pass

    def getFeature(idx: int) -> Feature: pass

    def containsFeature(feature: Feature) -> bool: pass

    def getFeatureIndex(feature: Feature) -> int: pass

    def getNumFeatures() -> int: pass

    def orderFeatures(func: BoolFeature2Functor) -> None: pass

    def getEntity(idx: int) -> Chem.Entity3D: pass

    def getNumEntities() -> int: pass

    def __getstate__() -> tuple: pass

    ##
    # \brief Extends the current set of pharmacophore features by a copy of the features in the pharmacophore <em>pharm</em>.
    # 
    # Internally calls append() to perform the actual work.
    # 
    # \param pharm The pharmacophore providing the features to append.
    # 
    # \return \a self
    # 
    def __iadd__(pharm: Pharmacophore) -> Pharmacophore: pass

    ##
    # \brief Extends the current set of pharmacophore features by a copy of the features in the feature container <em>cntnr</em>.
    # 
    # Internally calls append() to perform the actual work.
    # 
    # \param cntnr The feature container providing the features to append.
    # 
    # \return \a self
    # 
    def __iadd__(cntnr: FeatureContainer) -> Pharmacophore: pass

    ##
    # \brief Removes the pharmacophore features referenced by the feature container <em>cntnr</em> from this <tt>Pharmacophore</tt> instance.
    # 
    # Internally calls remove() to perform the actual work.
    # 
    # \param cntnr The feature container providing the features to remove.
    # 
    # \return \a self
    # 
    def __isub__(cntnr: FeatureContainer) -> Pharmacophore: pass

    def __delitem__(idx: int) -> None: pass

    def __delitem__(key: Base.LookupKey) -> bool: pass

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

    def __len__() -> int: pass
