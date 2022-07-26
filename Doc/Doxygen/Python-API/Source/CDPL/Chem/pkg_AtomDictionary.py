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
class AtomDictionary(Boost.Python.instance):

    ##
    # \brief 
    #
    class Entry(Boost.Python.instance):

        ##
        # \brief Initializes the \e %Entry instance.
        # \param self The \e %Entry instance to initialize.
        #
        def __init__(self: object) -> None: pass

        ##
        # \brief Initializes the \e %Entry instance.
        # \param self The \e %Entry instance to initialize.
        # \param entry 
        #
        def __init__(self: object, entry: Entry) -> None: pass

        ##
        # \brief Initializes the \e %Entry instance.
        # \param arg1 The \e %Entry instance to initialize.
        # \param atom_type 
        # \param iso 
        # \param sym 
        # \param name 
        # \param most_abdt_iso 
        # \param avg_weight 
        # \param iupac_grp 
        # \param metal 
        # \param non_metal 
        # \param val_states 
        # \param vdw_rad 
        # \param cov_radii 
        # \param ar_eneg 
        # \param iso_masses 
        #
        def __init__(arg1: object, atom_type: int, iso: int, sym: str, name: str, most_abdt_iso: int, avg_weight: float, iupac_grp: int, metal: bool, non_metal: bool, val_states: object, vdw_rad: float, cov_radii: object, ar_eneg: float, iso_masses: object) -> None: pass

        ##
        # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
        # \param self The \e %Entry instance this method is called upon.
        #
        # Different Python \e %Entry instances may reference the same underlying C++ class instance. The commonly used Python expression
        # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %Entry instances \e a and \e b reference different C++ objects. 
        # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
        # <tt>a.getObjectID() != b.getObjectID()</tt>.
        #
        # \return The numeric ID of the internally referenced C++ class instance.
        #
        def getObjectID(self: Entry) -> int: pass

        ##
        # \brief Replaces the current state of \a self with a copy of the state of the \e %Entry instance \a entry.
        # \param self The \e %Entry instance this method is called upon.
        # \param entry The \e %Entry instance to copy.
        # \return The assignment target \a self.
        #
        def assign(self: Entry, entry: Entry) -> Entry: pass

        ##
        # \brief 
        # \param self The \e %Entry instance this method is called upon.
        # \return 
        #
        def getType(self: Entry) -> int: pass

        ##
        # \brief 
        # \param self The \e %Entry instance this method is called upon.
        # \return 
        #
        def getIsotope(self: Entry) -> int: pass

        ##
        # \brief 
        # \param self The \e %Entry instance this method is called upon.
        # \return 
        #
        def getName(self: Entry) -> str: pass

        ##
        # \brief 
        # \param self The \e %Entry instance this method is called upon.
        # \return 
        #
        def getSymbol(self: Entry) -> str: pass

        ##
        # \brief 
        # \param self The \e %Entry instance this method is called upon.
        # \return 
        #
        def getMostAbundantIsotope(self: Entry) -> int: pass

        ##
        # \brief 
        # \param self The \e %Entry instance this method is called upon.
        # \return 
        #
        def getAverageWeight(self: Entry) -> float: pass

        ##
        # \brief 
        # \param self The \e %Entry instance this method is called upon.
        # \return 
        #
        def getIUPACGroup(self: Entry) -> int: pass

        ##
        # \brief 
        # \param self The \e %Entry instance this method is called upon.
        # \return 
        #
        def isMetal(self: Entry) -> bool: pass

        ##
        # \brief 
        # \param self The \e %Entry instance this method is called upon.
        # \return 
        #
        def isNonMetal(self: Entry) -> bool: pass

        ##
        # \brief 
        # \param self The \e %Entry instance this method is called upon.
        # \return 
        #
        def getValenceStates(self: Entry) -> CDPL.Util.STArray: pass

        ##
        # \brief 
        # \param self The \e %Entry instance this method is called upon.
        # \return 
        #
        def getVdWRadius(self: Entry) -> float: pass

        ##
        # \brief 
        # \param self The \e %Entry instance this method is called upon.
        # \param order 
        # \return 
        #
        def getCovalentRadius(self: Entry, order: int) -> float: pass

        ##
        # \brief 
        # \param self The \e %Entry instance this method is called upon.
        # \return 
        #
        def getAllredRochowElectronegativity(self: Entry) -> float: pass

        ##
        # \brief 
        # \param self The \e %Entry instance this method is called upon.
        # \return 
        #
        def getIsotopeMasses(self: Entry) -> dict: pass

        ##
        # \brief 
        #
        objectID = property(getObjectID)

        ##
        # \brief 
        #
        type = property(getType)

        ##
        # \brief 
        #
        isotope = property(getIsotope)

        ##
        # \brief 
        #
        name = property(getName)

        ##
        # \brief 
        #
        symbol = property(getSymbol)

        ##
        # \brief 
        #
        mostAbundantIsotope = property(getMostAbundantIsotope)

        ##
        # \brief 
        #
        averageWeight = property(getAverageWeight)

        ##
        # \brief 
        #
        IUPACGroup = property(getIUPACGroup)

        ##
        # \brief FIXME!
        #
        metal = property(getMetal)

        ##
        # \brief FIXME!
        #
        nonMetal = property(getNonMetal)

        ##
        # \brief 
        #
        valenceStates = property(getValenceStates)

        ##
        # \brief 
        #
        VdWRadius = property(getVdWRadius)

        ##
        # \brief 
        #
        AllredRochowElectronegativity = property(getAllredRochowElectronegativity)

        ##
        # \brief 
        #
        isotopeMasses = property(getIsotopeMasses)

    ##
    # \brief Initializes the \e %AtomDictionary instance.
    # \param self The \e %AtomDictionary instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %AtomDictionary instance.
    # \param self The \e %AtomDictionary instance to initialize.
    # \param dict 
    #
    def __init__(self: object, dict: AtomDictionary) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %AtomDictionary instance this method is called upon.
    #
    # Different Python \e %AtomDictionary instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %AtomDictionary instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: AtomDictionary) -> int: pass

    ##
    # \brief 
    # \param self The \e %AtomDictionary instance this method is called upon.
    # \param entry 
    #
    def addEntry(self: AtomDictionary, entry: Entry) -> None: pass

    ##
    # \brief 
    # \param self The \e %AtomDictionary instance this method is called upon.
    # \param type 
    # \param isotope 
    # \return 
    #
    def containsEntry(self: AtomDictionary, type: int, isotope: int) -> bool: pass

    ##
    # \brief 
    # \param self The \e %AtomDictionary instance this method is called upon.
    # \param type 
    # \param isotope 
    #
    def removeEntry(self: AtomDictionary, type: int, isotope: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %AtomDictionary instance this method is called upon.
    # \param type 
    # \param isotope 
    # \return 
    #
    def getEntry(self: AtomDictionary, type: int, isotope: int) -> Entry: pass

    ##
    # \brief 
    # \param self The \e %AtomDictionary instance this method is called upon.
    #
    def clear(self: AtomDictionary) -> None: pass

    ##
    # \brief 
    # \param self The \e %AtomDictionary instance this method is called upon.
    # \return 
    #
    def getNumEntries(self: AtomDictionary) -> int: pass

    ##
    # \brief 
    # \param self The \e %AtomDictionary instance this method is called upon.
    # \return 
    #
    def getEntries(self: AtomDictionary) -> list: pass

    ##
    # \brief 
    # \param self The \e %AtomDictionary instance this method is called upon.
    #
    def loadDefaults(self: AtomDictionary) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %AtomDictionary instance \a dict.
    # \param self The \e %AtomDictionary instance this method is called upon.
    # \param dict The \e %AtomDictionary instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: AtomDictionary, dict: AtomDictionary) -> AtomDictionary: pass

    ##
    # \brief 
    # \param dict 
    #
    @staticmethod
    def set(dict: AtomDictionary) -> None: pass

    ##
    # \brief 
    # \param  
    # \return 
    #
    @staticmethod
    def get(: ) -> AtomDictionary: pass

    ##
    # \brief 
    # \param type 
    # \param isotope 
    # \return 
    #
    @staticmethod
    def getSymbol(type: int, isotope: int = 0) -> str: pass

    ##
    # \brief 
    # \param type 
    # \param isotope 
    # \return 
    #
    @staticmethod
    def getName(type: int, isotope: int = 0) -> str: pass

    ##
    # \brief 
    # \param symbol 
    # \param strict 
    # \return 
    #
    @staticmethod
    def getType(symbol: str, strict: bool = False) -> int: pass

    ##
    # \brief 
    # \param type 
    # \return 
    #
    @staticmethod
    def getMostAbundantIsotope(type: int) -> int: pass

    ##
    # \brief 
    # \param type 
    # \return 
    #
    @staticmethod
    def getIUPACGroup(type: int) -> int: pass

    ##
    # \brief 
    # \param type 
    # \return 
    #
    @staticmethod
    def getNumValenceElectrons(type: int) -> int: pass

    ##
    # \brief 
    # \param type 
    # \param isotope 
    # \return 
    #
    @staticmethod
    def getAtomicWeight(type: int, isotope: int = 0) -> float: pass

    ##
    # \brief 
    # \param type 
    # \return 
    #
    @staticmethod
    def getVdWRadius(type: int) -> float: pass

    ##
    # \brief 
    # \param type 
    # \param order 
    # \return 
    #
    @staticmethod
    def getCovalentRadius(type: int, order: int = 1) -> float: pass

    ##
    # \brief 
    # \param type 
    # \return 
    #
    @staticmethod
    def getAllredRochowElectronegativity(type: int) -> float: pass

    ##
    # \brief 
    # \param type 
    # \return 
    #
    @staticmethod
    def getValenceStates(type: int) -> CDPL.Util.STArray: pass

    ##
    # \brief 
    # \param type 
    # \return 
    #
    @staticmethod
    def isChemicalElement(type: int) -> bool: pass

    ##
    # \brief 
    # \param type 
    # \return 
    #
    @staticmethod
    def isMainGroupElement(type: int) -> bool: pass

    ##
    # \brief 
    # \param type 
    # \return 
    #
    @staticmethod
    def isTransitionMetal(type: int) -> bool: pass

    ##
    # \brief 
    # \param type 
    # \return 
    #
    @staticmethod
    def isMetal(type: int) -> bool: pass

    ##
    # \brief 
    # \param type 
    # \return 
    #
    @staticmethod
    def isSemiMetal(type: int) -> bool: pass

    ##
    # \brief 
    # \param type 
    # \return 
    #
    @staticmethod
    def isNonMetal(type: int) -> bool: pass

    ##
    # \brief 
    # \param type 
    # \return 
    #
    @staticmethod
    def isHalogen(type: int) -> bool: pass

    ##
    # \brief 
    # \param type 
    # \return 
    #
    @staticmethod
    def isNobleGas(type: int) -> bool: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)

    ##
    # \brief 
    #
    numEntries = property(getNumEntries)

    ##
    # \brief 
    #
    entries = property(getEntries)
