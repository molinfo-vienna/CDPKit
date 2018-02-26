/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * RegularSpatialGrid.hpp 
 *
 * Copyright (C) 2010-2011 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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
 * \brief Definition of a regular spatial grid data type.
 */

#ifndef CDPL_MATH_REGULARSPATIALGRID_HPP
#define CDPL_MATH_REGULARSPATIALGRID_HPP

#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/utility.hpp>
#include <boost/swap.hpp>
#include <boost/shared_ptr.hpp>

#include "CDPL/Math/Config.hpp"
#include "CDPL/Math/GridExpression.hpp"
#include "CDPL/Math/Grid.hpp"
#include "CDPL/Math/Matrix.hpp"
#include "CDPL/Math/Vector.hpp"
#include "CDPL/Math/TypeTraits.hpp"
#include "CDPL/Base/Exceptions.hpp"


namespace CDPL
{

	namespace Math
	{

		template <typename MatrixType>
		struct GridCoordinatesMatrixTransformTraits
		{

			static CDPL_MATH_INLINE void init(MatrixType& mtx) {
				mtx.assign(IdentityMatrix<typename MatrixType::ValueType>(4, 4));
			}

			template <typename M>
			static CDPL_MATH_INLINE bool invert(const MatrixType& mtx, M& inv_mtx) {
				return Math::invert(mtx, inv_mtx);
			}

			template <typename V, typename R>
			static CDPL_MATH_INLINE void transform(const MatrixType& mtx, const V& v, R& r) {
				prod(mtx, v, r);
			}
		};

		template <typename T>
		struct GridCoordinatesTransformTraits;

		template <typename T>
		struct GridCoordinatesTransformTraits<CMatrix<T, 4, 4> > : public GridCoordinatesMatrixTransformTraits<CMatrix<T, 4, 4> > {};
	
		template <typename T>
		struct GridCoordinatesTransformTraits<BoundedMatrix<T, 4, 4> > : public GridCoordinatesMatrixTransformTraits<BoundedMatrix<T, 4, 4> > {};


		template <typename T, typename C = typename TypeTraits<T>::RealType, typename GD = Grid<T>, typename XF = CMatrix<C, 4, 4> > 
		class RegularSpatialGrid : public GridExpression<RegularSpatialGrid<T, C, GD, XF> >
		{

			typedef RegularSpatialGrid<T, C, GD, XF> SelfType;

		public:
			enum DataMode 
			{

			    CELL,
				POINT
			};

			typedef T ValueType;
			typedef C CoordinatesValueType;
			typedef GD GridDataType;
			typedef XF CoordinatesTransformType;
			typedef typename CoordinatesTransformType::MatrixTemporaryType InvCoordinatesTransformType;
			typedef typename boost::mpl::if_<boost::is_const<GD>,
											 typename GD::ConstReference,
											 typename GD::Reference>::type Reference;
			typedef typename GD::ConstReference ConstReference;
			typedef typename GD::SizeType SizeType;
			typedef typename GD::DifferenceType DifferenceType;
			typedef SelfType ClosureType;
			typedef const SelfType ConstClosureType;
            typedef boost::shared_ptr<SelfType> SharedPointer;

			CDPL_MATH_INLINE RegularSpatialGrid(const CoordinatesValueType& xs, const CoordinatesValueType& ys, const CoordinatesValueType& zs): 
				dataMode(POINT), xStep(xs), yStep(ys), zStep(zs) {
				
				GridCoordinatesTransformTraits<CoordinatesTransformType>::init(xform);
				GridCoordinatesTransformTraits<InvCoordinatesTransformType>::init(invXform);
			}

			CDPL_MATH_INLINE RegularSpatialGrid(const GridDataType& data, const CoordinatesValueType& xs, const CoordinatesValueType& ys, const CoordinatesValueType& zs): 
				dataMode(POINT), data(data), xStep(xs), yStep(ys), zStep(zs) {
			
				GridCoordinatesTransformTraits<CoordinatesTransformType>::init(xform);
				GridCoordinatesTransformTraits<InvCoordinatesTransformType>::init(invXform);
			}
	
			explicit CDPL_MATH_INLINE RegularSpatialGrid(const CoordinatesValueType& s): 
				dataMode(POINT), xStep(s), yStep(s), zStep(s) {

				GridCoordinatesTransformTraits<CoordinatesTransformType>::init(xform);
				GridCoordinatesTransformTraits<InvCoordinatesTransformType>::init(invXform);
			}

			CDPL_MATH_INLINE RegularSpatialGrid(const GridDataType& data, const CoordinatesValueType& s): 
				dataMode(POINT), data(data), xStep(s), yStep(s), zStep(s) {

				GridCoordinatesTransformTraits<CoordinatesTransformType>::init(xform);
				GridCoordinatesTransformTraits<InvCoordinatesTransformType>::init(invXform);
			}

			virtual CDPL_MATH_INLINE ~RegularSpatialGrid() {}

			void setDataMode(DataMode mode) {
				dataMode = mode;
			}

			DataMode getDataMode() const {
				return dataMode;
			}

			CDPL_MATH_INLINE Reference operator()(SizeType i) {
				return data(i);
			}

			CDPL_MATH_INLINE ConstReference operator()(SizeType i) const {
				return data(i);
			}

			CDPL_MATH_INLINE Reference operator()(SizeType i, SizeType j, SizeType k) {
				return data(i, j, k);
			}

			CDPL_MATH_INLINE ConstReference operator()(SizeType i, SizeType j, SizeType k) const {
				return data(i, j, k);
			}

			CDPL_MATH_INLINE SizeType getSize() const {
				return data.getSize();
			}

			CDPL_MATH_INLINE SizeType getSize1() const {
				return data.getSize1();
			}

			CDPL_MATH_INLINE SizeType getSize2() const {
				return data.getSize2();
			}

			CDPL_MATH_INLINE SizeType getSize3() const {
				return data.getSize3();
			}

			CDPL_MATH_INLINE SizeType getMaxSize() const {
				return data.getMaxSize();
			}
	
			CDPL_MATH_INLINE SizeType getMaxSize1() const {
				return data.getMaxSize1();
			}

			CDPL_MATH_INLINE SizeType getMaxSize2() const {
				return data.getMaxSize2();
			}
		
			CDPL_MATH_INLINE SizeType getMaxSize3() const {
				return data.getMaxSize3();
			}
		
			CDPL_MATH_INLINE CoordinatesValueType getXStepSize() const {
				return xStep;
			}
		
			CDPL_MATH_INLINE CoordinatesValueType getYStepSize() const {
				return yStep;
			}
		
			CDPL_MATH_INLINE CoordinatesValueType getZStepSize() const {
				return zStep;
			}

			CDPL_MATH_INLINE void setXStepSize(const CoordinatesValueType& xs) {
				xStep = xs;
			}
	
			CDPL_MATH_INLINE void setYStepSize(const CoordinatesValueType& ys) {
				yStep = ys;
			}

			CDPL_MATH_INLINE void setZStepSize(const CoordinatesValueType& zs) {
				zStep = zs;
			}

			CDPL_MATH_INLINE CoordinatesValueType getXExtent() const {
				return (data.getSize1() * xStep); 
			}

			CDPL_MATH_INLINE CoordinatesValueType getYExtent() const {
				return (data.getSize2() * yStep); 
			}

			CDPL_MATH_INLINE CoordinatesValueType getZExtent() const {
				return (data.getSize3() * zStep); 
			}

			template <typename V>
			CDPL_MATH_INLINE void getCoordinates(SizeType i, V& coords) const {
				SizeType z = i / (getSize1() * getSize2());
				SizeType xy = i % (getSize1() * getSize2());
				SizeType y = xy / getSize1();
				SizeType x = xy % getSize1();

				getCoordinates(x, y, z, coords);
			}
			
			template <typename V>
			CDPL_MATH_INLINE void getCoordinates(SizeType i, SizeType j, SizeType k, V& coords) const {
				CVector<CoordinatesValueType, 4> local_coords;
				
				getLocalCoordinates(i, j, k, local_coords);
				local_coords(3) = CoordinatesValueType(1);

				CVector<CoordinatesValueType, 4> world_coords;
				GridCoordinatesTransformTraits<CoordinatesTransformType>::transform(xform, local_coords, world_coords);
				
				coords[0] = world_coords(0);
				coords[1] = world_coords(1);
				coords[2] = world_coords(2);
			}

			template <typename V>
			CDPL_MATH_INLINE void getLocalCoordinates(SizeType i, SizeType j, SizeType k, V& coords) const {
				coords[0] = i * xStep + (xStep - getXExtent()) / 2;
				coords[1] = j * yStep + (yStep - getYExtent()) / 2;
				coords[2] = k * zStep + (zStep - getZExtent()) / 2;
			}

			template <typename V>
			CDPL_MATH_INLINE bool containsPoint(const V& pos) const {
				CVector<CoordinatesValueType, 4> local_coords;

				getLocalCoordinates(pos, local_coords);
				
				return containsLocalPoint(local_coords);
			}

			template <typename V>
			CDPL_MATH_INLINE bool containsLocalPoint(const V& pos) const {
				if (std::abs(CoordinatesValueType(pos[0])) > (getXExtent() / 2))
					return false;

				if (std::abs(CoordinatesValueType(pos[1])) > (getYExtent() / 2))
					return false;

				if (std::abs(CoordinatesValueType(pos[2])) > (getZExtent() / 2))
					return false;

				return true;
			}

			template <typename V1, typename V2>
			CDPL_MATH_INLINE bool getContainingCell(const V1& pos, V2& indices) const {
				CVector<CoordinatesValueType, 4> local_coords;

				getLocalCoordinates(pos, local_coords);

				return getLocalContainingCell(local_coords, indices);
			}

			template <typename V1, typename V2>
			CDPL_MATH_INLINE bool getLocalContainingCell(const V1& pos, V2& indices) const {
				CoordinatesValueType x = pos[0] + getXExtent() / 2;

				if (x < CoordinatesValueType(0))
					return false;

				CoordinatesValueType y = pos[1] + getYExtent() / 2;

				if (y < CoordinatesValueType(0))
					return false;

				CoordinatesValueType z = pos[2] + getZExtent() / 2;

				if (z < CoordinatesValueType(0))
					return false;

				SizeType i = std::floor(x / xStep); 

				if (i >= data.getSize1())
					return false;

				SizeType j = std::floor(y / yStep); 

				if (j >= data.getSize2())
					return false;

				SizeType k = std::floor(z / zStep); 

				if (k >= data.getSize3())
					return false;

				indices[0] = i;
				indices[1] = j;
				indices[2] = k;

				return true;
			}

			CDPL_MATH_INLINE bool isEmpty() const {
				return data.isEmpty();
			}
	
			CDPL_MATH_INLINE const GridDataType& getData() const {
				return data;
			}

			CDPL_MATH_INLINE GridDataType& getData() {
				return data;
			}

			CDPL_MATH_INLINE const CoordinatesTransformType& getCoordinatesTransform() const {
				return xform;
			}

			template <typename T1>
			CDPL_MATH_INLINE void setCoordinatesTransform(const T1& xform) {
				this->xform = xform;
				CDPL_MATH_CHECK(GridCoordinatesTransformTraits<CoordinatesTransformType>::invert(xform, invXform), "Inversion of transformation failed", Base::CalculationFailed);
			}

			CDPL_MATH_INLINE RegularSpatialGrid& operator=(const RegularSpatialGrid& usg) {
				dataMode = usg.dataMode;
				data = usg.data;
				xform = usg.xform;
				invXform = usg.invXform;
				xStep = usg.xStep;
				yStep = usg.yStep;
				zStep = usg.zStep;
				return *this;
			}

			template <typename E>
			CDPL_MATH_INLINE RegularSpatialGrid& operator=(const GridExpression<E>& e) {
				data.operator=(e);
				return *this;
			}

			template <typename E>
			CDPL_MATH_INLINE RegularSpatialGrid& operator+=(const GridExpression<E>& e) {
				data.operator+=(e);
				return *this;
			}	

			template <typename E>
			CDPL_MATH_INLINE RegularSpatialGrid& operator-=(const GridExpression<E>& e) {
				data.operator-=(e);
				return *this;
			}

			template <typename T1>
			CDPL_MATH_INLINE 
			typename boost::enable_if<IsScalar<T>, RegularSpatialGrid>::type& operator*=(const T1& t) {
				data.operator*=(t);
				return *this;
			}
	
			template <typename T1>
			CDPL_MATH_INLINE 
			typename boost::enable_if<IsScalar<T>, RegularSpatialGrid>::type& operator/=(const T1& t) {
				data.operator/=(t);
				return *this;
			}
			
			template <typename E>
			CDPL_MATH_INLINE RegularSpatialGrid& assign(const GridExpression<E>& e) {
				data.assign(e);
				return *this;
			}

			template <typename E>
			CDPL_MATH_INLINE RegularSpatialGrid& plusAssign(const GridExpression<E>& e) {
				data.plusAssign(e);
				return *this;
			}

			template <typename E>
			CDPL_MATH_INLINE RegularSpatialGrid& minusAssign(const GridExpression<E>& e) {
				data.minusAssign(e);
				return *this;
			}

			CDPL_MATH_INLINE void swap(RegularSpatialGrid& usg) {
				data.swap(usg.data);
				xform.swap(usg.xform);
				invXform.swap(usg.invXform);
				boost::swap(xStep, usg.xStep);
				boost::swap(yStep, usg.yStep);
				boost::swap(zStep, usg.zStep);
				boost::swap(dataMode, dataMode);
			}
	
			CDPL_MATH_INLINE friend void swap(RegularSpatialGrid& usg1, RegularSpatialGrid& usg2) {
				usg1.swap(usg2);
			}

			CDPL_MATH_INLINE void clear(const ValueType& v = ValueType()) {
				data.clear(v);
			}

			CDPL_MATH_INLINE void resize(SizeType m, SizeType n, SizeType o, bool preserve = true, const ValueType& v = ValueType()) {
				data.resize(m, n, o, preserve, v);
			}

		private:
			template <typename V1, typename V2>
			CDPL_MATH_INLINE void getLocalCoordinates(const V1& coords, V2& local_coords) const {
				CVector<CoordinatesValueType, 4> world_coords;
				
				world_coords(0) = coords[0];
				world_coords(1) = coords[1];
				world_coords(2) = coords[2];
				world_coords(3) = CoordinatesValueType(1);

				GridCoordinatesTransformTraits<InvCoordinatesTransformType>::transform(invXform, world_coords, local_coords);
			}

			DataMode                    dataMode;
			GridDataType                data;
			CoordinatesValueType        xStep;
			CoordinatesValueType        yStep;
			CoordinatesValueType        zStep;
			CoordinatesTransformType    xform;
			InvCoordinatesTransformType invXform;
		};

		/**
		 * \brief An unbounded dense regular grid in 3D space holding floating point values of type <tt>float</tt>.
		 */
		typedef RegularSpatialGrid<float> FRegularSpatialGrid;

		/**
		 * \brief An unbounded dense regular grid in 3D space holding floating point values of type <tt>double</tt>.
		 */
		typedef RegularSpatialGrid<double> DRegularSpatialGrid;
	}
}

#endif // CDPL_MATH_REGULARSPATIALGRID_HPP
