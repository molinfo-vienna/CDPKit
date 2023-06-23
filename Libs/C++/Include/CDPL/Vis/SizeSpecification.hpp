/* 
 * SizeSpecification.hpp 
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
 * \brief Definition of the class CDPL::Vis::SizeSpecification.
 */

#ifndef CDPL_VIS_SIZESPECIFICATION_HPP
#define CDPL_VIS_SIZESPECIFICATION_HPP

#include "CDPL/Vis/APIPrefix.hpp"


namespace CDPL 
{

	namespace Vis
	{
		
		/**
		 * \brief Specifies the value and type of a size attribute and defines how the value may change during processing steps.
		 */
		class CDPL_VIS_API SizeSpecification
		{

		public:
			/**
			 * \brief Constructs a \c %SizeSpecification object with the given attributes.
			 * \param value The value of the specified size.
			 * \param relative \c true if the size specification is relative (proportional) to another size, and \c false otherwise.
			 * \param input_scaling \c true if the specified size has to follow input scaling, and \c false otherwise.
			 * \param output_scaling \c true if the specified size has to follow output scaling, and \c false otherwise.
			 * \see setValue(), setRelative(), followInputScaling(), followOutputScaling()
			 */
			SizeSpecification(double value = 0.0, bool relative = false, bool input_scaling = false, bool output_scaling = false):
				value(value), relative(relative), inputScaling(input_scaling), outputScaling(output_scaling) {}

			/**
			 * \brief Sets value of the specified size.
			 * \param value The value of the specified size.
			 */
			void setValue(double value);

			/**
			 * \brief Returns the value of the specified size.
			 * \return The value of the specified size.
			 * \see setValue()
			 */
			double getValue() const;

			/**
			 * \brief Specifies if the size specification is absolute or relative to another size.
			 *
			 * If the size specification is relative (proportional) to another size, the size value is interpreted as a scaling
			 * factor for the absolute value of the other size.
			 *
			 * \param relative \c true if the size specification is relative, and \c false otherwise.
			 * \see setValue()
			 */
			void setRelative(bool relative);

			/**
			 * \brief Tells if the size specification is absolute or relative to another size.
			 * \return \c true if the size specification is relative, and \c false otherwise.
			 * \see setRelative()
			 */
			bool isRelative() const;

			/**
			 * \brief Specifies whether the specified size has to follow input scaling operations.
			 *
			 * Input scaling is a pre-processing step (performed by some other part of the system) where an input size quantity
			 * is scaled to fulfill a certain constraint. An example is the scaling of input atom
			 * coordinates to obtain a certain average bond length for the 2D depiction of a chemical structure or reaction. 
			 *
			 * \param follow \c true if the specified size has to follow input scaling operations, and \c false otherwise.
			 */
			void followInputScaling(bool follow);

			/**
			 * \brief Tells if the specified size follows input scaling operations.
			 * \return \c true if the specified size follows input scaling operations, and \c false otherwise.
			 * \see followInputScaling()
			 */
			bool followsInputScaling() const;

			/**
			 * \brief Specifies whether the specified size has to follow output scaling operations.
			 *
			 * Output scaling is a post-processing step (performed by some other part of the system) where an output size quantity
			 * is scaled to fulfill a certain constraint. An example is the scaling of output atom
			 * coordinates to fit the 2D depiction of a chemical structure or reaction into the viewport area. 
			 *
			 * \param follow \c true if the specified size has to follow output scaling operations, and \c false otherwise.
			 */
			void followOutputScaling(bool follow);
			
			/**
			 * \brief Tells if the specified size follows output scaling operations.
			 * \return \c true if the specified size follows output scaling operations, and \c false otherwise.
			 * \see followOutputScaling()
			 */
			bool followsOutputScaling() const;

			/**
			 * \brief Equality comparison operator.
			 * \param spec The other \c %SizeSpecification object to be compared with.
			 * \return \c true if all attributes compare equal, and \c false otherwise.
			 */
			bool operator==(const SizeSpecification& spec) const;

			/**
			 * \brief Inequality comparison operator.
			 *
			 * The result is equivalent to <tt>!(*this == spec)</tt>.
			 *
			 * \param spec The other \c %SizeSpecification object to be compared with.
			 * \return \c true if one of the attributes compares non-equal, and \c false otherwise.
			 */					
			bool operator!=(const SizeSpecification& spec) const;

		private:
			double  value;
			bool    relative;
			bool    inputScaling;
			bool    outputScaling;
		};
	}
}

#endif // CDPL_VIS_SIZESPECIFICATION_HPP
