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
# \brief Pharmacophore.
# 
class Pharmacophore(FeatureContainer):

    ##
    # \brief Initializes the \e %Pharmacophore instance.
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
    # \throw Base.IndexError if the number of features is zero or <em>idx</em> is not in the range [0, getNumFeatures() - 1].
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
    # \param cntnr The Pharm.FeatureContainer instance providing the features and properties to copy.
    # 
    def copy(cntnr: FeatureContainer) -> None: pass

    ##
    # \brief Extends the current set of pharmacophore features by a copy of the features in the pharmacophore <em>pharm</em>.
    # 
    # \param pharm The pharmacophore providing the features to append.
    # 
    # \note Does not affect any properties.
    # 
    def append(pharm: Pharmacophore) -> None: pass

    ##
    # \brief Extends the current set of pharmacophore features by a copy of the features in the feature container <em>cntnr</em>.
    # 
    # \param cntnr The Pharm.FeatureContainer instance providing the features to append.
    # 
    # \note Does not affect any properties.
    # 
    def append(cntnr: FeatureContainer) -> None: pass

    ##
    # \brief Removes the pharmacophore features referenced by the feature container <em>cntnr</em> from this <tt>Pharmacophore</tt> instance.
    # 
    # \param cntnr The Pharm.FeatureContainer instance providing the features to remove.
    # 
    # \note Does not affect any properties if <tt>this != &cntr</tt>.
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
    # \param cntnr The Pharm.FeatureContainer instance providing the features and properties to copy.
    # 
    # \return \a self
    # 
    def assign(cntnr: FeatureContainer) -> Pharmacophore: pass

    ##
    # \brief Creates a copy of the current pharmacophore state.
    # 
    # \return A smart reference to the copy of the pharmacophore.
    # 
    def clone() -> Pharmacophore: pass

    ##
    # \brief Returns a reference to the pharmacophore feature at index <em>idx</em>.
    # 
    # \param idx The zero-based index of the feature to return.
    # 
    # \return A reference to the feature at the specified index. 
    # 
    # \throw Base.IndexError if the number of featuress is zero or <em>idx</em> is not in the range [0, getNumFeatures() - 1].
    # 
    def getFeature(idx: int) -> Feature: pass

    ##
    # \brief 
    # \param ftr 
    # \return 
    #
    def containsFeature(ftr: Feature) -> bool: pass

    ##
    # \brief 
    # \param ftr 
    # \return 
    #
    def getFeatureIndex(ftr: Feature) -> int: pass

    ##
    # \brief Returns the number of pharmacophore features.
    # 
    # \return The number of features.
    # 
    def getNumFeatures() -> int: pass

    ##
    # \brief 
    # \param idx 
    # \return 
    #
    def getEntity(idx: int) -> Chem.Entity3D: pass

    ##
    # \brief 
    # \return 
    #
    def getNumEntities() -> int: pass

    ##
    # \brief 
    # \param arg1 
    # \return 
    #
    def __getstate__() -> tuple: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += pharm</tt>.
    # \param pharm Specifies the second addend.
    # \return The updated \e %Pharmacophore instance \a self.
    # 
    def __iadd__(pharm: Pharmacophore) -> Pharmacophore: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += cntnr</tt>.
    # \param cntnr Specifies the second addend.
    # \return The updated \e %Pharmacophore instance \a self.
    # 
    def __iadd__(cntnr: FeatureContainer) -> Pharmacophore: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= cntnr</tt>.
    # \param cntnr Specifies the subtrahend.
    # \return The updated \e %Pharmacophore instance \a self.
    # 
    def __isub__(cntnr: FeatureContainer) -> Pharmacophore: pass

    ##
    # \brief 
    # \param idx 
    #
    def __delitem__(idx: int) -> None: pass

    ##
    # \brief 
    # \param key 
    # \return 
    #
    def __delitem__(key: Base.LookupKey) -> bool: pass

    ##
    # \brief Returns the result of the membership test operation <tt>ftr in self</tt>.
    # \param ftr The value to test for membership.
    # \return The result of the membership test operation.
    # 
    def __contains__(ftr: Feature) -> bool: pass

    ##
    # \brief Returns the result of the membership test operation <tt>key in self</tt>.
    # \param key The value to test for membership.
    # \return The result of the membership test operation.
    # 
    def __contains__(key: Base.LookupKey) -> bool: pass

    ##
    # \brief 
    # \param idx 
    # \return 
    #
    def __getitem__(idx: int) -> Feature: pass

    ##
    # \brief 
    # \param key 
    # \return 
    #
    def __getitem__(key: Base.LookupKey) -> Base.Any: pass

    ##
    # \brief 
    # \return 
    #
    def __len__() -> int: pass

    ##
    # \brief 
    # \param key 
    # \param value 
    #
    def __setitem__(key: Base.LookupKey, value: Base.Any) -> None: pass
