/* 
 * FragmentConformerGenerator.hpp 
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
 * \brief Definition of class CDPL::ConfGen::FragmentConformerGenerator.
 */

#ifndef CDPL_CONFGEN_FRAGMENTCONFORMERGENERATOR_HPP
#define CDPL_CONFGEN_FRAGMENTCONFORMERGENERATOR_HPP

#include <memory>

#include <boost/iterator/indirect_iterator.hpp>

#include "CDPL/ConfGen/APIPrefix.hpp"
#include "CDPL/ConfGen/ConformerDataArray.hpp"
#include "CDPL/ConfGen/CallbackFunction.hpp"
#include "CDPL/ConfGen/LogMessageCallbackFunction.hpp"
#include "CDPL/ConfGen/FragmentConformerGeneratorSettings.hpp"


namespace CDPL
{

    namespace Chem
    {

        class MolecularGraph;
    }

    namespace ConfGen
    {

        class FragmentConformerGeneratorImpl;

        /**
         * \brief Driver for the generation of low-energy conformer ensembles for single molecular fragments (chain, small
         *        ring system or macrocycle)
         *
         * Conformer sampling is done in a stochastic manner using distance-geometry-based raw coordinates generation,
         * MMFF94 energy minimization and conformer RMSD clustering.
         *
         * \see [\ref CFRG]
         */
        class CDPL_CONFGEN_API FragmentConformerGenerator
        {

          public:
            /**
             * \brief A constant iterator over the generated conformers.
             */
            typedef boost::indirect_iterator<ConformerDataArray::const_iterator, const ConformerData> ConstConformerIterator;

            /**
             * \brief A mutable iterator over the generated conformers.
             */
            typedef boost::indirect_iterator<ConformerDataArray::const_iterator, ConformerData>       ConformerIterator;

            /**
             * \brief Constructs the \c %FragmentConformerGenerator instance.
             */
            FragmentConformerGenerator();

            FragmentConformerGenerator(const FragmentConformerGenerator&) = delete;

            /**
             * \brief Destructor.
             */
            ~FragmentConformerGenerator();

            FragmentConformerGenerator& operator=(const FragmentConformerGenerator&) = delete;

            /**
             * \brief Returns the current generator settings (mutable).
             * \return A reference to the settings.
             */
            FragmentConformerGeneratorSettings& getSettings();

            /**
             * \brief Returns the current generator settings.
             * \return A \c const reference to the settings.
             */
            const FragmentConformerGeneratorSettings& getSettings() const;

            /**
             * \brief Sets the callback invoked periodically to allow conformer generation to be aborted by the user.
             * \param func The abort-check callback.
             */
            void setAbortCallback(const CallbackFunction& func);

            /**
             * \brief Returns the currently configured abort-check callback.
             * \return A \c const reference to the abort-check callback.
             */
            const CallbackFunction& getAbortCallback() const;

            /**
             * \brief Sets the callback invoked periodically to check whether the configured timeout has elapsed.
             * \param func The timeout-check callback.
             */
            void setTimeoutCallback(const CallbackFunction& func);

            /**
             * \brief Returns the currently configured timeout-check callback.
             * \return A \c const reference to the timeout-check callback.
             */
            const CallbackFunction& getTimeoutCallback() const;

            /**
             * \brief Sets the callback that receives log messages produced during conformer generation.
             * \param func The log-message callback.
             */
            void setLogMessageCallback(const LogMessageCallbackFunction& func);

            /**
             * \brief Returns the currently configured log-message callback.
             * \return A \c const reference to the log-message callback.
             */
            const LogMessageCallbackFunction& getLogMessageCallback() const;

            /**
             * \brief Generates a conformer ensemble for the fragment \a molgraph (the fragment type is perceived automatically).
             * \param molgraph The fragment to process.
             * \return A status code defined in ConfGen::ReturnCode.
             */
            unsigned int generate(const Chem::MolecularGraph& molgraph);

            /**
             * \brief Generates a conformer ensemble for the fragment \a molgraph using the fragment-type-specific settings selected by \a frag_type.
             * \param molgraph The fragment to process.
             * \param frag_type One of the ConfGen::FragmentType values selecting the per-fragment-class settings.
             * \return A status code defined in ConfGen::ReturnCode.
             */
            unsigned int generate(const Chem::MolecularGraph& molgraph, unsigned int frag_type);

            /**
             * \brief Generates a conformer ensemble for the fragment \a molgraph while keeping the substructure \a fixed_substr at the supplied 3D coordinates.
             * \param molgraph The fragment to process.
             * \param fixed_substr The substructure that must retain the supplied 3D coordinates.
             * \param fixed_substr_coords The 3D coordinates assigned to \a fixed_substr.
             * \return A status code defined in ConfGen::ReturnCode.
             * \since 1.1
             */
            unsigned int generate(const Chem::MolecularGraph& molgraph, const Chem::MolecularGraph& fixed_substr,
                                  const Math::Vector3DArray& fixed_substr_coords);

            /**
             * \brief Generates a conformer ensemble for the fragment \a molgraph using the fragment-type-specific settings selected by \a frag_type
             *        while keeping the substructure \a fixed_substr at the supplied 3D coordinates.
             * \param molgraph The fragment to process.
             * \param frag_type One of the ConfGen::FragmentType values selecting the per-fragment-class settings.
             * \param fixed_substr The substructure that must retain the supplied 3D coordinates.
             * \param fixed_substr_coords The 3D coordinates assigned to \a fixed_substr.
             * \return A status code defined in ConfGen::ReturnCode.
             * \since 1.1
             */
            unsigned int generate(const Chem::MolecularGraph& molgraph, unsigned int frag_type,
                                  const Chem::MolecularGraph& fixed_substr,
                                  const Math::Vector3DArray& fixed_substr_coords);

            /**
             * \brief Transfers the generated conformer ensemble onto \a molgraph.
             *
             * The per-conformer 3D coordinates are written to each atom's 3D-coordinates array
             * (via Chem::set3DCoordinatesArray) and the corresponding per-conformer energies are
             * attached to the molecular graph (via Chem::setConformerEnergies).
             *
             * \param molgraph The molecular graph that receives the conformer coordinates and energies.
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
             * \brief Returns a constant iterator pointing to the first generated conformer.
             * \return A constant iterator pointing to the first conformer.
             */
            ConstConformerIterator getConformersBegin() const;

            /**
             * \brief Returns a constant iterator pointing one past the last generated conformer.
             * \return A constant iterator pointing one past the last conformer.
             */
            ConstConformerIterator getConformersEnd() const;

            /**
             * \brief Returns a mutable iterator pointing to the first generated conformer.
             * \return A mutable iterator pointing to the first conformer.
             */
            ConformerIterator getConformersBegin();

            /**
             * \brief Returns a mutable iterator pointing one past the last generated conformer.
             * \return A mutable iterator pointing one past the last conformer.
             */
            ConformerIterator getConformersEnd();

            /**
             * \brief Returns a constant iterator pointing to the first generated conformer (range-based for support).
             * \return A constant iterator pointing to the first conformer.
             */
            ConstConformerIterator begin() const;

            /**
             * \brief Returns a constant iterator pointing one past the last generated conformer (range-based for support).
             * \return A constant iterator pointing one past the last conformer.
             */
            ConstConformerIterator end() const;

            /**
             * \brief Returns a mutable iterator pointing to the first generated conformer (range-based for support).
             * \return A mutable iterator pointing to the first conformer.
             */
            ConformerIterator begin();

            /**
             * \brief Returns a mutable iterator pointing one past the last generated conformer (range-based for support).
             * \return A mutable iterator pointing one past the last conformer.
             */
            ConformerIterator end();

          private:
            typedef std::unique_ptr<FragmentConformerGeneratorImpl> ImplementationPointer;

            ImplementationPointer impl;
        };
    } // namespace ConfGen
} // namespace CDPL

#endif // CDPL_CONFGEN_FRAGMENTCONFORMERGENERATOR_HPP
