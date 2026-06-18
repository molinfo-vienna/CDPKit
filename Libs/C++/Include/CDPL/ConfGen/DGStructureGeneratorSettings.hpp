/* 
 * DGStructureGeneratorSettings.hpp 
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
 * \brief Definition of class CDPL::ConfGen::DGStructureGeneratorSettings.
 */

#ifndef CDPL_CONFGEN_DGSTRUCTUREGENERATORSETTINGS_HPP
#define CDPL_CONFGEN_DGSTRUCTUREGENERATORSETTINGS_HPP

#include "CDPL/ConfGen/APIPrefix.hpp"
#include "CDPL/ConfGen/DGConstraintGeneratorSettings.hpp"


namespace CDPL
{

    namespace ConfGen
    {

        /**
         * \brief Bundle of configuration parameters for raw coordinates generation via class ConfGen::DGStructureGenerator.
         */
        class CDPL_CONFGEN_API DGStructureGeneratorSettings : public DGConstraintGeneratorSettings
        {

          public:
            /**
             * \brief A static instance providing configuration parameter default values.
             */
            static const DGStructureGeneratorSettings DEFAULT;

            /**
             * \brief Constructs the \c %DGStructureGeneratorSettings instance with default configuration parameter values.
             */
            DGStructureGeneratorSettings();

            /**
             * \brief Sets the edge length of the bounding box used by the distance-geometry embedder.
             * \param size The new bounding-box edge length.
             */
            void setBoxSize(double size);

            /**
             * \brief Returns the edge length of the bounding box used by the distance-geometry embedder.
             * \return The bounding-box edge length.
             */
            double getBoxSize() const;

            /**
             * \brief Specifies whether planarity (zero-volume) constraints shall be added for sp2 atoms and double/aromatic bonds.
             * \param enable If \c true, planarity constraints are added.
             */
            void enablePlanarityConstraints(bool enable);

            /**
             * \brief Tells whether planarity constraints are enabled.
             * \return \c true if planarity constraints are enabled, and \c false otherwise.
             */
            bool enablePlanarityConstraints() const;

          private:
            double boxSize;
            bool   planarConstr;
        };
    } // namespace ConfGen
} // namespace CDPL

#endif // CDPL_CONFGEN_DGSTRUCTUREGENERATORSETTINGS_HPP
