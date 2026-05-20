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
# \brief Driver that generates an interaction pharmacophore by perceiving a core pharmacophore on a ligand, an environment pharmacophore on the surrounding pocket residues, analyzing the inter-feature interactions and emitting features representing the detected interactions (optionally with exclusion volumes).
# 
class InteractionPharmacophoreGenerator(Boost.Python.instance):

    ##
    # \brief Constructs the <tt>InteractionPharmacophoreGenerator</tt> instance.
    # 
    # \param core_ph4_gen_cfg Configuration flags for the core (ligand) pharmacophore generator.
    # \param env_ph4_gen_cfg Configuration flags for the environment (pocket) pharmacophore generator.
    # 
    def __init__(core_ph4_gen_cfg: Configuration = CDPL.Pharm.Configuration.DEFAULT_CONFIG, env_ph4_gen_cfg: Configuration = CDPL.Pharm.Configuration.DEFAULT_CONFIG) -> None: pass

    ##
    # \brief Initializes a copy of the \c %InteractionPharmacophoreGenerator instance \a gen.
    # \param gen The \c %InteractionPharmacophoreGenerator instance to copy.
    # 
    def __init__(gen: InteractionPharmacophoreGenerator) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %InteractionPharmacophoreGenerator instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %InteractionPharmacophoreGenerator instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %InteractionPharmacophoreGenerator instance \a gen.
    # \param gen The \c %InteractionPharmacophoreGenerator instance to copy.
    # \return \a self
    # 
    def assign(gen: InteractionPharmacophoreGenerator) -> InteractionPharmacophoreGenerator: pass

    ##
    # \brief Sets the cutoff radius around the core used to extract the environment substructure.
    # 
    # \param radius The new core-environment radius.
    # 
    def setCoreEnvironmentRadius(radius: float) -> None: pass

    ##
    # \brief Returns the currently configured core-environment cutoff radius.
    # 
    # \return The core-environment radius.
    # 
    def getCoreEnvironmentRadius() -> float: pass

    ##
    # \brief Specifies whether exclusion volume features shall be added to the output pharmacophore.
    # 
    # \param add <tt>True</tt> to add exclusion volumes, and <tt>False</tt> to skip them.
    # 
    def addExclusionVolumes(add: bool) -> None: pass

    ##
    # \brief Tells whether exclusion volume features are added.
    # 
    # \return <tt>True</tt> if exclusion volumes are added, and <tt>False</tt> otherwise.
    # 
    def exclusionVolumesAdded() -> bool: pass

    ##
    # \brief Returns the core (ligand) pharmacophore generator.
    # 
    # \return A reference to the core pharmacophore generator.
    # 
    def getCorePharmacophoreGenerator() -> PharmacophoreGenerator: pass

    ##
    # \brief Returns the environment (pocket) pharmacophore generator.
    # 
    # \return A reference to the environment pharmacophore generator.
    # 
    def getEnvironmentPharmacophoreGenerator() -> PharmacophoreGenerator: pass

    ##
    # \brief Returns the interaction analyzer used to perceive feature-feature interactions.
    # 
    # \return A reference to the interaction analyzer.
    # 
    def getInteractionAnalyzer() -> InteractionAnalyzer: pass

    ##
    # \brief Returns the core (ligand) pharmacophore produced by the last generate() call.
    # 
    # \return A reference to the core pharmacophore.
    # 
    def getCorePharmacophore() -> Pharmacophore: pass

    ##
    # \brief Returns the environment (pocket) pharmacophore produced by the last generate() call.
    # 
    # \return A reference to the environment pharmacophore.
    # 
    def getEnvironmentPharmacophore() -> Pharmacophore: pass

    ##
    # \brief Returns the feature-to-feature interaction mapping produced by the last generate() call.
    # 
    # \return A reference to the interaction mapping.
    # 
    def getInteractionMapping() -> FeatureMapping: pass

    ##
    # \brief Returns the core-environment substructure extracted by the last generate() call (only valid when <em>extract_core_env</em> was <tt>True</tt>).
    # 
    # \return A reference to the core-environment fragment.
    # 
    def getCoreEnvironment() -> Chem.Fragment: pass

    ##
    # \brief Generates the interaction pharmacophore for the (<em>core</em>, <em>tgt</em>) molecular graph pair.
    # 
    # \param core The core (ligand) molecular graph.
    # \param tgt The target (pocket) molecular graph.
    # \param ia_pharm The output interaction pharmacophore.
    # \param extract_core_env If <tt>True</tt>, the core environment is extracted from <em>tgt</em> before pharmacophore generation; if <tt>False</tt>, the environment pharmacophore is generated on <em>tgt</em> directly.
    # \param append If <tt>False</tt>, <em>ia_pharm</em> is cleared before any features are added.
    # 
    def generate(core: Chem.MolecularGraph, tgt: Chem.MolecularGraph, ia_pharm: Pharmacophore, extract_core_env: bool, append: bool = False) -> None: pass

    objectID = property(getObjectID)

    coreEnvironmentRadius = property(getCoreEnvironmentRadius, setCoreEnvironmentRadius)

    addXVolumes = property(exclusionVolumesAdded, addExclusionVolumes)

    corePharmacophoreGenerator = property(getCorePharmacophoreGenerator)

    envPharmacophoreGenerator = property(getEnvironmentPharmacophoreGenerator)

    interactionAnalyzer = property(getInteractionAnalyzer)

    corePharmacophore = property(getCorePharmacophore)

    envPharmacophore = property(getEnvironmentPharmacophore)

    interactionMapping = property(getInteractionMapping)

    coreEnvironment = property(getCoreEnvironment)
