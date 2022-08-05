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
    #
    def __init__() -> None: pass

    ##
    # \brief 
    #
    def clear() -> None: pass

    ##
    # \brief 
    # \return 
    #
    def addFeature() -> Feature: pass

    ##
    # \brief 
    # \param idx 
    #
    def removeFeature(idx: int) -> None: pass

    ##
    # \brief 
    # \param pharm 
    #
    def copy(pharm: Pharmacophore) -> None: pass

    ##
    # \brief 
    # \param cntnr 
    #
    def copy(cntnr: FeatureContainer) -> None: pass

    ##
    # \brief 
    # \param pharm 
    #
    def append(pharm: Pharmacophore) -> None: pass

    ##
    # \brief 
    # \param cntnr 
    #
    def append(cntnr: FeatureContainer) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %Pharmacophore instance \a pharm.
    # \param pharm The \e %Pharmacophore instance to copy.
    # \return The assignment target \a self.
    #
    def assign(pharm: Pharmacophore) -> Pharmacophore: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %Pharmacophore instance \a cntnr.
    # \param cntnr The \e %Pharmacophore instance to copy.
    # \return The assignment target \a self.
    #
    def assign(cntnr: FeatureContainer) -> Pharmacophore: pass

    ##
    # \brief 
    # \return 
    #
    def clone() -> Pharmacophore: pass

    ##
    # \brief 
    # \param idx 
    # \return 
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
    # \param arg1 
    # \param arg2 
    #
    def containsFeature(arg2: Feature) -> None: pass

    ##
    # \brief 
    # \param ftr 
    # \return 
    #
    def getFeatureIndex(ftr: Feature) -> int: pass

    ##
    # \brief 
    # \param arg1 
    # \param arg2 
    #
    def getFeatureIndex(arg2: Feature) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getNumFeatures() -> int: pass

    ##
    # \brief 
    # \param idx 
    # \return 
    #
    def getEntity(idx: int) -> CDPL.Chem.Entity3D: pass

    ##
    # \brief 
    # \return 
    #
    def getNumEntities() -> int: pass

    ##
    # \brief 
    # \param key 
    # \param value 
    #
    def setProperty(key: CDPL.Base.LookupKey, value: CDPL.Base.Variant) -> None: pass

    ##
    # \brief 
    # \param key 
    # \return 
    #
    def removeProperty(key: CDPL.Base.LookupKey) -> bool: pass

    ##
    # \brief 
    # \param key 
    # \param throw_ 
    # \return 
    #
    def getProperty(key: CDPL.Base.LookupKey, throw_: bool = False) -> CDPL.Base.Variant: pass

    ##
    # \brief 
    # \param key 
    # \return 
    #
    def isPropertySet(key: CDPL.Base.LookupKey) -> bool: pass

    ##
    # \brief 
    #
    def clearProperties() -> None: pass

    ##
    # \brief 
    # \param cntnr 
    #
    def addProperties(cntnr: CDPL.Base.PropertyContainer) -> None: pass

    ##
    # \brief 
    # \param cntnr 
    #
    def copyProperties(cntnr: CDPL.Base.PropertyContainer) -> None: pass

    ##
    # \brief 
    # \param cntnr 
    #
    def swap(cntnr: CDPL.Base.PropertyContainer) -> None: pass

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
    # \brief 
    # \param idx 
    #
    def __delitem__(idx: int) -> None: pass

    ##
    # \brief 
    # \param key 
    # \return 
    #
    def __delitem__(key: CDPL.Base.LookupKey) -> bool: pass

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
    def __getitem__(key: CDPL.Base.LookupKey) -> CDPL.Base.Variant: pass

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
    def __setitem__(key: CDPL.Base.LookupKey, value: CDPL.Base.Variant) -> None: pass
