/* 
 * DataSetPagePainter.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; see the file COPYING. If not, write to
 * the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */


#include <QRectF>
#include <QPointF>
#include <QPainter>

#include "CDPL/Vis/Pen.hpp"
#include "CDPL/Vis/Color.hpp"
#include "CDPL/Vis/SizeSpecification.hpp"
#include "CDPL/Vis/QtObjectFactory.hpp"

#include "DataSetPagePainter.hpp"
#include "DataRecordPainter.hpp"
#include "ControlParameterFunctions.hpp"
#include "Settings.hpp"


using namespace ChOX;


DataSetPagePainter::DataSetPagePainter(QPainter& painter, const Settings& settings): painter(painter), settings(settings) {}

void DataSetPagePainter::drawGrid(double vp_width, double vp_height, int num_rows, int num_cols) const
{
    using namespace CDPL;
    using namespace Vis;

    if (num_rows < 2 && num_cols < 2)
        return;

    Pen::LineStyle line_style = getGridLineStyleParameter(settings);
    double line_width = getGridLineWidthParameter(settings).getValue();
    const Color& line_color = getGridLineColorParameter(settings);

    painter.setPen(QtObjectFactory::createQPen(Pen(line_color, line_width, line_style)));

    if (num_cols >= 2) {
        for (int i = 1; i < num_cols; i++) {
            double x_pos = i * vp_width;

            painter.drawLine(QPointF(x_pos, 0.0), QPointF(x_pos, vp_height * num_rows));
        }
    }     

    if (num_rows >= 2) {
        for (int i = 1; i < num_rows; i++) {
            double y_pos = i * vp_height;

            painter.drawLine(QPointF(0.0, y_pos), QPointF(vp_width * num_cols, y_pos));
        }
    }     
}

void DataSetPagePainter::drawRecord(int row, int col, double vp_width, double vp_height, int rec_no, DataRecordPainter& rec_painter) const
{
    using namespace CDPL;

    double y_pos = vp_height * row;
    double x_pos = vp_width * col;

    painter.save();

    painter.translate(x_pos, y_pos);
    painter.setClipRect(QRectF(0.0, 0.0, vp_width, vp_height));

    rec_painter.drawRecord(rec_no, vp_width, vp_height);

    painter.restore();
}
