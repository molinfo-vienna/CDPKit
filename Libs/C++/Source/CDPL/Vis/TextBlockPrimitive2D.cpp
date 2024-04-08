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
#include <cctype>
#include <locale>

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

    constexpr double  SUB_SUPER_SCRIPT_FONT_SIZE_FACTOR = 0.6; 
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

        renderer.setPen(tf.defColor ? pen : tf.color);
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
    auto max_line_width = 0.0;
 
    std::vector<double> x_offsets(currLine + 1, 0.0);
    std::vector<Rectangle2D> line_bounds(currLine + 1);
    Rectangle2D tf_bounds;
    
    for (auto& tf : textFragments) {
        applyStyle(font, font_size, tf.style);

        font_metrics.setFont(font);

        auto y_offs = 0.0;

        if (tf.style.superscripted)
            y_offs = font_metrics.getAscent() - font_asc;

        else if (tf.style.subscripted)
            y_offs = font_desc - font_metrics.getDescent();

        tf.yPos = tf.line * line_spacing + font_asc + y_offs;
        tf.xPos = x_offsets[tf.line];

        font_metrics.getBounds(tf.text, tf_bounds);
        tf_bounds.translate({tf.xPos, tf.yPos});

        line_bounds[tf.line].addRectangle(tf_bounds);
        x_offsets[tf.line] += font_metrics.getWidth(tf.text);

        max_line_width = std::max(max_line_width, line_bounds[tf.line].getWidth());
    }

    auto almnt = (alignment & Alignment::H_ALIGNMENT_MASK);
    auto hor_shift_fact = (almnt == Alignment::H_CENTER ? 0.5 : almnt == Alignment::RIGHT ? 1.0 : 0.0);
  
    for (auto& tf : textFragments)
        tf.xPos += (max_line_width - line_bounds[tf.line].getWidth()) * hor_shift_fact - line_bounds[tf.line].getMin()(0);
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
    auto max_line_width = 0.0;
    
    std::vector<double> x_offsets(currLine + 1, 0.0);
    std::vector<Rectangle2D> line_bounds(currLine + 1);
    Rectangle2D tf_bounds;
    
    for (auto& tf : textFragments) {
        applyStyle(font, font_size, tf.style);

        font_metrics->setFont(font);

        auto y_offs = 0.0;

        if (tf.style.superscripted)
            y_offs = font_metrics->getAscent() - font_asc;

        else if (tf.style.subscripted)
            y_offs = font_desc - font_metrics->getDescent();

        auto y_pos = tf.line * line_spacing + font_asc + y_offs;
        auto x_pos = x_offsets[tf.line];

        font_metrics->getBounds(tf.text, tf_bounds);

        tf_bounds.translate({x_pos, y_pos});

        line_bounds[tf.line].addRectangle(tf_bounds);
        x_offsets[tf.line] += font_metrics->getWidth(tf.text);
        
        max_line_width = std::max(max_line_width, line_bounds[tf.line].getWidth());
    }

    bounds.setBounds(position(0), position(1), position(0) + max_line_width, position(1) +
                     currLine * line_spacing + font_asc + font_desc);
}

void Vis::TextBlockPrimitive2D::processText(const std::string& text)
{
    colorStack.clear();
    styleStack.clear();
    textFragments.clear();

    currStyle = Style();
    currLine = 0;
    
    auto tmp_text("<doc>" + text + "</doc>");
    rapidxml::xml_document<char> xml_doc;

    xml_doc.parse<0>(&tmp_text[0]);

    processNode(xml_doc.first_node());
}

void Vis::TextBlockPrimitive2D::processNode(XMLNode* node)
{
    for (node = node->first_node(); node; node = node->next_sibling()) {
        switch (node->type()) {

            case rapidxml::node_type::node_data:
            case rapidxml::node_type::node_cdata: {
                std::string text_frag;
                auto node_value = node->value();
                
                for (std::size_t i = 0, str_len = node->value_size(); i < str_len; i++) {
                    switch (auto c = node_value[i]) {

                        case '\n':
                            if (!text_frag.empty())
                                textFragments.emplace_back(text_frag, currStyle, currColor, colorStack.empty(), currLine);

                            currLine++;
                            continue;

                        case ' ':
                        case '\t':
                            text_frag.push_back(' ');
                            continue;
                            
                        default:
                            if (std::isspace(c, std::locale::classic()))
                                continue;
                                
                            text_frag.push_back(c);
                    }
                }

                if (!text_frag.empty())
                    textFragments.emplace_back(text_frag, currStyle, currColor, colorStack.empty(), currLine);

                continue;
            }

            case rapidxml::node_type::node_element: {
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
    currColor.setRGBA(0.0, 0.0, 0.0, 1.0);

    if (auto attr = node->first_attribute(COLOR_R_ATTR))
        currColor.setRed(Internal::parseNumber<double>(attr->value(), attr->value() + attr->value_size(),
                                                       "TextBlockPrimitive2D: error while parsing red color component"));

    if (auto attr = node->first_attribute(COLOR_G_ATTR))
        currColor.setGreen(Internal::parseNumber<double>(attr->value(), attr->value() + attr->value_size(),
                                                         "TextBlockPrimitive2D: error while parsing green color component"));

    if (auto attr = node->first_attribute(COLOR_B_ATTR))
        currColor.setBlue(Internal::parseNumber<double>(attr->value(), attr->value() + attr->value_size(),
                                                        "TextBlockPrimitive2D: error while parsing blue color component"));

    if (auto attr = node->first_attribute(COLOR_A_ATTR))
        currColor.setAlpha(Internal::parseNumber<double>(attr->value(), attr->value() + attr->value_size(),
                                                         "TextBlockPrimitive2D: error while parsing alpha color component"));
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
