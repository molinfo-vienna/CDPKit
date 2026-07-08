/* 
 * GaussianShape.hpp 
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
 * \brief Definition of class CDPL::Shape::GaussianShape.
 */

#ifndef CDPL_SHAPE_GAUSSIANSHAPE_HPP
#define CDPL_SHAPE_GAUSSIANSHAPE_HPP

#include <cstddef>
#include <vector>
#include <memory>

#include "CDPL/Shape/APIPrefix.hpp"
#include "CDPL/Base/PropertyContainer.hpp"
#include "CDPL/Math/Vector.hpp"


namespace CDPL
{

    namespace Shape
    {

        /**
         * \brief Data type for the descripton of arbitrary shapes composed of spheres approximated by gaussian functions.
         */
        class CDPL_SHAPE_API GaussianShape : public Base::PropertyContainer
        {

          public:
            /**
             * \brief Data structure representing a single sphere of the Gaussian shape, characterized by a position, radius, hardness and color.
             */
            class Element
            {

              public:
                /**
                 * \brief Constructs an \c %Element with the given attributes.
                 * \param pos The position of the sphere center.
                 * \param radius The sphere radius.
                 * \param color The color (numeric identifier) used to attribute the sphere (e.g. for pharmacophore-aware overlays).
                 * \param hardness The hardness of the Gaussian (default: \e 2.7).
                 */
                Element(const Math::Vector3D& pos, double radius, std::size_t color = 0, double hardness = 2.7):
                    position(pos), radius(radius), hardness(hardness), color(color) {}

                /**
                 * \brief Returns the position of the sphere center.
                 * \return The sphere center position.
                 */
                const Math::Vector3D& getPosition() const
                {
                    return position;
                }

                /**
                 * \brief Sets the position of the sphere center.
                 * \param pos The sphere center position.
                 */
                void setPosition(const Math::Vector3D& pos)
                {
                    position = pos;
                }

                /**
                 * \brief Returns the sphere radius.
                 * \return The sphere radius.
                 */
                double getRadius() const
                {
                    return radius;
                }

                /**
                 * \brief Sets the sphere radius.
                 * \param radius The sphere radius.
                 */
                void setRadius(double radius)
                {
                    this->radius = radius;
                }

                /**
                 * \brief Returns the color attribute of the sphere.
                 * \return The color attribute.
                 */
                std::size_t getColor() const
                {
                    return color;
                }

                /**
                 * \brief Sets the color attribute of the sphere.
                 * \param color The color attribute.
                 */
                void setColor(std::size_t color)
                {
                    this->color = color;
                }

                /**
                 * \brief Returns the hardness of the Gaussian.
                 * \return The Gaussian hardness.
                 */
                double getHardness() const
                {
                    return hardness;
                }

                /**
                 * \brief Sets the hardness of the Gaussian.
                 * \param hardness The Gaussian hardness.
                 */
                void setHardness(double hardness)
                {
                    this->hardness = hardness;
                }

              private:
                Math::Vector3D position;
                double         radius;
                double         hardness;
                std::size_t    color;
            };

          private:
            typedef std::vector<Element> ElementList;

          public:
            /**
             * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %GaussianShape instances.
             */
            typedef std::shared_ptr<GaussianShape> SharedPointer;

            /**
             * \brief A constant iterator over the elements of the shape.
             */
            typedef ElementList::const_iterator ConstElementIterator;

            /**
             * \brief A mutable iterator over the elements of the shape.
             */
            typedef ElementList::iterator       ElementIterator;

            /**
             * \brief Removes all elements from the shape.
             */
            void clear();

            /**
             * \brief Returns the number of elements in the shape.
             * \return The number of elements.
             */
            std::size_t getNumElements() const;

            /**
             * \brief Adds a new element to the shape.
             * \param pos The position of the new element's sphere center.
             * \param radius The sphere radius.
             * \param color The color attribute.
             * \param hardness The hardness of the Gaussian.
             */
            void addElement(const Math::Vector3D& pos, double radius, std::size_t color = 0, double hardness = 2.7);

            /**
             * \brief Adds the given element to the shape.
             * \param elem The element to add.
             */
            void addElement(const Element& elem);

            /**
             * \brief Removes the element at index \a idx.
             * \param idx The index of the element to remove.
             * \throw Base::IndexError if \a idx is not in the range [0, getNumElements()).
             */
            void removeElement(std::size_t idx);

            /**
             * \brief Returns a \c const reference to the element at index \a idx.
             * \param idx The index of the element.
             * \return A \c const reference to the element.
             * \throw Base::IndexError if \a idx is not in the range [0, getNumElements()).
             */
            const Element& getElement(std::size_t idx) const;

            /**
             * \brief Returns a reference to the element at index \a idx.
             * \param idx The index of the element.
             * \return A reference to the element.
             * \throw Base::IndexError if \a idx is not in the range [0, getNumElements()).
             */
            Element& getElement(std::size_t idx);

            /**
             * \brief Returns a constant iterator pointing to the first element.
             * \return A constant iterator pointing to the first element.
             */
            ConstElementIterator getElementsBegin() const;

            /**
             * \brief Returns a constant iterator pointing one past the last element.
             * \return A constant iterator pointing one past the last element.
             */
            ConstElementIterator getElementsEnd() const;

            /**
             * \brief Returns a mutable iterator pointing to the first element.
             * \return A mutable iterator pointing to the first element.
             */
            ElementIterator getElementsBegin();

            /**
             * \brief Returns a mutable iterator pointing one past the last element.
             * \return A mutable iterator pointing one past the last element.
             */
            ElementIterator getElementsEnd();

            /**
             * \brief Returns a constant iterator pointing to the first element (range-based for support).
             * \return A constant iterator pointing to the first element.
             */
            ConstElementIterator begin() const;

            /**
             * \brief Returns a constant iterator pointing one past the last element (range-based for support).
             * \return A constant iterator pointing one past the last element.
             */
            ConstElementIterator end() const;

            /**
             * \brief Returns a mutable iterator pointing to the first element (range-based for support).
             * \return A mutable iterator pointing to the first element.
             */
            ElementIterator begin();

            /**
             * \brief Returns a mutable iterator pointing one past the last element (range-based for support).
             * \return A mutable iterator pointing one past the last element.
             */
            ElementIterator end();

          private:
            ElementList elements;
        };
    } // namespace Shape
} // namespace CDPL

#endif // CDPL_SHAPE_GAUSSIANSHAPE_HPP
