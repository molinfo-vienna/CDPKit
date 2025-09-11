/* 
 * Path2D.hpp 
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
 * \brief Definition of class CDPL::Vis::Path2D.
 */

#ifndef CDPL_VIS_PATH2D_HPP
#define CDPL_VIS_PATH2D_HPP

#include <vector>

#include "CDPL/Vis/APIPrefix.hpp"
#include "CDPL/Math/Vector.hpp"


namespace CDPL
{

    namespace Vis
    {

        class Path2DConverter;
        class Rectangle2D;
        
        /**
         * \brief Provides a container for painting operations, enabling arbitrary graphical shapes to be constructed and reused.
         *
         * A path consits of a number of graphical building blocks, such as rectangles, ellipses, lines and arcs. Building blocks
         * can be joined to form closed subpaths, for example a rounded rectangle, or they can exist independently as unclosed 
         * subpaths, such as lines and curves. A closed path has coinciding start and end points. 
         *
         * \c %Path2D objects can be used for filling, outlining, and clipping. The main advantage over a sequence of basic drawing
         * operations is that complex shapes need to be created only once and can be stored for repeated later uses.
         *
         * A \c %Path2D object can be constructed as an empty path, or as a copy of another \c %Path2D instance. Once created, lines and curves
         * can be added to the path using the lineTo(), arcTo() and arc() functions. The lines and curves stretch from the current position
         * to the position passed as argument.
         * The current position is always the end point of the last drawing operation. Use the moveTo()
         * method to move the current position without adding a component. The moveTo() method implicitly starts a new subpath, and closes the
         * previous one. Another way of starting a new subpath is to call the closePath() method which closes the current path by adding a line
         * from the current position back to the path's start position.
         * The \c %Path2D class also provides convenience methods for the generation of common shapes: addEllipse() and addRectangle(). 
         * The generation of these shapes is implemented by executing a sequence of appropriate moveTo(), lineTo() and arcTo() calls.
         * The axis-aligned bounding box of a path constructed in this way can be calculated by the method getBounds().
         *
         * Whether or not a \c %Path2D object contains any elements can be queried by the method isEmpty(). Whether the path also features
         * visual elements (lines and arcs) can be queried by the method hasDrawingElements(). The method clear() deletes all 
         * elements added so far and sets the default fill rule (see setFillRule() and getFillRule()).
         *
         * Elements added to a \c %Path2D object cannot inspected directly. For path analysis and rendering the method convert()
         * is available which calls element type specific methods on a provided instance of a class implementing the Vis::Path2DConverter interface.
         *
         * \since 1.1
         */
        class CDPL_VIS_API Path2D
        {

          public:
            /**
             * \brief Specifies which method to use for filling closed shapes described by the \c %Path2D object.
             */
            enum FillRule
            {

                /**
                 * \brief Specifies that the path has to be filled using the odd even fill rule. 
                 *
                 * With this rule, the question whether a point is inside the shape can be answered by the following method:
                 * Draw a horizontal line from the point to a location outside the shape, and count the number of 
                 * intersections. If the number of intersections is an odd number, the point is inside the shape.
                 */
                EVEN_ODD,

                /**
                 * \brief Specifies that the path has to be filled using the non-zero winding rule.
                 *
                 * With this rule, the question whether a point is inside the shape can be answered by the following method:
                 * Draw a horizontal line from the point to a location outside the shape. Determine whether the
                 * direction of the line at each intersection point is up or down. The winding number is determined
                 * by summing the direction of each intersection. If the number is non-zero, the point is inside the shape.
                 */
                WINDING
            };

            /**
             * \brief Constructs an empty \c %Path2D instance.
             */
            Path2D();

            /**
             * \brief Constructs a copy of the \c %Path2D instance \a path.
             * \param path The \c %Path2D instance to copy.
             */
            Path2D(const Path2D& path);

            /**
             * \brief Virtual destructor.
             */
            virtual ~Path2D();

            /**
             * \brief Tells whether the \c %Path2D instance does not contain any elements.
             * \return \c true is no elements have been added to the \c %Path2D instance so far, and \c false otherwise.
             */
            bool isEmpty() const;
            
            /**
             * \brief Tells whether the \c %Path2D instance contains any elements representing drawing operations (lines and arcs).
             * \return \c true if the \c %Path2D instance contains any visual elements, and \c false otherwise.
             */
            bool hasDrawingElements() const;

            /**
             * \brief Deletes all path elements added so far and sets the fill rule to its default.
             * \see setFillRule()
             */
            void clear();

            /**
             * \brief Sets the fill rule of the path to the specified value.
             * \param rule The new fill rule.
             * \note The default fill rule is Path2D::EVEN_ODD.
             */
            void setFillRule(FillRule rule);

            /**
             * \brief Returns the currently set fill rule.
             * \return The currently set fill rule.
             */
            FillRule getFillRule() const;

            /**
             * \brief Sets the current position to <em>(x, y)</em> and starts a new subpath, implicitly closing the previous path.
             * \param x Specifies the x-coordinate of the new position.
             * \param y Specifies the y-coordinate of the new position.
             */
            void moveTo(double x, double y);

            /**
             * \brief Sets the current position to \a pos and starts a new subpath, implicitly closing the previous path.
             * \param pos A 2D vector specifying the new position.
             */
            void moveTo(const Math::Vector2D& pos);

            /**
             * \brief Creates an elliptical arc centered at <em>(cx, cy)</em> with ellipse radii \a rx and \a ry beginning 
             *        at the angle \a start_ang and extending \a sweep degrees clockwise.
             *
             * Angles are specified in degrees. Counter-clockwise arcs can be specified using negative angles.
             * After the arc has been added, the current position is the end point of the arc. To draw a line back to the first point, use
             * the closePath() method.
             *
             * \param cx        The x-coordinate of the ellipse center.
             * \param cy        The y-coordinate of the ellipse center.
             * \param rx        The x-radius of the ellipse.
             * \param ry        The y-radius of the ellipse.
             * \param start_ang The start angle of the arg in degrees.
             * \param sweep     The length of the arg in degrees.
             * \note The method first performs a moveTo() call with the starting point of the arc as argument and thus avoids an implicit line being drawn 
             *       from the current position to the arc's starting position (see arcTo()).
             */
            void arc(double cx, double cy, double rx, double ry, double start_ang, double sweep);

            /**
             * \brief Creates an elliptical arc centered at \a ctr with ellipse radii \a rx and \a ry beginning 
             *        at the angle \a start_ang and extending \a sweep degrees clockwise.
             *
             * Angles are specified in degrees. Counter-clockwise arcs can be specified using negative angles.
             * After the arc has been added, the current position is the end point of the arc. To draw a line back to the first point, use
             * the closePath() method.
             *
             * \param ctr       A 2D vector specifying the ellipse center.
             * \param rx        The x-radius of the ellipse.
             * \param ry        The y-radius of the ellipse.
             * \param start_ang The start angle of the arg in degrees.
             * \param sweep     The length of the arg in degrees.
             * \note The method first performs a moveTo() call with the starting point of the arc as argument and thus avoids an implicit line being drawn 
             *       from the current position to the arc's starting position (see arcTo()).
             */
            void arc(const Math::Vector2D& ctr, double rx, double ry, double start_ang, double sweep);

            /**
             * \brief Creates an elliptical arc centered at <em>(cx, cy)</em> with ellipse radii \a rx and \a ry beginning 
             *        at the angle \a start_ang and extending \a sweep degrees clockwise.
             *
             * Angles are specified in degrees. Counter-clockwise arcs can be specified using negative angles.
             * After the arc has been added, the current position is the end point of the arc. To draw a line back to the first point, use
             * the closePath() method.    
             *
             * \param cx        The x-coordinate of the ellipse center.
             * \param cy        The y-coordinate of the ellipse center.
             * \param rx        The x-radius of the ellipse.
             * \param ry        The y-radius of the ellipse.
             * \param start_ang The start angle of the arg in degrees.
             * \param sweep     The length of the arg in degrees.
             * \note The method implicitly connects the starting point of the arc to the current position if they are not already connected.
             *       The rendering result is undefined if no subpath starting point has been specified (see moveTo())!
             */
            void arcTo(double cx, double cy, double rx, double ry, double start_ang, double sweep);

            /**
             * \brief Creates an elliptical arc centered at \a ctr with ellipse radii \a rx and \a ry beginning 
             *        at the angle \a start_ang and extending \a sweep degrees clockwise.
             *
             * Angles are specified in degrees. Counter-clockwise arcs can be specified using negative angles.
             * After the arc has been added, the current position is the end point of the arc. To draw a line back to the first point, use
             * the closePath() method.
             *
             * \param ctr       A 2D vector specifying the ellipse center.
             * \param rx        The x-radius of the ellipse.
             * \param ry        The y-radius of the ellipse.
             * \param start_ang The start angle of the arg in degrees.
             * \param sweep     The length of the arg in degrees.
             * \note The method implicitly connects the starting point of the arc to the current position if they are not already connected.
             *       The rendering result is undefined if no subpath starting point has been specified (see moveTo())!
             */
            void arcTo(const Math::Vector2D& ctr, double rx, double ry, double start_ang, double sweep);

            /**
             * \brief Adds a straight line from the current position to the point <em>(x, y)</em>. 
             *
             * After the line is drawn, the current position is updated to be at the end point of the line.
             *
             * \param x Specifies the x-coordinate of the line's end point.
             * \param y Specifies the y-coordinate of the line's end point. 
             * \note The rendering result is undefined if no subpath starting point has been specified (see moveTo())!
             */
            void lineTo(double x, double y);
            
            /**
             * \brief Adds a straight line from the current position to the point <em>(x, y)</em>. 
             *
             * After the line is drawn, the current position is updated to be at the end point of the line.
             *
             * \param pos A 2D vector specifying the line end point.
             * \note The rendering result is undefined if no subpath starting point has been specified (see moveTo())!
             */
            void lineTo(const Math::Vector2D& pos);

            /**
             * \brief Closes the current subpath by drawing a line to the beginning of the subpath, automatically starting a new path. 
             *
             * A call to this methods has no effect if the current subpath does not contain any elements.
             *
             * \note After closing the subpath the current point is undefined!
             */
            void closePath();

            /**
             * \brief Creates an ellipse positioned at <em>(x, y)</em> with the specified width and height, and adds it to this
             *        path as a closed subpath.
             * \param x      The x-coordinate of the ellipse center.
             * \param y      The y-coordinate of the ellipse center.
             * \param width  The width of the ellipse.
             * \param height The height of the ellipse.
             */
            void addEllipse(double x, double y, double width, double height);

            /**
             * \brief Creates an ellipse positioned at \a pos with the specified width and height, and adds it to this
             *        path as a closed subpath.
             * \param pos    A 2D vector specifying the ellipse center.
             * \param width  The width of the ellipse.
             * \param height The height of the ellipse.
             */
            void addEllipse(const Math::Vector2D& pos, double width, double height);

            /**
             * \brief Creates a rectangle positioned at <em>(x, y)</em> with the specified width and height, and adds it to this
             *        path as a closed subpath.
             * \param x      The x-coordinate of the top-left corner.
             * \param y      The y-coordinate of the top-left corner.
             * \param width  The width of the rectangle.
             * \param height The height of the rectangle.
             */
            void addRectangle(double x, double y, double width, double height);

            /**
             * \brief Creates a rectangle positioned at \a pos with the specified width and height, and adds it to this
             *        path as a closed subpath.
             * \param pos    A 2D vector specifying the top-left corner.
             * \param width  The width of the rectangle.
             * \param height The height of the rectangle.
             */
            void addRectangle(const Math::Vector2D& pos, double width, double height);

            /**
             * \brief Calculates the axis-aligned bounding box of the path.
             * \param bounds The Vis::Rectangle2D instance storing the calculated bounding box.
             */
            void getBounds(Rectangle2D& bounds) const;

            /**
             * \brief Iterates over the stored path elements and calls the corresponding method of \a conv for each visited element. 
             * \param conv An instance of a class implementing the Vis::Path2DConverter interface.
             */
            void convert(Path2DConverter& conv) const;

            /**
             * \brief Equality comparison operator.
             * \param path The \c %Path2D instance to compare with.
             * \return \c true if this path is equal to \a path, and \c false otherwise.
             */
            bool operator==(const Path2D& path) const;

            /**
             * \brief Non-equality comparison operator.
             * \param path The \c %Path2D instance to compare with.
             * \return \c true if this path is not equal to \a path, and \c false otherwise.
             */
            bool operator!=(const Path2D& path) const;

            /**
             * \brief Appends the elements stored in the \c %Path2D instance \a path to this path.
             * \param path The \c %Path2D instance providing the elements to append.
             * \return A reference to itself.
             */
            Path2D& operator+=(const Path2D& path);

            /**
             * \brief Assignment operator.
             * \param path The \c %Path2D instance to copy.
             * \return A reference to itself.
             */
            Path2D& operator=(const Path2D& path);
            
          private:
            struct Element;

            typedef std::vector<Element> ElementList;

            FillRule    fillRule;
            ElementList elements;
        };
    } // namespace Vis
} // namespace CDPL

#endif // CDPL_VIS_PATH2D_HPP
