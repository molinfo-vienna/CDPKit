/* 
 * BFGSMinimizer.hpp 
 *
 * Copyright (C) 2010-2011 Thomas Seidel <thomas.seidel@univie.ac.at>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; see the file COPYING. If not, write to
 * the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

/**
 * \file
 * \brief Implementation of the BFGS optimization algorithm.
 */

#ifndef CDPL_MATH_BFGSMINIMIZER_HPP
#define CDPL_MATH_BFGSMINIMIZER_HPP

#include <cstddef>
#include <limits>
#include <functional>

#include "CDPL/Math/MinimizerVariableArrayTraits.hpp"
#include "CDPL/Math/TypeTraits.hpp"


namespace CDPL
{

    namespace Math
    {

        /**
         * \brief Fletcher's implementation of the BFGS method.
         *
         * The implementation has been taken from the <em>GNU Scientific Library</em>.
         *
         * \see R. Fletcher, "Practical Method's of Optimization", Second
         *      Edition, ISBN 0471915475.  Algorithms 2.6.2 and 2.6.4. 
         */
        template <typename VA, typename VT = typename MinimizerVariableArrayTraits<VA>::ValueType, typename FVT = VT>
        class BFGSMinimizer
        {

          public:
            typedef VA  VariableArrayType;
            typedef VT  ValueType;
            typedef FVT FunctionValueType;

            typedef typename std::function<FVT(const VA&, VA&)> GradientFunction;
            typedef typename std::function<FVT(const VA&)>      ObjectiveFunction;

            enum Status
            {

                SUCCESS            = 0, // general success indicator
                NO_PROGRESS        = 1, // no more progress towards solution
                ITER_LIMIT_REACHED = 2, // the maximum number of minimization iterations has been reached
                GNORM_REACHED      = 4, // the specified gradient norm has been reached
                DELTAF_REACHED     = 8 // the specified function value delta between successive iterations has been reached
            };

            BFGSMinimizer(const ObjectiveFunction& func, const GradientFunction& grad_func):
                rho(0.01), tau1(9), tau2(0.05), tau3(0.5), order(3), sigma(0.1), func(func), gradFunc(grad_func), status(SUCCESS) {}

            ValueType getGradientNorm() const
            {
                return g0Norm;
            }

            ValueType getFunctionDelta() const
            {
                return -deltaF;
            }

            ValueType getFunctionValue() const
            {
                return fValue;
            }

            std::size_t getNumIterations() const
            {
                return numIter;
            }

            Status getStatus() const
            {
                return status;
            }

            Status minimize(VariableArrayType& x, VariableArrayType& g, std::size_t max_iter,
                            const ValueType& g_norm, const ValueType& delta_f, bool do_setup = true)
            {
                if (do_setup)
                    setup(x, g);

                fValue = ValueType(0);

                for (std::size_t i = 0; max_iter == 0 || i < max_iter; i++) {
                    status = iterate(fValue, x, g);

                    if (status != SUCCESS)
                        return status;

                    if (g_norm >= ValueType(0) && g0Norm <= g_norm)
                        status = GNORM_REACHED;

                    if (delta_f >= ValueType(0) && deltaF <= delta_f)
                        status = Status(status | DELTAF_REACHED);

                    if (status != SUCCESS)
                        return status;
                }

                return (status = ITER_LIMIT_REACHED);
            }

            ValueType setup(const VariableArrayType& x, VariableArrayType& g,
                            const ValueType& step_size = 0.001, const ValueType& tol = 0.15)
            {
                numIter = 0;
                step    = step_size;
                deltaF  = ValueType(0);

                startF = gradFunc(x, g);

                /* Use the gradient as the initial direction */

                assign(x0, x);
                assign(g0, g);
                g0Norm = norm2(g0);

                assign(p, g);
                multiply(p, -1 / g0Norm);

                pNorm = norm2(p); /* should be 1 */
                fp0   = -g0Norm;

                /* Prepare the function evaluation cache */

                initFuncEvalCache();

                /* Prepare 1d minimisation parameters */

                sigma = tol;

                return startF;
            }

            Status iterate(ValueType& f, VariableArrayType& x, VariableArrayType& g)
            {
                if (numIter == 0)
                    f = startF;

                ValueType alpha = ValueType(0), alpha1;
                ValueType f0    = f;

                if (pNorm == ValueType(0) || g0Norm == ValueType(0) || fp0 == ValueType(0)) {
                    clear(dx);
                    return NO_PROGRESS;
                }

                if (deltaF < ValueType(0)) {
                    ValueType del = std::max(-deltaF, 10 * std::numeric_limits<ValueType>::epsilon() * TypeTraits<ValueType>::abs(f0));
                    alpha1        = std::min(ValueType(1), 2 * del / -fp0);

                } else
                    alpha1 = TypeTraits<ValueType>::abs(step);

                /* line minimisation, with cubic interpolation (order = 3) */

                Status status = minimize(alpha1, alpha);

                if (status != SUCCESS)
                    return status;

                updatePosition(alpha, x, f, g);

                deltaF = f - f0;

                /* Choose a new direction for the next step */

                /* This is the BFGS update: */
                /* p' = g1 - A dx - B dg */
                /* A = - (1 + dg.dg / dx.dg) B + dg.g / dx.dg */
                /* B = dx.g / dx.dg */

                /* dx0 = x - x0 */

                assign(dx0, x);
                sub(dx0, x0);
                assign(dx, dx0); /* keep a copy */

                /* dg0 = g - g0 */

                assign(dg0, g);
                sub(dg0, g0);

                ValueType dxg    = dot(dx0, g);
                ValueType dgg    = dot(dg0, g);
                ValueType dxdg   = dot(dx0, dg0);
                ValueType dgnorm = norm2(dg0);

                ValueType A = ValueType(0);
                ValueType B = ValueType(0);

                if (dxdg != 0) {
                    B = dxg / dxdg;
                    A = -(1 + dgnorm * dgnorm / dxdg) * B + dgg / dxdg;
                }

                assign(p, g);

                axpy(-A, dx0, p);
                axpy(-B, dg0, p);

                assign(g0, g);
                assign(x0, x);
                g0Norm = norm2(g0);
                pNorm  = norm2(p);

                /* update direction and fp0 */

                ValueType pg = dot(p, g);
                ValueType dir(pg >= ValueType(0) ? -1 : +1);

                multiply(p, dir / pNorm);

                pNorm = norm2(p);

                fp0 = dot(p, g0);

                changeDirection();

                numIter++;

                return SUCCESS;
            }

          private:
            BFGSMinimizer();

            BFGSMinimizer& operator=(const BFGSMinimizer&);

            void initFuncEvalCache()
            {
                assign(xAlpha, x0);
                assign(gAlpha, g0);

                xCacheKey  = ValueType(0);
                fAlpha     = startF;
                fCacheKey  = ValueType(0);
                gCacheKey  = ValueType(0);
                dfAlpha    = slope();
                dfCacheKey = ValueType(0);
            }

            void assign(VariableArrayType& v1, const VariableArrayType& v2)
            {
                MinimizerVariableArrayTraits<VA>::assign(v1, v2);
            }

            void clear(VariableArrayType& v)
            {
                MinimizerVariableArrayTraits<VA>::clear(v);
            }

            void multiply(VariableArrayType& v, const ValueType& f)
            {
                MinimizerVariableArrayTraits<VA>::multiply(v, f);
            }

            void sub(VariableArrayType& v1, const VariableArrayType& v2)
            {
                MinimizerVariableArrayTraits<VA>::sub(v1, v2);
            }

            ValueType norm2(const VariableArrayType& v) const
            {
                return MinimizerVariableArrayTraits<VA>::template norm2<ValueType>(v);
            }

            ValueType dot(const VariableArrayType& v1, const VariableArrayType& v2) const
            {
                return MinimizerVariableArrayTraits<VA>::template dot<ValueType>(v1, v2);
            }

            void axpy(const ValueType& alpha, const VariableArrayType& x, VariableArrayType& y) const
            {
                MinimizerVariableArrayTraits<VA>::axpy(alpha, x, y);
            }

            ValueType slope() const
            { /* compute gradient . direction */
                return dot(gAlpha, p);
            }

            void moveTo(const ValueType& alpha)
            {
                if (alpha == xCacheKey) /* using previously cached position */
                    return;

                /* set xAlpha = x + alpha * p */

                assign(xAlpha, x0);

                axpy(alpha, p, xAlpha);

                xCacheKey = alpha;
            }

            ValueType getF(const ValueType& alpha)
            {
                if (alpha == fCacheKey) /* using previously cached f(alpha) */
                    return fAlpha;

                moveTo(alpha);

                fAlpha    = func(xAlpha);
                fCacheKey = alpha;

                return fAlpha;
            }

            ValueType getDF(const ValueType& alpha)
            {
                if (alpha == dfCacheKey) /* using previously cached df(alpha) */
                    return dfAlpha;

                moveTo(alpha);

                if (alpha != gCacheKey) {
                    fAlpha    = gradFunc(xAlpha, gAlpha);
                    gCacheKey = alpha;
                    fCacheKey = alpha;
                }

                dfAlpha    = slope();
                dfCacheKey = alpha;

                return dfAlpha;
            }

            void getFDF(const ValueType& alpha, ValueType& f, ValueType& df)
            {
                /* Check for previously cached values */

                if (alpha == fCacheKey && alpha == dfCacheKey) {
                    f  = fAlpha;
                    df = dfAlpha;
                    return;
                }

                if (alpha == fCacheKey || alpha == dfCacheKey) {
                    df = getDF(alpha);
                    f  = getF(alpha);
                    return;
                }

                moveTo(alpha);

                fAlpha    = gradFunc(xAlpha, gAlpha);
                fCacheKey = alpha;
                gCacheKey = alpha;

                dfAlpha    = slope();
                dfCacheKey = alpha;

                f  = fAlpha;
                df = dfAlpha;
            }

            void updatePosition(const ValueType& alpha, VariableArrayType& x, ValueType& f, VariableArrayType& g)
            {
                ValueType f_alpha, df_alpha;

                /* ensure that everything is fully cached */

                getFDF(alpha, f_alpha, df_alpha);

                f = f_alpha;
                assign(x, xAlpha);
                assign(g, gAlpha);
            }

            void changeDirection()
            {
                /* Convert the cache values from the end of the current minimisation
                   to those needed for the start of the next minimisation, alpha = 0 */

                /* The new xAlpha for alpha = 0 is the current position */

                assign(xAlpha, x0);
                xCacheKey = ValueType(0);

                /* The function value does not change */

                fCacheKey = ValueType(0);

                /* The new gAlpha for alpha = 0 is the current gradient at the endpoint */

                assign(gAlpha, g0);
                gCacheKey = ValueType(0);

                /* Calculate the slope along the new direction vector, p */

                dfAlpha    = slope();
                dfCacheKey = ValueType(0);
            }

            std::size_t solveQuadratic(const ValueType& a, const ValueType& b, const ValueType& c,
                                       ValueType& x0, ValueType& x1) const
            {

                ValueType disc = b * b - 4 * a * c;

                if (a == ValueType(0)) { /* Handle linear case */
                    if (b == ValueType(0))
                        return 0;

                    else {
                        x0 = -c / b;
                        return 1;
                    };
                }

                if (disc > ValueType(0)) {
                    if (b == ValueType(0)) {
                        ValueType r = TypeTraits<ValueType>::abs(TypeTraits<ValueType>::sqrt(disc) / (a * 2));
                        x0          = -r;
                        x1          = r;

                    } else {
                        ValueType sgnb(b > ValueType(0) ? 1 : -1);
                        ValueType temp = -(b + sgnb * TypeTraits<ValueType>::sqrt(disc)) / 2;
                        ValueType r1   = temp / a;
                        ValueType r2   = c / temp;

                        if (r1 < r2) {
                            x0 = r1;
                            x1 = r2;

                        } else {
                            x0 = r2;
                            x1 = r1;
                        }
                    }

                    return 2;

                } else if (disc == ValueType(0)) {
                    x0 = -b / (2 * a);
                    x1 = -b / (2 * a);
                    return 2;

                } else
                    return 0;
            }

            /* 
             * Find a minimum in x = [0, 1] of the interpolating quadratic through
             * (0, f0) (1, f1) with derivative fp0 at x = 0.  The interpolating
             * polynomial is q(x) = f0 + fp0 * z + (f1 - f0 - fp0) * z^2
             */
            ValueType interpolateQuadratic(const ValueType& f0, const ValueType& fp0, const ValueType& f1,
                                           const ValueType& zl, const ValueType& zh) const
            {

                ValueType fl = f0 + zl * (fp0 + zl * (f1 - f0 - fp0));
                ValueType fh = f0 + zh * (fp0 + zh * (f1 - f0 - fp0));
                ValueType c  = 2 * (f1 - f0 - fp0); /* curvature */

                ValueType zmin = zl, fmin = fl;

                if (fh < fmin) {
                    zmin = zh;
                    fmin = fh;
                }

                if (c > ValueType(0)) { /* positive curvature required for a minimum */
                    ValueType z = -fp0 / c; /* location of minimum */

                    if (z > zl && z < zh) {
                        ValueType f = f0 + z * (fp0 + z * (f1 - f0 - fp0));

                        if (f < fmin) {
                            zmin = z;
                            fmin = f;
                        }
                    }
                }

                return zmin;
            }

            /*
             * Find a minimum in x = [0, 1] of the interpolating cubic through
             * (0, f0) (1, f1) with derivatives fp0 at x = 0 and fp1 at x = 1.
             *
             * The interpolating polynomial is:
             *
             * c(x) = f0 + fp0 * z + eta * z^2 + xi * z^3
             *
             * where eta = 3 * (f1 - f0) - 2 * fp0 - fp1, xi = fp0 + fp1 - 2 * (f1 - f0). 
             */
            ValueType cubic(const ValueType& c0, const ValueType& c1, const ValueType& c2,
                            const ValueType& c3, const ValueType& z) const
            {

                return c0 + z * (c1 + z * (c2 + z * c3));
            }

            void checkExtremum(const ValueType& c0, const ValueType& c1, const ValueType& c2,
                               const ValueType& c3, const ValueType& z, ValueType& zmin, ValueType& fmin) const
            {
                /* could make an early return by testing curvature > 0 for minimum */

                ValueType y = cubic(c0, c1, c2, c3, z);

                if (y < fmin) {
                    zmin = z; /* accepted new point*/
                    fmin = y;
                }
            }

            ValueType interpolateCubic(const ValueType& f0, const ValueType& fp0, const ValueType& f1,
                                       const ValueType& fp1, const ValueType& zl, const ValueType& zh) const
            {

                ValueType eta = 3 * (f1 - f0) - 2 * fp0 - fp1;
                ValueType xi  = fp0 + fp1 - 2 * (f1 - f0);
                ValueType c0 = f0, c1 = fp0, c2 = eta, c3 = xi;

                ValueType zmin = zl;
                ValueType fmin = cubic(c0, c1, c2, c3, zl);

                checkExtremum(c0, c1, c2, c3, zh, zmin, fmin);

                ValueType   z0, z1;
                std::size_t n = solveQuadratic(3 * c3, 2 * c2, c1, z0, z1);

                if (n == 2) { /* found 2 roots */
                    if (z0 > zl && z0 < zh)
                        checkExtremum(c0, c1, c2, c3, z0, zmin, fmin);

                    if (z1 > zl && z1 < zh)
                        checkExtremum(c0, c1, c2, c3, z1, zmin, fmin);

                } else if (n == 1) { /* found 1 root */
                    if (z0 > zl && z0 < zh)
                        checkExtremum(c0, c1, c2, c3, z0, zmin, fmin);
                }

                return zmin;
            }

            ValueType interpolate(const ValueType& a, const ValueType& fa, const ValueType& fpa,
                                  const ValueType& b, const ValueType& fb, const ValueType& fpb,
                                  const ValueType& xmin, const ValueType& xmax) const
            {
                /* Map [a, b] to [0, 1] */

                ValueType zmin = (xmin - a) / (b - a);
                ValueType zmax = (xmax - a) / (b - a);

                if (zmin > zmax) {
                    ValueType tmp(zmin);
                    zmin = zmax;
                    zmax = tmp;
                }

                ValueType z;

                if (order > 2 && std::isfinite(fpb))
                    z = interpolateCubic(fa, fpa * (b - a), fb, fpb * (b - a), zmin, zmax);
                else
                    z = interpolateQuadratic(fa, fpa * (b - a), fb, zmin, zmax);

                ValueType alpha = a + z * (b - a);

                return alpha;
            }

            Status minimize(const ValueType& alpha1, ValueType& alpha_new)
            {
                ValueType falpha, fpalpha, delta, alpha_next;
                ValueType alpha = alpha1, alpha_prev = ValueType(0);
                ValueType a = ValueType(0), fb = ValueType(0), fpb = ValueType(0);

                ValueType f0, fp0;

                getFDF(ValueType(0), f0, fp0);

                ValueType falpha_prev  = f0;
                ValueType fpalpha_prev = fp0;

                ValueType b   = alpha;
                ValueType fa  = f0;
                ValueType fpa = fp0;

                /* Begin bracketing */

                const std::size_t num_brack_iter = 100, section_iters = 100;
                std::size_t       i = 0;

                while (i++ < num_brack_iter) {
                    falpha = getF(alpha);

                    /* Fletcher's rho test */

                    if (falpha > f0 + alpha * rho * fp0 || falpha >= falpha_prev) {
                        a   = alpha_prev;
                        fa  = falpha_prev;
                        fpa = fpalpha_prev;
                        b   = alpha;
                        fb  = falpha;
                        fpb = std::numeric_limits<ValueType>::quiet_NaN();
                        break; /* goto sectioning */
                    }

                    fpalpha = getDF(alpha);

                    /* Fletcher's sigma test */

                    if (TypeTraits<ValueType>::abs(fpalpha) <= -sigma * fp0) {
                        alpha_new = alpha;
                        return SUCCESS;
                    }

                    if (fpalpha >= ValueType(0)) {
                        a   = alpha;
                        fa  = falpha;
                        fpa = fpalpha;
                        b   = alpha_prev;
                        fb  = falpha_prev;
                        fpb = fpalpha_prev;
                        break; /* goto sectioning */
                    }

                    delta = alpha - alpha_prev;

                    ValueType lower = alpha + delta;
                    ValueType upper = alpha + tau1 * delta;

                    alpha_next = interpolate(alpha_prev, falpha_prev, fpalpha_prev,
                                             alpha, falpha, fpalpha, lower, upper);

                    alpha_prev   = alpha;
                    falpha_prev  = falpha;
                    fpalpha_prev = fpalpha;
                    alpha        = alpha_next;
                }

                /*  Sectioning of bracket [a, b] */

                while (i++ < section_iters) {
                    delta = b - a;

                    ValueType lower = a + tau2 * delta;
                    ValueType upper = b - tau3 * delta;

                    alpha  = interpolate(a, fa, fpa, b, fb, fpb, lower, upper);
                    falpha = getF(alpha);

                    if ((a - alpha) * fpa <= std::numeric_limits<ValueType>::epsilon()) {
                        /* roundoff prevents progress */
                        return NO_PROGRESS;
                    }

                    if (falpha > f0 + rho * alpha * fp0 || falpha >= fa) {
                        /*  a_next = a; */
                        b   = alpha;
                        fb  = falpha;
                        fpb = std::numeric_limits<ValueType>::quiet_NaN();

                    } else {
                        fpalpha = getDF(alpha);

                        if (TypeTraits<ValueType>::abs(fpalpha) <= -sigma * fp0) {
                            alpha_new = alpha;
                            return SUCCESS; /* terminate */
                        }

                        if (((b - a) >= ValueType(0) && fpalpha >= ValueType(0)) || ((b - a) <= ValueType(0) && fpalpha <= ValueType(0))) {
                            b   = a;
                            fb  = fa;
                            fpb = fpa;
                            a   = alpha;
                            fa  = falpha;
                            fpa = fpalpha;

                        } else {
                            a   = alpha;
                            fa  = falpha;
                            fpa = fpalpha;
                        }
                    }
                }

                return SUCCESS;
            }

            const ValueType   rho;
            const ValueType   tau1;
            const ValueType   tau2;
            const ValueType   tau3;
            const std::size_t order;
            std::size_t       numIter;
            ValueType         step;
            ValueType         g0Norm;
            ValueType         pNorm;
            ValueType         startF;
            ValueType         deltaF;
            ValueType         fValue;
            ValueType         fp0;
            VariableArrayType x0;
            VariableArrayType g0;
            VariableArrayType p;
            VariableArrayType dx;
            VariableArrayType dx0;
            VariableArrayType dg0;
            VariableArrayType xAlpha;
            VariableArrayType gAlpha;
            ValueType         sigma;
            ValueType         fAlpha;
            ValueType         dfAlpha;
            ValueType         fCacheKey;
            ValueType         dfCacheKey;
            ValueType         xCacheKey;
            ValueType         gCacheKey;
            ObjectiveFunction func;
            GradientFunction  gradFunc;
            Status            status;
        };
    } // namespace Math
} // namespace CDPL

#endif // CDPL_MATH_BFGSMINIMIZER_HPP
