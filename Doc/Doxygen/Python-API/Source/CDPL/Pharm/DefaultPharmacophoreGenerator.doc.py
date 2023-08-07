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
# \brief DefaultPharmacophoreGenerator.
# 
class DefaultPharmacophoreGenerator(PharmacophoreGenerator):

    ##
    # \brief Flags controlling feature generation.
    # 
    class Configuration(Boost.Python.enum):

        ##
        # \brief If set, ionic features are only generated for explicitely charged atoms/groups.
        # 
        PI_NI_ON_CHARGED_GROUPS_ONLY = 1

        ##
        # \brief If set, the HBD feature representation will always be a defined vector from the hydrogen donor heavy atom to the hydrogen atom.
        # 
        STATIC_H_DONORS = 2

        ##
        # \brief Default configuration.
        # 
        DEFAULT_CONFIG = 0

    ##
    # \brief Constructs the <tt>DefaultPharmacophoreGenerator</tt> instance.
    # 
    def __init__(config: int = CDPL.Pharm.Configuration.DEFAULT_CONFIG) -> None: pass

    ##
    # \brief Perceives all pharmacophore features of the molecular graph a\ molgraph and adds them to the pharmacophore <em>pharm</em>.
    # 
    # \param molgraph The molecular graph for which to perceive the features.
    # \param pharm The output pharmacophore where to add the generated features.
    # \param config Feature generation configuration.
    # 
    def __init__(molgraph: Chem.MolecularGraph, pharm: Pharmacophore, config: int = CDPL.Pharm.Configuration.DEFAULT_CONFIG) -> None: pass

    ##
    # \brief Initializes a copy of the \e %DefaultPharmacophoreGenerator instance \a gen.
    # \param gen The \e %DefaultPharmacophoreGenerator instance to copy.
    # 
    def __init__(gen: DefaultPharmacophoreGenerator) -> None: pass

    ##
    # \brief 
    # \param config 
    #
    def applyConfiguration(config: int) -> None: pass
