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
# \brief 
#
class FeatureSet(FeatureContainer):

    ##
    # \brief Initializes the \e %FeatureSet instance.
    #
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %FeatureSet instance.
    # \param ftr_set 
    #
    def __init__(ftr_set: FeatureSet) -> None: pass

    ##
    # \brief Initializes the \e %FeatureSet instance.
    # \param cntnr 
    #
    def __init__(cntnr: FeatureContainer) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %FeatureSet instance \a ftr_set.
    # \param ftr_set The \e %FeatureSet instance to copy.
    # \return \a self
    #
    def assign(ftr_set: FeatureSet) -> FeatureSet: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %FeatureContainer instance \a cntnr.
    # \param cntnr The \e %FeatureContainer instance to copy.
    # \return \a self
    #
    def assign(cntnr: FeatureContainer) -> FeatureSet: pass

    ##
    # \brief 
    # \param ftr 
    # \return 
    #
    def addFeature(ftr: Feature) -> bool: pass

    ##
    # \brief 
    # \param idx 
    #
    def removeFeature(idx: int) -> None: pass

    ##
    # \brief 
    # \param ftr 
    # \return 
    #
    def removeFeature(ftr: Feature) -> bool: pass

    ##
    # \brief 
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
    # \param key The value to test for membership.
    # \return The result of the membership test operation.
    #
    def __contains__(key: CDPL.Base.LookupKey) -> bool: pass

    ##
    # \brief Returns the result of the membership test operation <tt>ftr in self</tt>.
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
    # \param cntnr Specifies the second addend.
    # \return The updated \e %FeatureSet instance \a self.
    #
    def __iadd__(cntnr: FeatureContainer) -> FeatureSet: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= cntnr</tt>.
    # \param cntnr Specifies the subtrahend.
    # \return The updated \e %FeatureSet instance \a self.
    #
    def __isub__(cntnr: FeatureContainer) -> FeatureSet: pass
