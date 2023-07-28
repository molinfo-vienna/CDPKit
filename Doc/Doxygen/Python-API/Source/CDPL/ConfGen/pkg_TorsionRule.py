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
        def __init__(ang: float, tol1: float, tol2: float, score: float) -> None: pass

        ##
        # \brief Initializes the \e %AngleEntry instance.
        # \param self The \e %AngleEntry instance to initialize.
        # \param entry 
        # 
        def __init__(entry: AngleEntry) -> None: pass

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
        def getObjectID() -> int: pass

        ##
        # \brief Replaces the current state of \a self with a copy of the state of the \e %AngleEntry instance \a entry.
        # \param self The \e %AngleEntry instance this method is called upon.
        # \param entry The \e %AngleEntry instance to copy.
        # \return \a self
        # 
        def assign(entry: AngleEntry) -> AngleEntry: pass

        ##
        # \brief 
        # \return 
        #
        def getAngle() -> float: pass

        ##
        # \brief 
        # \return 
        #
        def getScore() -> float: pass

        ##
        # \brief 
        # \return 
        #
        def getTolerance1() -> float: pass

        ##
        # \brief 
        # \return 
        #
        def getTolerance2() -> float: pass

        objectID = property(getObjectID)

        angle = property(getAngle)

        score = property(getScore)

        tolerance1 = property(getTolerance1)

        tolerance2 = property(getTolerance2)

    ##
    # \brief Initializes the \e %TorsionRule instance.
    # \param self The \e %TorsionRule instance to initialize.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %TorsionRule instance.
    # \param self The \e %TorsionRule instance to initialize.
    # \param rule 
    # 
    def __init__(rule: TorsionRule) -> None: pass

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
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %TorsionRule instance \a rule.
    # \param self The \e %TorsionRule instance this method is called upon.
    # \param rule The \e %TorsionRule instance to copy.
    # \return \a self
    # 
    def assign(rule: TorsionRule) -> TorsionRule: pass

    ##
    # \brief 
    # \return 
    #
    def getMatchPatternString() -> str: pass

    ##
    # \brief 
    # \param ptn_str 
    #
    def setMatchPatternString(ptn_str: str) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getMatchPattern() -> CDPL.Chem.MolecularGraph: pass

    ##
    # \brief 
    # \param ptn 
    #
    def setMatchPattern(ptn: CDPL.Chem.MolecularGraph) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getNumAngles() -> int: pass

    ##
    # \brief 
    # \param idx 
    # \return 
    #
    def getAngle(idx: int) -> AngleEntry: pass

    ##
    # \brief 
    # \param idx 
    #
    def removeAngle(idx: int) -> None: pass

    ##
    # \brief 
    # \param ang_entry 
    #
    def addAngle(ang_entry: AngleEntry) -> None: pass

    ##
    # \brief 
    # \param ang 
    # \param tol1 
    # \param tol2 
    # \param score 
    #
    def addAngle(ang: float, tol1: float, tol2: float, score: float) -> None: pass

    ##
    # \brief 
    #
    def clear() -> None: pass

    ##
    # \brief 
    # \param rule 
    #
    def swap(rule: TorsionRule) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def __len__() -> int: pass

    ##
    # \brief 
    # \param idx 
    # \return 
    #
    def __getitem__(idx: int) -> AngleEntry: pass

    ##
    # \brief 
    # \param idx 
    #
    def __delitem__(idx: int) -> None: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += ang_entry</tt>.
    # \param self The \e %TorsionRule instance acting as in-place addend.
    # \param ang_entry Specifies the second addend.
    # \return The updated \e %None instance \a self.
    # 
    def __iadd__(ang_entry: AngleEntry) -> None: pass

    objectID = property(getObjectID)

    numAngles = property(getNumAngles)

    matchPatternString = property(getMatchPatternString, setMatchPatternString)

    matchPattern = property(getMatchPattern, setMatchPattern)
