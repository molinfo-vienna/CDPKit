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
class Feature(CDPL.Chem.Entity3D):

    ##
    # \brief Initializes the \e %Feature instance.
    # \param self The \e %Feature instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief 
    # \param self The \e %Feature instance this method is called upon.
    # \return 
    #
    def getPharmacophore(self: Feature) -> Pharmacophore: pass

    ##
    # \brief 
    # \param self The \e %Feature instance this method is called upon.
    # \return 
    #
    def getIndex(self: Feature) -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %Feature instance \a ftr.
    # \param self The \e %Feature instance this method is called upon.
    # \param ftr The \e %Feature instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: Feature, ftr: Feature) -> Feature: pass

    ##
    # \brief 
    # \param self The \e %Feature instance this method is called upon.
    # \param key 
    # \param value 
    #
    def setProperty(self: Feature, key: CDPL.Base.LookupKey, value: CDPL.Base.Variant) -> None: pass

    ##
    # \brief 
    # \param self The \e %Feature instance this method is called upon.
    # \param key 
    # \return 
    #
    def removeProperty(self: Feature, key: CDPL.Base.LookupKey) -> bool: pass

    ##
    # \brief 
    # \param self The \e %Feature instance this method is called upon.
    # \param key 
    # \param throw_ 
    # \return 
    #
    def getProperty(self: Feature, key: CDPL.Base.LookupKey, throw_: bool = False) -> CDPL.Base.Variant: pass

    ##
    # \brief 
    # \param self The \e %Feature instance this method is called upon.
    # \param key 
    # \return 
    #
    def isPropertySet(self: Feature, key: CDPL.Base.LookupKey) -> bool: pass

    ##
    # \brief 
    # \param self The \e %Feature instance this method is called upon.
    #
    def clearProperties(self: Feature) -> None: pass

    ##
    # \brief 
    # \param self The \e %Feature instance this method is called upon.
    # \param cntnr 
    #
    def addProperties(self: PropertyContainer, cntnr: CDPL.Base.PropertyContainer) -> None: pass

    ##
    # \brief 
    # \param self The \e %Feature instance this method is called upon.
    # \param cntnr 
    #
    def copyProperties(self: PropertyContainer, cntnr: CDPL.Base.PropertyContainer) -> None: pass

    ##
    # \brief 
    # \param self The \e %Feature instance this method is called upon.
    # \param cntnr 
    #
    def swap(self: Feature, cntnr: CDPL.Base.PropertyContainer) -> None: pass

    ##
    # \brief 
    # \param self The \e %Feature instance this method is called upon.
    # \param key 
    # \return 
    #
    def __getitem__(self: PropertyContainer, key: CDPL.Base.LookupKey) -> CDPL.Base.Variant: pass

    ##
    # \brief Returns the result of the membership test operation <tt>key in self</tt>.
    # \param self The \e %Feature instance this method is called upon.
    # \param key The value to test for membership.
    # \return The result of the membership test operation.
    #
    def __contains__(self: Feature, key: CDPL.Base.LookupKey) -> bool: pass

    ##
    # \brief 
    # \param self The \e %Feature instance this method is called upon.
    # \param key 
    # \param value 
    #
    def __setitem__(self: Feature, key: CDPL.Base.LookupKey, value: CDPL.Base.Variant) -> None: pass

    ##
    # \brief 
    # \param self The \e %Feature instance this method is called upon.
    # \param key 
    # \return 
    #
    def __delitem__(self: Feature, key: CDPL.Base.LookupKey) -> bool: pass

    ##
    # \brief 
    # \param self The \e %Feature instance this method is called upon.
    # \return 
    #
    def __len__(self: Feature) -> int: pass

    ##
    # \brief 
    #
    pharmacophore = property(getPharmacophore)

    ##
    # \brief 
    #
    index = property(getIndex)
