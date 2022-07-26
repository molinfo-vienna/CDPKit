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
class TorsionRule(Boost.Python.instance):

    ##
    # \brief 
    #
    class AngleEntry(Boost.Python.instance):

        ##
        # \brief Initializes the \e %AngleEntry instance.
        # \param self The \e %AngleEntry instance to initialize.
        # \param ang 
        # \param tol1 
        # \param tol2 
        # \param score 
        #
        def __init__(self: object, ang: float, tol1: float, tol2: float, score: float) -> None: pass

        ##
        # \brief Initializes the \e %AngleEntry instance.
        # \param self The \e %AngleEntry instance to initialize.
        # \param entry 
        #
        def __init__(self: object, entry: AngleEntry) -> None: pass

        ##
        # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
        # \param self The \e %AngleEntry instance this method is called upon.
        #
        # Different Python \e %AngleEntry instances may reference the same underlying C++ class instance. The commonly used Python expression
        # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %AngleEntry instances \e a and \e b reference different C++ objects. 
        # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
        # <tt>a.getObjectID() != b.getObjectID()</tt>.
        #
        # \return The numeric ID of the internally referenced C++ class instance.
        #
        def getObjectID(self: AngleEntry) -> int: pass

        ##
        # \brief Replaces the current state of \a self with a copy of the state of the \e %AngleEntry instance \a entry.
        # \param self The \e %AngleEntry instance this method is called upon.
        # \param entry The \e %AngleEntry instance to copy.
        # \return The assignment target \a self.
        #
        def assign(self: AngleEntry, entry: AngleEntry) -> AngleEntry: pass

        ##
        # \brief 
        # \param self The \e %AngleEntry instance this method is called upon.
        # \return 
        #
        def getAngle(self: AngleEntry) -> float: pass

        ##
        # \brief 
        # \param self The \e %AngleEntry instance this method is called upon.
        # \return 
        #
        def getScore(self: AngleEntry) -> float: pass

        ##
        # \brief 
        # \param self The \e %AngleEntry instance this method is called upon.
        # \return 
        #
        def getTolerance1(self: AngleEntry) -> float: pass

        ##
        # \brief 
        # \param self The \e %AngleEntry instance this method is called upon.
        # \return 
        #
        def getTolerance2(self: AngleEntry) -> float: pass

        ##
        # \brief 
        #
        objectID = property(getObjectID)

        ##
        # \brief 
        #
        angle = property(getAngle)

        ##
        # \brief 
        #
        score = property(getScore)

        ##
        # \brief 
        #
        tolerance1 = property(getTolerance1)

        ##
        # \brief 
        #
        tolerance2 = property(getTolerance2)

    ##
    # \brief Initializes the \e %TorsionRule instance.
    # \param self The \e %TorsionRule instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %TorsionRule instance.
    # \param self The \e %TorsionRule instance to initialize.
    # \param rule 
    #
    def __init__(self: object, rule: TorsionRule) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %TorsionRule instance this method is called upon.
    #
    # Different Python \e %TorsionRule instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %TorsionRule instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: TorsionRule) -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %TorsionRule instance \a rule.
    # \param self The \e %TorsionRule instance this method is called upon.
    # \param rule The \e %TorsionRule instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: TorsionRule, rule: TorsionRule) -> TorsionRule: pass

    ##
    # \brief 
    # \param self The \e %TorsionRule instance this method is called upon.
    # \return 
    #
    def getMatchPatternString(self: TorsionRule) -> str: pass

    ##
    # \brief 
    # \param self The \e %TorsionRule instance this method is called upon.
    # \param ptn_str 
    #
    def setMatchPatternString(self: TorsionRule, ptn_str: str) -> None: pass

    ##
    # \brief 
    # \param self The \e %TorsionRule instance this method is called upon.
    # \return 
    #
    def getMatchPattern(self: TorsionRule) -> CDPL.Chem.MolecularGraph: pass

    ##
    # \brief 
    # \param self The \e %TorsionRule instance this method is called upon.
    # \param ptn 
    #
    def setMatchPattern(self: TorsionRule, ptn: CDPL.Chem.MolecularGraph) -> None: pass

    ##
    # \brief 
    # \param self The \e %TorsionRule instance this method is called upon.
    # \return 
    #
    def getNumAngles(self: TorsionRule) -> int: pass

    ##
    # \brief 
    # \param self The \e %TorsionRule instance this method is called upon.
    # \param idx 
    # \return 
    #
    def getAngle(self: TorsionRule, idx: int) -> AngleEntry: pass

    ##
    # \brief 
    # \param self The \e %TorsionRule instance this method is called upon.
    # \param idx 
    #
    def removeAngle(self: TorsionRule, idx: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %TorsionRule instance this method is called upon.
    # \param ang_entry 
    #
    def addAngle(self: TorsionRule, ang_entry: AngleEntry) -> None: pass

    ##
    # \brief 
    # \param self The \e %TorsionRule instance this method is called upon.
    # \param ang 
    # \param tol1 
    # \param tol2 
    # \param score 
    #
    def addAngle(self: TorsionRule, ang: float, tol1: float, tol2: float, score: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %TorsionRule instance this method is called upon.
    #
    def clear(self: TorsionRule) -> None: pass

    ##
    # \brief 
    # \param self The \e %TorsionRule instance this method is called upon.
    # \param rule 
    #
    def swap(self: TorsionRule, rule: TorsionRule) -> None: pass

    ##
    # \brief 
    # \param self The \e %TorsionRule instance this method is called upon.
    # \return 
    #
    def __len__(self: TorsionRule) -> int: pass

    ##
    # \brief 
    # \param self The \e %TorsionRule instance this method is called upon.
    # \param idx 
    # \return 
    #
    def __getitem__(self: TorsionRule, idx: int) -> AngleEntry: pass

    ##
    # \brief 
    # \param self The \e %TorsionRule instance this method is called upon.
    # \param idx 
    #
    def __delitem__(self: TorsionRule, idx: int) -> None: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += ang_entry</tt>.
    # \param self The \e %TorsionRule instance acting as in-place addend.
    # \param ang_entry Specifies the second addend.
    # \return The updated \e %TorsionRule instance \a self.
    #
    def __iadd__(self: TorsionRule, ang_entry: AngleEntry) -> None: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)

    ##
    # \brief 
    #
    numAngles = property(getNumAngles)

    ##
    # \brief 
    #
    matchPatternString = property(getMatchPatternString, setMatchPatternString)

    ##
    # \brief 
    #
    matchPattern = property(getMatchPattern, setMatchPattern)
