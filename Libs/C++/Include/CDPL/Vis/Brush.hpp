/* 
 * Brush.hpp 
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
 * \brief Definition of the class CDPL::Vis::Brush.
 */

#ifndef CDPL_VIS_BRUSH_HPP
#define CDPL_VIS_BRUSH_HPP

#include "CDPL/Vis/APIPrefix.hpp"
#include "CDPL/Vis/Color.hpp"


namespace CDPL 
{

    namespace Vis
    {

        /**
         * \brief Specifies the fill pattern and fill color of shapes.
         *
         * A brush has a style and a color attribute. The style defines the look of the fill pattern and the
         * color attribute specifies the color of the specified fill pattern. The style of a default constructed \c %Brush
         * object is Brush::NO_PATTERN, which tells the renderer not to fill drawn shapes.
         */
        class CDPL_VIS_API Brush
        {

        public:
            /**
             *\brief Defines constants for supported fill pattern styles.
             */
            enum Style
            {

                /**
                 * \brief Specifies that shapes should not be filled.
                 */
                NO_PATTERN,

                /**
                 * \brief Specifies a solid pattern without any transparent pixels.
                 */
                SOLID_PATTERN,

                /**
                 * \brief Specifies a pattern with \e 6.25% uniformly distributed transparent pixels.  
                 */
                DENSE1_PATTERN,

                /**
                 * \brief Specifies a pattern with \e 12.5% uniformly distributed transparent pixels.  
                 */
                DENSE2_PATTERN,

                /**
                 * \brief Specifies a pattern with \e 37.5% uniformly distributed transparent pixels.  
                 */
                DENSE3_PATTERN,

                /**
                 * \brief Specifies a pattern with \e 50.0% uniformly distributed transparent pixels.  
                 */
                DENSE4_PATTERN,

                /**
                 * \brief Specifies a pattern with \e 62.5% uniformly distributed transparent pixels.  
                 */
                DENSE5_PATTERN,

                /**
                 * \brief Specifies a pattern with \e 87.5% uniformly distributed transparent pixels.  
                 */
                DENSE6_PATTERN,

                /**
                 * \brief Specifies a pattern with \e 93.75% uniformly distributed transparent pixels.  
                 */
                DENSE7_PATTERN,
                
                /**
                 * \brief Specifies a pattern with equidistant horizontal lines. 
                 */
                H_PATTERN,
                
                /**
                 * \brief Specifies a pattern with equidistant vertical lines. 
                 */
                V_PATTERN,

                /**
                 * \brief Specifies a pattern with equidistant horizontal and vertical lines. 
                 */
                CROSS_PATTERN,

                /**
                 * \brief Specifies a pattern with equidistant diagonal lines from the upper right to the lower left corner.
                 */
                LEFT_DIAG_PATTERN,

                /**
                 * \brief Specifies a pattern with equidistant diagonal lines from the upper left to the lower right corner.
                 */
                RIGHT_DIAG_PATTERN,

                /**
                 * \brief Specifies a pattern with equidistant diagonal lines in both directions.
                 */
                DIAG_CROSS_PATTERN
            };

            /**
             * \brief Constructs a brush with fill pattern style Brush::NO_PATTERN and color Color::BLACK.
             */
            Brush();
            
            /**
             * \brief Constructs a brush with the specified fill pattern style and the color Color::BLACK.
             * \param style The style of the fill pattern.
             */
            Brush(Style style); 

            /**
             * \brief Constructs a brush with the specified fill pattern style and color.
             * \param color The fill pattern color.
             * \param style The fill pattern style .
             */
            Brush(const Color& color, Style style = SOLID_PATTERN); 

            /**
             * \brief Sets the fill pattern style.
             * \param style The the fill pattern style.
             */
            void setStyle(Style style); 

            /**
             * \brief Returns the fill pattern style.
             * \return The fill pattern style.
             */
            Style getStyle() const; 

            /**
             * \brief Sets the fill pattern color.
             * \param color The fill pattern color.
             */
            void setColor(const Color& color); 

            /**
             * \brief Returns the fill pattern color.
             * \return The fill pattern color.
             */
            const Color& getColor() const; 
    
            /**
             * \brief Equality comparison operator.
             * \param brush The other \c %Brush object to be compared with.
             * \return \c true if the style and color attributes compare equal, and \c false otherwise.
             */
            bool operator==(const Brush& brush) const;
        
            /**
             * \brief Inequality comparison operator.
             *
             * The result is equivalent to <tt>!(*this == brush)</tt>.
             *
             * \param brush The other \c %Brush object to be compared with.
             * \return \c true if either the style or the color attributes compare non-equal, and \c false otherwise.
             */
            bool operator!=(const Brush& brush) const;

        private:
            Style style;
            Color color;
        };
    }
}

#endif // CDPL_VIS_BRUSH_HPP
