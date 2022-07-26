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
class Pharmacophore(FeatureContainer):

    ##
    # \brief Initializes the \e %Pharmacophore instance.
    # \param self The \e %Pharmacophore instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief 
    # \param self The \e %Pharmacophore instance this method is called upon.
    #
    def clear(self: Pharmacophore) -> None: pass

    ##
    # \brief 
    # \param self The \e %Pharmacophore instance this method is called upon.
    # \return 
    #
    def addFeature(self: Pharmacophore) -> Feature: pass

    ##
    # \brief 
    # \param self The \e %Pharmacophore instance this method is called upon.
    # \param idx 
    #
    def removeFeature(self: Pharmacophore, idx: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %Pharmacophore instance this method is called upon.
    # \param pharm 
    #
    def copy(self: Pharmacophore, pharm: Pharmacophore) -> None: pass

    ##
    # \brief 
    # \param self The \e %Pharmacophore instance this method is called upon.
    # \param cntnr 
    #
    def copy(self: Pharmacophore, cntnr: FeatureContainer) -> None: pass

    ##
    # \brief 
    # \param self The \e %Pharmacophore instance this method is called upon.
    # \param pharm 
    #
    def append(self: Pharmacophore, pharm: Pharmacophore) -> None: pass

    ##
    # \brief 
    # \param self The \e %Pharmacophore instance this method is called upon.
    # \param cntnr 
    #
    def append(self: Pharmacophore, cntnr: FeatureContainer) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %Pharmacophore instance \a pharm.
    # \param self The \e %Pharmacophore instance this method is called upon.
    # \param pharm The \e %Pharmacophore instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: Pharmacophore, pharm: Pharmacophore) -> Pharmacophore: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %Pharmacophore instance \a cntnr.
    # \param self The \e %Pharmacophore instance this method is called upon.
    # \param cntnr The \e %Pharmacophore instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: Pharmacophore, cntnr: FeatureContainer) -> Pharmacophore: pass

    ##
    # \brief 
    # \param self The \e %Pharmacophore instance this method is called upon.
    # \return 
    #
    def clone(self: Pharmacophore) -> Pharmacophore: pass

    ##
    # \brief 
    # \param self The \e %Pharmacophore instance this method is called upon.
    # \param idx 
    # \return 
    #
    def getFeature(self: Pharmacophore, idx: int) -> Feature: pass

    ##
    # \brief 
    # \param self The \e %Pharmacophore instance this method is called upon.
    # \param ftr 
    # \return 
    #
    def containsFeature(self: FeatureContainer, ftr: Feature) -> bool: pass

    ##
    # \brief 
    # \param self The \e %Pharmacophore instance this method is called upon.
    # \param arg1 
    # \param arg2 
    #
    def containsFeature(arg1: Pharmacophore, arg2: Feature) -> None: pass

    ##
    # \brief 
    # \param self The \e %Pharmacophore instance this method is called upon.
    # \param ftr 
    # \return 
    #
    def getFeatureIndex(self: FeatureContainer, ftr: Feature) -> int: pass

    ##
    # \brief 
    # \param self The \e %Pharmacophore instance this method is called upon.
    # \param arg1 
    # \param arg2 
    #
    def getFeatureIndex(arg1: Pharmacophore, arg2: Feature) -> None: pass

    ##
    # \brief 
    # \param self The \e %Pharmacophore instance this method is called upon.
    # \return 
    #
    def getNumFeatures(self: Pharmacophore) -> int: pass

    ##
    # \brief 
    # \param self The \e %Pharmacophore instance this method is called upon.
    # \param idx 
    # \return 
    #
    def getEntity(self: Pharmacophore, idx: int) -> CDPL.Chem.Entity3D: pass

    ##
    # \brief 
    # \param self The \e %Pharmacophore instance this method is called upon.
    # \return 
    #
    def getNumEntities(self: Pharmacophore) -> int: pass

    ##
    # \brief 
    # \param self The \e %Pharmacophore instance this method is called upon.
    # \param key 
    # \param value 
    #
    def setProperty(self: Pharmacophore, key: CDPL.Base.LookupKey, value: CDPL.Base.Variant) -> None: pass

    ##
    # \brief 
    # \param self The \e %Pharmacophore instance this method is called upon.
    # \param key 
    # \return 
    #
    def removeProperty(self: Pharmacophore, key: CDPL.Base.LookupKey) -> bool: pass

    ##
    # \brief 
    # \param self The \e %Pharmacophore instance this method is called upon.
    # \param key 
    # \param throw_ 
    # \return 
    #
    def getProperty(self: Pharmacophore, key: CDPL.Base.LookupKey, throw_: bool = False) -> CDPL.Base.Variant: pass

    ##
    # \brief 
    # \param self The \e %Pharmacophore instance this method is called upon.
    # \param key 
    # \return 
    #
    def isPropertySet(self: Pharmacophore, key: CDPL.Base.LookupKey) -> bool: pass

    ##
    # \brief 
    # \param self The \e %Pharmacophore instance this method is called upon.
    #
    def clearProperties(self: Pharmacophore) -> None: pass

    ##
    # \brief 
    # \param self The \e %Pharmacophore instance this method is called upon.
    # \param cntnr 
    #
    def addProperties(self: PropertyContainer, cntnr: CDPL.Base.PropertyContainer) -> None: pass

    ##
    # \brief 
    # \param self The \e %Pharmacophore instance this method is called upon.
    # \param cntnr 
    #
    def copyProperties(self: PropertyContainer, cntnr: CDPL.Base.PropertyContainer) -> None: pass

    ##
    # \brief 
    # \param self The \e %Pharmacophore instance this method is called upon.
    # \param cntnr 
    #
    def swap(self: Pharmacophore, cntnr: CDPL.Base.PropertyContainer) -> None: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += pharm</tt>.
    # \param self The \e %Pharmacophore instance acting as in-place addend.
    # \param pharm Specifies the second addend.
    # \return The updated \e %Pharmacophore instance \a self.
    #
    def __iadd__(self: Pharmacophore, pharm: Pharmacophore) -> Pharmacophore: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += cntnr</tt>.
    # \param self The \e %Pharmacophore instance acting as in-place addend.
    # \param cntnr Specifies the second addend.
    # \return The updated \e %Pharmacophore instance \a self.
    #
    def __iadd__(self: Pharmacophore, cntnr: FeatureContainer) -> Pharmacophore: pass

    ##
    # \brief 
    # \param self The \e %Pharmacophore instance this method is called upon.
    # \param idx 
    #
    def __delitem__(self: Pharmacophore, idx: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %Pharmacophore instance this method is called upon.
    # \param key 
    # \return 
    #
    def __delitem__(self: Pharmacophore, key: CDPL.Base.LookupKey) -> bool: pass

    ##
    # \brief Returns the result of the membership test operation <tt>ftr in self</tt>.
    # \param self The \e %Pharmacophore instance this method is called upon.
    # \param ftr The value to test for membership.
    # \return The result of the membership test operation.
    #
    def __contains__(self: FeatureContainer, ftr: Feature) -> bool: pass

    ##
    # \brief Returns the result of the membership test operation <tt>key in self</tt>.
    # \param self The \e %Pharmacophore instance this method is called upon.
    # \param key The value to test for membership.
    # \return The result of the membership test operation.
    #
    def __contains__(self: Pharmacophore, key: CDPL.Base.LookupKey) -> bool: pass

    ##
    # \brief 
    # \param self The \e %Pharmacophore instance this method is called upon.
    # \param idx 
    # \return 
    #
    def __getitem__(self: Pharmacophore, idx: int) -> Feature: pass

    ##
    # \brief 
    # \param self The \e %Pharmacophore instance this method is called upon.
    # \param key 
    # \return 
    #
    def __getitem__(self: PropertyContainer, key: CDPL.Base.LookupKey) -> CDPL.Base.Variant: pass

    ##
    # \brief 
    # \param self The \e %Pharmacophore instance this method is called upon.
    # \return 
    #
    def __len__(self: Pharmacophore) -> int: pass

    ##
    # \brief 
    # \param self The \e %Pharmacophore instance this method is called upon.
    # \param key 
    # \param value 
    #
    def __setitem__(self: Pharmacophore, key: CDPL.Base.LookupKey, value: CDPL.Base.Variant) -> None: pass
