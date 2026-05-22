/* 
 * StructureGenerator.hpp 
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
 * \brief Definition of class CDPL::ConfGen::StructureGenerator.
 */

#ifndef CDPL_CONFGEN_STRUCTUREGENERATOR_HPP
#define CDPL_CONFGEN_STRUCTUREGENERATOR_HPP

#include <memory>

#include "CDPL/ConfGen/APIPrefix.hpp"
#include "CDPL/ConfGen/CallbackFunction.hpp"
#include "CDPL/ConfGen/LogMessageCallbackFunction.hpp"
#include "CDPL/ConfGen/StructureGeneratorSettings.hpp"
#include "CDPL/ConfGen/ConformerData.hpp"
#include "CDPL/ConfGen/FragmentLibrary.hpp"
#include "CDPL/ConfGen/TorsionLibrary.hpp"


namespace CDPL
{

    namespace Chem
    {

        class MolecularGraph;
    }

    namespace ConfGen
    {

        class ConformerGeneratorImpl;

        /**
         * \brief High-level driver for the generation of a single low-energy 3D structure from a molecular graph.
         *
         * Internally delegates to the same pipeline as ConfGen::ConformerGenerator but stops after the first acceptable
         * conformer has been produced.
         */
        class CDPL_CONFGEN_API StructureGenerator
        {

          public:
            /**
             * \brief Constructs the \c %StructureGenerator instance.
             */
            StructureGenerator();

            StructureGenerator(const StructureGenerator&) = delete;

            /**
             * \brief Destructor.
             */
            ~StructureGenerator();

            StructureGenerator& operator=(const StructureGenerator&) = delete;

            /**
             * \brief Returns the current generator settings.
             * \return A \c const reference to the settings.
             */
            const StructureGeneratorSettings& getSettings() const;

            /**
             * \brief Returns the current generator settings (mutable).
             * \return A reference to the settings.
             */
            StructureGeneratorSettings& getSettings();

            /**
             * \brief Removes all configured fragment libraries.
             */
            void clearFragmentLibraries();

            /**
             * \brief Adds \a lib to the list of fragment libraries consulted during fragment-based 3D structure generation.
             * \param lib The fragment library to add.
             */
            void addFragmentLibrary(const FragmentLibrary::SharedPointer& lib);

            /**
             * \brief Removes all configured torsion libraries.
             */
            void clearTorsionLibraries();

            /**
             * \brief Adds \a lib to the list of torsion libraries consulted during torsion driving.
             * \param lib The torsion library to add.
             */
            void addTorsionLibrary(const TorsionLibrary::SharedPointer& lib);

            /**
             * \brief Sets the callback invoked periodically to allow the generation to be aborted by the user.
             * \param func The abort-check callback.
             */
            void setAbortCallback(const CallbackFunction& func);

            /**
             * \brief Returns the currently configured abort-check callback.
             * \return A \c const reference to the abort-check callback.
             */
            const CallbackFunction& getAbortCallback() const;

            /**
             * \brief Sets the callback invoked when the configured timeout is reached.
             * \param func The timeout callback.
             */
            void setTimeoutCallback(const CallbackFunction& func);

            /**
             * \brief Returns the currently configured timeout callback.
             * \return A \c const reference to the timeout callback.
             */
            const CallbackFunction& getTimeoutCallback() const;

            /**
             * \brief Sets the callback receiving log messages emitted by the generator.
             * \param func The log-message callback.
             */
            void setLogMessageCallback(const LogMessageCallbackFunction& func);

            /**
             * \brief Returns the currently configured log-message callback.
             * \return A \c const reference to the log-message callback.
             */
            const LogMessageCallbackFunction& getLogMessageCallback() const;

            /**
             * \brief Generates a single 3D structure for \a molgraph.
             * \param molgraph The input molecular graph.
             * \return A ConfGen::ReturnCode value reporting the outcome of the generation.
             */
            unsigned int generate(const Chem::MolecularGraph& molgraph);

            /**
             * \brief Generates a single 3D structure for \a molgraph while keeping the substructure \a fixed_substr at its current 3D coordinates.
             * \param molgraph The input molecular graph.
             * \param fixed_substr The substructure that must retain its current 3D coordinates.
             * \return A ConfGen::ReturnCode value reporting the outcome of the generation.
             * \since 1.1
             */
            unsigned int generate(const Chem::MolecularGraph& molgraph, const Chem::MolecularGraph& fixed_substr);

            /**
             * \brief Generates a single 3D structure for \a molgraph while keeping the substructure \a fixed_substr at the supplied 3D coordinates \a fixed_substr_coords.
             * \param molgraph The input molecular graph.
             * \param fixed_substr The substructure that must retain the supplied 3D coordinates.
             * \param fixed_substr_coords The 3D coordinates assigned to \a fixed_substr.
             * \return A ConfGen::ReturnCode value reporting the outcome of the generation.
             * \since 1.1
             */
            unsigned int generate(const Chem::MolecularGraph& molgraph, const Chem::MolecularGraph& fixed_substr,
                                  const Math::Vector3DArray& fixed_substr_coords);

            /**
             * \brief Transfers the generated 3D coordinates onto \a molgraph (sets the \c ATOM_COORDINATES_3D atom properties).
             * \param molgraph The molecular graph receiving the 3D coordinates.
             */
            void setCoordinates(Chem::MolecularGraph& molgraph) const;

            /**
             * \brief Returns the conformer data produced by the most recent generate() call.
             * \return A \c const reference to the conformer data.
             */
            const ConformerData& getCoordinates() const;

          private:
            unsigned int generate(const Chem::MolecularGraph& molgraph, const Chem::MolecularGraph* fixed_substr,
                                  const Math::Vector3DArray* fixed_substr_coords);

            typedef std::unique_ptr<ConformerGeneratorImpl> ImplementationPointer;

            ImplementationPointer      impl;
            StructureGeneratorSettings settings;
            ConformerData              coordinates;
        };
    } // namespace ConfGen
} // namespace CDPL

#endif // CDPL_CONFGEN_STRUCTUREGENERATOR_HPP
