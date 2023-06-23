/* 
 * Pen.hpp 
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
 * \brief Definition of the class CDPL::Vis::Pen.
 */

#ifndef CDPL_VIS_PEN_HPP
#define CDPL_VIS_PEN_HPP

#include "CDPL/Vis/APIPrefix.hpp"
#include "CDPL/Vis/Color.hpp"


namespace CDPL 
{

	namespace Vis
	{
	
		/**
		 * \brief Specifies how to draw lines and outlines of shapes.
		 *
		 * A pen has a line style, width, color, cap style and join style attribute. The line style specifies how a line
		 * will look like (solid, dashed, ...). The default line style is Pen::SOLID_LINE. Setting the line style to 
		 * Pen::NO_LINE tells the renderer not to draw lines or outlines. The pen color defines the color of lines and text.
		 * The default line color is Color::BLACK. The cap style specifies how the end points of lines are drawn and the join
		 * style defines how the joins between two or more connected have to be drawn. The default cap style is Pen::ROUND_CAP
		 * and the default join style is Pen::ROUND_JOIN.
		 */
		class CDPL_VIS_API Pen
		{

		  public:
			/**
			 *\brief Defines constants for supported line styles.
			 */
			enum LineStyle
			{

  				/**
				 * \brief Tells the renderer not to draw lines or shape outlines.
				 */	
				NO_LINE,

				/**
				 * \brief Specifies a solid line without gaps.
				 */	
				SOLID_LINE,

				/**
				 * \brief Specifies a dashed line.
				 */	
				DASH_LINE, 

				/**
				 * \brief Specifies a dotted line.
				 */	
				DOT_LINE,

				/**
				 * \brief Specifies a line with alternating dots and dashes.
				 */	
				DASH_DOT_LINE,

				/**
				 * \brief Specifies a line with dashes that are followed by two dots.
				 */	
				DASH_DOT_DOT_LINE
			};

			/**
			 *\brief Defines constants for supported line cap styles.
			 */
			enum CapStyle
			{

				/**
				 * \brief Specifies a squared line end that does not cover the end point of the line.
				 */
				FLAT_CAP,

				/**
				 * \brief Specifies a squared line end that covers the end point and extends beyond it with half the line width.
				 */
				SQUARE_CAP,

				/**
				 * \brief Specifies a rounded line end. 
				 */	
				ROUND_CAP
			};

			/**
			 *\brief Defines constants for supported line join styles.
			 */
			enum JoinStyle
			{

				/**
				 * \brief Specifies a join style where the outer edges of the lines are extended to meet at an angle, and this area is filled.
				 */	
				MITER_JOIN,

				/**
				 * \brief Specifies a join style where the triangular notch between the two lines is filled.
				 */	
				BEVEL_JOIN,

				/**
				 * \brief Specifies a join style where the circular arc between the two lines is filled.
				 */	
				ROUND_JOIN
			};

			/**
			 * \brief Constructs a pen with line style Pen::SOLID_LINE, line width \e 1.0, cap style Pen::ROUND_CAP, 
			 *        join style Pen::ROUND_JOIN and color Color::BLACK.
			 */
			Pen();
		
			/**
			 * \brief Constructs a pen with the specified line style, line width \e 1.0, cap style Pen::ROUND_CAP, 
			 *        join style Pen::ROUND_JOIN and color Color::BLACK.
			 * \param line_style The line style.
			 */
			Pen(LineStyle line_style); 
		
			/**
			 * \brief Constructs a pen with the specified color, line width, line style, cap style and join style.
			 *
			 * If \a width is negative, the line width is set to zero.
			 *
			 * \param color The pen color.
			 * \param width The line width.
			 * \param line_style The line style.
			 * \param cap_style The line cap style.
			 * \param join_style The line join style.
			 */
			Pen(const Color& color, double width = 1.0, LineStyle line_style = SOLID_LINE, 
				CapStyle cap_style = ROUND_CAP, JoinStyle join_style = ROUND_JOIN); 

			/**
			 * \brief Sets the line style to \a line_style.
			 * \param line_style The line style.
			 */
			void setLineStyle(LineStyle line_style); 

			/**
			 * \brief Returns the line style.
			 * \return The line style.
			 */
			LineStyle getLineStyle() const; 

			/**
			 * \brief Sets the line width to the specified value.
			 *
			 * If \a width is negative, the line width is set to zero.
			 *
			 * \param width The line width.
			 */
			void setWidth(double width); 

			/**
			 * \brief Returns the line width.
			 * \return The line width.
			 */
			double getWidth() const; 
	
			/**
			 * \brief Sets the pen's color to the specified value.
			 * \param color The color of the pen.
			 */
			void setColor(const Color& color); 

			/**
			 * \brief Returns the color of the pen.
			 * \return The color of the pen.
			 */
			const Color& getColor() const; 

			/**
			 * \brief Sets the line cap style to \a cap_style.
			 * \param cap_style The line cap style.
			 */
			void setCapStyle(CapStyle cap_style); 

			/**
			 * \brief Returns the line cap style.
			 * \return The line cap style.
			 */
			CapStyle getCapStyle() const; 
	
			/**
			 * \brief Sets the line join style to \a join_style.
			 * \param join_style The line join style.
			 */
			void setJoinStyle(JoinStyle join_style); 

			/**
			 * \brief Returns the line join style.
			 * \return The line join style.
			 */	
			JoinStyle getJoinStyle() const; 
		
			/**
			 * \brief Equality comparison operator.
			 * \param pen The other \c %Pen object to be compared with.
			 * \return \c true if all pen attributes compare equal, and \c false otherwise.
			 */
			bool operator==(const Pen& pen) const;
	
			/**
			 * \brief Inequality comparison operator.
			 *
			 * The result is equivalent to <tt>!(*this == pen)</tt>.
			 *
			 * \param pen The other \c %Pen object to be compared with.
			 * \return \c true if the pen attributes compare non-equal, and \c false otherwise.
			 */			
			bool operator!=(const Pen& pen) const;

		  private:
			Color     color;
			LineStyle lineStyle;
			CapStyle  capStyle;
			JoinStyle joinStyle;
			double    width;
		};
	}
}

#endif // CDPL_VIS_PEN_HPP
