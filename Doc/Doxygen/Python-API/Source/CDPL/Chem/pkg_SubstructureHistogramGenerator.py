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
class SubstructureHistogramGenerator(Boost.Python.instance):

    ##
    # \brief 
    #
    class Pattern(Boost.Python.instance):

        ##
        # \brief Initializes the \e %Pattern instance.
        # \param self The \e %Pattern instance to initialize.
        # \param ptn 
        #
        def __init__(self: object, ptn: Pattern) -> None: pass

        ##
        # \brief Initializes the \e %Pattern instance.
        # \param self The \e %Pattern instance to initialize.
        # \param structure 
        # \param id 
        # \param priority 
        # \param all_matches 
        # \param unique_matches 
        #
        def __init__(self: object, structure: MolecularGraph, id: int, priority: int = 0, all_matches: bool = True, unique_matches: bool = True) -> None: pass

        ##
        # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
        # \param self The \e %Pattern instance this method is called upon.
        #
        # Different Python \e %Pattern instances may reference the same underlying C++ class instance. The commonly used Python expression
        # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %Pattern instances \e a and \e b reference different C++ objects. 
        # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
        # <tt>a.getObjectID() != b.getObjectID()</tt>.
        #
        # \return The numeric ID of the internally referenced C++ class instance.
        #
        def getObjectID(self: Pattern) -> int: pass

        ##
        # \brief Replaces the current state of \a self with a copy of the state of the \e %Pattern instance \a ptn.
        # \param self The \e %Pattern instance this method is called upon.
        # \param ptn The \e %Pattern instance to copy.
        # \return The assignment target \a self.
        #
        def assign(self: Pattern, ptn: Pattern) -> Pattern: pass

        ##
        # \brief 
        # \param self The \e %Pattern instance this method is called upon.
        # \return 
        #
        def getStructure(self: Pattern) -> MolecularGraph: pass

        ##
        # \brief 
        # \param self The \e %Pattern instance this method is called upon.
        # \return 
        #
        def getPriority(self: Pattern) -> int: pass

        ##
        # \brief 
        # \param self The \e %Pattern instance this method is called upon.
        # \return 
        #
        def getID(self: Pattern) -> int: pass

        ##
        # \brief 
        # \param self The \e %Pattern instance this method is called upon.
        # \return 
        #
        def processAllMatches(self: Pattern) -> bool: pass

        ##
        # \brief 
        # \param self The \e %Pattern instance this method is called upon.
        # \return 
        #
        def processUniqueMatchesOnly(self: Pattern) -> bool: pass

        ##
        # \brief 
        #
        objectID = property(getObjectID)

        ##
        # \brief 
        #
        structure = property(getStructure)

        ##
        # \brief 
        #
        priority = property(getPriority)

        ##
        # \brief FIXME!
        #
        id = property(getId)

        ##
        # \brief FIXME!
        #
        allMatches = property(getAllMatches)

        ##
        # \brief FIXME!
        #
        uniqueMatches = property(getUniqueMatches)

    ##
    # \brief Initializes the \e %SubstructureHistogramGenerator instance.
    # \param self The \e %SubstructureHistogramGenerator instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %SubstructureHistogramGenerator instance.
    # \param self The \e %SubstructureHistogramGenerator instance to initialize.
    # \param generator 
    #
    def __init__(self: object, generator: SubstructureHistogramGenerator) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %SubstructureHistogramGenerator instance this method is called upon.
    #
    # Different Python \e %SubstructureHistogramGenerator instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %SubstructureHistogramGenerator instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: SubstructureHistogramGenerator) -> int: pass

    ##
    # \brief 
    # \param self The \e %SubstructureHistogramGenerator instance this method is called upon.
    # \param structure 
    # \param id 
    # \param priority 
    # \param all_matches 
    # \param unique_matches 
    #
    def addPattern(self: SubstructureHistogramGenerator, structure: MolecularGraph, id: int = 0, priority: int = 0, all_matches: bool = True, unique_matches: bool = True) -> None: pass

    ##
    # \brief 
    # \param self The \e %SubstructureHistogramGenerator instance this method is called upon.
    # \param ptn 
    #
    def addPattern(self: SubstructureHistogramGenerator, ptn: Pattern) -> None: pass

    ##
    # \brief 
    # \param self The \e %SubstructureHistogramGenerator instance this method is called upon.
    # \param idx 
    # \return 
    #
    def getPattern(self: SubstructureHistogramGenerator, idx: int) -> Pattern: pass

    ##
    # \brief 
    # \param self The \e %SubstructureHistogramGenerator instance this method is called upon.
    # \param idx 
    #
    def removePattern(self: SubstructureHistogramGenerator, idx: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %SubstructureHistogramGenerator instance this method is called upon.
    #
    def clear(self: SubstructureHistogramGenerator) -> None: pass

    ##
    # \brief 
    # \param self The \e %SubstructureHistogramGenerator instance this method is called upon.
    # \return 
    #
    def getNumPatterns(self: SubstructureHistogramGenerator) -> int: pass

    ##
    # \brief 
    # \param self The \e %SubstructureHistogramGenerator instance this method is called upon.
    # \param molgraph 
    # \param histo 
    #
    def generate(self: SubstructureHistogramGenerator, molgraph: MolecularGraph, histo: object) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %SubstructureHistogramGenerator instance \a generator.
    # \param self The \e %SubstructureHistogramGenerator instance this method is called upon.
    # \param generator The \e %SubstructureHistogramGenerator instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: SubstructureHistogramGenerator, generator: SubstructureHistogramGenerator) -> SubstructureHistogramGenerator: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)

    ##
    # \brief 
    #
    numPatterns = property(getNumPatterns)
