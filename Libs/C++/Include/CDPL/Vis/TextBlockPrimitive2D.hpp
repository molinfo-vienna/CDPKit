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
 * \brief Definition of class CDPL::Vis::TextBlockPrimitive2D.
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
         * \brief A graphics primitive representing a block of styled text.
         *
         * Class \c %TextBlockPrimitive2D is smiliar to Vis::TextLabelPrimitive2D but way more versatile.
         * \c %TextBlockPrimitive2D can store/render text that spans multiple lines with configurable line
         * spacing (see setLineSpacing()) and alignment (see setAlignment()), and supports changing text color and various
         * attributes like font weight and slant for individual text portions. Furthermore, text fragments can be rendered sub/super-scripted,
         * under- and overlined as well as striked out.
         * This is achieved by using an XML-based syntax where a portion of text to be rendered in a particular style is
         * enclosed in specific start and end tags.
         * More information on the syntax, the supported styling tags and their meaning can be found in the documentation of the method setText().
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
             *
             * Color, font attributes and style of individual text fragments can be controlled by
             * enclosing the concerned piece of text in specific XML tags. The following tags are supported:
             *
             * <table width="95%" bgcolor="#FAFAFA" border="1" align="center" rules="all" cellpadding="3">
             *  <tr bgcolor="#DDDDDD" align="center" valign="middle">
             *   <th>Tag</th> <th>Effect/Description</th>
             *  </tr>
             *  <tr>
             *   <td>\<br/\></td>
             *   <td>Line break</td>
             *  </tr>
             *  <tr>
             *   <td>\<b\></td>
             *   <td>Boldfaced text</td>
             *  </tr>
             *  <tr>
             *   <td>\<i\></td>
             *   <td>Italicized text</td>
             *  </tr>
             *  <tr>
             *   <td>\<o\></td>
             *   <td>Overlined text</td>
             *  </tr>
             *  <tr>
             *   <td>\<u\></td>
             *   <td>Underlined text</td>
             *  </tr>
             *  <tr>
             *   <td>\<s\></td>
             *   <td>Striked-out text</td>
             *  </tr>
             *  <tr>
             *   <td>\<sub\></td>
             *   <td>Subscripted text</td>
             *  </tr>
             *  <tr>
             *   <td>\<sup\></td>
             *   <td>Superscripted text</td>
             *  </tr>
             *  <tr>
             *   <td>\<color\></td>
             *   <td>Text color; supports the attributes \e r, \e g, \e b and \e a with a value in the range [0.0, 1.0]; default component
             *       values are \e r=0, \e b=0, \e g=0 and \e a=1</td>
             *  </tr>
             * </table>
             *
             * Newline characters <tt>\\n</tt> are regarded and interpreted as such. Tab characters <tt>\\t</tt> are replaced by a single whitespace character.
             * Any other special characters are deleted.
             * The supported tags listed above are all optional. Plain ASCII text will thus be rendered using the set font (see setFont()) and color (see setPen()).
             *
             * \param text The text content of the block.
             * \throw Base::ValueError if XML parsing of the specified text failed.
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
             * \brief Tells whether the text block has any visible text (includes whitespace).
             * \return \c true if there is any visible text and \c false otherwise.
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
             * \note Calling this method invalidates the current layout (see layout()).
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
             * Possible horizontal alignment values are defined in namespace Vis::Alignment.
             * 
             * \param alignment The horizontal text alignment specification.
             */
            void setAlignment(unsigned int alignment);

            /**
             * \brief Returns the active horizontal text alignment specification.
             *
             * Possible horizontal alignment values are defined in namespace Vis::Alignment.
             * 
             * \return The current horizontal text alignment specification.
             */
            unsigned int getAlignment() const;
            
            /**
             * \brief Sets the line spacing value.
             *
             * The final base line spacing is the product of the specified line spacing and the font height
             * returned by the method Vis::FontMetrics::getHeight() for the set font.
             *
             * \param spacing The desired line spacing.
             */
            void setLineSpacing(double spacing);

            /**
             * \brief Returns the active line spacing value.
             * \return The line spacing value.
             */
            double getLineSpacing() const;

            /**
             * \brief Performs a layout of the text for the currently specified font using the provided Vis::FontMetrics instance \a font_metrics.
             * \param font_metrics An instance of a class implementing the Vis::FontMetrics interface.
             * \note This method must be called before the text is rendered by calling the method render(). 
             *       The methods setText() or setFont() invalidate the text layout.
             */
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
