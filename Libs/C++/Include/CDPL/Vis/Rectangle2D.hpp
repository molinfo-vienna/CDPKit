/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * Rectangle2D.hpp 
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

/**
 * \file
 * \brief Definition of the class CDPL::Vis::Rectangle2D.
 */

#ifndef CDPL_VIS_RECTANGLE2D_HPP
#define CDPL_VIS_RECTANGLE2D_HPP

#include "CDPL/Vis/APIPrefix.hpp"
#include "CDPL/Math/Vector.hpp"


namespace CDPL 
{

	namespace Vis
	{

		/**
		 * \addtogroup CDPL_VIS_GEOMETRIC_PRIMITIVES
		 * @{
		 */

		/**
		 * \brief Specifies an axis aligned rectangular area in 2D space.
		 *
		 * The rectangle is defined by a minimum point \f$ (x_{min}, y_{min}) \f$ and a maximum point
		 * \f$ (x_{max}, y_{max}) \f$. For a well defined rectangle the coordinates of the minimum and 
		 * maximum point must satisfy the follwing inequalities: \f$ x_{min} \leq x_{max} \f$ and 
		 * \f$ y_{min} \leq y_{max} \f$.  
		 */
		class CDPL_VIS_API Rectangle2D
		{

		public:
			/**
			 * \brief Constructs an undefined rectangle.
			 *
			 * The coordinates of the minimum point are set to <tt>std::numeric_limits<double>::max()</tt>
			 * and the coordinates of the maximum point are set to \c -<tt>std::numeric_limits<double>::max()</tt>.
			 */
			Rectangle2D();

			/**
			 * \brief Constructs a rectangle with the minimum point set to \a min and the maximum point set to \a max.
			 * \param min The minimum point.
			 * \param max The maximum point.
			 */
			Rectangle2D(const Math::Vector2D& min, const Math::Vector2D& max);

			/**
			 * \brief Constructs a rectangle with the minimum point set to <em>(min_x, min_y)</em> and the
			 *        maximum point set to <em>(max_x, max_y)</em>.
			 * \param min_x The x-coordinate of the minimum point.
			 * \param min_y The y-coordinate of the minimum point.
			 * \param max_x The x-coordinate of the maximum point.
			 * \param max_y The y-coordinate of the maximum point.
			 */
			Rectangle2D(double min_x, double min_y, double max_x, double max_y);

			/**
			 * \brief Virtual destructor.
			 */
			virtual ~Rectangle2D() {}

			/**
			 * \brief Tells if the rectangle is well defined.
			 *
			 * The rectangle is well defined if neither the height nor the width of the rectangle is negative.
			 *
			 * \return \c true if the rectangle is defined, and \c false otherwise.
			 * \see getWidth(), getHeight()
			 */
			bool isDefined() const;

			/**
			 * \brief Adds the point \a pt to the current rectangle.
			 *
			 * The resulting (adjusted) rectangle represents the smallest rectangular area that contains both the original
			 * rectangle and the specified point \a pt.
			 *
			 * \param pt The point to add.
			 */
			void addPoint(const Math::Vector2D& pt);

			/**
			 * \brief Adds the point <em>(x, y)</em> to the current rectangle.
			 *
			 * The resulting (adjusted) rectangle represents the smallest rectangular area that contains both the original
			 * rectangle and the specified point <em>(x, y)</em>.
			 *
			 * \param x The x-coordinate of the point to add.
			 * \param y The y-coordinate of the point to add.
			 */
			void addPoint(double x, double y);

			/**
			 * \brief Extends the rectangle by adding a margin with the specified width and height.
			 *
			 * The minimum point gets translated by <em>(-width, -height)</em> and the maximum point by <em>(width, height)</em>.
			 *
			 * \param width The amount the rectangle will be extended horizontally.
			 * \param height The amount the rectangle will be extended vertically.
			 */
			void addMargin(double width, double height);

			/**
			 * \brief Adds the rectangle \a rect to the current rectangle.
			 *
			 * The resulting rectangle is the union of the two rectangle objects and contains both the original
			 * rectangle and the specified rectangle \a rect.
			 *
			 * \param rect The other rectangle to add.
			 */
			void addRectangle(const Rectangle2D& rect);

			/**
			 * \brief Tests if the point \a pt is within the boundary of the rectangle.
			 *
			 * A point lying exactly on one of the edges or corners is also considered to be within the boundaries.
			 *
			 * \param pt The point to test.
			 * \return \c true if \a pt is within the boundary of the rectangle, and \c false otherwise.  
			 */
			bool containsPoint(const Math::Vector2D& pt) const;

			/**
			 * \brief Tests if the point <em>(x, y)</em> is within the boundary of the rectangle.
			 *
			 * A point lying exactly on one of the edges or corners is also considered to be within the boundaries.
			 *
			 * \param x The x-coordinate of the point to test.
			 * \param y The y-coordinate of the point to test.
			 * \return \c true if the point <em>(x, y)</em> is within the boundary of the rectangle, and 
			 *         \c false otherwise.  
			 */
			bool containsPoint(double x, double y) const;

			/**
			 * \brief Tests if the specified rectangle \a rect is within the boundary of this rectangle.
			 *
			 * The result is equivalent to <tt>(this->containsPoint(rect.getMin()) && this->containsPoint(rect.getMax()))</tt>.
			 *
			 * \param rect The rectangle to test.
			 * \return \c true if the rectangle \a rect is within the boundary of this rectangle, and \c false otherwise.
			 */
			bool containsRectangle(const Rectangle2D& rect) const;

			/**
			 * \brief Tests if the interior of this rectangle intersects the rectangle \a rect.
			 *
			 * If the rectangles overlap only on one of their edges or corners, they are also considered to intersect.
			 *
			 * \param rect The rectangle to test.
			 * \return \c true if the rectangles intersect, and \c false otherwise.
			 */
			bool intersectsRectangle(const Rectangle2D& rect) const;

			/**
			 * \brief Sets the minimum point of the rectangle to \a pt.
			 * \param pt The new minimum point.
			 */
			void setMin(const Math::Vector2D& pt);
	
			/**
			 * \brief Sets the minimum point of the rectangle to <em>(x, y)</em>.
			 * \param x The x-coordinate of the new minimum point.
			 * \param y The y-coordinate of the new minimum point.
			 */	
			void setMin(double x, double y);

			/**
			 * \brief Sets the maximum point of the rectangle to \a pt.
			 * \param pt The new maximum point.
			 */
			void setMax(const Math::Vector2D& pt);

			/**
			 * \brief Sets the maximum point of the rectangle to <em>(x, y)</em>.
			 * \param x The x-coordinate of the new maximum point.
			 * \param y The y-coordinate of the new maximum point.
			 */	
			void setMax(double x, double y);
		
			/**
			 * \brief Sets the minimum point of the rectangle to <em>(min_x, min_y)</em> and the maximum point to <em>(max_x, max_y)</em>.
			 * \param min_x The x-coordinate of the new minimum point.
			 * \param min_y The y-coordinate of the new minimum point.
			 * \param max_x The x-coordinate of the new maximum point.
			 * \param max_y The y-coordinate of the new maximum point.
			 */
			void setBounds(double min_x, double min_y, double max_x, double max_y);
	
			/**
			 * \brief Sets the minimum point of the rectangle to \a min and the maximum point to \a max.
			 * \param min The new minimum point.
			 * \param max The new maximum point.
			 */
			void setBounds(const Math::Vector2D& min, const Math::Vector2D& max);

			/**
			 * \brief Returns the minimum point of the rectangle.
			 * \return The minimum point of the rectangle.
			 */
			const Math::Vector2D& getMin() const;

			/**
			 * \brief Returns the maximum point of the rectangle.
			 * \return The maximum point of the rectangle.
			 */
			const Math::Vector2D& getMax() const;

			/**
			 * \brief Calculates the center of the rectangle.
			 * \return The center of the rectangle.
			 */
			Math::Vector2D getCenter() const;
		
			/**
			 * \brief Calculates the center of the rectangle and stores the result in \a ctr.
			 * \param ctr A vector storing the calculated center point.
			 */
			void getCenter(Math::Vector2D& ctr) const;

			/**
			 * \brief Returns the width of the rectangle.
			 *
			 * The width of the rectangle is the difference \f$ x_{max} - x_{min} \f$ between the x-coordinate of the
			 * maximum point \f$ x_{max} \f$ and the x-coordinate of the minimum point \f$ x_{min} \f$.
			 *
			 * \return The width of the rectangle.
			 */
			double getWidth() const;

			/**
			 * \brief Returns the height of the rectangle.
			 *
			 * The height of the rectangle is the difference \f$ y_{max} - y_{min} \f$ between the y-coordinate of the
			 * maximum point \f$ y_{max} \f$ and the y-coordinate of the minimum point \f$ y_{min} \f$.
			 *
			 * \return The height of the rectangle.
			 */	
			double getHeight() const;

			/**
			 * \brief Calculates the area of the rectangle.
			 * \return The calculated area of the rectangle.
			 */
			double getArea() const;

			/**
			 * \brief Resets the rectangle to an undefinded state.
			 *
			 * The coordinates of the minimum point are set to <tt>std::numeric_limits<double>::max()</tt>
			 * and the coordinates of the maximum point are set to \c -<tt>std::numeric_limits<double>::max()</tt>.
			 */
			void reset();

			/**
			 * \brief Translates the minimum and maximum point of the rectangle by \a vec.
			 * \param vec The translation vector.
			 */
			void translate(const Math::Vector2D& vec);

			/**
			 * \brief Scales the minimum and maximum point of the rectangle by the specified factor.
			 * \param factor The scaling factor.
			 */
			void scale(double factor);
	
			/**
			 * \brief Equality comparison operator.
			 * \param rect The other \c %Rectangle2D object to be compared with.
			 * \return \c true if the minimum and maximum points compare equal, and \c false otherwise.
			 */
			bool operator==(const Rectangle2D& rect) const;
		
			/**
			 * \brief Inequality comparison operator.
			 *
			 * The result is equivalent to <tt>!(*this == rect)</tt>.
			 *
			 * \param rect The other \c %Rectangle2D object to be compared with.
			 * \return \c true if either the minimum or maximum points compare non-equal, and \c false otherwise.
			 */			
			bool operator!=(const Rectangle2D& rect) const;

		private:
			Math::Vector2D min;
			Math::Vector2D max;
		};

		/**
		 * @}
		 */
	}
}

#endif // CDPL_VIS_RECTANGLE2D_HPP
