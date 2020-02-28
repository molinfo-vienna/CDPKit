/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * Utilities.hpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2020 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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


#ifndef CHOX_UTILITIES_HPP
#define CHOX_UTILITIES_HPP

#include "CDPLFwd.hpp"


class QPainter;
class QString;


namespace ChOx
{

	void drawText(QPainter& painter, const QString& text, unsigned int alignment, 
				  double width, double height, double margin);

	void initData(CDPL::Chem::Reaction& rxn);
	void initData(CDPL::Chem::Molecule& mol);

	void prepareOutputData(CDPL::Chem::Reaction& rxn, const CDPL::Base::DataFormat& opt_fmt, 
						   const CDPL::Base::ControlParameterContainer& params);
	void prepareOutputData(CDPL::Chem::Molecule& mol, const CDPL::Base::DataFormat& opt_fmt, 
						   const CDPL::Base::ControlParameterContainer& params);
}

#endif // CHOX_UTILITIES_HPP
