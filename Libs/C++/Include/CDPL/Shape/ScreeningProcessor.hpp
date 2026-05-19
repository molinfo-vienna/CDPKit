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
 * \brief Definition of class CDPL::Shape::ScreeningProcessor.
 */

#ifndef CDPL_SHAPE_SCREENINGPROCESSOR_HPP
#define CDPL_SHAPE_SCREENINGPROCESSOR_HPP

#include <cstddef>
#include <vector>
#include <memory>
#include <functional>

#include <boost/iterator/indirect_iterator.hpp>

#include "CDPL/Shape/APIPrefix.hpp"
#include "CDPL/Shape/FastGaussianShapeAlignment.hpp"
#include "CDPL/Shape/GaussianShapeGenerator.hpp"
#include "CDPL/Shape/ScreeningSettings.hpp"
#include "CDPL/Pharm/DefaultPharmacophoreGenerator.hpp"


namespace CDPL
{

    namespace Chem
    {

        class MolecularGraph;
    }

    namespace Shape
    {

        class AlignmentResult;

        /**
         * \brief High-level driver for shape-based virtual screening of molecular databases.
         *
         * The processor maintains a set of query molecules and aligns each incoming database
         * molecule against all of them, reporting alignment hits through a user-supplied callback.
         * The behaviour (similarity score type, shape generation, alignment options, etc.) is
         * configured via the embedded Shape::ScreeningSettings instance.
         */
        class CDPL_SHAPE_API ScreeningProcessor
        {

            typedef std::vector<const Chem::MolecularGraph*> MolecularGraphList;

          public:
            /** \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %ScreeningProcessor instances. */
            typedef std::shared_ptr<ScreeningProcessor>                                                                   SharedPointer;
            /** \brief A constant iterator over the query molecules. */
            typedef boost::indirect_iterator<MolecularGraphList::const_iterator, const Chem::MolecularGraph>              ConstMolecularGraphIterator;
            /** \brief Type of the callback invoked for each alignment hit (arguments: query, hit, alignment result). */
            typedef std::function<void(const Chem::MolecularGraph&, const Chem::MolecularGraph&, const AlignmentResult&)> HitCallbackFunction;

            /** \brief Constructs an empty \c %ScreeningProcessor instance. */
            ScreeningProcessor();

            /**
             * \brief Constructs a \c %ScreeningProcessor instance with \a query as the single query molecule.
             * \param query The query molecule.
             */
            ScreeningProcessor(const Chem::MolecularGraph& query);

            ScreeningProcessor(const ScreeningProcessor& proc) = delete;

            /** \brief Destructor. */
            ~ScreeningProcessor();

            ScreeningProcessor& operator=(const ScreeningProcessor& proc) = delete;

            /** \brief Sets the callback that is invoked for every alignment hit produced by process(). */
            void setHitCallback(const HitCallbackFunction& func);

            /** \brief Returns the currently configured hit callback. */
            const HitCallbackFunction& getHitCallback() const;

            /** \brief Returns the current screening settings. */
            const ScreeningSettings& getSettings() const;

            /** \brief Returns the current screening settings (mutable). */
            ScreeningSettings& getSettings();

            /** \brief Removes all query molecules. */
            void clearQuerySet();

            /**
             * \brief Adds \a molgraph to the query set.
             * \param molgraph The query molecule.
             */
            void addQuery(const Chem::MolecularGraph& molgraph);

            /** \brief Returns the number of query molecules. */
            std::size_t getQuerySetSize() const;

            /**
             * \brief Returns the query molecule at index \a idx.
             * \param idx The zero-based index of the query molecule.
             * \return A \c const reference to the query molecule.
             * \throw Base::IndexError if the number of query molecules is zero or \a idx is not in the range [0, getQuerySetSize() - 1].
             */
            const Chem::MolecularGraph& getQuery(std::size_t idx) const;

            /** \brief Returns a constant iterator pointing to the first query molecule. */
            ConstMolecularGraphIterator getQuerySetBegin() const;

            /** \brief Returns a constant iterator pointing one past the last query molecule. */
            ConstMolecularGraphIterator getQuerySetEnd() const;

            /**
             * \brief Processes the database molecule \a molgraph, aligning it against all query molecules.
             * \param molgraph The database molecule.
             * \return \c true if at least one alignment hit was produced for \a molgraph, and \c false otherwise.
             */
            bool process(const Chem::MolecularGraph& molgraph);

          private:
            void init();
            void applyShapeGenSettings(bool query);
            void applyAlignmentSettings();
            void resetQuery();

            ScreeningSettings                    settings;
            ScreeningSettings::ColorFeatureType  colorFtrType;
            bool                                 allCarbon;
            Pharm::DefaultPharmacophoreGenerator expChgPharmGen;
            FastGaussianShapeAlignment           alignment;
            GaussianShapeGenerator               shapeGen;
            MolecularGraphList                   queryList;
            HitCallbackFunction                  hitCallback;
        };
    } // namespace Shape
} // namespace CDPL

#endif // CDPL_SHAPE_SCREENINGPROCESSOR_HPP
