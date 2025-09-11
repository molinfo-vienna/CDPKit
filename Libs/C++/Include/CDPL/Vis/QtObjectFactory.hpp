/* 
 * QtObjectFactory.hpp 
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
 * \brief Definition of class CDPL::Vis::QtObjectFactory.
 */

#ifndef CDPL_VIS_QTOBJECTFACTORY_HPP
#define CDPL_VIS_QTOBJECTFACTORY_HPP

#include "CDPL/Vis/APIPrefix.hpp"


class QFont;
class QBrush;
class QPen;
class QColor;
class QPainterPath;


namespace CDPL
{

    namespace Vis
    {

        class Font;
        class Color;
        class Pen;
        class Brush;
        class Path2D;

        /**
         * \brief Provides methods for the creation of \c QFont, \c QColor, \c QPen and \c QBrush objects
         *        from Font, Color, Pen and Brush instances.
         *
         * For information about \c QFont, \c QColor, \c QPen and \c QBrush see [\ref QTDOC].
         */
        class CDPL_VIS_QT_API QtObjectFactory
        {

          public:
            /**
             * \brief Creates a \c QFont object that corresponds to the specified font.
             * \param font The font object.
             * \return A \c QFont object equivalent to \a font.
             */
            static QFont createQFont(const Font& font);

            /**
             * \brief Creates a \c QColor object that corresponds to the specified color.
             * \param color The color object.
             * \return A \c QColor object equivalent to \a color.
             */
            static QColor createQColor(const Color& color);

            /**
             * \brief Creates a \c QPen object that corresponds to the specified pen.
             * \param pen The pen object.
             * \return A \c QPen object equivalent to \a pen.
             */
            static QPen createQPen(const Pen& pen);

            /**
             * \brief Creates a \c QBrush object that corresponds to the specified brush.
             * \param brush The brush object.
             * \return A \c QBrush object equivalent to \a brush.
             */
            static QBrush createQBrush(const Brush& brush);

            /**
             * \brief Creates a \c QPainterPath object that corresponds to the specified path.
             * \param path The path object.
             * \param qt_path The QPainterPath object to create.
             * \return The argument \a qt_path.
             */
            static QPainterPath& createQPainterPath(const Path2D& path, QPainterPath& qt_path);

          private:
            QtObjectFactory() {}
        };
    } // namespace Vis
} // namespace CDPL

#endif // CDPL_VIS_QTOBJECTFACTORY_HPP
