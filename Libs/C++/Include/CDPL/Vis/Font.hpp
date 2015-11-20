/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * Font.hpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2010 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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
 * \brief Definition of the class CDPL::Vis::Font.
 */

#ifndef CDPL_VIS_FONT_HPP
#define CDPL_VIS_FONT_HPP

#include <string>

#include "CDPL/Vis/APIPrefix.hpp"


namespace CDPL 
{

	namespace Vis
	{

		/**
		 * \addtogroup CDPL_VIS_RENDERING_DATA_STRUCTURES
		 * @{
		 */

		/**
		 * \brief Specifies a font for drawing text.
		 *
		 * On creation of a \c %Font object one can specify various attributes the font should have. The attributes set in
		 * the constructor can also be set later, e.g. setFamily() and setSize(). The remaining attributes must be set after
		 * construction, e.g. setBold(), setItalic(), setUnderlined(), setOverlined(), setStrikedOut() and setFixedPitch().
		 * The corresponding getter methods like getFamily() and getSize() return the values that were set, even though
		 * the values used may differ. Renderer2D implementations generally will use the font with the specified attributes,
		 * or if no exactly matching font exists, they will take the closest matching available font.
		 */
		class CDPL_VIS_API Font
		{

		public:
			/**
			 * \brief Constructs a font object with an unspecified family name and a font size of \e 12.0.
			 */
			Font();
		
			/**
			 * \brief Constructs a font object with the specified font family name and font size.
			 *
			 * If \a size is negative, the font size is set to zero.
			 *
			 * \param family The font family name.
			 * \param size The font size.
			 */
			Font(const std::string& family, double size = 12.0); 

			/**
			 * \brief Sets the font family name.
			 * \param family The font family name.
			 */
			void setFamily(const std::string& family);
 
			/**
			 * \brief Returns the font family name.
			 * \return The font family name.
			 */
			const std::string& getFamily() const; 

			/**
			 * \brief Sets the font size.
			 *
			 * If \a size is negative, the font size is set to zero.
			 *
			 * \param size The font size.
			 */
			void setSize(double size); 

			/**
			 * \brief Returns the font size.
			 * \return The font size.
			 */
			double getSize() const; 

			/**
			 * \brief Sets or clears the flag specifying whether text should be rendered bold.
			 * \param flag \c true if text should be rendered bold, and \c false otherwise.
			 */
			void setBold(bool flag); 

			/**
			 * \brief Returns the flag specifying whether text is rendered bold.
			 * \return \c true if text is rendered bold, and \c false otherwise.
			 */
			bool isBold() const; 
	
			/**
			 * \brief Sets or clears the flag specifying whether text should be rendered italicized.
			 * \param flag \c true if text should be rendered italicized, and \c false otherwise.
			 */
			void setItalic(bool flag); 

			/**
			 * \brief Returns the flag specifying whether text is rendered italicized.
			 * \return \c true if text is rendered italicized, and \c false otherwise.
			 */
			bool isItalic() const; 
		
			/**
			 * \brief Sets or clears the flag specifying whether text should be rendered underlined.
			 * \param flag \c true if text should be rendered underlined, and \c false otherwise.
			 */
			void setUnderlined(bool flag); 

			/**
			 * \brief Returns the flag specifying whether text is rendered underlined.
			 * \return \c true if text is rendered underlined, and \c false otherwise.
			 */
			bool isUnderlined() const; 

			/**
			 * \brief Sets or clears the flag specifying whether text should be rendered overlined.
			 * \param flag \c true if text should be rendered overlined, and \c false otherwise.
			 */
			void setOverlined(bool flag); 

			/**
			 * \brief Returns the flag specifying whether text is rendered overlined.
			 * \return \c true if text is rendered overlined, and \c false otherwise.
			 */
			bool isOverlined() const; 
	
			/**
			 * \brief Sets or clears the flag specifying whether text should be rendered striked-out.
			 * \param flag \c true if text should be rendered striked-out, and \c false otherwise.
			 */
			void setStrikedOut(bool flag); 

			/**
			 * \brief Returns the flag specifying whether text is rendered striked-out.
			 * \return \c true if text is rendered striked-out, and \c false otherwise.
			 */
			bool isStrikedOut() const; 

			/**
			 * \brief Sets or clears the fixed pitch flag.
			 * \param flag \c true if the font has a fixed pitch, and \c false otherwise.
			 */
			void setFixedPitch(bool flag); 

			/**
			 * \brief Returns the fixed pitch flag.
			 * \return \c true if the font has a fixed pitch, and \c false otherwise.
			 */
			bool hasFixedPitch() const; 

			/**
			 * \brief Equality comparison operator.
			 * \param font The other \c %Font object to be compared with.
			 * \return \c true if all font attributes compare equal, and \c false otherwise.
			 */
			bool operator==(const Font& font) const;

			/**
			 * \brief Inequality comparison operator.
			 *
			 * The result is equivalent to <tt>!(*this == font)</tt>.
			 *
			 * \param font The other \c %Font object to be compared with.
			 * \return \c true if one of the font attributes compares non-equal, and \c false otherwise.
			 */					
			bool operator!=(const Font& font) const;

		private:
			std::string family;
			double      size;
			bool        bold;
			bool        italic;
			bool        underlined;
			bool        overlined;
			bool        strikedOut;
			bool        fixedPitch;
		};

		/**
		 * @}
		 */
	}
}

#endif // CDPL_VIS_FONT_HPP
