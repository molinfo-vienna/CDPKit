/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * GradientVectorTraits.hpp 
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

/**
 * \file
 * \brief Definition of the class CDPL::ForceField::GradientVectorTraits.
 */

#ifndef CDPL_FORCEFIELD_GRADIENTVECTORTRAITS_HPP
#define CDPL_FORCEFIELD_GRADIENTVECTORTRAITS_HPP

#include <cstddef>
#include <vector>

#include "CDPL/Math/VectorArray.hpp"


namespace CDPL
{

    namespace ForceField
    {

		/**
		 * \addtogroup CDPL_FORCEFIELD_HELPER_CLASSES
		 * @{
		 */

		template <typename GV>
		struct GradientVectorTraits
		{

			typedef GV VectorType;
			typedef std::size_t SizeType;

			static void clear(VectorType& g, std::size_t num_elem) {
				for (std::size_t i = 0; i < num_elem; i++) {
					g[i][0] = 0;
					g[i][1] = 0;
					g[i][2] = 0;
				}
			}
		};
	
		template <typename V>
		struct GradientVectorTraits<Math::VectorArray<V> >
		{
	
			typedef Math::VectorArray<V> VectorType;
			typedef V ElementType;
			typedef typename V::ValueType ValueType;
			typedef typename VectorType::SizeType SizeType;

			static void clear(VectorType& g, std::size_t num_elem) {
				for (typename VectorType::ElementIterator it = g.getElementsBegin(), end = g.getElementsBegin() + num_elem; it != end; ++it)
					it->clear(ValueType());
			}
		};

		template <typename V>
		struct GradientVectorTraits<std::vector<V> >
		{
	
			typedef std::vector<V> VectorType;
			typedef V ElementType;
			typedef typename V::ValueType ValueType;
			typedef typename VectorType::size_type SizeType;

			static void clear(VectorType& g, std::size_t num_elem) {
				for (typename std::vector<V>::iterator it = g.begin(), end = g.begin() + num_elem; it != end; ++it)
					it->clear(ValueType());
			}
		};

		/**
		 * @}
		 */
    }
}

#endif // CDPL_FORCEFIELD_GRADIENTVECTORTRAITS_HPP
