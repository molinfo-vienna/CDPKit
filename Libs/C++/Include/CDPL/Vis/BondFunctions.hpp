/* 
 * BondFunctions.hpp 
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
 * \brief Declaration of functions that operate on Chem::Bond instances.
 */

#ifndef CDPL_VIS_BONDFUNCTIONS_HPP
#define CDPL_VIS_BONDFUNCTIONS_HPP

#include <string>

#include "CDPL/Vis/APIPrefix.hpp"


namespace CDPL
{

    namespace Chem
    {

        class Bond;
    }

    namespace Vis
    {

        class Color;
        class Font;
        class Brush;
        class Pen;
        class SizeSpecification;

        CDPL_VIS_API const Color& getColor(const Chem::Bond& bond);

        CDPL_VIS_API void setColor(Chem::Bond& bond, const Color& color);

        CDPL_VIS_API bool hasColor(const Chem::Bond& bond);

        CDPL_VIS_API void clearColor(Chem::Bond& bond);


        CDPL_VIS_API const SizeSpecification& getLineWidth(const Chem::Bond& bond);

        CDPL_VIS_API void setLineWidth(Chem::Bond& bond, const SizeSpecification& width);

        CDPL_VIS_API bool hasLineWidth(const Chem::Bond& bond);

        CDPL_VIS_API void clearLineWidth(Chem::Bond& bond);


        CDPL_VIS_API const SizeSpecification& getLineSpacing(const Chem::Bond& bond);

        CDPL_VIS_API void setLineSpacing(Chem::Bond& bond, const SizeSpecification& spacing);

        CDPL_VIS_API bool hasLineSpacing(const Chem::Bond& bond);

        CDPL_VIS_API void clearLineSpacing(Chem::Bond& bond);


        CDPL_VIS_API const SizeSpecification& getStereoBondWedgeWidth(const Chem::Bond& bond);

        CDPL_VIS_API void setStereoBondWedgeWidth(Chem::Bond& bond, const SizeSpecification& width);

        CDPL_VIS_API bool hasStereoBondWedgeWidth(const Chem::Bond& bond);

        CDPL_VIS_API void clearStereoBondWedgeWidth(Chem::Bond& bond);


        CDPL_VIS_API const SizeSpecification& getStereoBondHashSpacing(const Chem::Bond& bond);

        CDPL_VIS_API void setStereoBondHashSpacing(Chem::Bond& bond, const SizeSpecification& spacing);

        CDPL_VIS_API bool hasStereoBondHashSpacing(const Chem::Bond& bond);

        CDPL_VIS_API void clearStereoBondHashSpacing(Chem::Bond& bond);


        CDPL_VIS_API const SizeSpecification& getReactionCenterLineLength(const Chem::Bond& bond);

        CDPL_VIS_API void setReactionCenterLineLength(Chem::Bond& bond, const SizeSpecification& length);

        CDPL_VIS_API bool hasReactionCenterLineLength(const Chem::Bond& bond);

        CDPL_VIS_API void clearReactionCenterLineLength(Chem::Bond& bond);


        CDPL_VIS_API const SizeSpecification& getReactionCenterLineSpacing(const Chem::Bond& bond);

        CDPL_VIS_API void setReactionCenterLineSpacing(Chem::Bond& bond, const SizeSpecification& spacing);

        CDPL_VIS_API bool hasReactionCenterLineSpacing(const Chem::Bond& bond);

        CDPL_VIS_API void clearReactionCenterLineSpacing(Chem::Bond& bond);


        CDPL_VIS_API const SizeSpecification& getDoubleBondTrimLength(const Chem::Bond& bond);

        CDPL_VIS_API void setDoubleBondTrimLength(Chem::Bond& bond, const SizeSpecification& length);

        CDPL_VIS_API bool hasDoubleBondTrimLength(const Chem::Bond& bond);

        CDPL_VIS_API void clearDoubleBondTrimLength(Chem::Bond& bond);


        CDPL_VIS_API const SizeSpecification& getTripleBondTrimLength(const Chem::Bond& bond);

        CDPL_VIS_API void setTripleBondTrimLength(Chem::Bond& bond, const SizeSpecification& length);

        CDPL_VIS_API bool hasTripleBondTrimLength(const Chem::Bond& bond);

        CDPL_VIS_API void clearTripleBondTrimLength(Chem::Bond& bond);


        CDPL_VIS_API const Font& getLabelFont(const Chem::Bond& bond);

        CDPL_VIS_API void setLabelFont(Chem::Bond& bond, const Font& font);

        CDPL_VIS_API bool hasLabelFont(const Chem::Bond& bond);

        CDPL_VIS_API void clearLabelFont(Chem::Bond& bond);


        CDPL_VIS_API const SizeSpecification& getLabelSize(const Chem::Bond& bond);

        CDPL_VIS_API void setLabelSize(Chem::Bond& bond, const SizeSpecification& size);

        CDPL_VIS_API bool hasLabelSize(const Chem::Bond& bond);

        CDPL_VIS_API void clearLabelSize(Chem::Bond& bond);


        CDPL_VIS_API const SizeSpecification& getLabelMargin(const Chem::Bond& bond);

        CDPL_VIS_API void setLabelMargin(Chem::Bond& bond, const SizeSpecification& margin);

        CDPL_VIS_API bool hasLabelMargin(const Chem::Bond& bond);

        CDPL_VIS_API void clearLabelMargin(Chem::Bond& bond);

        /**
         * \since 1.1
         */
        CDPL_VIS_API const Font& getConfigurationLabelFont(const Chem::Bond& bond);

        CDPL_VIS_API void setConfigurationLabelFont(Chem::Bond& bond, const Font& font);

        CDPL_VIS_API bool hasConfigurationLabelFont(const Chem::Bond& bond);

        CDPL_VIS_API void clearConfigurationLabelFont(Chem::Bond& bond);

        /**
         * \since 1.1
         */
        CDPL_VIS_API const SizeSpecification& getConfigurationLabelSize(const Chem::Bond& bond);

        CDPL_VIS_API void setConfigurationLabelSize(Chem::Bond& bond, const SizeSpecification& size);

        CDPL_VIS_API bool hasConfigurationLabelSize(const Chem::Bond& bond);

        CDPL_VIS_API void clearConfigurationLabelSize(Chem::Bond& bond);
        
        /**
         * \since 1.2
         */
        CDPL_VIS_API const Color& getConfigurationLabelColor(const Chem::Bond& bond);

        CDPL_VIS_API void setConfigurationLabelColor(Chem::Bond& bond, const Color& color);

        CDPL_VIS_API bool hasConfigurationLabelColor(const Chem::Bond& bond);

        CDPL_VIS_API void clearConfigurationLabelColor(Chem::Bond& bond);

        /**
         * \since 1.2
         */
        CDPL_VIS_API const Font& getCustomLabelFont(const Chem::Bond& bond);

        CDPL_VIS_API void setCustomLabelFont(Chem::Bond& bond, const Font& font);

        CDPL_VIS_API bool hasCustomLabelFont(const Chem::Bond& bond);

        CDPL_VIS_API void clearCustomLabelFont(Chem::Bond& bond);

        /**
         * \since 1.2
         */
        CDPL_VIS_API const SizeSpecification& getCustomLabelSize(const Chem::Bond& bond);

        CDPL_VIS_API void setCustomLabelSize(Chem::Bond& bond, const SizeSpecification& size);

        CDPL_VIS_API bool hasCustomLabelSize(const Chem::Bond& bond);

        CDPL_VIS_API void clearCustomLabelSize(Chem::Bond& bond);
        
        /**
         * \since 1.2
         */
        CDPL_VIS_API const Color& getCustomLabelColor(const Chem::Bond& bond);

        CDPL_VIS_API void setCustomLabelColor(Chem::Bond& bond, const Color& color);

        CDPL_VIS_API bool hasCustomLabelColor(const Chem::Bond& bond);

        CDPL_VIS_API void clearCustomLabelColor(Chem::Bond& bond);

        /**
         * \since 1.2
         */
        CDPL_VIS_API const std::string& getCustomLabel(const Chem::Bond& bond);

        CDPL_VIS_API void setCustomLabel(Chem::Bond& bond, const std::string& text);

        CDPL_VIS_API bool hasCustomLabel(const Chem::Bond& bond);

        CDPL_VIS_API void clearCustomLabel(Chem::Bond& bond);
    
        /**
         * \since 1.2
         */
        CDPL_VIS_API bool getHighlightedFlag(const Chem::Bond& bond);

        CDPL_VIS_API void setHighlightedFlag(Chem::Bond& bond, bool highlighted);

        CDPL_VIS_API bool hasHighlightedFlag(const Chem::Bond& bond);

        CDPL_VIS_API void clearHighlightedFlag(Chem::Bond& bond);

        /**
         * \since 1.2
         */
        CDPL_VIS_API const Brush& getHighlightAreaBrush(const Chem::Bond& bond);

        CDPL_VIS_API void setHighlightAreaBrush(Chem::Bond& bond, const Brush& brush);

        CDPL_VIS_API bool hasHighlightAreaBrush(const Chem::Bond& bond);

        CDPL_VIS_API void clearHighlightAreaBrush(Chem::Bond& bond);

        /**
         * \since 1.2
         */
        CDPL_VIS_API const Pen& getHighlightAreaOutlinePen(const Chem::Bond& bond);

        CDPL_VIS_API void setHighlightAreaOutlinePen(Chem::Bond& bond, const Pen& pen);

        CDPL_VIS_API bool hasHighlightAreaOutlinePen(const Chem::Bond& bond);

        CDPL_VIS_API void clearHighlightAreaOutlinePen(Chem::Bond& bond);

    } // namespace Vis
} // namespace CDPL

#endif // CDPL_VIS_BONDFUNCTIONS_HPP
