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
# \brief Bundle of configuration parameters for raw coordinates generation via class ConfGen.DGStructureGenerator.
# 
class DGStructureGeneratorSettings(DGConstraintGeneratorSettings):

    ##
    # \brief A static instance providing configuration parameter default values.
    # 
    DEFAULT_ = _HIDDEN_VALUE_

    ##
    # \brief Constructs the <tt>DGStructureGeneratorSettings</tt> instance with default configuration parameter values.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \c %DGStructureGeneratorSettings instance \a settings.
    # \param settings The \c %DGStructureGeneratorSettings instance to copy.
    # 
    def __init__(settings: DGStructureGeneratorSettings) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %DGStructureGeneratorSettings instance \a settings.
    # \param settings The \c %DGStructureGeneratorSettings instance to copy.
    # \return \a self
    # 
    def assign(settings: DGStructureGeneratorSettings) -> DGStructureGeneratorSettings: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %DGConstraintGeneratorSettings instance \a settings.
    # \param settings The \c %DGConstraintGeneratorSettings instance to copy.
    # \return \a self
    # 
    def assign(settings: DGConstraintGeneratorSettings) -> DGStructureGeneratorSettings: pass

    ##
    # \brief Sets the edge length of the bounding box used by the distance-geometry embedder.
    # 
    # \param size The new bounding-box edge length.
    # 
    def setBoxSize(size: float) -> None: pass

    ##
    # \brief Returns the edge length of the bounding box used by the distance-geometry embedder.
    # 
    # \return The bounding-box edge length.
    # 
    def getBoxSize() -> float: pass

    ##
    # \brief Specifies whether planarity (zero-volume) constraints shall be added for sp2 atoms and double/aromatic bonds.
    # 
    # \param enable If <tt>True</tt>, planarity constraints are added.
    # 
    def enablePlanarityConstraints(enable: bool) -> None: pass

    ##
    # \brief Tells whether planarity constraints are enabled.
    # 
    # \return <tt>True</tt> if planarity constraints are enabled, and <tt>False</tt> otherwise.
    # 
    def enablePlanarityConstraints() -> bool: pass

    boxSize = property(getBoxSize, setBoxSize)

    planarityConstraints = property(enablePlanarityConstraints, enablePlanarityConstraints)
