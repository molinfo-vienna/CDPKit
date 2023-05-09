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
class InteractionAnalyzer(Boost.Python.instance):

    ##
    # \brief Initializes the \e %InteractionAnalyzer instance.
    #
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %InteractionAnalyzer instance.
    # \param analyzer 
    #
    def __init__(analyzer: InteractionAnalyzer) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    #
    # Different Python \e %InteractionAnalyzer instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %InteractionAnalyzer instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID() -> int: pass

    ##
    # \brief 
    # \param type1 
    # \param type2 
    # \param func 
    #
    def setConstraintFunction(type1: int, type2: int, func: BoolFeature2Functor) -> None: pass

    ##
    # \brief 
    # \param type1 
    # \param type2 
    #
    def removeConstraintFunction(type1: int, type2: int) -> None: pass

    ##
    # \brief 
    # \param type1 
    # \param type2 
    # \return 
    #
    def getConstraintFunction(type1: int, type2: int) -> BoolFeature2Functor: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %InteractionAnalyzer instance \a analyzer.
    # \param analyzer The \e %InteractionAnalyzer instance to copy.
    # \return \a self
    #
    def assign(analyzer: InteractionAnalyzer) -> InteractionAnalyzer: pass

    ##
    # \brief 
    # \param cntnr1 
    # \param cntnr2 
    # \param iactions 
    # \param append 
    #
    def analyze(cntnr1: FeatureContainer, cntnr2: FeatureContainer, iactions: FeatureMapping, append: bool = False) -> None: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)
