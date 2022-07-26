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
class InteractionPharmacophoreGenerator(Boost.Python.instance):

    ##
    # \brief Initializes the \e %InteractionPharmacophoreGenerator instance.
    # \param self The \e %InteractionPharmacophoreGenerator instance to initialize.
    # \param core_ph4_gen_cfg 
    # \param env_ph4_gen_cfg 
    #
    def __init__(self: object, core_ph4_gen_cfg: Configuration = CDPL.Pharm.Configuration.DEFAULT_CONFIG, env_ph4_gen_cfg: Configuration = CDPL.Pharm.Configuration.DEFAULT_CONFIG) -> None: pass

    ##
    # \brief Initializes the \e %InteractionPharmacophoreGenerator instance.
    # \param self The \e %InteractionPharmacophoreGenerator instance to initialize.
    # \param gen 
    #
    def __init__(self: object, gen: InteractionPharmacophoreGenerator) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %InteractionPharmacophoreGenerator instance this method is called upon.
    #
    # Different Python \e %InteractionPharmacophoreGenerator instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %InteractionPharmacophoreGenerator instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: InteractionPharmacophoreGenerator) -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %InteractionPharmacophoreGenerator instance \a gen.
    # \param self The \e %InteractionPharmacophoreGenerator instance this method is called upon.
    # \param gen The \e %InteractionPharmacophoreGenerator instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: InteractionPharmacophoreGenerator, gen: InteractionPharmacophoreGenerator) -> InteractionPharmacophoreGenerator: pass

    ##
    # \brief 
    # \param self The \e %InteractionPharmacophoreGenerator instance this method is called upon.
    # \param radius 
    #
    def setCoreEnvironmentRadius(self: InteractionPharmacophoreGenerator, radius: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %InteractionPharmacophoreGenerator instance this method is called upon.
    # \return 
    #
    def getCoreEnvironmentRadius(self: InteractionPharmacophoreGenerator) -> float: pass

    ##
    # \brief 
    # \param self The \e %InteractionPharmacophoreGenerator instance this method is called upon.
    # \param add 
    #
    def addExclusionVolumes(self: InteractionPharmacophoreGenerator, add: bool) -> None: pass

    ##
    # \brief 
    # \param self The \e %InteractionPharmacophoreGenerator instance this method is called upon.
    # \return 
    #
    def exclusionVolumesAdded(self: InteractionPharmacophoreGenerator) -> bool: pass

    ##
    # \brief 
    # \param self The \e %InteractionPharmacophoreGenerator instance this method is called upon.
    # \return 
    #
    def getCorePharmacophoreGenerator(self: InteractionPharmacophoreGenerator) -> PharmacophoreGenerator: pass

    ##
    # \brief 
    # \param self The \e %InteractionPharmacophoreGenerator instance this method is called upon.
    # \return 
    #
    def getEnvironmentPharmacophoreGenerator(self: InteractionPharmacophoreGenerator) -> PharmacophoreGenerator: pass

    ##
    # \brief 
    # \param self The \e %InteractionPharmacophoreGenerator instance this method is called upon.
    # \return 
    #
    def getInteractionAnalyzer(self: InteractionPharmacophoreGenerator) -> InteractionAnalyzer: pass

    ##
    # \brief 
    # \param self The \e %InteractionPharmacophoreGenerator instance this method is called upon.
    # \return 
    #
    def getCorePharmacophore(self: InteractionPharmacophoreGenerator) -> Pharmacophore: pass

    ##
    # \brief 
    # \param self The \e %InteractionPharmacophoreGenerator instance this method is called upon.
    # \return 
    #
    def getEnvironmentPharmacophore(self: InteractionPharmacophoreGenerator) -> Pharmacophore: pass

    ##
    # \brief 
    # \param self The \e %InteractionPharmacophoreGenerator instance this method is called upon.
    # \return 
    #
    def getInteractionMapping(self: InteractionPharmacophoreGenerator) -> FeatureMapping: pass

    ##
    # \brief 
    # \param self The \e %InteractionPharmacophoreGenerator instance this method is called upon.
    # \return 
    #
    def getCoreEnvironment(self: InteractionPharmacophoreGenerator) -> CDPL.Chem.Fragment: pass

    ##
    # \brief 
    # \param self The \e %InteractionPharmacophoreGenerator instance this method is called upon.
    # \param core 
    # \param tgt 
    # \param ia_pharm 
    # \param extract_core_env 
    # \param append 
    #
    def generate(self: InteractionPharmacophoreGenerator, core: CDPL.Chem.MolecularGraph, tgt: CDPL.Chem.MolecularGraph, ia_pharm: Pharmacophore, extract_core_env: bool, append: bool = False) -> None: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)

    ##
    # \brief 
    #
    coreEnvironmentRadius = property(getCoreEnvironmentRadius, setCoreEnvironmentRadius)

    ##
    # \brief FIXME!
    #
    addXVolumes = property(getAddXVolumes, setAddXVolumes)

    ##
    # \brief 
    #
    corePharmacophoreGenerator = property(getCorePharmacophoreGenerator)

    ##
    # \brief FIXME!
    #
    envPharmacophoreGenerator = property(getEnvPharmacophoreGenerator)

    ##
    # \brief 
    #
    interactionAnalyzer = property(getInteractionAnalyzer)

    ##
    # \brief 
    #
    corePharmacophore = property(getCorePharmacophore)

    ##
    # \brief FIXME!
    #
    envPharmacophore = property(getEnvPharmacophore)

    ##
    # \brief 
    #
    interactionMapping = property(getInteractionMapping)

    ##
    # \brief 
    #
    coreEnvironment = property(getCoreEnvironment)
