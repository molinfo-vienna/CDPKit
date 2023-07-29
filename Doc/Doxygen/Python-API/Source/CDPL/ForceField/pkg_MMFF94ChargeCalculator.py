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
class MMFF94ChargeCalculator(Boost.Python.instance):

    ##
    # \brief Initializes the \e %MMFF94ChargeCalculator instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %MMFF94ChargeCalculator instance.
    # \param calc 
    # 
    def __init__(calc: MMFF94ChargeCalculator) -> None: pass

    ##
    # \brief Initializes the \e %MMFF94ChargeCalculator instance.
    # \param molgraph 
    # \param charges 
    # \param strict 
    # 
    def __init__(molgraph: Chem.MolecularGraph, charges: Util.DArray, strict: bool) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \e %MMFF94ChargeCalculator instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %MMFF94ChargeCalculator instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief 
    # \param func 
    #
    def setAromaticRingSetFunction(func: MMFF94RingSetFunction) -> None: pass

    ##
    # \brief 
    # \param func 
    #
    def setNumericAtomTypeFunction(func: MMFF94NumericAtomTypeFunction) -> None: pass

    ##
    # \brief 
    # \param func 
    #
    def setSymbolicAtomTypeFunction(func: MMFF94SymbolicAtomTypeFunction) -> None: pass

    ##
    # \brief 
    # \param func 
    #
    def setBondTypeIndexFunction(func: MMFF94BondTypeIndexFunction) -> None: pass

    ##
    # \brief 
    # \param table 
    #
    def setAtomTypePropertyTable(table: MMFF94AtomTypePropertyTable) -> None: pass

    ##
    # \brief 
    # \param table 
    #
    def setFormalChargeDefinitionTable(table: MMFF94FormalAtomChargeDefinitionTable) -> None: pass

    ##
    # \brief 
    # \param table 
    #
    def setBondChargeIncrementTable(table: MMFF94BondChargeIncrementTable) -> None: pass

    ##
    # \brief 
    # \param table 
    #
    def setPartialBondChargeIncrementTable(table: MMFF94PartialBondChargeIncrementTable) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %MMFF94ChargeCalculator instance \a parameterizer.
    # \param parameterizer The \e %MMFF94ChargeCalculator instance to copy.
    # \return \a self
    # 
    def assign(parameterizer: MMFF94ChargeCalculator) -> MMFF94ChargeCalculator: pass

    ##
    # \brief Calculates MMFF94 partial charges for the atoms of a molecular graph.
    # 
    # The partial atomic charges are constructed from initial full or fractional formal atomic charges \f$ q_I^0 \f$ (usually zero, but, e.g., <em>+1/3</em> for guanidinium nitrogens) by adding contributions from bond charge increments \f$ w_{KI} \f$ which describe the polarity of the bonds to atom <em>i</em> from attached atoms <em>k</em>. Thus, \f$ w_{KI} \f$ is the contribution to the total charge on atom <em>i</em> of atom type <em>I</em> accumulated from, and at the expense of, its bonded neighbor <em>k</em> of atom type <em>K</em>. Specifically, MMFF computes \f$ q_i \f$ as
    # 
    # \f$ q_i = (1 - M_I \: u_I) \:q_I^0 + \sum (u_K \: q_K^0) + \sum w_{KI} \f$
    # 
    # where \f$ w_{KI} = -w_{IK} \f$ and where the sums on the right hand side run over the \f$ M_I = crd(I) \f$ atoms <em>k</em> of MMFF atom type <em>K</em> directly attached to atom <em>i</em> ( \f$ crd(I) \f$ comes from "MMFFPROP.PAR"). In this equation, \f$ q_I^0 \f$ and \f$ q_K^0 \f$ are the formal charges assigned in the atom typing procedure (usually, by subroutine XTYPE), and the sum of the first two terms gives the "effective" fractional formal atomic charge residing on atom <em>i</em>. This approach allows a formal atomic charge initially affixed by the atom-typing procedure (e.g., \f$ q_I^0 \f$) to be shared in a prescribed manner with the neighbors bonded to the atom in question. For example, for the series <em>PO4</em>(-3), <em>HPO4</em>(-2), <em>H2PO4-</em>, <em>H3P04</em>, it allows allows the partial charges on the terminal oxygens (each represented by the same numerical atom type, <em>"32"</em>) to vary in a way which properly reflects the partial charges obtained from fits to the <em>6-31G*</em> electrostatic potential. In particular, the difference between the resultant charges \f$ q_i \f$ calculated for the single terminal oxygen in <em>H3PO4</em> and for the four equivalent terminal oxygens in <em>PO4</em>(-3) comes to <em>-0.375</em>, half (because \f$ u_{32} = -0.5 \f$) the difference of <em>-0.75</em> in the \f$ q_K^0 \f$ charges (i.e., <em>0.00</em> and <em>-0.75</em>, respectively) and reasonably in accord with the difference of <em>-0.42</em> found by fitting the electrostatic potential.
    # 
    # \param molgraph The molecular graph for which to calculate partial atomic charges.
    # \param charges The output array storing the calculated partial charges.
    # \param strict If <tt>True</tt>, strict parameterization will be peformed that might fail.
    # 
    def calculate(molgraph: Chem.MolecularGraph, charges: Util.DArray, strict: bool) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getFormalCharges() -> Util.DArray: pass

    ##
    # \brief 
    # \param arg1 
    # \return 
    #
    def formalCharges() -> Util.DArray: pass

    objectID = property(getObjectID)
