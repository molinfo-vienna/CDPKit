/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ImageWriter.hpp 
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


#ifndef CDPL_VIS_IMAGEWRITER_HPP
#define CDPL_VIS_IMAGEWRITER_HPP

#include <memory>

#include "CDPL/Vis/APIPrefix.hpp"


typedef struct _cairo_surface cairo_surface_t;


namespace CDPL 
{

	namespace Base
	{
		
		class DataIOBase;
	}

	namespace Chem
	{

		class Reaction;
		class MolecularGraph;
	}

	namespace Vis
	{

		class View2D;
		class ReactionView2D;
		class StructureView2D;
		class Rectangle2D;

		class CDPL_VIS_API ImageWriter
		{

		protected:
			ImageWriter(const Base::DataIOBase& io_base);

			virtual ~ImageWriter();

			cairo_surface_t* renderMolGraphImage(const Chem::MolecularGraph&);
			cairo_surface_t* renderReactionImage(const Chem::Reaction&);

			virtual cairo_surface_t* createCairoSurface(double, double) const = 0;
			virtual cairo_surface_t* createCairoSurface() const = 0;

		private:
			ImageWriter(const ImageWriter&);

			cairo_surface_t* renderImage(View2D&) const;

			void getImageBounds(View2D&, Rectangle2D&) const;

			ImageWriter& operator=(const ImageWriter&);

			typedef std::auto_ptr<StructureView2D> StructureViewPtr;
			typedef std::auto_ptr<ReactionView2D> ReactionViewPtr;

			const Base::DataIOBase& ioBase;
			StructureViewPtr        structureView;
			ReactionViewPtr         reactionView;
		};
	}
}

#endif // CDPL_VIS_IMAGEWRITER_HPP
