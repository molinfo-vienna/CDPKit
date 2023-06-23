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
 * \brief Definition of the class CDPL::Vis::QtObjectFactory.
 */

#ifndef CDPL_VIS_QTOBJECTFACTORY_HPP
#define CDPL_VIS_QTOBJECTFACTORY_HPP

#include "CDPL/Vis/APIPrefix.hpp"


class QFont;
class QBrush;
class QPen;
class QColor;


namespace CDPL 
{

	namespace Vis
	{

		class Font;
		class Color;
		class Pen;
		class Brush;

		/**
		 * \brief Provides methods for the creation of \c QFont, \c QColor, \c QPen and \c QBrush objects
		 *        from Font, Color, Pen and Brush instances.
		 *
		 * For information about \c QFont, \c QColor, \c QPen and \c QBrush see [\ref QTDOC].
		 */
		class CDPL_VIS_API QtObjectFactory
		{

		public:
			/**
			 * \brief Creates a \c QFont object that corresponds to the specified font \a f.
			 * \param f The font object.
			 * \return A \c QFont object equivalent to \a f.
			 */
			static QFont createQFont(const Font& f);

			/**
			 * \brief Creates a \c QColor object that corresponds to the specified color \a c.
			 * \param c The color object.
			 * \return A \c QColor object equivalent to \a c.
			 * \note <em>Qt 3.x</em> does not support alpha channels.
			 */
			static QColor createQColor(const Color& c);

			/**
			 * \brief Creates a \c QPen object that corresponds to the specified pen \a p.
			 * \param p The pen object.
			 * \return A \c QPen object equivalent to \a p.
			 */
			static QPen createQPen(const Pen& p);
		
			/**
			 * \brief Creates a \c QBrush object that corresponds to the specified brush \a b.
			 * \param b The brush object.
			 * \return A \c QBrush object equivalent to \a b.
			 */
			static QBrush createQBrush(const Brush& b);

		private:
			QtObjectFactory() {}
		};
	}
}

#endif // CDPL_VIS_QTOBJECTFACTORY_HPP
