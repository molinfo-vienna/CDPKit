/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * RXNReactionReader.cpp 
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


#include "StaticInit.hpp"

#include <boost/lexical_cast.hpp>

#include "CDPL/Chem/RXNReactionReader.hpp"
#include "CDPL/Chem/Reaction.hpp"
#include "CDPL/Base/Exceptions.hpp"

#include "MDLDataReader.hpp"


using namespace CDPL;


Chem::RXNReactionReader::RXNReactionReader(std::istream& is): 
	Util::StreamDataReader<Reaction, RXNReactionReader>(is), reader(new MDLDataReader(*this)) {}

Chem::RXNReactionReader::~RXNReactionReader() {}

bool Chem::RXNReactionReader::readData(std::istream& is, Reaction& rxn, bool overwrite)
{
	try {
		if (overwrite)
			rxn.clear();

		return reader->readRXNFile(is, rxn);

	} catch (const std::exception& e) {
		throw Base::IOError("RXNReactionReader: while reading record " + boost::lexical_cast<std::string>(getRecordIndex()) + 
							": " + e.what());
	}
}

bool Chem::RXNReactionReader::skipData(std::istream& is)
{
	try {
		return reader->skipRXNFile(is);

	} catch (const std::exception& e) {
		throw Base::IOError("RXNReactionReader: while skipping record " + boost::lexical_cast<std::string>(getRecordIndex()) + 
							": " + e.what());
	}
}

bool Chem::RXNReactionReader::moreData(std::istream& is)
{
	return reader->hasMoreData(is);
}
