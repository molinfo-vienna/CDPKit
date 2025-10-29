/* 
 * AtomFunctions.hpp 
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
 * \brief Declaration of functions that operate on Chem::Atom instances.
 */

#ifndef CDPL_VIS_ATOMFUNCTIONS_HPP
#define CDPL_VIS_ATOMFUNCTIONS_HPP

#include <string>

#include "CDPL/Vis/APIPrefix.hpp"


namespace CDPL
{

    namespace Chem
    {

        class Atom;
    }

    namespace Vis
    {

        class Color;
        class Font;
        class Brush;
        class Pen;
        class SizeSpecification;

        CDPL_VIS_API const Color& getColor(const Chem::Atom& atom);

        CDPL_VIS_API void setColor(Chem::Atom& atom, const Color& color);

        CDPL_VIS_API bool hasColor(const Chem::Atom& atom);

        CDPL_VIS_API void clearColor(Chem::Atom& atom);


        CDPL_VIS_API const Font& getLabelFont(const Chem::Atom& atom);

        CDPL_VIS_API void setLabelFont(Chem::Atom& atom, const Font& font);

        CDPL_VIS_API bool hasLabelFont(const Chem::Atom& atom);

        CDPL_VIS_API void clearLabelFont(Chem::Atom& atom);


        CDPL_VIS_API const SizeSpecification& getLabelSize(const Chem::Atom& atom);

        CDPL_VIS_API void setLabelSize(Chem::Atom& atom, const SizeSpecification& size);

        CDPL_VIS_API bool hasLabelSize(const Chem::Atom& atom);

        CDPL_VIS_API void clearLabelSize(Chem::Atom& atom);


        CDPL_VIS_API const Font& getSecondaryLabelFont(const Chem::Atom& atom);

        CDPL_VIS_API void setSecondaryLabelFont(Chem::Atom& atom, const Font&);

        CDPL_VIS_API bool hasSecondaryLabelFont(const Chem::Atom& atom);

        CDPL_VIS_API void clearSecondaryLabelFont(Chem::Atom& atom);


        CDPL_VIS_API const SizeSpecification& getSecondaryLabelSize(const Chem::Atom& atom);

        CDPL_VIS_API void setSecondaryLabelSize(Chem::Atom& atom, const SizeSpecification& size);

        CDPL_VIS_API bool hasSecondaryLabelSize(const Chem::Atom& atom);

        CDPL_VIS_API void clearSecondaryLabelSize(Chem::Atom& atom);


        CDPL_VIS_API const SizeSpecification& getLabelMargin(const Chem::Atom& atom);

        CDPL_VIS_API void setLabelMargin(Chem::Atom& atom, const SizeSpecification& margin);

        CDPL_VIS_API bool hasLabelMargin(const Chem::Atom& atom);

        CDPL_VIS_API void clearLabelMargin(Chem::Atom& atom);


        CDPL_VIS_API const SizeSpecification& getRadicalElectronDotSize(const Chem::Atom& atom);

        CDPL_VIS_API void setRadicalElectronDotSize(Chem::Atom& atom, const SizeSpecification& size);

        CDPL_VIS_API bool hasRadicalElectronDotSize(const Chem::Atom& atom);

        CDPL_VIS_API void clearRadicalElectronDotSize(Chem::Atom& atom);

        /**
         * \since 1.1
         */
        CDPL_VIS_API const Font& getConfigurationLabelFont(const Chem::Atom& atom);

        CDPL_VIS_API void setConfigurationLabelFont(Chem::Atom& atom, const Font& font);

        CDPL_VIS_API bool hasConfigurationLabelFont(const Chem::Atom& atom);

        CDPL_VIS_API void clearConfigurationLabelFont(Chem::Atom& atom);

        /**
         * \since 1.1
         */
        CDPL_VIS_API const SizeSpecification& getConfigurationLabelSize(const Chem::Atom& atom);

        CDPL_VIS_API void setConfigurationLabelSize(Chem::Atom& atom, const SizeSpecification& size);

        CDPL_VIS_API bool hasConfigurationLabelSize(const Chem::Atom& atom);

        CDPL_VIS_API void clearConfigurationLabelSize(Chem::Atom& atom);

        /**
         * \since 1.2
         */
        CDPL_VIS_API const Color& getConfigurationLabelColor(const Chem::Atom& atom);

        CDPL_VIS_API void setConfigurationLabelColor(Chem::Atom& atom, const Color& color);

        CDPL_VIS_API bool hasConfigurationLabelColor(const Chem::Atom& atom);

        CDPL_VIS_API void clearConfigurationLabelColor(Chem::Atom& atom);

        /**
         * \since 1.2
         */
        CDPL_VIS_API const Font& getCustomLabelFont(const Chem::Atom& atom);

        CDPL_VIS_API void setCustomLabelFont(Chem::Atom& atom, const Font& font);

        CDPL_VIS_API bool hasCustomLabelFont(const Chem::Atom& atom);

        CDPL_VIS_API void clearCustomLabelFont(Chem::Atom& atom);

        /**
         * \since 1.2
         */
        CDPL_VIS_API const SizeSpecification& getCustomLabelSize(const Chem::Atom& atom);

        CDPL_VIS_API void setCustomLabelSize(Chem::Atom& atom, const SizeSpecification& size);

        CDPL_VIS_API bool hasCustomLabelSize(const Chem::Atom& atom);

        CDPL_VIS_API void clearCustomLabelSize(Chem::Atom& atom);
        
        /**
         * \since 1.2
         */
        CDPL_VIS_API const Color& getCustomLabelColor(const Chem::Atom& atom);

        CDPL_VIS_API void setCustomLabelColor(Chem::Atom& atom, const Color& color);

        CDPL_VIS_API bool hasCustomLabelColor(const Chem::Atom& atom);

        CDPL_VIS_API void clearCustomLabelColor(Chem::Atom& atom);

        /**
         * \since 1.2
         */
        CDPL_VIS_API const std::string& getCustomLabel(const Chem::Atom& atom);

        CDPL_VIS_API void setCustomLabel(Chem::Atom& atom, const std::string& text);

        CDPL_VIS_API bool hasCustomLabel(const Chem::Atom& atom);

        CDPL_VIS_API void clearCustomLabel(Chem::Atom& atom);
 
        /**
         * \since 1.2
         */
        CDPL_VIS_API bool getHighlightedFlag(const Chem::Atom& atom);

        CDPL_VIS_API void setHighlightedFlag(Chem::Atom& atom, bool highlighted);

        CDPL_VIS_API bool hasHighlightedFlag(const Chem::Atom& atom);

        CDPL_VIS_API void clearHighlightedFlag(Chem::Atom& atom);

        /**
         * \since 1.2
         */
        CDPL_VIS_API const Brush& getHighlightAreaBrush(const Chem::Atom& atom);

        CDPL_VIS_API void setHighlightAreaBrush(Chem::Atom& atom, const Brush& brush);

        CDPL_VIS_API bool hasHighlightAreaBrush(const Chem::Atom& atom);

        CDPL_VIS_API void clearHighlightAreaBrush(Chem::Atom& atom);

        /**
         * \since 1.2
         */
        CDPL_VIS_API const Pen& getHighlightAreaOutlinePen(const Chem::Atom& atom);

        CDPL_VIS_API void setHighlightAreaOutlinePen(Chem::Atom& atom, const Pen& pen);

        CDPL_VIS_API bool hasHighlightAreaOutlinePen(const Chem::Atom& atom);

        CDPL_VIS_API void clearHighlightAreaOutlinePen(Chem::Atom& atom);
        
    } // namespace Vis
} // namespace CDPL

#endif // CDPL_VIS_ATOMFUNCTIONS_HPP
