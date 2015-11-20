/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FontMetrics.hpp 
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
 * \brief Definition of the class CDPL::Vis::FontMetrics.
 */

#ifndef CDPL_VIS_FONTMETRICS_HPP
#define CDPL_VIS_FONTMETRICS_HPP

#include <string>

#include "CDPL/Vis/APIPrefix.hpp"


namespace CDPL 
{

	namespace Vis
	{

		/**
		 * \addtogroup CDPL_VIS_RENDERING_INTERFACES
		 * @{
		 */

		class Font;
		class Rectangle2D;

		/**
		 * \brief An interface class with methods that provide information about the metrics of a font.
		 *
		 * Implementations of the \c %FontMetrics interface provide height and width information for a
		 * given font and specific character glyphs in that font. Once a font has been specified with setFont(),
		 * there are several methods that operate on the font.
		 *
		 * The methods
		 *   - getAscent()
		 *   - getDescent()
		 *   - getHeight()
		 *   - and getLeading()
		 *
		 * return basic size properties of the font. The ascent is the maximum amount by which characters ascend
		 * \e above the baseline, and the descent is the maximum amount by which characters descend \e below the
		 * baseline. The leading, or interline spacing, is the logical amount of space to be reserved between the
		 * descent of one line of text and the ascent of the next line. The height metric is the sum of the ascent
		 * and descent plus some implementation dependent extra space.
		 *
		 * For single characters or strings, the advance width can be obtained by getWidth(). The advance width
		 * specifies the distance to a position on the baseline where the next character(s) should be drawn.
		 * A bounding rectangle large enough to contain the rendered glyph of a character, or a set of glyphs for
		 * a string, can be retrieved by getBounds().
		 */
		class CDPL_VIS_API FontMetrics
		{

		public:
			/**Ren
			 * \brief Virtual destructor.
			 */
			virtual ~FontMetrics() {}

			/**
			 * \brief Specifies the font for which to obtain the metrics.
			 * \param font Specifies the font for which to retrieve the metrics.
			 */
			virtual void setFont(const Font& font) = 0;

			/**
			 * \brief Returns the ascent of the font.
			 *
			 * The ascent is the maximum distance from the baseline to the highest position characters extend to.
			 * Some font designers break this rule, e.g. when they put more than one accent on top of a character,
			 * or to accommodate an unusual character in an exotic language, so it is possible (though rare) that
			 * this value will be too small.
			 *
			 * \return The ascent of the font.
			 * \see getDescent()
			 */
			virtual double getAscent() const = 0; 

			/**
			 * \brief Returns the descent of the font.
			 *
			 * The descent is the distance from the baseline to the lowest position characters extend to. Some
			 * font designers break this rule, e.g. to accommodate an unusual character in an exotic language, 
			 * so it is possible (though rare) that this value will be too small.
			 *
			 * \return The descent of the font.
			 * \see getAscent()
			 */
			virtual double getDescent() const = 0; 

			/**
			 * \brief Returns the height of the font.
			 *
			 * The returned height is the sum of the ascent and descent plus some possible implementation dependent
			 * extra space.
			 *
			 * \return The height of the font.
			 */
			virtual double getHeight() const = 0; 

			/**
			 * \brief Returns the leading of the font.
			 *
			 * The leading, or interline spacing, is the logical amount of space to be reserved between the descent
			 * of one line of text and the ascent of the next line. 
			 *
			 * \return The leading of the font.
			 */
			virtual double getLeading() const = 0; 

			/**
			 * \brief Returns the total advance width for the characters in the string \a str.
			 *
		     * The advance is the distance from the leftmost point to the rightmost point on the string's baseline.
			 * Note that the advance of a string is not necessarily the sum of the advances of its characters.
			 *
			 * \param str The string to be measured.
			 * \return The total advance width for the characters in \a str.
			 */
			virtual double getWidth(const std::string& str) const = 0; 

			/**
			 * \brief Returns the advance width for the character \a ch.
			 *
			 * The advance width is the distance from the leftmost point to the rightmost point on the character's baseline.
			 *
			 * \param ch The character to be measured.
			 * \return The advance width for \a ch.
			 */
			virtual double getWidth(char ch) const = 0; 

			/**
			 * \brief Returns the total bounding rectangle for the characters in the string \a str.
			 *
			 * The bounding rectangle always covers at least the set of pixels the text would cover if drawn at <em>(0, 0)</em>.
			 * Note that the bounding rectangle may extend to the left of <em>(0, 0)</em>, e.g. for italicized fonts, and that
			 * the width of the returned rectangle might be different than what the getWidth() method returns. Furthermore,
			 * the bounding rectangle usually extends both above and below the baseline.
			 *
			 * \param str The string for which to calculate the bounding rectangle.
			 * \param bounds A rectangle holding the calculated bounds.
			 * \note Newline characters are processed as normal characters, not as linebreaks.
			 */
			virtual void getBounds(const std::string& str, Rectangle2D& bounds) const = 0; 

			/**
			 * \brief Returns the bounding rectangle of the character \a ch relative to the left-most point on the baseline.
			 *
			 * Note that the bounding rectangle may extend to the left of <em>(0, 0)</em>, e.g. for italicized fonts, and that
			 * the text output may cover all pixels in the bounding rectangle. Furthermore, the bounding rectangle usually
			 * extends both above and below the baseline.
			 *
			 * \param ch The character for which to calculate the bounding rectangle.
			 * \param bounds A rectangle holding the calculated bounds.
			 */
			virtual void getBounds(char ch, Rectangle2D& bounds) const = 0; 
		};

		/**
		 * @}
		 */
	}
}

#endif // CDPL_VIS_FONTMETRICS_HPP
