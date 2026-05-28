/* 
 * GradientVectorTraits.hpp 
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
 * \brief Definition of class CDPL::ForceField::GradientVectorTraits.
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
         * \brief Generic primary traits template providing zero-initialization for a 3D gradient vector container of type \a GV.
         *
         * The primary template assumes \a GV is indexable via <tt>operator[]</tt> with each element exposing 3 components
         * (\c [0], \c [1], \c [2]) and clears them by direct assignment.
         *
         * \tparam GV The gradient-vector container type.
         */
        template <typename GV>
        struct GradientVectorTraits
        {

            /** \brief The gradient-vector container type. */
            typedef GV          VectorType;
            /** \brief The type used to specify element counts. */
            typedef std::size_t SizeType;

            /**
             * \brief Zeroes the first \a num_elem components of the gradient vector \a g.
             * \param g The gradient vector to clear.
             * \param num_elem The number of leading elements to clear.
             */
            static void clear(VectorType& g, std::size_t num_elem)
            {
                for (std::size_t i = 0; i < num_elem; i++) {
                    g[i][0] = 0;
                    g[i][1] = 0;
                    g[i][2] = 0;
                }
            }
        };

        /**
         * \brief GradientVectorTraits specialization for Math::VectorArray gradient containers.
         * \tparam V The element vector type stored in the Math::VectorArray.
         */
        template <typename V>
        struct GradientVectorTraits<Math::VectorArray<V> >
        {

            /** \brief The gradient-vector container type. */
            typedef Math::VectorArray<V>          VectorType;
            /** \brief The element vector type stored in the container. */
            typedef V                             ElementType;
            /** \brief The scalar value type of the element vector. */
            typedef typename V::ValueType         ValueType;
            /** \brief The type used to specify element counts. */
            typedef typename VectorType::SizeType SizeType;

            /**
             * \brief Zeroes the first \a num_elem element vectors of \a g.
             * \param g The gradient vector to clear.
             * \param num_elem The number of leading elements to clear.
             */
            static void clear(VectorType& g, std::size_t num_elem)
            {
                for (typename VectorType::ElementIterator it = g.getElementsBegin(), end = g.getElementsBegin() + num_elem; it != end; ++it)
                    it->clear(ValueType());
            }
        };

        /**
         * \brief GradientVectorTraits specialization for \c std::vector gradient containers.
         * \tparam V The element vector type stored in the \c std::vector.
         */
        template <typename V>
        struct GradientVectorTraits<std::vector<V> >
        {

            /** \brief The gradient-vector container type. */
            typedef std::vector<V>                 VectorType;
            /** \brief The element vector type stored in the container. */
            typedef V                              ElementType;
            /** \brief The scalar value type of the element vector. */
            typedef typename V::ValueType          ValueType;
            /** \brief The type used to specify element counts. */
            typedef typename VectorType::size_type SizeType;

            /**
             * \brief Zeroes the first \a num_elem element vectors of \a g.
             * \param g The gradient vector to clear.
             * \param num_elem The number of leading elements to clear.
             */
            static void clear(VectorType& g, std::size_t num_elem)
            {
                for (typename std::vector<V>::iterator it = g.begin(), end = g.begin() + num_elem; it != end; ++it)
                    it->clear(ValueType());
            }
        };
    } // namespace ForceField
} // namespace CDPL

#endif // CDPL_FORCEFIELD_GRADIENTVECTORTRAITS_HPP
