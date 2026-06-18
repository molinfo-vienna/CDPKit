/* 
 * RegularSpatialGrid.hpp 
 *
 * Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
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
#include <memory>

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

        /**
         * \brief Reusable transformation traits used by Math::RegularSpatialGrid when the coordinate transform is a 4x4 matrix.
         * \tparam MatrixType The 4x4 transformation matrix type.
         */
        template <typename MatrixType>
        struct GridCoordinatesMatrixTransformTraits
        {

            /**
             * \brief Initializes \a mtx to the 4x4 identity matrix.
             * \param mtx The matrix to initialize.
             */
            static void init(MatrixType& mtx)
            {
                mtx.assign(IdentityMatrix<typename MatrixType::ValueType>(4, 4));
            }

            /**
             * \brief Computes \a inv_mtx as the inverse of \a mtx.
             * \tparam M The output matrix type.
             * \param mtx The matrix to invert.
             * \param inv_mtx The output matrix receiving the inverse.
             * \return \c true if \a mtx is invertible, and \c false otherwise.
             */
            template <typename M>
            static bool invert(const MatrixType& mtx, M& inv_mtx)
            {
                return Math::invert(mtx, inv_mtx);
            }

            /**
             * \brief Computes \a r as <tt>mtx * v</tt>.
             * \tparam V The input vector type.
             * \tparam R The output vector type.
             * \param mtx The transformation matrix.
             * \param v The input vector.
             * \param r The output vector receiving the transformed result.
             */
            template <typename V, typename R>
            static void transform(const MatrixType& mtx, const V& v, R& r)
            {
                prod(mtx, v, r);
            }
        };

        /**
         * \brief Primary traits template for grid-coordinate transformations of type \a T (left unspecialized; specialize for new transform types).
         * \tparam T The coordinate transformation type.
         */
        template <typename T>
        struct GridCoordinatesTransformTraits;

        /**
         * \brief Math::GridCoordinatesTransformTraits specialization for the fixed-size Math::CMatrix 4x4 transformation type.
         * \tparam T The matrix element value type.
         */
        template <typename T>
        struct GridCoordinatesTransformTraits<CMatrix<T, 4, 4> > : public GridCoordinatesMatrixTransformTraits<CMatrix<T, 4, 4> >
        {};

        /**
         * \brief Math::GridCoordinatesTransformTraits specialization for the bounded Math::BoundedMatrix 4x4 transformation type.
         * \tparam T The matrix element value type.
         */
        template <typename T>
        struct GridCoordinatesTransformTraits<BoundedMatrix<T, 4, 4> > : public GridCoordinatesMatrixTransformTraits<BoundedMatrix<T, 4, 4> >
        {};


        /**
         * \brief 3D grid data structure combining a Math::Grid data store with a coordinate-system transformation
         *        that maps grid-cell indices to 3D world positions.
         *
         * \tparam T The grid cell value type.
         * \tparam C The coordinate (real) value type used in the world frame.
         * \tparam GD The underlying grid data container type (default: Math::Grid).
         * \tparam XF The transformation type that maps cell indices to world coordinates (default: Math::CMatrix \f$ 4 \times 4 \f$).
         */
        template <typename T, typename C = typename TypeTraits<T>::RealType, typename GD = Grid<T>, typename XF = CMatrix<C, 4, 4> >
        class RegularSpatialGrid : public GridExpression<RegularSpatialGrid<T, C, GD, XF> >
        {

            typedef RegularSpatialGrid<T, C, GD, XF> SelfType;

          public:
            /**
             * \brief The grid cell value type.
             */
            typedef T                                                       ValueType;

            /**
             * \brief The coordinate (real) value type used in the world frame.
             */
            typedef C                                                       CoordinatesValueType;

            /**
             * \brief The underlying grid data container type.
             */
            typedef GD                                                      GridDataType;

            /**
             * \brief The coordinate transformation type mapping cell indices to world coordinates.
             */
            typedef XF                                                      CoordinatesTransformType;

            /**
             * \brief The inverse coordinate transformation type.
             */
            typedef typename CoordinatesTransformType::MatrixTemporaryType  InvCoordinatesTransformType;

            /**
             * \brief Mutable reference type to a grid cell (degrades to ConstReference when the data container is \c const).
             */
            typedef typename std::conditional<std::is_const<GD>::value,
                                              typename GD::ConstReference,
                                              typename GD::Reference>::type Reference;

            /**
             * \brief Constant reference type to a grid cell.
             */
            typedef typename GD::ConstReference                             ConstReference;

            /**
             * \brief The unsigned size type used by the grid data container.
             */
            typedef typename GD::SizeType                                   SizeType;

            /**
             * \brief A signed size type used for offset arithmetic.
             */
            typedef std::ptrdiff_t                                          SSizeType;

            /**
             * \brief The signed difference type used by the grid data container.
             */
            typedef typename GD::DifferenceType                             DifferenceType;

            /**
             * \brief Closure type used when this grid appears inside another expression.
             */
            typedef SelfType                                                ClosureType;

            /**
             * \brief Constant closure type used when this grid appears inside another expression.
             */
            typedef const SelfType                                          ConstClosureType;

            /**
             * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %RegularSpatialGrid instances.
             */
            typedef std::shared_ptr<SelfType>                               SharedPointer;

            /**
             * \brief Constructs an empty grid with anisotropic per-axis step sizes.
             * \param xs The step size along the x-axis.
             * \param ys The step size along the y-axis.
             * \param zs The step size along the z-axis.
             */
            RegularSpatialGrid(const CoordinatesValueType& xs, const CoordinatesValueType& ys, const CoordinatesValueType& zs):
                xStep(xs), yStep(ys), zStep(zs)
            {

                GridCoordinatesTransformTraits<CoordinatesTransformType>::init(xform);
                GridCoordinatesTransformTraits<InvCoordinatesTransformType>::init(invXform);
            }

            /**
             * \brief Constructs the grid with anisotropic per-axis step sizes initialized to the supplied grid data.
             * \param data The grid data container.
             * \param xs The step size along the x-axis.
             * \param ys The step size along the y-axis.
             * \param zs The step size along the z-axis.
             */
            RegularSpatialGrid(const GridDataType& data, const CoordinatesValueType& xs, const CoordinatesValueType& ys, const CoordinatesValueType& zs):
                data(data), xStep(xs), yStep(ys), zStep(zs)
            {

                GridCoordinatesTransformTraits<CoordinatesTransformType>::init(xform);
                GridCoordinatesTransformTraits<InvCoordinatesTransformType>::init(invXform);
            }

            /**
             * \brief Constructs an empty grid with isotropic step size \a s on all three axes.
             * \param s The step size used on every axis.
             */
            explicit RegularSpatialGrid(const CoordinatesValueType& s):
                xStep(s), yStep(s), zStep(s)
            {

                GridCoordinatesTransformTraits<CoordinatesTransformType>::init(xform);
                GridCoordinatesTransformTraits<InvCoordinatesTransformType>::init(invXform);
            }

            /**
             * \brief Constructs the grid with isotropic step size \a s and the supplied grid data.
             * \param data The grid data container.
             * \param s The step size used on every axis.
             */
            RegularSpatialGrid(const GridDataType& data, const CoordinatesValueType& s):
                data(data), xStep(s), yStep(s), zStep(s)
            {

                GridCoordinatesTransformTraits<CoordinatesTransformType>::init(xform);
                GridCoordinatesTransformTraits<InvCoordinatesTransformType>::init(invXform);
            }

            /**
             * \brief Constructs a copy of the \c %RegularSpatialGrid instance \a usg.
             * \param usg The grid to copy.
             */
            RegularSpatialGrid(const RegularSpatialGrid& usg):
                data(usg.data), xStep(usg.xStep), yStep(usg.yStep), zStep(usg.zStep),
                xform(usg.xform), invXform(usg.invXform) {}

            /**
             * \brief Move-constructs the grid by moving \a usg.
             * \param usg The source grid (left in a valid but unspecified state).
             */
            RegularSpatialGrid(RegularSpatialGrid&& usg):
                data(std::move(usg.data)), xStep(usg.xStep), yStep(usg.yStep), zStep(usg.zStep),
                xform(usg.xform), invXform(usg.invXform) {}

            /**
             * \brief Virtual destructor.
             */
            virtual ~RegularSpatialGrid() {}

            /**
             * \brief Returns a mutable reference to the cell at the linear index \a i.
             * \param i The zero-based linear cell index.
             * \return A mutable reference to the cell value.
             */
            Reference operator()(SizeType i)
            {
                return data(i);
            }

            /**
             * \brief Returns a \c const reference to the cell at the linear index \a i.
             * \param i The zero-based linear cell index.
             * \return A \c const reference to the cell value.
             */
            ConstReference operator()(SizeType i) const
            {
                return data(i);
            }

            /**
             * \brief Returns a mutable reference to the cell at the (\a i, \a j, \a k) position.
             * \param i The zero-based first-dimension index.
             * \param j The zero-based second-dimension index.
             * \param k The zero-based third-dimension index.
             * \return A mutable reference to the cell value.
             */
            Reference operator()(SizeType i, SizeType j, SizeType k)
            {
                return data(i, j, k);
            }

            /**
             * \brief Returns a \c const reference to the cell at the (\a i, \a j, \a k) position.
             * \param i The zero-based first-dimension index.
             * \param j The zero-based second-dimension index.
             * \param k The zero-based third-dimension index.
             * \return A \c const reference to the cell value.
             */
            ConstReference operator()(SizeType i, SizeType j, SizeType k) const
            {
                return data(i, j, k);
            }

            /**
             * \brief Returns the total number of cells of the grid.
             * \return The total cell count.
             */
            SizeType getSize() const
            {
                return data.getSize();
            }

            /**
             * \brief Returns the size of the grid along the first dimension.
             * \return The first-dimension size.
             */
            SizeType getSize1() const
            {
                return data.getSize1();
            }

            /**
             * \brief Returns the size of the grid along the second dimension.
             * \return The second-dimension size.
             */
            SizeType getSize2() const
            {
                return data.getSize2();
            }

            /**
             * \brief Returns the size of the grid along the third dimension.
             * \return The third-dimension size.
             */
            SizeType getSize3() const
            {
                return data.getSize3();
            }

            /**
             * \brief Returns the maximum total number of cells the grid can hold.
             * \return The maximum total cell capacity.
             */
            SizeType getMaxSize() const
            {
                return data.getMaxSize();
            }

            /**
             * \brief Returns the maximum size of the grid along the first dimension.
             * \return The maximum first-dimension size.
             */
            SizeType getMaxSize1() const
            {
                return data.getMaxSize1();
            }

            /**
             * \brief Returns the maximum size of the grid along the second dimension.
             * \return The maximum second-dimension size.
             */
            SizeType getMaxSize2() const
            {
                return data.getMaxSize2();
            }

            /**
             * \brief Returns the maximum size of the grid along the third dimension.
             * \return The maximum third-dimension size.
             */
            SizeType getMaxSize3() const
            {
                return data.getMaxSize3();
            }

            /**
             * \brief Returns the per-cell step size along the x-axis.
             * \return The x-axis step size.
             */
            CoordinatesValueType getXStepSize() const
            {
                return xStep;
            }

            /**
             * \brief Returns the per-cell step size along the y-axis.
             * \return The y-axis step size.
             */
            CoordinatesValueType getYStepSize() const
            {
                return yStep;
            }

            /**
             * \brief Returns the per-cell step size along the z-axis.
             * \return The z-axis step size.
             */
            CoordinatesValueType getZStepSize() const
            {
                return zStep;
            }

            /**
             * \brief Sets the per-cell step size along the x-axis to \a xs.
             * \param xs The new x-axis step size.
             */
            void setXStepSize(const CoordinatesValueType& xs)
            {
                xStep = xs;
            }

            /**
             * \brief Sets the per-cell step size along the y-axis to \a ys.
             * \param ys The new y-axis step size.
             */
            void setYStepSize(const CoordinatesValueType& ys)
            {
                yStep = ys;
            }

            /**
             * \brief Sets the per-cell step size along the z-axis to \a zs.
             * \param zs The new z-axis step size.
             */
            void setZStepSize(const CoordinatesValueType& zs)
            {
                zStep = zs;
            }

            /**
             * \brief Returns the spatial extent of the grid along the x-axis (\f$ (\mathrm{size}_1 - 1) \cdot \mathrm{xStep} \f$ for non-empty grids).
             * \return The x-axis extent.
             */
            CoordinatesValueType getXExtent() const
            {
                return ((data.getSize1() <= 1 ? SizeType(0) : (data.getSize1() - 1)) * xStep);
            }

            /**
             * \brief Returns the spatial extent of the grid along the y-axis.
             * \return The y-axis extent.
             */
            CoordinatesValueType getYExtent() const
            {
                return ((data.getSize2() <= 1 ? SizeType(0) : (data.getSize2() - 1)) * yStep);
            }

            /**
             * \brief Returns the spatial extent of the grid along the z-axis.
             * \return The z-axis extent.
             */
            CoordinatesValueType getZExtent() const
            {
                return ((data.getSize3() <= 1 ? SizeType(0) : (data.getSize3() - 1)) * zStep);
            }

            /**
             * \brief Writes the world-space 3D position of the cell with linear index \a i into \a coords.
             * \tparam V The output vector type (must be indexable via <tt>operator[]</tt>).
             * \param i The zero-based linear cell index.
             * \param coords The output vector receiving the X/Y/Z position.
             */
            template <typename V>
            void getCoordinates(SizeType i, V& coords) const
            {
                SizeType z  = i / (getSize1() * getSize2());
                SizeType xy = i % (getSize1() * getSize2());
                SizeType y  = xy / getSize1();
                SizeType x  = xy % getSize1();

                getCoordinates(x, y, z, coords);
            }

            /**
             * \brief Writes the world-space 3D position of the cell at (\a i, \a j, \a k) into \a coords.
             * \tparam V The output vector type.
             * \param i The first-dimension cell index.
             * \param j The second-dimension cell index.
             * \param k The third-dimension cell index.
             * \param coords The output vector receiving the X/Y/Z position.
             */
            template <typename V>
            void getCoordinates(SSizeType i, SSizeType j, SSizeType k, V& coords) const
            {
                CVector<CoordinatesValueType, 4> local_coords;

                getLocalCoordinates(i, j, k, local_coords);
                local_coords(3) = CoordinatesValueType(1);

                CVector<CoordinatesValueType, 4> world_coords;
                GridCoordinatesTransformTraits<CoordinatesTransformType>::transform(xform, local_coords, world_coords);

                coords[0] = world_coords(0);
                coords[1] = world_coords(1);
                coords[2] = world_coords(2);
            }

            /**
             * \brief Writes the local-space 3D position of the cell at (\a i, \a j, \a k) into \a coords.
             *
             * Local coordinates are centered at the grid origin (the cell-center cell-index coordinate system
             * before applying the world-space transformation).
             *
             * \tparam V The output vector type.
             * \param i The first-dimension cell index.
             * \param j The second-dimension cell index.
             * \param k The third-dimension cell index.
             * \param coords The output vector receiving the local X/Y/Z position.
             */
            template <typename V>
            void getLocalCoordinates(SSizeType i, SSizeType j, SSizeType k, V& coords) const
            {
                coords[0] = i * xStep - getXExtent() * CoordinatesValueType(0.5);
                coords[1] = j * yStep - getYExtent() * CoordinatesValueType(0.5);
                coords[2] = k * zStep - getZExtent() * CoordinatesValueType(0.5);
            }

            /**
             * \brief Transforms the world-space point \a world_coords into the grid's local coordinate frame and stores the result in \a local_coords.
             * \tparam V1 The input vector type.
             * \tparam V2 The output vector type.
             * \param world_coords The input world-space 3D position.
             * \param local_coords The output vector receiving the local-frame 3D position.
             */
            template <typename V1, typename V2>
            void getLocalCoordinates(const V1& world_coords, V2& local_coords) const
            {
                CVector<CoordinatesValueType, 4> tmp_local_coords;

                transformToLocalCoordinates(world_coords, tmp_local_coords);

                local_coords[0] = tmp_local_coords[0];
                local_coords[1] = tmp_local_coords[1];
                local_coords[2] = tmp_local_coords[2];
            }

            /**
             * \brief Tells whether the world-space point \a pos lies within the grid bounds.
             * \tparam V The point-vector type.
             * \param pos The world-space 3D position to test.
             * \return \c true if \a pos is inside the grid, and \c false otherwise.
             */
            template <typename V>
            bool containsPoint(const V& pos) const
            {
                CVector<CoordinatesValueType, 4> local_coords;

                transformToLocalCoordinates(pos, local_coords);

                return containsLocalPoint(local_coords);
            }

            /**
             * \brief Tells whether the local-space point \a pos lies within the grid bounds.
             * \tparam V The point-vector type.
             * \param pos The local-frame 3D position to test.
             * \return \c true if \a pos is inside the grid, and \c false otherwise.
             */
            template <typename V>
            bool containsLocalPoint(const V& pos) const
            {
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

            /**
             * \brief Writes the (i, j, k) cell indices of the cell containing the world-space point \a pos into \a indices.
             * \tparam V1 The input point type.
             * \tparam V2 The output indices type.
             * \param pos The world-space 3D position.
             * \param indices The output vector receiving the three cell indices.
             */
            template <typename V1, typename V2>
            void getContainingCell(const V1& pos, V2& indices) const
            {
                CVector<CoordinatesValueType, 4> local_coords;

                transformToLocalCoordinates(pos, local_coords);

                getLocalContainingCell(local_coords, indices);
            }

            /**
             * \brief Writes the (i, j, k) cell indices of the cell containing the local-space point \a pos into \a indices.
             * \tparam V1 The input point type.
             * \tparam V2 The output indices type.
             * \param pos The local-frame 3D position.
             * \param indices The output vector receiving the three cell indices.
             */
            template <typename V1, typename V2>
            void getLocalContainingCell(const V1& pos, V2& indices) const
            {
                CoordinatesValueType x = pos[0] + getXExtent() * CoordinatesValueType(0.5);
                CoordinatesValueType y = pos[1] + getYExtent() * CoordinatesValueType(0.5);
                CoordinatesValueType z = pos[2] + getZExtent() * CoordinatesValueType(0.5);

                indices[0] = SSizeType(std::floor(x / xStep));
                indices[1] = SSizeType(std::floor(y / yStep));
                indices[2] = SSizeType(std::floor(z / zStep));
            }

            /**
             * \brief Tells whether the grid is empty (zero cells along any dimension).
             * \return \c true if the grid is empty, and \c false otherwise.
             */
            bool isEmpty() const
            {
                return data.isEmpty();
            }

            /**
             * \brief Returns a \c const reference to the underlying grid data container.
             * \return A \c const reference to the grid data.
             */
            const GridDataType& getData() const
            {
                return data;
            }

            /**
             * \brief Returns a mutable reference to the underlying grid data container.
             * \return A mutable reference to the grid data.
             */
            GridDataType& getData()
            {
                return data;
            }

            /**
             * \brief Returns the coordinate transformation mapping cell-index coordinates to world coordinates.
             * \return A \c const reference to the transformation matrix.
             */
            const CoordinatesTransformType& getCoordinatesTransform() const
            {
                return xform;
            }

            /**
             * \brief Sets the cell-index to world-coordinate transformation to \a xform and caches its inverse.
             * \tparam T1 A type assignable to CoordinatesTransformType.
             * \param xform The new transformation.
             * \throw Base::CalculationFailed if the transformation cannot be inverted (only when math checks are enabled).
             */
            template <typename T1>
            void setCoordinatesTransform(const T1& xform)
            {
                this->xform = xform;
#ifdef CDPL_MATH_CHECKS_DISABLE
                GridCoordinatesTransformTraits<CoordinatesTransformType>::invert(xform, invXform);
#else
                CDPL_MATH_CHECK(GridCoordinatesTransformTraits<CoordinatesTransformType>::invert(xform, invXform),
                                "Inversion of transformation failed", Base::CalculationFailed);
#endif // CDPL_MATH_CHECKS_DISABLE
            }

            /**
             * \brief Copy-assigns from \a usg.
             * \param usg The source grid.
             * \return A reference to itself.
             */
            RegularSpatialGrid& operator=(const RegularSpatialGrid& usg)
            {
                data     = usg.data;
                xform    = usg.xform;
                invXform = usg.invXform;
                xStep    = usg.xStep;
                yStep    = usg.yStep;
                zStep    = usg.zStep;
                return *this;
            }

            /**
             * \brief Move-assigns from \a usg.
             * \param usg The source grid (left in a valid but unspecified state).
             * \return A reference to itself.
             */
            RegularSpatialGrid& operator=(RegularSpatialGrid&& usg)
            {
                data     = std::move(usg.data);
                xform    = usg.xform;
                invXform = usg.invXform;
                xStep    = usg.xStep;
                yStep    = usg.yStep;
                zStep    = usg.zStep;
                return *this;
            }

            /**
             * \brief Assigns the grid expression \a e to the underlying grid data (the spatial parameters are left unchanged).
             * \tparam E The source grid expression type.
             * \param e The source grid expression.
             * \return A reference to itself.
             */
            template <typename E>
            RegularSpatialGrid& operator=(const GridExpression<E>& e)
            {
                data.operator=(e);
                return *this;
            }

            /**
             * \brief Adds the grid expression \a e cell-wise to the underlying grid data.
             * \tparam E The source grid expression type.
             * \param e The grid expression to add.
             * \return A reference to itself.
             */
            template <typename E>
            RegularSpatialGrid& operator+=(const GridExpression<E>& e)
            {
                data.operator+=(e);
                return *this;
            }

            /**
             * \brief Subtracts the grid expression \a e cell-wise from the underlying grid data.
             * \tparam E The source grid expression type.
             * \param e The grid expression to subtract.
             * \return A reference to itself.
             */
            template <typename E>
            RegularSpatialGrid& operator-=(const GridExpression<E>& e)
            {
                data.operator-=(e);
                return *this;
            }

            /**
             * \brief Multiplies every cell by the scalar \a t.
             * \tparam T1 The scalar type.
             * \param t The scalar multiplier.
             * \return A reference to itself.
             */
            template <typename T1>
            typename std::enable_if<IsScalar<T>::value, RegularSpatialGrid>::type& operator*=(const T1& t)
            {
                data.operator*=(t);
                return *this;
            }

            /**
             * \brief Divides every cell by the scalar \a t.
             * \tparam T1 The scalar type.
             * \param t The scalar divisor.
             * \return A reference to itself.
             */
            template <typename T1>
            typename std::enable_if<IsScalar<T>::value, RegularSpatialGrid>::type& operator/=(const T1& t)
            {
                data.operator/=(t);
                return *this;
            }

            /**
             * \brief Assigns the grid expression \a e to the underlying grid data without intermediate temporary.
             * \tparam E The source grid expression type.
             * \param e The source grid expression.
             * \return A reference to itself.
             */
            template <typename E>
            RegularSpatialGrid& assign(const GridExpression<E>& e)
            {
                data.assign(e);
                return *this;
            }

            /**
             * \brief Adds the grid expression \a e to the underlying grid data without intermediate temporary.
             * \tparam E The source grid expression type.
             * \param e The source grid expression.
             * \return A reference to itself.
             */
            template <typename E>
            RegularSpatialGrid& plusAssign(const GridExpression<E>& e)
            {
                data.plusAssign(e);
                return *this;
            }

            /**
             * \brief Subtracts the grid expression \a e from the underlying grid data without intermediate temporary.
             * \tparam E The source grid expression type.
             * \param e The source grid expression.
             * \return A reference to itself.
             */
            template <typename E>
            RegularSpatialGrid& minusAssign(const GridExpression<E>& e)
            {
                data.minusAssign(e);
                return *this;
            }

            /**
             * \brief Swaps the contents of this grid with those of \a usg.
             * \param usg The grid to swap with.
             */
            void swap(RegularSpatialGrid& usg)
            {
                data.swap(usg.data);
                xform.swap(usg.xform);
                invXform.swap(usg.invXform);
                std::swap(xStep, usg.xStep);
                std::swap(yStep, usg.yStep);
                std::swap(zStep, usg.zStep);
            }

            /**
             * \brief ADL-enabled free-function form of swap().
             * \param usg1 The first grid.
             * \param usg2 The second grid.
             */
            friend void swap(RegularSpatialGrid& usg1, RegularSpatialGrid& usg2)
            {
                usg1.swap(usg2);
            }

            /**
             * \brief Sets every cell of the grid to the value \a v.
             * \param v The fill value.
             */
            void clear(const ValueType& v = ValueType())
            {
                data.clear(v);
            }

            /**
             * \brief Resizes the grid to \f$ m \times n \times o \f$ cells.
             * \param m The new first-dimension size.
             * \param n The new second-dimension size.
             * \param o The new third-dimension size.
             * \param preserve If \c true, existing cell values are kept where the indices remain valid. If \c false, all cells are set to \a v.
             * \param v The fill value used for newly added cells (and for all cells if \a preserve is \c false).
             */
            void resize(SizeType m, SizeType n, SizeType o, bool preserve = true, const ValueType& v = ValueType())
            {
                data.resize(m, n, o, preserve, v);
            }

          private:
            template <typename V1, typename V2>
            void transformToLocalCoordinates(const V1& coords, V2& local_coords) const
            {
                CVector<CoordinatesValueType, 4> world_coords;

                world_coords(0) = coords[0];
                world_coords(1) = coords[1];
                world_coords(2) = coords[2];
                world_coords(3) = CoordinatesValueType(1);

                GridCoordinatesTransformTraits<InvCoordinatesTransformType>::transform(invXform, world_coords, local_coords);
            }

            GridDataType                data;
            CoordinatesValueType        xStep;
            CoordinatesValueType        yStep;
            CoordinatesValueType        zStep;
            CoordinatesTransformType    xform;
            InvCoordinatesTransformType invXform;
        };

        /**
         * \brief Returns the trilinearly-interpolated value of \a grid at \a pos.
         * \tparam T The grid cell value type.
         * \tparam C The coordinate value type.
         * \tparam GD The underlying grid data container type.
         * \tparam XF The coordinate transformation type.
         * \tparam V The position vector type (indexable via <tt>operator[]</tt> for 3 components).
         * \param grid The regular spatial grid.
         * \param pos The query position.
         * \param local_pos If \c true, \a pos is interpreted as local (cell-index space) coordinates;
         *                  if \c false, \a pos is interpreted as world coordinates and converted via the inverse transform.
         * \return The trilinearly-interpolated cell value at \a pos (zero if \a grid is empty).
         */
        template <typename T, typename C, typename GD, typename XF, typename V>
        T interpolateTrilinear(const RegularSpatialGrid<T, C, GD, XF>& grid, const V& pos, bool local_pos)
        {
            typedef RegularSpatialGrid<T, C, GD, XF> GridType;

            typedef typename GridType::CoordinatesValueType CoordinatesValueType;
            typedef typename GridType::SSizeType            SSizeType;
            typedef typename GridType::ValueType            ValueType;

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

            inds_p1[0] = inds[0] + 1;
            inds_p1[1] = inds[1] + 1;
            inds_p1[2] = inds[2] + 1;

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
         * \brief Unbounded dense regular grid storing floating point values of type <tt>float</tt>.
         */
        typedef RegularSpatialGrid<float> FRegularSpatialGrid;

        /**
         * \brief Unbounded dense regular grid storing floating point values of type <tt>double</tt>.
         */
        typedef RegularSpatialGrid<double> DRegularSpatialGrid;
    } // namespace Math
} // namespace CDPL

#endif // CDPL_MATH_REGULARSPATIALGRID_HPP
