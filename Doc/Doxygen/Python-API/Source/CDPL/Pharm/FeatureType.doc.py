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
# \brief Provides constants for the specification of the generic type of a pharmacophore feature.
# 
class FeatureType(Boost.Python.instance):

    ##
    # \brief Specifies an unknown pharmacophore feature type.
    # 
    UNKNOWN = 0

    ##
    # \brief Specifies a hydrophobic feature.
    # 
    HYDROPHOBIC = 1

    ##
    # \brief Specifies an aromatic feature.
    # 
    AROMATIC = 2

    ##
    # \brief Specifies a negatively ionizable feature.
    # 
    NEGATIVE_IONIZABLE = 3

    ##
    # \brief Specifies a positively ionizable feature.
    # 
    POSITIVE_IONIZABLE = 4

    ##
    # \brief Specifies a hydrogen-bond donor feature.
    # 
    H_BOND_DONOR = 5

    ##
    # \brief Specifies a hydrogen-bond acceptor feature.
    # 
    H_BOND_ACCEPTOR = 6

    ##
    # \brief Specifies a halogen-bond donor feature.
    # 
    HALOGEN_BOND_DONOR = 7

    ##
    # \brief Specifies a halogen-bond acceptor feature.
    # 
    HALOGEN_BOND_ACCEPTOR = 8

    ##
    # \brief Specifies an excluded-volume feature.
    # 
    EXCLUSION_VOLUME = 9

    ##
    # \brief Specifies the highest feature type constant defined in this namespace.
    # 
    MAX_TYPE = 9
