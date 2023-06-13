/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * TextLabelPrimitive2D.hpp 
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
 * \brief Definition of the class CDPL::Vis::TextLabelPrimitive2D.
 */

#ifndef CDPL_VIS_TEXTLABELPRIMITIVE2D_HPP
#define CDPL_VIS_TEXTLABELPRIMITIVE2D_HPP

#include <string>
#include <memory>

#include "CDPL/Vis/GraphicsPrimitive2D.hpp"
#include "CDPL/Vis/Pen.hpp"
#include "CDPL/Vis/Font.hpp"
#include "CDPL/Math/Vector.hpp"


namespace CDPL 
{

	namespace Vis
	{

		/**
		 * \brief A graphics primitive representing a text label.
		 */
		class CDPL_VIS_API TextLabelPrimitive2D : public GraphicsPrimitive2D
		{

		public:
			/**
			 * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %TextLabelPrimitive2D instances.
			 */
			typedef std::shared_ptr<TextLabelPrimitive2D> SharedPointer;

			/**
			 * \brief Construct an empty text label primitive at position <em>(0, 0)</em>.
			 */
			TextLabelPrimitive2D();

			void render(Renderer2D& renderer) const;

			/**
			 * \brief Sets the text of the label.
			 * \param txt The text of the label.
			 */
			void setText(const std::string& txt);

			/**
			 * \brief Returns the text of the label.
			 * \return The text of the label.
			 */
			const std::string& getText() const;

			/**
			 * \brief Sets the position of the text label.
			 * \param pos The baseline position of the text label.
			 */
			void setPosition(const Math::Vector2D& pos);

			/**
			 * \brief Sets the position of the text label to <em>(x, y)</em>.
			 * \param x The x-position of the text label.
			 * \param y The y-position of the baseline.
			 */
			void setPosition(double x, double y);

			/**
			 * \brief Returns the position of the text label.
			 * \return The position of the text label.
			 */
			const Math::Vector2D& getPosition() const;
		
			/**
			 * \brief Sets the pen defining the color of the text label.
			 * \param pen The pen defining the color of the text label.
			 */
			void setPen(const Pen& pen);

			/**
			 * \brief Returns the pen defining the color of the text label.
			 * \return The pen defining the color of the text label.
			 */
			const Pen& getPen() const;

			/**
			 * \brief Sets the font of the text label.
			 * \param font The font of the text label.
			 */
			void setFont(const Font& font);

			/**
			 * \brief Returns the font of the text label.
			 * \return The font of the text label.
			 */
			const Font& getFont() const;

			GraphicsPrimitive2D::SharedPointer clone() const;

			void getBounds(Rectangle2D& bounds, FontMetrics* font_metrics) const;

		private:
			Pen            pen;
			Font           font;
			Math::Vector2D position;
			std::string    text;
		};
	}
}

#endif // CDPL_VIS_TEXTLABELPRIMITIVE2D_HPP
