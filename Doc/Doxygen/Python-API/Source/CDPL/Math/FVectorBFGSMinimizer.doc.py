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
# \brief Implementation of the <em>Broyden-Fletcher-Goldfarb-Shanno (BFGS)</em> algorithm for solving unconstrained nonlinear optimization problems.
# 
# The base implementation has been taken from the <em>GNU Scientific Library</em>.
# 
# \see [\ref BFGS, \ref GSL]
# 
class FVectorBFGSMinimizer(Boost.Python.instance):

    ##
    # \brief Status bitmask reported by minimize() and getStatus(). Multiple flags may be combined.
    # 
    class Status(Boost.Python.enum):

        ##
        # \brief Iteration step completed successfully (no termination condition met yet).
        # 
        SUCCESS = 0

        ##
        # \brief No more progress towards the solution can be made.
        # 
        NO_PROGRESS = 1

        ##
        # \brief The maximum number of minimization iterations has been reached.
        # 
        ITER_LIMIT_REACHED = 2

        ##
        # \brief The configured gradient-norm threshold has been reached.
        # 
        GNORM_REACHED = 4

        ##
        # \brief The configured function-value delta between successive iterations has been reached.
        # 
        DELTAF_REACHED = 8

    ##
    # \brief Constructs the <tt>BFGSMinimizer</tt> instance with the given objective and gradient functions.
    # 
    # \param func The objective function.
    # \param grad_func The gradient function (also computes the objective value).
    # 
    def __init__(func: FloatFVectorFunctor, grad_func: object) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %FVectorBFGSMinimizer instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %FVectorBFGSMinimizer instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Returns the L2 norm of the gradient at the end of the most recent iterate() call.
    # 
    # \return The gradient norm.
    # 
    def getGradientNorm() -> float: pass

    ##
    # \brief Returns the magnitude of the function-value decrease produced by the most recent iterate() call.
    # 
    # \return The function-value delta (positive when the function decreased).
    # 
    def getFunctionDelta() -> float: pass

    ##
    # \brief Returns the function value at the end of the most recent iterate() call.
    # 
    # \return The function value.
    # 
    def getFunctionValue() -> float: pass

    ##
    # \brief Returns the number of iterations performed by the most recent minimize() or iterate() loop.
    # 
    # \return The iteration count.
    # 
    def getNumIterations() -> int: pass

    ##
    # \brief Returns the current status of the minimizer.
    # 
    # \return The Status bitmask.
    # 
    def getStatus() -> Status: pass

    ##
    # \brief Runs the BFGS minimization loop on <em>x</em>.
    # 
    # \param x The variable vector to be minimized (modified in place).
    # \param g The gradient vector (modified in place).
    # \param max_iter The maximum number of iterations (<em>0</em> means unlimited).
    # \param g_norm The gradient-norm threshold below which the minimization is stopped (negative values disable this stop condition).
    # \param delta_f The function-value-delta threshold below which the minimization is stopped (negative values disable this stop condition).
    # \param do_setup If <tt>True</tt>, setup() is invoked at the start to initialize the minimizer.
    # 
    # \return The terminal Status bitmask of the minimization.
    # 
    def minimize(x: FVector, g: FVector, max_iter: int, g_norm: float, delta_f: float, do_setup: bool = True) -> Status: pass

    ##
    # \brief Initializes the minimizer state for a subsequent iterate() / minimize() loop.
    # 
    # \param x The starting variable vector.
    # \param g The gradient vector (filled with the gradient at <em>x</em>).
    # \param step_size The initial step-size guess.
    # \param tol The line-search tolerance.
    # 
    # \return The objective-function value at <em>x</em>.
    # 
    def setup(x: FVector, g: FVector, step_size: float = 0.001, tol: float = 0.15) -> float: pass

    ##
    # \brief Performs a single BFGS iteration: line search along the current search direction, BFGS update of the inverse Hessian approximation, and selection of the new search direction.
    # 
    # \param f The current function value (updated in place).
    # \param x The current variable vector (updated in place).
    # \param g The current gradient vector (updated in place).
    # 
    # \return Status.SUCCESS if the iteration produced a step, otherwise the bitmask of stop conditions met.
    # 
    def iterate(f: float, x: FVector, g: FVector) -> tuple: pass

    objectID = property(getObjectID)

    gradientNorm = property(getGradientNorm)

    functionDelta = property(getFunctionDelta)

    functionValue = property(getFunctionValue)

    numIterations = property(getNumIterations)

    status = property(getStatus)
