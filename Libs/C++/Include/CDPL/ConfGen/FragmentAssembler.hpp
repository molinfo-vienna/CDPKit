/* 
 * FragmentAssembler.hpp 
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
 * \brief Definition of class CDPL::ConfGen::FragmentAssembler.
 */

#ifndef CDPL_CONFGEN_FRAGMENTASSEMBLER_HPP
#define CDPL_CONFGEN_FRAGMENTASSEMBLER_HPP

#include <cstddef>
#include <memory>

#include <boost/iterator/indirect_iterator.hpp>

#include "CDPL/ConfGen/APIPrefix.hpp"
#include "CDPL/ConfGen/FragmentAssemblerSettings.hpp"
#include "CDPL/ConfGen/FragmentLibrary.hpp"
#include "CDPL/ConfGen/ConformerDataArray.hpp"
#include "CDPL/ConfGen/CallbackFunction.hpp"
#include "CDPL/ConfGen/LogMessageCallbackFunction.hpp"


namespace CDPL
{

    namespace Chem
    {

        class MolecularGraph;
    }

    namespace ConfGen
    {

        class FragmentAssemblerImpl;

        /**
         * \brief Driver for the fragment-based generation of 3D starting conformers.
         *
         * The assembler decomposes a molecular graph into chain and ring fragments, looks up pre-built conformers
         * from a ConfGen::FragmentLibrary for each fragment (generating them on the fly when no library entry is
         * available) and reassembles them into full 3D structures. The conformers produced this way are intended
         * to serve as <em>starting conformers</em> for subsequent torsion driving — they are not (in general) a
         * final conformer ensemble.
         *
         * \see ConfGen::TorsionDriver, ConfGen::ConformerGenerator
         */
        class CDPL_CONFGEN_API FragmentAssembler
        {

          public:
            /**
             * \brief A constant iterator over the assembled conformers.
             */
            typedef boost::indirect_iterator<ConformerDataArray::const_iterator, const ConformerData> ConstConformerIterator;

            /**
             * \brief A mutable iterator over the assembled conformers.
             */
            typedef boost::indirect_iterator<ConformerDataArray::const_iterator, ConformerData>       ConformerIterator;

            /**
             * \brief Constructs the \c %FragmentAssembler instance.
             */
            FragmentAssembler();

            FragmentAssembler(const FragmentAssembler&) = delete;

            /**
             * \brief Destructor.
             */
            ~FragmentAssembler();

            FragmentAssembler& operator=(const FragmentAssembler&) = delete;

            /**
             * \brief Returns the current assembler settings.
             * \return A \c const reference to the settings.
             */
            const FragmentAssemblerSettings& getSettings() const;

            /**
             * \brief Returns the current assembler settings (mutable).
             * \return A reference to the settings.
             */
            FragmentAssemblerSettings& getSettings();

            /**
             * \brief Removes all configured fragment libraries.
             */
            void clearFragmentLibraries();

            /**
             * \brief Adds \a lib to the list of fragment libraries consulted during assembly.
             * \param lib The fragment library to add.
             */
            void addFragmentLibrary(const FragmentLibrary::SharedPointer& lib);

            /**
             * \brief Sets the callback invoked periodically to allow the processing to be aborted by the user.
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
             * \brief Sets the callback receiving log messages emitted by the assembler.
             * \param func The log-message callback.
             */
            void setLogMessageCallback(const LogMessageCallbackFunction& func);

            /**
             * \brief Returns the currently configured log-message callback.
             * \return A \c const reference to the log-message callback.
             */
            const LogMessageCallbackFunction& getLogMessageCallback() const;

            /**
             * \brief Assembles 3D conformer(s) for \a molgraph from fragment building blocks.
             * \param molgraph The input molecular graph.
             * \return A ConfGen::ReturnCode value reporting the outcome of the assembly.
             */
            unsigned int assemble(const Chem::MolecularGraph& molgraph);

            /**
             * \brief Assembles 3D conformer(s) for \a molgraph while keeping the substructure \a fixed_substr at the supplied 3D coordinates.
             * \param molgraph The input molecular graph.
             * \param fixed_substr The substructure that must retain the supplied 3D coordinates.
             * \param fixed_substr_coords The 3D coordinates assigned to \a fixed_substr.
             * \return A ConfGen::ReturnCode value reporting the outcome of the assembly.
             * \since 1.1
             */
            unsigned int assemble(const Chem::MolecularGraph& molgraph, const Chem::MolecularGraph& fixed_substr,
                                  const Math::Vector3DArray& fixed_substr_coords);

            /**
             * \brief Returns the number of assembled conformers.
             * \return The conformer count.
             */
            std::size_t getNumConformers() const;

            /**
             * \brief Returns the conformer at index \a idx.
             * \param idx The zero-based conformer index.
             * \return A \c const reference to the conformer data.
             * \throw Base::IndexError if \a idx is not in the range [0, getNumConformers()).
             */
            const ConformerData& getConformer(std::size_t idx) const;

            /**
             * \brief Returns the conformer at index \a idx.
             * \param idx The zero-based conformer index.
             * \return A reference to the conformer data.
             * \throw Base::IndexError if \a idx is not in the range [0, getNumConformers()).
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
            typedef std::unique_ptr<FragmentAssemblerImpl> ImplementationPointer;

            ImplementationPointer impl;
        };
    } // namespace ConfGen
} // namespace CDPL

#endif // CDPL_CONFGEN_FRAGMENTASSEMBLER_HPP
