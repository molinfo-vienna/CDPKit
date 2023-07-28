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
    # \brief Specifies the membership of an atom in aromatic rings.
    # 
    AROMATICITY = 128

    ##
    # \brief Specifies the generic type or element of an atom.
    # 
    TYPE = 2

    ##
    # \brief Specifies the <em>CIP</em>-configuration of a chiral atom.
    # 
    CIP_CONFIGURATION = 1

    ##
    # \brief Specifies the configuration of a stereogenic atom.
    # 
    CONFIGURATION = 256

    ##
    # \brief Specifies the formal charge of an atom.
    # 
    FORMAL_CHARGE = 8

    ##
    # \brief Specifies the hydrogen count of an atom.
    # 
    H_COUNT = 16

    ##
    # \brief Specifies the heavy bond count of an atom.
    # 
    HEAVY_BOND_COUNT = 1024

    ##
    # \brief Specifies the explicit bond count of an atom.
    # 
    EXPLICIT_BOND_COUNT = 4096

    ##
    # \brief Specifies the valence of an atom.
    # 
    VALENCE = 2048

    ##
    # \brief Specifies the isotopic mass of an atom.
    # 
    ISOTOPE = 4

    ##
    # \brief Specifies the symbol of an atom's element.
    # 
    SYMBOL = 32

    ##
    # \brief Specifies the ring/chain topology of an atom.
    # 
    TOPOLOGY = 64

    ##
    # \brief Specifies the hybridization state an atom.
    # 
    HYBRIDIZATION_STATE = 8192

    ##
    # \brief Specifies the atom-mapping ID an atom in a reaction.
    # 
    ATOM_MAPPING_ID = 512
