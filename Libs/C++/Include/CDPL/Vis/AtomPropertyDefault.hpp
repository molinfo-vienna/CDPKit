/* 
 * AtomPropertyDefault.hpp 
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
 * \brief Definition of constants in namespace CDPL::Vis::AtomPropertyDefault.
 */

#ifndef CDPL_VIS_ATOMPROPERTYDEFAULT_HPP
#define CDPL_VIS_ATOMPROPERTYDEFAULT_HPP

#include <string>

#include "CDPL/Vis/APIPrefix.hpp"
#include "CDPL/Vis/Color.hpp"
#include "CDPL/Vis/Font.hpp"
#include "CDPL/Vis/Brush.hpp"
#include "CDPL/Vis/Pen.hpp"
#include "CDPL/Vis/SizeSpecification.hpp"


namespace CDPL
{

    namespace Vis
    {

        /**
         * \brief Provides default values for built-in Chem::Atom properties.
         */
        namespace AtomPropertyDefault
        {

            /**
             * \brief Default value of the Vis::AtomProperty::COLOR property.
             */
            extern CDPL_VIS_API const Color             COLOR;

            /**
             * \brief Default value of the Vis::AtomProperty::LABEL_FONT property.
             */
            extern CDPL_VIS_API const Font              LABEL_FONT;

            /**
             * \brief Default value of the Vis::AtomProperty::LABEL_SIZE property.
             */
            extern CDPL_VIS_API const SizeSpecification LABEL_SIZE;

            /**
             * \brief Default value of the Vis::AtomProperty::SECONDARY_LABEL_FONT property.
             */
            extern CDPL_VIS_API const Font              SECONDARY_LABEL_FONT;

            /**
             * \brief Default value of the Vis::AtomProperty::SECONDARY_LABEL_SIZE property.
             */
            extern CDPL_VIS_API const SizeSpecification SECONDARY_LABEL_SIZE;

            /**
             * \brief Default value of the Vis::AtomProperty::LABEL_MARGIN property.
             */
            extern CDPL_VIS_API const SizeSpecification LABEL_MARGIN;

            /**
             * \brief Default value of the Vis::AtomProperty::RADICAL_ELECTRON_DOT_SIZE property.
             */
            extern CDPL_VIS_API const SizeSpecification RADICAL_ELECTRON_DOT_SIZE;

            /**
             * \brief Default value of the Vis::AtomProperty::CONFIGURATION_LABEL_FONT property.
             * \since 1.1
             */
            extern CDPL_VIS_API const Font              CONFIGURATION_LABEL_FONT;

            /**
             * \brief Default value of the Vis::AtomProperty::CONFIGURATION_LABEL_SIZE property.
             * \since 1.1
             */
            extern CDPL_VIS_API const SizeSpecification CONFIGURATION_LABEL_SIZE;

            /**
             * \brief Default value of the Vis::AtomProperty::CONFIGURATION_LABEL_COLOR property.
             * \since 1.2
             */
            extern CDPL_VIS_API const Color             CONFIGURATION_LABEL_COLOR;

            /**
             * \brief Default value of the Vis::AtomProperty::CUSTOM_LABEL_FONT property.
             * \since 1.2
             */
            extern CDPL_VIS_API const Font              CUSTOM_LABEL_FONT;

            /**
             * \brief Default value of the Vis::AtomProperty::CUSTOM_LABEL_SIZE property.
             * \since 1.2
             */
            extern CDPL_VIS_API const SizeSpecification CUSTOM_LABEL_SIZE;

            /**
             * \brief Default value of the Vis::AtomProperty::CUSTOM_LABEL_COLOR property.
             * \since 1.2
             */
            extern CDPL_VIS_API const Color             CUSTOM_LABEL_COLOR;

            /**
             * \brief Default value of the Vis::AtomProperty::CUSTOM_LABEL property.
             * \since 1.2
             */
            extern CDPL_VIS_API const std::string       CUSTOM_LABEL;

            /**
             * \brief Default value of the Vis::AtomProperty::HIGHLIGHTED_FLAG property.
             * \since 1.2
             */
            extern CDPL_VIS_API const bool              HIGHLIGHTED_FLAG;

            /**
             * \brief Default value of the Vis::AtomProperty::HIGHLIGHT_AREA_BRUSH property.
             * \since 1.2
             */
            extern CDPL_VIS_API const Brush             HIGHLIGHT_AREA_BRUSH;

            /**
             * \brief Default value of the Vis::AtomProperty::HIGHLIGHT_AREA_OUTLINE_PEN property.
             * \since 1.2
             */
            extern CDPL_VIS_API const Pen               HIGHLIGHT_AREA_OUTLINE_PEN;
        } // namespace AtomPropertyDefault
    } // namespace Vis
} // namespace CDPL

#endif // CDPL_VIS_ATOMPROPERTYDEFAULT_HPP
