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
# \brief Provides keys for built-in MolProp.Atom properties.
# 
class AtomProperty(Boost.Python.instance):

    ##
    # \brief 
    #
    HYDROPHOBICITY = CDPL.Base.LookupKey('HYDROPHOBICITY')

    ##
    # \brief 
    #
    PEOE_SIGMA_CHARGE = CDPL.Base.LookupKey('PEOE_SIGMA_CHARGE')

    ##
    # \brief 
    #
    PEOE_SIGMA_ELECTRONEGATIVITY = CDPL.Base.LookupKey('PEOE_SIGMA_ELECTRONEGATIVITY')

    ##
    # \brief 
    #
    MHMO_PI_CHARGE = CDPL.Base.LookupKey('MHMO_PI_CHARGE')

    ##
    # \brief 
    #
    H_BOND_DONOR_TYPE = CDPL.Base.LookupKey('H_BOND_DONOR_TYPE')

    ##
    # \brief 
    #
    H_BOND_ACCEPTOR_TYPE = CDPL.Base.LookupKey('H_BOND_ACCEPTOR_TYPE')
