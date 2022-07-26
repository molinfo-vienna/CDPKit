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
class GaussianShapeAlignmentStartGenerator(Boost.Python.instance):

    ##
    # \brief Initializes the \e %GaussianShapeAlignmentStartGenerator instance.
    # \param self The \e %GaussianShapeAlignmentStartGenerator instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %GaussianShapeAlignmentStartGenerator instance this method is called upon.
    #
    # Different Python \e %GaussianShapeAlignmentStartGenerator instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %GaussianShapeAlignmentStartGenerator instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: GaussianShapeAlignmentStartGenerator) -> int: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeAlignmentStartGenerator instance this method is called upon.
    # \param func 
    # \param xform 
    # \return 
    #
    def setupReference(self: GaussianShapeAlignmentStartGenerator, func: GaussianShapeFunction, xform: CDPL.Math.Matrix4D) -> int: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeAlignmentStartGenerator instance this method is called upon.
    # \param func 
    # \param xform 
    # \return 
    #
    def setupAligned(self: GaussianShapeAlignmentStartGenerator, func: GaussianShapeFunction, xform: CDPL.Math.Matrix4D) -> int: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeAlignmentStartGenerator instance this method is called upon.
    # \param func 
    # \param sym_class 
    #
    def setReference(self: GaussianShapeAlignmentStartGenerator, func: GaussianShapeFunction, sym_class: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeAlignmentStartGenerator instance this method is called upon.
    # \param func 
    # \param sym_class 
    # \return 
    #
    def generate(self: GaussianShapeAlignmentStartGenerator, func: GaussianShapeFunction, sym_class: int) -> bool: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeAlignmentStartGenerator instance this method is called upon.
    # \return 
    #
    def getNumStartTransforms(self: GaussianShapeAlignmentStartGenerator) -> int: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeAlignmentStartGenerator instance this method is called upon.
    # \return 
    #
    def getNumStartSubTransforms(self: GaussianShapeAlignmentStartGenerator) -> int: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeAlignmentStartGenerator instance this method is called upon.
    # \param idx 
    # \return 
    #
    def getStartTransform(self: GaussianShapeAlignmentStartGenerator, idx: int) -> CDPL.Math.Vector7D: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeAlignmentStartGenerator instance this method is called upon.
    # \return 
    #
    def __len__(self: GaussianShapeAlignmentStartGenerator) -> int: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeAlignmentStartGenerator instance this method is called upon.
    # \param idx 
    # \return 
    #
    def __getitem__(self: GaussianShapeAlignmentStartGenerator, idx: int) -> CDPL.Math.Vector7D: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)

    ##
    # \brief 
    #
    numStartSubTransforms = property(getNumStartSubTransforms)
