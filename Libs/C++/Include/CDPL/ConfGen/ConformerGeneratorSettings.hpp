/* 
 * ConformerGeneratorSettings.hpp 
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
 * \brief Definition of class CDPL::ConfGen::ConformerGeneratorSettings.
 */

#ifndef CDPL_CONFGEN_CONFORMERGENERATORSETTINGS_HPP
#define CDPL_CONFGEN_CONFORMERGENERATORSETTINGS_HPP

#include <cstddef>
#include <vector>
#include <utility>

#include "CDPL/ConfGen/APIPrefix.hpp"
#include "CDPL/ConfGen/FragmentConformerGeneratorSettings.hpp"


namespace CDPL
{

    namespace ConfGen
    {

        class CDPL_CONFGEN_API ConformerGeneratorSettings
        {

          public:
            static const ConformerGeneratorSettings DEFAULT;

            static const ConformerGeneratorSettings SMALL_SET_DIVERSE;
            static const ConformerGeneratorSettings MEDIUM_SET_DIVERSE;
            static const ConformerGeneratorSettings LARGE_SET_DIVERSE;

            static const ConformerGeneratorSettings SMALL_SET_DENSE;
            static const ConformerGeneratorSettings MEDIUM_SET_DENSE;
            static const ConformerGeneratorSettings LARGE_SET_DENSE;

            ConformerGeneratorSettings();

            void setSamplingMode(unsigned int mode);

            unsigned int getSamplingMode() const;

            void sampleHeteroAtomHydrogens(bool sample);

            bool sampleHeteroAtomHydrogens() const;

            void sampleAngleToleranceRanges(bool sample);

            bool sampleAngleToleranceRanges() const;

            void enumerateRings(bool enumerate);

            bool enumerateRings() const;

            void setNitrogenEnumerationMode(unsigned int mode);

            unsigned int getNitrogenEnumerationMode() const;

            void generateCoordinatesFromScratch(bool generate);

            bool generateCoordinatesFromScratch() const;

            void includeInputCoordinates(bool include);

            bool includeInputCoordinates() const;

            void setEnergyWindow(double win_size);

            double getEnergyWindow() const;

            /*
             * \since 1.1
             */
            double getEnergyWindow(std::size_t num_rot_bonds) const;

            /*
             * \since 1.1
             */
            void clearEnergyWindowRanges();

            /*
             * \since 1.1
             */
            void addEnergyWindowRange(std::size_t num_rot_bonds, double win_size);
            
            void setMaxPoolSize(std::size_t max_size);

            std::size_t getMaxPoolSize() const;

            /*
             * \since 1.1
             */
            void setMaxRotatableBondCount(long max_count);

            /*
             * \since 1.1
             */
            long getMaxRotatableBondCount() const;

            void setTimeout(std::size_t mil_secs);

            std::size_t getTimeout() const;

            void setForceFieldTypeSystematic(unsigned int type);

            unsigned int getForceFieldTypeSystematic() const;

            void setForceFieldTypeStochastic(unsigned int type);

            unsigned int getForceFieldTypeStochastic() const;

            void strictForceFieldParameterization(bool strict);

            bool strictForceFieldParameterization() const;

            void setDielectricConstant(double de_const);

            double getDielectricConstant() const;

            void setDistanceExponent(double exponent);

            double getDistanceExponent() const;

            void setMaxNumOutputConformers(std::size_t max_num);

            std::size_t getMaxNumOutputConformers() const;

            /*
             * \since 1.1
             */
            std::size_t getMaxNumOutputConformers(std::size_t num_rot_bonds) const;

            /*
             * \since 1.1
             */
            void clearMaxNumOutputConformersRanges();

            /*
             * \since 1.1
             */
            void addMaxNumOutputConformersRange(std::size_t num_rot_bonds, std::size_t max_num);
            
            void setMinRMSD(double min_rmsd);

            double getMinRMSD() const;

            /*
             * \since 1.1
             */
            double getMinRMSD(std::size_t num_rot_bonds) const;

            /*
             * \since 1.1
             */
            void clearMinRMSDRanges();

            /*
             * \since 1.1
             */
            void addMinRMSDRange(std::size_t num_rot_bonds, double min_rmsd);
            
            void setMaxNumRefinementIterations(std::size_t max_iter);

            std::size_t getMaxNumRefinementIterations() const;

            void setRefinementTolerance(double tol);

            double getRefinementTolerance() const;

            void setMaxNumSampledConformers(std::size_t max_num);

            std::size_t getMaxNumSampledConformers() const;

            void setConvergenceCheckCycleSize(std::size_t size);

            std::size_t getConvergenceCheckCycleSize() const;

            void setMacrocycleRotorBondCountThreshold(std::size_t min_count);

            std::size_t getMacrocycleRotorBondCountThreshold() const;

            FragmentConformerGeneratorSettings& getFragmentBuildSettings();

            const FragmentConformerGeneratorSettings& getFragmentBuildSettings() const;

          private:
            typedef std::pair<std::size_t, std::size_t> STPair;
            typedef std::pair<std::size_t, double>      STDoublePair;
            typedef std::vector<STPair>                 STPairArray;
            typedef std::vector<STDoublePair>           STDoublePairArray;

            template <typename A>
            static typename A::value_type::second_type getValueForCount(const A& array, std::size_t num_rot_bonds);
            
            unsigned int                       samplingMode;
            bool                               sampleHetAtomHs;
            bool                               sampleTolRanges;
            bool                               enumRings;
            unsigned int                       nitrogenEnumMode;
            bool                               fromScratch;
            bool                               incInputCoords;
            double                             eWindow;
            STDoublePairArray                  eWindowRanges;
            std::size_t                        maxPoolSize;
            long                               maxRotorBondCount;
            std::size_t                        timeout;
            unsigned int                       forceFieldTypeSys;
            unsigned int                       forceFieldTypeStoch;
            bool                               strictParam;
            double                             dielectricConst;
            double                             distExponent;
            std::size_t                        maxNumOutputConfs;
            STPairArray                        maxNumOutputConfRanges;
            double                             minRMSD;
            STDoublePairArray                  minRMSDRanges;
            std::size_t                        maxNumRefIters;
            double                             refTolerance;
            std::size_t                        maxNumSampledConfs;
            std::size_t                        convCheckCycleSize;
            std::size_t                        mcRotorBondCountThresh;
            FragmentConformerGeneratorSettings fragBuildSettings;
        };
    }; // namespace ConfGen
} // namespace CDPL

#endif // CDPL_CONFGEN_CONFORMERGENERATORSETTINGS_HPP
