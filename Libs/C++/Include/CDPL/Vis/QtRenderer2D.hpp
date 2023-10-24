/* 
 * QtRenderer2D.hpp 
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
 * \brief Definition of the class CDPL::Vis::QtRenderer2D.
 */

#ifndef CDPL_VIS_QTRENDERER2D_HPP
#define CDPL_VIS_QTRENDERER2D_HPP

#include <memory>

#include "CDPL/Vis/APIPrefix.hpp"
#include "CDPL/Vis/Renderer2D.hpp"


class QPainter;
class QPolygonF;
class QPainterPath;


namespace CDPL
{

    namespace Vis
    {

        /**
         * \brief Implements the Renderer2D interface on top of the <em>Qt Toolkit</em>.
         *
         * \c %QtRenderer2D is implemented by forwarding the drawing operations to a provided \c QPainter
         * instance which has been created for the desired output device (screen, printer, off-screen image, ...). 
         * For more information about \c QPainter and the <em>Qt Toolkit</em> see [\ref QTDOC].
         */
        class CDPL_VIS_QT_API QtRenderer2D : public Renderer2D
        {

          public:
            /**
             * \brief Constructs a renderer object which uses the \c QPainter instance \a painter for its drawing operations.
             * \param painter The wrapped \c QPainter instance.
             */
            QtRenderer2D(QPainter& painter);

            /**
             * \brief Destructor.
             */
            ~QtRenderer2D();

            void saveState();
            void restoreState();

            void setTransform(const Math::Matrix3D& xform);
            void transform(const Math::Matrix3D& xform);

            void setPen(const Pen& pen);
            void setBrush(const Brush& brush);
            void setFont(const Font& font);

            void drawRectangle(double x1, double y1, double x2, double y2);
            void drawPolygon(const Math::Vector2DArray& points);
            void drawLine(double x1, double y1, double x2, double y2);
            void drawPolyline(const Math::Vector2DArray& points);
            void drawLineSegments(const Math::Vector2DArray& points);
            void drawPoint(double x, double y);
            void drawText(double x, double y, const std::string& txt);
            void drawEllipse(double x, double y, double width, double height);
            void drawPath(const Path2D& path);

            void setClipPath(const Path2D& path);
            void clearClipPath();

          private:
            QtRenderer2D(const QtRenderer2D&);

            QtRenderer2D& operator=(const QtRenderer2D&);

            void convertToQPolygon(const Math::Vector2DArray&);

            QPainter&                     qPainter;
            std::unique_ptr<QPolygonF>    qPolygon;
            std::unique_ptr<QPainterPath> qPainterPath;
        };
    } // namespace Vis
} // namespace CDPL

#endif // CDPL_VIS_QTRENDERER2D_HPP
