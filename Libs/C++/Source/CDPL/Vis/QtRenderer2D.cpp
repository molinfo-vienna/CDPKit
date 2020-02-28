/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * QtRenderer2D.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2020 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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


#include "StaticInit.hpp"

#include <QPainter>
#include <QPolygonF>
#include <QPointF>
#include <QRectF>
#include <QString>
#include <QTransform>

#include "CDPL/Vis/QtRenderer2D.hpp"
#include "CDPL/Vis/QtObjectFactory.hpp"


using namespace CDPL;


Vis::QtRenderer2D::QtRenderer2D(QPainter& painter): qPainter(painter) {}

Vis::QtRenderer2D::~QtRenderer2D() {}

void Vis::QtRenderer2D::saveState()
{
	qPainter.save();
}

void Vis::QtRenderer2D::restoreState()
{
	qPainter.restore();
}

void Vis::QtRenderer2D::setTransform(const Math::Matrix3D& xform)
{
	qPainter.setWorldTransform(QTransform(xform(0, 0), xform(1, 0), xform(2, 0),
										  xform(0, 1), xform(1, 1), xform(2, 1),
										  xform(0, 2), xform(1, 2), xform(2, 2)), false);
}

void Vis::QtRenderer2D::transform(const Math::Matrix3D& xform)
{
	qPainter.setWorldTransform(QTransform(xform(0, 0), xform(1, 0), xform(2, 0),
										  xform(0, 1), xform(1, 1), xform(2, 1),
										  xform(0, 2), xform(1, 2), xform(2, 2)), true);
}

void Vis::QtRenderer2D::setPen(const Pen& pen)
{
	qPainter.setPen(QtObjectFactory::createQPen(pen));
}

void Vis::QtRenderer2D::setBrush(const Brush& brush)
{
	qPainter.setBrush(QtObjectFactory::createQBrush(brush));
}

void Vis::QtRenderer2D::setFont(const Font& font)
{
	qPainter.setFont(QtObjectFactory::createQFont(font));
}

void Vis::QtRenderer2D::drawRectangle(double x, double y, double width, double height)
{
	qPainter.drawRect(QRectF(x, y, width, height));
}

void Vis::QtRenderer2D::drawPolygon(const Math::Vector2DArray& points)
{
	convertToQPolygon(points);

	qPainter.drawPolygon(*qPolygon);
}

void Vis::QtRenderer2D::drawLine(double x1, double y1, double x2, double y2)
{
	qPainter.drawLine(QPointF(x1, y1), QPointF(x2, y2));
}

void Vis::QtRenderer2D::drawPolyline(const Math::Vector2DArray& points)
{
	convertToQPolygon(points);

	qPainter.drawPolyline(*qPolygon);
}

void Vis::QtRenderer2D::drawLineSegments(const Math::Vector2DArray& points)
{
	std::size_t num_points = points.getSize();

	for (std::size_t i = 0; i < num_points; i += 2)
		drawLine(points[i][0], points[i][1], points[i + 1][0], points[i + 1][1]);
}

void Vis::QtRenderer2D::drawPoint(double x, double y)
{
	qPainter.drawPoint(QPointF(x, y));
}

void Vis::QtRenderer2D::drawText(double x, double y, const std::string& txt)
{
	qPainter.drawText(QPointF(x, y), QString::fromStdString(txt));
}

void Vis::QtRenderer2D::drawEllipse(double x, double y, double width, double height)
{
	qPainter.drawEllipse(QPointF(x, y), width * 0.5, height * 0.5);
}

void Vis::QtRenderer2D::convertToQPolygon(const Math::Vector2DArray& points)
{
	if (!qPolygon.get())
		qPolygon.reset(new QPolygonF());

	QPolygonF& qt_polygon = *qPolygon;
	qt_polygon.clear();

	Math::Vector2DArray::ConstElementIterator points_end = points.getElementsEnd();
	Math::Vector2DArray::ConstElementIterator p_it = points.getElementsBegin();

	for ( ; p_it != points_end; ++p_it) {
		const Math::Vector2D& pt = *p_it;

		qt_polygon.append(QPointF(pt[0], pt[1]));
	}
}
