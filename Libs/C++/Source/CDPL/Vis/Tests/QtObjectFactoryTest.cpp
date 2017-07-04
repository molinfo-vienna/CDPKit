/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * QtObjectFactoryTest.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2010 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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


#include <QPen>
#include <QBrush>
#include <QFont>
#include <QColor>

#include <boost/test/auto_unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>

#include "CDPL/Vis/QtObjectFactory.hpp"
#include "CDPL/Vis/Pen.hpp"
#include "CDPL/Vis/Brush.hpp"
#include "CDPL/Vis/Font.hpp"
#include "CDPL/Vis/Color.hpp"


namespace
{

	void compareColors(const QColor& lhs, const QColor& rhs)
	{
		BOOST_CHECK_CLOSE(lhs.redF(), rhs.redF(), 1.0);
		BOOST_CHECK_CLOSE(lhs.greenF(), rhs.greenF(), 1.0);
		BOOST_CHECK_CLOSE(lhs.blueF(), rhs.blueF(), 1.0);
		BOOST_CHECK_CLOSE(lhs.alphaF(), rhs.alphaF(), 1.0);
	}

	void comparePens(const QPen& lhs, const QPen& rhs)
	{
		compareColors(lhs.color(), rhs.color());

		BOOST_CHECK_CLOSE(lhs.widthF(), rhs.widthF(), 0.5);
		BOOST_CHECK(lhs.capStyle() == rhs.capStyle());
		BOOST_CHECK(lhs.joinStyle() == rhs.joinStyle());
		BOOST_CHECK(lhs.style() == rhs.style());
	}

	void compareBrushes(const QBrush& lhs, const QBrush& rhs)
	{
		compareColors(lhs.color(), rhs.color());

		BOOST_CHECK(lhs.style() == rhs.style());
	}

	void compareFonts(const QFont& lhs, const QFont& rhs)
	{
		BOOST_CHECK(lhs.family() == rhs.family());
		BOOST_CHECK(lhs.pointSizeF() == rhs.pointSizeF());
		BOOST_CHECK(lhs.bold() == rhs.bold());
		BOOST_CHECK(lhs.italic() == rhs.italic());
		BOOST_CHECK(lhs.underline() == rhs.underline());
		BOOST_CHECK(lhs.overline() == rhs.overline());
		BOOST_CHECK(lhs.strikeOut() == rhs.strikeOut());
		BOOST_CHECK(lhs.fixedPitch() == rhs.fixedPitch());
	}
}


BOOST_AUTO_TEST_CASE(QtObjectFactoryTest)
{
	using namespace CDPL;
	using namespace Vis;

	compareColors(QColor(0, 0, 0, 255), QtObjectFactory::createQColor(Color::BLACK));
	compareColors(QColor(255, 0, 0), QtObjectFactory::createQColor(Color::RED));
	compareColors(QColor(0, 255, 0), QtObjectFactory::createQColor(Color::GREEN));
	compareColors(QColor(0, 0, 255, 255), QtObjectFactory::createQColor(Color::BLUE));
	compareColors(QColor(255, 255, 255, 255), QtObjectFactory::createQColor(Color::WHITE));

	compareColors(QColor(25, 51, 153, 255), QtObjectFactory::createQColor(Color(25.0 / 255.0, 51.3 / 255.0, 152.9 / 255.0)));
	compareColors(QColor(25, 51, 153, 0), QtObjectFactory::createQColor(Color(25.0 / 255.0, 51.0 / 255.0, 153.0 / 255.0, 0.0)));
	compareColors(QColor(25, 51, 153, 150), 
				  QtObjectFactory::createQColor(Color(25.1 / 255.0, 51.2 / 255.0, 153.0 / 255.0, 150.0 / 255.0)));
	compareColors(QColor(25, 51, 153, 255), QtObjectFactory::createQColor(Color(25.1 / 255.0, 51.0 / 255.0, 153.0 / 255.0, 1.0)));
	compareColors(QColor(25, 51, 153, 255), QtObjectFactory::createQColor(Color(25.2 / 255.0, 51.0 / 255.0, 153.0 / 255.0, 2.0)));
	compareColors(QColor(25, 51, 153, 0), QtObjectFactory::createQColor(Color(25.2 / 255.0, 51.1 / 255.0, 153.0 / 255.0, -1.2)));

//-----

	compareBrushes(QBrush(), QtObjectFactory::createQBrush(Brush(Color::BLACK, Brush::NO_PATTERN)));
	compareBrushes(QBrush(Qt::red), QtObjectFactory::createQBrush(Brush(Color::RED, Brush::SOLID_PATTERN)));
	compareBrushes(QBrush(Qt::Dense1Pattern), QtObjectFactory::createQBrush(Brush(Color::BLACK, Brush::DENSE1_PATTERN)));
	compareBrushes(QBrush(Qt::green, Qt::CrossPattern), QtObjectFactory::createQBrush(Brush(Color::GREEN, Brush::CROSS_PATTERN)));

//-----

	comparePens(QPen(), QtObjectFactory::createQPen(Pen(Color::BLACK, 1.0, Pen::SOLID_LINE, Pen::SQUARE_CAP, Pen::BEVEL_JOIN)));
	comparePens(QPen(Qt::DotLine), QtObjectFactory::createQPen(Pen(Color::BLACK, 1.0, Pen::DOT_LINE, Pen::SQUARE_CAP, Pen::BEVEL_JOIN)));
	comparePens(QPen(Qt::red), QtObjectFactory::createQPen(Pen(Color::RED, 1.0, Pen::SOLID_LINE, Pen::SQUARE_CAP, Pen::BEVEL_JOIN)));
	comparePens(QPen(Qt::green, 2), 
				QtObjectFactory::createQPen(Pen(Color::GREEN, 2.0, Pen::SOLID_LINE, Pen::SQUARE_CAP, Pen::BEVEL_JOIN)));
	comparePens(QPen(Qt::blue, 3, Qt::DashDotLine), 
				QtObjectFactory::createQPen(Pen(Color::BLUE, 3.0, Pen::DASH_DOT_LINE, Pen::SQUARE_CAP, Pen::BEVEL_JOIN)));
	comparePens(QPen(Qt::yellow, 1, Qt::DashLine, Qt::RoundCap, Qt::MiterJoin), 
				QtObjectFactory::createQPen(Pen(Color::YELLOW, 1.0, Pen::DASH_LINE, Pen::ROUND_CAP, Pen::MITER_JOIN)));

//-----

	compareFonts(QFont("", 12), QtObjectFactory::createQFont(Font()));

	Font font("Times", 13.0);
	QFont qfont("Times", 13);

	compareFonts(qfont, QtObjectFactory::createQFont(font));

	font.setBold(true);
	qfont.setBold(true);

	compareFonts(qfont, QtObjectFactory::createQFont(font));

	font.setItalic(true);
	qfont.setItalic(true);

	compareFonts(qfont, QtObjectFactory::createQFont(font));

	font.setUnderlined(true);
	qfont.setUnderline(true);

	compareFonts(qfont, QtObjectFactory::createQFont(font));

	font.setOverlined(true);
	qfont.setOverline(true);

	compareFonts(qfont, QtObjectFactory::createQFont(font));

	font.setStrikedOut(true);
	qfont.setStrikeOut(true);

	compareFonts(qfont, QtObjectFactory::createQFont(font));

	font.setFixedPitch(true);
	qfont.setFixedPitch(true);

	compareFonts(qfont, QtObjectFactory::createQFont(font));

	font.setFamily("Arial");
	qfont.setFamily("Arial");

	compareFonts(qfont, QtObjectFactory::createQFont(font));

	font.setSize(11.5);
	qfont.setPointSizeF(11.5);

	compareFonts(qfont, QtObjectFactory::createQFont(font));
}

