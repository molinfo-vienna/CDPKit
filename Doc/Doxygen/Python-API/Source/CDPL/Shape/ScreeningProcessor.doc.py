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
# \brief High-level driver for shape-based virtual screening of molecular databases.
# 
# The processor maintains a set of query molecules and aligns each incoming database molecule against all of them, reporting alignment hits through a user-supplied callback. The behaviour (similarity score type, shape generation, alignment options, etc.) is configured via the embedded Shape.ScreeningSettings instance.
# 
class ScreeningProcessor(Boost.Python.instance):

    ##
    # \brief Constructs an empty <tt>ScreeningProcessor</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Constructs a <tt>ScreeningProcessor</tt> instance with <em>query</em> as the single query molecule.
    # 
    # \param query The query molecule.
    # 
    def __init__(query: Chem.MolecularGraph) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %ScreeningProcessor instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %ScreeningProcessor instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Sets the callback that is invoked for every alignment hit produced by process().
    # 
    # \param func The hit-callback function.
    # 
    def setHitCallback(func: VoidMolecularGraph2AlignmentResultFunctor) -> None: pass

    ##
    # \brief Returns the currently configured hit callback.
    # 
    # \return A reference to the hit-callback function.
    # 
    def getHitCallback() -> VoidMolecularGraph2AlignmentResultFunctor: pass

    ##
    # \brief Returns the current screening settings (mutable).
    # 
    # \return A reference to the screening settings.
    # 
    def getSettings() -> ScreeningSettings: pass

    ##
    # \brief Removes all query molecules.
    # 
    def clearQuerySet() -> None: pass

    ##
    # \brief Adds <em>molgraph</em> to the query set.
    # 
    # \param molgraph The query molecule.
    # 
    def addQuery(molgraph: Chem.MolecularGraph) -> None: pass

    ##
    # \brief Returns the number of query molecules.
    # 
    # \return The number of query molecules.
    # 
    def getQuerySetSize() -> int: pass

    ##
    # \brief Returns the query molecule at index <em>idx</em>.
    # 
    # \param idx The zero-based index of the query molecule.
    # 
    # \return A reference to the query molecule. 
    # 
    # \throw Base.IndexError if the number of query molecules is zero or <em>idx</em> is not in the range [0, getQuerySetSize() - 1].
    # 
    def getQuery(idx: int) -> Chem.MolecularGraph: pass

    ##
    # \brief Processes the database molecule <em>molgraph</em>, aligning it against all query molecules.
    # 
    # \param molgraph The database molecule.
    # 
    # \return <tt>True</tt> if at least one alignment hit was produced for <em>molgraph</em>, and <tt>False</tt> otherwise.
    # 
    def process(molgraph: Chem.MolecularGraph) -> bool: pass

    objectID = property(getObjectID)

    hitCallback = property(getHitCallback, setHitCallback)

    settings = property(getSettings)

    querySetSize = property(getQuerySetSize)
