/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FragmentConformerCache.cpp 
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


#include "StaticInit.hpp"

#include "FragmentConformerCache.hpp"


using namespace CDPL;


namespace
{

    const std::size_t MAX_CACHE_SIZE = 10000;
}


ConfGen::FragmentConformerCache* ConfGen::FragmentConformerCache::instance = 0;

boost::once_flag ConfGen::FragmentConformerCache::onceFlag = BOOST_ONCE_INIT;


ConfGen::FragmentConformerCache::FragmentConformerCache():
    lruListHead(0), numEntries(0)
{}

ConfGen::FragmentConformerCache::~FragmentConformerCache() 
{}

const ConfGen::ConformerDataArray* ConfGen::FragmentConformerCache::getEntry(Base::uint64 frag_hash)
{
    FragmentConformerCache& inst = getInstance();
    HashToCacheEntryMap::const_iterator it = inst.hashToEntryMap.find(frag_hash);

    if (it == inst.hashToEntryMap.end())
		return 0;

	Entry* entry = it->second;

	// unlink entry
	entry->previous->next = entry->next;
	entry->next->previous = entry->previous;

	// insert entry before current head of the LRU list  
	entry->next = inst.lruListHead;
	entry->previous = inst.lruListHead->previous;
	entry->previous->next = entry;
	inst.lruListHead->previous = entry;
	
	// make entry new head of the LRU list  
	inst.lruListHead = entry;

    return &entry->conformers;
}

void ConfGen::FragmentConformerCache::addEntry(Base::uint64 frag_hash, 
											   const ConformerDataArray::const_iterator& confs_beg, 
											   const ConformerDataArray::const_iterator& confs_end)
{
    FragmentConformerCache& inst = getInstance();
    HashToCacheEntryMap::const_iterator it = inst.hashToEntryMap.find(frag_hash);

    if (it != inst.hashToEntryMap.end())
		return;

	std::ptrdiff_t num_new_confs = confs_end - confs_beg;

	if (num_new_confs <= 0) // sanity check
		return;

	if (!inst.lruListHead) { // create first entry
		Entry* new_entry = new Entry();

		new_entry->next = new_entry;
		new_entry->previous = new_entry;

		inst.lruListHead = new_entry;
		inst.numEntries = 1;

	} else if (inst.numEntries < MAX_CACHE_SIZE) { // add new entry
		Entry* new_entry = new Entry();

		new_entry->next = inst.lruListHead;
		new_entry->previous = inst.lruListHead->previous;
		new_entry->previous->next = new_entry;
		inst.lruListHead->previous = new_entry;

		inst.numEntries++;

    } else // reuse old entry at LRU list tail
		inst.hashToEntryMap.erase(inst.lruListHead->previous->fragHash);
    
	Entry* entry = inst.lruListHead->previous;

	entry->fragHash = frag_hash;
	entry->conformers.reserve(num_new_confs);

	while (entry->conformers.size() > std::size_t(num_new_confs)) {
		inst.confDataCache.push_back(entry->conformers.back());
		entry->conformers.pop_back();
	}

	while (entry->conformers.size() < std::size_t(num_new_confs)) {
		if (inst.confDataCache.empty()) 
			entry->conformers.push_back(ConformerData::SharedPointer(new ConformerData()));

		else {
			entry->conformers.push_back(inst.confDataCache.back());
			inst.confDataCache.pop_back();
		}
	}

	for (ConformerDataArray::const_iterator src_it = confs_beg, tgt_it = entry->conformers.begin(); src_it != confs_end; ++src_it, ++tgt_it)
		(*src_it)->swap(**tgt_it);

	inst.hashToEntryMap.insert(HashToCacheEntryMap::value_type(frag_hash, entry));
	inst.lruListHead = entry;
}

boost::mutex& ConfGen::FragmentConformerCache::getMutex()
{
    return getInstance().mutex;
}

void ConfGen::FragmentConformerCache::createInstance() 
{
    instance = new FragmentConformerCache();
}

ConfGen::FragmentConformerCache& ConfGen::FragmentConformerCache::getInstance() 
{
    boost::call_once(&createInstance, onceFlag);

    return *instance;
}
