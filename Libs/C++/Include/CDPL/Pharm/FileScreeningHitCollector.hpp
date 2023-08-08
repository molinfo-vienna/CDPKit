/* 
 * FileScreeningHitCollector.hpp 
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
 * \brief Definition of the class CDPL::Pharm::FileScreeningHitCollector.
 */

#ifndef CDPL_PHARM_FILESCREENINGHITCOLLECTOR_HPP
#define CDPL_PHARM_FILESCREENINGHITCOLLECTOR_HPP

#include "CDPL/Pharm/APIPrefix.hpp"
#include "CDPL/Pharm/ScreeningProcessor.hpp"
#include "CDPL/Chem/BasicMolecule.hpp"
#include "CDPL/Math/VectorArray.hpp"


namespace CDPL
{

    namespace Base
    {

        template <typename T>
        class DataWriter;
    }

    namespace Pharm
    {

        /**
         * \brief FileScreeningHitCollector.
         */
        class CDPL_PHARM_API FileScreeningHitCollector
        {

          public:
            typedef Base::DataWriter<Chem::MolecularGraph> MolecularGraphWriter;

            FileScreeningHitCollector(MolecularGraphWriter& writer);

            void setDataWriter(MolecularGraphWriter& writer);

            MolecularGraphWriter& getDataWriter() const;

            void alignHitMolecule(bool align);

            bool alignHitMolecule() const;

            void outputScoreProperty(bool output);

            bool outputScoreProperty() const;

            void outputDBNameProperty(bool output);

            bool outputDBNameProperty() const;

            void outputDBMoleculeIndexProperty(bool output);

            bool outputDBMoleculeIndexProperty() const;

            void outputMoleculeConfIndexProperty(bool output);

            bool outputMoleculeConfIndexProperty() const;

            bool operator()(const ScreeningProcessor::SearchHit& hit, double score);

          private:
            MolecularGraphWriter* dataWriter;
            bool                  alignMolecule;
            bool                  optScore;
            bool                  optDBName;
            bool                  optMolIndex;
            bool                  optConfIndex;
            Math::Vector3DArray   alignedCoords;
            Chem::BasicMolecule   molecule;
        };
    } // namespace Pharm
} // namespace CDPL

#endif // CDPL_PHARM_FILESCREENINGHITCOLLECTOR_HPP
