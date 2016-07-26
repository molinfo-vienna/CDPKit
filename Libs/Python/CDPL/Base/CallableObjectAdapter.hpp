/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * CallableObjectAdapter.hpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2010 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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


#ifndef CDPL_PYTHON_BASE_CALLABLEOBJECTADAPTER_HPP
#define CDPL_PYTHON_BASE_CALLABLEOBJECTADAPTER_HPP

#include <functional>

#include <boost/python.hpp>


namespace CDPLPythonBase 
{

	template <typename ResType, typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type, bool Copy = false>
	class QuarternaryFunctionAdapter
	{

	public:
		QuarternaryFunctionAdapter(const boost::python::object& callable): callable(callable) {}

		ResType operator()(const Arg1Type& arg1, const Arg2Type& arg2, const Arg3Type& arg3, const Arg4Type& arg4) const {
			if (Copy)
				return boost::python::call<ResType>(callable.ptr(), arg1, arg2, arg3, arg4);

			return boost::python::call<ResType>(callable.ptr(), boost::ref(arg1), boost::ref(arg2), boost::ref(arg3), boost::ref(arg4));
		}

	private:
		boost::python::object callable;
	};

	template <typename ResType, typename Arg1Type, typename Arg2Type, typename Arg3Type, bool Copy = false>
	class TernaryFunctionAdapter
	{

	public:
		TernaryFunctionAdapter(const boost::python::object& callable): callable(callable) {}

		ResType operator()(const Arg1Type& arg1, const Arg2Type& arg2, const Arg3Type& arg3) const {
			if (Copy)
				return boost::python::call<ResType>(callable.ptr(), arg1, arg2, arg3);

			return boost::python::call<ResType>(callable.ptr(), boost::ref(arg1), boost::ref(arg2), boost::ref(arg3));
		}

	private:
		boost::python::object callable;
	};

	template <typename ResType, typename Arg1Type, typename Arg2Type, bool Copy = false>
	class BinaryFunctionAdapter : public std::binary_function<Arg1Type, Arg2Type, ResType>
	{

	public:
		BinaryFunctionAdapter(const boost::python::object& callable): callable(callable) {}

		ResType operator()(const Arg1Type& arg1, const Arg2Type& arg2) const {
			if (Copy)
				return boost::python::call<ResType>(callable.ptr(), arg1, arg2);

			return boost::python::call<ResType>(callable.ptr(), boost::ref(arg1), boost::ref(arg2));
		}

	private:
		boost::python::object callable;
	};

	template <typename ResType, typename ArgType>
	class UnaryFunctionAdapter : public std::unary_function<ArgType, ResType>
	{

	public:
		UnaryFunctionAdapter(const boost::python::object& callable): callable(callable) {}

		ResType operator()(const ArgType& arg) const {
			return boost::python::call<ResType>(callable.ptr(), boost::ref(arg));
		}

	private:
		boost::python::object callable;
	};

	template <typename ResType>
	class NoArgFunctionAdapter
	{

	public:
		NoArgFunctionAdapter(const boost::python::object& callable): callable(callable) {}

		ResType operator()() const {
			return boost::python::call<ResType>(callable.ptr());
		}

	private:
		boost::python::object callable;
	};
}

#endif // CDPL_PYTHON_BASE_CALLABLEOBJECTADAPTER_HPP
