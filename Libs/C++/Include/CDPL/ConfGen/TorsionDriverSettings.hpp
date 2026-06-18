/* 
 * TorsionDriverSettings.hpp 
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
 * \brief Definition of class CDPL::ConfGen::TorsionDriverSettings.
 */

#ifndef CDPL_CONFGEN_TORSIONDRIVERSETTINGS_HPP
#define CDPL_CONFGEN_TORSIONDRIVERSETTINGS_HPP

#include <cstddef>

#include "CDPL/ConfGen/APIPrefix.hpp"


namespace CDPL
{

    namespace ConfGen
    {

        /**
         * \brief Bundle of configuration parameters for systematic conformer enumeration via class ConfGen::TorsionDriver.
         */
        class CDPL_CONFGEN_API TorsionDriverSettings
        {

          public:
            /**
             * \brief A static instance providing configuration parameter default values.
             */
            static const TorsionDriverSettings DEFAULT;

            /**
             * \brief Constructs the \c %TorsionDriverSettings instance with default configuration parameter values.
             */
            TorsionDriverSettings();

            /**
             * \brief Specifies whether torsions of heteroatom hydrogen rotors shall be sampled.
             * \param sample If \c true, such torsions are sampled.
             */
            void sampleHeteroAtomHydrogens(bool sample);

            /**
             * \brief Tells whether torsions of heteroatom hydrogen rotors are sampled.
             * \return \c true if sampling is enabled, and \c false otherwise.
             */
            bool sampleHeteroAtomHydrogens() const;

            /**
             * \brief Specifies whether additional torsion samples within the tolerance ranges defined by the torsion library entries shall be generated.
             * \param sample If \c true, tolerance-range sampling is enabled.
             */
            void sampleAngleToleranceRanges(bool sample);

            /**
             * \brief Tells whether tolerance-range sampling is enabled.
             * \return \c true if tolerance-range sampling is enabled, and \c false otherwise.
             */
            bool sampleAngleToleranceRanges() const;

            /**
             * \brief Specifies whether the generated conformers shall be sorted by ascending energy.
             * \param order If \c true, the output conformers are sorted by energy.
             */
            void orderByEnergy(bool order);

            /**
             * \brief Tells whether the generated conformers are sorted by ascending energy.
             * \return \c true if conformer energy ordering is enabled, and \c false otherwise.
             */
            bool orderByEnergy() const;

            /**
             * \brief Sets the energy window size (in kcal/mol) above the found global minimum within which conformers are kept.
             * \param win_size The new energy window size in kcal/mol.
             */
            void setEnergyWindow(double win_size);

            /**
             * \brief Returns the configured energy window size.
             * \return The energy window size in kcal/mol.
             */
            double getEnergyWindow() const;

            /**
             * \brief Sets the maximum number of conformers to keep in the internal candidate pool.
             * \param max_size The new maximum pool size.
             */
            void setMaxPoolSize(std::size_t max_size);

            /**
             * \brief Returns the maximum number of conformers kept in the internal candidate pool.
             * \return The maximum pool size.
             */
            std::size_t getMaxPoolSize() const;

            /**
             * \brief Sets the force field type used to score the generated conformers.
             * \param type One of the ConfGen::ForceFieldType values.
             */
            void setForceFieldType(unsigned int type);

            /**
             * \brief Returns the force field type used to score the generated conformers.
             * \return One of the ConfGen::ForceFieldType values.
             */
            unsigned int getForceFieldType() const;

            /**
             * \brief Specifies whether strict MMFF94 parameterization is required.
             * \param strict If \c true, missing/ambiguous parameters cause a failure.
             *               Otherwise, in case of parameterization problems, suitable fallback parameters will be used.
             */
            void strictForceFieldParameterization(bool strict);

            /**
             * \brief Tells whether strict MMFF94 parameterization is required.
             * \return \c true if strict parameterization is required, and \c false otherwise.
             */
            bool strictForceFieldParameterization() const;

            /**
             * \brief Sets the dielectric constant used by the MMFF94 electrostatic interactions.
             * \param de_const The new dielectric constant.
             */
            void setDielectricConstant(double de_const);

            /**
             * \brief Returns the dielectric constant used by the MMFF94 electrostatic interactions.
             * \return The dielectric constant.
             */
            double getDielectricConstant() const;

            /**
             * \brief Sets the exponent of the MMFF94 distance-dependent electrostatic term.
             * \param exponent The new distance exponent.
             */
            void setDistanceExponent(double exponent);

            /**
             * \brief Returns the exponent of the MMFF94 distance-dependent electrostatic term.
             * \return The distance exponent.
             */
            double getDistanceExponent() const;

          private:
            bool         sampleHetAtomHs;
            bool         sampleTolRanges;
            bool         energyOrdered;
            double       eWindow;
            std::size_t  maxPoolSize;
            unsigned int forceFieldType;
            bool         strictParam;
            double       dielectricConst;
            double       distExponent;
        };
    } // namespace ConfGen
} // namespace CDPL

#endif // CDPL_CONFGEN_TORSIONDRIVERSETTINGS_HPP
