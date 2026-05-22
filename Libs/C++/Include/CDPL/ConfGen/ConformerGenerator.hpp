/* 
 * ConformerGenerator.hpp 
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
 * \brief Definition of class CDPL::ConfGen::ConformerGenerator.
 */

#ifndef CDPL_CONFGEN_CONFORMERGENERATOR_HPP
#define CDPL_CONFGEN_CONFORMERGENERATOR_HPP

#include <memory>

#include <boost/iterator/indirect_iterator.hpp>

#include "CDPL/ConfGen/APIPrefix.hpp"
#include "CDPL/ConfGen/ConformerDataArray.hpp"
#include "CDPL/ConfGen/CallbackFunction.hpp"
#include "CDPL/ConfGen/LogMessageCallbackFunction.hpp"
#include "CDPL/ConfGen/ConformerGeneratorSettings.hpp"
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
         * \brief High-level driver for the systematic generation of low-energy 3D conformer ensembles from a molecular graph.
         *
         * The generator coordinates the full pipeline: 2D-to-3D fragment-based structure generation, torsion-driven
         * conformer enumeration, MMFF94-based energy minimization, RMSD-based clustering and final selection.
         * Pipeline behaviour is controlled via the embedded Settings instance, the configured fragment and torsion
         * libraries and optional abort/timeout/log callbacks.
         */
        class CDPL_CONFGEN_API ConformerGenerator
        {

          public:
            /** \brief A constant iterator over the generated conformers. */
            typedef boost::indirect_iterator<ConformerDataArray::const_iterator, const ConformerData> ConstConformerIterator;
            /** \brief A mutable iterator over the generated conformers. */
            typedef boost::indirect_iterator<ConformerDataArray::const_iterator, ConformerData>       ConformerIterator;

            /**
             * \brief Constructs the \c %ConformerGenerator instance.
             */
            ConformerGenerator();

            ConformerGenerator(const ConformerGenerator&) = delete;

            /**
             * \brief Destructor.
             */
            ~ConformerGenerator();

            ConformerGenerator& operator=(const ConformerGenerator&) = delete;

            /**
             * \brief Returns the current generator settings.
             * \return A \c const reference to the settings.
             */
            const ConformerGeneratorSettings& getSettings() const;

            /**
             * \brief Returns the current generator settings (mutable).
             * \return A reference to the settings.
             */
            ConformerGeneratorSettings& getSettings();

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
             * \brief Generates a conformer ensemble for \a molgraph.
             * \param molgraph The input molecular graph.
             * \return A ConfGen::ReturnCode value reporting the outcome of the generation.
             */
            unsigned int generate(const Chem::MolecularGraph& molgraph);

            /**
             * \brief Generates a conformer ensemble for \a molgraph while keeping the substructure \a fixed_substr at its current 3D coordinates.
             * \param molgraph The input molecular graph.
             * \param fixed_substr The substructure that must retain its current 3D coordinates.
             * \return A ConfGen::ReturnCode value reporting the outcome of the generation.
             * \since 1.1
             */
            unsigned int generate(const Chem::MolecularGraph& molgraph, const Chem::MolecularGraph& fixed_substr);

            /**
             * \brief Generates a conformer ensemble for \a molgraph while keeping the substructure \a fixed_substr at the supplied 3D coordinates \a fixed_substr_coords.
             * \param molgraph The input molecular graph.
             * \param fixed_substr The substructure that must retain the supplied 3D coordinates.
             * \param fixed_substr_coords The 3D coordinates assigned to \a fixed_substr.
             * \return A ConfGen::ReturnCode value reporting the outcome of the generation.
             * \since 1.1
             */
            unsigned int generate(const Chem::MolecularGraph& molgraph, const Chem::MolecularGraph& fixed_substr,
                                  const Math::Vector3DArray& fixed_substr_coords);

            /**
             * \brief Transfers the generated conformer ensemble onto \a molgraph (adds Chem::MolecularGraphProperty::CONFORMER_DATA entries).
             * \param molgraph The molecular graph receiving the conformer data.
             */
            void setConformers(Chem::MolecularGraph& molgraph) const;

            /**
             * \brief Returns the number of generated conformers.
             * \return The conformer count.
             */
            std::size_t getNumConformers() const;

            /**
             * \brief Returns the conformer at index \a idx.
             * \param idx The zero-based conformer index.
             * \return A \c const reference to the conformer data.
             * \throw Base::IndexError if the number of conformers is zero or \a idx is not in the range [0, getNumConformers() - 1].
             */
            const ConformerData& getConformer(std::size_t idx) const;

            /**
             * \brief Returns the conformer at index \a idx.
             * \param idx The zero-based conformer index.
             * \return A reference to the conformer data.
             * \throw Base::IndexError if the number of conformers is zero or \a idx is not in the range [0, getNumConformers() - 1].
             */
            ConformerData& getConformer(std::size_t idx);

            /**
             * \brief Returns a constant iterator pointing to the first conformer.
             * \return A constant iterator pointing to the first conformer.
             */
            ConstConformerIterator getConformersBegin() const;

            /**
             * \brief Returns a constant iterator pointing one past the last conformer.
             * \return A constant iterator pointing one past the last conformer.
             */
            ConstConformerIterator getConformersEnd() const;

            /**
             * \brief Returns a mutable iterator pointing to the first conformer.
             * \return A mutable iterator pointing to the first conformer.
             */
            ConformerIterator getConformersBegin();

            /**
             * \brief Returns a mutable iterator pointing one past the last conformer.
             * \return A mutable iterator pointing one past the last conformer.
             */
            ConformerIterator getConformersEnd();

            /**
             * \brief Returns a constant iterator pointing to the first conformer (range-based for support).
             * \return A constant iterator pointing to the first conformer.
             */
            ConstConformerIterator begin() const;

            /**
             * \brief Returns a constant iterator pointing one past the last conformer (range-based for support).
             * \return A constant iterator pointing one past the last conformer.
             */
            ConstConformerIterator end() const;

            /**
             * \brief Returns a mutable iterator pointing to the first conformer (range-based for support).
             * \return A mutable iterator pointing to the first conformer.
             */
            ConformerIterator begin();

            /**
             * \brief Returns a mutable iterator pointing one past the last conformer (range-based for support).
             * \return A mutable iterator pointing one past the last conformer.
             */
            ConformerIterator end();

          private:
            typedef std::unique_ptr<ConformerGeneratorImpl> ImplementationPointer;

            ImplementationPointer impl;
        };
    } // namespace ConfGen
} // namespace CDPL

#endif // CDPL_CONFGEN_CONFORMERGENERATOR_HPP
