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
class MMFF94VanDerWaalsParameterTable(Boost.Python.instance):

    ##
    # \brief 
    #
    class Entry(Boost.Python.instance):

        ##
        # \brief Initializes the \e %Entry instance.
        # 
        def __init__() -> None: pass

        ##
        # \brief Initializes the \e %Entry instance with a copy of the state of the \e %Entry instance \a entry.
        # \param entry The \e %Entry instance to copy.
        # 
        def __init__(entry: Entry) -> None: pass

        ##
        # \brief Initializes the \e %Entry instance.
        # \param atom_type 
        # \param atom_pol 
        # \param eff_el_num 
        # \param fact_a 
        # \param fact_g 
        # \param don_acc_type 
        # 
        def __init__(atom_type: int, atom_pol: float, eff_el_num: float, fact_a: float, fact_g: float, don_acc_type: HDonorAcceptorType) -> None: pass

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
        # \return \a self
        # 
        def assign(entry: Entry) -> Entry: pass

        ##
        # \brief 
        # \return 
        #
        def getAtomType() -> int: pass

        ##
        # \brief Returns the atomic polarizability parameter.
        # 
        # \return The atomic polarizability.
        # 
        def getAtomicPolarizability() -> float: pass

        ##
        # \brief Returns the Slater-Kirkwood effective number of valence electrons parameter.
        # 
        # \return The Slater-Kirkwood effective number of valence electrons.
        # 
        def getEffectiveElectronNumber() -> float: pass

        ##
        # \brief Returns the scaling factor A parameter.
        # 
        # \return The scaling factor A.
        # 
        def getFactorA() -> float: pass

        ##
        # \brief Returns the scaling factor G parameter.
        # 
        # \return The scaling factor G
        # 
        def getFactorG() -> float: pass

        ##
        # \brief 
        # \return 
        #
        def getHDonorAcceptorType() -> HDonorAcceptorType: pass

        ##
        # \brief 
        # \return 
        #
        def __nonzero__() -> bool: pass

        ##
        # \brief 
        # \return 
        #
        def __bool__() -> bool: pass

        objectID = property(getObjectID)

        atomType = property(getAtomType)

        atomicPolarizability = property(getAtomicPolarizability)

        ##
        # \brief FIXME!
        # \brief 
        #
        effElectronNumber = property(getEffElectronNumber)

        factorA = property(getFactorA)

        factorG = property(getFactorG)

        hDonorAcceptorType = property(getHDonorAcceptorType)

    ##
    # \brief Initializes the \e %MMFF94VanDerWaalsParameterTable instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %MMFF94VanDerWaalsParameterTable instance with a copy of the state of the \e %MMFF94VanDerWaalsParameterTable instance \a table.
    # \param table The \e %MMFF94VanDerWaalsParameterTable instance to copy.
    # 
    def __init__(table: MMFF94VanDerWaalsParameterTable) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \e %MMFF94VanDerWaalsParameterTable instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %MMFF94VanDerWaalsParameterTable instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief 
    # \param atom_type 
    # \param atom_pol 
    # \param eff_el_num 
    # \param fact_a 
    # \param fact_g 
    # \param don_acc_type 
    #
    def addEntry(atom_type: int, atom_pol: float, eff_el_num: float, fact_a: float, fact_g: float, don_acc_type: HDonorAcceptorType) -> None: pass

    ##
    # \brief 
    # \param atom_type 
    # \return 
    #
    def removeEntry(atom_type: int) -> bool: pass

    ##
    # \brief 
    # \param atom_type 
    # \return 
    #
    def getEntry(atom_type: int) -> Entry: pass

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
    # \param is 
    #
    def load(is: Base.IStream) -> None: pass

    ##
    # \brief 
    #
    def loadDefaults() -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %MMFF94VanDerWaalsParameterTable instance \a table.
    # \param table The \e %MMFF94VanDerWaalsParameterTable instance to copy.
    # \return \a self
    # 
    def assign(table: MMFF94VanDerWaalsParameterTable) -> MMFF94VanDerWaalsParameterTable: pass

    ##
    # \brief 
    # \param value 
    #
    def setExponent(value: float) -> None: pass

    ##
    # \brief 
    # \param value 
    #
    def setBeta(value: float) -> None: pass

    ##
    # \brief 
    # \param value 
    #
    def setFactorB(value: float) -> None: pass

    ##
    # \brief 
    # \param value 
    #
    def setFactorDARAD(value: float) -> None: pass

    ##
    # \brief 
    # \param value 
    #
    def setFactorDAEPS(value: float) -> None: pass

    ##
    # \brief Returns the exponent used in the calculation of van der Waals interaction energies.
    # 
    # \return The exponent.
    # 
    def getExponent() -> float: pass

    ##
    # \brief Returns the value of the <em>B</em> factor used in the calculation of van der Waals interaction energies.
    # 
    # \return The value of the <em>B</em> factor.
    # 
    def getFactorB() -> float: pass

    ##
    # \brief Returns the value of <em>beta</em> used in the calculation of van der Waals interaction energies.
    # 
    # \return The value of <em>beta</em>.
    # 
    def getBeta() -> float: pass

    ##
    # \brief Returns the value of the <em>DARAD</em> factor used in the calculation of van der Waals interaction energies.
    # 
    # \return The value of the <em>DARAD</em> factor.
    # 
    def getFactorDARAD() -> float: pass

    ##
    # \brief Returns the value of the <em>DAEPS</em> factor used in the calculation of van der Waals interaction energies.
    # 
    # \return The value of the <em>DAEPS</em> factor.
    # 
    def getFactorDAEPS() -> float: pass

    ##
    # \brief 
    # \param table 
    #
    @staticmethod
    def set(table: MMFF94VanDerWaalsParameterTable) -> None: pass

    ##
    # \brief 
    # \param  
    # \return 
    #
    @staticmethod
    def get(: ) -> MMFF94VanDerWaalsParameterTable: pass

    objectID = property(getObjectID)

    numEntries = property(getNumEntries)

    entries = property(getEntries)

    exponent = property(getExponent, setExponent)

    beta = property(getBeta, setBeta)

    factorB = property(getFactorB, setFactorB)

    factorDARAD = property(getFactorDARAD, setFactorDARAD)

    factorDAEPS = property(getFactorDAEPS, setFactorDAEPS)
