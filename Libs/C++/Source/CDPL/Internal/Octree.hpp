/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * Octree.hpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2010 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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

// Copyright (c) 2015 Jens Behley, University of Bonn
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights  to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.


#ifndef CDPL_INTERNAL_OCTREE_HPP
#define CDPL_INTERNAL_OCTREE_HPP

#include <cstddef>
#include <cmath>
#include <limits>
#include <vector>

#include <boost/shared_ptr.hpp>


namespace CDPL
{

    namespace Internal
    {

		/** 
		 * \brief Index-based Octree implementation offering different queries and insertion/removal of points.
		 *
		 * The index-based Octree uses a successor relation and a start index in each Octant to improve runtime
		 * performance for radius queries. The efficient storage of the points by relinking list elements
		 * bases on the insight that children of an Octant contain disjoint subsets of points inside the Octant and
		 * that we can reorganize the points such that we get an continuous single connect list that we can use to
		 * store in each octant the start of this list.
		 *
		 * Special about the implementation is that it allows to search for neighbors with arbitrary p-norms, which
		 * distinguishes it from most other Octree implementations.
		 *
		 * If you use the implementation or ideas from the corresponding paper in your academic work, it would be nice if you
		 * cite the corresponding paper:
		 *
		 *    J. Behley, V. Steinhage, A.B. Cremers. Efficient Radius Neighbor Search in Three-dimensional Point Clouds,
		 *    Proc. of the IEEE International Conference on Robotics and Automation (ICRA), 2015.
		 *
		 * In future, we might add also other neighbor queries and implement the removal and adding of points.
		 *
		 * \version 0.1-icra
		 * \author behley
		 */
		template <typename PointT, typename ContainerT = std::vector<PointT>, typename ScalarT = typename PointT::ValueType>
		class Octree
		{

		public:
			/**
			 * Some generic distances: Manhattan, (squared) Euclidean, and Maximum distance.
			 *
			 * A Distance has to implement the methods
			 * 1. compute of two points p and q to compute and return the distance between two points, and
			 * 2. norm of x,y,z coordinates to compute and return the norm of a point p = (x,y,z)
			 * 3. sqr and sqrt of value to compute the correct radius if a comparison is performed using squared norms (see
			 *    L2Distance)...
			 */
			struct L1Distance
			{

				static ScalarT compute(const PointT& p, const PointT& q) {
					ScalarT diff1 = p[0] - q[0];
					ScalarT diff2 = p[1] - q[1];
					ScalarT diff3 = p[2] - q[2];

					return std::abs(diff1) + std::abs(diff2) + std::abs(diff3);
				}

				static ScalarT norm(ScalarT x, ScalarT y, ScalarT z) {
					return std::abs(x) + std::abs(y) + std::abs(z);
				}

				static ScalarT sqr(ScalarT r) {
					return r;
				}

				static ScalarT sqrt(ScalarT r) {
					return r;
				}
			};

			struct L2Distance
			{

				static ScalarT compute(const PointT& p, const PointT& q) {
					ScalarT diff1 = p[0] - q[0];
					ScalarT diff2 = p[1] - q[1];
					ScalarT diff3 = p[2] - q[2];

					return std::pow(diff1, 2) + std::pow(diff2, 2) + std::pow(diff3, 2);
				}

				static ScalarT norm(ScalarT x, ScalarT y, ScalarT z)	{
					return std::pow(x, 2) + std::pow(y, 2) + std::pow(z, 2);
				}

				static ScalarT sqr(ScalarT r) {
					return r * r;
				}

				static ScalarT sqrt(ScalarT r) {
					return std::sqrt(r);
				}
			};

			struct MaxDistance
			{

				static ScalarT compute(const PointT& p, const PointT& q) {
					ScalarT diff1 = std::abs(p[0] - q[0]);
					ScalarT diff2 = std::abs(p[1] - q[1]);
					ScalarT diff3 = std::abs(p[2] - q[2]);
					ScalarT maximum = diff1;

					if (diff2 > maximum) 
						maximum = diff2;
					if (diff3 > maximum) 
						maximum = diff3;

					return maximum;
				}

				static ScalarT norm(ScalarT x, ScalarT y, ScalarT z)	{
					ScalarT maximum = x;

					if (y > maximum) 
						maximum = y;
					if (z > maximum) 
						maximum = z;

					return maximum;
				}

				static ScalarT sqr(ScalarT r) {
					return r;
				}

				static ScalarT sqrt(ScalarT r) {
					return r;
				}
			};

			Octree();

			/** \brief initialize octree with all points **/
			void initialize(const ContainerT& pts, std::size_t bucket_size = 32, ScalarT min_extent = 0.0);

			/**
			 * \brief radius neighbor queries where radius determines the maximal radius of reported indices of points in resultIndices.
			 **/
			template <typename Distance, typename IdxOutputIter>
			void radiusNeighbors(const PointT& query, ScalarT radius, IdxOutputIter result_indices) const;

			/** \brief radius neighbor queries with explicit (squared) distance computation. **/
			template <typename Distance, typename IdxOutputIter, typename DistOutputIter>
			void radiusNeighbors(const PointT& query, ScalarT radius, IdxOutputIter result_indices,
								 DistOutputIter distances) const;

			/** 
			 * \brief nearest neighbor queries. Using min_distance >= 0, we explicitly disallow self-matches.
			 * \return index of nearest neighbor n with Distance::compute(query, n) > min_distance and otherwise -1.
			 **/
			template <typename Distance>
			long findNeighbor(const PointT& query, ScalarT min_distance = ScalarT(-1)) const;

		private:
			struct Octant
			{

				// bounding box of the octant needed for overlap and contains tests...
				ScalarT     x, y, z;     // center
				ScalarT     extent;      // half of side-length
				std::size_t start, end;  // start and end in succ_
				std::size_t size;        // number of points
				bool        isLeaf;
				Octant*     child[8];
			};

			typedef boost::shared_ptr<Octant> OctantPtr;

			// not copyable, not assignable ...
			Octree(Octree& oct);

			Octree& operator=(const Octree& oct);

			/**
			 * \brief creation of an octant using the elements starting at startIdx.
			 *
			 * The method reorders the index such that all points are correctly linked to successors belonging
			 * to the same octant.
			 *
			 * \param x,y,z           center coordinates of octant.
			 * \param extent          extent of octant.
			 * \param start_idx       first index of points inside octant.
			 * \param end_idx         last index of points inside octant.
			 * \param size            number of points in octant.
			 *
			 * \return  octant with children nodes.
			 */
			Octant* createOctant(ScalarT x, ScalarT y, ScalarT z, ScalarT extent, std::size_t start_idx, std::size_t end_idx, std::size_t size);

			/** @return true, if search finished, otherwise false. **/
			template <typename Distance>
			bool findNeighbor(const Octant* octant, const PointT& query, ScalarT min_distance, ScalarT& max_distance,
							  long& result_index) const;

			template <typename Distance, typename IdxOutputIter>
			void radiusNeighbors(const Octant* octant, const PointT& query, ScalarT radius, ScalarT sqr_radius,
								 IdxOutputIter& result_indices) const;

			template <typename Distance, typename IdxOutputIter, typename DistOutputIter>
			void radiusNeighbors(const Octant* octant, const PointT& query, ScalarT radius, ScalarT sqr_radius,
								 IdxOutputIter& result_indices, DistOutputIter& distances) const;

			/** \brief test if search ball S(q,r) overlaps with octant
			 *
			 * @param query   query point
			 * @param radius  "squared" radius
			 * @param o       pointer to octant
			 *
			 * @return true, if search ball overlaps with octant, false otherwise.
			 */
			template <typename Distance>
			static bool overlaps(const PointT& query, ScalarT radius, ScalarT sqRadius, const Octant* o);

			/** \brief test if search ball S(q,r) contains octant
			 *
			 * @param query    query point
			 * @param sqRadius "squared" radius
			 * @param octant   pointer to octant
			 *
			 * @return true, if search ball overlaps with octant, false otherwise.
			 */
			template <typename Distance>
			static bool contains(const PointT& query, ScalarT sqRadius, const Octant* octant);

			/** \brief test if search ball S(q,r) is completely inside octant.
			 *
			 * @param query   query point
			 * @param radius  radius r
			 * @param octant  point to octant.
			 *
			 * @return true, if search ball is completely inside the octant, false otherwise.
			 */
			template <typename Distance>
			static bool inside(const PointT& query, ScalarT radius, const Octant* octant);

			typedef std::vector<OctantPtr> AllocOctantList;

			std::size_t              freeOctantIdx;
			AllocOctantList          allocOctants;
			std::size_t              bucketSize;
			ScalarT                  minExtent;
			Octant*                  rootNode;
			const ContainerT*        pointData;
			std::vector<std::size_t> succIndices;  // single connected list of next point indices...
		};


		// Implementation

		template <typename PointT, typename ContainerT, typename ScalarT>
		Octree<PointT, ContainerT, ScalarT>::Octree() : rootNode(0), pointData(0) 
		{}

		template <typename PointT, typename ContainerT, typename ScalarT>
		void Octree<PointT, ContainerT, ScalarT>::initialize(const ContainerT& pts, std::size_t bucket_size, ScalarT min_extent)
		{
			freeOctantIdx = 0;

			pointData = &pts;
			bucketSize = bucket_size;
			minExtent = min_extent;

			const std::size_t num_pts = pts.size();

			succIndices.resize(num_pts);

			// determine axis-aligned bounding box.
			ScalarT min[3], max[3];

			min[0] = pts[0][0];
			min[1] = pts[0][1];
			min[2] = pts[0][2];
			max[0] = min[0];
			max[1] = min[1];
			max[2] = min[2];

			for (std::size_t i = 0; i < num_pts; ++i) {
				// initially each element links simply to the following element.
				succIndices[i] = i + 1;

				const PointT& p = pts[i];

				if (p[0] < min[0]) 
					min[0] = p[0];
				if (p[1] < min[1]) 
					min[1] = p[1];
				if (p[2] < min[2]) 
					min[2] = p[2];
				if (p[0] > max[0]) 
					max[0] = p[0];
				if (p[1] > max[1]) 
					max[1] = p[1];
				if (p[2] > max[2]) 
					max[2] = p[2];
			}

			ScalarT ctr[3] = { min[0], min[1], min[2] };
			ScalarT max_extent = (max[0] - min[0]) / 2;

			ctr[0] += max_extent;

			for (std::size_t i = 1; i < 3; ++i) {
				ScalarT extent = (max[i] - min[i]) / 2;
				ctr[i] += extent;

				if (extent > max_extent) 
					max_extent = extent;
			}

			rootNode = createOctant(ctr[0], ctr[1], ctr[2], max_extent, 0, num_pts - 1, num_pts);
		}

		template <typename PointT, typename ContainerT, typename ScalarT>
		typename Octree<PointT, ContainerT, ScalarT>::Octant* Octree<PointT, ContainerT, ScalarT>::createOctant(ScalarT x, ScalarT y, ScalarT z,
																												ScalarT extent, std::size_t start_idx,
																												std::size_t end_idx, std::size_t size) {
			if (freeOctantIdx >= allocOctants.size()) {
				allocOctants.reserve(freeOctantIdx + 1);

				OctantPtr octant_ptr(new Octant());

				allocOctants.push_back(octant_ptr);
			} 

			Octant* octant = allocOctants[freeOctantIdx++].get();

			for (std::size_t i = 0; i < 8; i++)
				octant->child[i] = 0;

			// For a leaf we don't have to change anything; points are already correctly linked or correctly reordered.
			octant->isLeaf = true;

			octant->x = x;
			octant->y = y;
			octant->z = z;
			octant->extent = extent;

			octant->start = start_idx;
			octant->end = end_idx;
			octant->size = size;

			const ScalarT factor[] =  { ScalarT(-0.5), ScalarT(0.5) };

			// subdivide subset of points and re-link points according to Morton codes
			if (size > bucketSize && extent > 2 * minExtent) {
				octant->isLeaf = false;

				std::size_t child_starts[8] = {};
				std::size_t child_ends[8] = {};
				std::size_t child_sizes[8] = {};

				// re-link disjoint child subsets...
				std::size_t idx = start_idx;

				for (std::size_t i = 0; i < size; ++i) {
					const PointT& p = (*pointData)[idx];

					// determine Morton code for each point...
					std::size_t morton_code = 0;

					if (p[0] > x) 
						morton_code |= 1;
					if (p[1] > y) 
						morton_code |= 2;
					if (p[2] > z) 
						morton_code |= 4;

					// set child starts and update successors...
					if (child_sizes[morton_code] == 0)
						child_starts[morton_code] = idx;
					else
						succIndices[child_ends[morton_code]] = idx;
		    
					child_sizes[morton_code] += 1;

					child_ends[morton_code] = idx;
					idx = succIndices[idx];
				}

				// now, we can create the child nodes...
				ScalarT child_extent = extent / 2;
				bool first_time = true;
				std::size_t last_child_idx = 0;

				for (std::size_t i = 0; i < 8; ++i) {
					if (child_sizes[i] == 0)
						continue;

					ScalarT childX = x + factor[(i & 1) > 0] * extent;
					ScalarT childY = y + factor[(i & 2) > 0] * extent;
					ScalarT childZ = z + factor[(i & 4) > 0] * extent;

					octant->child[i] = createOctant(childX, childY, childZ, child_extent, child_starts[i], child_ends[i], child_sizes[i]);

					if (first_time)
						octant->start = octant->child[i]->start;
					else
						succIndices[octant->child[last_child_idx]->end] =
							octant->child[i]->start;  // we have to ensure that also the child ends link to the next child start.

					last_child_idx = i;
					octant->end = octant->child[i]->end;
					first_time = false;
				}
			}

			return octant;
		}

		template <typename PointT, typename ContainerT, typename ScalarT>
		template <typename Distance, typename IdxOutputIter>
		void Octree<PointT, ContainerT, ScalarT>::radiusNeighbors(const Octant* octant, const PointT& query, ScalarT radius,
																  ScalarT sqr_radius, IdxOutputIter& result_indices) const
		{
			// if search ball S(q,r) contains octant, simply add point indexes.
			if (contains<Distance>(query, sqr_radius, octant)) {
				std::size_t idx = octant->start;
		
				for (std::size_t i = 0; i < octant->size; ++i, ++result_indices) {
					*result_indices = idx;
					idx = succIndices[idx];
				}

				return;  // early pruning.
			}

			if (octant->isLeaf) {
				std::size_t idx = octant->start;
		    
				for (std::size_t i = 0; i < octant->size; ++i) {
					const PointT& p = (*pointData)[idx];
					ScalarT dist = Distance::compute(query, p);
	
					if (dist < sqr_radius)  {
						*result_indices = idx;
						++result_indices;
					}

					idx = succIndices[idx];
				}

				return;
			}

			// check whether child nodes are in range.
			for (std::size_t c = 0; c < 8; ++c) {
				if (octant->child[c] == 0) 
					continue;
		    
				if (!overlaps<Distance>(query, radius, sqr_radius, octant->child[c])) 
					continue;
		    
				radiusNeighbors<Distance>(octant->child[c], query, radius, sqr_radius, result_indices);
			}
		}

		template <typename PointT, typename ContainerT, typename ScalarT>
		template <typename Distance, typename IdxOutputIter, typename DistOutputIter>
		void Octree<PointT, ContainerT, ScalarT>::radiusNeighbors(const Octant* octant, const PointT& query, ScalarT radius,
																  ScalarT sqr_radius, IdxOutputIter& result_indices,
																  DistOutputIter& distances) const
		{
			// if search ball S(q,r) contains octant, simply add point indexes and compute squared distances.
			if (contains<Distance>(query, sqr_radius, octant)) {
				std::size_t idx = octant->start;

				for (std::size_t i = 0; i < octant->size; ++i, ++result_indices, ++distances) {
					*result_indices = idx;
					*distances = Distance::compute(query, (*pointData)[idx]);
					idx = succIndices[idx];
				}

				return;  // early pruning.
			}

			if (octant->isLeaf) {
				std::size_t idx = octant->start;

				for (std::size_t i = 0; i < octant->size; ++i) {
					const PointT& p = (*pointData)[idx];
					ScalarT dist = Distance::compute(query, p);
		
					if (dist < sqr_radius) {
						*result_indices = idx;
						*distances = dist;
						++result_indices;
						++distances;
					}
		    
					idx = succIndices[idx];
				}

				return;
			}

			// check whether child nodes are in range.
			for (std::size_t c = 0; c < 8; ++c) {
				if (octant->child[c] == 0) 
					continue;
		    
				if (!overlaps<Distance>(query, radius, sqr_radius, octant->child[c])) 
					continue;
		    
				radiusNeighbors<Distance>(octant->child[c], query, radius, sqr_radius, result_indices, distances);
			}
		}

		template <typename PointT, typename ContainerT, typename ScalarT>
		template <typename Distance, typename IdxOutputIter>
		void Octree<PointT, ContainerT, ScalarT>::radiusNeighbors(const PointT& query, ScalarT radius,
																  IdxOutputIter result_indices) const
		{
			if (rootNode == 0) 
				return;

			ScalarT sqr_radius = Distance::sqr(radius);  // "squared" radius
			radiusNeighbors<Distance>(rootNode, query, radius, sqr_radius, result_indices);
		}

		template <typename PointT, typename ContainerT, typename ScalarT>
		template <typename Distance, typename IdxOutputIter, typename DistOutputIter>
		void Octree<PointT, ContainerT, ScalarT>::radiusNeighbors(const PointT& query, ScalarT radius,
																  IdxOutputIter result_indices,
																  DistOutputIter distances) const
		{
			if (rootNode == 0) 
				return;

			ScalarT sqr_radius = Distance::sqr(radius);  // "squared" radius
			radiusNeighbors<Distance>(rootNode, query, radius, sqr_radius, result_indices, distances);
		}

		template <typename PointT, typename ContainerT, typename ScalarT>
		template <typename Distance>
		bool Octree<PointT, ContainerT, ScalarT>::overlaps(const PointT& query, ScalarT radius, ScalarT sq_radius, const Octant* o)
		{
			// we exploit the symmetry to reduce the test to testing if its inside the Minkowski sum around the positive quadrant.
			ScalarT x = std::abs(query[0] - o->x);
			ScalarT y = std::abs(query[1] - o->y);
			ScalarT z = std::abs(query[2] - o->z);
			ScalarT max_dist = radius + o->extent;

			// Completely outside, since q' is outside the relevant area.
			if (x > max_dist || y > max_dist || z > max_dist) 
				return false;

			int num_less_extent = (x < o->extent) + (y < o->extent) + (z < o->extent);

			// Checking different cases:

			// a. inside the surface region of the octant.
			if (num_less_extent > 1) 
				return true;

			// b. checking the corner region && edge region.
			x = std::max(x - o->extent, ScalarT(0));
			y = std::max(y - o->extent, ScalarT(0));
			z = std::max(z - o->extent, ScalarT(0));

			return (Distance::norm(x, y, z) < sq_radius);
		}

		template <typename PointT, typename ContainerT, typename ScalarT>
		template <typename Distance>
		bool Octree<PointT, ContainerT, ScalarT>::contains(const PointT& query, ScalarT sq_radius, const Octant* o)
		{
			// we exploit the symmetry to reduce the test to test
			// whether the farthest corner is inside the search ball.
			ScalarT x = std::abs(query[0] - o->x);
			ScalarT y = std::abs(query[1] - o->y);
			ScalarT z = std::abs(query[2] - o->z);

			// reminder: (x, y, z) - (-e, -e, -e) = (x, y, z) + (e, e, e)
			x += o->extent;
			y += o->extent;
			z += o->extent;

			return (Distance::norm(x, y, z) < sq_radius);
		}

		template <typename PointT, typename ContainerT, typename ScalarT>
		template <typename Distance>
		long Octree<PointT, ContainerT, ScalarT>::findNeighbor(const PointT& query, ScalarT min_distance) const
		{
			ScalarT max_distance = std::numeric_limits<ScalarT>::infinity();
			long result_index = -1;

			findNeighbor<Distance>(rootNode, query, min_distance, max_distance, result_index);

			return result_index;
		}

		template <typename PointT, typename ContainerT, typename ScalarT>
		template <typename Distance>
		bool Octree<PointT, ContainerT, ScalarT>::findNeighbor(const Octant* octant, const PointT& query, ScalarT min_distance,
															   ScalarT& max_distance, long& result_index) const
		{
			// 1. first descend to leaf and check in leafs points.
			if (octant->isLeaf)	{
				std::size_t idx = octant->start;
				ScalarT sqr_max_dist = Distance::sqr(max_distance);
				ScalarT sqr_min_dist = (min_distance < 0) ? min_distance : Distance::sqr(min_distance);

				for (std::size_t i = 0; i < octant->size; ++i) {
					const PointT& p = (*pointData)[idx];
					ScalarT dist = Distance::compute(query, p);

					if (dist > sqr_min_dist && dist < sqr_max_dist) {
						result_index = idx;
						sqr_max_dist = dist;
					}
		    
					idx = succIndices[idx];
				}

				max_distance = Distance::sqrt(sqr_max_dist);

				return inside<Distance>(query, max_distance, octant);
			}

			// determine Morton code for each point...
			std::size_t morton_code = 0;

			if (query[0] > octant->x) 
				morton_code |= 1;
			if (query[1] > octant->y) 
				morton_code |= 2;
			if (query[2] > octant->z) 
				morton_code |= 4;

			if (octant->child[morton_code] != 0)	{
				if (findNeighbor<Distance>(octant->child[morton_code], query, min_distance, max_distance, result_index)) 
					return true;
			}

			// 2. if current best point completely inside, just return.
			ScalarT sqr_max_dist = Distance::sqr(max_distance);

			// 3. check adjacent octants for overlap and check these if necessary.
			for (std::size_t c = 0; c < 8; ++c)	{
				if (c == morton_code) 
					continue;
		
				if (octant->child[c] == 0) 
					continue;
		
				if (!overlaps<Distance>(query, max_distance, sqr_max_dist, octant->child[c])) 
					continue;
		
				if (findNeighbor<Distance>(octant->child[c], query, min_distance, max_distance, result_index))
					return true;  // early pruning
			}

			// all children have been checked...check if point is inside the current octant...
			return inside<Distance>(query, max_distance, octant);
		}

		template <typename PointT, typename ContainerT, typename ScalarT>
		template <typename Distance>
		bool Octree<PointT, ContainerT, ScalarT>::inside(const PointT& query, ScalarT radius, const Octant* octant)
		{
			// we exploit the symmetry to reduce the test to test
			// whether the farthest corner is inside the search ball.
			ScalarT x = std::abs(query[0] - octant->x) + radius;
			ScalarT y = std::abs(query[1] - octant->y) + radius;
			ScalarT z = std::abs(query[2] - octant->z) + radius;

			if (x > octant->extent) 
				return false;
			if (y > octant->extent) 
				return false;
			if (z > octant->extent) 
				return false;

			return true;
		}
    }
}

#endif // CDPL_INTERNAL_OCTREE_HPP
