/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PSDMolecularGraphWriter.cpp 
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


#include "StaticInit.hpp"

#include <fstream>

#include <boost/filesystem.hpp>
#include <boost/iostreams/copy.hpp>

#include "CDPL/Pharm/PSDMolecularGraphWriter.hpp"
#include "CDPL/Pharm/ControlParameterFunctions.hpp"
#include "CDPL/Base/Exceptions.hpp"


using namespace CDPL;


Pharm::PSDMolecularGraphWriter::PSDMolecularGraphWriter(std::iostream& ios): 
	output(&ios), outputPos(ios.tellp()), dbOpen(false), state(true)
{
	try {
		boost::filesystem::path tmp_file = boost::filesystem::temp_directory_path() / boost::filesystem::unique_path();

		tmpFile = tmp_file.native();
		dbFile = tmpFile;

		std::ofstream tmp_fs(tmpFile.c_str());

		boost::iostreams::copy(ios, tmp_fs);

		if (!ios.good() || !tmp_fs.good())
			throw Base::IOError("copying input data failed");

	} catch (const std::exception& e) {
		removeTmpFile();
		throw Base::IOError(std::string("PSDMolecularGraphWriter: could not create temporary database file: ") + e.what());
	}
}

Pharm::PSDMolecularGraphWriter::PSDMolecularGraphWriter(const std::string& file_name):
	output(0), dbFile(file_name), dbOpen(false), state(true)
{}

Pharm::PSDMolecularGraphWriter::~PSDMolecularGraphWriter() 
{
	try { close(); } catch (...) {}
	removeTmpFile();
}

Pharm::PSDMolecularGraphWriter& Pharm::PSDMolecularGraphWriter::write(const Chem::MolecularGraph& molgraph)
{
	state = false;

	if (!dbOpen) {
		try {
			creator.open(dbFile, getPSDCreationModeParameter(*this), 
						 getPSDAllowDuplicatesParameter(*this));
			dbOpen = true;

		} catch (const std::exception& e) {
			throw Base::IOError(std::string("PSDMolecularGraphWriter: could not open database: ") + e.what());
		}
	}

	try {
		creator.process(molgraph);

	} catch (const std::exception& e) {
		throw Base::IOError(std::string("PSDMolecularGraphWriter: could not write record: ") + e.what());
	}

	state = true;

	invokeIOCallbacks(1.0);

    return *this;
}

void Pharm::PSDMolecularGraphWriter::close()
{
	state = false;

	try {
		if (dbOpen) {
			creator.close();
			dbOpen = false;
		}

		if (!tmpFile.empty()) {
			std::ifstream tmp_fs(tmpFile.c_str());

			output->seekp(outputPos);
			boost::iostreams::copy(tmp_fs, *output);

			if (!output->good() || !tmp_fs.good())
				throw Base::IOError("copying of temporary database file failed");
		}

	} catch (const std::exception& e) {
		throw Base::IOError(std::string("PSDMolecularGraphWriter: could not close database: ") + e.what());
	}

	state = true;
}

Pharm::PSDMolecularGraphWriter::operator const void*() const
{
    return (state ? this : 0);
}

bool Pharm::PSDMolecularGraphWriter::operator!() const
{
    return !state;
}

void Pharm::PSDMolecularGraphWriter::removeTmpFile()
{
	try {
		if (!tmpFile.empty())
			boost::filesystem::remove(tmpFile);
	} catch (...) {}
}
