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
        #
        def __init__() -> None: pass

        ##
        # \brief Initializes the \e %Entry instance.
        # \param entry 
        #
        def __init__(entry: Entry) -> None: pass

        ##
        # \brief Initializes the \e %Entry instance.
        # \param atom_type 
        # \param iso 
        # \param sym 
        # \param name 
        # \param most_abdt_iso 
        # \param avg_weight 
        # \param iupac_grp 
        # \param period 
        # \param metal 
        # \param non_metal 
        # \param val_states 
        # \param vdw_rad 
        # \param cov_radii 
        # \param ar_eneg 
        # \param iso_masses 
        #
        def __init__(atom_type: int, iso: int, sym: str, name: str, most_abdt_iso: int, avg_weight: float, iupac_grp: int, period: int, metal: bool, non_metal: bool, val_states: object, vdw_rad: float, cov_radii: object, ar_eneg: float, iso_masses: object) -> None: pass

        ##
        # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
        #
        # Different Python \e %Entry instances may reference the same underlying C++ class instance. The commonly used Python expression
        # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %Entry instances \e a and \e b reference different C++ objects. 
        # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
        # <tt>a.getObjectID() != b.getObjectID()</tt>.
        #
        # \return The numeric ID of the internally referenced C++ class instance.
        #
        def getObjectID() -> int: pass

        ##
        # \brief Replaces the current state of \a self with a copy of the state of the \e %Entry instance \a entry.
        # \param entry The \e %Entry instance to copy.
        # \return The assignment target \a self.
        #
        def assign(entry: Entry) -> Entry: pass

        ##
        # \brief 
        # \return 
        #
        def getType() -> int: pass

        ##
        # \brief 
        # \return 
        #
        def getIsotope() -> int: pass

        ##
        # \brief 
        # \return 
        #
        def getName() -> str: pass

        ##
        # \brief 
        # \return 
        #
        def getSymbol() -> str: pass

        ##
        # \brief 
        # \return 
        #
        def getMostAbundantIsotope() -> int: pass

        ##
        # \brief 
        # \return 
        #
        def getAverageWeight() -> float: pass

        ##
        # \brief 
        # \return 
        #
        def getIUPACGroup() -> int: pass

        ##
        # \brief 
        # \return 
        #
        def getPeriod() -> int: pass

        ##
        # \brief 
        # \return 
        #
        def isMetal() -> bool: pass

        ##
        # \brief 
        # \return 
        #
        def isNonMetal() -> bool: pass

        ##
        # \brief 
        # \return 
        #
        def getValenceStates() -> CDPL.Util.STArray: pass

        ##
        # \brief 
        # \return 
        #
        def getVdWRadius() -> float: pass

        ##
        # \brief 
        # \param order 
        # \return 
        #
        def getCovalentRadius(order: int) -> float: pass

        ##
        # \brief 
        # \return 
        #
        def getAllredRochowElectronegativity() -> float: pass

        ##
        # \brief 
        # \return 
        #
        def getIsotopeMasses() -> dict: pass

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
        # \brief 
        #
        period = property(getPeriod)

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
    #
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %AtomDictionary instance.
    # \param dict 
    #
    def __init__(dict: AtomDictionary) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    #
    # Different Python \e %AtomDictionary instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %AtomDictionary instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID() -> int: pass

    ##
    # \brief 
    # \param entry 
    #
    def addEntry(entry: Entry) -> None: pass

    ##
    # \brief 
    # \param type 
    # \param isotope 
    # \return 
    #
    def containsEntry(type: int, isotope: int) -> bool: pass

    ##
    # \brief 
    # \param type 
    # \param isotope 
    #
    def removeEntry(type: int, isotope: int) -> None: pass

    ##
    # \brief 
    # \param type 
    # \param isotope 
    # \return 
    #
    def getEntry(type: int, isotope: int) -> Entry: pass

    ##
    # \brief 
    #
    def clear() -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getNumEntries() -> int: pass

    ##
    # \brief 
    # \return 
    #
    def getEntries() -> list: pass

    ##
    # \brief 
    #
    def loadDefaults() -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %AtomDictionary instance \a dict.
    # \param dict The \e %AtomDictionary instance to copy.
    # \return The assignment target \a self.
    #
    def assign(dict: AtomDictionary) -> AtomDictionary: pass

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
    def getPeriod(type: int) -> int: pass

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
