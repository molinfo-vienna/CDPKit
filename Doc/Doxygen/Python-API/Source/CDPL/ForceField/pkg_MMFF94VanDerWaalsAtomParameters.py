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
class MMFF94VanDerWaalsAtomParameters(Boost.Python.instance):

    ##
    # \brief Initializes the \e %MMFF94VanDerWaalsAtomParameters instance.
    # \param params 
    #
    def __init__(params: MMFF94VanDerWaalsAtomParameters) -> None: pass

    ##
    # \brief Initializes the \e %MMFF94VanDerWaalsAtomParameters instance.
    # \param atom_pol 
    # \param eff_el_num 
    # \param fact_a 
    # \param fact_g 
    # \param don_acc_type 
    #
    def __init__(atom_pol: float, eff_el_num: float, fact_a: float, fact_g: float, don_acc_type: HDonorAcceptorType) -> None: pass
