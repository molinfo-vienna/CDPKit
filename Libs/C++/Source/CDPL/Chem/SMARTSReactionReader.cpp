/* 
 * SMARTSReactionReader.cpp 
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

#include "CDPL/Chem/SMARTSReactionReader.hpp"
#include "CDPL/Chem/Reaction.hpp"
#include "CDPL/Base/Exceptions.hpp"

#include "SMARTSDataReader.hpp"


using namespace CDPL;


Chem::SMARTSReactionReader::SMARTSReactionReader(std::istream& is): 
	Util::StreamDataReader<Reaction, SMARTSReactionReader>(is), reader(new SMARTSDataReader(*this)) {}

Chem::SMARTSReactionReader::~SMARTSReactionReader() {}

bool Chem::SMARTSReactionReader::readData(std::istream& is, Reaction& rxn, bool overwrite)
{
	try {
		if (overwrite)
			rxn.clear();

		return reader->readReaction(is, rxn);

	} catch (const std::exception& e) {
		throw Base::IOError("SMARTSReactionReader: while reading record " + std::to_string(getRecordIndex()) + 
							": " + e.what());
	}
}

bool Chem::SMARTSReactionReader::skipData(std::istream& is)
{
	try {
		return reader->skipReaction(is);

	} catch (const std::exception& e) {
		throw Base::IOError("SMARTSReactionReader: while skipping record " + std::to_string(getRecordIndex()) + 
							": " + e.what());
	}
}

bool Chem::SMARTSReactionReader::moreData(std::istream& is)
{
	return reader->hasMoreData(is);
}
