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

        class CDPL_SHAPE_API ScreeningProcessor
        {

            typedef std::vector<const Chem::MolecularGraph*> MolecularGraphList;

          public:
            typedef std::shared_ptr<ScreeningProcessor>                                                                   SharedPointer;
            typedef boost::indirect_iterator<MolecularGraphList::const_iterator, const Chem::MolecularGraph>              ConstMolecularGraphIterator;
            typedef std::function<void(const Chem::MolecularGraph&, const Chem::MolecularGraph&, const AlignmentResult&)> HitCallbackFunction;

            ScreeningProcessor();

            ScreeningProcessor(const Chem::MolecularGraph& query);

            ScreeningProcessor(const ScreeningProcessor& proc) = delete;
              
            ~ScreeningProcessor();

            ScreeningProcessor& operator=(const ScreeningProcessor& proc) = delete;

            void setHitCallback(const HitCallbackFunction& func);

            const HitCallbackFunction& getHitCallback() const;

            const ScreeningSettings& getSettings() const;

            ScreeningSettings& getSettings();

            void clearQuerySet();

            void addQuery(const Chem::MolecularGraph& molgraph);

            std::size_t getQuerySetSize() const;

            const Chem::MolecularGraph& getQuery(std::size_t idx) const;

            ConstMolecularGraphIterator getQuerySetBegin() const;

            ConstMolecularGraphIterator getQuerySetEnd() const;

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
