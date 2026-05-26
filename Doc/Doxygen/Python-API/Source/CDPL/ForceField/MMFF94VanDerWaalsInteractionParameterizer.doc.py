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
# \brief Generates the MMFF94 Van der Waals interactions for the non-bonded atom pairs of a molecular graph.
# 
# For every pair of atoms separated by at least three bonds the parameterizer looks up the per-atom-type Van der Waals parameters and the donor/acceptor classification from the supplied parameter table, applies the MMFF94 combining rules and emits an MMFF94VanDerWaalsInteraction record into the output list.
# 
class MMFF94VanDerWaalsInteractionParameterizer(Boost.Python.instance):

    ##
    # \brief Constructs an <tt>MMFF94VanDerWaalsInteractionParameterizer</tt> instance using the default MMFF94 parameter tables.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \c %MMFF94VanDerWaalsInteractionParameterizer instance \a parameterizer.
    # \param parameterizer The \c %MMFF94VanDerWaalsInteractionParameterizer instance to copy.
    # 
    def __init__(parameterizer: MMFF94VanDerWaalsInteractionParameterizer) -> None: pass

    ##
    # \brief Constructs the parameterizer and immediately processes <em>molgraph</em> into <em>ia_list</em>.
    # 
    # \param molgraph The molecular graph for which to parameterize the Van der Waals interactions.
    # \param ia_list Output list receiving the generated MMFF94VanDerWaalsInteraction records.
    # \param strict If <tt>True</tt>, missing/ambiguous parameters cause a parameterization failure.
    # 
    def __init__(molgraph: Chem.MolecularGraph, ia_list: MMFF94VanDerWaalsInteractionList, strict: bool) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %MMFF94VanDerWaalsInteractionParameterizer instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %MMFF94VanDerWaalsInteractionParameterizer instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Sets the filter function used to skip atom pairs during parameterization.
    # 
    # \param func The new filter function (when it returns <tt>False</tt> for an atom pair, the pair is skipped).
    # 
    def setFilterFunction(func: Chem.BoolAtom2Functor) -> None: pass

    ##
    # \brief Sets the function used to look up the MMFF94 numeric atom type of an atom.
    # 
    # \param func The new numeric-atom-type lookup function.
    # 
    def setAtomTypeFunction(func: MMFF94NumericAtomTypeFunction) -> None: pass

    ##
    # \brief Sets the function used to determine the topological distance between two atoms (number of bonds along the shortest path).
    # 
    # \param func The new topological-distance function.
    # 
    def setTopologicalDistanceFunction(func: TopologicalAtomDistanceFunction) -> None: pass

    ##
    # \brief Sets the table providing per-numeric-atom-type Van der Waals parameters and donor/acceptor classifications.
    # 
    # \param table The new Van der Waals parameter table.
    # 
    def setVanDerWaalsParameterTable(table: MMFF94VanDerWaalsParameterTable) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %MMFF94VanDerWaalsInteractionParameterizer instance \a parameterizer.
    # \param parameterizer The \c %MMFF94VanDerWaalsInteractionParameterizer instance to copy.
    # \return \a self
    # 
    def assign(parameterizer: MMFF94VanDerWaalsInteractionParameterizer) -> MMFF94VanDerWaalsInteractionParameterizer: pass

    ##
    # \brief Generates the MMFF94 Van der Waals interactions for <em>molgraph</em> and writes them to <em>ia_list</em>.
    # 
    # \param molgraph The molecular graph for which to parameterize the Van der Waals interactions.
    # \param ia_list Output list receiving the generated MMFF94VanDerWaalsInteraction records.
    # \param strict If <tt>True</tt>, missing/ambiguous parameters cause a parameterization failure.
    # 
    def parameterize(molgraph: Chem.MolecularGraph, ia_list: MMFF94VanDerWaalsInteractionList, strict: bool) -> None: pass

    objectID = property(getObjectID)
