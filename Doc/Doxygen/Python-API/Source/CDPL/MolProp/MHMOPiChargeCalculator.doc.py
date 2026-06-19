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
# \brief Calculator that uses a Modified Hückel Molecular Orbital (MHMO) treatment to compute &pi;-electron densities, &pi;-charges, &pi;-bond orders and the total &pi;-electron energy of a molecular graph.
# 
# The calculator can either perceive the &pi;-electron systems of the molecular graph itself (via Chem.ElectronSystemList) or accept a pre-computed list of &pi;-systems. The MHMO parameter set follows the parameterization described in the PhD thesis of Thomas Kleinöder (Computer Chemistry Center, Univ. Erlangen-Nuremberg, 2005).
# 
# \see [\ref MHMO]
# 
class MHMOPiChargeCalculator(Boost.Python.instance):

    ##
    # \brief Constructs the <tt>MHMOPiChargeCalculator</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Constructs the <tt>MHMOPiChargeCalculator</tt> instance and performs the MHMO calculation for <em>molgraph</em>.
    # 
    # The &pi;-electron systems are perceived from <em>molgraph</em>.
    # 
    # \param molgraph The molecular graph for which to perform the MHMO calculation.
    # 
    def __init__(molgraph: Chem.MolecularGraph) -> None: pass

    ##
    # \brief Constructs the <tt>MHMOPiChargeCalculator</tt> instance and performs the MHMO calculation for the given &pi;-electron systems of <em>molgraph</em>.
    # 
    # \param pi_sys_list The list of &pi;-electron systems.
    # \param molgraph The molecular graph.
    # 
    def __init__(pi_sys_list: Chem.ElectronSystemList, molgraph: Chem.MolecularGraph) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %MHMOPiChargeCalculator instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %MHMOPiChargeCalculator instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Specifies whether the calculation shall use localized pi-bonds.
    # 
    # \param localized If <tt>True</tt>, conjugated &pi;-systems are treated as a set of localized pi-bonds.
    # 
    def localizedPiBonds(localized: bool) -> None: pass

    ##
    # \brief Specifies whether the calculation shall use localized pi-bonds.
    # 
    # \param localized If <tt>True</tt>, conjugated &pi;-systems are treated as a set of localized pi-bonds.
    # 
    def localizedPiBonds() -> bool: pass

    ##
    # \brief Performs the MHMO calculation for <em>molgraph</em>, perceiving the &pi;-electron systems on the fly.
    # 
    # \param molgraph The molecular graph for which to perform the MHMO calculation.
    # 
    def calculate(molgraph: Chem.MolecularGraph) -> None: pass

    ##
    # \brief Performs the MHMO calculation for the given &pi;-electron systems of <em>molgraph</em>.
    # 
    # \param pi_sys_list The list of &pi;-electron systems.
    # \param molgraph The molecular graph.
    # 
    def calculate(pi_sys_list: Chem.ElectronSystemList, molgraph: Chem.MolecularGraph) -> None: pass

    ##
    # \brief Returns the calculated &pi;-electron density of the atom at index <em>atom_idx</em>.
    # 
    # \param atom_idx The zero-based atom index.
    # 
    # \return The calculated &pi;-electron density. 
    # 
    # \throw Base.IndexError if <em>atom_idx</em> is out of bounds.
    # 
    def getElectronDensity(atom_idx: int) -> float: pass

    ##
    # \brief Returns the calculated &pi;-charge of the atom at index <em>atom_idx</em>.
    # 
    # \param atom_idx The zero-based atom index.
    # 
    # \return The calculated &pi;-charge. 
    # 
    # \throw Base.IndexError if <em>atom_idx</em> is out of bounds.
    # 
    def getCharge(atom_idx: int) -> float: pass

    ##
    # \brief Returns the calculated &pi;-bond order of the bond at index <em>bond_idx</em>.
    # 
    # \param bond_idx The zero-based bond index.
    # 
    # \return The calculated &pi;-bond order. 
    # 
    # \throw Base.IndexError if <em>bond_idx</em> is out of bounds.
    # 
    def getBondOrder(bond_idx: int) -> float: pass

    ##
    # \brief Returns the total &pi;-electron energy of the molecular graph from the last calculation.
    # 
    # \return The total &pi;-electron energy.
    # 
    def getEnergy() -> float: pass

    objectID = property(getObjectID)

    locPiBonds = property(localizedPiBonds, localizedPiBonds)

    energy = property(getEnergy)
