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
# \brief High-level driver for the generation of low-energy conformer ensembles of molecular graphs.
# 
# The generator implements two complementary sampling strategies for producing the conformer ensemble: 
#  - a systematic strategy that performs a fragment-based 3D structure generation followed by exhaustive torsion-driving of all rotatable bonds, and
#  - a stochastic strategy that picks conformations randomly from the conformational space of the molecule (by default used only for flexible macrocyclic molecules).
# 
# Both strategies share a common downstream pipeline of MMFF94-based energy minimization, RMSD-based clustering and energy window filtering. Behaviour is controlled by the embedded conformer generation settings instance, the configured fragment and torsion libraries and the optional abort/timeout/log callbacks.
# 
# \see [\ref CFRG]
# 
class ConformerGenerator(Boost.Python.instance):

    ##
    # \brief Constructs the <tt>ConformerGenerator</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %ConformerGenerator instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %ConformerGenerator instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Returns the current generator settings (mutable).
    # 
    # \return A reference to the settings.
    # 
    def getSettings() -> ConformerGeneratorSettings: pass

    ##
    # \brief Removes all configured fragment libraries.
    # 
    def clearFragmentLibraries() -> None: pass

    ##
    # \brief Adds <em>lib</em> to the list of fragment libraries consulted during fragment-based 3D structure generation.
    # 
    # \param lib The fragment library to add.
    # 
    def addFragmentLibrary(lib: FragmentLibrary) -> None: pass

    ##
    # \brief Removes all configured torsion libraries.
    # 
    def clearTorsionLibraries() -> None: pass

    ##
    # \brief Adds <em>lib</em> to the list of torsion libraries consulted during torsion driving.
    # 
    # \param lib The torsion library to add.
    # 
    def addTorsionLibrary(lib: TorsionLibrary) -> None: pass

    ##
    # \brief Sets the callback invoked periodically to allow the generation to be aborted by the user.
    # 
    # \param func The abort-check callback.
    # 
    def setAbortCallback(func: CallbackFunction) -> None: pass

    ##
    # \brief Returns the currently configured abort-check callback.
    # 
    # \return A reference to the abort-check callback.
    # 
    def getAbortCallback() -> CallbackFunction: pass

    ##
    # \brief Sets the callback invoked periodically to check whether the configured timeout has elapsed.
    # 
    # \param func The timeout-check callback.
    # 
    def setTimeoutCallback(func: CallbackFunction) -> None: pass

    ##
    # \brief Returns the currently configured timeout-check callback.
    # 
    # \return A reference to the timeout-check callback.
    # 
    def getTimeoutCallback() -> CallbackFunction: pass

    ##
    # \brief Sets the callback receiving log messages emitted by the generator.
    # 
    # \param func The log-message callback.
    # 
    def setLogMessageCallback(func: LogMessageCallbackFunction) -> None: pass

    ##
    # \brief Returns the currently configured log-message callback.
    # 
    # \return A reference to the log-message callback.
    # 
    def getLogMessageCallback() -> LogMessageCallbackFunction: pass

    ##
    # \brief Generates a conformer ensemble for <em>molgraph</em>.
    # 
    # \param molgraph The input molecular graph.
    # 
    # \return A ConfGen.ReturnCode value reporting the outcome of the generation.
    # 
    def generate(molgraph: Chem.MolecularGraph) -> int: pass

    ##
    # \brief Generates a conformer ensemble for <em>molgraph</em> while keeping the substructure <em>fixed_substr</em> at its current 3D coordinates.
    # 
    # \param molgraph The input molecular graph.
    # \param fixed_substr The substructure that must retain its current 3D coordinates.
    # 
    # \return A ConfGen.ReturnCode value reporting the outcome of the generation. 
    # 
    # \since 1.1
    # 
    def generate(molgraph: Chem.MolecularGraph, fixed_substr: Chem.MolecularGraph) -> int: pass

    ##
    # \brief Generates a conformer ensemble for <em>molgraph</em> while keeping the substructure <em>fixed_substr</em> at the supplied 3D coordinates <em>fixed_substr_coords</em>.
    # 
    # \param molgraph The input molecular graph.
    # \param fixed_substr The substructure that must retain the supplied 3D coordinates.
    # \param fixed_substr_coords The 3D coordinates assigned to <em>fixed_substr</em>.
    # 
    # \return A ConfGen.ReturnCode value reporting the outcome of the generation. 
    # 
    # \since 1.1
    # 
    def generate(molgraph: Chem.MolecularGraph, fixed_substr: Chem.MolecularGraph, fixed_substr_coords: Math.Vector3DArray) -> int: pass

    ##
    # \brief Transfers the generated conformer ensemble onto <em>molgraph</em>.
    # 
    # The per-conformer 3D coordinates are written to each atom's 3D-coordinates array (via Chem.set3DCoordinatesArray) and the corresponding per-conformer energies are attached to the molecular graph (via Chem.setConformerEnergies).
    # 
    # \param molgraph The molecular graph that receives the conformer coordinates and energies.
    # 
    def setConformers(molgraph: Chem.MolecularGraph) -> None: pass

    ##
    # \brief Returns the number of generated conformers.
    # 
    # \return The conformer count.
    # 
    def getNumConformers() -> int: pass

    ##
    # \brief 
    # \param conf_idx 
    # \return 
    #
    def getConformer(conf_idx: int) -> ConformerData: pass

    ##
    # \brief 
    # \param conf_idx 
    # \return 
    #
    def __getitem__(conf_idx: int) -> ConformerData: pass

    objectID = property(getObjectID)

    numConformers = property(getNumConformers)

    settings = property(getSettings)

    abortCallback = property(getAbortCallback, setAbortCallback)

    timeoutCallback = property(getTimeoutCallback, setTimeoutCallback)

    logMessageCallback = property(getLogMessageCallback, setLogMessageCallback)
