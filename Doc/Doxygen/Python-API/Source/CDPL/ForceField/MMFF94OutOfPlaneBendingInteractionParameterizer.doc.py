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
# \brief Generates the MMFF94 out-of-plane bending interactions for the trigonal centers of a molecular graph.
# 
# For every atom <em>j</em> with exactly three neighbors that is a trigonal center (per the MMFF94 atom-type properties) the parameterizer generates three out-of-plane records — one for each permutation of the three neighbors as the out-of-plane atom <em>l</em> with the remaining two as in-plane terminal atoms. The required out-of-plane force constants are taken from the parameter table, falling back through the primary-to-parameter atom-type map when no exact entry is available.
# 
class MMFF94OutOfPlaneBendingInteractionParameterizer(Boost.Python.instance):

    ##
    # \brief Constructs an <tt>MMFF94OutOfPlaneBendingInteractionParameterizer</tt> instance using the default MMFF94 parameter tables.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \c %MMFF94OutOfPlaneBendingInteractionParameterizer instance \a parameterizer.
    # \param parameterizer The \c %MMFF94OutOfPlaneBendingInteractionParameterizer instance to copy.
    # 
    def __init__(parameterizer: MMFF94OutOfPlaneBendingInteractionParameterizer) -> None: pass

    ##
    # \brief Constructs the parameterizer and immediately processes <em>molgraph</em> into <em>ia_list</em>.
    # 
    # \param molgraph The molecular graph for which to parameterize the out-of-plane bending interactions.
    # \param ia_list Output list receiving the generated MMFF94OutOfPlaneBendingInteraction records.
    # \param strict If <tt>True</tt>, missing/ambiguous parameters cause a parameterization failure.
    # 
    def __init__(molgraph: Chem.MolecularGraph, ia_list: MMFF94OutOfPlaneBendingInteractionList, strict: bool) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %MMFF94OutOfPlaneBendingInteractionParameterizer instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %MMFF94OutOfPlaneBendingInteractionParameterizer instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Sets the filter function used to skip atom quadruplets during parameterization.
    # 
    # \param func The new four-atom filter function (when it returns <tt>False</tt>, the quadruplet is skipped).
    # 
    def setFilterFunction(func: InteractionFilterFunction4) -> None: pass

    ##
    # \brief Sets the function used to look up the MMFF94 numeric atom type of an atom.
    # 
    # \param func The new numeric-atom-type lookup function.
    # 
    def setAtomTypeFunction(func: MMFF94NumericAtomTypeFunction) -> None: pass

    ##
    # \brief Sets the table providing per-atom-type-quadruplet out-of-plane bending force constants.
    # 
    # \param table The new out-of-plane bending parameter table.
    # 
    def setOutOfPlaneBendingParameterTable(table: MMFF94OutOfPlaneBendingParameterTable) -> None: pass

    ##
    # \brief Sets the table providing per-numeric-atom-type property data (used to identify trigonal centers).
    # 
    # \param table The new atom-type property table.
    # 
    def setAtomTypePropertyTable(table: MMFF94AtomTypePropertyTable) -> None: pass

    ##
    # \brief Sets the map used to translate primary atom types into their corresponding parameter-atom types.
    # 
    # \param map The new primary-to-parameter atom-type map.
    # 
    def setParameterAtomTypeMap(map: MMFF94PrimaryToParameterAtomTypeMap) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %MMFF94OutOfPlaneBendingInteractionParameterizer instance \a parameterizer.
    # \param parameterizer The \c %MMFF94OutOfPlaneBendingInteractionParameterizer instance to copy.
    # \return \a self
    # 
    def assign(parameterizer: MMFF94OutOfPlaneBendingInteractionParameterizer) -> MMFF94OutOfPlaneBendingInteractionParameterizer: pass

    ##
    # \brief Generates the MMFF94 out-of-plane bending interactions for <em>molgraph</em> and writes them to <em>ia_list</em>.
    # 
    # \param molgraph The molecular graph for which to parameterize the out-of-plane bending interactions.
    # \param ia_list Output list receiving the generated MMFF94OutOfPlaneBendingInteraction records.
    # \param strict If <tt>True</tt>, missing/ambiguous parameters cause a parameterization failure.
    # 
    def parameterize(molgraph: Chem.MolecularGraph, ia_list: MMFF94OutOfPlaneBendingInteractionList, strict: bool) -> None: pass

    objectID = property(getObjectID)
