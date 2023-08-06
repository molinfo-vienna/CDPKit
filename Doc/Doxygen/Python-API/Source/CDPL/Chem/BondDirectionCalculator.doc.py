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
# \brief BondDirectionCalculator.
# 
# \see [\ref SMILES]
# 
class BondDirectionCalculator(Boost.Python.instance):

    ##
    # \brief Construcst the <tt>BondDirectionCalculator</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Constructs the <tt>BondDirectionCalculator</tt> instance and calculates direction flags for a minimum set of directional bonds that unambiguously define the configuration of double bonds in the molecular graph <em>molgraph</em>.
    # 
    # \param molgraph The molecular graph for which to calculate the bond direction flags.
    # \param dirs An array containing the calculated bond direction flags (possible values are defined as constants in namespace Chem.BondDirection). The directions are stored in the same order as the bonds appear in the bond list of the molecular graph (i.e. the direction flag of a bond is accessible via its index).
    # 
    def __init__(molgraph: MolecularGraph, dirs: Util.UIArray) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \e %BondDirectionCalculator instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %BondDirectionCalculator instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Allows to specify whether or not the configuration of ring double bonds shall also be regarded in the performed bond direction calculations.
    # 
    # \param include If <tt>True</tt>, ring double bond geometries will be taken into consideration and get ignored otherwise.
    # 
    # \note By default, the configuration of ring double bonds is taken into consideration. 
    # 
    # \see setRingSizeLimit()
    # 
    def includeRingBonds(include: bool) -> None: pass

    ##
    # \brief Tells whether the configuration of ring double bonds is also regarded in the performed bond direction calculations.
    # 
    # \return <tt>True</tt> if ring double bond geometries are taken into consideration, and <em>False</em> otherwise. 
    # 
    # \see setRingSizeLimit()
    # 
    def ringBondsIncluded() -> bool: pass

    ##
    # \brief Sets the minimum ring size that is required for ring double bonds to be considered in the performed bond direction calculations.
    # 
    # \param min_size The minimum required ring size.
    # 
    # \note The default minimum ring size is set to <em>8</em>. This settings is only effective when the general inclusion of ring double bonds is not disabled (see includeRingBonds()).
    # 
    def setRingSizeLimit(min_size: int) -> None: pass

    ##
    # \brief Returns the minimum ring size that is required for ring double bonds to be considered in the performed bond direction calculations.
    # 
    # \return The minimum required ring size.
    # 
    def getRingSizeLimit() -> int: pass

    ##
    # \brief Calculates direction flags for a minimum set of directional bonds that unambiguously define the configuration of double bonds in the molecular graph <em>molgraph</em>.
    # 
    # \param molgraph The molecular graph for which to calculate the bond direction flags.
    # \param dirs An array containing the calculated bond direction flags (possible values are defined as constants in namespace Chem.BondDirection). The directions are stored in the same order as the bonds appear in the bond list of the molecular graph (i.e. the direction flag of a bond is accessible via its index).
    # 
    def calculate(molgraph: MolecularGraph, dirs: Util.UIArray) -> None: pass

    objectID = property(getObjectID)

    ringSizeLimit = property(getRingSizeLimit, setRingSizeLimit)

    ##
    # \brief FIXME!
    #
    ringBonds = property(getRingBonds, setRingBonds)
