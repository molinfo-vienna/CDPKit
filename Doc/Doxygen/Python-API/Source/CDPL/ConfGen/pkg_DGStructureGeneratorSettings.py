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
# \brief 
#
class DGStructureGeneratorSettings(DGConstraintGeneratorSettings):

    ##
    # \brief 
    #
    DEFAULT_ = _HIDDEN_VALUE_

    ##
    # \brief Initializes the \e %DGStructureGeneratorSettings instance.
    # \param self The \e %DGStructureGeneratorSettings instance to initialize.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %DGStructureGeneratorSettings instance.
    # \param self The \e %DGStructureGeneratorSettings instance to initialize.
    # \param settings 
    # 
    def __init__(settings: DGStructureGeneratorSettings) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %DGStructureGeneratorSettings instance \a settings.
    # \param self The \e %DGStructureGeneratorSettings instance this method is called upon.
    # \param settings The \e %DGStructureGeneratorSettings instance to copy.
    # \return \a self
    # 
    def assign(settings: DGStructureGeneratorSettings) -> DGStructureGeneratorSettings: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %DGConstraintGeneratorSettings instance \a settings.
    # \param self The \e %DGStructureGeneratorSettings instance this method is called upon.
    # \param settings The \e %DGConstraintGeneratorSettings instance to copy.
    # \return \a self
    # 
    def assign(settings: DGConstraintGeneratorSettings) -> DGStructureGeneratorSettings: pass

    ##
    # \brief 
    # \param size 
    #
    def setBoxSize(size: float) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getBoxSize() -> float: pass

    ##
    # \brief 
    # \param enable 
    #
    def enablePlanarityConstraints(enable: bool) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def enablePlanarityConstraints() -> bool: pass

    boxSize = property(getBoxSize, setBoxSize)

    ##
    # \brief FIXME!
    # \brief 
    #
    planarityConstraints = property(getPlanarityConstraints, setPlanarityConstraints)
