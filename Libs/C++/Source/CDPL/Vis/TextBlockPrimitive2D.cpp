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
}


Vis::TextBlockPrimitive2D::TextBlockPrimitive2D():
    alignment(Alignment::LEFT)
{}

void Vis::TextBlockPrimitive2D::render(Renderer2D& renderer) const
{
    renderer.setPen(pen);
    renderer.setFont(font);

    renderer.drawText(position(0), position(1), text);
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

Vis::GraphicsPrimitive2D::SharedPointer Vis::TextBlockPrimitive2D::clone() const
{
    return SharedPointer(new TextBlockPrimitive2D(*this));
}

void Vis::TextBlockPrimitive2D::getBounds(Rectangle2D& bounds, FontMetrics* fm) const
{
    if (!fm) {
        bounds.reset();
        return;
    }

    // TODO
}

void Vis::TextBlockPrimitive2D::processText(const std::string& text)
{
    colorStack.clear();
    styleStack.clear();
    textFragments.clear();

    currColor = pen.getColor();
    currStyle = Style();
    currLine = 0;
    
    std::string tmp_text("<doc>" + text + "</doc>");
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
                        throw Base::ValueError("TextBlockPrimitive2D: element " + LINE_BREAK_TAG + " must not have any content");
                    currLine++;
                    continue;
                }
      
                if (node_name == COLOR_TAG) {
                    auto color = getColor(node);
                    
                    colorStack.push_back(currColor);
                    currColor = color;

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
                        throw Base::ValueError("TextBlockPrimitive2D: conflicting nested " + SUPERSCRIPT_TAG + '/' +
                                               SUBSCRIPT_TAG + " elements");
                    
                    styleStack.push_back(currStyle);
                    currStyle.superscripted = true;
                    
                } else if (node_name == SUBSCRIPT_TAG) {
                    if (currStyle.superscripted)
                        throw Base::ValueError("TextBlockPrimitive2D: conflicting nested " + SUPERSCRIPT_TAG + '/' +
                                               SUBSCRIPT_TAG + " elements");
                    
                    styleStack.push_back(currStyle);
                    currStyle.subscripted = true;
                 
                } else
                   throw Base::ValueError("TextBlockPrimitive2D: unsupported tag '" + std::string(node->name()) + '\'');
                   
                processNode(node);

                currStyle = styleStack.back();
                styleStack.pop_back();
            }

            default:
                continue;
        }
    }
}

Vis::Color Vis::TextBlockPrimitive2D::getColor(XMLNode* node) const
{
    Color color(0.0, 0.0, 0.0, 1.0);
    bool comp_spec = false;
    
    if (auto attr = node->first_attribute(COLOR_R_ATTR)) {
        color.setRed(Internal::parseNumber<double>(attr->value(), attr->value() + attr->value_size(),
                                                   "TextBlockPrimitive2D: error while parsing red color component"));
        comp_spec = true;
    }
    
    if (auto attr = node->first_attribute(COLOR_G_ATTR)) {
        color.setGreen(Internal::parseNumber<double>(attr->value(), attr->value() + attr->value_size(),
                                                     "TextBlockPrimitive2D: error while parsing green color component"));
        comp_spec = true;
    }
   
    if (auto attr = node->first_attribute(COLOR_B_ATTR)) {
        color.setBlue(Internal::parseNumber<double>(attr->value(), attr->value() + attr->value_size(),
                                                    "TextBlockPrimitive2D: error while parsing blue color component"));
        comp_spec = true;
    }
   
    if (auto attr = node->first_attribute(COLOR_A_ATTR)) {
        color.setAlpha(Internal::parseNumber<double>(attr->value(), attr->value() + attr->value_size(),
                                                     "TextBlockPrimitive2D: error while parsing alpha color component"));
        comp_spec = true;
    }
   
    if (!comp_spec)
        return pen.getColor();

    return color;
}
