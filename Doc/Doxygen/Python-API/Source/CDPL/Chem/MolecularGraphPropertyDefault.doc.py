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
# \brief Provides default values for built-in Chem.MolecularGraph properties.
# 
class MolecularGraphPropertyDefault(Boost.Python.instance):

    ##
    # \brief Default value for the Chem.MolecularGraphProperty.NAME property.
    # 
    NAME = ''

    ##
    # \brief Default value for the Chem.MolecularGraphProperty.COMMENT property.
    # 
    COMMENT = ''

    ##
    # \brief Default value for the Chem.MolecularGraphProperty.STOICHIOMETRIC_NUMBER property.
    # 
    STOICHIOMETRIC_NUMBER = 1.0

    ##
    # \brief Default value for the Chem.MolecularGraphProperty.MATCH_CONSTRAINTS property.
    # 
    MATCH_CONSTRAINTS = MatchConstraintList()

    ##
    # \brief Default value for the Chem.MolecularGraphProperty.MDL_CTAB_VERSION property.
    # 
    MDL_CTAB_VERSION = 0

    ##
    # \brief Default value for the Chem.MolecularGraphProperty.MDL_PROGRAM_NAME property.
    # 
    MDL_PROGRAM_NAME = 'CDPL'

    ##
    # \brief Default value for the Chem.MolecularGraphProperty.MDL_USER_INITIALS property.
    # 
    MDL_USER_INITIALS = ''

    ##
    # \brief Default value for the Chem.MolecularGraphProperty.MDL_DIMENSIONALITY property.
    # 
    MDL_DIMENSIONALITY = 0

    ##
    # \brief Default value for the Chem.MolecularGraphProperty.MDL_ENERGY property.
    # 
    MDL_ENERGY = 0.0

    ##
    # \brief Default value for the Chem.MolecularGraphProperty.MDL_CHIRAL_FLAG property.
    # 
    MDL_CHIRAL_FLAG = False

    ##
    # \brief Default value for the Chem.MolecularGraphProperty.MDL_SCALING_FACTOR1 property.
    # 
    MDL_SCALING_FACTOR1 = 1

    ##
    # \brief Default value for the Chem.MolecularGraphProperty.MDL_SCALING_FACTOR2 property.
    # 
    MDL_SCALING_FACTOR2 = 1.0

    ##
    # \brief Default value for the Chem.MolecularGraphProperty.MOL2_MOLECULE_TYPE property.
    # 
    MOL2_MOLECULE_TYPE = 0

    ##
    # \brief Default value for the Chem.MolecularGraphProperty.MOL2_CHARGE_TYPE property.
    # 
    MOL2_CHARGE_TYPE = 0
