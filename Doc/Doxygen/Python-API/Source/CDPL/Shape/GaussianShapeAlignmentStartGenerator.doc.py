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
# \brief Abstract base for generators of starting transformations used to seed Gaussian-shape overlap optimization.
# 
# Concrete subclasses (e.g. Shape.PrincipalAxesAlignmentStartGenerator) implement the pure virtual member functions to provide a set of candidate transformations placing the aligned shape relative to the reference shape.
# 
class GaussianShapeAlignmentStartGenerator(Boost.Python.instance):

    ##
    # \brief Initializes the \c %GaussianShapeAlignmentStartGenerator instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %GaussianShapeAlignmentStartGenerator instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %GaussianShapeAlignmentStartGenerator instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Prepares the reference shape function for use by the start generator.
    # 
    # \param func The reference shape function (may be modified, e.g. centered).
    # \param xform The output transformation that maps the reference shape from its prepared frame back to its original frame.
    # 
    # \return The perceived symmetry class of the reference shape (see namespace Shape.SymmetryClass).
    # 
    def setupReference(func: GaussianShapeFunction, xform: Math.Matrix4D) -> int: pass

    ##
    # \brief Prepares the aligned shape function for use by the start generator.
    # 
    # \param func The aligned shape function (may be modified, e.g. centered).
    # \param xform The output transformation that maps the aligned shape from its prepared frame back to its original frame.
    # 
    # \return The perceived symmetry class of the aligned shape (see namespace Shape.SymmetryClass).
    # 
    def setupAligned(func: GaussianShapeFunction, xform: Math.Matrix4D) -> int: pass

    ##
    # \brief 
    # \param func 
    # \param sym_class 
    #
    def setReference(func: GaussianShapeFunction, sym_class: int) -> None: pass

    ##
    # \brief Generates the set of starting transformations for the alignment of <em>func</em>.
    # 
    # \param func The aligned shape function.
    # \param sym_class The symmetry class of the aligned shape (see namespace Shape.SymmetryClass).
    # 
    # \return <tt>True</tt> if at least one starting transformation was produced, and <tt>False</tt> otherwise.
    # 
    def generate(func: GaussianShapeFunction, sym_class: int) -> bool: pass

    ##
    # \brief Returns the number of starting transformations produced by the last generate() call.
    # 
    # \return The number of starting transformations.
    # 
    def getNumStartTransforms() -> int: pass

    ##
    # \brief Returns the number of sub-transformations sharing the same starting transformation index space.
    # 
    # Subclasses that produce multiple sub-transforms per logical start (e.g. for symmetry-related variants) use this method to expose the secondary count.
    # 
    # \return The number of sub-transformations per starting transformation.
    # 
    def getNumStartSubTransforms() -> int: pass

    ##
    # \brief Returns the starting transformation at index <em>idx</em>.
    # 
    # \param idx The zero-based index of the starting transformation.
    # 
    # \return A reference to the starting transformation. 
    # 
    # \throw Base.IndexError if the number of starting transformations is zero or <em>idx</em> is not in the range [0, getNumStartTransforms() - 1].
    # 
    def getStartTransform(idx: int) -> Math.Vector7D: pass

    ##
    # \brief 
    # \return 
    #
    def __len__() -> int: pass

    ##
    # \brief 
    # \param idx 
    # \return 
    #
    def __getitem__(idx: int) -> Math.Vector7D: pass

    objectID = property(getObjectID)

    numStartSubTransforms = property(getNumStartSubTransforms)
