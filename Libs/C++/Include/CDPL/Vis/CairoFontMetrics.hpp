/* 
 * CairoFontMetrics.hpp 
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
 * \brief Definition of class CDPL::Vis::CairoFontMetrics.
 */

#ifndef CDPL_VIS_CAIROFONTMETRICS_HPP
#define CDPL_VIS_CAIROFONTMETRICS_HPP

#include <memory>

#include "CDPL/Vis/APIPrefix.hpp"
#include "CDPL/Vis/FontMetrics.hpp"
#include "CDPL/Vis/CairoPointer.hpp"


typedef struct _cairo _cairo_t;


namespace CDPL
{

    namespace Vis
    {

        /**
         * \brief Implements the FontMetrics interface for the \e Cairo rendering backend.
         *
         * For more information about the <em>Cairo 2D Graphics Library</em> see [\ref CAIRO].
         */
        class CDPL_VIS_API CairoFontMetrics : public FontMetrics
        {

          public:
            /**
             * \brief Constructs a font metrics object that operates on the \e Cairo drawing context specified by
             *        \a cairo_ctxt.
             * \param cairo_ctxt The \e Cairo drawing context.
             * \throw Base::NullPointerException if \a cairo_ctxt is \e null.
             */
            CairoFontMetrics(const CairoPointer<cairo_t>& cairo_ctxt);

            CairoFontMetrics(const CairoFontMetrics&) = delete;
            
            /**
             * \brief Destructor.
             */
            ~CairoFontMetrics();

            CairoFontMetrics& operator=(const CairoFontMetrics&) = delete;

            /**
             * \brief Specifies the font to use for the calculation of text metrics.
             * \param font The font used for the calculation of text metrics.
             */
            void setFont(const Font& font);

            /**
             * \brief Returns the ascent of the current font.
             * \return The ascent of the current font.
             */
            double getAscent() const;

            /**
             * \brief Returns the descent of the current font.
             * \return The descent of the current font.
             */
            double getDescent() const;

            /**
             * \brief Returns the height of the current font.
             * \return The height of the current font.
             */
            double getHeight() const;

            /**
             * \brief Returns the leading of the current font.
             * \return The leading of the current font.
             */
            double getLeading() const;

            /**
             * \brief Returns the total advance width of the rendered string \a str in the current font.
             * \param str The string for which to retrieve the total advance width.
             * \return The total advance width of \a str.
             */
            double getWidth(const std::string& str) const;

            /**
             * \brief Returns the advance width of the rendered character \a ch in the current font.
             * \param ch The character for which to retrieve the advance width.
             * \return The advance width of \a ch.
             */
            double getWidth(char ch) const;

            /**
             * \brief Computes the tight bounding rectangle of the rendered string \a str in the current font.
             * \param str The string for which to compute the bounding rectangle.
             * \param bounds The Rectangle2D instance receiving the result.
             */
            void getBounds(const std::string& str, Rectangle2D& bounds) const;

            /**
             * \brief Computes the tight bounding rectangle of the rendered character \a ch in the current font.
             * \param ch The character for which to compute the bounding rectangle.
             * \param bounds The Rectangle2D instance receiving the result.
             */
            void getBounds(char ch, Rectangle2D& bounds) const;

          private:
            struct CairoExtents;

            CairoPointer<cairo_t>       cairoContext;
            std::unique_ptr<CairoExtents> cairoExtents;
        };
    } // namespace Vis
} // namespace CDPL

#endif // CDPL_VIS_CAIROFONTMETRICS_HPP
