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
# \brief Bundle of configuration parameters for ConfGen.FragmentAssembler.
# 
class FragmentAssemblerSettings(Boost.Python.instance):

    ##
    # \brief Default settings used by a freshly-constructed FragmentAssemblerSettings.
    # 
    DEFAULT = _HIDDEN_VALUE_

    ##
    # \brief Constructs the settings instance with default values.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \c %FragmentAssemblerSettings instance \a settings.
    # \param settings The \c %FragmentAssemblerSettings instance to copy.
    # 
    def __init__(settings: FragmentAssemblerSettings) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %FragmentAssemblerSettings instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %FragmentAssemblerSettings instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %FragmentAssemblerSettings instance \a settings.
    # \param settings The \c %FragmentAssemblerSettings instance to copy.
    # \return \a self
    # 
    def assign(settings: FragmentAssemblerSettings) -> FragmentAssemblerSettings: pass

    ##
    # \brief Specifies whether ring conformations shall be enumerated during fragment assembly.
    # 
    # \param enumerate If <tt>True</tt>, multiple ring conformations are emitted.
    # 
    def enumerateRings(enumerate: bool) -> None: pass

    ##
    # \brief Tells whether ring conformations are enumerated during fragment assembly.
    # 
    # \return <tt>True</tt> if ring conformations are enumerated, and <tt>False</tt> otherwise.
    # 
    def enumerateRings() -> bool: pass

    ##
    # \brief Sets the enumeration mode for stereogenic nitrogen centers.
    # 
    # \param mode One of the ConfGen.NitrogenEnumerationMode values.
    # 
    def setNitrogenEnumerationMode(mode: int) -> None: pass

    ##
    # \brief Returns the currently configured stereogenic-nitrogen enumeration mode.
    # 
    # \return One of the ConfGen.NitrogenEnumerationMode values.
    # 
    def getNitrogenEnumerationMode() -> int: pass

    ##
    # \brief 
    # \param reuse 
    #
    def generateCoordinatesFromScratch(reuse: bool) -> None: pass

    ##
    # \brief Tells whether 3D coordinates are generated from scratch.
    # 
    # \return <tt>True</tt> if 3D coordinates are always regenerated, and <tt>False</tt> otherwise.
    # 
    def generateCoordinatesFromScratch() -> bool: pass

    ##
    # \brief Returns a reference to the nested fragment-conformer build settings.
    # 
    # \return A reference to the build settings.
    # 
    def getFragmentBuildSettings() -> FragmentConformerGeneratorSettings: pass

    objectID = property(getObjectID)

    enumRings = property(enumerateRings, enumerateRings)

    nitrogenEnumMode = property(getNitrogenEnumerationMode, setNitrogenEnumerationMode)

    genCoordsFromScratch = property(generateCoordinatesFromScratch, generateCoordinatesFromScratch)

    fragmentBuildSettings = property(getFragmentBuildSettings)
