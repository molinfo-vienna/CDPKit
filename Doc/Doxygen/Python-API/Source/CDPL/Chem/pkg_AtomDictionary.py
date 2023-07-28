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
# \brief A global dictionary for the lookup of meta-data associated with the atom types defined in namespace Chem.AtomType.
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
        def __init__() -> None: pass

        ##
        # \brief Initializes the \e %Entry instance.
        # \param self The \e %Entry instance to initialize.
        # \param entry 
        # 
        def __init__(entry: Entry) -> None: pass

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
        # \param self The \e %Entry instance this method is called upon.
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
        # \brief 
        # \param entry 
        # \return 
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

        objectID = property(getObjectID)

        type = property(getType)

        isotope = property(getIsotope)

        name = property(getName)

        symbol = property(getSymbol)

        mostAbundantIsotope = property(getMostAbundantIsotope)

        averageWeight = property(getAverageWeight)

        IUPACGroup = property(getIUPACGroup)

        period = property(getPeriod)

        ##
        # \brief FIXME!
        # \brief 
        #
        metal = property(getMetal)

        ##
        # \brief FIXME!
        # \brief 
        #
        nonMetal = property(getNonMetal)

        valenceStates = property(getValenceStates)

        VdWRadius = property(getVdWRadius)

        AllredRochowElectronegativity = property(getAllredRochowElectronegativity)

        isotopeMasses = property(getIsotopeMasses)

    ##
    # \brief Initializes the \e %AtomDictionary instance.
    # \param self The \e %AtomDictionary instance to initialize.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %AtomDictionary instance.
    # \param self The \e %AtomDictionary instance to initialize.
    # \param dict 
    # 
    def __init__(dict: AtomDictionary) -> None: pass

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
    # \brief 
    # \param dict 
    # \return 
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
    # \brief Returns the symbol that is associated with the specified atom type and isotope.
    # 
    # The <em>isotope</em> argument has only an effect for hydrogen whose isotopes have different symbols (D for <em>Deuterium</em> and T for <em>Tritium</em>).
    # 
    # \param type The atom type.
    # \param isotope The mass number of the isotope, or <em>0</em> if not specified.
    # 
    # \return The atom type symbol, or an empty string if the symbol for the specified type and isotope is not available.
    # 
    @staticmethod
    def getSymbol(type: int, isotope: int = 0) -> str: pass

    ##
    # \brief Returns the name of the chemical element that is associated with the specified atom type and isotope.
    # 
    # The <em>isotope</em> argument has only an effect for hydrogen whose isotopes are named differently (<em>Deuterium</em> and <em>Tritium</em>).
    # 
    # \param type The atom type specifying the chemical element.
    # \param isotope The mass number of the element's isotope, or <em>0</em> if not specified.
    # 
    # \return The name of the element isotope, or an empty string if <em>type</em> does not specify a supported chemical element.
    # 
    @staticmethod
    def getName(type: int, isotope: int = 0) -> str: pass

    ##
    # \brief Returns the numeric atom type that is associated with the specified atom type symbol.
    # 
    # \param symbol The atom type symbol.
    # \param strict If <tt>True</tt>, dictionary symbols strictly have to match the argument symbol. Otherwise, the symbols will be converted to upper-case before their comparison.
    # 
    # \return The numeric atom type, or AtomType.UNKNOWN if <em>symbol</em> does not specify a supported atom type.
    # 
    @staticmethod
    def getType(symbol: str, strict: bool = False) -> int: pass

    ##
    # \brief Returns the mass number of the most abundant isotope of the chemical element specified by <em>type</em>.
    # 
    # \param type The atom type specifying the chemical element.
    # 
    # \return The mass number of the most abundant isotope of the element, or <em>0</em> if <em>type</em> does not specify a supported chemical element.
    # 
    @staticmethod
    def getMostAbundantIsotope(type: int) -> int: pass

    ##
    # \brief Returns the IUPAC group of the chemical element specified by <em>type</em>.
    # 
    # \param type The atom type specifying the chemical element.
    # 
    # \return The IUPAC group of the element, or <em>0</em> if <em>type</em> does not specify a supported chemical element.
    # 
    @staticmethod
    def getIUPACGroup(type: int) -> int: pass

    ##
    # \brief Returns the period number of the chemical element specified by <em>type</em>.
    # 
    # \param type The atom type specifying the chemical element.
    # 
    # \return The period of the element, or <em>0</em> if <em>type</em> does not specify a supported chemical element.
    # 
    @staticmethod
    def getPeriod(type: int) -> int: pass

    ##
    # \brief Returns the number of valence electrons of the chemical element specified by <em>type</em>.
    # 
    # \param type The atom type specifying the chemical element.
    # 
    # \return The number of valence electrons, or <em>0</em> if <em>type</em> does not specify a supported chemical element.
    # 
    @staticmethod
    def getNumValenceElectrons(type: int) -> int: pass

    ##
    # \brief Returns the standard atomic weight or the relative isotopic mass of an isotope of the chemical element specified by <em>type</em>.
    # 
    # If the element isotope is left unspecified, i.e. the argument <em>isotope</em> is zero, then the standard atomic weight of the chemical element will be returned. If an isotope is specified and the exact relative isotopic mass of the specified isotope is not available, the relative isotopic mass is approximated by the provided mass number of the isotope.
    # 
    # \param type The atom type specifying the chemical element.
    # \param isotope The mass number of the element's isotope, or <em>0</em> if not specified.
    # 
    # \return The relative isotopic mass of the specified element isotope, or the standard atomic weight of the element if <em>isotope</em> is zero.
    # 
    @staticmethod
    def getAtomicWeight(type: int, isotope: int = 0) -> float: pass

    ##
    # \brief Returns the <em>van der Waals</em> radius of the chemical element specified by <em>type</em>.
    # 
    # \param type The atom type specifying the chemical element.
    # 
    # \return The <em>van der Waals</em> radius, or <em>0.0</em> if <em>type</em> does not specify a supported chemical element.
    # 
    @staticmethod
    def getVdWRadius(type: int) -> float: pass

    ##
    # \brief Returns the covalent radius of the chemical element specified by <em>type</em> for the given bond order.
    # 
    # \param type The atom type specifying the chemical element.
    # \param order The bond order.
    # 
    # \return The covalent radius for the specified bond order, or <em>0.0</em> if <em>type</em> does not specify a supported chemical element, <em>order</em> is not valid or the radius is unknown.
    # 
    @staticmethod
    def getCovalentRadius(type: int, order: int = 1) -> float: pass

    ##
    # \brief Returns the <em>Allred-Rochow</em> electronegativity of the chemical element specified by <em>type</em>.
    # 
    # \param type The atom type specifying the chemical element.
    # 
    # \return The <em>Allred-Rochow</em> electronegativity, or <em>0.0</em> if the electronegativity of the specified element is not available.
    # 
    @staticmethod
    def getAllredRochowElectronegativity(type: int) -> float: pass

    ##
    # \brief Returns an array with the valence states of the chemical element specified by <em>type</em>.
    # 
    # \param type The atom type specifying the chemical element.
    # 
    # \return An array with the valence states of the specified chemical element.
    # 
    @staticmethod
    def getValenceStates(type: int) -> CDPL.Util.STArray: pass

    ##
    # \brief Tells whether the specified atom type represents a chemical element.
    # 
    # \param type The atom type.
    # 
    # \return <tt>True</tt> if <em>type</em> specifies a chemical element, and <tt>False</tt> otherwise.
    # 
    @staticmethod
    def isChemicalElement(type: int) -> bool: pass

    ##
    # \brief Tells whether the chemical element specified by <em>type</em> is a main group element.
    # 
    # \param type The atom type specifying the chemical element.
    # 
    # \return <tt>True</tt> if <em>type</em> specifies a main group element, and <tt>False</tt> otherwise.
    # 
    @staticmethod
    def isMainGroupElement(type: int) -> bool: pass

    ##
    # \brief Tells whether the chemical element specified by <em>type</em> is a transition metal.
    # 
    # \param type The atom type specifying the chemical element.
    # 
    # \return <tt>True</tt> if <em>type</em> specifies a transition metal, and <tt>False</tt> otherwise.
    # 
    @staticmethod
    def isTransitionMetal(type: int) -> bool: pass

    ##
    # \brief Tells whether the chemical element specified by <em>type</em> is a metal.
    # 
    # \param type The atom type specifying the chemical element.
    # 
    # \return <tt>True</tt> if <em>type</em> specifies a metal, and <tt>False</tt> otherwise.
    # 
    @staticmethod
    def isMetal(type: int) -> bool: pass

    ##
    # \brief Tells whether the chemical element specified by <em>type</em> is a semi-metal.
    # 
    # \param type The atom type specifying the chemical element.
    # 
    # \return <tt>True</tt> if <em>type</em> specifies a semi-metal, and <tt>False</tt> otherwise.
    # 
    @staticmethod
    def isSemiMetal(type: int) -> bool: pass

    ##
    # \brief Tells whether the chemical element specified by <em>type</em> is a non-metal.
    # 
    # \param type The atom type specifying the chemical element.
    # 
    # \return <tt>True</tt> if <em>type</em> specifies a non-metal, and <tt>False</tt> otherwise.
    # 
    @staticmethod
    def isNonMetal(type: int) -> bool: pass

    ##
    # \brief Tells whether the chemical element specified by <em>type</em> is a halogen.
    # 
    # \param type The atom type specifying the chemical element.
    # 
    # \return <tt>True</tt> if <em>type</em> specifies a halogen, and <tt>False</tt> otherwise.
    # 
    @staticmethod
    def isHalogen(type: int) -> bool: pass

    ##
    # \brief Tells whether the chemical element specified by <em>type</em> is a noble gas.
    # 
    # \param type The atom type specifying the chemical element.
    # 
    # \return <tt>True</tt> if <em>type</em> specifies a noble gas, and <tt>False</tt> otherwise.
    # 
    @staticmethod
    def isNobleGas(type: int) -> bool: pass

    objectID = property(getObjectID)

    numEntries = property(getNumEntries)

    entries = property(getEntries)
