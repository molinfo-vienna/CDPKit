#
# This file is part of the Chemical Data Processing Toolkit
#
# Copyright (C) Thomas A. Seidel <thomas.seidel@univie.ac.at>
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
    # \param self The \e %FeatureSet instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %FeatureSet instance.
    # \param self The \e %FeatureSet instance to initialize.
    # \param ftr_set 
    #
    def __init__(self: object, ftr_set: FeatureSet) -> None: pass

    ##
    # \brief Initializes the \e %FeatureSet instance.
    # \param self The \e %FeatureSet instance to initialize.
    # \param cntnr 
    #
    def __init__(self: object, cntnr: FeatureContainer) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %FeatureSet instance \a ftr_set.
    # \param self The \e %FeatureSet instance this method is called upon.
    # \param ftr_set The \e %FeatureSet instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: FeatureSet, ftr_set: FeatureSet) -> FeatureSet: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %FeatureSet instance \a cntnr.
    # \param self The \e %FeatureSet instance this method is called upon.
    # \param cntnr The \e %FeatureSet instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: FeatureSet, cntnr: FeatureContainer) -> FeatureSet: pass

    ##
    # \brief 
    # \param self The \e %FeatureSet instance this method is called upon.
    # \param ftr 
    # \return 
    #
    def addFeature(self: FeatureSet, ftr: Feature) -> bool: pass

    ##
    # \brief 
    # \param self The \e %FeatureSet instance this method is called upon.
    # \param idx 
    #
    def removeFeature(self: FeatureSet, idx: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %FeatureSet instance this method is called upon.
    # \param ftr 
    # \return 
    #
    def removeFeature(self: FeatureSet, ftr: Feature) -> bool: pass

    ##
    # \brief 
    # \param self The \e %FeatureSet instance this method is called upon.
    #
    def clear(self: FeatureSet) -> None: pass

    ##
    # \brief 
    # \param self The \e %FeatureSet instance this method is called upon.
    # \param key 
    # \return 
    #
    def __getitem__(self: PropertyContainer, key: CDPL.Base.LookupKey) -> CDPL.Base.Variant: pass

    ##
    # \brief 
    # \param self The \e %FeatureSet instance this method is called upon.
    # \param idx 
    # \return 
    #
    def __getitem__(self: FeatureSet, idx: int) -> Feature: pass

    ##
    # \brief Returns the result of the membership test operation <tt>key in self</tt>.
    # \param self The \e %FeatureSet instance this method is called upon.
    # \param key The value to test for membership.
    # \return The result of the membership test operation.
    #
    def __contains__(self: FeatureSet, key: CDPL.Base.LookupKey) -> bool: pass

    ##
    # \brief Returns the result of the membership test operation <tt>ftr in self</tt>.
    # \param self The \e %FeatureSet instance this method is called upon.
    # \param ftr The value to test for membership.
    # \return The result of the membership test operation.
    #
    def __contains__(self: FeatureContainer, ftr: Feature) -> bool: pass

    ##
    # \brief 
    # \param self The \e %FeatureSet instance this method is called upon.
    # \param key 
    # \param value 
    #
    def __setitem__(self: FeatureSet, key: CDPL.Base.LookupKey, value: CDPL.Base.Variant) -> None: pass

    ##
    # \brief 
    # \param self The \e %FeatureSet instance this method is called upon.
    # \param key 
    # \return 
    #
    def __delitem__(self: FeatureSet, key: CDPL.Base.LookupKey) -> bool: pass

    ##
    # \brief 
    # \param self The \e %FeatureSet instance this method is called upon.
    # \return 
    #
    def __len__(self: FeatureSet) -> int: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += cntnr</tt>.
    # \param self The \e %FeatureSet instance acting as in-place addend.
    # \param cntnr Specifies the second addend.
    # \return The updated \e %FeatureSet instance \a self.
    #
    def __iadd__(self: FeatureSet, cntnr: FeatureContainer) -> FeatureSet: pass
