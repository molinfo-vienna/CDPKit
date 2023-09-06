/* 
 * QtFontMetrics.hpp 
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
 * \brief Definition of the class CDPL::Vis::QtFontMetrics.
 */

#ifndef CDPL_VIS_QTFONTMETRICS_HPP
#define CDPL_VIS_QTFONTMETRICS_HPP

#include <memory>

#include "CDPL/Vis/APIPrefix.hpp"
#include "CDPL/Vis/FontMetrics.hpp"


class QFontMetricsF;
class QPaintDevice;


namespace CDPL
{

    namespace Vis
    {

        /**
         * \brief Implements the FontMetrics interface for the \e Qt rendering backend.
         *
         * \c %QtFontMetrics is implemented by wrapping a corresponding \c QFontMetrics instance created for the
         * font specified by setFont(). For more information about \c QFontMetrics and the <em>Qt Toolkit</em> see
         * [\ref QTDOC].
         */
        class CDPL_VIS_API QtFontMetrics : public FontMetrics
        {

          public:
            /**
             * \brief Constructs a font metrics object for \e Qt's default font and the given paint device.
             * \param paint_dev A pointer to the \e Qt paint device, or \e null if unspecified.
             */
            QtFontMetrics(QPaintDevice* paint_dev = 0);

            /**
             * \brief Destructor.
             */
            ~QtFontMetrics();

            void setFont(const Font& font);

            double getAscent() const;
            double getDescent() const;
            double getHeight() const;
            double getLeading() const;

            double getWidth(const std::string& str) const;
            double getWidth(char ch) const;

            void getBounds(const std::string& str, Rectangle2D& bounds) const;
            void getBounds(char ch, Rectangle2D& bounds) const;

          private:
            QtFontMetrics(const QtFontMetrics&);

            QtFontMetrics& operator=(const QtFontMetrics&);

            QPaintDevice*                qPaintDevice;
            std::unique_ptr<QFontMetricsF> qFontMetrics;
        };
    } // namespace Vis
} // namespace CDPL

#endif // CDPL_VIS_QTFONTMETRICS_HPP
