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
# \brief ResonanceStructureGenerator.
# 
class ResonanceStructureGenerator(Boost.Python.instance):

    ##
    # \brief 
    #
    class StructureData(Boost.Python.instance):

        ##
        # \brief Initializes the \e %StructureData instance with a copy of the state of the \e %StructureData instance \a data.
        # \param data The \e %StructureData instance to copy.
        # 
        def __init__(data: StructureData) -> None: pass

        ##
        # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
        # 
        # Different Python \e %StructureData instances may reference the same underlying C++ class instance. The commonly used Python expression
        # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %StructureData instances \e a and \e b reference different C++ objects. 
        # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
        # <tt>a.getObjectID() != b.getObjectID()</tt>.
        # 
        # \return The numeric ID of the internally referenced C++ class instance.
        # 
        def getObjectID() -> int: pass

        ##
        # \brief Replaces the current state of \a self with a copy of the state of the \e %ResonanceStructureGenerator instance \a data.
        # \param data The \e %ResonanceStructureGenerator instance to copy.
        # \return \a self
        # 
        def assign(data: ResonanceStructureGenerator) -> ResonanceStructureGenerator: pass

        ##
        # \brief 
        # \return 
        #
        def getAtomCharges() -> Util.LArray: pass

        ##
        # \brief 
        # \return 
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
    # \brief Initializes the \e %ResonanceStructureGenerator instance with a copy of the state of the \e %ResonanceStructureGenerator instance \a gen.
    # \param gen The \e %ResonanceStructureGenerator instance to copy.
    # 
    def __init__(gen: ResonanceStructureGenerator) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \e %ResonanceStructureGenerator instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %ResonanceStructureGenerator instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %ResonanceStructureGenerator instance \a gen.
    # \param gen The \e %ResonanceStructureGenerator instance to copy.
    # \return \a self
    # 
    def assign(gen: ResonanceStructureGenerator) -> ResonanceStructureGenerator: pass

    ##
    # \brief 
    # \return 
    #
    def octetRuleViolationsMinimized() -> bool: pass

    ##
    # \brief 
    # \param minimize 
    #
    def minimizeOctetRuleViolations(minimize: bool) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def sp1GeometryViolationsMinimized() -> bool: pass

    ##
    # \brief 
    # \param minimize 
    #
    def minimizeSP1GeometryViolations(minimize: bool) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def carbonBond12ChargesMinimized() -> bool: pass

    ##
    # \brief 
    # \param minimize 
    #
    def minimizeCarbonBond12Charges(minimize: bool) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getOctetRuleCheckAtomTypes() -> Util.BitSet: pass

    ##
    # \brief 
    # \return 
    #
    def getChargeCountWindow() -> int: pass

    ##
    # \brief 
    # \param win_size 
    #
    def setChargeCountWindow(win_size: int) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getMaxNumGeneratedStructures() -> int: pass

    ##
    # \brief 
    # \param max_num 
    #
    def setMaxNumGeneratedStructures(max_num: int) -> None: pass

    ##
    # \brief Generates all unique resonanceStructures of the molecular graph <em>molgraph</em>.
    # 
    # \param molgraph The molecular graph for which to generate the resonanceStructures.
    # 
    def generate(molgraph: MolecularGraph) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getNumStructures() -> int: pass

    ##
    # \brief 
    # \param idx 
    # \return 
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

    ##
    # \brief FIXME!
    #
    minOctetRuleViolations = property(getMinOctetRuleViolations, setMinOctetRuleViolations)

    ##
    # \brief FIXME!
    #
    minSP1GeometryViolations = property(getMinSP1GeometryViolations, setMinSP1GeometryViolations)

    ##
    # \brief FIXME!
    #
    minCarbonBond12Charges = property(getMinCarbonBond12Charges, setMinCarbonBond12Charges)

    octetRuleCheckAtomTypes = property(getOctetRuleCheckAtomTypes)

    chargeCountWindow = property(getChargeCountWindow, setChargeCountWindow)

    maxNumGeneratedStructures = property(getMaxNumGeneratedStructures, setMaxNumGeneratedStructures)
