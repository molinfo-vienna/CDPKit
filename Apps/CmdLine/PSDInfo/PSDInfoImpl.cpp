/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PSDInfoImpl.cpp
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


#include <cstdlib>
#include <algorithm>
#include <numeric>
#include <functional>
#include <sstream>
#include <iomanip>

#include <boost/lexical_cast.hpp>
#include <boost/bind.hpp>

#include "CDPL/Pharm/PSDScreeningDBAccessor.hpp"
#include "CDPL/Pharm/FeatureTypeHistogram.hpp"
#include "CDPL/Pharm/FeatureType.hpp"
#include "CDPL/Util/FileFunctions.hpp"
#include "CDPL/Base/Exceptions.hpp"

#include "PSDInfoImpl.hpp"


using namespace PSDInfo;


PSDInfoImpl::PSDInfoImpl(): printConfStats(false), printPharmStats(false), printFeatureStats(false)
{
	addOption("input,i", "Database(s) to analyze.", 
			  value<StringList>(&inputDatabases)->multitoken()->required());
	addOption("conf-stats,C", "Print molecule conformation count statistics (default: false).", 
			  value<bool>(&printConfStats)->implicit_value(true));
	addOption("pharm-stats,P", "Print pharmacophore feature count statistics (default: false).", 
			  value<bool>(&printPharmStats)->implicit_value(true));
	addOption("feature-stats,F", "Print feature type statistics (default: false).", 
			  value<bool>(&printFeatureStats)->implicit_value(true));
}

const char* PSDInfoImpl::getProgName() const
{
    return "PSDInfo";
}

const char* PSDInfoImpl::getProgCopyright() const
{
    return "Thomas A. Seidel";
}

const char* PSDInfoImpl::getProgAboutText() const
{
	return "Provides information about the content of pharmacophore-screening databases.";
}

int PSDInfoImpl::process()
{
	printMessage(INFO, getProgTitleString());
	printMessage(INFO, "");

	checkInputFiles();
	printOptionSummary();

	return printStatistics();
}

int PSDInfoImpl::printStatistics()
{
	for (StringList::const_iterator it = inputDatabases.begin(), end = inputDatabases.end(); it != end; ++it) {
		if (termSignalCaught())
			return EXIT_FAILURE;

		printStatistics(*it);
	}

	if (termSignalCaught())
		return EXIT_FAILURE;

	return EXIT_SUCCESS;
}

void PSDInfoImpl::printStatistics(const std::string& db_name)
{
	using namespace CDPL;

	Pharm::PSDScreeningDBAccessor db_acc(db_name);

	std::size_t num_mols = db_acc.getNumMolecules();
	std::size_t num_pharms = db_acc.getNumPharmacophores();

	printMessage(INFO, "Database '" + db_name + "':");
	printMessage(INFO, " Num. Molecules:         " + boost::lexical_cast<std::string>(num_mols));
	printMessage(INFO, " Num. Pharmacophores:    " + boost::lexical_cast<std::string>(num_pharms));

	if ((printConfStats || printPharmStats || printFeatureStats) && num_mols > 0 && num_pharms > 0) {
		printMessage(INFO, "");
		printMessage(INFO, " Statistics:             | Min.      | Avg.      | Max.");
		printMessage(INFO, " ------------------------+-----------+-----------+-----------");
	
		std::ostringstream oss;

		oss << std::fixed << std::setprecision(3);

		if (printConfStats) {
			std::size_t min_confs = 0;
			std::size_t max_confs = 0;
		
			for (std::size_t i = 0; i < num_mols; i++) {
				std::size_t num_confs = db_acc.getNumPharmacophores(i);

				if (i == 0) {
					min_confs = num_confs;
					max_confs = num_confs;
					continue;
				}

				min_confs = std::min(min_confs, num_confs);
				max_confs = std::max(max_confs, num_confs);
			}

			printTableRow(oss, "Mol. Conf. Count", min_confs, double(num_pharms) / num_mols, max_confs);
		}

		if (printPharmStats) {
			std::size_t min_cnt = 0;
			std::size_t max_cnt = 0;
			std::size_t tot_num_ftrs = 0;

			for (std::size_t i = 0; i < num_pharms; i++) {
				const Pharm::FeatureTypeHistogram& ftr_counts = db_acc.getFeatureCounts(i);
				std::size_t num_ftrs = std::accumulate(ftr_counts.getEntriesBegin(), ftr_counts.getEntriesEnd(), std::size_t(0),
													   boost::bind(std::plus<std::size_t>(), _1, 
																   boost::bind(&Pharm::FeatureTypeHistogram::Entry::second, _2)));
				tot_num_ftrs += num_ftrs;

				if (i == 0) {
					min_cnt = num_ftrs;
					max_cnt = num_ftrs;
					continue;
				}

				min_cnt = std::min(min_cnt, num_ftrs);
				max_cnt = std::max(max_cnt, num_ftrs);
			}

			printTableRow(oss, "Pharm. Feature Count", min_cnt, double(tot_num_ftrs) / num_pharms, max_cnt);
		}

		if (printFeatureStats) {
			Pharm::FeatureTypeHistogram min_cnts, max_cnts, avg_cnts;
			unsigned int ftr_types[] = { Pharm::FeatureType::H_BOND_ACCEPTOR, Pharm::FeatureType::H_BOND_DONOR,
										 Pharm::FeatureType::NEGATIVE_IONIZABLE, Pharm::FeatureType::POSITIVE_IONIZABLE,
										 Pharm::FeatureType::AROMATIC, Pharm::FeatureType::HYDROPHOBIC,
			                             Pharm::FeatureType::HALOGEN_BOND_DONOR };

			for (std::size_t i = 0; i < num_pharms; i++) {
				const Pharm::FeatureTypeHistogram& ftr_counts = db_acc.getFeatureCounts(i);

				for (std::size_t j = 0; j < sizeof(ftr_types) / sizeof(unsigned int); j++) {
					unsigned int type = ftr_types[j];
					std::size_t count = ftr_counts[type];

					if (!min_cnts.containsEntry(type)) {
						min_cnts[type] = count;
						max_cnts[type] = count;
						avg_cnts[type] = count;

					} else {
						min_cnts[type] = std::min(count, min_cnts[type]);
						max_cnts[type] = std::max(count, max_cnts[type]);
						avg_cnts[type] += count;
					}
				}
			}

			printTableRow(oss, "HBA Feature Count", min_cnts[Pharm::FeatureType::H_BOND_ACCEPTOR], 
						  double(avg_cnts[Pharm::FeatureType::H_BOND_ACCEPTOR]) / num_pharms, 
						  max_cnts[Pharm::FeatureType::H_BOND_ACCEPTOR]);
			printTableRow(oss, "HBD Feature Count", min_cnts[Pharm::FeatureType::H_BOND_DONOR], 
						  double(avg_cnts[Pharm::FeatureType::H_BOND_DONOR]) / num_pharms, 
						  max_cnts[Pharm::FeatureType::H_BOND_DONOR]);
			printTableRow(oss, "NI Feature Count", min_cnts[Pharm::FeatureType::NEGATIVE_IONIZABLE], 
						  double(avg_cnts[Pharm::FeatureType::NEGATIVE_IONIZABLE]) / num_pharms, 
						  max_cnts[Pharm::FeatureType::NEGATIVE_IONIZABLE]);
			printTableRow(oss, "PI Feature Count", min_cnts[Pharm::FeatureType::POSITIVE_IONIZABLE], 
						  double(avg_cnts[Pharm::FeatureType::POSITIVE_IONIZABLE]) / num_pharms, 
						  max_cnts[Pharm::FeatureType::POSITIVE_IONIZABLE]);
			printTableRow(oss, "AR Feature Count", min_cnts[Pharm::FeatureType::AROMATIC], 
						  double(avg_cnts[Pharm::FeatureType::AROMATIC]) / num_pharms, 
						  max_cnts[Pharm::FeatureType::AROMATIC]);
			printTableRow(oss, "HYD Feature Count", min_cnts[Pharm::FeatureType::HYDROPHOBIC], 
						  double(avg_cnts[Pharm::FeatureType::HYDROPHOBIC]) / num_pharms, 
						  max_cnts[Pharm::FeatureType::HYDROPHOBIC]);
			printTableRow(oss, "XBD Feature Count", min_cnts[Pharm::FeatureType::HALOGEN_BOND_DONOR], 
						  double(avg_cnts[Pharm::FeatureType::HALOGEN_BOND_DONOR]) / num_pharms, 
						  max_cnts[Pharm::FeatureType::HALOGEN_BOND_DONOR]);
		}

		printMessage(INFO, oss.str(), false);
	}
}

void PSDInfoImpl::printTableRow(std::ostream& os, const std::string& stat_type, std::size_t min, double avg, std::size_t max) const
{
	os << ' ' << std::setw(24) << std::left << stat_type << "| " 
	   << std::setw(10) << min << "| " 
	   << std::setw(10) << avg << "| " 
	   << std::setw(10) << max << std::endl;
}

void PSDInfoImpl::checkInputFiles() const
{
	using namespace CDPL;

	StringList::const_iterator it = std::find_if(inputDatabases.begin(), inputDatabases.end(),
												 boost::bind(std::logical_not<bool>(), 
															 boost::bind(Util::fileExists, _1)));
	if (it != inputDatabases.end())
		throw Base::IOError("file '" + *it + "' does not exist");
}

void PSDInfoImpl::printOptionSummary()
{
	printMessage(VERBOSE, "Option Summary:");
	printMessage(VERBOSE, " Input Databases(s):       " + inputDatabases[0]);
	
	for (StringList::const_iterator it = ++inputDatabases.begin(), end = inputDatabases.end(); it != end; ++it)
		printMessage(VERBOSE, std::string(27, ' ') + *it);

	printMessage(VERBOSE, std::string(" Conf. Count Statistics:   ") + (printConfStats ? "Yes" : "No"));
	printMessage(VERBOSE, std::string(" Feature Count Statistics: ") + (printPharmStats ? "Yes" : "No"));
	printMessage(VERBOSE, std::string(" Feature Type Statistics:  ") + (printFeatureStats ? "Yes" : "No"));
	printMessage(VERBOSE, "");
}
