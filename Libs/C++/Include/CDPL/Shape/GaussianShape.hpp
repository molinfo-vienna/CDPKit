/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

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
 * \brief Definition of the class CDPL::Shape::GaussianShape.
 */

#ifndef CDPL_SHAPE_GAUSSIANSHAPE_HPP
#define CDPL_SHAPE_GAUSSIANSHAPE_HPP

#include <cstddef>
#include <vector>

#include <boost/shared_ptr.hpp>

#include "CDPL/Shape/APIPrefix.hpp"
#include "CDPL/Base/PropertyContainer.hpp"
#include "CDPL/Math/Vector.hpp"


namespace CDPL 
{

    namespace Shape
    {

		/**
		 * \brief A data type for the descripton of arbitrary shapes composed of spheres approximated by gaussian functions.
		 */
		class CDPL_SHAPE_API GaussianShape : public Base::PropertyContainer
		{

		  public:
			class Element
			{

			public:
				Element(const Math::Vector3D& pos, double radius, std::size_t color = 0, double hardness = 2.7):
					position(pos), radius(radius), hardness(hardness), color(color) {}

				const Math::Vector3D& getPosition() const {
					return position;
				}

				void setPosition(const Math::Vector3D& pos) {
					position = pos;
				}
		
				double getRadius() const {
					return radius;
				}

				void setRadius(double radius) {
					this->radius = radius;
				}
		
				std::size_t getColor() const {
					return color;
				}

				void setColor(std::size_t color) {
					this->color = color;
				}
		
				double getHardness() const {
					return hardness;
				}

				void setHardness(double hardness) {
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
			typedef boost::shared_ptr<GaussianShape> SharedPointer;

			typedef ElementList::const_iterator ConstElementIterator;
			typedef ElementList::iterator ElementIterator;
		    
			void clear();

			std::size_t getNumElements() const;
	    
			void addElement(const Math::Vector3D& pos, double radius, std::size_t color = 0, double hardness = 2.7);

			void addElement(const Element& elem);

			void removeElement(std::size_t idx);
	    
			const Element& getElement(std::size_t idx) const;

			Element& getElement(std::size_t idx);

			ConstElementIterator getElementsBegin() const;

			ConstElementIterator getElementsEnd() const;

			ElementIterator getElementsBegin();

			ElementIterator getElementsEnd();
	    
		  private:
			ElementList elements;
		};
    }
}

#endif // CDPL_SHAPE_GAUSSIANSHAPE_HPP
