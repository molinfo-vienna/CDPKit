/* 
 * TextBlockPrimitive2D.hpp 
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
 * \brief Definition of the class CDPL::Vis::TextBlockPrimitive2D.
 */

#ifndef CDPL_VIS_TEXTBLOCKPRIMITIVE2D_HPP
#define CDPL_VIS_TEXTBLOCKPRIMITIVE2D_HPP

#include <string>
#include <vector>
#include <cstddef>
#include <memory>

#include "CDPL/Vis/GraphicsPrimitive2D.hpp"
#include "CDPL/Vis/Pen.hpp"
#include "CDPL/Vis/Font.hpp"
#include "CDPL/Math/Vector.hpp"


namespace rapidxml
{

    template <typename C> class xml_node;
}


namespace CDPL
{

    namespace Vis
    {

        /**
         * \brief A graphics primitive representing a block of styled text that comprises multiple lines.
         */
        class CDPL_VIS_API TextBlockPrimitive2D : public GraphicsPrimitive2D
        {

          public:
            /**
             * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %TextBlockPrimitive2D instances.
             */
            typedef std::shared_ptr<TextBlockPrimitive2D> SharedPointer;

            /**
             * \brief Construct an empty text block primitive at position <em>(0, 0)</em>.
             */
            TextBlockPrimitive2D();

            void render(Renderer2D& renderer) const;

            /**
             * \brief Specifies the block's text content.
             * \param text The text content of the block.
             */
            void setText(const std::string& text);

            /**
             * \brief Clears the block's text content.
             */
            void clearText();

            /**
             * \brief Returns the block's text content.
             * \return The text content of the block.
             */
            const std::string& getText() const;

            /**
             * \brief Tells whether the text block has any renderable text.
             * \return \c true if there is renderable text and \c false otherwise.
             */
            bool hasText() const;

            /**
             * \brief Sets the position of the text block in 2D space.
             *
             * The position specifies the upper-left corner of the text block's bounding box.
             *
             * \param pos Theposition of the text block.
             */
            void setPosition(const Math::Vector2D& pos);

            /**
             * \brief Sets the position of the text block to <em>(x, y)</em>.
             *
             * The position specifies the upper-left corner of the text block's bounding box.
             *
             * \param x The x-position of the text block.
             * \param y The y-position of the baseline.
             */
            void setPosition(double x, double y);

            /**
             * \brief Returns the position of the text block.
             * \return The position of the text block.
             * \see setPosition()
             */
            const Math::Vector2D& getPosition() const;

            /**
             * \brief Sets the pen defining the default text color.
             * \param pen The pen defining the default text color.
             */
            void setPen(const Pen& pen);

            /**
             * \brief Returns the pen defining the default text color.
             * \return The pen defining the default text color.
             */
            const Pen& getPen() const;

            /**
             * \brief Sets the font used for text rendering.
             * \param font The font used for text rendering.
             */
            void setFont(const Font& font);

            /**
             * \brief Returns the font used for text rendering.
             * \return The font used for text rendering.
             */
            const Font& getFont() const;

            /**
             * \brief Specifies the way lines should be horizontally aligned.
             *
             * Possible values are defined in namespace Vis::Alignment.
             * 
             * \param alignment The horizontal text alignment specification.
             */
            void setAlignment(unsigned int alignment);

            /**
             * \brief Returns the active horizontal text alignment specification.
             *
             * Possible values are defined in namespace Vis::Alignment.
             * 
             * \return The current horizontal text alignment specification.
             */
            unsigned int getAlignment() const;
            
            /**
             * \brief Sets the line spacing value.
             *
             * The final base line spacing is the product of the specified line spacing and the font height
             * returned by the method FontMetrics::getHeight() for the set font.
             *
             * \param spacing The desired line spacing.
             */
            void setLineSpacing(double spacing);

            /**
             * \brief Returns the active line spacing value.
             * \return The line spacing value.
             */
            double getLineSpacing() const;

            void layout(FontMetrics& font_metrics);

            GraphicsPrimitive2D::SharedPointer clone() const;

            void getBounds(Rectangle2D& bounds, FontMetrics* font_metrics) const;

          private:
            struct Style
            {

                bool bold{false};
                bool italic{false};
                bool underlined{false};
                bool overlined{false};
                bool strikedOut{false};
                bool subscripted{false};
                bool superscripted{false};
            };

            struct TextFragment
            {

                TextFragment(std::string& text, const Style& style, const Color& color,
                             bool def_color, std::size_t line):
                    style(style), color(color), defColor(def_color), line(line)
                {
                    this->text.swap(text);
                }

                std::string  text;
                Style        style;
                Color        color;
                bool         defColor;
                std::size_t  line;
                double       xPos;
                double       yPos;
            };

            typedef rapidxml::xml_node<char>  XMLNode;
            typedef std::vector<Color>        ColorStack;
            typedef std::vector<Style>        StyleStack;
            typedef std::vector<TextFragment> TextFragmentList;

            void processText(const std::string& text);
            void processNode(XMLNode* node);
            void getColor(XMLNode* node);
            void applyStyle(Font& font, const Style& style) const;

            Pen              pen;
            Font             font;
            Math::Vector2D   position;
            std::string      text;
            unsigned int     alignment;
            double           lineSpacing;
            ColorStack       colorStack;
            StyleStack       styleStack;
            Color            currColor;
            Style            currStyle;
            std::size_t      currLine;
            TextFragmentList textFragments;
        };
    } // namespace Vis
} // namespace CDPL

#endif // CDPL_VIS_TEXTBLOCKPRIMITIVE2D_HPP
