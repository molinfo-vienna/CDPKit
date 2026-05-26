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
# \brief Adjusts the protonation state of a molecule (atom formal charges and bonded hydrogen counts) according to one of several pre-defined objectives.
# 
class ProtonationStateStandardizer(Boost.Python.instance):

    ##
    # \brief Selects the objective driving the protonation-state adjustment.
    # 
    class Flavor(Boost.Python.enum):

        ##
        # \brief Minimize the total number of formally charged atoms (neutralize where possible).
        # 
        MIN_CHARGED_ATOM_COUNT = 0

        ##
        # \brief Set the protonation state expected under physiological conditions (pH ~7.4).
        # 
        PHYSIOLOGICAL_CONDITION_STATE = 1

        ##
        # \brief Maximize the cancellation of opposite formal charges (neutralize zwitterion-like pairs).
        # 
        MAX_CHARGE_COMPENSATION = 2

    ##
    # \brief Constructs the <tt>ProtonationStateStandardizer</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Constructs a copy of the <tt>ProtonationStateStandardizer</tt> instance <em>standardizer</em>.
    # 
    # \param standardizer The <tt>ProtonationStateStandardizer</tt> to copy.
    # 
    def __init__(standardizer: ProtonationStateStandardizer) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %ProtonationStateStandardizer instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %ProtonationStateStandardizer instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the state of this standardizer by a copy of the state of <em>standardizer</em>.
    # 
    # \param standardizer The source <tt>ProtonationStateStandardizer</tt>.
    # 
    # \return \a self
    # 
    def assign(standardizer: ProtonationStateStandardizer) -> ProtonationStateStandardizer: pass

    ##
    # \brief Adjusts the protonation state of <em>mol</em> in place according to the selected <em>flavor</em>.
    # 
    # \param mol The molecule to standardize (modified in place).
    # \param flavor The protonation-state objective.
    # 
    # \return <tt>True</tt> if the molecule was modified, and <tt>False</tt> otherwise.
    # 
    def standardize(mol: Molecule, flavor: Flavor) -> bool: pass

    ##
    # \brief Writes a standardized copy of <em>mol</em> to <em>std_mol</em> without modifying <em>mol</em>.
    # 
    # \param mol The input molecule.
    # \param std_mol The output molecule receiving the standardized copy.
    # \param flavor The protonation-state objective.
    # 
    # \return <tt>True</tt> if the output differs from the input, and <tt>False</tt> otherwise.
    # 
    def standardize(mol: Molecule, std_mol: Molecule, flavor: Flavor) -> bool: pass

    objectID = property(getObjectID)
