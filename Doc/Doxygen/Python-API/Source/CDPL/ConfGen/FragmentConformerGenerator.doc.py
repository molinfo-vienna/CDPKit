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
# \brief Driver for the generation of low-energy 3D conformers for a single molecular fragment (chain, small ring or macrocycle) via distance geometry plus MMFF94 minimization plus RMSD clustering.
# 
class FragmentConformerGenerator(Boost.Python.instance):

    ##
    # \brief Constructs the <tt>FragmentConformerGenerator</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %FragmentConformerGenerator instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %FragmentConformerGenerator instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Sets the callback invoked periodically to allow conformer generation to be aborted by the user.
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
    # \brief Sets the callback invoked periodically to check whether the configured generation timeout has elapsed.
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
    # \brief Sets the callback that receives log messages produced during conformer generation.
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
    # \brief Generates a conformer ensemble for the fragment <em>molgraph</em> (the fragment type is perceived automatically).
    # 
    # \param molgraph The fragment to process.
    # 
    # \return A status code defined in ConfGen.ReturnCode.
    # 
    def generate(molgraph: Chem.MolecularGraph) -> int: pass

    ##
    # \brief Generates a conformer ensemble for the fragment <em>molgraph</em> while keeping the substructure <em>fixed_substr</em> at the supplied 3D coordinates.
    # 
    # \param molgraph The fragment to process.
    # \param fixed_substr The substructure that must retain the supplied 3D coordinates.
    # \param fixed_substr_coords The 3D coordinates assigned to <em>fixed_substr</em>.
    # 
    # \return A status code defined in ConfGen.ReturnCode. 
    # 
    # \since 1.1
    # 
    def generate(molgraph: Chem.MolecularGraph, fixed_substr: Chem.MolecularGraph, fixed_substr_coords: Math.Vector3DArray) -> int: pass

    ##
    # \brief Generates a conformer ensemble for the fragment <em>molgraph</em> using the fragment-type-specific settings selected by <em>frag_type</em>.
    # 
    # \param molgraph The fragment to process.
    # \param frag_type One of the ConfGen.FragmentType values selecting the per-fragment-class settings.
    # 
    # \return A status code defined in ConfGen.ReturnCode.
    # 
    def generate(molgraph: Chem.MolecularGraph, frag_type: int) -> int: pass

    ##
    # \brief Generates a conformer ensemble for the fragment <em>molgraph</em> using the fragment-type-specific settings selected by <em>frag_type</em> while keeping the substructure <em>fixed_substr</em> at the supplied 3D coordinates.
    # 
    # \param molgraph The fragment to process.
    # \param frag_type One of the ConfGen.FragmentType values selecting the per-fragment-class settings.
    # \param fixed_substr The substructure that must retain the supplied 3D coordinates.
    # \param fixed_substr_coords The 3D coordinates assigned to <em>fixed_substr</em>.
    # 
    # \return A status code defined in ConfGen.ReturnCode. 
    # 
    # \since 1.1
    # 
    def generate(molgraph: Chem.MolecularGraph, frag_type: int, fixed_substr: Chem.MolecularGraph, fixed_substr_coords: Math.Vector3DArray) -> int: pass

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
    # \brief Returns the current generator settings.
    # 
    # \return A reference to the settings.
    # 
    def getSettings() -> FragmentConformerGeneratorSettings: pass

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
