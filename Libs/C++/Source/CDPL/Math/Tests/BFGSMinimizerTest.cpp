/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * BFGSMinimizerTest.cpp 
 *
 * Copyright (C) 2010-2011 Thomas A. Seidel <thomas.seidel@univie.ac.at>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; see the file COPYING. If not, write to
 * the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */


#include <string>
#include <cstddef>

#include <boost/test/auto_unit_test.hpp>

#include "CDPL/Math/BFGSMinimizer.hpp"
#include "CDPL/Math/Vector.hpp"
#include "CDPL/Math/IO.hpp"


namespace
{

	struct Rosenbrock
	{

		typedef double ValueType;
		typedef CDPL::Math::Vector<double> VectorType;

		VectorType  x;
		VectorType  g;
		VectorType  solution;
		std::string name;

		static const std::size_t maxNumIter = 20;

		Rosenbrock(): x(2), g(2), solution(2), name("Rosenbrock") {
			solution(0) = 1.0;
			solution(1) = 1.0;
		}

		void init() {
			x(0) = -1.2;
			x(1) = 1.0;
		}

		static double valueFunc(const VectorType& x) {
			double u = x(0);
			double v = x(1);
			double a = u - 1;
			double b = u * u - v;

			return (a * a + 10 * b * b);
		}

		static double valueAndGradientFunc(const VectorType& x, VectorType& g) {
			double u = x(0);
			double v = x(1);
			double a = u - 1;
			double b = u * u - v;

			g(0) = 2 * (u - 1) + 40 * u * b;
			g(1) = -20 * b;  

			return (a * a + 10 * b * b);
		}

		void testMinimizationSolution() {
			for (VectorType::SizeType j = 0; j < solution.getSize(); j++)
				BOOST_CHECK_CLOSE(solution(j), x(j), 0.0001);
		}

		ValueType xNorm2() {
			return norm2(x);
		}
	};

	struct Roth
	{

		typedef double ValueType;
		typedef CDPL::Math::Vector<double> VectorType;

		VectorType  x;
		VectorType  g;
		VectorType  solution;
		std::string name;

		static const std::size_t maxNumIter = 20;

		Roth(): x(2), g(2), solution(2), name("Roth") {
			solution(0) = 5.0;
			solution(1) = 4.0;
		}

		void init() {
			x(0) = 4.5;
			x(1) = 3.5;
		}

		static double valueFunc(const VectorType& x) {
			double u = x(0);
			double v = x(1);
			double a = -13.0 + u + ((5.0 - v) * v - 2.0) * v;
			double b = -29.0 + u + ((v + 1.0) * v - 14.0) * v;

			return (a * a + b * b);
		}

		static double valueAndGradientFunc(const VectorType& x, VectorType& g) {
			double f = valueFunc(x);
			
			double u = x(0);
			double v = x(1);
			double a = -13.0 + u + ((5.0 - v) * v - 2.0) * v;
			double b = -29.0 + u + ((v + 1.0) * v - 14.0) * v;
			double c = -2 + v * (10 - 3 * v);
			double d = -14 + v * (2 + 3 * v);

			g(0) = 2 * a + 2 * b;
			g(1) = 2 * a * c + 2 * b * d;

			return f;
		}

		void testMinimizationSolution() {
			for (VectorType::SizeType j = 0; j < solution.getSize(); j++)
				BOOST_CHECK_CLOSE(solution(j), x(j), 0.0001);
		}

		ValueType xNorm2() {
			return norm2(x);
		}
	};

	struct Wood
	{

		typedef double ValueType;
		typedef CDPL::Math::Vector2DArray VectorType;

		VectorType  x;
		VectorType  g;
		VectorType  solution;
		std::string name;

		static const std::size_t maxNumIter = 500;

		Wood(): x(), g(), solution(), name("Wood") {
			x.resize(2);
			g.resize(2);
			solution.resize(2);

			solution[0](0) = 1.0;
			solution[0](1) = 1.0;
			solution[1](0) = 1.0;
			solution[1](1) = 1.0;
		}

		void init() {
			x[0](0) = -3.0;
			x[0](1) = 1.0;
			x[1](0) = -3.0;
			x[1](1) = 1.0;
		}

		static double valueFunc(const VectorType& x) {
			double u1 = x[0](0);
			double u2 = x[0](1);
			double u3 = x[1](0);
			double u4 = x[1](1);
			double t1 = u1 * u1 - u2;
			double t2 = u3 * u3 - u4;

			return (100 * t1 * t1 + (1 - u1) * (1 - u1)
					+ 90 * t2 * t2 + (1 - u3) * (1 - u3)
					+ 10.1 * ((1 - u2) * (1 - u2) + (1 - u4) * (1 - u4))
					+ 19.8 * (1 - u2) * (1 - u4));
		}

		static double valueAndGradientFunc(const VectorType& x, VectorType& g) {
			double f = valueFunc(x);
			
			double u1 = x[0](0);
			double u2 = x[0](1);
			double u3 = x[1](0);
			double u4 = x[1](1);
			double t1 = u1 * u1 - u2;
			double t2 = u3 * u3 - u4;

			g[0](0) = 400 * u1 * t1 - 2 * (1 - u1);
			g[0](1) = -200 * t1 - 20.2 * (1 - u2) - 19.8 * (1 - u4);
			g[1](0) = 360 * u3 * t2 - 2 * (1 - u3);
			g[1](1) = -180 * t2 - 20.2 * (1 - u4) - 19.8 * (1 - u2);
			
			return f;
		}

		void testMinimizationSolution() {
			for (std::size_t i = 0; i < solution.getSize(); i++)
				for (VectorType::ElementType::SizeType j = 0; j < solution[i].getSize(); j++)
					BOOST_CHECK_CLOSE(solution[i](j), x[i](j), 0.0001);
		}

		ValueType xNorm2() {
			return std::sqrt(innerProd(x[0], x[0]) + innerProd(x[1], x[1]));
		}
	};

	template <typename F>
	void testMinimization(F& func)
	{
		using namespace CDPL;
		using namespace Math;

		typedef BFGSMinimizer<typename F::VectorType> MinimizerType;

		func.init();

		MinimizerType minimizer(&F::valueFunc, &F::valueAndGradientFunc);

		typename F::ValueType last_fval = minimizer.setup(func.x, func.g, 0.1 * func.xNorm2(), 0.1);
		typename F::ValueType fval;
		std::size_t num_req_iter;

		// BOOST_MESSAGE("#### Testing minimization of " << func.name << " function ####");

		// BOOST_MESSAGE("# initial fval = " << fval);
		// BOOST_MESSAGE("# initial x = " << func.x);
		// BOOST_MESSAGE("# initial g = " << func.g);

		for (num_req_iter = 0; num_req_iter < F::maxNumIter; num_req_iter++) {
			typename MinimizerType::Status status = minimizer.iterate(fval, func.x, func.g);

			//BOOST_MESSAGE("i = " << num_req_iter << "; status = " << status << "; fval = " << fval);

			if (status == MinimizerType::NO_PROGRESS) 
				break;

			BOOST_CHECK(fval < last_fval);
			BOOST_CHECK_EQUAL(minimizer.getFunctionDelta(), (last_fval - fval));
			BOOST_CHECK_EQUAL(minimizer.getNumIterations(), (num_req_iter + 1));

			last_fval = fval;
		}

		// BOOST_MESSAGE("# final fval = " << fval);
		// BOOST_MESSAGE("# final x = " << func.x);
		// BOOST_MESSAGE("# final g = " << func.g);
		// BOOST_MESSAGE("# num_req_iter = " << num_req_iter);

		BOOST_CHECK_EQUAL(minimizer.getNumIterations(), num_req_iter);
		BOOST_CHECK(num_req_iter < F::maxNumIter);

		func.testMinimizationSolution();

		// -----------------

		func.init();
		minimizer.setup(func.x, func.g, 0.1 * func.xNorm2(), 0.1);
	
		typename MinimizerType::Status status = minimizer.minimize(func.x, func.g, num_req_iter, -1, -1, false);
		
		BOOST_CHECK_EQUAL(status, minimizer.getStatus());
		BOOST_CHECK_EQUAL(status, MinimizerType::ITER_LIMIT_REACHED);

		func.testMinimizationSolution();

		// -----------------

		func.init();
		minimizer.setup(func.x, func.g, 0.1 * func.xNorm2(), 0.1);
	
		status = minimizer.minimize(func.x, func.g, num_req_iter + 1, -1, -1, false);
		
		BOOST_CHECK_EQUAL(status, minimizer.getStatus());
		BOOST_CHECK_EQUAL(status, MinimizerType::NO_PROGRESS);

		func.testMinimizationSolution();

		// -----------------

		typename F::ValueType min_gnorm = minimizer.getGradientNorm();
		typename F::ValueType min_deltaf = minimizer.getFunctionDelta();

		func.init();
		minimizer.setup(func.x, func.g, 0.1 * func.xNorm2(), 0.1);
	
		status = minimizer.minimize(func.x, func.g, num_req_iter + 1, min_gnorm * 2, -1, false);
		
		BOOST_CHECK_EQUAL(status, minimizer.getStatus());
		BOOST_CHECK_EQUAL(status, MinimizerType::GNORM_REACHED);

		// -----------------

		func.init();
		minimizer.setup(func.x, func.g, 0.1 * func.xNorm2(), 0.1);
	
		status = minimizer.minimize(func.x, func.g, num_req_iter + 1, -1, min_deltaf * 2, false);
		
		BOOST_CHECK_EQUAL(status, minimizer.getStatus());
		BOOST_CHECK_EQUAL(status, MinimizerType::DELTAF_REACHED);
	}
}

BOOST_AUTO_TEST_CASE(BFGSMinimizerTest)
{
	using namespace CDPL;
	using namespace Math;

	Rosenbrock func1;
	Roth func2;
	Wood func3;

	testMinimization(func1);
	testMinimization(func2);
	testMinimization(func3);
}
