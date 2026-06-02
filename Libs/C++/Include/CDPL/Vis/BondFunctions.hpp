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

        /**
         * \brief Returns the value of the Vis::BondProperty::COLOR property of the bond \a bond.
         * \param bond The bond for which to return the property value.
         * \return The value of the Vis::BondProperty::COLOR property.
         */
        CDPL_VIS_API const Color& getColor(const Chem::Bond& bond);

        /**
         * \brief Sets the value of the Vis::BondProperty::COLOR property of the bond \a bond to \a color.
         * \param bond The bond for which to set the property value.
         * \param color The new value of the Vis::BondProperty::COLOR property.
         */
        CDPL_VIS_API void setColor(Chem::Bond& bond, const Color& color);

        /**
         * \brief Tells whether the Vis::BondProperty::COLOR property of the bond \a bond is set.
         * \param bond The bond for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasColor(const Chem::Bond& bond);

        /**
         * \brief Clears the value of the Vis::BondProperty::COLOR property of the bond \a bond.
         * \param bond The bond for which to clear the property value.
         */
        CDPL_VIS_API void clearColor(Chem::Bond& bond);


        /**
         * \brief Returns the value of the Vis::BondProperty::LINE_WIDTH property of the bond \a bond.
         * \param bond The bond for which to return the property value.
         * \return The value of the Vis::BondProperty::LINE_WIDTH property.
         */
        CDPL_VIS_API const SizeSpecification& getLineWidth(const Chem::Bond& bond);

        /**
         * \brief Sets the value of the Vis::BondProperty::LINE_WIDTH property of the bond \a bond to \a width.
         * \param bond The bond for which to set the property value.
         * \param width The new value of the Vis::BondProperty::LINE_WIDTH property.
         */
        CDPL_VIS_API void setLineWidth(Chem::Bond& bond, const SizeSpecification& width);

        /**
         * \brief Tells whether the Vis::BondProperty::LINE_WIDTH property of the bond \a bond is set.
         * \param bond The bond for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasLineWidth(const Chem::Bond& bond);

        /**
         * \brief Clears the value of the Vis::BondProperty::LINE_WIDTH property of the bond \a bond.
         * \param bond The bond for which to clear the property value.
         */
        CDPL_VIS_API void clearLineWidth(Chem::Bond& bond);


        /**
         * \brief Returns the value of the Vis::BondProperty::LINE_SPACING property of the bond \a bond.
         * \param bond The bond for which to return the property value.
         * \return The value of the Vis::BondProperty::LINE_SPACING property.
         */
        CDPL_VIS_API const SizeSpecification& getLineSpacing(const Chem::Bond& bond);

        /**
         * \brief Sets the value of the Vis::BondProperty::LINE_SPACING property of the bond \a bond to \a spacing.
         * \param bond The bond for which to set the property value.
         * \param spacing The new value of the Vis::BondProperty::LINE_SPACING property.
         */
        CDPL_VIS_API void setLineSpacing(Chem::Bond& bond, const SizeSpecification& spacing);

        /**
         * \brief Tells whether the Vis::BondProperty::LINE_SPACING property of the bond \a bond is set.
         * \param bond The bond for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasLineSpacing(const Chem::Bond& bond);

        /**
         * \brief Clears the value of the Vis::BondProperty::LINE_SPACING property of the bond \a bond.
         * \param bond The bond for which to clear the property value.
         */
        CDPL_VIS_API void clearLineSpacing(Chem::Bond& bond);


        /**
         * \brief Returns the value of the Vis::BondProperty::STEREO_BOND_WEDGE_WIDTH property of the bond \a bond.
         * \param bond The bond for which to return the property value.
         * \return The value of the Vis::BondProperty::STEREO_BOND_WEDGE_WIDTH property.
         */
        CDPL_VIS_API const SizeSpecification& getStereoBondWedgeWidth(const Chem::Bond& bond);

        /**
         * \brief Sets the value of the Vis::BondProperty::STEREO_BOND_WEDGE_WIDTH property of the bond \a bond to \a width.
         * \param bond The bond for which to set the property value.
         * \param width The new value of the Vis::BondProperty::STEREO_BOND_WEDGE_WIDTH property.
         */
        CDPL_VIS_API void setStereoBondWedgeWidth(Chem::Bond& bond, const SizeSpecification& width);

        /**
         * \brief Tells whether the Vis::BondProperty::STEREO_BOND_WEDGE_WIDTH property of the bond \a bond is set.
         * \param bond The bond for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasStereoBondWedgeWidth(const Chem::Bond& bond);

        /**
         * \brief Clears the value of the Vis::BondProperty::STEREO_BOND_WEDGE_WIDTH property of the bond \a bond.
         * \param bond The bond for which to clear the property value.
         */
        CDPL_VIS_API void clearStereoBondWedgeWidth(Chem::Bond& bond);


        /**
         * \brief Returns the value of the Vis::BondProperty::STEREO_BOND_HASH_SPACING property of the bond \a bond.
         * \param bond The bond for which to return the property value.
         * \return The value of the Vis::BondProperty::STEREO_BOND_HASH_SPACING property.
         */
        CDPL_VIS_API const SizeSpecification& getStereoBondHashSpacing(const Chem::Bond& bond);

        /**
         * \brief Sets the value of the Vis::BondProperty::STEREO_BOND_HASH_SPACING property of the bond \a bond to \a spacing.
         * \param bond The bond for which to set the property value.
         * \param spacing The new value of the Vis::BondProperty::STEREO_BOND_HASH_SPACING property.
         */
        CDPL_VIS_API void setStereoBondHashSpacing(Chem::Bond& bond, const SizeSpecification& spacing);

        /**
         * \brief Tells whether the Vis::BondProperty::STEREO_BOND_HASH_SPACING property of the bond \a bond is set.
         * \param bond The bond for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasStereoBondHashSpacing(const Chem::Bond& bond);

        /**
         * \brief Clears the value of the Vis::BondProperty::STEREO_BOND_HASH_SPACING property of the bond \a bond.
         * \param bond The bond for which to clear the property value.
         */
        CDPL_VIS_API void clearStereoBondHashSpacing(Chem::Bond& bond);


        /**
         * \brief Returns the value of the Vis::BondProperty::REACTION_CENTER_LINE_LENGTH property of the bond \a bond.
         * \param bond The bond for which to return the property value.
         * \return The value of the Vis::BondProperty::REACTION_CENTER_LINE_LENGTH property.
         */
        CDPL_VIS_API const SizeSpecification& getReactionCenterLineLength(const Chem::Bond& bond);

        /**
         * \brief Sets the value of the Vis::BondProperty::REACTION_CENTER_LINE_LENGTH property of the bond \a bond to \a length.
         * \param bond The bond for which to set the property value.
         * \param length The new value of the Vis::BondProperty::REACTION_CENTER_LINE_LENGTH property.
         */
        CDPL_VIS_API void setReactionCenterLineLength(Chem::Bond& bond, const SizeSpecification& length);

        /**
         * \brief Tells whether the Vis::BondProperty::REACTION_CENTER_LINE_LENGTH property of the bond \a bond is set.
         * \param bond The bond for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasReactionCenterLineLength(const Chem::Bond& bond);

        /**
         * \brief Clears the value of the Vis::BondProperty::REACTION_CENTER_LINE_LENGTH property of the bond \a bond.
         * \param bond The bond for which to clear the property value.
         */
        CDPL_VIS_API void clearReactionCenterLineLength(Chem::Bond& bond);


        /**
         * \brief Returns the value of the Vis::BondProperty::REACTION_CENTER_LINE_SPACING property of the bond \a bond.
         * \param bond The bond for which to return the property value.
         * \return The value of the Vis::BondProperty::REACTION_CENTER_LINE_SPACING property.
         */
        CDPL_VIS_API const SizeSpecification& getReactionCenterLineSpacing(const Chem::Bond& bond);

        /**
         * \brief Sets the value of the Vis::BondProperty::REACTION_CENTER_LINE_SPACING property of the bond \a bond to \a spacing.
         * \param bond The bond for which to set the property value.
         * \param spacing The new value of the Vis::BondProperty::REACTION_CENTER_LINE_SPACING property.
         */
        CDPL_VIS_API void setReactionCenterLineSpacing(Chem::Bond& bond, const SizeSpecification& spacing);

        /**
         * \brief Tells whether the Vis::BondProperty::REACTION_CENTER_LINE_SPACING property of the bond \a bond is set.
         * \param bond The bond for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasReactionCenterLineSpacing(const Chem::Bond& bond);

        /**
         * \brief Clears the value of the Vis::BondProperty::REACTION_CENTER_LINE_SPACING property of the bond \a bond.
         * \param bond The bond for which to clear the property value.
         */
        CDPL_VIS_API void clearReactionCenterLineSpacing(Chem::Bond& bond);


        /**
         * \brief Returns the value of the Vis::BondProperty::DOUBLE_BOND_TRIM_LENGTH property of the bond \a bond.
         * \param bond The bond for which to return the property value.
         * \return The value of the Vis::BondProperty::DOUBLE_BOND_TRIM_LENGTH property.
         */
        CDPL_VIS_API const SizeSpecification& getDoubleBondTrimLength(const Chem::Bond& bond);

        /**
         * \brief Sets the value of the Vis::BondProperty::DOUBLE_BOND_TRIM_LENGTH property of the bond \a bond to \a length.
         * \param bond The bond for which to set the property value.
         * \param length The new value of the Vis::BondProperty::DOUBLE_BOND_TRIM_LENGTH property.
         */
        CDPL_VIS_API void setDoubleBondTrimLength(Chem::Bond& bond, const SizeSpecification& length);

        /**
         * \brief Tells whether the Vis::BondProperty::DOUBLE_BOND_TRIM_LENGTH property of the bond \a bond is set.
         * \param bond The bond for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasDoubleBondTrimLength(const Chem::Bond& bond);

        /**
         * \brief Clears the value of the Vis::BondProperty::DOUBLE_BOND_TRIM_LENGTH property of the bond \a bond.
         * \param bond The bond for which to clear the property value.
         */
        CDPL_VIS_API void clearDoubleBondTrimLength(Chem::Bond& bond);


        /**
         * \brief Returns the value of the Vis::BondProperty::TRIPLE_BOND_TRIM_LENGTH property of the bond \a bond.
         * \param bond The bond for which to return the property value.
         * \return The value of the Vis::BondProperty::TRIPLE_BOND_TRIM_LENGTH property.
         */
        CDPL_VIS_API const SizeSpecification& getTripleBondTrimLength(const Chem::Bond& bond);

        /**
         * \brief Sets the value of the Vis::BondProperty::TRIPLE_BOND_TRIM_LENGTH property of the bond \a bond to \a length.
         * \param bond The bond for which to set the property value.
         * \param length The new value of the Vis::BondProperty::TRIPLE_BOND_TRIM_LENGTH property.
         */
        CDPL_VIS_API void setTripleBondTrimLength(Chem::Bond& bond, const SizeSpecification& length);

        /**
         * \brief Tells whether the Vis::BondProperty::TRIPLE_BOND_TRIM_LENGTH property of the bond \a bond is set.
         * \param bond The bond for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasTripleBondTrimLength(const Chem::Bond& bond);

        /**
         * \brief Clears the value of the Vis::BondProperty::TRIPLE_BOND_TRIM_LENGTH property of the bond \a bond.
         * \param bond The bond for which to clear the property value.
         */
        CDPL_VIS_API void clearTripleBondTrimLength(Chem::Bond& bond);


        /**
         * \brief Returns the value of the Vis::BondProperty::LABEL_FONT property of the bond \a bond.
         * \param bond The bond for which to return the property value.
         * \return The value of the Vis::BondProperty::LABEL_FONT property.
         */
        CDPL_VIS_API const Font& getLabelFont(const Chem::Bond& bond);

        /**
         * \brief Sets the value of the Vis::BondProperty::LABEL_FONT property of the bond \a bond to \a font.
         * \param bond The bond for which to set the property value.
         * \param font The new value of the Vis::BondProperty::LABEL_FONT property.
         */
        CDPL_VIS_API void setLabelFont(Chem::Bond& bond, const Font& font);

        /**
         * \brief Tells whether the Vis::BondProperty::LABEL_FONT property of the bond \a bond is set.
         * \param bond The bond for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasLabelFont(const Chem::Bond& bond);

        /**
         * \brief Clears the value of the Vis::BondProperty::LABEL_FONT property of the bond \a bond.
         * \param bond The bond for which to clear the property value.
         */
        CDPL_VIS_API void clearLabelFont(Chem::Bond& bond);


        /**
         * \brief Returns the value of the Vis::BondProperty::LABEL_SIZE property of the bond \a bond.
         * \param bond The bond for which to return the property value.
         * \return The value of the Vis::BondProperty::LABEL_SIZE property.
         */
        CDPL_VIS_API const SizeSpecification& getLabelSize(const Chem::Bond& bond);

        /**
         * \brief Sets the value of the Vis::BondProperty::LABEL_SIZE property of the bond \a bond to \a size.
         * \param bond The bond for which to set the property value.
         * \param size The new value of the Vis::BondProperty::LABEL_SIZE property.
         */
        CDPL_VIS_API void setLabelSize(Chem::Bond& bond, const SizeSpecification& size);

        /**
         * \brief Tells whether the Vis::BondProperty::LABEL_SIZE property of the bond \a bond is set.
         * \param bond The bond for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasLabelSize(const Chem::Bond& bond);

        /**
         * \brief Clears the value of the Vis::BondProperty::LABEL_SIZE property of the bond \a bond.
         * \param bond The bond for which to clear the property value.
         */
        CDPL_VIS_API void clearLabelSize(Chem::Bond& bond);


        /**
         * \brief Returns the value of the Vis::BondProperty::LABEL_MARGIN property of the bond \a bond.
         * \param bond The bond for which to return the property value.
         * \return The value of the Vis::BondProperty::LABEL_MARGIN property.
         */
        CDPL_VIS_API const SizeSpecification& getLabelMargin(const Chem::Bond& bond);

        /**
         * \brief Sets the value of the Vis::BondProperty::LABEL_MARGIN property of the bond \a bond to \a margin.
         * \param bond The bond for which to set the property value.
         * \param margin The new value of the Vis::BondProperty::LABEL_MARGIN property.
         */
        CDPL_VIS_API void setLabelMargin(Chem::Bond& bond, const SizeSpecification& margin);

        /**
         * \brief Tells whether the Vis::BondProperty::LABEL_MARGIN property of the bond \a bond is set.
         * \param bond The bond for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_VIS_API bool hasLabelMargin(const Chem::Bond& bond);

        /**
         * \brief Clears the value of the Vis::BondProperty::LABEL_MARGIN property of the bond \a bond.
         * \param bond The bond for which to clear the property value.
         */
        CDPL_VIS_API void clearLabelMargin(Chem::Bond& bond);

        /**
         * \brief Returns the value of the Vis::BondProperty::CONFIGURATION_LABEL_FONT property of the bond \a bond.
         * \param bond The bond for which to return the property value.
         * \return The value of the Vis::BondProperty::CONFIGURATION_LABEL_FONT property.
         * \since 1.1
         */
        CDPL_VIS_API const Font& getConfigurationLabelFont(const Chem::Bond& bond);

        /**
         * \brief Sets the value of the Vis::BondProperty::CONFIGURATION_LABEL_FONT property of the bond \a bond to \a font.
         * \param bond The bond for which to set the property value.
         * \param font The new value of the Vis::BondProperty::CONFIGURATION_LABEL_FONT property.
         * \since 1.1
         */
        CDPL_VIS_API void setConfigurationLabelFont(Chem::Bond& bond, const Font& font);

        /**
         * \brief Tells whether the Vis::BondProperty::CONFIGURATION_LABEL_FONT property of the bond \a bond is set.
         * \param bond The bond for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         * \since 1.1
         */
        CDPL_VIS_API bool hasConfigurationLabelFont(const Chem::Bond& bond);

        /**
         * \brief Clears the value of the Vis::BondProperty::CONFIGURATION_LABEL_FONT property of the bond \a bond.
         * \param bond The bond for which to clear the property value.
         * \since 1.1
         */
        CDPL_VIS_API void clearConfigurationLabelFont(Chem::Bond& bond);

        /**
         * \brief Returns the value of the Vis::BondProperty::CONFIGURATION_LABEL_SIZE property of the bond \a bond.
         * \param bond The bond for which to return the property value.
         * \return The value of the Vis::BondProperty::CONFIGURATION_LABEL_SIZE property.
         * \since 1.1
         */
        CDPL_VIS_API const SizeSpecification& getConfigurationLabelSize(const Chem::Bond& bond);

        /**
         * \brief Sets the value of the Vis::BondProperty::CONFIGURATION_LABEL_SIZE property of the bond \a bond to \a size.
         * \param bond The bond for which to set the property value.
         * \param size The new value of the Vis::BondProperty::CONFIGURATION_LABEL_SIZE property.
         * \since 1.1
         */
        CDPL_VIS_API void setConfigurationLabelSize(Chem::Bond& bond, const SizeSpecification& size);

        /**
         * \brief Tells whether the Vis::BondProperty::CONFIGURATION_LABEL_SIZE property of the bond \a bond is set.
         * \param bond The bond for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         * \since 1.1
         */
        CDPL_VIS_API bool hasConfigurationLabelSize(const Chem::Bond& bond);

        /**
         * \brief Clears the value of the Vis::BondProperty::CONFIGURATION_LABEL_SIZE property of the bond \a bond.
         * \param bond The bond for which to clear the property value.
         * \since 1.1
         */
        CDPL_VIS_API void clearConfigurationLabelSize(Chem::Bond& bond);

        /**
         * \brief Returns the value of the Vis::BondProperty::CONFIGURATION_LABEL_COLOR property of the bond \a bond.
         * \param bond The bond for which to return the property value.
         * \return The value of the Vis::BondProperty::CONFIGURATION_LABEL_COLOR property.
         * \since 1.2
         */
        CDPL_VIS_API const Color& getConfigurationLabelColor(const Chem::Bond& bond);

        /**
         * \brief Sets the value of the Vis::BondProperty::CONFIGURATION_LABEL_COLOR property of the bond \a bond to \a color.
         * \param bond The bond for which to set the property value.
         * \param color The new value of the Vis::BondProperty::CONFIGURATION_LABEL_COLOR property.
         * \since 1.2
         */
        CDPL_VIS_API void setConfigurationLabelColor(Chem::Bond& bond, const Color& color);

        /**
         * \brief Tells whether the Vis::BondProperty::CONFIGURATION_LABEL_COLOR property of the bond \a bond is set.
         * \param bond The bond for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         * \since 1.2
         */
        CDPL_VIS_API bool hasConfigurationLabelColor(const Chem::Bond& bond);

        /**
         * \brief Clears the value of the Vis::BondProperty::CONFIGURATION_LABEL_COLOR property of the bond \a bond.
         * \param bond The bond for which to clear the property value.
         * \since 1.2
         */
        CDPL_VIS_API void clearConfigurationLabelColor(Chem::Bond& bond);

        /**
         * \brief Returns the value of the Vis::BondProperty::CUSTOM_LABEL_FONT property of the bond \a bond.
         * \param bond The bond for which to return the property value.
         * \return The value of the Vis::BondProperty::CUSTOM_LABEL_FONT property.
         * \since 1.2
         */
        CDPL_VIS_API const Font& getCustomLabelFont(const Chem::Bond& bond);

        /**
         * \brief Sets the value of the Vis::BondProperty::CUSTOM_LABEL_FONT property of the bond \a bond to \a font.
         * \param bond The bond for which to set the property value.
         * \param font The new value of the Vis::BondProperty::CUSTOM_LABEL_FONT property.
         * \since 1.2
         */
        CDPL_VIS_API void setCustomLabelFont(Chem::Bond& bond, const Font& font);

        /**
         * \brief Tells whether the Vis::BondProperty::CUSTOM_LABEL_FONT property of the bond \a bond is set.
         * \param bond The bond for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         * \since 1.2
         */
        CDPL_VIS_API bool hasCustomLabelFont(const Chem::Bond& bond);

        /**
         * \brief Clears the value of the Vis::BondProperty::CUSTOM_LABEL_FONT property of the bond \a bond.
         * \param bond The bond for which to clear the property value.
         * \since 1.2
         */
        CDPL_VIS_API void clearCustomLabelFont(Chem::Bond& bond);

        /**
         * \brief Returns the value of the Vis::BondProperty::CUSTOM_LABEL_SIZE property of the bond \a bond.
         * \param bond The bond for which to return the property value.
         * \return The value of the Vis::BondProperty::CUSTOM_LABEL_SIZE property.
         * \since 1.2
         */
        CDPL_VIS_API const SizeSpecification& getCustomLabelSize(const Chem::Bond& bond);

        /**
         * \brief Sets the value of the Vis::BondProperty::CUSTOM_LABEL_SIZE property of the bond \a bond to \a size.
         * \param bond The bond for which to set the property value.
         * \param size The new value of the Vis::BondProperty::CUSTOM_LABEL_SIZE property.
         * \since 1.2
         */
        CDPL_VIS_API void setCustomLabelSize(Chem::Bond& bond, const SizeSpecification& size);

        /**
         * \brief Tells whether the Vis::BondProperty::CUSTOM_LABEL_SIZE property of the bond \a bond is set.
         * \param bond The bond for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         * \since 1.2
         */
        CDPL_VIS_API bool hasCustomLabelSize(const Chem::Bond& bond);

        /**
         * \brief Clears the value of the Vis::BondProperty::CUSTOM_LABEL_SIZE property of the bond \a bond.
         * \param bond The bond for which to clear the property value.
         * \since 1.2
         */
        CDPL_VIS_API void clearCustomLabelSize(Chem::Bond& bond);

        /**
         * \brief Returns the value of the Vis::BondProperty::CUSTOM_LABEL_COLOR property of the bond \a bond.
         * \param bond The bond for which to return the property value.
         * \return The value of the Vis::BondProperty::CUSTOM_LABEL_COLOR property.
         * \since 1.2
         */
        CDPL_VIS_API const Color& getCustomLabelColor(const Chem::Bond& bond);

        /**
         * \brief Sets the value of the Vis::BondProperty::CUSTOM_LABEL_COLOR property of the bond \a bond to \a color.
         * \param bond The bond for which to set the property value.
         * \param color The new value of the Vis::BondProperty::CUSTOM_LABEL_COLOR property.
         * \since 1.2
         */
        CDPL_VIS_API void setCustomLabelColor(Chem::Bond& bond, const Color& color);

        /**
         * \brief Tells whether the Vis::BondProperty::CUSTOM_LABEL_COLOR property of the bond \a bond is set.
         * \param bond The bond for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         * \since 1.2
         */
        CDPL_VIS_API bool hasCustomLabelColor(const Chem::Bond& bond);

        /**
         * \brief Clears the value of the Vis::BondProperty::CUSTOM_LABEL_COLOR property of the bond \a bond.
         * \param bond The bond for which to clear the property value.
         * \since 1.2
         */
        CDPL_VIS_API void clearCustomLabelColor(Chem::Bond& bond);

        /**
         * \brief Returns the value of the Vis::BondProperty::CUSTOM_LABEL property of the bond \a bond.
         * \param bond The bond for which to return the property value.
         * \return The value of the Vis::BondProperty::CUSTOM_LABEL property.
         * \since 1.2
         */
        CDPL_VIS_API const std::string& getCustomLabel(const Chem::Bond& bond);

        /**
         * \brief Sets the value of the Vis::BondProperty::CUSTOM_LABEL property of the bond \a bond to \a text.
         * \param bond The bond for which to set the property value.
         * \param text The new value of the Vis::BondProperty::CUSTOM_LABEL property.
         * \since 1.2
         */
        CDPL_VIS_API void setCustomLabel(Chem::Bond& bond, const std::string& text);

        /**
         * \brief Tells whether the Vis::BondProperty::CUSTOM_LABEL property of the bond \a bond is set.
         * \param bond The bond for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         * \since 1.2
         */
        CDPL_VIS_API bool hasCustomLabel(const Chem::Bond& bond);

        /**
         * \brief Clears the value of the Vis::BondProperty::CUSTOM_LABEL property of the bond \a bond.
         * \param bond The bond for which to clear the property value.
         * \since 1.2
         */
        CDPL_VIS_API void clearCustomLabel(Chem::Bond& bond);

        /**
         * \brief Returns the value of the Vis::BondProperty::HIGHLIGHTED_FLAG property of the bond \a bond.
         * \param bond The bond for which to return the property value.
         * \return The value of the Vis::BondProperty::HIGHLIGHTED_FLAG property.
         * \since 1.2
         */
        CDPL_VIS_API bool getHighlightedFlag(const Chem::Bond& bond);

        /**
         * \brief Sets the value of the Vis::BondProperty::HIGHLIGHTED_FLAG property of the bond \a bond to \a highlighted.
         * \param bond The bond for which to set the property value.
         * \param highlighted The new value of the Vis::BondProperty::HIGHLIGHTED_FLAG property.
         * \since 1.2
         */
        CDPL_VIS_API void setHighlightedFlag(Chem::Bond& bond, bool highlighted);

        /**
         * \brief Tells whether the Vis::BondProperty::HIGHLIGHTED_FLAG property of the bond \a bond is set.
         * \param bond The bond for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         * \since 1.2
         */
        CDPL_VIS_API bool hasHighlightedFlag(const Chem::Bond& bond);

        /**
         * \brief Clears the value of the Vis::BondProperty::HIGHLIGHTED_FLAG property of the bond \a bond.
         * \param bond The bond for which to clear the property value.
         * \since 1.2
         */
        CDPL_VIS_API void clearHighlightedFlag(Chem::Bond& bond);

        /**
         * \brief Returns the value of the Vis::BondProperty::HIGHLIGHT_AREA_BRUSH property of the bond \a bond.
         * \param bond The bond for which to return the property value.
         * \return The value of the Vis::BondProperty::HIGHLIGHT_AREA_BRUSH property.
         * \since 1.2
         */
        CDPL_VIS_API const Brush& getHighlightAreaBrush(const Chem::Bond& bond);

        /**
         * \brief Sets the value of the Vis::BondProperty::HIGHLIGHT_AREA_BRUSH property of the bond \a bond to \a brush.
         * \param bond The bond for which to set the property value.
         * \param brush The new value of the Vis::BondProperty::HIGHLIGHT_AREA_BRUSH property.
         * \since 1.2
         */
        CDPL_VIS_API void setHighlightAreaBrush(Chem::Bond& bond, const Brush& brush);

        /**
         * \brief Tells whether the Vis::BondProperty::HIGHLIGHT_AREA_BRUSH property of the bond \a bond is set.
         * \param bond The bond for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         * \since 1.2
         */
        CDPL_VIS_API bool hasHighlightAreaBrush(const Chem::Bond& bond);

        /**
         * \brief Clears the value of the Vis::BondProperty::HIGHLIGHT_AREA_BRUSH property of the bond \a bond.
         * \param bond The bond for which to clear the property value.
         * \since 1.2
         */
        CDPL_VIS_API void clearHighlightAreaBrush(Chem::Bond& bond);

        /**
         * \brief Returns the value of the Vis::BondProperty::HIGHLIGHT_AREA_OUTLINE_PEN property of the bond \a bond.
         * \param bond The bond for which to return the property value.
         * \return The value of the Vis::BondProperty::HIGHLIGHT_AREA_OUTLINE_PEN property.
         * \since 1.2
         */
        CDPL_VIS_API const Pen& getHighlightAreaOutlinePen(const Chem::Bond& bond);

        /**
         * \brief Sets the value of the Vis::BondProperty::HIGHLIGHT_AREA_OUTLINE_PEN property of the bond \a bond to \a pen.
         * \param bond The bond for which to set the property value.
         * \param pen The new value of the Vis::BondProperty::HIGHLIGHT_AREA_OUTLINE_PEN property.
         * \since 1.2
         */
        CDPL_VIS_API void setHighlightAreaOutlinePen(Chem::Bond& bond, const Pen& pen);

        /**
         * \brief Tells whether the Vis::BondProperty::HIGHLIGHT_AREA_OUTLINE_PEN property of the bond \a bond is set.
         * \param bond The bond for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         * \since 1.2
         */
        CDPL_VIS_API bool hasHighlightAreaOutlinePen(const Chem::Bond& bond);

        /**
         * \brief Clears the value of the Vis::BondProperty::HIGHLIGHT_AREA_OUTLINE_PEN property of the bond \a bond.
         * \param bond The bond for which to clear the property value.
         * \since 1.2
         */
        CDPL_VIS_API void clearHighlightAreaOutlinePen(Chem::Bond& bond);

    } // namespace Vis
} // namespace CDPL

#endif // CDPL_VIS_BONDFUNCTIONS_HPP
