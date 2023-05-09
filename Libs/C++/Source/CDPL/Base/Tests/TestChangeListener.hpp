/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * TestChangeListener.hpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
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


#ifndef CDPL_BASE_TEST_TESTCHANGELISTENER_HPP
#define CDPL_BASE_TEST_TESTCHANGELISTENER_HPP

#include <cstddef>

#include "CDPL/Base/LookupKey.hpp"
#include "CDPL/Base/Variant.hpp"


namespace
{

	const CDPL::Base::LookupKey RESET_KEY = CDPL::Base::LookupKey::create("reset_key");

	struct TestChangeListener
	{

		TestChangeListener(): 
			numParamChangedCalls(0), numParamRemovedCalls(0), numParentChangedCalls(0),
			changedParamKey(RESET_KEY), removedParamKey(RESET_KEY)  {}

		void reset() {
			numParamChangedCalls = 0;
			numParamRemovedCalls = 0;
			numParentChangedCalls = 0;

			changedParamKey = RESET_KEY;
			removedParamKey = RESET_KEY;

			changedParamValue = CDPL::Base::Variant();
		}

		void parameterChanged(const CDPL::Base::LookupKey& key, const CDPL::Base::Variant& var) {
			numParamChangedCalls++;
			changedParamKey = key;
			changedParamValue = var; 
		}
		
		void parameterRemoved(const CDPL::Base::LookupKey& key) {
			numParamRemovedCalls++;
			removedParamKey = key;
		}

		void parentChanged() {
			numParentChangedCalls++;
		}
		
		std::size_t           numParamChangedCalls;
		std::size_t           numParamRemovedCalls;
		std::size_t           numParentChangedCalls;
		CDPL::Base::LookupKey changedParamKey;
		CDPL::Base::LookupKey removedParamKey;
		CDPL::Base::Variant   changedParamValue;
	};
}

#endif // CDPL_BASE_TEST_TESTCHANGELISTENER_HPP
