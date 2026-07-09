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
# \brief Data structure for the storage and lookup of MMFF94 interaction parameters.
# 
# In addition to the per-atom type entries, the table also stores the five global scalar parameters (exponent, B, beta, DARAD, DAEPS) used by the buffered 14-7 MMFF94 Van der Waals energy expression.
# 
# \see [\ref MMFF94]
# 
class MMFF94VanDerWaalsParameterTable(Boost.Python.instance):

    ##
    # \brief Data structure for the storage of values associated with a single table entry.
    # 
    class Entry(Boost.Python.instance):

        ##
        # \brief Constructs an empty (uninitialized) <tt>Entry</tt> instance.
        # 
        def __init__() -> None: pass

        ##
        # \brief Initializes a copy of the \c %Entry instance \a entry.
        # \param entry The \c %Entry instance to copy.
        # 
        def __init__(entry: Entry) -> None: pass

        ##
        # \brief Constructs an <tt>Entry</tt> instance storing the given values.
        # 
        # \param atom_type The numeric MMFF94 atom type.
        # \param atom_pol The atomic polarizability parameter.
        # \param eff_el_num The Slater-Kirkwood effective number of valence electrons.
        # \param fact_a The scaling factor <tt>A</tt>.
        # \param fact_g The scaling factor <tt>G</tt>.
        # \param don_acc_type The H-donor/-acceptor classification of the atom type.
        # 
        def __init__(atom_type: int, atom_pol: float, eff_el_num: float, fact_a: float, fact_g: float, don_acc_type: HDonorAcceptorType) -> None: pass

        ##
        # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
        # 
        # Different Python \c %Entry instances may reference the same underlying C++ class instance. The commonly used Python expression
        # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %Entry instances \e a and \e b reference different C++ objects. 
        # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
        # <tt>a.getObjectID() != b.getObjectID()</tt>.
        # 
        # \return The numeric ID of the internally referenced C++ class instance.
        # 
        def getObjectID() -> int: pass

        ##
        # \brief Replaces the current state of \a self with a copy of the state of the \c %Entry instance \a entry.
        # \param entry The \c %Entry instance to copy.
        # \return \a self
        # 
        def assign(entry: Entry) -> Entry: pass

        ##
        # \brief Returns the numeric MMFF94 atom type of the entry.
        # 
        # \return The numeric atom type.
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
        # \brief Returns the H-donor/-acceptor classification associated with the numeric MMFF94 atom type.
        # 
        # \return The H-donor/-acceptor classification.
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

        effElectronNumber = property(getEffectiveElectronNumber)

        factorA = property(getFactorA)

        factorG = property(getFactorG)

        hDonorAcceptorType = property(getHDonorAcceptorType)

    ##
    # \brief Constructs an empty <tt>MMFF94VanDerWaalsParameterTable</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \c %MMFF94VanDerWaalsParameterTable instance \a table.
    # \param table The \c %MMFF94VanDerWaalsParameterTable instance to copy.
    # 
    def __init__(table: MMFF94VanDerWaalsParameterTable) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %MMFF94VanDerWaalsParameterTable instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %MMFF94VanDerWaalsParameterTable instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Adds a new (or overwrites an existing) entry for the numeric MMFF94 atom type <em>atom_type</em> that stores the given parameter values.
    # 
    # \param atom_type The numeric MMFF94 atom type.
    # \param atom_pol The atomic polarizability parameter.
    # \param eff_el_num The Slater-Kirkwood effective number of valence electrons.
    # \param fact_a The scaling factor <tt>A</tt>.
    # \param fact_g The scaling factor <tt>G</tt>.
    # \param don_acc_type The H-donor/-acceptor classification of the atom type.
    # 
    def addEntry(atom_type: int, atom_pol: float, eff_el_num: float, fact_a: float, fact_g: float, don_acc_type: HDonorAcceptorType) -> None: pass

    ##
    # \brief Removes the entry for the numeric MMFF94 atom type <em>atom_type</em>.
    # 
    # \param atom_type The numeric MMFF94 atom type.
    # 
    # \return <tt>True</tt> if a matching entry was removed, and <tt>False</tt> if no such entry existed.
    # 
    def removeEntry(atom_type: int) -> bool: pass

    ##
    # \brief Returns the entry for the numeric MMFF94 atom type <em>atom_type</em>.
    # 
    # \param atom_type The numeric MMFF94 atom type.
    # 
    # \return A reference to the matching entry or to an uninitialized entry if no matching entry exists.
    # 
    def getEntry(atom_type: int) -> Entry: pass

    ##
    # \brief Removes all entries from the table.
    # 
    def clear() -> None: pass

    ##
    # \brief Returns the number of entries in the table.
    # 
    # \return The entry count.
    # 
    def getNumEntries() -> int: pass

    ##
    # \brief 
    # \return 
    #
    def getEntries() -> list: pass

    ##
    # \brief Loads table entries from the input stream <em>is</em>.
    # 
    # \param is The input stream to read from.
    # 
    def load(is: Base.IStream) -> None: pass

    ##
    # \brief Loads the built-in default MMFF94 Van der Waals parameter entries and global scalar parameters.
    # 
    def loadDefaults() -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %MMFF94VanDerWaalsParameterTable instance \a table.
    # \param table The \c %MMFF94VanDerWaalsParameterTable instance to copy.
    # \return \a self
    # 
    def assign(table: MMFF94VanDerWaalsParameterTable) -> MMFF94VanDerWaalsParameterTable: pass

    ##
    # \brief Sets the global exponent used in the buffered 14-7 Van der Waals energy expression.
    # 
    # \param value The new exponent value.
    # 
    def setExponent(value: float) -> None: pass

    ##
    # \brief Sets the global <em>beta</em> value used in the buffered 14-7 Van der Waals energy expression.
    # 
    # \param value The new <em>beta</em> value.
    # 
    def setBeta(value: float) -> None: pass

    ##
    # \brief Sets the global <em>B</em> factor used in the buffered 14-7 Van der Waals energy expression.
    # 
    # \param value The new <em>B</em> factor value.
    # 
    def setFactorB(value: float) -> None: pass

    ##
    # \brief Sets the global <em>DARAD</em> factor used in the buffered 14-7 Van der Waals energy expression.
    # 
    # \param value The new <em>DARAD</em> factor value.
    # 
    def setFactorDARAD(value: float) -> None: pass

    ##
    # \brief Sets the global <em>DAEPS</em> factor used in the buffered 14-7 Van der Waals energy expression.
    # 
    # \param value The new <em>DAEPS</em> factor value.
    # 
    def setFactorDAEPS(value: float) -> None: pass

    ##
    # \brief Returns the exponent used in the calculation of Van der Waals interaction energies.
    # 
    # \return The exponent.
    # 
    def getExponent() -> float: pass

    ##
    # \brief Returns the value of the <em>B</em> factor used in the calculation of Van der Waals interaction energies.
    # 
    # \return The value of the <em>B</em> factor.
    # 
    def getFactorB() -> float: pass

    ##
    # \brief Returns the value of <em>beta</em> used in the calculation of Van der Waals interaction energies.
    # 
    # \return The value of <em>beta</em>.
    # 
    def getBeta() -> float: pass

    ##
    # \brief Returns the value of the <em>DARAD</em> factor used in the calculation of Van der Waals interaction energies.
    # 
    # \return The value of the <em>DARAD</em> factor.
    # 
    def getFactorDARAD() -> float: pass

    ##
    # \brief Returns the value of the <em>DAEPS</em> factor used in the calculation of Van der Waals interaction energies.
    # 
    # \return The value of the <em>DAEPS</em> factor.
    # 
    def getFactorDAEPS() -> float: pass

    ##
    # \brief Replaces the process-wide default table by <em>table</em>.
    # 
    # \param table The new default table (<tt>None</tt> resets to the built-in default).
    # 
    @staticmethod
    def set(table: MMFF94VanDerWaalsParameterTable) -> None: pass

    ##
    # \brief Returns the process-wide default table (lazily initialized on first call).
    # 
    # \return A shared reference to the default table.
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
