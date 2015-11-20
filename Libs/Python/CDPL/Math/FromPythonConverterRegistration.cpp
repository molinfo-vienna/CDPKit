/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FromPythonConverterRegistration.cpp 
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


#include <boost/python.hpp>
#include <boost/python/ssize_t.hpp>
#include <boost/ref.hpp>

#include "CDPL/Math/Vector.hpp"
#include "CDPL/Math/Matrix.hpp"
#include "CDPL/Math/Quaternion.hpp"
#include "CDPL/Math/AffineTransform.hpp"
#include "CDPL/Math/VectorArray.hpp"
#include "CDPL/Math/VectorProxy.hpp"
#include "CDPL/Math/MatrixProxy.hpp"
#include "CDPL/Math/MatrixAdapter.hpp"
#include "CDPL/Math/VectorAdapter.hpp"
#include "CDPL/Math/QuaternionAdapter.hpp"

#include "Base/GenericVariantFromPythonConverter.hpp"

#include "VectorExpressionAdapter.hpp"
#include "MatrixExpressionAdapter.hpp"
#include "QuaternionExpressionAdapter.hpp"
#include "ConverterRegistration.hpp"


namespace
{

	template <typename VectorType>
	struct CVectorFromPySequenceConverter 
	{

		CVectorFromPySequenceConverter() {
			using namespace boost;

			python::converter::registry::insert(&convertible, &construct, python::type_id<VectorType>());
		}

		static void* convertible(PyObject* obj_ptr) {
			using namespace boost;

			if (!obj_ptr)
				return 0;

			if (!PyList_Check(obj_ptr) && !PyTuple_Check(obj_ptr))
				return 0;

			python::ssize_t size = PySequence_Size(obj_ptr);

			if (size != python::ssize_t(VectorType::Size))
				return 0;

			for (python::ssize_t i = 0; i < size; i++)
				if (!python::extract<typename VectorType::ValueType>(PySequence_GetItem(obj_ptr, i)).check())
					return 0;
			
			return obj_ptr;
		}

		static void construct(PyObject* obj_ptr, boost::python::converter::rvalue_from_python_stage1_data* data) {
			using namespace boost;

			void* storage = ((python::converter::rvalue_from_python_storage<VectorType>*)data)->storage.bytes;

			new (storage) VectorType();

			VectorType& vec = *static_cast<VectorType*>(storage);

			python::ssize_t size = PySequence_Size(obj_ptr);

			for (python::ssize_t i = 0; i < size; i++)
				vec(i) = python::extract<typename VectorType::ValueType>(PySequence_GetItem(obj_ptr, i));

			data->convertible = storage;
		}
	};

	template <typename MatrixType>
	struct CMatrixFromPySequenceConverter 
	{

		CMatrixFromPySequenceConverter() {
			using namespace boost;

			python::converter::registry::insert(&convertible, &construct, python::type_id<MatrixType>());
		}

		static void* convertible(PyObject* obj_ptr) {
			using namespace boost;

			if (!obj_ptr)
				return 0;

			if (!PyList_Check(obj_ptr) && !PyTuple_Check(obj_ptr))
				return 0;

			python::ssize_t num_rows = PySequence_Size(obj_ptr);

			if (num_rows != python::ssize_t(MatrixType::Size1))
				return 0;

			for (python::ssize_t i = 0; i < num_rows; i++) {
				PyObject* row_ptr = PySequence_GetItem(obj_ptr, i);

				if (!PySequence_Check(row_ptr))
					return 0;

				python::ssize_t row_size = PySequence_Size(row_ptr);

				if (row_size > python::ssize_t(MatrixType::Size2))
					return 0;

				for (python::ssize_t j = 0; j < row_size; j++) 
					if (!python::extract<typename MatrixType::ValueType>(PySequence_GetItem(row_ptr, j)).check())
						return 0;
			}

			return obj_ptr;
		}

		static void construct(PyObject* obj_ptr, boost::python::converter::rvalue_from_python_stage1_data* data) {
			using namespace boost;

			void* storage = ((python::converter::rvalue_from_python_storage<MatrixType>*)data)->storage.bytes;

			new (storage) MatrixType();

			MatrixType& mtx = *static_cast<MatrixType*>(storage);

			python::ssize_t num_rows = PySequence_Size(obj_ptr);

			for (python::ssize_t i = 0; i < num_rows; i++) {
				PyObject* row_ptr = PySequence_GetItem(obj_ptr, i);

				python::ssize_t row_size = PySequence_Size(row_ptr);

				for (python::ssize_t j = 0; j < row_size; j++) 
					mtx(i, j) = python::extract<typename MatrixType::ValueType>(PySequence_GetItem(row_ptr, j));
			}

			data->convertible = storage;
		}
	};

	template <typename MatrixType>
	struct MatrixFromPySequenceConverter 
	{

		MatrixFromPySequenceConverter() {
			using namespace boost;

			python::converter::registry::insert(&convertible, &construct, python::type_id<MatrixType>());
		}

		static void* convertible(PyObject* obj_ptr) {
			using namespace boost;

			if (!obj_ptr)
				return 0;

			if (!PyList_Check(obj_ptr) && !PyTuple_Check(obj_ptr))
				return 0;

			python::ssize_t num_rows = PySequence_Size(obj_ptr);
			python::ssize_t num_cols = 0;

			for (python::ssize_t i = 0; i < num_rows; i++) {
				PyObject* row_ptr = PySequence_GetItem(obj_ptr, i);

				if (!PySequence_Check(row_ptr))
					return 0;

				if (i == 0) 
					num_cols = PySequence_Size(row_ptr);

				else if (num_cols != PySequence_Size(row_ptr))
					return 0;

				for (python::ssize_t j = 0; j < num_cols; j++) 
					if (!python::extract<typename MatrixType::ValueType>(PySequence_GetItem(row_ptr, j)).check())
						return 0;
			}

			return obj_ptr;
		}

		static void construct(PyObject* obj_ptr, boost::python::converter::rvalue_from_python_stage1_data* data) {
			using namespace boost;

			MatrixType mtx;

			python::ssize_t num_rows = PySequence_Size(obj_ptr);
			python::ssize_t num_cols = 0;

			for (python::ssize_t i = 0; i < num_rows; i++) {
				PyObject* row_ptr = PySequence_GetItem(obj_ptr, i);

				if (i == 0) {
					num_cols = PySequence_Size(row_ptr);
					mtx.resize(num_rows, num_cols);
				}

				for (python::ssize_t j = 0; j < num_cols; j++)
					mtx(i, j) = python::extract<typename MatrixType::ValueType>(PySequence_GetItem(row_ptr, j));
			}

			void* storage = ((python::converter::rvalue_from_python_storage<MatrixType>*)data)->storage.bytes;

			new (storage) MatrixType();

			static_cast<MatrixType*>(storage)->swap(mtx);

			data->convertible = storage;
		}
	};

	template <typename VectorType>
	struct VectorFromPySequenceConverter 
	{

		VectorFromPySequenceConverter() {
			using namespace boost;

			python::converter::registry::insert(&convertible, &construct, python::type_id<VectorType>());
		}

		static void* convertible(PyObject* obj_ptr) {
			using namespace boost;

			if (!obj_ptr)
				return 0;

			if (!PyList_Check(obj_ptr) && !PyTuple_Check(obj_ptr))
				return 0;

			python::ssize_t size = PySequence_Size(obj_ptr);

			for (python::ssize_t i = 0; i < size; i++) 
				if (!python::extract<typename VectorType::ValueType>(PySequence_GetItem(obj_ptr, i)).check())
					return 0;

			return obj_ptr;
		}

		static void construct(PyObject* obj_ptr, boost::python::converter::rvalue_from_python_stage1_data* data) {
			using namespace boost;

			python::ssize_t size = PySequence_Size(obj_ptr);

			VectorType vec(size);

			for (python::ssize_t i = 0; i < size; i++)
				vec(i) = python::extract<typename VectorType::ValueType>(PySequence_GetItem(obj_ptr, i));

			void* storage = ((python::converter::rvalue_from_python_storage<VectorType>*)data)->storage.bytes;

			new (storage) VectorType();

			static_cast<VectorType*>(storage)->swap(vec);

			data->convertible = storage;
		}
	};

	template <typename HeldDataType, typename AdapterType, typename ExpressionPointerType>
	struct ExpressionPointerFromPyObjectConverter 
	{

		ExpressionPointerFromPyObjectConverter() {
			using namespace boost;

			python::converter::registry::insert(&convertible, &construct, python::type_id<ExpressionPointerType>());
		}

		static void* convertible(PyObject* obj_ptr) {
			if (!obj_ptr)
				return 0;

			if (!boost::python::extract<HeldDataType&>(obj_ptr).check())
				return 0;

			return obj_ptr;
		}

		static void construct(PyObject* obj_ptr, boost::python::converter::rvalue_from_python_stage1_data* data) {
			using namespace boost;

			void* storage = ((python::converter::rvalue_from_python_storage<ExpressionPointerType>*)data)->storage.bytes;

			new (storage) ExpressionPointerType(new AdapterType(boost::ref(python::extract<HeldDataType&>(obj_ptr)()), 
																python::handle<>(python::borrowed(obj_ptr))));

			data->convertible = storage;
		}
	};

	template <typename VectorType>
	struct ConstVectorExpressionPointerFromPyObjectConverter 
	{

		ConstVectorExpressionPointerFromPyObjectConverter() {
			using namespace boost;
			using namespace CDPLPythonMath;

			typedef ConstVectorExpressionAdapter<boost::reference_wrapper<VectorType>, python::handle<> > ConstAdapterType;
			typedef typename ConstAdapterType::ConstExpressionPointer ConstExpressionPointerType;

			ExpressionPointerFromPyObjectConverter<VectorType, ConstAdapterType, ConstExpressionPointerType>();
		}
	};

	template <typename VectorType>
	struct VectorExpressionPointerFromPyObjectConverter 
	{

		VectorExpressionPointerFromPyObjectConverter() {
			using namespace boost;
			using namespace CDPLPythonMath;

			typedef VectorExpressionAdapter<boost::reference_wrapper<VectorType>, python::handle<> > AdapterType;
			typedef typename AdapterType::ExpressionPointer ExpressionPointerType;

			ExpressionPointerFromPyObjectConverter<VectorType, AdapterType, ExpressionPointerType>();
		}
	};

	template <typename MatrixType>
	struct ConstMatrixExpressionPointerFromPyObjectConverter 
	{

		ConstMatrixExpressionPointerFromPyObjectConverter() {
			using namespace boost;
			using namespace CDPLPythonMath;

			typedef ConstMatrixExpressionAdapter<boost::reference_wrapper<MatrixType>, python::handle<> > ConstAdapterType;
			typedef typename ConstAdapterType::ConstExpressionPointer ConstExpressionPointerType;

			ExpressionPointerFromPyObjectConverter<MatrixType, ConstAdapterType, ConstExpressionPointerType>();
		}
	};

	template <typename MatrixType>
	struct MatrixExpressionPointerFromPyObjectConverter 
	{

		MatrixExpressionPointerFromPyObjectConverter() {
			using namespace boost;
			using namespace CDPLPythonMath;

			typedef MatrixExpressionAdapter<boost::reference_wrapper<MatrixType>, python::handle<> > AdapterType;
			typedef typename AdapterType::ExpressionPointer ExpressionPointerType;

			ExpressionPointerFromPyObjectConverter<MatrixType, AdapterType, ExpressionPointerType>();
		}
	};

	template <typename QuaternionType>
	struct ConstQuaternionExpressionPointerFromPyObjectConverter 
	{

		ConstQuaternionExpressionPointerFromPyObjectConverter() {
			using namespace boost;
			using namespace CDPLPythonMath;

			typedef ConstQuaternionExpressionAdapter<boost::reference_wrapper<QuaternionType>, python::handle<> > ConstAdapterType;
			typedef typename ConstAdapterType::ConstExpressionPointer ConstExpressionPointerType;

			ExpressionPointerFromPyObjectConverter<QuaternionType, ConstAdapterType, ConstExpressionPointerType>();
		}
	};

	template <typename QuaternionType>
	struct QuaternionExpressionPointerFromPyObjectConverter 
	{

		QuaternionExpressionPointerFromPyObjectConverter() {
			using namespace boost;
			using namespace CDPLPythonMath;

			typedef QuaternionExpressionAdapter<boost::reference_wrapper<QuaternionType>, python::handle<> > AdapterType;
			typedef typename AdapterType::ExpressionPointer ExpressionPointerType;

			ExpressionPointerFromPyObjectConverter<QuaternionType, AdapterType, ExpressionPointerType>();
		}
	};
}


void CDPLPythonMath::registerFromPythonConverters()
{
	using namespace CDPL;

	// Vector Types

	CVectorFromPySequenceConverter<Math::Vector2F>();
	CVectorFromPySequenceConverter<Math::Vector3F>();
	CVectorFromPySequenceConverter<Math::Vector4F>();
	CVectorFromPySequenceConverter<Math::Vector2D>();
	CVectorFromPySequenceConverter<Math::Vector3D>();
	CVectorFromPySequenceConverter<Math::Vector4D>();
	CVectorFromPySequenceConverter<Math::Vector2L>();
	CVectorFromPySequenceConverter<Math::Vector3L>();
	CVectorFromPySequenceConverter<Math::Vector4L>();
	CVectorFromPySequenceConverter<Math::Vector2UL>();
	CVectorFromPySequenceConverter<Math::Vector3UL>();
	CVectorFromPySequenceConverter<Math::Vector4UL>();

	VectorFromPySequenceConverter<Math::FVector>();
	VectorFromPySequenceConverter<Math::DVector>();
	VectorFromPySequenceConverter<Math::LVector>();
	VectorFromPySequenceConverter<Math::ULVector>();

	// Matrix Types

	CMatrixFromPySequenceConverter<Math::Matrix2F>();
	CMatrixFromPySequenceConverter<Math::Matrix3F>();
	CMatrixFromPySequenceConverter<Math::Matrix4F>();
	CMatrixFromPySequenceConverter<Math::Matrix2D>();
	CMatrixFromPySequenceConverter<Math::Matrix3D>();
	CMatrixFromPySequenceConverter<Math::Matrix4D>();
	CMatrixFromPySequenceConverter<Math::Matrix2L>();
	CMatrixFromPySequenceConverter<Math::Matrix3L>();
	CMatrixFromPySequenceConverter<Math::Matrix4L>();
	CMatrixFromPySequenceConverter<Math::Matrix2UL>();
	CMatrixFromPySequenceConverter<Math::Matrix3UL>();
	CMatrixFromPySequenceConverter<Math::Matrix4UL>();

	MatrixFromPySequenceConverter<Math::FMatrix>();
	MatrixFromPySequenceConverter<Math::DMatrix>();
	MatrixFromPySequenceConverter<Math::LMatrix>();
	MatrixFromPySequenceConverter<Math::ULMatrix>();

	// Vector Types

	VectorExpressionPointerFromPyObjectConverter<Math::Vector2F>();
	VectorExpressionPointerFromPyObjectConverter<Math::Vector3F>();
	VectorExpressionPointerFromPyObjectConverter<Math::Vector4F>();
	VectorExpressionPointerFromPyObjectConverter<Math::Vector2D>();
	VectorExpressionPointerFromPyObjectConverter<Math::Vector3D>();
	VectorExpressionPointerFromPyObjectConverter<Math::Vector4D>();
	VectorExpressionPointerFromPyObjectConverter<Math::Vector2L>();
	VectorExpressionPointerFromPyObjectConverter<Math::Vector3L>();
	VectorExpressionPointerFromPyObjectConverter<Math::Vector4L>();
	VectorExpressionPointerFromPyObjectConverter<Math::Vector2UL>();
	VectorExpressionPointerFromPyObjectConverter<Math::Vector3UL>();
	VectorExpressionPointerFromPyObjectConverter<Math::Vector4UL>();

	VectorExpressionPointerFromPyObjectConverter<Math::FVector>();
	VectorExpressionPointerFromPyObjectConverter<Math::DVector>();
	VectorExpressionPointerFromPyObjectConverter<Math::LVector>();
	VectorExpressionPointerFromPyObjectConverter<Math::ULVector>();

	ConstVectorExpressionPointerFromPyObjectConverter<Math::FScalarVector>();
	ConstVectorExpressionPointerFromPyObjectConverter<Math::DScalarVector>();
	ConstVectorExpressionPointerFromPyObjectConverter<Math::LScalarVector>();
	ConstVectorExpressionPointerFromPyObjectConverter<Math::ULScalarVector>();

	ConstVectorExpressionPointerFromPyObjectConverter<Math::FZeroVector>();
	ConstVectorExpressionPointerFromPyObjectConverter<Math::DZeroVector>();
	ConstVectorExpressionPointerFromPyObjectConverter<Math::LZeroVector>();
	ConstVectorExpressionPointerFromPyObjectConverter<Math::ULZeroVector>();

	ConstVectorExpressionPointerFromPyObjectConverter<Math::FUnitVector>();
	ConstVectorExpressionPointerFromPyObjectConverter<Math::DUnitVector>();
	ConstVectorExpressionPointerFromPyObjectConverter<Math::LUnitVector>();
	ConstVectorExpressionPointerFromPyObjectConverter<Math::ULUnitVector>();

	// Matrix Types

	MatrixExpressionPointerFromPyObjectConverter<Math::Matrix2F>();
	MatrixExpressionPointerFromPyObjectConverter<Math::Matrix3F>();
	MatrixExpressionPointerFromPyObjectConverter<Math::Matrix4F>();
	MatrixExpressionPointerFromPyObjectConverter<Math::Matrix2D>();
	MatrixExpressionPointerFromPyObjectConverter<Math::Matrix3D>();
	MatrixExpressionPointerFromPyObjectConverter<Math::Matrix4D>();
	MatrixExpressionPointerFromPyObjectConverter<Math::Matrix2L>();
	MatrixExpressionPointerFromPyObjectConverter<Math::Matrix3L>();
	MatrixExpressionPointerFromPyObjectConverter<Math::Matrix4L>();
	MatrixExpressionPointerFromPyObjectConverter<Math::Matrix2UL>();
	MatrixExpressionPointerFromPyObjectConverter<Math::Matrix3UL>();
	MatrixExpressionPointerFromPyObjectConverter<Math::Matrix4UL>();

	MatrixExpressionPointerFromPyObjectConverter<Math::FMatrix>();
	MatrixExpressionPointerFromPyObjectConverter<Math::DMatrix>();
	MatrixExpressionPointerFromPyObjectConverter<Math::LMatrix>();
	MatrixExpressionPointerFromPyObjectConverter<Math::ULMatrix>();

	ConstMatrixExpressionPointerFromPyObjectConverter<Math::FScalingMatrix>();
	ConstMatrixExpressionPointerFromPyObjectConverter<Math::DScalingMatrix>();
	ConstMatrixExpressionPointerFromPyObjectConverter<Math::LScalingMatrix>();
	ConstMatrixExpressionPointerFromPyObjectConverter<Math::ULScalingMatrix>();

	ConstMatrixExpressionPointerFromPyObjectConverter<Math::FRotationMatrix>();
	ConstMatrixExpressionPointerFromPyObjectConverter<Math::DRotationMatrix>();
	ConstMatrixExpressionPointerFromPyObjectConverter<Math::LRotationMatrix>();
	ConstMatrixExpressionPointerFromPyObjectConverter<Math::ULRotationMatrix>();

	ConstMatrixExpressionPointerFromPyObjectConverter<Math::FTranslationMatrix>();
	ConstMatrixExpressionPointerFromPyObjectConverter<Math::DTranslationMatrix>();
	ConstMatrixExpressionPointerFromPyObjectConverter<Math::LTranslationMatrix>();
	ConstMatrixExpressionPointerFromPyObjectConverter<Math::ULTranslationMatrix>();

	ConstMatrixExpressionPointerFromPyObjectConverter<Math::FZeroMatrix>();
	ConstMatrixExpressionPointerFromPyObjectConverter<Math::DZeroMatrix>();
	ConstMatrixExpressionPointerFromPyObjectConverter<Math::LZeroMatrix>();
	ConstMatrixExpressionPointerFromPyObjectConverter<Math::ULZeroMatrix>();

	ConstMatrixExpressionPointerFromPyObjectConverter<Math::FScalarMatrix>();
	ConstMatrixExpressionPointerFromPyObjectConverter<Math::DScalarMatrix>();
	ConstMatrixExpressionPointerFromPyObjectConverter<Math::LScalarMatrix>();
	ConstMatrixExpressionPointerFromPyObjectConverter<Math::ULScalarMatrix>();

	ConstMatrixExpressionPointerFromPyObjectConverter<Math::FIdentityMatrix>();
	ConstMatrixExpressionPointerFromPyObjectConverter<Math::DIdentityMatrix>();
	ConstMatrixExpressionPointerFromPyObjectConverter<Math::LIdentityMatrix>();
	ConstMatrixExpressionPointerFromPyObjectConverter<Math::ULIdentityMatrix>();

	// Quaternion Types

	QuaternionExpressionPointerFromPyObjectConverter<Math::FQuaternion>();
	QuaternionExpressionPointerFromPyObjectConverter<Math::DQuaternion>();
	QuaternionExpressionPointerFromPyObjectConverter<Math::LQuaternion>();
	QuaternionExpressionPointerFromPyObjectConverter<Math::ULQuaternion>();

	ConstQuaternionExpressionPointerFromPyObjectConverter<Math::FRealQuaternion>();
	ConstQuaternionExpressionPointerFromPyObjectConverter<Math::DRealQuaternion>();
	ConstQuaternionExpressionPointerFromPyObjectConverter<Math::LRealQuaternion>();
	ConstQuaternionExpressionPointerFromPyObjectConverter<Math::ULRealQuaternion>();

	// VectorProxy Types

	VectorExpressionPointerFromPyObjectConverter<Math::VectorRange<VectorExpression<float> > >();
	VectorExpressionPointerFromPyObjectConverter<Math::VectorRange<VectorExpression<double> > >();
	VectorExpressionPointerFromPyObjectConverter<Math::VectorRange<VectorExpression<long> > >();
	VectorExpressionPointerFromPyObjectConverter<Math::VectorRange<VectorExpression<unsigned long> > >();

	ConstVectorExpressionPointerFromPyObjectConverter<Math::VectorRange<const ConstVectorExpression<float> > >();
	ConstVectorExpressionPointerFromPyObjectConverter<Math::VectorRange<const ConstVectorExpression<double> > >();
	ConstVectorExpressionPointerFromPyObjectConverter<Math::VectorRange<const ConstVectorExpression<long> > >();
	ConstVectorExpressionPointerFromPyObjectConverter<Math::VectorRange<const ConstVectorExpression<unsigned long> > >();

	VectorExpressionPointerFromPyObjectConverter<Math::VectorSlice<VectorExpression<float> > >();
	VectorExpressionPointerFromPyObjectConverter<Math::VectorSlice<VectorExpression<double> > >();
	VectorExpressionPointerFromPyObjectConverter<Math::VectorSlice<VectorExpression<long> > >();
	VectorExpressionPointerFromPyObjectConverter<Math::VectorSlice<VectorExpression<unsigned long> > >();

	ConstVectorExpressionPointerFromPyObjectConverter<Math::VectorSlice<const ConstVectorExpression<float> > >();
	ConstVectorExpressionPointerFromPyObjectConverter<Math::VectorSlice<const ConstVectorExpression<double> > >();
	ConstVectorExpressionPointerFromPyObjectConverter<Math::VectorSlice<const ConstVectorExpression<long> > >();
	ConstVectorExpressionPointerFromPyObjectConverter<Math::VectorSlice<const ConstVectorExpression<unsigned long> > >();

	// MatrixProxy Types

	MatrixExpressionPointerFromPyObjectConverter<Math::MatrixRange<MatrixExpression<float> > >();
	MatrixExpressionPointerFromPyObjectConverter<Math::MatrixRange<MatrixExpression<double> > >();
	MatrixExpressionPointerFromPyObjectConverter<Math::MatrixRange<MatrixExpression<long> > >();
	MatrixExpressionPointerFromPyObjectConverter<Math::MatrixRange<MatrixExpression<unsigned long> > >();

	ConstMatrixExpressionPointerFromPyObjectConverter<Math::MatrixRange<const ConstMatrixExpression<float> > >();
	ConstMatrixExpressionPointerFromPyObjectConverter<Math::MatrixRange<const ConstMatrixExpression<double> > >();
	ConstMatrixExpressionPointerFromPyObjectConverter<Math::MatrixRange<const ConstMatrixExpression<long> > >();
	ConstMatrixExpressionPointerFromPyObjectConverter<Math::MatrixRange<const ConstMatrixExpression<unsigned long> > >();

	MatrixExpressionPointerFromPyObjectConverter<Math::MatrixSlice<MatrixExpression<float> > >();
	MatrixExpressionPointerFromPyObjectConverter<Math::MatrixSlice<MatrixExpression<double> > >();
	MatrixExpressionPointerFromPyObjectConverter<Math::MatrixSlice<MatrixExpression<long> > >();
	MatrixExpressionPointerFromPyObjectConverter<Math::MatrixSlice<MatrixExpression<unsigned long> > >();

	ConstMatrixExpressionPointerFromPyObjectConverter<Math::MatrixSlice<const ConstMatrixExpression<float> > >();
	ConstMatrixExpressionPointerFromPyObjectConverter<Math::MatrixSlice<const ConstMatrixExpression<double> > >();
	ConstMatrixExpressionPointerFromPyObjectConverter<Math::MatrixSlice<const ConstMatrixExpression<long> > >();
	ConstMatrixExpressionPointerFromPyObjectConverter<Math::MatrixSlice<const ConstMatrixExpression<unsigned long> > >();

	VectorExpressionPointerFromPyObjectConverter<Math::MatrixRow<MatrixExpression<float> > >();
	VectorExpressionPointerFromPyObjectConverter<Math::MatrixRow<MatrixExpression<double> > >();
	VectorExpressionPointerFromPyObjectConverter<Math::MatrixRow<MatrixExpression<long> > >();
	VectorExpressionPointerFromPyObjectConverter<Math::MatrixRow<MatrixExpression<unsigned long> > >();

	ConstVectorExpressionPointerFromPyObjectConverter<Math::MatrixRow<const ConstMatrixExpression<float> > >();
	ConstVectorExpressionPointerFromPyObjectConverter<Math::MatrixRow<const ConstMatrixExpression<double> > >();
	ConstVectorExpressionPointerFromPyObjectConverter<Math::MatrixRow<const ConstMatrixExpression<long> > >();
	ConstVectorExpressionPointerFromPyObjectConverter<Math::MatrixRow<const ConstMatrixExpression<unsigned long> > >();

	VectorExpressionPointerFromPyObjectConverter<Math::MatrixColumn<MatrixExpression<float> > >();
	VectorExpressionPointerFromPyObjectConverter<Math::MatrixColumn<MatrixExpression<double> > >();
	VectorExpressionPointerFromPyObjectConverter<Math::MatrixColumn<MatrixExpression<long> > >();
	VectorExpressionPointerFromPyObjectConverter<Math::MatrixColumn<MatrixExpression<unsigned long> > >();

	ConstVectorExpressionPointerFromPyObjectConverter<Math::MatrixColumn<const ConstMatrixExpression<float> > >();
	ConstVectorExpressionPointerFromPyObjectConverter<Math::MatrixColumn<const ConstMatrixExpression<double> > >();
	ConstVectorExpressionPointerFromPyObjectConverter<Math::MatrixColumn<const ConstMatrixExpression<long> > >();
	ConstVectorExpressionPointerFromPyObjectConverter<Math::MatrixColumn<const ConstMatrixExpression<unsigned long> > >();

	// MatrixAdapter Types

	MatrixExpressionPointerFromPyObjectConverter<Math::MatrixTranspose<MatrixExpression<float> > >();
	MatrixExpressionPointerFromPyObjectConverter<Math::MatrixTranspose<MatrixExpression<double> > >();
	MatrixExpressionPointerFromPyObjectConverter<Math::MatrixTranspose<MatrixExpression<long> > >();
	MatrixExpressionPointerFromPyObjectConverter<Math::MatrixTranspose<MatrixExpression<long double> > >();

	ConstMatrixExpressionPointerFromPyObjectConverter<Math::MatrixTranspose<const ConstMatrixExpression<float> > >();
	ConstMatrixExpressionPointerFromPyObjectConverter<Math::MatrixTranspose<const ConstMatrixExpression<double> > >();
	ConstMatrixExpressionPointerFromPyObjectConverter<Math::MatrixTranspose<const ConstMatrixExpression<long> > >();
	ConstMatrixExpressionPointerFromPyObjectConverter<Math::MatrixTranspose<const ConstMatrixExpression<long double> > >();

	ConstMatrixExpressionPointerFromPyObjectConverter<Math::TriangularAdapter<const ConstMatrixExpression<float>, Math::Upper> >();
	ConstMatrixExpressionPointerFromPyObjectConverter<Math::TriangularAdapter<const ConstMatrixExpression<float>, Math::UnitUpper> >();
	ConstMatrixExpressionPointerFromPyObjectConverter<Math::TriangularAdapter<const ConstMatrixExpression<float>, Math::Lower> >();
	ConstMatrixExpressionPointerFromPyObjectConverter<Math::TriangularAdapter<const ConstMatrixExpression<float>, Math::UnitLower> >();

	ConstMatrixExpressionPointerFromPyObjectConverter<Math::TriangularAdapter<const ConstMatrixExpression<double>, Math::Upper> >();
	ConstMatrixExpressionPointerFromPyObjectConverter<Math::TriangularAdapter<const ConstMatrixExpression<double>, Math::UnitUpper> >();
	ConstMatrixExpressionPointerFromPyObjectConverter<Math::TriangularAdapter<const ConstMatrixExpression<double>, Math::Lower> >();
	ConstMatrixExpressionPointerFromPyObjectConverter<Math::TriangularAdapter<const ConstMatrixExpression<double>, Math::UnitLower> >();

	ConstMatrixExpressionPointerFromPyObjectConverter<Math::TriangularAdapter<const ConstMatrixExpression<long>, Math::Upper> >();
	ConstMatrixExpressionPointerFromPyObjectConverter<Math::TriangularAdapter<const ConstMatrixExpression<long>, Math::UnitUpper> >();
	ConstMatrixExpressionPointerFromPyObjectConverter<Math::TriangularAdapter<const ConstMatrixExpression<long>, Math::Lower> >();
	ConstMatrixExpressionPointerFromPyObjectConverter<Math::TriangularAdapter<const ConstMatrixExpression<long>, Math::UnitLower> >();

	ConstMatrixExpressionPointerFromPyObjectConverter<Math::TriangularAdapter<const ConstMatrixExpression<unsigned long>, Math::Upper> >();
	ConstMatrixExpressionPointerFromPyObjectConverter<Math::TriangularAdapter<const ConstMatrixExpression<unsigned long>, Math::UnitUpper> >();
	ConstMatrixExpressionPointerFromPyObjectConverter<Math::TriangularAdapter<const ConstMatrixExpression<unsigned long>, Math::Lower> >();
	ConstMatrixExpressionPointerFromPyObjectConverter<Math::TriangularAdapter<const ConstMatrixExpression<unsigned long>, Math::UnitLower> >();

	// VectorAdapter Types

	QuaternionExpressionPointerFromPyObjectConverter<Math::VectorQuaternionAdapter<VectorExpression<float> > >();
	QuaternionExpressionPointerFromPyObjectConverter<Math::VectorQuaternionAdapter<VectorExpression<double> > >();
	QuaternionExpressionPointerFromPyObjectConverter<Math::VectorQuaternionAdapter<VectorExpression<long> > >();
	QuaternionExpressionPointerFromPyObjectConverter<Math::VectorQuaternionAdapter<VectorExpression<unsigned long> > >();

	ConstQuaternionExpressionPointerFromPyObjectConverter<Math::VectorQuaternionAdapter<const ConstVectorExpression<float> > >();
	ConstQuaternionExpressionPointerFromPyObjectConverter<Math::VectorQuaternionAdapter<const ConstVectorExpression<double> > >();
	ConstQuaternionExpressionPointerFromPyObjectConverter<Math::VectorQuaternionAdapter<const ConstVectorExpression<long> > >();
	ConstQuaternionExpressionPointerFromPyObjectConverter<Math::VectorQuaternionAdapter<const ConstVectorExpression<unsigned long> > >();

	// QuaternionAdapter Types

	VectorExpressionPointerFromPyObjectConverter<Math::QuaternionVectorAdapter<QuaternionExpression<float> > >();
	VectorExpressionPointerFromPyObjectConverter<Math::QuaternionVectorAdapter<QuaternionExpression<double> > >();
	VectorExpressionPointerFromPyObjectConverter<Math::QuaternionVectorAdapter<QuaternionExpression<long> > >();
	VectorExpressionPointerFromPyObjectConverter<Math::QuaternionVectorAdapter<QuaternionExpression<unsigned long> > >();

	ConstVectorExpressionPointerFromPyObjectConverter<Math::QuaternionVectorAdapter<const ConstQuaternionExpression<float> > >();
	ConstVectorExpressionPointerFromPyObjectConverter<Math::QuaternionVectorAdapter<const ConstQuaternionExpression<double> > >();
	ConstVectorExpressionPointerFromPyObjectConverter<Math::QuaternionVectorAdapter<const ConstQuaternionExpression<long> > >();
	ConstVectorExpressionPointerFromPyObjectConverter<Math::QuaternionVectorAdapter<const ConstQuaternionExpression<unsigned long> > >();

	// Variant Converters

	CDPLPythonBase::GenericVariantFromPythonConverter<Math::DMatrix::SharedPointer>();
	CDPLPythonBase::GenericVariantFromPythonConverter<Math::LMatrix::SharedPointer>();
	CDPLPythonBase::GenericVariantFromPythonConverter<Math::ULMatrix::SharedPointer>();

	CDPLPythonBase::GenericVariantFromPythonConverter<Math::DVector::SharedPointer>();
	CDPLPythonBase::GenericVariantFromPythonConverter<Math::LVector::SharedPointer>();
	CDPLPythonBase::GenericVariantFromPythonConverter<Math::ULVector::SharedPointer>();

	CDPLPythonBase::GenericVariantFromPythonConverter<Math::Vector2DArray::SharedPointer>();
	CDPLPythonBase::GenericVariantFromPythonConverter<Math::Vector3DArray::SharedPointer>();
}
