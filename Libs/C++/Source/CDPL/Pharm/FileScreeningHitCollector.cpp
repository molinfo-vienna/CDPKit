/* 
 * FileScreeningHitCollector.cpp 
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

#include <string>
#include <algorithm>

#include <boost/filesystem.hpp>

#include "CDPL/Pharm/FileScreeningHitCollector.hpp"
#include "CDPL/Pharm/ScreeningDBAccessor.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/AtomContainerFunctions.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/Entity3DContainerFunctions.hpp"
#include "CDPL/Math/VectorArrayFunctions.hpp"
#include "CDPL/Base/DataWriter.hpp"


using namespace CDPL;


namespace
{

    const std::string SCORE_PROPERTY_NAME      = "<Score>";
    const std::string DB_NAME_PROPERTY_NAME    = "<Source Database>";
    const std::string MOL_INDEX_PROPERTY_NAME  = "<Molecule Index>";
    const std::string CONF_INDEX_PROPERTY_NAME = "<Conformation Index>";
}


Pharm::FileScreeningHitCollector::FileScreeningHitCollector(MolecularGraphWriter& writer):
    dataWriter(&writer), alignMolecule(true), optScore(true), optDBName(true), 
    optMolIndex(true), optConfIndex(false)
{}

void Pharm::FileScreeningHitCollector::setDataWriter(MolecularGraphWriter& writer)
{
    dataWriter = &writer;
}

Pharm::FileScreeningHitCollector::MolecularGraphWriter& Pharm::FileScreeningHitCollector::getDataWriter() const
{
    return *dataWriter;
}

void Pharm::FileScreeningHitCollector::alignHitMolecule(bool align)
{
    alignMolecule = align;
}

bool Pharm::FileScreeningHitCollector::alignHitMolecule() const
{
    return alignMolecule;
}

void Pharm::FileScreeningHitCollector::outputScoreProperty(bool output)
{
    optScore = output;
}

bool Pharm::FileScreeningHitCollector::outputScoreProperty() const
{
    return optScore;
}

void Pharm::FileScreeningHitCollector::outputDBNameProperty(bool output)
{
    optDBName = output;
}

bool Pharm::FileScreeningHitCollector::outputDBNameProperty() const
{
    return optDBName;
}

void Pharm::FileScreeningHitCollector::outputDBMoleculeIndexProperty(bool output)
{
    optMolIndex = output;
}

bool Pharm::FileScreeningHitCollector::outputDBMoleculeIndexProperty() const
{
    return optMolIndex;
}
    
void Pharm::FileScreeningHitCollector::outputMoleculeConfIndexProperty(bool output)
{
    optConfIndex = output;
}

bool Pharm::FileScreeningHitCollector::outputMoleculeConfIndexProperty() const
{
    return optConfIndex;
}

bool Pharm::FileScreeningHitCollector::operator()(const ScreeningProcessor::SearchHit& hit, double score)
{
    molecule.copy(hit.getHitMolecule());

    if (alignMolecule) {
        alignedCoords.clear();

        getConformation(molecule, hit.getHitConformationIndex(), alignedCoords);

        transform(alignedCoords, hit.getHitAlignmentTransform());

        set3DCoordinates(molecule, alignedCoords);
    
    } else
        applyConformation(molecule, hit.getHitConformationIndex());

    std::for_each(molecule.getAtomsBegin(), molecule.getAtomsEnd(), &Chem::clear3DCoordinatesArray);
    
    perceiveSSSR(molecule, true);

    perceiveAtomStereoCenters(molecule, false, false);
    perceiveBondStereoCenters(molecule, false, false);
    calcAtomStereoDescriptors(molecule, true, 3);
    calcBondStereoDescriptors(molecule, true, 3);

    Chem::StringDataBlock::SharedPointer struc_data;

    if (hasStructureData(molecule))  
        struc_data.reset(new Chem::StringDataBlock(*getStructureData(molecule)));
    else
        struc_data.reset(new Chem::StringDataBlock());

    if (optScore)
        struc_data->addEntry(SCORE_PROPERTY_NAME, 
                             std::to_string(score));

    if (optDBName)
        struc_data->addEntry(DB_NAME_PROPERTY_NAME, 
                             boost::filesystem::path(hit.getHitProvider().getDBAccessor().getDatabaseName()).filename().string());

    if (optMolIndex) {
        struc_data->addEntry(MOL_INDEX_PROPERTY_NAME, 
                             std::to_string(hit.getHitMoleculeIndex()));
    }

    if (optConfIndex)
        struc_data->addEntry(CONF_INDEX_PROPERTY_NAME, 
                             std::to_string(hit.getHitConformationIndex()));

    setStructureData(molecule, struc_data);
    dataWriter->write(molecule);

    return true;
}
