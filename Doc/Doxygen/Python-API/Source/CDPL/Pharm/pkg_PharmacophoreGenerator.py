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
# \brief PharmacophoreGenerator.
# 
class PharmacophoreGenerator(Boost.Python.instance):

    ##
    # \brief Constructs the <tt>PharmacophoreGenerator</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %PharmacophoreGenerator instance.
    # \param self The \e %PharmacophoreGenerator instance to initialize.
    # \param gen 
    # 
    def __init__(gen: PharmacophoreGenerator) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %PharmacophoreGenerator instance this method is called upon.
    # 
    # Different Python \e %PharmacophoreGenerator instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %PharmacophoreGenerator instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Perceives the enabled pharmacophore features of the molecular graph a\ molgraph and adds them to the pharmacophore <em>pharm</em>.
    # 
    # \param molgraph The molecular graph for which to perceive the features.
    # \param pharm The pharmacophore instance where the generated output features get appended.
    # \param append If <tt>False</tt>, <em>pharm</em> gets cleared before adding any new features.
    # 
    def generate(molgraph: CDPL.Chem.MolecularGraph, pharm: Pharmacophore, append: bool = False) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def clone() -> PharmacophoreGenerator: pass

    ##
    # \brief Specifies a function for the retrieval of atom 3D-coordinates for feature generation.
    # 
    # \param func The atom 3D-coordinates function.
    # 
    def setAtom3DCoordinatesFunction(func: CDPL.Chem.Atom3DCoordinatesFunction) -> None: pass

    ##
    # \brief Returns the function that was registered for the retrieval of atom 3D-coordinates.
    # 
    # \return The registered atom 3D-coordinates function.
    # 
    def getAtom3DCoordinatesFunction() -> CDPL.Chem.Atom3DCoordinatesFunction: pass

    ##
    # \brief Specifies a Pharm.FeatureGenerator instance that gets used for the generation of the specified type of features.
    # 
    # \param type An identifier for the type of features the generator instance gets used for.
    # \param ftr_gen The generator instance.
    # 
    def setFeatureGenerator(type: int, ftr_gen: FeatureGenerator) -> None: pass

    ##
    # \brief Removes the Pharm.FeatureGenerator instance for the specified type of features.
    # 
    # \param type An identifier for the type of features for which the generator instance has to be removed.
    # 
    def removeFeatureGenerator(type: int) -> None: pass

    ##
    # \brief Returns the Pharm.FeatureGenerator instance that was registered for the generation of the specified type of features.
    # 
    # \param type An identifier for the type of features of interest.
    # 
    # \return The registered generator instance.
    # 
    def getFeatureGenerator(type: int) -> FeatureGenerator: pass

    ##
    # \brief Enables or disables the generation of features of the specified type.
    # 
    # \param type An identifier for the type of the features to enable/disable.
    # \param enable <tt>True</tt> if the generation of the given type of features should be enabled, and <tt>False</tt> if disabled.
    # 
    def enableFeature(type: int, enable: bool) -> None: pass

    ##
    # \brief 
    # \param ft_type 
    # \return 
    #
    def isFeatureEnabled(ft_type: int) -> bool: pass

    ##
    # \brief 
    # \param arg1 
    # \return 
    #
    def clearEnabledFeatures(self: int) -> bool: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %PharmacophoreGenerator instance \a gen.
    # \param self The \e %PharmacophoreGenerator instance this method is called upon.
    # \param gen The \e %PharmacophoreGenerator instance to copy.
    # \return \a self
    # 
    def assign(gen: PharmacophoreGenerator) -> PharmacophoreGenerator: pass

    objectID = property(getObjectID)

    ##
    # \brief FIXME!
    # \brief 
    #
    atom3DCoordsFunc = property(getAtom3DCoordsFunc, setAtom3DCoordsFunc)
