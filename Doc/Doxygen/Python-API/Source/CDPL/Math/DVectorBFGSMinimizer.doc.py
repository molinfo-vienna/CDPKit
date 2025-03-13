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
# \brief Fletcher's implementation of the BFGS method.
# 
# The implementation has been taken from the <em>GNU Scientific Library</em>.
# 
# \see R. Fletcher, "Practical Method's of Optimization", Second Edition, ISBN 0471915475. Algorithms 2.6.2 and 2.6.4.
# 
class DVectorBFGSMinimizer(Boost.Python.instance):

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
    # \brief Initializes the \e %DVectorBFGSMinimizer instance.
    # \param func 
    # \param grad_func 
    # 
    def __init__(func: DoubleDVectorFunctor, grad_func: object) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %DVectorBFGSMinimizer instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %DVectorBFGSMinimizer instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief 
    # \return 
    #
    def getGradientNorm() -> float: pass

    ##
    # \brief 
    # \return 
    #
    def getFunctionDelta() -> float: pass

    ##
    # \brief 
    # \return 
    #
    def getFunctionValue() -> float: pass

    ##
    # \brief 
    # \return 
    #
    def getNumIterations() -> int: pass

    ##
    # \brief 
    # \return 
    #
    def getStatus() -> Status: pass

    ##
    # \brief 
    # \param x 
    # \param g 
    # \param max_iter 
    # \param g_norm 
    # \param delta_f 
    # \param do_setup 
    # \return 
    #
    def minimize(x: DVector, g: DVector, max_iter: int, g_norm: float, delta_f: float, do_setup: bool = True) -> Status: pass

    ##
    # \brief 
    # \param x 
    # \param g 
    # \param step_size 
    # \param tol 
    # \return 
    #
    def setup(x: DVector, g: DVector, step_size: float = 0.001, tol: float = 0.15) -> float: pass

    ##
    # \brief 
    # \param f 
    # \param x 
    # \param g 
    # \return 
    #
    def iterate(f: float, x: DVector, g: DVector) -> tuple: pass

    objectID = property(getObjectID)

    gradientNorm = property(getGradientNorm)

    functionDelta = property(getFunctionDelta)

    functionValue = property(getFunctionValue)

    numIterations = property(getNumIterations)

    status = property(getStatus)
