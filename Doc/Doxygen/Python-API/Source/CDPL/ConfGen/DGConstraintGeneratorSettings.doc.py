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
# \brief Bundle of configuration parameters for distance-geometry constraint generation via class ConfGen.DGConstraintGenerator.
# 
class DGConstraintGeneratorSettings(Boost.Python.instance):

    ##
    # \brief A static instance providing configuration parameter default values.
    # 
    DEFAULT = _HIDDEN_VALUE_

    ##
    # \brief Constructs the <tt>DGConstraintGeneratorSettings</tt> instance with default configuration parameter values.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \c %DGConstraintGeneratorSettings instance \a settings.
    # \param settings The \c %DGConstraintGeneratorSettings instance to copy.
    # 
    def __init__(settings: DGConstraintGeneratorSettings) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %DGConstraintGeneratorSettings instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %DGConstraintGeneratorSettings instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %DGConstraintGeneratorSettings instance \a settings.
    # \param settings The \c %DGConstraintGeneratorSettings instance to copy.
    # \return \a self
    # 
    def assign(settings: DGConstraintGeneratorSettings) -> DGConstraintGeneratorSettings: pass

    ##
    # \brief Specifies whether hydrogen atoms shall be excluded from the constraint set.
    # 
    # \param exclude If <tt>True</tt>, hydrogen atoms are skipped during constraint generation.
    # 
    def excludeHydrogens(exclude: bool) -> None: pass

    ##
    # \brief Tells whether hydrogen atoms are excluded from the constraint set.
    # 
    # \return <tt>True</tt> if hydrogens are excluded, and <tt>False</tt> otherwise.
    # 
    def excludeHydrogens() -> bool: pass

    ##
    # \brief Specifies whether atom stereo center configurations shall be enforced by volume constraints.
    # 
    # \param regard If <tt>True</tt>, atom-configuration constraints are added.
    # 
    def regardAtomConfiguration(regard: bool) -> None: pass

    ##
    # \brief Tells whether atom stereo center configurations are enforced.
    # 
    # \return <tt>True</tt> if atom-configuration constraints are added, and <tt>False</tt> otherwise.
    # 
    def regardAtomConfiguration() -> bool: pass

    ##
    # \brief Specifies whether bond stereo center configurations (cis/trans) shall be enforced.
    # 
    # \param regard If <tt>True</tt>, bond-configuration constraints are added.
    # 
    def regardBondConfiguration(regard: bool) -> None: pass

    ##
    # \brief Tells whether bond stereo center configurations are enforced.
    # 
    # \return <tt>True</tt> if bond-configuration constraints are added, and <tt>False</tt> otherwise.
    # 
    def regardBondConfiguration() -> bool: pass

    objectID = property(getObjectID)

    exclHydrogens = property(excludeHydrogens, excludeHydrogens)

    regardAtomConfig = property(regardAtomConfiguration, regardAtomConfiguration)

    regardBondConfig = property(regardBondConfiguration, regardBondConfiguration)
