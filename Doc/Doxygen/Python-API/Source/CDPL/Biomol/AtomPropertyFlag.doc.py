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
# \brief Provides flags for the specification of basic Chem.Atom properties.
# 
class AtomPropertyFlag(Boost.Python.instance):

    ##
    # \brief Represents an empty set of atom properties.
    # 
    NONE = 0

    ##
    # \brief Represents the default set of atom properties.
    # 
    DEFAULT = 2147483648

    ##
    # \brief Flag indicating that the residue three-letter code identifies the atom's owning residue.
    # 
    RESIDUE_CODE = 1024

    ##
    # \brief Flag indicating that the residue sequence number identifies the atom's owning residue.
    # 
    RESIDUE_SEQ_NO = 2048

    ##
    # \brief Flag indicating that the residue insertion code identifies the atom's owning residue.
    # 
    RESIDUE_INS_CODE = 4096

    ##
    # \brief Flag indicating that the chain identifier identifies the atom's owning residue.
    # 
    CHAIN_ID = 8192

    ##
    # \brief Flag indicating that the PDB model number identifies the atom's owning residue.
    # 
    MODEL_NUMBER = 16384
