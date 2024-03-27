/* 
 * TextBlockPrimitive2D.cpp 
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


#include "StaticInit.hpp"

#include <algorithm>

#include "RapidXML/rapidxml.hpp"

#include "CDPL/Vis/TextBlockPrimitive2D.hpp"
#include "CDPL/Vis/Renderer2D.hpp"
#include "CDPL/Vis/Rectangle2D.hpp"
#include "CDPL/Vis/FontMetrics.hpp"
#include "CDPL/Vis/Alignment.hpp"
#include "CDPL/Internal/StringDataIOUtilities.hpp"


using namespace CDPL;


namespace
{

    typedef rapidxml::xml_document<char>  XMLDocument;
    typedef rapidxml::xml_attribute<char> XMLAttribute;

    const std::string LINE_BREAK_TAG  = "br";
    const std::string BOLD_TAG        = "b";
    const std::string ITALIC_TAG      = "i";
    const std::string UNDERLINED_TAG  = "u";
    const std::string OVERLINED_TAG   = "o";
    const std::string STRIKEDOUT_TAG  = "s";
    const std::string SUPERSCRIPT_TAG = "sup";
    const std::string SUBSCRIPT_TAG   = "sub";
    const std::string COLOR_TAG       = "color";
    const char*       COLOR_R_ATTR    = "r";
    const char*       COLOR_G_ATTR    = "g";
    const char*       COLOR_B_ATTR    = "b";
    const char*       COLOR_A_ATTR    = "a";

    constexpr double  SUB_SUPER_SCRIPT_FONT_SIZE_FACTOR = 0.5; 
}


Vis::TextBlockPrimitive2D::TextBlockPrimitive2D():
    alignment(Alignment::LEFT), lineSpacing(1.0)
{}

void Vis::TextBlockPrimitive2D::render(Renderer2D& renderer) const
{
    if (textFragments.empty())
        return;

    auto font = this->font;
    auto font_size = font.getSize();
    
    for (auto& tf : textFragments) {
        applyStyle(font, font_size, tf.style);

        renderer.setPen(tf.color.second ? pen : tf.color.first);
        renderer.setFont(font);
        renderer.drawText(tf.xPos + position(0), tf.yPos + position(1), tf.text);
    }
}

void Vis::TextBlockPrimitive2D::setText(const std::string& text)
{
    try {
        processText(text);

        this->text = text;
        
    } catch (const rapidxml::parse_error& e) {
        throw Base::ValueError("TextBlockPrimitive2D: text processing failed: " + std::string(e.what()));
    }
}

const std::string& Vis::TextBlockPrimitive2D::getText() const
{
    return text;
}

void Vis::TextBlockPrimitive2D::setPosition(const Math::Vector2D& pos)
{
    position = pos;
}

void Vis::TextBlockPrimitive2D::setPosition(double x, double y)
{
    position(0) = x;
    position(1) = y;
}

const Math::Vector2D& Vis::TextBlockPrimitive2D::getPosition() const
{
    return position;
}

void Vis::TextBlockPrimitive2D::setPen(const Pen& pen)
{
    this->pen = pen;
}

const Vis::Pen& Vis::TextBlockPrimitive2D::getPen() const
{
    return pen;
}

void Vis::TextBlockPrimitive2D::setFont(const Font& font)
{
    this->font = font;
}

const Vis::Font& Vis::TextBlockPrimitive2D::getFont() const
{
    return font;
}    

void Vis::TextBlockPrimitive2D::setAlignment(unsigned int alignment)
{
    this->alignment = alignment;
}

unsigned int Vis::TextBlockPrimitive2D::getAlignment() const
{
    return alignment;
}    

void Vis::TextBlockPrimitive2D::setLineSpacing(double spacing)
{
    lineSpacing = spacing;
}

double Vis::TextBlockPrimitive2D::getLineSpacing() const
{
    return lineSpacing;
}

void Vis::TextBlockPrimitive2D::layout(FontMetrics& font_metrics)
{
    if (textFragments.empty())
        return;

    font_metrics.setFont(this->font);

    auto line_spacing = lineSpacing * font_metrics.getHeight();
    auto font_size = font.getSize();
    auto font_asc = font_metrics.getAscent();
    auto font_desc = font_metrics.getDescent();
    auto font = this->font;
   
    std::vector<double> line_widths(currLine + 1, 0.0);

    for (auto& tf : textFragments) {
        applyStyle(font, font_size, tf.style);

        font_metrics.setFont(font);
        font_metrics.getBounds(tf.text, tf.bBox);

        auto y_offs = 0.0;

        if (tf.style.superscripted)
            y_offs = font_metrics.getAscent() - font_asc;

        else if (tf.style.subscripted)
            y_offs = font_desc - font_metrics.getDescent();

        tf.yPos = tf.line * line_spacing + font_asc + y_offs;
        tf.xPos = line_widths[tf.line];

        line_widths[tf.line] += font_metrics.getWidth(tf.text);
    }

    auto hor_shift_fact = (alignment == Alignment::H_CENTER ? 0.5 : alignment == Alignment::RIGHT ? 1.0 : 0.0);
    auto max_width = *std::max_element(line_widths.begin(), line_widths.end());

    if (hor_shift_fact > 0.0)
        for (auto& tf : textFragments)
            tf.xPos += (max_width - line_widths[tf.line]) * hor_shift_fact;

    auto min_x = max_width;

    for (auto& tf : textFragments)
        min_x = std::min(min_x, tf.xPos + tf.bBox.getMin()(0));

    for (auto& tf : textFragments)
        tf.xPos -= min_x;
 }

Vis::GraphicsPrimitive2D::SharedPointer Vis::TextBlockPrimitive2D::clone() const
{
    return SharedPointer(new TextBlockPrimitive2D(*this));
}

void Vis::TextBlockPrimitive2D::getBounds(Rectangle2D& bounds, FontMetrics* font_metrics) const
{
    if (!font_metrics || textFragments.empty()) {
        bounds.reset();
        return;
    }

    font_metrics->setFont(this->font);

    auto line_spacing = lineSpacing * font_metrics->getHeight();
    auto font_size = font.getSize();
    auto font_asc = font_metrics->getAscent();
    auto font_desc = font_metrics->getDescent();
    auto font = this->font;
    Rectangle2D text_bounds;
   
    std::vector<double> line_widths(currLine + 1, 0.0);
    std::vector<Rectangle2D> line_bounds(currLine + 1);

    for (auto& tf : textFragments) {
        applyStyle(font, font_size, tf.style);

        font_metrics->setFont(font);

        auto y_offs = 0.0;

        if (tf.style.superscripted)
            y_offs = font_metrics->getAscent() - font_asc;

        else if (tf.style.subscripted)
            y_offs = font_desc - font_metrics->getDescent();

        auto y_pos = tf.line * line_spacing + font_asc + y_offs;
        auto x_pos = line_widths[tf.line];

        font_metrics->getBounds(tf.text, text_bounds);

        text_bounds.translate({x_pos, y_pos});

        line_bounds[tf.line].addRectangle(text_bounds);
        line_widths[tf.line] += font_metrics->getWidth(tf.text);
    }

    auto hor_shift_fact = (alignment == Alignment::H_CENTER ? 0.5 : alignment == Alignment::RIGHT ? 1.0 : 0.0);
    auto max_width = *std::max_element(line_widths.begin(), line_widths.end());
    auto min_x = 0.0;
    auto max_x = 0.0;

    for (std::size_t i = 0; i < line_bounds.size(); i++) {
        if (!line_bounds[i].isDefined())
            continue;

        auto d_x = (max_width - line_widths[i]) * hor_shift_fact;

        min_x = std::min(min_x, line_bounds[i].getMin()(0) + d_x);
        max_x = std::max(max_x, line_bounds[i].getMax()(0) + d_x);
    }

    bounds.setBounds(position(0), position(1), position(0) + max_x - min_x, position(1) + (currLine + 1) * line_spacing);
}

void Vis::TextBlockPrimitive2D::processText(const std::string& text)
{
    colorStack.clear();
    styleStack.clear();
    textFragments.clear();

    currColor.second = true;
    currStyle = Style();
    currLine = 0;
    
    auto tmp_text("<doc>" + text + "</doc>");
    XMLDocument xml_doc;

    xml_doc.parse<0>(&tmp_text[0]);

    processNode(xml_doc.first_node());
}

void Vis::TextBlockPrimitive2D::processNode(XMLNode* node)
{
    for (node = node->first_node(); node; node = node->next_sibling()) {
        switch (node->type()) {

            case rapidxml::node_data:
            case rapidxml::node_cdata:
                textFragments.emplace_back(node->value(), currStyle, currColor, currLine);
                continue;

            case rapidxml::node_element: {
                auto node_name = node->name();

                if (node_name == LINE_BREAK_TAG) {
                    if (node->first_node())
                        throw Base::ValueError("TextBlockPrimitive2D: element <" + LINE_BREAK_TAG + "> must not have any content");

                    currLine++;
                    continue;
                }
      
                if (node_name == COLOR_TAG) {
                    colorStack.push_back(currColor);
                    getColor(node);

                    processNode(node);
 
                    currColor = colorStack.back();
                    colorStack.pop_back();
                    continue;
                }

                if (node_name == BOLD_TAG) {
                    styleStack.push_back(currStyle);
                    currStyle.bold = true;
                   
                } else  if (node_name == ITALIC_TAG) {
                    styleStack.push_back(currStyle);
                    currStyle.italic = true;

                } else if  (node_name == UNDERLINED_TAG) {
                    styleStack.push_back(currStyle);
                    currStyle.underlined = true;

                } else if (node_name == STRIKEDOUT_TAG) {
                    styleStack.push_back(currStyle);
                    currStyle.strikedOut = true;

                } else if (node_name == OVERLINED_TAG) {
                    styleStack.push_back(currStyle);
                    currStyle.overlined = true;
                   
                } else if (node_name == SUPERSCRIPT_TAG) {
                    if (currStyle.subscripted)
                        throw Base::ValueError("TextBlockPrimitive2D: conflicting nested <" + SUPERSCRIPT_TAG + ">/<" +
                                               SUBSCRIPT_TAG + "> elements");
                    
                    styleStack.push_back(currStyle);
                    currStyle.superscripted = true;
                    
                } else if (node_name == SUBSCRIPT_TAG) {
                    if (currStyle.superscripted)
                        throw Base::ValueError("TextBlockPrimitive2D: conflicting nested <" + SUPERSCRIPT_TAG + ">/<" +
                                               SUBSCRIPT_TAG + "> elements");
                    
                    styleStack.push_back(currStyle);
                    currStyle.subscripted = true;
                 
                } else
                   throw Base::ValueError("TextBlockPrimitive2D: unsupported tag '<" + std::string(node->name()) + ">\'");
                   
                processNode(node);

                currStyle = styleStack.back();
                styleStack.pop_back();
            }

            default:
                continue;
        }
    }
}

void Vis::TextBlockPrimitive2D::getColor(XMLNode* node)
{
    currColor.first.setRGBA(0.0, 0.0, 0.0, 1.0);
    currColor.second = true;
    
    if (auto attr = node->first_attribute(COLOR_R_ATTR)) {
        currColor.first.setRed(Internal::parseNumber<double>(attr->value(), attr->value() + attr->value_size(),
                                                             "TextBlockPrimitive2D: error while parsing red color component"));
        currColor.second = false;
    }
    
    if (auto attr = node->first_attribute(COLOR_G_ATTR)) {
        currColor.first.setGreen(Internal::parseNumber<double>(attr->value(), attr->value() + attr->value_size(),
                                                               "TextBlockPrimitive2D: error while parsing green color component"));
        currColor.second = false;
    }
   
    if (auto attr = node->first_attribute(COLOR_B_ATTR)) {
        currColor.first.setBlue(Internal::parseNumber<double>(attr->value(), attr->value() + attr->value_size(),
                                                              "TextBlockPrimitive2D: error while parsing blue color component"));
        currColor.second = false;
    }
   
    if (auto attr = node->first_attribute(COLOR_A_ATTR)) {
        currColor.first.setAlpha(Internal::parseNumber<double>(attr->value(), attr->value() + attr->value_size(),
                                                               "TextBlockPrimitive2D: error while parsing alpha color component"));
        currColor.second = false;
    }
}

void Vis::TextBlockPrimitive2D::applyStyle(Font& font, double font_size, const Style& style) const
{
    font.setBold(style.bold);
    font.setItalic(style.italic);
    font.setUnderlined(style.underlined);
    font.setOverlined(style.overlined);
    font.setStrikedOut(style.strikedOut);

    if (style.subscripted || style.superscripted)
        font.setSize(font_size * SUB_SUPER_SCRIPT_FONT_SIZE_FACTOR);
    else
        font.setSize(font_size);
}
