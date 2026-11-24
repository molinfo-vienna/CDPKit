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
# \brief Computes a spatial alignment between two sets of atoms by combining topological atom matching with Kabsch-style 3D superposition.
# 
# The class drives an internal Chem.TopologicalAtomAlignment instance over the two atom sets to enumerate candidate atom mappings (subject to constraints specified via setMinTopologicalMappingSize() and setTopAlignmentConstraintFunction()), then computes the optimal rigid-body transformation for each accepted mapping using Kabsch's algorithm [\ref KABA] with the atom 3D coordinates supplied by a retrieval function specified via setEntity3DCoordinatesFunction() and (optionally) the per-atom weights supplied by a function specified by setEntityWeightFunction(). Calls to nextAlignment() advance the search. The resulting transformation and the corresponding topological mapping can be accessed by the methods getTransform() and getTopologicalMapping(), respectively.
# 
class SpatialAtomAlignment(Boost.Python.instance):

    ##
    # \brief Constructs the <tt>SpatialAtomAlignment</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Contructs a copy of the \c SpatialAtomAlignment instance \a alignment.
    # \param alignment The \c SpatialAtomAlignment instance to copy.
    # 
    def __init__(alignment: SpatialAtomAlignment) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c SpatialAtomAlignment instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c SpatialAtomAlignment instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Specifies a function for restricting allowed atom mappings in the search for alignment solutions.
    # 
    # \param func The constraint check function.
    # 
    def setEntityMatchFunction(func: BoolAtom2Functor) -> None: pass

    ##
    # \brief Returns the function that was registered for restricting allowed atom mappings.
    # 
    # \return The registered constraint check function.
    # 
    def getEntityMatchFunction() -> BoolAtom2Functor: pass

    ##
    # \brief Specifies a function for checking the compatibility of atom pairs in the search for alignment solutions.
    # 
    # \param func The constraint check function.
    # 
    # \note This function gets only called for pairs with already matching first and second atoms.
    # 
    def setEntityPairMatchFunction(func: BoolAtom4Functor) -> None: pass

    ##
    # \brief Returns the function that was registered for checking the compatibility of atom pairs.
    # 
    # \return The registered constraint check function.
    # 
    def getEntityPairMatchFunction() -> BoolAtom4Functor: pass

    ##
    # \brief Specifies a function for restricting allowed topological atom alignments.
    # 
    # \param func The constraint check function.
    # 
    def setTopAlignmentConstraintFunction(func: BoolSTPairArrayFunctor) -> None: pass

    ##
    # \brief Returns the function that was registered for restricting allowed topological atom alignments.
    # 
    # \return The registered constraint check function.
    # 
    def getTopAlignmentConstraintFunction() -> BoolSTPairArrayFunctor: pass

    ##
    # \brief Specifies a function for the retrieval of atom 3D coordinates.
    # 
    # \param func The atom 3D coordinates function.
    # 
    def setEntity3DCoordinatesFunction(func: Atom3DCoordinatesFunction) -> None: pass

    ##
    # \brief Returns the function that was registered for the retrieval of atom 3D coordinates.
    # 
    # \return The registered atom 3D coordinates function.
    # 
    def getEntity3DCoordinatesFunction() -> Atom3DCoordinatesFunction: pass

    ##
    # \brief Specifies a function for the retrieval of atom weights for spatial alignment.
    # 
    # \param func The atom weight function.
    # 
    def setEntityWeightFunction(func: DoubleAtomFunctor) -> None: pass

    ##
    # \brief Returns the function that was registered for the retrieval of atom weights for spatial alignment.
    # 
    # \return The registered atom weight function.
    # 
    def getEntityWeightFunction() -> DoubleAtomFunctor: pass

    ##
    # \brief Specifies whether additional topological atom mappings (derived from the found max.\ mappings) shall be enumerated in order to increase the number of generated spatial alignment candidates.
    # 
    # \param exhaustive <tt>True</tt> to enumerate additional topological mappings, and <tt>False</tt> if only the primary max. mappings shall be used.
    # 
    def performExhaustiveSearch(exhaustive: bool) -> None: pass

    ##
    # \brief Tells whether or not additional topological atom mappings (derived from the found max.\ mappings) are enumerated.
    # 
    # \return <tt>True</tt> if exhaustive enumeration is enabled, and <tt>False</tt> otherwise. 
    # 
    # \see performExhaustiveSearch()
    # 
    def exhaustiveSearchPerformed() -> bool: pass

    ##
    # \brief Adds an atom to the specified set.
    # 
    # \param entity The atom to add.
    # \param first_set If <tt>True</tt>, the atom is added to the first set, if <tt>False</tt> to the second one.
    # 
    def addEntity(entity: Atom, first_set: bool) -> None: pass

    ##
    # \brief Removes all atoms in the specified set.
    # 
    # \param first_set If <tt>True</tt>, the first set is cleared, if <tt>False</tt> the second one.
    # 
    def clearEntities(first_set: bool) -> None: pass

    ##
    # \brief Returns the number of atoms in the specified set.
    # 
    # \param first_set If <tt>True</tt>, the size of first set is returned, if <tt>False</tt> the size of the second one.
    # 
    def getNumEntities(first_set: bool) -> int: pass

    ##
    # \brief Returns a list containing the atoms in the specified set.
    # \param first_set If \c True, the atoms in the first set are returned and if \c False, the atoms in the second set.
    # \return A list containing the atoms in the specified set.
    # 
    def getEntities(first_set: bool) -> list: pass

    ##
    # \brief Returns the stored atom at index <em>idx</em> in the specified set.
    # 
    # \param idx The zero-based index of the atom instance to return.
    # \param first_set <tt>True</tt>, if the atom to return is stored in the first set. <tt>False</tt>, if stored in the second set.
    # 
    # \return The atom stored at index <em>idx</em> in the specified set. 
    # 
    # \throw Base.IndexError if <em>idx</em> is not in the range [0, getNumEntities()).
    # 
    def getEntity(idx: int, first_set: bool) -> Atom: pass

    ##
    # \brief Specifies the minimum number of topologically mapped atoms that is required to enable a subsequent spatial alignment.
    # 
    # \param min_size The minimum required number of topologically mapped atoms.
    # 
    def setMinTopologicalMappingSize(min_size: int) -> None: pass

    ##
    # \brief Returns the minimum number of topologically mapped atoms that is required to enable a subsequent spatial alignment.
    # 
    # \return The minimum required number of topologically mapped atoms.
    # 
    def getMinTopologicalMappingSize() -> int: pass

    ##
    # \brief Discards the current alignment search state so that the next call to nextAlignment() restarts the topological mapping enumeration from scratch.
    # 
    def reset() -> None: pass

    ##
    # \brief Searches for the next alignment solution.
    # 
    # \return <tt>True</tt> if a new alignment solution could be found, and <tt>False</tt> otherwise.
    # 
    def nextAlignment() -> bool: pass

    ##
    # \brief Returns the alignment transformation matrix that was calculated in the last successful call to nextAlignment().
    # 
    # A transformation of the positions of the atoms in the second set aligns them spatially to the topologically mapped atoms in the first set.
    # 
    # \return The alignment transformation matrix.
    # 
    def getTransform() -> Math.Matrix4D: pass

    ##
    # \brief Replaces the current state with a copy of the state of the \c SpatialAtomAlignment instance \a alignment.
    # \param alignment The \c SpatialAtomAlignment instance to copy.
    # \return \a self.
    # 
    def assign(alignment: SpatialAtomAlignment) -> SpatialAtomAlignment: pass

    ##
    # \brief Returns the topological atom mapping resulting from the last successful call to nextAlignment().
    # 
    # \return The topological atom mapping as an array of pairs of atom indices.
    # 
    def getTopologicalMapping() -> Util.STPairArray: pass

    objectID = property(getObjectID)

    topMapping = property(getTopologicalMapping)

    minTopologicalMappingSize = property(getMinTopologicalMappingSize, setMinTopologicalMappingSize)

    exhaustiveSearch = property(exhaustiveSearchPerformed, performExhaustiveSearch)

    transform = property(getTransform)

    entityMatchFunction = property(getEntityMatchFunction, setEntityMatchFunction)

    entityPairMatchFunction = property(getEntityPairMatchFunction, setEntityPairMatchFunction)

    topAlignmentConstraintFunction = property(getTopAlignmentConstraintFunction, setTopAlignmentConstraintFunction)

    entityCoordsFunction = property(getEntity3DCoordinatesFunction, setEntity3DCoordinatesFunction)

    entityWeightFunction = property(getEntityWeightFunction, setEntityWeightFunction)
