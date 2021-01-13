/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * BronKerboschAlgorithm.cpp 
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


#include <algorithm>
#include <iterator>

#include <boost/bind.hpp>

#include "CDPL/Util/BronKerboschAlgorithm.hpp"


using namespace CDPL;


Util::BronKerboschAlgorithm::BronKerboschAlgorithm(const BitSetArray& adj_mtx)
{
	init(adj_mtx);
}

Util::BronKerboschAlgorithm::BronKerboschAlgorithm(const BronKerboschAlgorithm& bka):
	adjMatrix(bka.adjMatrix), nodeDegrees(bka.nodeDegrees)
{
	for (StateStack::const_iterator it = bka.states.begin(), end = bka.states.end(); it != end; ++it) {
		State* state = stateCache.getRaw();

		*state = **it;
		states.push_back(state);
	}
}

Util::BronKerboschAlgorithm& Util::BronKerboschAlgorithm::operator=(const BronKerboschAlgorithm& bka)
{
	adjMatrix = bka.adjMatrix;
	nodeDegrees = bka.nodeDegrees;

	states.clear();
	stateCache.putAll();

	for (StateStack::const_iterator it = bka.states.begin(), end = bka.states.end(); it != end; ++it) {
		State* state = stateCache.getRaw();

		*state = **it;
		states.push_back(state);
	}

	return *this;
}

void Util::BronKerboschAlgorithm::init(const BitSetArray& adj_mtx)
{
	adjMatrix = &adj_mtx;

	nodeDegrees.clear();

	std::transform(adj_mtx.getElementsBegin(), adj_mtx.getElementsEnd(), 
				   std::back_inserter(nodeDegrees), boost::bind(&BitSet::count, _1));
	
	states.clear();
	stateCache.putAll();

	std::size_t num_nodes = adj_mtx.getSize();
	State* init_state = stateCache.getRaw();

	init_state->curr.resize(num_nodes);
	init_state->curr.reset();
	init_state->excl.resize(num_nodes);
	init_state->excl.reset();
	init_state->pool.resize(num_nodes);
	init_state->pool.set();
	init_state->v = 0;

	states.push_back(init_state);
}

bool Util::BronKerboschAlgorithm::nextClique(BitSet& clique)
{
  	while (!states.empty()) {
		State* state = states.back();

		if (state->v == 0) {
			if (state->pool.none() && state->excl.none()) {
				states.pop_back();
				stateCache.put();

				clique = state->curr;				
				return true;
			}
	
			pivotCandSet = state->pool;
			pivotCandSet |= state->excl;

			for (std::size_t i = pivotCandSet.find_first(), max_deg = 0; i != BitSet::npos; i = pivotCandSet.find_next(i)) {
				if (i == 0 || nodeDegrees[i] > max_deg) {
					max_deg = nodeDegrees[i];
					state->u = i;
				} 
			}

			state->v = state->pool.find_first();
		}

		bool iterate = false;

		for ( ; state->v != BitSet::npos; state->v = state->pool.find_next(state->v)) {
			if ((*adjMatrix)[state->u].test(state->v))
				continue;
		
			State* new_state = stateCache.getRaw();

			*new_state = *state;
			new_state->curr.set(state->v);
			new_state->pool &= (*adjMatrix)[state->v];
			new_state->excl &= (*adjMatrix)[state->v];
			new_state->v = 0;

			state->pool.reset(state->v);
			state->excl.set(state->v);
			state->v = state->pool.find_next(state->v);

			iterate = true;
			states.push_back(new_state);
			break;
		}
		
		if (iterate)
			continue;

		states.pop_back();
		stateCache.put();
	}

	return false;
}
