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
class MMFF94AngleBendingInteractionParameterizer(Boost.Python.instance):

    ##
    # \brief Initializes the \e %MMFF94AngleBendingInteractionParameterizer instance.
    # \param self The \e %MMFF94AngleBendingInteractionParameterizer instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %MMFF94AngleBendingInteractionParameterizer instance.
    # \param self The \e %MMFF94AngleBendingInteractionParameterizer instance to initialize.
    # \param parameterizer 
    #
    def __init__(self: object, parameterizer: MMFF94AngleBendingInteractionParameterizer) -> None: pass

    ##
    # \brief Initializes the \e %MMFF94AngleBendingInteractionParameterizer instance.
    # \param self The \e %MMFF94AngleBendingInteractionParameterizer instance to initialize.
    # \param molgraph 
    # \param ia_data 
    # \param strict 
    #
    def __init__(self: object, molgraph: CDPL.Chem.MolecularGraph, ia_data: MMFF94AngleBendingInteractionData, strict: bool) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %MMFF94AngleBendingInteractionParameterizer instance this method is called upon.
    #
    # Different Python \e %MMFF94AngleBendingInteractionParameterizer instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %MMFF94AngleBendingInteractionParameterizer instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: MMFF94AngleBendingInteractionParameterizer) -> int: pass

    ##
    # \brief 
    # \param self The \e %MMFF94AngleBendingInteractionParameterizer instance this method is called upon.
    # \param func 
    #
    def setFilterFunction(self: MMFF94AngleBendingInteractionParameterizer, func: InteractionFilterFunction3) -> None: pass

    ##
    # \brief 
    # \param self The \e %MMFF94AngleBendingInteractionParameterizer instance this method is called upon.
    # \param func 
    #
    def setAtomTypeFunction(self: MMFF94AngleBendingInteractionParameterizer, func: MMFF94NumericAtomTypeFunction) -> None: pass

    ##
    # \brief 
    # \param self The \e %MMFF94AngleBendingInteractionParameterizer instance this method is called upon.
    # \param func 
    #
    def setBondTypeIndexFunction(self: MMFF94AngleBendingInteractionParameterizer, func: MMFF94BondTypeIndexFunction) -> None: pass

    ##
    # \brief 
    # \param self The \e %MMFF94AngleBendingInteractionParameterizer instance this method is called upon.
    # \param func 
    #
    def setAromaticRingSetFunction(self: MMFF94AngleBendingInteractionParameterizer, func: MMFF94RingSetFunction) -> None: pass

    ##
    # \brief 
    # \param self The \e %MMFF94AngleBendingInteractionParameterizer instance this method is called upon.
    # \param table 
    #
    def setAngleBendingParameterTable(self: MMFF94AngleBendingInteractionParameterizer, table: MMFF94AngleBendingParameterTable) -> None: pass

    ##
    # \brief 
    # \param self The \e %MMFF94AngleBendingInteractionParameterizer instance this method is called upon.
    # \param table 
    #
    def setBondStretchingParameterTable(self: MMFF94AngleBendingInteractionParameterizer, table: MMFF94BondStretchingParameterTable) -> None: pass

    ##
    # \brief 
    # \param self The \e %MMFF94AngleBendingInteractionParameterizer instance this method is called upon.
    # \param table 
    #
    def setBondStretchingRuleParameterTable(self: MMFF94AngleBendingInteractionParameterizer, table: MMFF94BondStretchingRuleParameterTable) -> None: pass

    ##
    # \brief 
    # \param self The \e %MMFF94AngleBendingInteractionParameterizer instance this method is called upon.
    # \param table 
    #
    def setAtomTypePropertyTable(self: MMFF94AngleBendingInteractionParameterizer, table: MMFF94AtomTypePropertyTable) -> None: pass

    ##
    # \brief 
    # \param self The \e %MMFF94AngleBendingInteractionParameterizer instance this method is called upon.
    # \param map 
    #
    def setParameterAtomTypeMap(self: MMFF94AngleBendingInteractionParameterizer, map: MMFF94PrimaryToParameterAtomTypeMap) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %MMFF94AngleBendingInteractionParameterizer instance \a parameterizer.
    # \param self The \e %MMFF94AngleBendingInteractionParameterizer instance this method is called upon.
    # \param parameterizer The \e %MMFF94AngleBendingInteractionParameterizer instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: MMFF94AngleBendingInteractionParameterizer, parameterizer: MMFF94AngleBendingInteractionParameterizer) -> MMFF94AngleBendingInteractionParameterizer: pass

    ##
    # \brief 
    # \param self The \e %MMFF94AngleBendingInteractionParameterizer instance this method is called upon.
    # \param molgraph 
    # \param ia_data 
    # \param strict 
    #
    def parameterize(self: MMFF94AngleBendingInteractionParameterizer, molgraph: CDPL.Chem.MolecularGraph, ia_data: MMFF94AngleBendingInteractionData, strict: bool) -> None: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)
