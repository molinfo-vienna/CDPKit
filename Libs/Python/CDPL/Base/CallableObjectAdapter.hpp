/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * CallableObjectAdapter.hpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2020 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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
#include <string>

#include <boost/python.hpp>
#include <boost/type_traits.hpp>


namespace CDPLPythonBase 
{

	template <typename T, bool FundamentalType = false>
	struct MakeRef
	{

		typedef typename boost::reference_wrapper<T> RetType;

		static inline RetType make(T& arg) {
			return boost::ref(arg);
		}
	};

	template <typename T>
	struct MakeRef<T, true>
	{

		typedef const T& RetType;

		static inline RetType make(T& arg) {
			return arg;
		}
	};

	template <>
	struct MakeRef<const std::string, false>
	{

		typedef boost::python::str RetType;

		static inline RetType make(const std::string& arg) {
			return boost::python::str(arg);
		}
	};

	template <typename T>
	inline typename MakeRef<T, boost::is_fundamental<T>::value>::RetType makeRef(T& arg)
	{
		return MakeRef<T, boost::is_fundamental<T>::value>::make(arg);
	}

	template <typename ResType, typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type>
	class QuarternaryFunctionAdapter
	{

	public:
		QuarternaryFunctionAdapter(const boost::python::object& callable): callable(callable) {}

		ResType operator()(const Arg1Type& arg1, const Arg2Type& arg2, const Arg3Type& arg3, const Arg4Type& arg4) const {
			using namespace boost;

			return python::call<ResType>(callable.ptr(), makeRef(arg1), makeRef(arg2), makeRef(arg3), makeRef(arg4));
		}

	private:
		boost::python::object callable;
	};

	template <typename ResType, typename Arg1Type, typename Arg2Type, typename Arg3Type, typename Arg4Type>
	class QuarternaryFunctionAdapter<ResType&, Arg1Type, Arg2Type, Arg3Type, Arg4Type>
	{

	public:
		QuarternaryFunctionAdapter(const boost::python::object& callable): callable(callable) {}

		ResType& operator()(const Arg1Type& arg1, const Arg2Type& arg2, const Arg3Type& arg3, const Arg4Type& arg4) {
			using namespace boost;

			result = python::call<python::object>(callable.ptr(), makeRef(arg1), makeRef(arg2), makeRef(arg3), makeRef(arg4));

			return python::extract<ResType&>(result);
		}

	private:
		boost::python::object callable;
		boost::python::object result;
	};

//----------

	template <typename ResType, typename Arg1Type, typename Arg2Type, typename Arg3Type>
	class TernaryFunctionAdapter
	{

	public:
		TernaryFunctionAdapter(const boost::python::object& callable): callable(callable) {}

		ResType operator()(const Arg1Type& arg1, const Arg2Type& arg2, const Arg3Type& arg3) const {
			using namespace boost;

			return python::call<ResType>(callable.ptr(), makeRef(arg1), makeRef(arg2), makeRef(arg3));
		}

	private:
		boost::python::object callable;
	};

	template <typename ResType, typename Arg1Type, typename Arg2Type, typename Arg3Type>
	class TernaryFunctionAdapter<ResType&, Arg1Type, Arg2Type, Arg3Type>
	{

	public:
		TernaryFunctionAdapter(const boost::python::object& callable): callable(callable) {}

		ResType& operator()(const Arg1Type& arg1, const Arg2Type& arg2, const Arg3Type& arg3) {
			using namespace boost;

			result = python::call<python::object>(callable.ptr(), makeRef(arg1), makeRef(arg2), makeRef(arg3));

			return python::extract<ResType&>(result);
		}

	private:
		boost::python::object callable;
		boost::python::object result;
	};

//----------

	template <typename ResType, typename Arg1Type, typename Arg2Type>
	class BinaryFunctionAdapter : public std::binary_function<Arg1Type, Arg2Type, ResType>
	{

	public:
		BinaryFunctionAdapter(const boost::python::object& callable): callable(callable) {}

		ResType operator()(const Arg1Type& arg1, const Arg2Type& arg2) const {
			using namespace boost;

			return python::call<ResType>(callable.ptr(), makeRef(arg1), makeRef(arg2));
		}

	private:
		boost::python::object callable;
	};

	template <typename ResType, typename Arg1Type, typename Arg2Type>
	class BinaryFunctionAdapter<ResType&, Arg1Type, Arg2Type> : public std::binary_function<Arg1Type, Arg2Type, ResType&>
	{

	public:
		BinaryFunctionAdapter(const boost::python::object& callable): callable(callable) {}

		ResType& operator()(const Arg1Type& arg1, const Arg2Type& arg2) {
			using namespace boost;

			result = python::call<python::object>(callable.ptr(), makeRef(arg1), makeRef(arg2));

			return python::extract<ResType&>(result);
		}

	private:
		boost::python::object callable;
		boost::python::object result;
	};

//----------

	template <typename ResType, typename ArgType>
	class UnaryFunctionAdapter : public std::unary_function<ArgType, ResType>
	{

	public:
		UnaryFunctionAdapter(const boost::python::object& callable): callable(callable) {}

		ResType operator()(const ArgType& arg) const {
			using namespace boost;

			return python::call<ResType>(callable.ptr(), makeRef(arg));
		}

	private:
		boost::python::object callable;
	};

	template <typename ResType, typename ArgType>
	class UnaryFunctionAdapter<ResType&, ArgType>  : public std::unary_function<ArgType, ResType&>
	{

	public:
		UnaryFunctionAdapter(const boost::python::object& callable): callable(callable) {}

		ResType& operator()(const ArgType& arg) {
			using namespace boost;

			result = python::call<python::object>(callable.ptr(), makeRef(arg));

			return python::extract<ResType&>(result);
		}

	private:
		boost::python::object callable;
		boost::python::object result;
	};

//----------

	template <typename ResType>
	class NoArgFunctionAdapter
	{

	public:
		NoArgFunctionAdapter(const boost::python::object& callable): callable(callable) {}

		ResType operator()() const {
			using namespace boost;

			return python::call<ResType>(callable.ptr());
		}

	private:
		boost::python::object callable;
	};

	template <typename ResType>
	class NoArgFunctionAdapter<ResType&>
	{

	public:
		NoArgFunctionAdapter(const boost::python::object& callable): callable(callable) {}

		ResType& operator()() {
			using namespace boost;

			result = python::call<python::object>(callable.ptr());

			return python::extract<ResType&>(result);
		}

	private:
		boost::python::object callable;
		boost::python::object result;
	};
}

#endif // CDPL_PYTHON_BASE_CALLABLEOBJECTADAPTER_HPP
