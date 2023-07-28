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
# \brief FeatureContainer.
# 
class FeatureContainer(CDPL.Chem.Entity3DContainer, CDPL.Base.PropertyContainer):

    ##
    # \brief Initializes the \e %FeatureContainer instance.
    # \param self The \e %FeatureContainer instance to initialize.
    # 
    def __init__() -> None: pass

    ##
    # \brief Returns a reference to the pharmacophore feature at index <em>idx</em>.
    # 
    # \param idx The zero-based index of the feature to return.
    # 
    # \return A reference to the feature at the specified index. 
    # 
    # \throw Base.IndexError if the number of features is zero or <em>idx</em> is not in the range [0, getNumFeatures() - 1].
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
    # \brief Returns the number of contained features.
    # 
    # \return The number of features.
    # 
    def getNumFeatures() -> int: pass

    ##
    # \brief Returns a reference to the entity at index <em>idx</em>.
    # 
    # \param idx The zero-based index of the Chem.Entity3D instance to return.
    # 
    # \return A reference to the entity at the specified index. 
    # 
    # \throw Base.IndexError if the number of entities is zero or <em>idx</em> is not in the range [0, getNumEntities() - 1].
    # 
    def getEntity(idx: int) -> CDPL.Chem.Entity3D: pass

    ##
    # \brief Returns the number of stored Chem.Entity3D objects.
    # 
    # \return The number of stored Chem.Entity3D objects.
    # 
    def getNumEntities() -> int: pass

    ##
    # \brief Returns the result of the membership test operation <tt>ftr in self</tt>.
    # \param self The \e %FeatureContainer instance this method is called upon.
    # \param ftr The value to test for membership.
    # \return The result of the membership test operation.
    # 
    def __contains__(ftr: Feature) -> bool: pass

    ##
    # \brief Returns the result of the membership test operation <tt>key in self</tt>.
    # \param self The \e %FeatureContainer instance this method is called upon.
    # \param key The value to test for membership.
    # \return The result of the membership test operation.
    # 
    def __contains__(key: CDPL.Base.LookupKey) -> bool: pass

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
    def __getitem__(key: CDPL.Base.LookupKey) -> CDPL.Base.Any: pass

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
    def __setitem__(key: CDPL.Base.LookupKey, value: CDPL.Base.Any) -> None: pass

    ##
    # \brief 
    # \param key 
    # \return 
    #
    def __delitem__(key: CDPL.Base.LookupKey) -> bool: pass

    numFeatures = property(getNumFeatures)
