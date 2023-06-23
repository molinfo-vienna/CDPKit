/* 
 * Color.hpp 
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
 * \brief Definition of the class CDPL::Vis::Color.
 */

#ifndef CDPL_VIS_COLOR_HPP
#define CDPL_VIS_COLOR_HPP

#include "CDPL/Vis/APIPrefix.hpp"


namespace CDPL 
{

    namespace Vis
    {

        /**
         * \brief Specifies a color in terms of its red, green and blue components and an alpha-channel
         *        for transparency.
         *
         * Each component of the RGBA quadruplet is represented by a double precision floating-point value
         * in the interval <em>[0, 1]</em>, where \e 0 corresponds to the lowest (zero) intensity
         * of a color component and the value \e 1 represents the highest intensity. Likewise, a
         * value of \e 1 for the alpha-channel corresponds to complete opaqueness and \e 0 represents
         * complete transparency. 
         */
        class CDPL_VIS_API Color
        {

        public:
            /**
             * \brief A preinitialized \c %Color instance for the color \e black.
             */
            static const Color BLACK;

            /**
             * \brief A preinitialized \c %Color instance for the color \e white.
             */
            static const Color WHITE;

            /**
             * \brief A preinitialized \c %Color instance for the color \e red.
             */
            static const Color RED;

            /**
             * \brief A preinitialized \c %Color instance for the color <em>dark red</em>.
             */
            static const Color DARK_RED;

            /**
             * \brief A preinitialized \c %Color instance for the color \e green.
             */
            static const Color GREEN;
            
            /**
             * \brief A preinitialized \c %Color instance for the color <em>dark green</em>.
             */
            static const Color DARK_GREEN;

            /**
             * \brief A preinitialized \c %Color instance for the color \e blue.
             */
            static const Color BLUE;

            /**
             * \brief A preinitialized \c %Color instance for the color <em>dark blue</em>.
             */
            static const Color DARK_BLUE;

            /**
             * \brief A preinitialized \c %Color instance for the color \e cyan.
             */
            static const Color CYAN;

            /**
             * \brief A preinitialized \c %Color instance for the color <em>dark cyan</em>.
             */
            static const Color DARK_CYAN;

            /**
             * \brief A preinitialized \c %Color instance for the color \e magenta.
             */
            static const Color MAGENTA;

            /**
             * \brief A preinitialized \c %Color instance for the color <em>dark magenta</em>.
             */
            static const Color DARK_MAGENTA;

            /**
             * \brief A preinitialized \c %Color instance for the color \e yellow.
             */
            static const Color YELLOW;

            /**
             * \brief A preinitialized \c %Color instance for the color <em>dark yellow</em>.
             */
            static const Color DARK_YELLOW;

            /**
             * \brief A preinitialized \c %Color instance for the color \e gray.
             */
            static const Color GRAY;

            /**
             * \brief A preinitialized \c %Color instance for the color <em>light gray</em>.
             */
            static const Color LIGHT_GRAY;

            /**
             * \brief A preinitialized \c %Color instance for the color <em>dark gray</em>.
             */
            static const Color DARK_GRAY;

            /**
             * \brief A preinitialized \c %Color instance for a totally transparent (alpha = 0) \e black.
             */
            static const Color TRANSPARENT;

            /**
             * \brief Constructs and initializes a \c %Color object with all RGBA components set to zero.
             */
            Color();
            
            /**
             * \brief Constructs and initializes a \c %Color object with the RGBA components set to 
             *        the specified values.
             *
             * Component values outside the interval <em>[0, 1]</em> are clamped to the nearest interval
              * bound, i.e. \e 0 if the value is negative and \e 1 if the value is greater than one.
             *
             * \param red The value of the red color component.
             * \param green The value of the green color component.
             * \param blue The value of the blue color component.
             * \param alpha The value of the alpha component.
             */
            Color(double red, double green, double blue, double alpha = 1.0);

            /**
             * \brief Sets the value of the red color component to \a red.
             *
             * If \a red is outside the interval <em>[0, 1]</em> the value is clamped to the nearest interval
             * bound, i.e. \e 0 if \a red is negative and \e 1 if \a red is greater than one.
             *
             * \param red The value of the red color component.
             */
            void setRed(double red);

            /**
             * \brief Returns the value of the red color component.
             * \return The value of the red color component.
             */
            double getRed() const;
        
            /**
             * \brief Sets the the value of green color component to \a green.
             *
             * If \a green is outside the interval <em>[0, 1]</em> the value is clamped to the nearest interval
             * bound, i.e. \e 0 if \a green is negative and \e 1 if \a green is greater than one.
             *
             * \param green The value of the green color component.
             */
            void setGreen(double green);

            /**
             * \brief Returns the value of the green color component.
             * \return The value of the green color component.
             */
            double getGreen() const;

            /**
             * \brief Sets the value of the blue color component to \a blue.
             *
             * If \a blue is outside the interval <em>[0, 1]</em> the value is clamped to the nearest interval
             * bound, i.e. \e 0 if \a blue is negative and \e 1 if \a blue is greater than one.
             *
             * \param blue The value of the blue color component.
             */
            void setBlue(double blue);

            /**
             * \brief Returns the value of the blue color component.
             * \return The value of the blue color component.
             */
            double getBlue() const;

            /**
             * \brief Sets the value of the alpha component to \a alpha.
             *
             * If \a alpha is outside the interval <em>[0, 1]</em> the value is clamped to the nearest interval
             * bound, i.e. \e 0 if \a alpha is negative and \e 1 if \a alpha is greater than one.
             *
             * \param alpha The value of the alpha component.
             */
            void setAlpha(double alpha);

            /**
             * \brief Returns the value of the alpha component.
             * \return The value of the alpha component.
             */
            double getAlpha() const;
        
            /**
             * \brief Sets the values of the RGBA components to specified values.
             *
             * Component values outside the interval <em>[0, 1]</em> are clamped to the nearest interval
             * bound, i.e. \e 0 if the value is negative and \e 1 if the value is greater than one.
             *
             * \param red The value of the red color component.
             * \param green The value of the green color component.
             * \param blue The value of the blue color component.
             * \param alpha The value of the alpha component.
             */
            void setRGBA(double red, double green, double blue, double alpha = 1.0);

            /**
             * \brief Equality comparison operator.
             * \param color The other \c %Color object to be compared with.
             * \return \c true if all pairs of the RGBA components compare equal, \c false otherwise.
             */
            bool operator==(const Color& color) const;

            /**
             * \brief Inequality comparison operator.
             *
             * The result is equivalent to <tt>!(*this == color)</tt>.
             *
             * \param color The other \c %Color object to be compared with.
             * \return \c true if at least one pair of the RGBA components compares non-equal, \c false otherwise.
             */
            bool operator!=(const Color& color) const;

        private:
            double red;
            double green;
            double blue;
            double alpha;
        };
    }
}

#endif // CDPL_VIS_COLOR_HPP
