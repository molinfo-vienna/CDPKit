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
class ProtonationStateStandardizer(Boost.Python.instance):

    ##
    # \brief 
    #
    class Flavor(Boost.Python.enum):

        ##
        # \brief MIN_CHARGED_ATOM_COUNT.
        #
        MIN_CHARGED_ATOM_COUNT = 0

        ##
        # \brief PHYSIOLOGICAL_CONDITION_STATE.
        #
        PHYSIOLOGICAL_CONDITION_STATE = 1

        ##
        # \brief MAX_CHARGE_COMPENSATION.
        #
        MAX_CHARGE_COMPENSATION = 2

    ##
    # \brief Initializes the \e %ProtonationStateStandardizer instance.
    #
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %ProtonationStateStandardizer instance.
    # \param standardizer 
    #
    def __init__(standardizer: ProtonationStateStandardizer) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    #
    # Different Python \e %ProtonationStateStandardizer instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %ProtonationStateStandardizer instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %ProtonationStateStandardizer instance \a standardizer.
    # \param standardizer The \e %ProtonationStateStandardizer instance to copy.
    # \return \a self
    #
    def assign(standardizer: ProtonationStateStandardizer) -> ProtonationStateStandardizer: pass

    ##
    # \brief 
    # \param mol 
    # \param flavor 
    # \return 
    #
    def standardize(mol: Molecule, flavor: Flavor) -> bool: pass

    ##
    # \brief 
    # \param mol 
    # \param std_mol 
    # \param flavor 
    # \return 
    #
    def standardize(mol: Molecule, std_mol: Molecule, flavor: Flavor) -> bool: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)
