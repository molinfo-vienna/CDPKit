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
class Vector3FArrayBFGSMinimizer(Boost.Python.instance):

    ##
    # \brief 
    #
    class Status(Boost.Python.enum):

        ##
        # \brief SUCCESS.
        #
        SUCCESS = 0

        ##
        # \brief NO_PROGRESS.
        #
        NO_PROGRESS = 1

        ##
        # \brief ITER_LIMIT_REACHED.
        #
        ITER_LIMIT_REACHED = 2

        ##
        # \brief GNORM_REACHED.
        #
        GNORM_REACHED = 4

        ##
        # \brief DELTAF_REACHED.
        #
        DELTAF_REACHED = 8

    ##
    # \brief Initializes the \e %Vector3FArrayBFGSMinimizer instance.
    # \param self The \e %Vector3FArrayBFGSMinimizer instance to initialize.
    # \param func 
    # \param grad_func 
    #
    def __init__(self: object, func: FloatVector3FArrayFunctor, grad_func: object) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %Vector3FArrayBFGSMinimizer instance this method is called upon.
    #
    # Different Python \e %Vector3FArrayBFGSMinimizer instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %Vector3FArrayBFGSMinimizer instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: Vector3FArrayBFGSMinimizer) -> int: pass

    ##
    # \brief 
    # \param self The \e %Vector3FArrayBFGSMinimizer instance this method is called upon.
    # \return 
    #
    def getGradientNorm(self: Vector3FArrayBFGSMinimizer) -> float: pass

    ##
    # \brief 
    # \param self The \e %Vector3FArrayBFGSMinimizer instance this method is called upon.
    # \return 
    #
    def getFunctionDelta(self: Vector3FArrayBFGSMinimizer) -> float: pass

    ##
    # \brief 
    # \param self The \e %Vector3FArrayBFGSMinimizer instance this method is called upon.
    # \return 
    #
    def getFunctionValue(self: Vector3FArrayBFGSMinimizer) -> float: pass

    ##
    # \brief 
    # \param self The \e %Vector3FArrayBFGSMinimizer instance this method is called upon.
    # \return 
    #
    def getNumIterations(self: Vector3FArrayBFGSMinimizer) -> int: pass

    ##
    # \brief 
    # \param self The \e %Vector3FArrayBFGSMinimizer instance this method is called upon.
    # \return 
    #
    def getStatus(self: Vector3FArrayBFGSMinimizer) -> Status: pass

    ##
    # \brief 
    # \param self The \e %Vector3FArrayBFGSMinimizer instance this method is called upon.
    # \param x 
    # \param g 
    # \param max_iter 
    # \param g_norm 
    # \param delta_f 
    # \param do_setup 
    # \return 
    #
    def minimize(self: Vector3FArrayBFGSMinimizer, x: Vector3FArray, g: Vector3FArray, max_iter: int, g_norm: float, delta_f: float, do_setup: bool = True) -> Status: pass

    ##
    # \brief 
    # \param self The \e %Vector3FArrayBFGSMinimizer instance this method is called upon.
    # \param x 
    # \param g 
    # \param step_size 
    # \param tol 
    # \return 
    #
    def setup(self: Vector3FArrayBFGSMinimizer, x: Vector3FArray, g: Vector3FArray, step_size: float = 0.001, tol: float = 0.15) -> float: pass

    ##
    # \brief 
    # \param self The \e %Vector3FArrayBFGSMinimizer instance this method is called upon.
    # \param f 
    # \param x 
    # \param g 
    # \return 
    #
    def iterate(self: Vector3FArrayBFGSMinimizer, f: float, x: Vector3FArray, g: Vector3FArray) -> tuple: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)

    ##
    # \brief 
    #
    gradientNorm = property(getGradientNorm)

    ##
    # \brief 
    #
    functionDelta = property(getFunctionDelta)

    ##
    # \brief 
    #
    functionValue = property(getFunctionValue)

    ##
    # \brief 
    #
    numIterations = property(getNumIterations)

    ##
    # \brief 
    #
    status = property(getStatus)
