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
# \brief SubstructureHistogramCalculator.
# 
class SubstructureHistogramCalculator(Boost.Python.instance):

    ##
    # \brief 
    #
    class Pattern(Boost.Python.instance):

        ##
        # \brief Initializes the \e %Pattern instance.
        # \param ptn 
        # 
        def __init__(ptn: Pattern) -> None: pass

        ##
        # \brief Initializes the \e %Pattern instance.
        # \param structure 
        # \param id 
        # \param priority 
        # \param all_matches 
        # \param unique_matches 
        # 
        def __init__(structure: MolecularGraph, id: int, priority: int = 0, all_matches: bool = True, unique_matches: bool = True) -> None: pass

        ##
        # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
        # 
        # Different Python \e %Pattern instances may reference the same underlying C++ class instance. The commonly used Python expression
        # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %Pattern instances \e a and \e b reference different C++ objects. 
        # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
        # <tt>a.getObjectID() != b.getObjectID()</tt>.
        # 
        # \return The numeric ID of the internally referenced C++ class instance.
        # 
        def getObjectID() -> int: pass

        ##
        # \brief Replaces the current state of \a self with a copy of the state of the \e %Pattern instance \a ptn.
        # \param ptn The \e %Pattern instance to copy.
        # \return \a self
        # 
        def assign(ptn: Pattern) -> Pattern: pass

        ##
        # \brief 
        # \return 
        #
        def getStructure() -> MolecularGraph: pass

        ##
        # \brief 
        # \return 
        #
        def getPriority() -> int: pass

        ##
        # \brief 
        # \return 
        #
        def getID() -> int: pass

        ##
        # \brief 
        # \return 
        #
        def processAllMatches() -> bool: pass

        ##
        # \brief 
        # \return 
        #
        def processUniqueMatchesOnly() -> bool: pass

        objectID = property(getObjectID)

        structure = property(getStructure)

        priority = property(getPriority)

        ##
        # \brief FIXME!
        # \brief 
        #
        id = property(getId)

        ##
        # \brief FIXME!
        # \brief 
        #
        allMatches = property(getAllMatches)

        ##
        # \brief FIXME!
        # \brief 
        #
        uniqueMatches = property(getUniqueMatches)

    ##
    # \brief Initializes the \e %SubstructureHistogramCalculator instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %SubstructureHistogramCalculator instance.
    # \param calc 
    # 
    def __init__(calc: SubstructureHistogramCalculator) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \e %SubstructureHistogramCalculator instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %SubstructureHistogramCalculator instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief 
    # \param structure 
    # \param id 
    # \param priority 
    # \param all_matches 
    # \param unique_matches 
    #
    def addPattern(structure: MolecularGraph, id: int = 0, priority: int = 0, all_matches: bool = True, unique_matches: bool = True) -> None: pass

    ##
    # \brief 
    # \param ptn 
    #
    def addPattern(ptn: Pattern) -> None: pass

    ##
    # \brief 
    # \param idx 
    # \return 
    #
    def getPattern(idx: int) -> Pattern: pass

    ##
    # \brief 
    # \param idx 
    #
    def removePattern(idx: int) -> None: pass

    ##
    # \brief 
    #
    def clear() -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getNumPatterns() -> int: pass

    ##
    # \brief 
    # \param molgraph 
    # \param histo 
    #
    def calculate(molgraph: MolecularGraph, histo: object) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %SubstructureHistogramCalculator instance \a calc.
    # \param calc The \e %SubstructureHistogramCalculator instance to copy.
    # \return \a self
    # 
    def assign(calc: SubstructureHistogramCalculator) -> SubstructureHistogramCalculator: pass

    objectID = property(getObjectID)

    numPatterns = property(getNumPatterns)
