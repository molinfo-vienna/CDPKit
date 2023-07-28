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
class MMFF94VanDerWaalsInteractionParameterizer(Boost.Python.instance):

    ##
    # \brief Initializes the \e %MMFF94VanDerWaalsInteractionParameterizer instance.
    # \param self The \e %MMFF94VanDerWaalsInteractionParameterizer instance to initialize.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %MMFF94VanDerWaalsInteractionParameterizer instance.
    # \param self The \e %MMFF94VanDerWaalsInteractionParameterizer instance to initialize.
    # \param parameterizer 
    # 
    def __init__(parameterizer: MMFF94VanDerWaalsInteractionParameterizer) -> None: pass

    ##
    # \brief Initializes the \e %MMFF94VanDerWaalsInteractionParameterizer instance.
    # \param self The \e %MMFF94VanDerWaalsInteractionParameterizer instance to initialize.
    # \param molgraph 
    # \param ia_data 
    # \param strict 
    # 
    def __init__(molgraph: CDPL.Chem.MolecularGraph, ia_data: MMFF94VanDerWaalsInteractionData, strict: bool) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %MMFF94VanDerWaalsInteractionParameterizer instance this method is called upon.
    # 
    # Different Python \e %MMFF94VanDerWaalsInteractionParameterizer instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %MMFF94VanDerWaalsInteractionParameterizer instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief 
    # \param func 
    #
    def setFilterFunction(func: InteractionFilterFunction2) -> None: pass

    ##
    # \brief 
    # \param func 
    #
    def setAtomTypeFunction(func: MMFF94NumericAtomTypeFunction) -> None: pass

    ##
    # \brief 
    # \param func 
    #
    def setTopologicalDistanceFunction(func: TopologicalAtomDistanceFunction) -> None: pass

    ##
    # \brief 
    # \param table 
    #
    def setVanDerWaalsParameterTable(table: MMFF94VanDerWaalsParameterTable) -> None: pass

    ##
    # \brief 
    # \param parameterizer 
    # \return 
    #
    def assign(parameterizer: MMFF94VanDerWaalsInteractionParameterizer) -> MMFF94VanDerWaalsInteractionParameterizer: pass

    ##
    # \brief 
    # \param molgraph 
    # \param ia_data 
    # \param strict 
    #
    def parameterize(molgraph: CDPL.Chem.MolecularGraph, ia_data: MMFF94VanDerWaalsInteractionData, strict: bool) -> None: pass

    objectID = property(getObjectID)
