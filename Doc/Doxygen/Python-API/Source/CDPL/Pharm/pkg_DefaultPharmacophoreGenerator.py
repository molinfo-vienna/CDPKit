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
#
class DefaultPharmacophoreGenerator(PharmacophoreGenerator):

    ##
    # \brief 
    #
    class Configuration(Boost.Python.enum):

        ##
        # \brief PI_NI_ON_CHARGED_GROUPS_ONLY.
        #
        PI_NI_ON_CHARGED_GROUPS_ONLY = 1

        ##
        # \brief STATIC_H_DONORS.
        #
        STATIC_H_DONORS = 2

        ##
        # \brief DEFAULT_CONFIG.
        #
        DEFAULT_CONFIG = 0

    ##
    # \brief Initializes the \e %DefaultPharmacophoreGenerator instance.
    # \param config 
    #
    def __init__(config: Configuration = CDPL.Pharm.Configuration.DEFAULT_CONFIG) -> None: pass

    ##
    # \brief Initializes the \e %DefaultPharmacophoreGenerator instance.
    # \param molgraph 
    # \param pharm 
    # \param config 
    #
    def __init__(molgraph: CDPL.Chem.MolecularGraph, pharm: Pharmacophore, config: Configuration = CDPL.Pharm.Configuration.DEFAULT_CONFIG) -> None: pass

    ##
    # \brief Initializes the \e %DefaultPharmacophoreGenerator instance.
    # \param gen 
    #
    def __init__(gen: DefaultPharmacophoreGenerator) -> None: pass

    ##
    # \brief 
    # \param config 
    #
    def applyConfiguration(config: Configuration) -> None: pass
