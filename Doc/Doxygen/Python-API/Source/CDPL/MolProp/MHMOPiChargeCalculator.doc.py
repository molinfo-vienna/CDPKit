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
# \brief MHMOPiChargeCalculator.
# 
# \see [\ref MHMO]
# 
class MHMOPiChargeCalculator(Boost.Python.instance):

    ##
    # \brief Initializes the \e %MHMOPiChargeCalculator instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %MHMOPiChargeCalculator instance.
    # \param molgraph 
    # 
    def __init__(molgraph: Chem.MolecularGraph) -> None: pass

    ##
    # \brief Initializes the \e %MHMOPiChargeCalculator instance.
    # \param pi_sys_list 
    # \param molgraph 
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
    # \brief 
    # \param localized 
    #
    def localizedPiBonds(localized: bool) -> None: pass

    ##
    # \brief 
    # \param localized 
    # \return 
    #
    def localizedPiBonds() -> bool: pass

    ##
    # \brief 
    # \param molgraph 
    #
    def calculate(molgraph: Chem.MolecularGraph) -> None: pass

    ##
    # \brief 
    # \param pi_sys_list 
    # \param molgraph 
    #
    def calculate(pi_sys_list: Chem.ElectronSystemList, molgraph: Chem.MolecularGraph) -> None: pass

    ##
    # \brief 
    # \param atom_idx 
    # \return 
    #
    def getElectronDensity(atom_idx: int) -> float: pass

    ##
    # \brief 
    # \param atom_idx 
    # \return 
    #
    def getCharge(atom_idx: int) -> float: pass

    ##
    # \brief 
    # \param bond_idx 
    # \return 
    #
    def getBondOrder(bond_idx: int) -> float: pass

    ##
    # \brief 
    # \return 
    #
    def getEnergy() -> float: pass

    objectID = property(getObjectID)

    locPiBonds = property(localizedPiBonds, localizedPiBonds)

    energy = property(getEnergy)
