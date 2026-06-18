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
 * \brief Definition of class CDPL::Pharm::FileScreeningHitCollector.
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
         * \brief Hit-callback functor for use with Pharm::ScreeningProcessor that writes each accepted hit molecule
         *        (optionally aligned and annotated with score/database properties) to a Base::DataWriter sink.
         */
        class CDPL_PHARM_API FileScreeningHitCollector
        {

          public:
            /**
             * \brief Type of the underlying molecular graph data writer.
             */
            typedef Base::DataWriter<Chem::MolecularGraph> MolecularGraphWriter;

            /**
             * \brief Constructs the \c %FileScreeningHitCollector instance.
             * \param writer The molecular graph writer used to output hit molecules.
             */
            FileScreeningHitCollector(MolecularGraphWriter& writer);

            /**
             * \brief Specifies the molecular graph writer used to output hit molecules.
             * \param writer The data writer.
             */
            void setDataWriter(MolecularGraphWriter& writer);

            /**
             * \brief Returns the currently configured molecular graph writer.
             * \return A reference to the data writer.
             */
            MolecularGraphWriter& getDataWriter() const;

            /**
             * \brief Specifies whether the hit molecule's coordinates shall be transformed by the alignment matrix before writing.
             * \param align \c true to align the hit molecule, and \c false to write the original coordinates.
             */
            void alignHitMolecule(bool align);

            /**
             * \brief Tells whether the hit molecule is aligned before writing.
             * \return \c true if alignment is performed, and \c false otherwise.
             */
            bool alignHitMolecule() const;

            /**
             * \brief Specifies whether the alignment score shall be written as a molecule property.
             * \param output \c true to write the score property, and \c false to skip it.
             */
            void outputScoreProperty(bool output);

            /**
             * \brief Tells whether the alignment score is written as a molecule property.
             * \return \c true if the score property is written, and \c false otherwise.
             */
            bool outputScoreProperty() const;

            /**
             * \brief Specifies whether the source-database name shall be written as a molecule property.
             * \param output \c true to write the database-name property, and \c false to skip it.
             */
            void outputDBNameProperty(bool output);

            /**
             * \brief Tells whether the source-database name is written as a molecule property.
             * \return \c true if the database-name property is written, and \c false otherwise.
             */
            bool outputDBNameProperty() const;

            /**
             * \brief Specifies whether the source-database molecule index shall be written as a molecule property.
             * \param output \c true to write the molecule-index property, and \c false to skip it.
             */
            void outputDBMoleculeIndexProperty(bool output);

            /**
             * \brief Tells whether the source-database molecule index is written as a molecule property.
             * \return \c true if the molecule-index property is written, and \c false otherwise.
             */
            bool outputDBMoleculeIndexProperty() const;

            /**
             * \brief Specifies whether the conformer index within the source molecule shall be written as a molecule property.
             * \param output \c true to write the conformer-index property, and \c false to skip it.
             */
            void outputMoleculeConfIndexProperty(bool output);

            /**
             * \brief Tells whether the conformer index within the source molecule is written as a molecule property.
             * \return \c true if the conformer-index property is written, and \c false otherwise.
             */
            bool outputMoleculeConfIndexProperty() const;

            /**
             * \brief Specifies whether emitted molecule and conformer indices are zero-based (rather than one-based).
             * \param zero_based \c true to use zero-based indices, and \c false to use one-based indices.
             */
            void outputZeroBasedIndices(bool zero_based);

            /**
             * \brief Tells whether emitted molecule and conformer indices are zero-based.
             * \return \c true if zero-based indices are used, and \c false otherwise.
             */
            bool outputZeroBasedIndices() const;

            /**
             * \brief Writes the search hit \a hit and its alignment score \a score to the configured data writer.
             * \param hit The screening search hit.
             * \param score The alignment score of the hit.
             * \return \c true if the hit was successfully written, and \c false otherwise.
             */
            bool operator()(const ScreeningProcessor::SearchHit& hit, double score);

          private:
            MolecularGraphWriter* dataWriter;
            bool                  alignMolecule;
            bool                  optScore;
            bool                  optDBName;
            bool                  optMolIndex;
            bool                  optConfIndex;
            bool                  optZeroBasedInds;
            Math::Vector3DArray   alignedCoords;
            Chem::BasicMolecule   molecule;
        };
    } // namespace Pharm
} // namespace CDPL

#endif // CDPL_PHARM_FILESCREENINGHITCOLLECTOR_HPP
