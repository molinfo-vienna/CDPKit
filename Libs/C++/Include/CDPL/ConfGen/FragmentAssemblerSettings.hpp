/* 
 * FragmentAssemblerSettings.hpp 
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
 * \brief Definition of class CDPL::ConfGen::FragmentAssemblerSettings.
 */

#ifndef CDPL_CONFGEN_FRAGMENTASSEMBLERSETTINGS_HPP
#define CDPL_CONFGEN_FRAGMENTASSEMBLERSETTINGS_HPP

#include "CDPL/ConfGen/APIPrefix.hpp"
#include "CDPL/ConfGen/FragmentConformerGeneratorSettings.hpp"


namespace CDPL
{

    namespace ConfGen
    {

        /**
         * \brief Bundle of configuration parameters for ConfGen::FragmentAssembler.
         */
        class CDPL_CONFGEN_API FragmentAssemblerSettings
        {

          public:
            /** \brief Default settings used by a freshly-constructed FragmentAssemblerSettings. */
            static const FragmentAssemblerSettings DEFAULT;

            /**
             * \brief Constructs the settings instance with default values.
             */
            FragmentAssemblerSettings();

            /**
             * \brief Specifies whether ring conformations shall be enumerated during fragment assembly.
             * \param enumerate If \c true, multiple ring conformations are emitted.
             */
            void enumerateRings(bool enumerate);

            /**
             * \brief Tells whether ring conformations are enumerated during fragment assembly.
             * \return \c true if ring conformations are enumerated, and \c false otherwise.
             */
            bool enumerateRings() const;

            /**
             * \brief Sets the enumeration mode for stereogenic nitrogen centers.
             * \param mode One of the ConfGen::NitrogenEnumerationMode values.
             */
            void setNitrogenEnumerationMode(unsigned int mode);

            /**
             * \brief Returns the currently configured stereogenic-nitrogen enumeration mode.
             * \return One of the ConfGen::NitrogenEnumerationMode values.
             */
            unsigned int getNitrogenEnumerationMode() const;

            /**
             * \brief Specifies whether 3D coordinates shall be generated from scratch (ignoring any 3D input).
             * \param generate If \c true, 3D coordinates are always regenerated.
             */
            void generateCoordinatesFromScratch(bool generate);

            /**
             * \brief Tells whether 3D coordinates are generated from scratch.
             * \return \c true if 3D coordinates are always regenerated, and \c false otherwise.
             */
            bool generateCoordinatesFromScratch() const;

            /**
             * \brief Returns a reference to the nested fragment-conformer build settings.
             * \return A reference to the build settings.
             */
            FragmentConformerGeneratorSettings& getFragmentBuildSettings();

            /**
             * \brief Returns a \c const reference to the nested fragment-conformer build settings.
             * \return A \c const reference to the build settings.
             */
            const FragmentConformerGeneratorSettings& getFragmentBuildSettings() const;

          private:
            bool                               enumRings;
            unsigned int                       nitrogenEnumMode;
            bool                               fromScratch;
            FragmentConformerGeneratorSettings fragBuildSettings;
        };
    } // namespace ConfGen
} // namespace CDPL

#endif // CDPL_CONFGEN_FRAGMENTASSEMBLERSETTINGS_HPP
