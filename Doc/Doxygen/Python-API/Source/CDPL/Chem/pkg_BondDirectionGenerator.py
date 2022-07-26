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
class BondDirectionGenerator(Boost.Python.instance):

    ##
    # \brief Initializes the \e %BondDirectionGenerator instance.
    # \param self The \e %BondDirectionGenerator instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %BondDirectionGenerator instance.
    # \param self The \e %BondDirectionGenerator instance to initialize.
    # \param molgraph 
    # \param dirs 
    #
    def __init__(self: object, molgraph: MolecularGraph, dirs: CDPL.Util.UIArray) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %BondDirectionGenerator instance this method is called upon.
    #
    # Different Python \e %BondDirectionGenerator instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %BondDirectionGenerator instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: BondDirectionGenerator) -> int: pass

    ##
    # \brief 
    # \param self The \e %BondDirectionGenerator instance this method is called upon.
    # \param include 
    #
    def includeRingBonds(self: BondDirectionGenerator, include: bool) -> None: pass

    ##
    # \brief 
    # \param self The \e %BondDirectionGenerator instance this method is called upon.
    # \return 
    #
    def ringBondsIncluded(self: BondDirectionGenerator) -> bool: pass

    ##
    # \brief 
    # \param self The \e %BondDirectionGenerator instance this method is called upon.
    # \param min_size 
    #
    def setRingSizeLimit(self: BondDirectionGenerator, min_size: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %BondDirectionGenerator instance this method is called upon.
    # \return 
    #
    def getRingSizeLimit(self: BondDirectionGenerator) -> int: pass

    ##
    # \brief 
    # \param self The \e %BondDirectionGenerator instance this method is called upon.
    # \param molgraph 
    # \param dirs 
    #
    def generate(self: BondDirectionGenerator, molgraph: MolecularGraph, dirs: CDPL.Util.UIArray) -> None: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)

    ##
    # \brief 
    #
    ringSizeLimit = property(getRingSizeLimit, setRingSizeLimit)

    ##
    # \brief FIXME!
    #
    ringBonds = property(getRingBonds, setRingBonds)
