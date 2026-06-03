/* 
 * ScreeningProcessor.hpp 
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
 * \brief Definition of class CDPL::Pharm::ScreeningProcessor.
 */

#ifndef CDPL_PHARM_SCREENINGPROCESSOR_HPP
#define CDPL_PHARM_SCREENINGPROCESSOR_HPP

#include <memory>
#include <cstddef>
#include <functional>

#include "CDPL/Pharm/APIPrefix.hpp"
#include "CDPL/Math/Matrix.hpp"


namespace CDPL
{

    namespace Chem
    {

        class Molecule;
    }

    namespace Pharm
    {

        class FeatureContainer;
        class ScreeningDBAccessor;
        class ScreeningProcessorImpl;

        /**
         * \brief High-level driver for pharmacophore-based screening of a Pharm::ScreeningDBAccessor-backed database
         *        against a query feature container, reporting alignment hits via a user-supplied callback.
         */
        class CDPL_PHARM_API ScreeningProcessor
        {

          public:
            /**
             * \brief Specifies which conformer-level hits are reported per molecule.
             */
            enum HitReportMode
            {

                /** \brief Report the first conformer that matches the query. */
                FIRST_MATCHING_CONF,
                /** \brief Report only the best-scoring matching conformer. */
                BEST_MATCHING_CONF,
                /** \brief Report every conformer that matches the query. */
                ALL_MATCHING_CONFS
            };

            /**
             * \brief Data structure representing a single alignment hit produced by the screening processor, bundling the source pharmacophore/molecule,
             *        the alignment transformation and the source-database indices.
             */
            class CDPL_PHARM_API SearchHit
            {

              public:
                /**
                 * \brief Constructs the \c %SearchHit instance with the given references.
                 * \param hit_prov The screening processor that produced the hit.
                 * \param qry_pharm The query pharmacophore.
                 * \param hit_pharm The hit pharmacophore.
                 * \param mol The hit molecule.
                 * \param xform The alignment transformation that maps the hit onto the query.
                 * \param pharm_idx The zero-based pharmacophore index within the source database.
                 * \param mol_idx The zero-based molecule index within the source database.
                 * \param conf_idx The zero-based conformer index within the source molecule.
                 */
                SearchHit(const ScreeningProcessor& hit_prov, const FeatureContainer& qry_pharm,
                          const FeatureContainer& hit_pharm, const Chem::Molecule& mol,
                          const Math::Matrix4D& xform, std::size_t pharm_idx,
                          std::size_t mol_idx, std::size_t conf_idx);

                /**
                 * \brief Returns the screening processor that produced the hit.
                 * \return A \c const reference to the hit-providing screening processor.
                 */
                const ScreeningProcessor& getHitProvider() const;

                /**
                 * \brief Returns the query pharmacophore.
                 * \return A \c const reference to the query pharmacophore.
                 */
                const FeatureContainer& getQueryPharmacophore() const;

                /**
                 * \brief Returns the hit pharmacophore.
                 * \return A \c const reference to the hit pharmacophore.
                 */
                const FeatureContainer& getHitPharmacophore() const;

                /**
                 * \brief Returns the hit molecule.
                 * \return A \c const reference to the hit molecule.
                 */
                const Chem::Molecule& getHitMolecule() const;

                /**
                 * \brief Returns the rigid-body transformation that aligns the hit onto the query pharmacophore.
                 * \return A \c const reference to the alignment transformation matrix.
                 */
                const Math::Matrix4D& getHitAlignmentTransform() const;

                /**
                 * \brief Returns the source-database pharmacophore index of the hit.
                 * \return The zero-based pharmacophore index.
                 */
                std::size_t getHitPharmacophoreIndex() const;

                /**
                 * \brief Returns the source-database molecule index of the hit.
                 * \return The zero-based molecule index.
                 */
                std::size_t getHitMoleculeIndex() const;

                /**
                 * \brief Returns the conformer index within the source molecule.
                 * \return The zero-based conformer index.
                 */
                std::size_t getHitConformationIndex() const;

              private:
                const ScreeningProcessor* provider;
                const FeatureContainer*   qryPharm;
                const FeatureContainer*   hitPharm;
                const Chem::Molecule*     molecule;
                const Math::Matrix4D*     almntTransform;
                std::size_t               pharmIndex;
                std::size_t               molIndex;
                std::size_t               confIndex;
            };

            /** \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %ScreeningProcessor instances. */
            typedef std::shared_ptr<ScreeningProcessor> SharedPointer;

            /** \brief Type of the callback invoked for every alignment hit (return: \c true to continue, \c false to abort the search). */
            typedef std::function<bool(const SearchHit&, double)> HitCallbackFunction;
            /** \brief Type of the function used to score a search hit. */
            typedef std::function<double(const SearchHit&)>       ScoringFunction;
            /** \brief Type of the progress-reporting callback (arguments: current molecule index, total molecule count; return: \c true to continue, \c false to abort). */
            typedef std::function<bool(std::size_t, std::size_t)> ProgressCallbackFunction;

            /**
             * \brief Constructs the \c %ScreeningProcessor instance for the given
             *        screening database accessor \a db_acc.
             * \param db_acc An accessor for the database to screen.
             */
            ScreeningProcessor(ScreeningDBAccessor& db_acc);

            ScreeningProcessor(const ScreeningProcessor& proc) = delete;

            /**
             * \brief Destructor.
             */
            ~ScreeningProcessor();

            ScreeningProcessor& operator=(const ScreeningProcessor& proc) = delete;

            /**
             * \brief Specifies the screening database accessor.
             * \param db_acc The new database accessor.
             */
            void setDBAccessor(ScreeningDBAccessor& db_acc);

            /**
             * \brief Returns the currently configured screening database accessor.
             * \return A reference to the database accessor.
             */
            ScreeningDBAccessor& getDBAccessor() const;

            /**
             * \brief Sets the hit-report mode.
             * \param mode The new hit-report mode.
             */
            void setHitReportMode(HitReportMode mode);

            /**
             * \brief Returns the currently configured hit-report mode.
             * \return The hit-report mode.
             */
            HitReportMode getHitReportMode() const;

            /**
             * \brief Sets the maximum number of query features that may remain unmatched in a valid hit.
             * \param max_num The new maximum number of omitted features.
             */
            void setMaxNumOmittedFeatures(std::size_t max_num);

            /**
             * \brief Returns the currently configured maximum number of omitted features.
             * \return The maximum number of omitted features.
             */
            std::size_t getMaxNumOmittedFeatures() const;

            /**
             * \brief Specifies whether the alignment shall check exclusion-volume clashes between the query and the hit molecule.
             * \param check \c true to enable the clash check, and \c false to disable it.
             */
            void checkXVolumeClashes(bool check);

            /**
             * \brief Tells whether exclusion-volume clashes are checked during alignment.
             * \return \c true if the clash check is enabled, and \c false otherwise.
             */
            bool xVolumeClashesChecked() const;

            /**
             * \brief Specifies whether the alignment shall search for the best-scoring rather than the first valid alignment per pose.
             * \param seek_best \c true to seek the best alignment, and \c false to accept the first valid alignment.
             */
            void seekBestAlignments(bool seek_best);

            /**
             * \brief Tells whether the alignment seeks the best-scoring rather than the first valid alignment.
             * \return \c true if best-alignment seeking is enabled, and \c false otherwise.
             */
            bool bestAlignmentsSeeked() const;

            /**
             * \brief Specifies the hit-callback function.
             * \param func The hit-callback function.
             */
            void setHitCallback(const HitCallbackFunction& func);

            /**
             * \brief Returns the currently configured hit-callback function.
             * \return A \c const reference to the hit-callback function.
             */
            const HitCallbackFunction& getHitCallback() const;

            /**
             * \brief Specifies the progress-reporting callback.
             * \param func The progress-callback function.
             */
            void setProgressCallback(const ProgressCallbackFunction& func);

            /**
             * \brief Returns the currently configured progress-reporting callback.
             * \return A \c const reference to the progress-callback function.
             */
            const ProgressCallbackFunction& getProgressCallback() const;

            /**
             * \brief Specifies the function used to score a search hit.
             * \param func The scoring function.
             */
            void setScoringFunction(const ScoringFunction& func);

            /**
             * \brief Returns the currently configured scoring function.
             * \return A \c const reference to the scoring function.
             */
            const ScoringFunction& getScoringFunction() const;

            /**
             * \brief Screens the database with the supplied query pharmacophore.
             * \param query The query feature container.
             * \param mol_start_idx The zero-based index of the first molecule to screen.
             * \param mol_end_idx The exclusive upper bound of the molecule range; if \e 0, the search runs through the end of the database.
             * \return The number of accepted hits produced by the search.
             */
            std::size_t searchDB(const FeatureContainer& query, std::size_t mol_start_idx = 0, std::size_t mol_end_idx = 0);

          private:
            typedef std::unique_ptr<ScreeningProcessorImpl> ImplementationPointer;

            ImplementationPointer impl;
        };
    } // namespace Pharm
} // namespace CDPL

#endif // CDPL_PHARM_SCREENINGPROCESSOR_HPP
