/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FragmentConformerCache.hpp 
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
 * \brief Definition of the class CDPL::ConfGen::FragmentConformerCache.
 */

#ifndef CDPL_CONFGEN_FRAGMENTCONFORMERCACHE_HPP
#define CDPL_CONFGEN_FRAGMENTCONFORMERCACHE_HPP

#include <cstddef>
#include <unordered_map>

#include <boost/thread.hpp>

#include "CDPL/ConfGen/ConformerDataArray.hpp"
#include "CDPL/Base/IntegerTypes.hpp"


namespace CDPL 
{

    namespace ConfGen 
    {

		class FragmentConformerCache
		{
	    
		public:
			static const ConformerDataArray* getEntry(Base::uint64 frag_hash);

			static void addEntry(Base::uint64 frag_hash, 
								 const ConformerDataArray::const_iterator& confs_beg, 
								 const ConformerDataArray::const_iterator& confs_end);

			static boost::mutex& getMutex();

		private:
			struct Entry
			{

				Base::uint64       fragHash;
				ConformerDataArray conformers;
				Entry*             previous;
				Entry*             next;
			};

			FragmentConformerCache();
			FragmentConformerCache(const FragmentConformerCache& cache);

			~FragmentConformerCache();

			FragmentConformerCache& operator=(const FragmentConformerCache& cache);

			static FragmentConformerCache& getInstance();
			static void createInstance();
	    
			typedef std::unordered_map<Base::uint64, Entry*> HashToCacheEntryMap;

			static FragmentConformerCache* instance;
			static boost::once_flag        onceFlag;
			ConformerDataArray             confDataCache;
			HashToCacheEntryMap            hashToEntryMap;
			Entry*                         lruListHead;
			std::size_t                    numEntries;
			boost::mutex                   mutex;
		};
    }
}

#endif // CDPL_CONFGEN_FRAGMENTCONFORMERCACHE_HPP
