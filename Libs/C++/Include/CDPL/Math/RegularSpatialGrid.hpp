/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * RegularSpatialGrid.hpp 
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
 * \brief Definition of a regular spatial grid data type.
 */

#ifndef CDPL_MATH_REGULARSPATIALGRID_HPP
#define CDPL_MATH_REGULARSPATIALGRID_HPP

#include <type_traits>
#include <utility>

#include <boost/shared_ptr.hpp>

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

			static void init(MatrixType& mtx) {
				mtx.assign(IdentityMatrix<typename MatrixType::ValueType>(4, 4));
			}

			template <typename M>
			static bool invert(const MatrixType& mtx, M& inv_mtx) {
				return Math::invert(mtx, inv_mtx);
			}

			template <typename V, typename R>
			static void transform(const MatrixType& mtx, const V& v, R& r) {
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
			typedef typename std::conditional<std::is_const<GD>::value,
											 typename GD::ConstReference,
											 typename GD::Reference>::type Reference;
			typedef typename GD::ConstReference ConstReference;
			typedef typename GD::SizeType SizeType;
			typedef std::ptrdiff_t SSizeType;
			typedef typename GD::DifferenceType DifferenceType;
			typedef SelfType ClosureType;
			typedef const SelfType ConstClosureType;
            typedef boost::shared_ptr<SelfType> SharedPointer;

			RegularSpatialGrid(const CoordinatesValueType& xs, const CoordinatesValueType& ys, const CoordinatesValueType& zs): 
				dataMode(POINT), xStep(xs), yStep(ys), zStep(zs) {
				
				GridCoordinatesTransformTraits<CoordinatesTransformType>::init(xform);
				GridCoordinatesTransformTraits<InvCoordinatesTransformType>::init(invXform);
			}

			RegularSpatialGrid(const GridDataType& data, const CoordinatesValueType& xs, const CoordinatesValueType& ys, const CoordinatesValueType& zs): 
				dataMode(POINT), data(data), xStep(xs), yStep(ys), zStep(zs) {
			
				GridCoordinatesTransformTraits<CoordinatesTransformType>::init(xform);
				GridCoordinatesTransformTraits<InvCoordinatesTransformType>::init(invXform);
			}
	
			explicit RegularSpatialGrid(const CoordinatesValueType& s): 
				dataMode(POINT), xStep(s), yStep(s), zStep(s) {

				GridCoordinatesTransformTraits<CoordinatesTransformType>::init(xform);
				GridCoordinatesTransformTraits<InvCoordinatesTransformType>::init(invXform);
			}

			RegularSpatialGrid(const GridDataType& data, const CoordinatesValueType& s): 
				dataMode(POINT), data(data), xStep(s), yStep(s), zStep(s) {

				GridCoordinatesTransformTraits<CoordinatesTransformType>::init(xform);
				GridCoordinatesTransformTraits<InvCoordinatesTransformType>::init(invXform);
			}

			virtual ~RegularSpatialGrid() {}

			void setDataMode(DataMode mode) {
				dataMode = mode;
			}

			DataMode getDataMode() const {
				return dataMode;
			}

			Reference operator()(SizeType i) {
				return data(i);
			}

			ConstReference operator()(SizeType i) const {
				return data(i);
			}

			Reference operator()(SizeType i, SizeType j, SizeType k) {
				return data(i, j, k);
			}

			ConstReference operator()(SizeType i, SizeType j, SizeType k) const {
				return data(i, j, k);
			}

			SizeType getSize() const {
				return data.getSize();
			}

			SizeType getSize1() const {
				return data.getSize1();
			}

			SizeType getSize2() const {
				return data.getSize2();
			}

			SizeType getSize3() const {
				return data.getSize3();
			}

			SizeType getMaxSize() const {
				return data.getMaxSize();
			}
	
			SizeType getMaxSize1() const {
				return data.getMaxSize1();
			}

			SizeType getMaxSize2() const {
				return data.getMaxSize2();
			}
		
			SizeType getMaxSize3() const {
				return data.getMaxSize3();
			}
		
			CoordinatesValueType getXStepSize() const {
				return xStep;
			}
		
			CoordinatesValueType getYStepSize() const {
				return yStep;
			}
		
			CoordinatesValueType getZStepSize() const {
				return zStep;
			}

			void setXStepSize(const CoordinatesValueType& xs) {
				xStep = xs;
			}
	
			void setYStepSize(const CoordinatesValueType& ys) {
				yStep = ys;
			}

			void setZStepSize(const CoordinatesValueType& zs) {
				zStep = zs;
			}

			CoordinatesValueType getXExtent() const {
				if (dataMode == POINT)
					return (data.getSize1() * xStep); 

				return ((data.getSize1() <= 1 ? SizeType(0) : (data.getSize1() - 1)) * xStep); 
			}

			CoordinatesValueType getYExtent() const {
				if (dataMode == POINT)
					return (data.getSize2() * yStep); 

				return ((data.getSize2() <= 1 ? SizeType(0) : (data.getSize2() - 1)) * yStep); 
			}

			CoordinatesValueType getZExtent() const {
				if (dataMode == POINT)
					return (data.getSize3() * zStep); 

				return ((data.getSize3() <= 1 ? SizeType(0) : (data.getSize3() - 1)) * zStep); 
			}

			template <typename V>
			void getCoordinates(SizeType i, V& coords) const {
				SizeType z = i / (getSize1() * getSize2());
				SizeType xy = i % (getSize1() * getSize2());
				SizeType y = xy / getSize1();
				SizeType x = xy % getSize1();

				getCoordinates(x, y, z, coords);
			}
			
			template <typename V>
			void getCoordinates(SSizeType i, SSizeType j, SSizeType k, V& coords) const {
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
			void getLocalCoordinates(SSizeType i, SSizeType j, SSizeType k, V& coords) const {
				if (dataMode == POINT) {
					coords[0] = i * xStep + (xStep - getXExtent()) * CoordinatesValueType(0.5);
					coords[1] = j * yStep + (yStep - getYExtent()) * CoordinatesValueType(0.5);
					coords[2] = k * zStep + (zStep - getZExtent()) * CoordinatesValueType(0.5);
					return;
				}

				coords[0] = i * xStep - getXExtent() * CoordinatesValueType(0.5);
				coords[1] = j * yStep - getYExtent() * CoordinatesValueType(0.5);
				coords[2] = k * zStep - getZExtent() * CoordinatesValueType(0.5);
			}

			template <typename V1, typename V2>
			void getLocalCoordinates(const V1& world_coords, V2& local_coords) const {
				CVector<CoordinatesValueType, 4> tmp_local_coords;

				transformToLocalCoordinates(world_coords, tmp_local_coords);

				local_coords[0] = tmp_local_coords[0];
				local_coords[1] = tmp_local_coords[1];
				local_coords[2] = tmp_local_coords[2];
			}

			template <typename V>
			bool containsPoint(const V& pos) const {
				CVector<CoordinatesValueType, 4> local_coords;

				transformToLocalCoordinates(pos, local_coords);
				
				return containsLocalPoint(local_coords);
			}

			template <typename V>
			bool containsLocalPoint(const V& pos) const {
				if (CoordinatesValueType(pos[0]) >= (getXExtent() * CoordinatesValueType(0.5)))
					return false;

				if (CoordinatesValueType(pos[1]) >= (getYExtent() * CoordinatesValueType(0.5)))
					return false;

				if (CoordinatesValueType(pos[2]) >= (getZExtent() * CoordinatesValueType(0.5)))
					return false;
				
				if (CoordinatesValueType(pos[0]) < (-getXExtent() * CoordinatesValueType(0.5)))
					return false;

				if (CoordinatesValueType(pos[1]) < (-getYExtent() * CoordinatesValueType(0.5)))
					return false;

				if (CoordinatesValueType(pos[2]) < (-getZExtent() * CoordinatesValueType(0.5)))
					return false;

				return true;
			}

			template <typename V1, typename V2>
			void getContainingCell(const V1& pos, V2& indices) const {
				CVector<CoordinatesValueType, 4> local_coords;

				transformToLocalCoordinates(pos, local_coords);

				getLocalContainingCell(local_coords, indices);
			}

			template <typename V1, typename V2>
			void getLocalContainingCell(const V1& pos, V2& indices) const {
				CoordinatesValueType x = pos[0] + getXExtent() * CoordinatesValueType(0.5);
				CoordinatesValueType y = pos[1] + getYExtent() * CoordinatesValueType(0.5);
				CoordinatesValueType z = pos[2] + getZExtent() * CoordinatesValueType(0.5);

				indices[0] = SSizeType(std::floor(x / xStep)); 
				indices[1] = SSizeType(std::floor(y / yStep)); 
				indices[2] = SSizeType(std::floor(z / zStep)); 
			}

			bool isEmpty() const {
				return data.isEmpty();
			}
	
			const GridDataType& getData() const {
				return data;
			}

			GridDataType& getData() {
				return data;
			}

			const CoordinatesTransformType& getCoordinatesTransform() const {
				return xform;
			}

			template <typename T1>
			void setCoordinatesTransform(const T1& xform) {
				this->xform = xform;
				CDPL_MATH_CHECK(GridCoordinatesTransformTraits<CoordinatesTransformType>::invert(xform, invXform), "Inversion of transformation failed", Base::CalculationFailed);
			}

			RegularSpatialGrid& operator=(const RegularSpatialGrid& usg) {
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
			RegularSpatialGrid& operator=(const GridExpression<E>& e) {
				data.operator=(e);
				return *this;
			}

			template <typename E>
			RegularSpatialGrid& operator+=(const GridExpression<E>& e) {
				data.operator+=(e);
				return *this;
			}	

			template <typename E>
			RegularSpatialGrid& operator-=(const GridExpression<E>& e) {
				data.operator-=(e);
				return *this;
			}

			template <typename T1>
			typename std::enable_if<IsScalar<T>::value, RegularSpatialGrid>::type& operator*=(const T1& t) {
				data.operator*=(t);
				return *this;
			}
	
			template <typename T1>
			typename std::enable_if<IsScalar<T>::value, RegularSpatialGrid>::type& operator/=(const T1& t) {
				data.operator/=(t);
				return *this;
			}
			
			template <typename E>
			RegularSpatialGrid& assign(const GridExpression<E>& e) {
				data.assign(e);
				return *this;
			}

			template <typename E>
			RegularSpatialGrid& plusAssign(const GridExpression<E>& e) {
				data.plusAssign(e);
				return *this;
			}

			template <typename E>
			RegularSpatialGrid& minusAssign(const GridExpression<E>& e) {
				data.minusAssign(e);
				return *this;
			}

			void swap(RegularSpatialGrid& usg) {
				data.swap(usg.data);
				xform.swap(usg.xform);
				invXform.swap(usg.invXform);
				std::swap(xStep, usg.xStep);
				std::swap(yStep, usg.yStep);
				std::swap(zStep, usg.zStep);
				std::swap(dataMode, dataMode);
			}
	
			friend void swap(RegularSpatialGrid& usg1, RegularSpatialGrid& usg2) {
				usg1.swap(usg2);
			}

			void clear(const ValueType& v = ValueType()) {
				data.clear(v);
			}

			void resize(SizeType m, SizeType n, SizeType o, bool preserve = true, const ValueType& v = ValueType()) {
				data.resize(m, n, o, preserve, v);
			}

		private:
			template <typename V1, typename V2>
			void transformToLocalCoordinates(const V1& coords, V2& local_coords) const {
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

		template <typename T, typename C, typename GD, typename XF, typename V> 
		T interpolateTrilinear(const RegularSpatialGrid<T, C, GD, XF>& grid, const V& pos, bool local_pos)
		{
			typedef RegularSpatialGrid<T, C, GD, XF> GridType;

			typedef typename GridType::CoordinatesValueType CoordinatesValueType;
			typedef typename GridType::SSizeType SSizeType;
			typedef typename GridType::ValueType ValueType;

			if (grid.isEmpty())
				return CoordinatesValueType();

			CoordinatesValueType loc_pos[3];

			if (local_pos) {
				loc_pos[0] = pos[0];
				loc_pos[1] = pos[1];
				loc_pos[2] = pos[2];

			} else 
				grid.getLocalCoordinates(pos, loc_pos);

			SSizeType inds[3];

			grid.getLocalContainingCell(loc_pos, inds);
			
			CoordinatesValueType xyz0[3];

			grid.getLocalCoordinates(inds[0], inds[1], inds[2], xyz0);

			SSizeType inds_p1[3];

			if (grid.getDataMode() == GridType::POINT) {
				bool recalc_xyz0 = false;

				if (loc_pos[0] < xyz0[0]) {
					inds_p1[0] = inds[0];
					inds[0] -= 1; 
					recalc_xyz0 = true;

				} else
					inds_p1[0] = inds[0] + 1;

				if (loc_pos[1] < xyz0[1]) {
					inds_p1[1] = inds[1];
					inds[1] -= 1; 
					recalc_xyz0 = true;

				} else
					inds_p1[1] = inds[1] + 1;

				if (loc_pos[2] < xyz0[2]) {
					inds_p1[2] = inds[2];
					inds[2] -= 1; 
					recalc_xyz0 = true;

				} else
					inds_p1[2] = inds[2] + 1;

				if (recalc_xyz0)
					grid.getLocalCoordinates(inds[0], inds[1], inds[2], xyz0);

			} else {
				inds_p1[0] = inds[0] + 1;
				inds_p1[1] = inds[1] + 1;
				inds_p1[2] = inds[2] + 1;
			}

			inds[0] = std::max(SSizeType(0), inds[0]);
			inds[1] = std::max(SSizeType(0), inds[1]);
			inds[2] = std::max(SSizeType(0), inds[2]);
		
			inds[0] = std::min(SSizeType(grid.getSize1() - 1), inds[0]);
			inds[1] = std::min(SSizeType(grid.getSize2() - 1), inds[1]);
			inds[2] = std::min(SSizeType(grid.getSize3() - 1), inds[2]);
		
			inds_p1[0] = std::max(SSizeType(0), inds_p1[0]);
			inds_p1[1] = std::max(SSizeType(0), inds_p1[1]);
			inds_p1[2] = std::max(SSizeType(0), inds_p1[2]);
		
			inds_p1[0] = std::min(SSizeType(grid.getSize1() - 1), inds_p1[0]);
			inds_p1[1] = std::min(SSizeType(grid.getSize2() - 1), inds_p1[1]);
			inds_p1[2] = std::min(SSizeType(grid.getSize3() - 1), inds_p1[2]);
		
			CoordinatesValueType xd = (loc_pos[0] - xyz0[0]) / grid.getXStepSize();
			CoordinatesValueType yd = (loc_pos[1] - xyz0[1]) / grid.getYStepSize();
			CoordinatesValueType zd = (loc_pos[2] - xyz0[2]) / grid.getZStepSize();

			ValueType c00 = grid(inds[0], inds[1], inds[2]) * (1 - xd) + grid(inds_p1[0], inds[1], inds[2]) * xd;
			ValueType c01 = grid(inds[0], inds[1], inds_p1[2]) * (1 - xd) + grid(inds_p1[0], inds[1], inds_p1[2]) * xd;
			ValueType c10 = grid(inds[0], inds_p1[1], inds[2]) * (1 - xd) + grid(inds_p1[0], inds_p1[1], inds[2]) * xd;
			ValueType c11 = grid(inds[0], inds_p1[1], inds_p1[2]) * (1 - xd) + grid(inds_p1[0], inds_p1[1], inds_p1[2]) * xd;

			ValueType c0 = c00 * (1 - yd) + c10 * yd;
			ValueType c1 = c01 * (1 - yd) + c11 * yd;

			ValueType c = c0 * (1 - zd) + c1 * zd;

			return c;
		}
	
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
