/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PSDMergeImpl.cpp
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


#include <cstdlib>
#include <algorithm>

#include <boost/algorithm/string.hpp>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>

#include "CDPL/Pharm/PSDScreeningDBCreator.hpp"
#include "CDPL/Pharm/PSDScreeningDBAccessor.hpp"
#include "CDPL/Util/FileFunctions.hpp"
#include "CDPL/Base/Exceptions.hpp"

#include "Lib/HelperFunctions.hpp"

#include "PSDMergeImpl.hpp"


using namespace PSDMerge;


struct PSDMergeImpl::MergeDBsProgressCallback
{

	MergeDBsProgressCallback(PSDMergeImpl* parent, double offset, double scale): 
		parent(parent), offset(offset), scale(scale) {}

	bool operator()(double progress) const {
		if (PSDMergeImpl::termSignalCaught())
			return false;

		parent->printProgress("Merging Databases... ", offset + scale * progress);
		return true;
	}

	PSDMergeImpl* parent;
	double         offset;
	double         scale;
};


PSDMergeImpl::PSDMergeImpl(): 
	dropDuplicates(false), creationMode(CDPL::Pharm::ScreeningDBCreator::APPEND)
{
	addOption("input,i", "Input database file(s).", 
			  value<StringList>(&inputDatabases)->multitoken()->required());
	addOption("output,o", "Output database file.", 
			  value<std::string>(&outputDatabase)->required());
	addOption("mode,m", "Database merge mode (CREATE, APPEND, UPDATE, default: APPEND).", 
			  value<std::string>()->notifier(boost::bind(&PSDMergeImpl::setCreationMode, this, _1)));
	addOption("drop-duplicates,d", "Drop duplicate molecules (default: false).", 
			  value<bool>(&dropDuplicates)->implicit_value(true));
}

const char* PSDMergeImpl::getProgName() const
{
    return "PSDMerge";
}

const char* PSDMergeImpl::getProgCopyright() const
{
    return "Thomas A. Seidel";
}

const char* PSDMergeImpl::getProgAboutText() const
{
	return "Merges multiple pharmacophore-screening databases into a single database.";
}

void PSDMergeImpl::setCreationMode(const std::string& mode)
{
	using namespace CDPL::Pharm;

	std::string uc_mode = mode;
	boost::to_upper(uc_mode);

	if (uc_mode == "CREATE")
		creationMode = ScreeningDBCreator::CREATE;
	else if (uc_mode == "APPEND")
		creationMode = ScreeningDBCreator::APPEND;
	else if (uc_mode == "UPDATE")
		creationMode = ScreeningDBCreator::UPDATE;
	else
		throwValidationError("mode");
}

int PSDMergeImpl::process()
{
	startTime = Clock::now();

	printMessage(INFO, getProgTitleString());
	printMessage(INFO, "");

	checkInputFiles();
	printOptionSummary();

	return mergeDatabases();
}

int PSDMergeImpl::mergeDatabases()
{
	using namespace CDPL;

	typedef std::vector<Pharm::ScreeningDBAccessor::SharedPointer> DBAccessorList;

	std::size_t num_mols = 0;
	std::size_t num_pharms = 0;
	DBAccessorList db_accessors;

	printMessage(INFO, "Analyzing Input Databases...");

	for (std::size_t i = 0; i < inputDatabases.size(); i++) {
		if (termSignalCaught())
			return EXIT_FAILURE;

		Pharm::ScreeningDBAccessor::SharedPointer db_acc(new Pharm::PSDScreeningDBAccessor(inputDatabases[i]));

		num_pharms += db_acc->getNumPharmacophores();
		num_mols += db_acc->getNumMolecules();

		db_accessors.push_back(db_acc);
	}

	if (termSignalCaught())
		return EXIT_FAILURE;

	printMessage(INFO, " - Found " + boost::lexical_cast<std::string>(num_mols) + " Molecules/" +
				 boost::lexical_cast<std::string>(num_pharms) + " Pharmacophores");
	printMessage(INFO, "");

	Pharm::PSDScreeningDBCreator db_creator(outputDatabase, creationMode, !dropDuplicates);

	if (progressEnabled()) {
		initProgress();
		printMessage(INFO, "Merging Databases...", true, true); 
	} else
		printMessage(INFO, "Merging Databases..."); 

	for (std::size_t i = 0; i < inputDatabases.size(); i++) {
		if (termSignalCaught())
			return EXIT_FAILURE;

		db_creator.merge(*db_accessors[i], 
						 MergeDBsProgressCallback(this, i * 1.0 / inputDatabases.size(), 
												  1.0 / inputDatabases.size()));
	}

	printMessage(INFO, "");

	if (termSignalCaught())
		return EXIT_FAILURE;

	printStatistics(db_creator.getNumProcessed(), db_creator.getNumRejected(),
					db_creator.getNumDeleted(), db_creator.getNumInserted(),
					boost::chrono::duration_cast<boost::chrono::duration<std::size_t> >(Clock::now() - startTime).count());

	return EXIT_SUCCESS;
}

void PSDMergeImpl::printStatistics(std::size_t num_proc, std::size_t num_rej, 
								   std::size_t num_del, std::size_t num_ins,
								   std::size_t proc_time)
{
	printMessage(INFO, "Statistics:");
	printMessage(INFO, " Processed Molecules: " + boost::lexical_cast<std::string>(num_proc));
	printMessage(INFO, " Rejected  Molecules: " + boost::lexical_cast<std::string>(num_rej));
	printMessage(INFO, " Deleted Molecules:   " + boost::lexical_cast<std::string>(num_del));
	printMessage(INFO, " Inserted Molecules:  " + boost::lexical_cast<std::string>(num_ins));
	printMessage(INFO, " Processing Time:     " + AppUtils::formatTimeDuration(proc_time));
}

void PSDMergeImpl::checkInputFiles() const
{
	using namespace CDPL;

	StringList::const_iterator it = std::find_if(inputDatabases.begin(), inputDatabases.end(),
												 boost::bind(std::logical_not<bool>(), 
															 boost::bind(Util::fileExists, _1)));
	if (it != inputDatabases.end())
		throw Base::IOError("file '" + *it + "' does not exist");
			
														 
	if (std::find_if(inputDatabases.begin(), inputDatabases.end(),
					 boost::bind(Util::checkIfSameFile, boost::ref(outputDatabase),
								 _1)) != inputDatabases.end())
		throw Base::ValueError("output file must not occur in list of input files");
}

void PSDMergeImpl::printOptionSummary()
{
	printMessage(VERBOSE, "Option Summary:");
	printMessage(VERBOSE, " Input Databases(s):       " + inputDatabases[0]);
	
	for (StringList::const_iterator it = ++inputDatabases.begin(), end = inputDatabases.end(); it != end; ++it)
		printMessage(VERBOSE, std::string(27, ' ') + *it);

	printMessage(VERBOSE, " Output Database:          " + outputDatabase);
 	printMessage(VERBOSE, " Creation Mode:            " + getModeString());
 	printMessage(VERBOSE, " Drop Duplicates:          " + std::string(dropDuplicates ? "Yes" : "No"));
	printMessage(VERBOSE, "");
}

std::string PSDMergeImpl::getModeString() const
{
	using namespace CDPL;

	if (creationMode == Pharm::ScreeningDBCreator::CREATE)
		return "CREATE";

	if (creationMode == Pharm::ScreeningDBCreator::APPEND)
		return "APPEND";

	if (creationMode == Pharm::ScreeningDBCreator::UPDATE)
		return "UPDATE";
	
	return "UNKNOWN";
}
