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
# \brief FeatureSet.
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
    # \param cntnr The Pharm.FeatureContainer instance providing the features and properties to store.
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
    # \param cntnr The Pharm.FeatureContainer instance providing the features and properties to copy.
    # 
    # \return \a self
    # 
    def assign(cntnr: FeatureContainer) -> FeatureSet: pass

    ##
    # \brief Extends the feature set by the specified feature.
    # 
    # \param ftr The feature to add.
    # 
    # \return <tt>True</tt> if the feature was not already a part of the feature set, and <tt>False</tt> otherwise.
    # 
    def addFeature(ftr: Feature) -> bool: pass

    ##
    # \brief Removes the feature at the specified index.
    # 
    # \param idx The zero-based index of the feature to remove.
    # 
    # \throw Base.IndexError if the number of features is zero or <em>idx</em> is not in the range [0, getNumFeatures() - 1].
    # 
    def removeFeature(idx: int) -> None: pass

    ##
    # \brief Removes the specified feature.
    # 
    # \param ftr The feature to remove.
    # 
    # \return <tt>True</tt> if the feature was part of the feature set and has been removed, and <tt>False</tt> otherwise.
    # 
    def removeFeature(ftr: Feature) -> bool: pass

    ##
    # \brief Removes all features and properties.
    # 
    def clear() -> None: pass

    ##
    # \brief 
    # \param key 
    # \return 
    #
    def __getitem__(key: CDPL.Base.LookupKey) -> CDPL.Base.Any: pass

    ##
    # \brief 
    # \param idx 
    # \return 
    #
    def __getitem__(idx: int) -> Feature: pass

    ##
    # \brief Returns the result of the membership test operation <tt>key in self</tt>.
    # \param self The \e %FeatureSet instance this method is called upon.
    # \param key The value to test for membership.
    # \return The result of the membership test operation.
    # 
    def __contains__(key: CDPL.Base.LookupKey) -> bool: pass

    ##
    # \brief Returns the result of the membership test operation <tt>ftr in self</tt>.
    # \param self The \e %FeatureSet instance this method is called upon.
    # \param ftr The value to test for membership.
    # \return The result of the membership test operation.
    # 
    def __contains__(ftr: Feature) -> bool: pass

    ##
    # \brief 
    # \param key 
    # \param value 
    #
    def __setitem__(key: CDPL.Base.LookupKey, value: CDPL.Base.Any) -> None: pass

    ##
    # \brief 
    # \param key 
    # \return 
    #
    def __delitem__(key: CDPL.Base.LookupKey) -> bool: pass

    ##
    # \brief 
    # \return 
    #
    def __len__() -> int: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += cntnr</tt>.
    # \param self The \e %FeatureSet instance acting as in-place addend.
    # \param cntnr Specifies the second addend.
    # \return The updated \e %FeatureSet instance \a self.
    # 
    def __iadd__(cntnr: FeatureContainer) -> FeatureSet: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= cntnr</tt>.
    # \param self The \e %FeatureSet instance acting as in-place minuend.
    # \param cntnr Specifies the subtrahend.
    # \return The updated \e %FeatureSet instance \a self.
    # 
    def __isub__(cntnr: FeatureContainer) -> FeatureSet: pass
