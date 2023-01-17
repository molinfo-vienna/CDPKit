#
# This file is part of the Chemical Data Processing Toolkit
#
# Copyright (C) Thomas A. Seidel <thomas.seidel@univie.ac.at>
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
# \param sybyl_type 
# \return 
#
def sybylToAtomType(sybyl_type: int) -> int: pass

##
# \brief 
# \param sybyl_type 
# \return 
#
def sybylBondTypeToString(sybyl_type: int) -> str: pass

##
# \brief 
# \param sybyl_type 
# \return 
#
def sybylAtomTypeToString(sybyl_type: int) -> str: pass

##
# \brief 
# \param qry_type 
# \param tgt_type 
# \return 
#
def atomTypesMatch(qry_type: int, tgt_type: int) -> bool: pass
