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
class AttributedGrid(CDPL.Base.PropertyContainer):

    ##
    # \brief Initializes the \e %AttributedGrid instance.
    # \param self The \e %AttributedGrid instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief 
    # \param self The \e %AttributedGrid instance this method is called upon.
    # \return 
    #
    def isEmpty(self: AttributedGrid) -> bool: pass

    ##
    # \brief 
    # \param self The \e %AttributedGrid instance this method is called upon.
    # \return 
    #
    def getNumElements(self: AttributedGrid) -> int: pass

    ##
    # \brief 
    # \param self The \e %AttributedGrid instance this method is called upon.
    # \param key 
    # \param value 
    #
    def setProperty(self: AttributedGrid, key: CDPL.Base.LookupKey, value: CDPL.Base.Variant) -> None: pass

    ##
    # \brief 
    # \param self The \e %AttributedGrid instance this method is called upon.
    # \param key 
    # \return 
    #
    def removeProperty(self: AttributedGrid, key: CDPL.Base.LookupKey) -> bool: pass

    ##
    # \brief 
    # \param self The \e %AttributedGrid instance this method is called upon.
    # \param key 
    # \param throw_ 
    # \return 
    #
    def getProperty(self: AttributedGrid, key: CDPL.Base.LookupKey, throw_: bool = False) -> CDPL.Base.Variant: pass

    ##
    # \brief 
    # \param self The \e %AttributedGrid instance this method is called upon.
    # \param key 
    # \return 
    #
    def isPropertySet(self: AttributedGrid, key: CDPL.Base.LookupKey) -> bool: pass

    ##
    # \brief 
    # \param self The \e %AttributedGrid instance this method is called upon.
    #
    def clearProperties(self: AttributedGrid) -> None: pass

    ##
    # \brief 
    # \param self The \e %AttributedGrid instance this method is called upon.
    # \param cntnr 
    #
    def addProperties(self: PropertyContainer, cntnr: CDPL.Base.PropertyContainer) -> None: pass

    ##
    # \brief 
    # \param self The \e %AttributedGrid instance this method is called upon.
    # \param cntnr 
    #
    def copyProperties(self: PropertyContainer, cntnr: CDPL.Base.PropertyContainer) -> None: pass

    ##
    # \brief 
    # \param self The \e %AttributedGrid instance this method is called upon.
    # \param cntnr 
    #
    def swap(self: AttributedGrid, cntnr: CDPL.Base.PropertyContainer) -> None: pass

    ##
    # \brief 
    # \param self The \e %AttributedGrid instance this method is called upon.
    # \return 
    #
    def __len__(self: AttributedGrid) -> int: pass

    ##
    # \brief 
    # \param self The \e %AttributedGrid instance this method is called upon.
    # \param key 
    # \return 
    #
    def __getitem__(self: PropertyContainer, key: CDPL.Base.LookupKey) -> CDPL.Base.Variant: pass

    ##
    # \brief Returns the result of the membership test operation <tt>key in self</tt>.
    # \param self The \e %AttributedGrid instance this method is called upon.
    # \param key The value to test for membership.
    # \return The result of the membership test operation.
    #
    def __contains__(self: AttributedGrid, key: CDPL.Base.LookupKey) -> bool: pass

    ##
    # \brief 
    # \param self The \e %AttributedGrid instance this method is called upon.
    # \param key 
    # \param value 
    #
    def __setitem__(self: AttributedGrid, key: CDPL.Base.LookupKey, value: CDPL.Base.Variant) -> None: pass

    ##
    # \brief 
    # \param self The \e %AttributedGrid instance this method is called upon.
    # \param key 
    # \return 
    #
    def __delitem__(self: AttributedGrid, key: CDPL.Base.LookupKey) -> bool: pass

    ##
    # \brief 
    #
    numElements = property(getNumElements)
