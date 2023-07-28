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
# \brief InteractionPharmacophoreGenerator.
# 
class InteractionPharmacophoreGenerator(Boost.Python.instance):

    ##
    # \brief Constructs the <tt>InteractionPharmacophoreGenerator</tt> instance.
    # 
    def __init__(core_ph4_gen_cfg: Configuration = CDPL.Pharm.Configuration.DEFAULT_CONFIG, env_ph4_gen_cfg: Configuration = CDPL.Pharm.Configuration.DEFAULT_CONFIG) -> None: pass

    ##
    # \brief Initializes the \e %InteractionPharmacophoreGenerator instance.
    # \param self The \e %InteractionPharmacophoreGenerator instance to initialize.
    # \param gen 
    # 
    def __init__(gen: InteractionPharmacophoreGenerator) -> None: pass

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
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %InteractionPharmacophoreGenerator instance \a gen.
    # \param self The \e %InteractionPharmacophoreGenerator instance this method is called upon.
    # \param gen The \e %InteractionPharmacophoreGenerator instance to copy.
    # \return \a self
    # 
    def assign(gen: InteractionPharmacophoreGenerator) -> InteractionPharmacophoreGenerator: pass

    ##
    # \brief 
    # \param radius 
    #
    def setCoreEnvironmentRadius(radius: float) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getCoreEnvironmentRadius() -> float: pass

    ##
    # \brief 
    # \param add 
    #
    def addExclusionVolumes(add: bool) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def exclusionVolumesAdded() -> bool: pass

    ##
    # \brief 
    # \return 
    #
    def getCorePharmacophoreGenerator() -> PharmacophoreGenerator: pass

    ##
    # \brief 
    # \return 
    #
    def getEnvironmentPharmacophoreGenerator() -> PharmacophoreGenerator: pass

    ##
    # \brief 
    # \return 
    #
    def getInteractionAnalyzer() -> InteractionAnalyzer: pass

    ##
    # \brief 
    # \return 
    #
    def getCorePharmacophore() -> Pharmacophore: pass

    ##
    # \brief 
    # \return 
    #
    def getEnvironmentPharmacophore() -> Pharmacophore: pass

    ##
    # \brief 
    # \return 
    #
    def getInteractionMapping() -> FeatureMapping: pass

    ##
    # \brief 
    # \return 
    #
    def getCoreEnvironment() -> CDPL.Chem.Fragment: pass

    ##
    # \brief 
    # \param core 
    # \param tgt 
    # \param ia_pharm 
    # \param extract_core_env 
    # \param append 
    #
    def generate(core: CDPL.Chem.MolecularGraph, tgt: CDPL.Chem.MolecularGraph, ia_pharm: Pharmacophore, extract_core_env: bool, append: bool = False) -> None: pass

    objectID = property(getObjectID)

    coreEnvironmentRadius = property(getCoreEnvironmentRadius, setCoreEnvironmentRadius)

    ##
    # \brief FIXME!
    # \brief 
    #
    addXVolumes = property(getAddXVolumes, setAddXVolumes)

    corePharmacophoreGenerator = property(getCorePharmacophoreGenerator)

    ##
    # \brief FIXME!
    # \brief 
    #
    envPharmacophoreGenerator = property(getEnvPharmacophoreGenerator)

    interactionAnalyzer = property(getInteractionAnalyzer)

    corePharmacophore = property(getCorePharmacophore)

    ##
    # \brief FIXME!
    # \brief 
    #
    envPharmacophore = property(getEnvPharmacophore)

    interactionMapping = property(getInteractionMapping)

    coreEnvironment = property(getCoreEnvironment)
