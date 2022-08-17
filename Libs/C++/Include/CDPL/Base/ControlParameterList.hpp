/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ControlParameterList.hpp 
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
 * \brief Definition of the class CDPL::Base::ControlParameterList.
 */

#ifndef CDPL_BASE_CONTROLPARAMETERLIST_HPP
#define CDPL_BASE_CONTROLPARAMETERLIST_HPP

#include <boost/shared_ptr.hpp>

#include "CDPL/Base/APIPrefix.hpp"
#include "CDPL/Base/ControlParameterContainer.hpp"


namespace CDPL 
{
	
	namespace Base
	{
		
		/**
		 * \brief A data structure for the storage and lookup of control-parameter values.
		 * \see Base::ControlParameterContainer for a description of the available methods.
		 */
		class CDPL_BASE_API ControlParameterList : public ControlParameterContainer
		{
		
		public:
			/**
			 * \brief A reference-counted smart pointer [\ref BSHPTR] for dynamically allocated \c %ControlParameterList instances.
			 */
			typedef boost::shared_ptr<ControlParameterList> SharedPointer;

			/**
			 * \brief Constructs an empty \c %ControlParameterList instance.
			 */
			ControlParameterList(): ControlParameterContainer() {}

			/**
			 * \brief Constructs a copy of the \c %ControlParameterContainer instance \a cntnr.
			 * \param cntnr The \c %ControlParameterContainer instance to copy.
			 * \note Only the control-parameter entries of \a cntnr are copied. Entries in the parent container
			 *       of \a cntnr (if set) will be ignored (see setParent()).
			 */
			ControlParameterList(const ControlParameterContainer& cntnr): ControlParameterContainer(cntnr) {}

			/**
			 * \brief Assignment operator.
			 * \param cntnr The \c %ControlParameterContainer instance to copy.
			 * \return A reference to itself.
			 */
			ControlParameterList& operator=(const ControlParameterContainer& cntnr);
		};
	}
}

#endif // CDPL_BASE_CONTROLPARAMETERLIST_HPP
