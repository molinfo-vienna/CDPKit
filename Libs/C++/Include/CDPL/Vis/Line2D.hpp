/* 
 * Line2D.hpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
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
 * \brief Definition of the class CDPL::Vis::Line2D.
 */

#ifndef CDPL_VIS_LINE2D_HPP
#define CDPL_VIS_LINE2D_HPP

#include "CDPL/Vis/APIPrefix.hpp"
#include "CDPL/Math/Vector.hpp"


namespace CDPL 
{

    namespace Vis
    {

        class Rectangle2D;

        /**
         * \brief Specifies a line segment in 2D space.
         */
        class CDPL_VIS_API Line2D
        {

        public:
            /**
             * \brief Constructs a line whose starting and end point is set to <em>(0, 0)</em>.
             */
            Line2D();

            /**
             * \brief Constructs a line with the specified starting and end point.
             * \param beg The starting point.
             * \param end The end point.
             */
            Line2D(const Math::Vector2D& beg, const Math::Vector2D& end);

            /**
             * \brief Constructs a line with the starting point set to <em>(beg_x, beg_y)</em> and the end point
             *        set to <em>(end_x, end_y)</em>.
             * \param beg_x The x-coordinate of the starting point.
             * \param beg_y The y-coordinate of the starting point.
             * \param end_x The x-coordinate of the end point.
             * \param end_y The y-coordinate of the end point.
             */
            Line2D(double beg_x, double beg_y, double end_x, double end_y);
    
            /**
             * \brief Virtual destructor.
             */
            virtual ~Line2D() {}

            /**
             * \brief Sets the starting point of the line to \a pt.
             * \param pt The new starting point of the line.
             */
            void setBegin(const Math::Vector2D& pt);

            /**
             * \brief Sets the starting point of the line to <em>(x, y)</em>.
             * \param x The x-coordinate of the new starting point.
             * \param y The y-coordinate of the new starting point.
             */
            void setBegin(double x, double y);

            /**
             * \brief Returns the starting point of the line.
             * \return The starting point of the line.
             */
            const Math::Vector2D& getBegin() const;

            /**
             * \brief Sets the end point of the line to \a pt.
             * \param pt The new end point of the line.
             */
            void setEnd(const Math::Vector2D& pt);

            /**
             * \brief Sets the end point of the line to <em>(x, y)</em>.
             * \param x The x-coordinate of the new end point.
             * \param y The y-coordinate of the new end point.
             */
            void setEnd(double x, double y);

            /**
             * \brief Returns the end point of the line.
             * \return The end point of the line.
             */
            const Math::Vector2D& getEnd() const;
            
            /**
             * \brief Sets the starting point of the line to <em>(beg_x, beg_y)</em> and the end point to <em>(end_x, end_y)</em>.
             * \param beg_x The x-coordinate of the new starting point.
             * \param beg_y The y-coordinate of the new starting point.
             * \param end_x The x-coordinate of the new end point.
             * \param end_y The y-coordinate of the new end point.
             */
            void setPoints(double beg_x, double beg_y, double end_x, double end_y);

            /**
             * \brief Sets the starting point of the line to \a beg and the end point to \a end.
             * \param beg The new starting point.
             * \param end The new end point.
             */
            void setPoints(const Math::Vector2D& beg, const Math::Vector2D& end);

            /**
             * \brief Swaps the starting and end point of the line.
             *
             * The old starting point becomes the new end point and the old end point becomes the new starting point.
             */
            void swapPoints();

            /**
             * \brief Calculates the normalized direction vector of the line and stores the result in \a dir.
             * \param dir Holds the calculated direction vector.
             */
            void getDirection(Math::Vector2D& dir) const;

            /**
             * \brief Calculates the normalized direction vector of the line.
             * \return The calculated direction vector.
             */        
            Math::Vector2D getDirection() const;

            /**
             * \brief Calculates the normalized direction vector rotated by <em>90</em> degrees in counter-clockwise direction
             *        and stores the result in \a dir.
             * \param dir Holds the calculated rotated direction vector.
             */
            void getCCWPerpDirection(Math::Vector2D& dir) const;
            
            /**
             * \brief Calculates the normalized direction vector rotated by <em>90</em> degrees in counter-clockwise direction.
             * \return The calculated rotated direction vector.
             */
            Math::Vector2D getCCWPerpDirection() const;

            /**
             * \brief Calculates the normalized direction vector rotated by <em>90</em> degrees in clockwise direction
             *        and stores the result in \a dir.
             * \param dir Holds the calculated rotated direction vector.
             */
            void getCWPerpDirection(Math::Vector2D& dir) const;

            /**
             * \brief Calculates the normalized direction vector rotated by <em>90</em> degrees in clockwise direction.
             * \return The calculated rotated direction vector.
             */
            Math::Vector2D getCWPerpDirection() const;

            /**
             * \brief Calculates the center point of the line and stores the result in \a ctr.
             * \param ctr Holds the calculated center point of the line.
             */
            void getCenter(Math::Vector2D& ctr) const;
            
            /**
             * \brief Calculates the center point of the line.
             * \return The calculated center point of the line.
             */
            Math::Vector2D getCenter() const;

            /**
             * \brief Returns the length of the line segment.
             * \return The length of the line segment.
             */
            double getLength() const;

            /**
             * \brief Translates the starting and end point of the line by \a vec.
             * \param vec The translation vector.
             */
            void translate(const Math::Vector2D& vec);

            /**
             * \brief Translates the starting point of the line by \a vec.
             * \param vec The translation vector.
             */
            void translateBegin(const Math::Vector2D& vec);

            /**
             * \brief Translates the end of the line point by \a vec.
             * \param vec The translation vector.
             */
            void translateEnd(const Math::Vector2D& vec);

            /**
             * \brief Tests if the point \a pt is contained within the boundary of the line segment.
             *
             * The point \a pt is considered to be contained within the boundary of the line segment if the dot product
             * of the line's direction vector and the vector from the starting point to \a pt is positive
             * or zero, and furthermore the dot product of the direction vector and the vector from the end
             * point to \a pt is negative or zero.
             *
             * \param pt The point to test.
             * \return \c true if \a pt is contained within the boundary of the line segment, and \c false otherwise.
             */
            bool containsPoint(const Math::Vector2D& pt) const;

            /**
             * \brief Calculates the point of intersection with the specified line and stores the
             *        result in \a pt
             * \param line The other line for which the point of intersection will be calculated.
             * \param pt Holds the calculated intersection point.
             * \return \c false if the two lines are parallel, and \c true otherwise.
             */
            bool getIntersectionPoint(const Line2D& line, Math::Vector2D& pt) const;

            /**
             * \brief Sets the starting point of the line to the point of intersection with the specified line
             *        segment.
             * 
             * If the lines are parallel or the point of intersection is not within the boundaries of \e both line
             * segments, the starting point of the line is left unaltered and \c false is returned.
             *
             * \param line The other line segment to clip against.
             * \return \c false if the lines are parallel or the intersection point is not within the boundaries of 
             *         both line segments, and \c true otherwise.
             */
            bool clipBeginAgainstLineSeg(const Line2D& line);

            /**
             * \brief Sets the end point of the line to the point of intersection with the specified line
             *        segment.
             * 
             * If the lines are parallel or the point of intersection is not within the boundaries of \e both line
             * segments, the end point of the line is left unaltered and \c false is returned.
             *
             * \param line The other line segment to clip against.
             * \return \c false if the lines are parallel or the intersection point is not within the boundaries of 
             *         both line segments, and \c true otherwise.
             */
            bool clipEndAgainstLineSeg(const Line2D& line);
            
            /**
             * \brief Sets the starting point of the line to the point of intersection with the specified line
             *        segment.
             * 
             * If the lines are parallel or the point of intersection is not within the boundary of the line
             * segment \a line, the starting point of the line is left unaltered and \c false is returned.
             *
             * \param line The other line segment.
             * \return \c false if the lines are parallel or the intersection point is not within the boundary of 
             *         \a line, and \c true otherwise.
             */
            bool setBeginToLineSegIntersection(const Line2D& line);

            /**
             * \brief Sets the end point of the line to the point of intersection with the specified line
             *        segment.
             * 
             * If the lines are parallel or the point of intersection is not within the boundary of the line
             * segment \a line, the end point of the line is left unaltered and \c false is returned.
             *
             * \param line The other line segment.
             * \return \c false if the lines are parallel or the intersection point is not within the boundary of 
             *         \a line, and \c true otherwise.
             */
            bool setEndToLineSegIntersection(const Line2D& line);

            /**
             * \brief Sets the starting point of the line to the point of intersection between this line segment and the
             *        edges of the rectangle \a rect.
             *
             * If the line segment intersects with more than one edge of \a rect, the starting point is set to the intersection
             * point which results in the shortest clipped line segment. If the line segment does not intersect with an edge of
             * \a rect, the starting point is left unaltered and \c false is returned.
             *
             * \param rect The rectangle to clip againts.
             * \return \c true if the line segment was clipped against an edge of \a rect, and \c false otherwise.
             */
            bool clipBeginAgainstRectangle(const Rectangle2D& rect);

            /**
             * \brief Sets the end point of the line to the point of intersection between this line segment and the
             *        edges of the rectangle \a rect.
             *
             * If the line segment intersects with more than one edge of \a rect, the end point is set to the intersection
             * point which results in the shortest clipped line segment. If the line segment does not intersect with an edge of
             * \a rect, the end point is left unaltered and \c false is returned.
             *
             * \param rect The rectangle to clip againts.
             * \return \c true if the line segment was clipped against an edge of \a rect, and \c false otherwise.
             */    
            bool clipEndAgainstRectangle(const Rectangle2D& rect);

            /** 
             * \brief Returns the perpendicular distance of the point \a pt to this line.
             *
             * The measured distance is the distance between the point \a pt and the closest point on the 
             * infinitely extended line. If \a pt intersects the line, the method returns \e 0.0.
             *
             * \param pt The point for which to calculate the shortest distance.
             * \return The shortest distance between \a pt and the infinitely extended line.
             */
            double getDistance(const Math::Vector2D& pt) const;
        
            /**
             * \brief Equality comparison operator.
             * \param line The other \c %Line2D object to be compared with.
             * \return \c true if the starting and end points compare equal, and \c false otherwise.
             */
            bool operator==(const Line2D& line) const;

            /**
             * \brief Inequality comparison operator.
             *
             * The result is equivalent to <tt>!(*this == line)</tt>.
             *
             * \param line The other \c %Line2D object to be compared with.
             * \return \c true if either the starting or end points compare non-equal, and \c false otherwise.
             */            
            bool operator!=(const Line2D& line) const;

        private:
            Math::Vector2D begin;
            Math::Vector2D end;
        };
    }
}

#endif // CDPL_VIS_LINE2D_HPP
