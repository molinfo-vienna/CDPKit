/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ElectronSystemList.hpp 
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
 * \brief Definition of the class CDPL::Chem::ElectronSystemList.
 */

#ifndef CDPL_CHEM_ELECTRONSYSTEMLIST_HPP
#define CDPL_CHEM_ELECTRONSYSTEMLIST_HPP

#include <memory>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/ElectronSystem.hpp"
#include "CDPL/Util/IndirectArray.hpp"


namespace CDPL 
{

	namespace Chem
	{

		/**
		 * \brief A data type for the storage of Chem::ElectronSystem objects.
		 */
		class CDPL_CHEM_API ElectronSystemList : public Util::IndirectArray<ElectronSystem>
		{

		  public:
			typedef std::shared_ptr<ElectronSystemList> SharedPointer;

		  private:
			const char* getClassName() const {
				return "ElectronSystemList";
			}
		};
	}
}

#endif // CDPL_CHEM_ELECTRONSYSTEMLIST_HPP
