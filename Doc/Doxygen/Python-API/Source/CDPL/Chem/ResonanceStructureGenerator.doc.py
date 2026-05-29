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
# \brief Enumerates the resonance structures of a molecular graph by redistributing &pi;-electrons across the resonance-active bonds.
# 
# For each generated resonance structure the per-atom formal charges and per-bond bond-orders are reported as a Chem.ResonanceStructureGenerator.StructureData record. Optional post-processing minimizes octet-rule violations, sp-hybridization-geometry violations, and 1,2-charge separations on adjacent carbon atoms.
# 
class ResonanceStructureGenerator(Boost.Python.instance):

    ##
    # \brief Holds the per-atom formal charges and per-bond bond-orders that define a single resonance structure.
    # 
    class StructureData(Boost.Python.instance):

        ##
        # \brief Initializes a copy of the \c %StructureData instance \a data.
        # \param data The \c %StructureData instance to copy.
        # 
        def __init__(data: StructureData) -> None: pass

        ##
        # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
        # 
        # Different Python \c %StructureData instances may reference the same underlying C++ class instance. The commonly used Python expression
        # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %StructureData instances \e a and \e b reference different C++ objects. 
        # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
        # <tt>a.getObjectID() != b.getObjectID()</tt>.
        # 
        # \return The numeric ID of the internally referenced C++ class instance.
        # 
        def getObjectID() -> int: pass

        ##
        # \brief Replaces the current state of \a self with a copy of the state of the \c %ResonanceStructureGenerator instance \a data.
        # \param data The \c %ResonanceStructureGenerator instance to copy.
        # \return \a self
        # 
        def assign(data: ResonanceStructureGenerator) -> ResonanceStructureGenerator: pass

        ##
        # \brief Returns the per-atom formal charges of this resonance structure.
        # 
        # \return A reference to the per-atom formal-charge array.
        # 
        def getAtomCharges() -> Util.LArray: pass

        ##
        # \brief Returns the per-bond bond-orders of this resonance structure.
        # 
        # \return A reference to the per-bond bond-order array.
        # 
        def getBondOrders() -> Util.STArray: pass

        objectID = property(getObjectID)

        atomCharges = property(getAtomCharges)

        bondOrders = property(getBondOrders)

    ##
    # \brief Constructs the <tt>ResonanceStructureGenerator</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Constructs a copy of the <tt>ResonanceStructureGenerator</tt> instance <em>gen</em>.
    # 
    # \param gen The <tt>ResonanceStructureGenerator</tt> to copy.
    # 
    def __init__(gen: ResonanceStructureGenerator) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %ResonanceStructureGenerator instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %ResonanceStructureGenerator instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the state of this generator by a copy of the state of <em>gen</em>.
    # 
    # \param gen The source <tt>ResonanceStructureGenerator</tt>.
    # 
    # \return \a self
    # 
    def assign(gen: ResonanceStructureGenerator) -> ResonanceStructureGenerator: pass

    ##
    # \brief Tells whether octet-rule violations are minimized.
    # 
    # \return <tt>True</tt> if octet-rule violations are minimized, and <tt>False</tt> otherwise.
    # 
    def octetRuleViolationsMinimized() -> bool: pass

    ##
    # \brief Specifies whether resonance structures violating the octet rule shall be filtered out.
    # 
    # \param minimize If <tt>True</tt>, structures with octet-rule violations on the configured atom types are minimized.
    # 
    def minimizeOctetRuleViolations(minimize: bool) -> None: pass

    ##
    # \brief Tells whether sp-hybridization-geometry violations are minimized.
    # 
    # \return <tt>True</tt> if sp-geometry violations are minimized, and <tt>False</tt> otherwise.
    # 
    def sp1GeometryViolationsMinimized() -> bool: pass

    ##
    # \brief Specifies whether resonance structures with sp-hybridization-geometry violations shall be filtered out.
    # 
    # \param minimize If <tt>True</tt>, sp-hybridization-geometry violations are minimized.
    # 
    def minimizeSP1GeometryViolations(minimize: bool) -> None: pass

    ##
    # \brief Tells whether 1,2-charge separations on adjacent carbon atoms are minimized.
    # 
    # \return <tt>True</tt> if 1,2-charged C&minus;C resonance forms are minimized, and <tt>False</tt> otherwise.
    # 
    def carbonBond12ChargesMinimized() -> bool: pass

    ##
    # \brief Specifies whether resonance structures with 1,2-charge separations on adjacent carbon atoms shall be filtered out.
    # 
    # \param minimize If <tt>True</tt>, 1,2-charged C&minus;C resonance forms are minimized.
    # 
    def minimizeCarbonBond12Charges(minimize: bool) -> None: pass

    ##
    # \brief Returns the bit mask of atom types subjected to the octet-rule check during minimization.
    # 
    # \return A reference to the bit mask (indexed by Chem.AtomType value).
    # 
    def getOctetRuleCheckAtomTypes() -> Util.BitSet: pass

    ##
    # \brief Returns the configured charge-count window size.
    # 
    # \return The charge-count window size.
    # 
    def getChargeCountWindow() -> int: pass

    ##
    # \brief Sets the maximum allowed difference between the lowest and highest formal-charge count of accepted resonance structures.
    # 
    # \param win_size The new charge-count window size.
    # 
    def setChargeCountWindow(win_size: int) -> None: pass

    ##
    # \brief Returns the upper limit on the number of resonance structures generated per molecule.
    # 
    # \return The output-structure limit.
    # 
    def getMaxNumGeneratedStructures() -> int: pass

    ##
    # \brief Sets the upper limit on the number of resonance structures generated per molecule.
    # 
    # \param max_num The new output-structure limit.
    # 
    def setMaxNumGeneratedStructures(max_num: int) -> None: pass

    ##
    # \brief Generates all unique resonance structures of the molecular graph <em>molgraph</em>.
    # 
    # \param molgraph The molecular graph for which to generate the resonance structures.
    # 
    def generate(molgraph: MolecularGraph) -> None: pass

    ##
    # \brief Returns the number of generated resonance structures.
    # 
    # \return The resonance-structure count.
    # 
    def getNumStructures() -> int: pass

    ##
    # \brief Returns the resonance-structure record at index <em>idx</em>.
    # 
    # \param idx The zero-based structure index.
    # 
    # \return A reference to the resonance-structure record. 
    # 
    # \throw Base.IndexError if the number of resonance structures is zero or <em>idx</em> is not in the range [0, getNumStructures() - 1].
    # 
    def getStructureData(idx: int) -> StructureData: pass

    ##
    # \brief 
    # \param idx 
    # \return 
    #
    def __getitem__(idx: int) -> StructureData: pass

    ##
    # \brief 
    # \return 
    #
    def __len__() -> int: pass

    objectID = property(getObjectID)

    numStructures = property(getNumStructures)

    minOctetRuleViolations = property(octetRuleViolationsMinimized, minimizeOctetRuleViolations)

    minSP1GeometryViolations = property(sp1GeometryViolationsMinimized, minimizeSP1GeometryViolations)

    minCarbonBond12Charges = property(carbonBond12ChargesMinimized, minimizeCarbonBond12Charges)

    octetRuleCheckAtomTypes = property(getOctetRuleCheckAtomTypes)

    chargeCountWindow = property(getChargeCountWindow, setChargeCountWindow)

    maxNumGeneratedStructures = property(getMaxNumGeneratedStructures, setMaxNumGeneratedStructures)
