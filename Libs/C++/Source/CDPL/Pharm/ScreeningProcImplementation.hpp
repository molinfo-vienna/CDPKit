/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ScreeningProcImplementation.hpp 
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


#ifndef CDPL_PHARM_SCREENINGPROCIMPLEMENTATION_HPP
#define CDPL_PHARM_SCREENINGPROCIMPLEMENTATION_HPP

#include <vector>
#include <utility>

#include <boost/iterator/indirect_iterator.hpp>

#include "CDPL/Pharm/ScreeningProcessor.hpp"
#include "CDPL/Pharm/PharmacophoreAlignment.hpp"
#include "CDPL/Pharm/FeatureTypeHistogram.hpp"
#include "CDPL/Pharm/BasicPharmacophore.hpp"
#include "CDPL/Pharm/FeatureGeometryMatchFunctor.hpp"
#include "CDPL/Pharm/QueryTwoPointPharmacophore.hpp"
#include "CDPL/Pharm/TwoPointPharmacophoreGenerator.hpp"
#include "CDPL/Pharm/TwoPointPharmacophoreSet.hpp"
#include "CDPL/Chem/BasicMolecule.hpp"
#include "CDPL/Math/Matrix.hpp"
#include "CDPL/Math/Vector.hpp"
#include "CDPL/Math/VectorArray.hpp"
#include "CDPL/Util/BitSet.hpp"


namespace CDPL 
{

    namespace Pharm
    {
	
	class ScreeningDBAccessor;
	class FeatureMapping;

	class ScreeningProcImplementation
	{

	    typedef ScreeningProcessor::HitCallbackFunction HitCallbackFunction;
	    typedef ScreeningProcessor::ProgressCallbackFunction ProgressCallbackFunction;
	    typedef ScreeningProcessor::ScoringFunction ScoringFunction;
	    typedef ScreeningProcessor::SearchHit SearchHit;

	public:
	    ScreeningProcImplementation(ScreeningProcessor& parent, ScreeningDBAccessor& db_acc);

	    void setDBAccessor(ScreeningDBAccessor& db_acc);

	    ScreeningDBAccessor& getDBAccessor() const;

	    void setHitReportMode(ScreeningProcessor::HitReportMode mode);

	    ScreeningProcessor::HitReportMode getHitReportMode() const;

	    void setMaxNumOmittedFeatures(std::size_t max_num);

	    std::size_t getMaxNumOmittedFeatures() const;

	    void checkXVolumeClashes(bool check);

	    bool xVolumeClashesChecked() const;

	    void seekBestAlignments(bool seek_best);

	    bool bestAlignmentsSeeked() const;

	    void setHitCallbackFunction(const HitCallbackFunction& func);

	    const HitCallbackFunction& getHitCallbackFunction() const;

	    void setProgressCallbackFunction(const ProgressCallbackFunction& func);

	    const ProgressCallbackFunction& getProgressCallbackFunction() const;

	    void setScoringFunction(const ScoringFunction& func);

	    const ScoringFunction& getScoringFunction() const;

	    std::size_t searchDB(const Pharmacophore& query, std::size_t mol_start_idx, std::size_t mol_end_idx);

	private:
	    typedef std::vector<QueryTwoPointPharmacophore> TwoPointPharmacophoreList;
	    typedef std::vector<const Feature*> FeatureList;
	    typedef std::vector<FeatureList> FeatureMatrix;
	    typedef std::pair<std::size_t, std::size_t> IndexPair;
	    typedef std::pair<Math::Vector3D, double> PosAndRadiusPair;
	    typedef std::vector<IndexPair> IndexPairList;
	    typedef std::vector<PosAndRadiusPair> PosAndRadiusTable;
	    typedef std::vector<unsigned int> FeatureTypeTable;
	    typedef std::vector<double> RadiusTable;

	    typedef TwoPointPharmacophoreGenerator<TwoPointPharmacophore> DB2PointPharmGenerator;
	    typedef TwoPointPharmacophoreGenerator<QueryTwoPointPharmacophore> Query2PointPharmGenerator;

	    typedef boost::indirect_iterator<FeatureList::const_iterator, const Feature> FeatureListIterator;

	    struct IndexPair2ndCmpFunc
	    {

		bool operator()(const IndexPair& p1, const IndexPair& p2) const {
		    return (p1.second < p2.second);
		}
	    };

	    void prepareDBSearch(const Pharmacophore& query, std::size_t mol_start_idx, std::size_t mol_end_idx);

	    void initQueryData(const Pharmacophore& query);
	    void initPharmIndexList(std::size_t mol_start_idx, std::size_t mol_end_idx);

	    void insertFeature(const Feature& ftr, FeatureMatrix& ftr_mtx) const;

	    bool checkFeatureCounts(std::size_t pharm_idx) const;
	    bool check2PointPharmacophores(std::size_t pharm_idx);
	    bool performAlignment(std::size_t pharm_idx, std::size_t mol_idx);

	    bool checkGeomAlignment();
	    bool checkXVolumeClashes(std::size_t mol_idx, std::size_t conf_idx);

	    bool checkTopologicalMapping(const FeatureMapping& mapping) const;

	    double calcScore(const SearchHit& hit);

	    void loadPharmacophore(std::size_t pharm_idx);
	    void loadMolecule(std::size_t mol_idx);

	    bool processHit(const SearchHit& hit, double score);
	    bool reportHit(const SearchHit& hit, double score);

	    ScreeningProcessor*                   parent;
	    ScreeningDBAccessor*                  dbAccessor;
	    ScreeningProcessor::HitReportMode     reportMode;
	    std::size_t                           maxOmittedFeatures;
	    bool                                  checkXVolumes;
	    bool                                  bestAlignments;
	    HitCallbackFunction                   hitCallback;
	    ProgressCallbackFunction              progressCallback;
	    ScoringFunction                       scoringFunction;
	    FeatureGeometryMatchFunctor           ftrGeomMatchFunction;
	    const Pharmacophore*                  queryPharmacophore;
	    BasicPharmacophore                    dbPharmacophore;
	    Chem::BasicMolecule                   dbMolecule;
	    PharmacophoreAlignment                pharmAlignment;
	    Query2PointPharmGenerator             query2PointPharmGen;
	    DB2PointPharmGenerator                db2PointPharmGen;
	    FeatureTypeHistogram                  queryFeatureCounts; 
	    TwoPointPharmacophoreList             query2PointPharmList;
	    TwoPointPharmacophoreSet              db2PointPharmSet;
	    std::size_t                           minNum2PointPharmMatches;
	    FeatureMatrix                         mandFeatures;
	    PosAndRadiusTable                     mandFtrPosAndRadii;
	    FeatureTypeTable                      mandFeatureTypes;
	    FeatureMatrix                         optFeatures;
	    PosAndRadiusTable                     xVolumePosAndRadii;
	    FeatureList                           alignedMandFeatures;
	    FeatureList                           alignedOptFeatures;
	    Math::Vector3DArray                   atomCoordinates;
	    RadiusTable                           atomVdWRadii;
	    Math::Vector3DArray                   dbPharmFtrPositions;
	    FeatureTypeTable                      dbPharmFtrTypes;
	    IndexPairList                         pharmIndices;  
	    Util::BitSet                          molHitSet;
	    std::size_t                           numHits;
	    std::size_t                           loadedPharmIndex;
	    std::size_t                           loadedMolIndex;
	    Math::Matrix4D                        bestAlmntTransform;
	    Math::Matrix4D                        bestConfAlmntTransform;
	    std::size_t                           bestConfAlmntMolIdx;
	    std::size_t                           bestConfAlmntConfIdx;
	    std::size_t                           bestConfAlmntPharmIdx;
	    double                                bestConfAlmntScore;
	};
    }
}

#endif // CDPL_PHARM_SCREENINGPROCIMPLEMENTATION_HPP
