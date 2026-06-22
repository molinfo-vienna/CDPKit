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

        /**
         * \brief Returns the value of the Vis::AtomProperty::COLOR property of the atom \a atom.
         * \param atom The atom for which to return the property value.
         * \return The value of the Vis::AtomProperty::COLOR property.
         */
        CDPL_VIS_API const Color& getColor(const Chem::Atom& atom);

        /**
         * \brief Sets the value of the Vis::AtomProperty::COLOR property of the atom \a atom to \a color.
         * \param atom The atom for which to set the property value.
         * \param color The new value of the Vis::AtomProperty::COLOR property.
         */
        CDPL_VIS_API void setColor(Chem::Atom& atom, const Color& color);

        /**
         * \brief Tells whether the Vis::AtomProperty::COLOR property of the atom \a atom is set.
         * \param atom The atom for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasColor(const Chem::Atom& atom);

        /**
         * \brief Clears the value of the Vis::AtomProperty::COLOR property of the atom \a atom.
         * \param atom The atom for which to clear the property value.
         */
        CDPL_VIS_API void clearColor(Chem::Atom& atom);


        /**
         * \brief Returns the value of the Vis::AtomProperty::LABEL_FONT property of the atom \a atom.
         * \param atom The atom for which to return the property value.
         * \return The value of the Vis::AtomProperty::LABEL_FONT property.
         */
        CDPL_VIS_API const Font& getLabelFont(const Chem::Atom& atom);

        /**
         * \brief Sets the value of the Vis::AtomProperty::LABEL_FONT property of the atom \a atom to \a font.
         * \param atom The atom for which to set the property value.
         * \param font The new value of the Vis::AtomProperty::LABEL_FONT property.
         */
        CDPL_VIS_API void setLabelFont(Chem::Atom& atom, const Font& font);

        /**
         * \brief Tells whether the Vis::AtomProperty::LABEL_FONT property of the atom \a atom is set.
         * \param atom The atom for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasLabelFont(const Chem::Atom& atom);

        /**
         * \brief Clears the value of the Vis::AtomProperty::LABEL_FONT property of the atom \a atom.
         * \param atom The atom for which to clear the property value.
         */
        CDPL_VIS_API void clearLabelFont(Chem::Atom& atom);


        /**
         * \brief Returns the value of the Vis::AtomProperty::LABEL_SIZE property of the atom \a atom.
         * \param atom The atom for which to return the property value.
         * \return The value of the Vis::AtomProperty::LABEL_SIZE property.
         */
        CDPL_VIS_API const SizeSpecification& getLabelSize(const Chem::Atom& atom);

        /**
         * \brief Sets the value of the Vis::AtomProperty::LABEL_SIZE property of the atom \a atom to \a size.
         * \param atom The atom for which to set the property value.
         * \param size The new value of the Vis::AtomProperty::LABEL_SIZE property.
         */
        CDPL_VIS_API void setLabelSize(Chem::Atom& atom, const SizeSpecification& size);

        /**
         * \brief Tells whether the Vis::AtomProperty::LABEL_SIZE property of the atom \a atom is set.
         * \param atom The atom for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasLabelSize(const Chem::Atom& atom);

        /**
         * \brief Clears the value of the Vis::AtomProperty::LABEL_SIZE property of the atom \a atom.
         * \param atom The atom for which to clear the property value.
         */
        CDPL_VIS_API void clearLabelSize(Chem::Atom& atom);


        /**
         * \brief Returns the value of the Vis::AtomProperty::SECONDARY_LABEL_FONT property of the atom \a atom.
         * \param atom The atom for which to return the property value.
         * \return The value of the Vis::AtomProperty::SECONDARY_LABEL_FONT property.
         */
        CDPL_VIS_API const Font& getSecondaryLabelFont(const Chem::Atom& atom);

        /**
         * \brief Sets the value of the Vis::AtomProperty::SECONDARY_LABEL_FONT property of the atom \a atom to \a font.
         * \param atom The atom for which to set the property value.
         * \param font The new value of the Vis::AtomProperty::SECONDARY_LABEL_FONT property.
         */
        CDPL_VIS_API void setSecondaryLabelFont(Chem::Atom& atom, const Font& font);

        /**
         * \brief Tells whether the Vis::AtomProperty::SECONDARY_LABEL_FONT property of the atom \a atom is set.
         * \param atom The atom for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasSecondaryLabelFont(const Chem::Atom& atom);

        /**
         * \brief Clears the value of the Vis::AtomProperty::SECONDARY_LABEL_FONT property of the atom \a atom.
         * \param atom The atom for which to clear the property value.
         */
        CDPL_VIS_API void clearSecondaryLabelFont(Chem::Atom& atom);


        /**
         * \brief Returns the value of the Vis::AtomProperty::SECONDARY_LABEL_SIZE property of the atom \a atom.
         * \param atom The atom for which to return the property value.
         * \return The value of the Vis::AtomProperty::SECONDARY_LABEL_SIZE property.
         */
        CDPL_VIS_API const SizeSpecification& getSecondaryLabelSize(const Chem::Atom& atom);

        /**
         * \brief Sets the value of the Vis::AtomProperty::SECONDARY_LABEL_SIZE property of the atom \a atom to \a size.
         * \param atom The atom for which to set the property value.
         * \param size The new value of the Vis::AtomProperty::SECONDARY_LABEL_SIZE property.
         */
        CDPL_VIS_API void setSecondaryLabelSize(Chem::Atom& atom, const SizeSpecification& size);

        /**
         * \brief Tells whether the Vis::AtomProperty::SECONDARY_LABEL_SIZE property of the atom \a atom is set.
         * \param atom The atom for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasSecondaryLabelSize(const Chem::Atom& atom);

        /**
         * \brief Clears the value of the Vis::AtomProperty::SECONDARY_LABEL_SIZE property of the atom \a atom.
         * \param atom The atom for which to clear the property value.
         */
        CDPL_VIS_API void clearSecondaryLabelSize(Chem::Atom& atom);


        /**
         * \brief Returns the value of the Vis::AtomProperty::LABEL_MARGIN property of the atom \a atom.
         * \param atom The atom for which to return the property value.
         * \return The value of the Vis::AtomProperty::LABEL_MARGIN property.
         */
        CDPL_VIS_API const SizeSpecification& getLabelMargin(const Chem::Atom& atom);

        /**
         * \brief Sets the value of the Vis::AtomProperty::LABEL_MARGIN property of the atom \a atom to \a margin.
         * \param atom The atom for which to set the property value.
         * \param margin The new value of the Vis::AtomProperty::LABEL_MARGIN property.
         */
        CDPL_VIS_API void setLabelMargin(Chem::Atom& atom, const SizeSpecification& margin);

        /**
         * \brief Tells whether the Vis::AtomProperty::LABEL_MARGIN property of the atom \a atom is set.
         * \param atom The atom for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasLabelMargin(const Chem::Atom& atom);

        /**
         * \brief Clears the value of the Vis::AtomProperty::LABEL_MARGIN property of the atom \a atom.
         * \param atom The atom for which to clear the property value.
         */
        CDPL_VIS_API void clearLabelMargin(Chem::Atom& atom);


        /**
         * \brief Returns the value of the Vis::AtomProperty::RADICAL_ELECTRON_DOT_SIZE property of the atom \a atom.
         * \param atom The atom for which to return the property value.
         * \return The value of the Vis::AtomProperty::RADICAL_ELECTRON_DOT_SIZE property.
         */
        CDPL_VIS_API const SizeSpecification& getRadicalElectronDotSize(const Chem::Atom& atom);

        /**
         * \brief Sets the value of the Vis::AtomProperty::RADICAL_ELECTRON_DOT_SIZE property of the atom \a atom to \a size.
         * \param atom The atom for which to set the property value.
         * \param size The new value of the Vis::AtomProperty::RADICAL_ELECTRON_DOT_SIZE property.
         */
        CDPL_VIS_API void setRadicalElectronDotSize(Chem::Atom& atom, const SizeSpecification& size);

        /**
         * \brief Tells whether the Vis::AtomProperty::RADICAL_ELECTRON_DOT_SIZE property of the atom \a atom is set.
         * \param atom The atom for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasRadicalElectronDotSize(const Chem::Atom& atom);

        /**
         * \brief Clears the value of the Vis::AtomProperty::RADICAL_ELECTRON_DOT_SIZE property of the atom \a atom.
         * \param atom The atom for which to clear the property value.
         */
        CDPL_VIS_API void clearRadicalElectronDotSize(Chem::Atom& atom);

        /**
         * \brief Returns the value of the Vis::AtomProperty::CONFIGURATION_LABEL_FONT property of the atom \a atom.
         * \param atom The atom for which to return the property value.
         * \return The value of the Vis::AtomProperty::CONFIGURATION_LABEL_FONT property.
         * \since 1.1
         */
        CDPL_VIS_API const Font& getConfigurationLabelFont(const Chem::Atom& atom);

        /**
         * \brief Sets the value of the Vis::AtomProperty::CONFIGURATION_LABEL_FONT property of the atom \a atom to \a font.
         * \param atom The atom for which to set the property value.
         * \param font The new value of the Vis::AtomProperty::CONFIGURATION_LABEL_FONT property.
         * \since 1.1
         */
        CDPL_VIS_API void setConfigurationLabelFont(Chem::Atom& atom, const Font& font);

        /**
         * \brief Tells whether the Vis::AtomProperty::CONFIGURATION_LABEL_FONT property of the atom \a atom is set.
         * \param atom The atom for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         * \since 1.1
         */
        CDPL_VIS_API bool hasConfigurationLabelFont(const Chem::Atom& atom);

        /**
         * \brief Clears the value of the Vis::AtomProperty::CONFIGURATION_LABEL_FONT property of the atom \a atom.
         * \param atom The atom for which to clear the property value.
         * \since 1.1
         */
        CDPL_VIS_API void clearConfigurationLabelFont(Chem::Atom& atom);

        /**
         * \brief Returns the value of the Vis::AtomProperty::CONFIGURATION_LABEL_SIZE property of the atom \a atom.
         * \param atom The atom for which to return the property value.
         * \return The value of the Vis::AtomProperty::CONFIGURATION_LABEL_SIZE property.
         * \since 1.1
         */
        CDPL_VIS_API const SizeSpecification& getConfigurationLabelSize(const Chem::Atom& atom);

        /**
         * \brief Sets the value of the Vis::AtomProperty::CONFIGURATION_LABEL_SIZE property of the atom \a atom to \a size.
         * \param atom The atom for which to set the property value.
         * \param size The new value of the Vis::AtomProperty::CONFIGURATION_LABEL_SIZE property.
         * \since 1.1
         */
        CDPL_VIS_API void setConfigurationLabelSize(Chem::Atom& atom, const SizeSpecification& size);

        /**
         * \brief Tells whether the Vis::AtomProperty::CONFIGURATION_LABEL_SIZE property of the atom \a atom is set.
         * \param atom The atom for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         * \since 1.1
         */
        CDPL_VIS_API bool hasConfigurationLabelSize(const Chem::Atom& atom);

        /**
         * \brief Clears the value of the Vis::AtomProperty::CONFIGURATION_LABEL_SIZE property of the atom \a atom.
         * \param atom The atom for which to clear the property value.
         * \since 1.1
         */
        CDPL_VIS_API void clearConfigurationLabelSize(Chem::Atom& atom);

        /**
         * \brief Returns the value of the Vis::AtomProperty::CONFIGURATION_LABEL_COLOR property of the atom \a atom.
         * \param atom The atom for which to return the property value.
         * \return The value of the Vis::AtomProperty::CONFIGURATION_LABEL_COLOR property.
         * \since 1.2
         */
        CDPL_VIS_API const Color& getConfigurationLabelColor(const Chem::Atom& atom);

        /**
         * \brief Sets the value of the Vis::AtomProperty::CONFIGURATION_LABEL_COLOR property of the atom \a atom to \a color.
         * \param atom The atom for which to set the property value.
         * \param color The new value of the Vis::AtomProperty::CONFIGURATION_LABEL_COLOR property.
         * \since 1.2
         */
        CDPL_VIS_API void setConfigurationLabelColor(Chem::Atom& atom, const Color& color);

        /**
         * \brief Tells whether the Vis::AtomProperty::CONFIGURATION_LABEL_COLOR property of the atom \a atom is set.
         * \param atom The atom for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         * \since 1.2
         */
        CDPL_VIS_API bool hasConfigurationLabelColor(const Chem::Atom& atom);

        /**
         * \brief Clears the value of the Vis::AtomProperty::CONFIGURATION_LABEL_COLOR property of the atom \a atom.
         * \param atom The atom for which to clear the property value.
         * \since 1.2
         */
        CDPL_VIS_API void clearConfigurationLabelColor(Chem::Atom& atom);

        /**
         * \brief Returns the value of the Vis::AtomProperty::CUSTOM_LABEL_FONT property of the atom \a atom.
         * \param atom The atom for which to return the property value.
         * \return The value of the Vis::AtomProperty::CUSTOM_LABEL_FONT property.
         * \since 1.2
         */
        CDPL_VIS_API const Font& getCustomLabelFont(const Chem::Atom& atom);

        /**
         * \brief Sets the value of the Vis::AtomProperty::CUSTOM_LABEL_FONT property of the atom \a atom to \a font.
         * \param atom The atom for which to set the property value.
         * \param font The new value of the Vis::AtomProperty::CUSTOM_LABEL_FONT property.
         * \since 1.2
         */
        CDPL_VIS_API void setCustomLabelFont(Chem::Atom& atom, const Font& font);

        /**
         * \brief Tells whether the Vis::AtomProperty::CUSTOM_LABEL_FONT property of the atom \a atom is set.
         * \param atom The atom for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         * \since 1.2
         */
        CDPL_VIS_API bool hasCustomLabelFont(const Chem::Atom& atom);

        /**
         * \brief Clears the value of the Vis::AtomProperty::CUSTOM_LABEL_FONT property of the atom \a atom.
         * \param atom The atom for which to clear the property value.
         * \since 1.2
         */
        CDPL_VIS_API void clearCustomLabelFont(Chem::Atom& atom);

        /**
         * \brief Returns the value of the Vis::AtomProperty::CUSTOM_LABEL_SIZE property of the atom \a atom.
         * \param atom The atom for which to return the property value.
         * \return The value of the Vis::AtomProperty::CUSTOM_LABEL_SIZE property.
         * \since 1.2
         */
        CDPL_VIS_API const SizeSpecification& getCustomLabelSize(const Chem::Atom& atom);

        /**
         * \brief Sets the value of the Vis::AtomProperty::CUSTOM_LABEL_SIZE property of the atom \a atom to \a size.
         * \param atom The atom for which to set the property value.
         * \param size The new value of the Vis::AtomProperty::CUSTOM_LABEL_SIZE property.
         * \since 1.2
         */
        CDPL_VIS_API void setCustomLabelSize(Chem::Atom& atom, const SizeSpecification& size);

        /**
         * \brief Tells whether the Vis::AtomProperty::CUSTOM_LABEL_SIZE property of the atom \a atom is set.
         * \param atom The atom for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         * \since 1.2
         */
        CDPL_VIS_API bool hasCustomLabelSize(const Chem::Atom& atom);

        /**
         * \brief Clears the value of the Vis::AtomProperty::CUSTOM_LABEL_SIZE property of the atom \a atom.
         * \param atom The atom for which to clear the property value.
         * \since 1.2
         */
        CDPL_VIS_API void clearCustomLabelSize(Chem::Atom& atom);

        /**
         * \brief Returns the value of the Vis::AtomProperty::CUSTOM_LABEL_COLOR property of the atom \a atom.
         * \param atom The atom for which to return the property value.
         * \return The value of the Vis::AtomProperty::CUSTOM_LABEL_COLOR property.
         * \since 1.2
         */
        CDPL_VIS_API const Color& getCustomLabelColor(const Chem::Atom& atom);

        /**
         * \brief Sets the value of the Vis::AtomProperty::CUSTOM_LABEL_COLOR property of the atom \a atom to \a color.
         * \param atom The atom for which to set the property value.
         * \param color The new value of the Vis::AtomProperty::CUSTOM_LABEL_COLOR property.
         * \since 1.2
         */
        CDPL_VIS_API void setCustomLabelColor(Chem::Atom& atom, const Color& color);

        /**
         * \brief Tells whether the Vis::AtomProperty::CUSTOM_LABEL_COLOR property of the atom \a atom is set.
         * \param atom The atom for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         * \since 1.2
         */
        CDPL_VIS_API bool hasCustomLabelColor(const Chem::Atom& atom);

        /**
         * \brief Clears the value of the Vis::AtomProperty::CUSTOM_LABEL_COLOR property of the atom \a atom.
         * \param atom The atom for which to clear the property value.
         * \since 1.2
         */
        CDPL_VIS_API void clearCustomLabelColor(Chem::Atom& atom);

        /**
         * \brief Returns the value of the Vis::AtomProperty::CUSTOM_LABEL property of the atom \a atom.
         * \param atom The atom for which to return the property value.
         * \return The value of the Vis::AtomProperty::CUSTOM_LABEL property.
         * \since 1.2
         */
        CDPL_VIS_API const std::string& getCustomLabel(const Chem::Atom& atom);

        /**
         * \brief Sets the value of the Vis::AtomProperty::CUSTOM_LABEL property of the atom \a atom to \a text.
         * \param atom The atom for which to set the property value.
         * \param text The new value of the Vis::AtomProperty::CUSTOM_LABEL property.
         * \since 1.2
         */
        CDPL_VIS_API void setCustomLabel(Chem::Atom& atom, const std::string& text);

        /**
         * \brief Tells whether the Vis::AtomProperty::CUSTOM_LABEL property of the atom \a atom is set.
         * \param atom The atom for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         * \since 1.2
         */
        CDPL_VIS_API bool hasCustomLabel(const Chem::Atom& atom);

        /**
         * \brief Clears the value of the Vis::AtomProperty::CUSTOM_LABEL property of the atom \a atom.
         * \param atom The atom for which to clear the property value.
         * \since 1.2
         */
        CDPL_VIS_API void clearCustomLabel(Chem::Atom& atom);

        /**
         * \brief Returns the value of the Vis::AtomProperty::HIGHLIGHTED_FLAG property of the atom \a atom.
         * \param atom The atom for which to return the property value.
         * \return The value of the Vis::AtomProperty::HIGHLIGHTED_FLAG property.
         * \since 1.2
         */
        CDPL_VIS_API bool getHighlightedFlag(const Chem::Atom& atom);

        /**
         * \brief Sets the value of the Vis::AtomProperty::HIGHLIGHTED_FLAG property of the atom \a atom to \a highlighted.
         * \param atom The atom for which to set the property value.
         * \param highlighted The new value of the Vis::AtomProperty::HIGHLIGHTED_FLAG property.
         * \since 1.2
         */
        CDPL_VIS_API void setHighlightedFlag(Chem::Atom& atom, bool highlighted);

        /**
         * \brief Tells whether the Vis::AtomProperty::HIGHLIGHTED_FLAG property of the atom \a atom is set.
         * \param atom The atom for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         * \since 1.2
         */
        CDPL_VIS_API bool hasHighlightedFlag(const Chem::Atom& atom);

        /**
         * \brief Clears the value of the Vis::AtomProperty::HIGHLIGHTED_FLAG property of the atom \a atom.
         * \param atom The atom for which to clear the property value.
         * \since 1.2
         */
        CDPL_VIS_API void clearHighlightedFlag(Chem::Atom& atom);

        /**
         * \brief Returns the value of the Vis::AtomProperty::HIGHLIGHT_AREA_BRUSH property of the atom \a atom.
         * \param atom The atom for which to return the property value.
         * \return The value of the Vis::AtomProperty::HIGHLIGHT_AREA_BRUSH property.
         * \since 1.2
         */
        CDPL_VIS_API const Brush& getHighlightAreaBrush(const Chem::Atom& atom);

        /**
         * \brief Sets the value of the Vis::AtomProperty::HIGHLIGHT_AREA_BRUSH property of the atom \a atom to \a brush.
         * \param atom The atom for which to set the property value.
         * \param brush The new value of the Vis::AtomProperty::HIGHLIGHT_AREA_BRUSH property.
         * \since 1.2
         */
        CDPL_VIS_API void setHighlightAreaBrush(Chem::Atom& atom, const Brush& brush);

        /**
         * \brief Tells whether the Vis::AtomProperty::HIGHLIGHT_AREA_BRUSH property of the atom \a atom is set.
         * \param atom The atom for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         * \since 1.2
         */
        CDPL_VIS_API bool hasHighlightAreaBrush(const Chem::Atom& atom);

        /**
         * \brief Clears the value of the Vis::AtomProperty::HIGHLIGHT_AREA_BRUSH property of the atom \a atom.
         * \param atom The atom for which to clear the property value.
         * \since 1.2
         */
        CDPL_VIS_API void clearHighlightAreaBrush(Chem::Atom& atom);

        /**
         * \brief Returns the value of the Vis::AtomProperty::HIGHLIGHT_AREA_OUTLINE_PEN property of the atom \a atom.
         * \param atom The atom for which to return the property value.
         * \return The value of the Vis::AtomProperty::HIGHLIGHT_AREA_OUTLINE_PEN property.
         * \since 1.2
         */
        CDPL_VIS_API const Pen& getHighlightAreaOutlinePen(const Chem::Atom& atom);

        /**
         * \brief Sets the value of the Vis::AtomProperty::HIGHLIGHT_AREA_OUTLINE_PEN property of the atom \a atom to \a pen.
         * \param atom The atom for which to set the property value.
         * \param pen The new value of the Vis::AtomProperty::HIGHLIGHT_AREA_OUTLINE_PEN property.
         * \since 1.2
         */
        CDPL_VIS_API void setHighlightAreaOutlinePen(Chem::Atom& atom, const Pen& pen);

        /**
         * \brief Tells whether the Vis::AtomProperty::HIGHLIGHT_AREA_OUTLINE_PEN property of the atom \a atom is set.
         * \param atom The atom for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         * \since 1.2
         */
        CDPL_VIS_API bool hasHighlightAreaOutlinePen(const Chem::Atom& atom);

        /**
         * \brief Clears the value of the Vis::AtomProperty::HIGHLIGHT_AREA_OUTLINE_PEN property of the atom \a atom.
         * \param atom The atom for which to clear the property value.
         * \since 1.2
         */
        CDPL_VIS_API void clearHighlightAreaOutlinePen(Chem::Atom& atom);
    } // namespace Vis
} // namespace CDPL

#endif // CDPL_VIS_ATOMFUNCTIONS_HPP
