/* 
 * TorsionDriver.hpp 
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
 * \brief Definition of class CDPL::ConfGen::TorsionDriver.
 */

#ifndef CDPL_CONFGEN_TORSIONDRIVER_HPP
#define CDPL_CONFGEN_TORSIONDRIVER_HPP

#include <cstddef>
#include <memory>

#include <boost/iterator/indirect_iterator.hpp>

#include "CDPL/ConfGen/APIPrefix.hpp"
#include "CDPL/ConfGen/TorsionDriverSettings.hpp"
#include "CDPL/ConfGen/TorsionLibrary.hpp"
#include "CDPL/ConfGen/CallbackFunction.hpp"
#include "CDPL/ConfGen/LogMessageCallbackFunction.hpp"
#include "CDPL/ConfGen/ConformerDataArray.hpp"
#include "CDPL/Util/BitSet.hpp"


namespace CDPL
{

    namespace Chem
    {

        class MolecularGraph;
        class Fragment;
    } // namespace Chem

    namespace ConfGen
    {

        class TorsionDriverImpl;

        /**
         * \brief Driver for the systematic enumeration of conformers obtained by rotating around rotatable bonds of a
         *        molecular graph, using preferred torsion angles taken from configured ConfGen::TorsionLibrary instances.
         */
        class CDPL_CONFGEN_API TorsionDriver
        {

          public:
            /** \brief A constant iterator over the generated conformers. */
            typedef boost::indirect_iterator<ConformerDataArray::const_iterator, const ConformerData> ConstConformerIterator;
            /** \brief A mutable iterator over the generated conformers. */
            typedef boost::indirect_iterator<ConformerDataArray::const_iterator, ConformerData>       ConformerIterator;

            /**
             * \brief Constructs the \c %TorsionDriver instance.
             */
            TorsionDriver();

            TorsionDriver(const TorsionDriver&) = delete;

            /**
             * \brief Destructor.
             */
            ~TorsionDriver();

            TorsionDriver& operator=(const TorsionDriver&) = delete;

            /**
             * \brief Returns the current driver settings.
             * \return A \c const reference to the settings.
             */
            const TorsionDriverSettings& getSettings() const;

            /**
             * \brief Returns the current driver settings (mutable).
             * \return A reference to the settings.
             */
            TorsionDriverSettings& getSettings();

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
             * \brief Sets the callback receiving log messages emitted by the driver.
             * \param func The log-message callback.
             */
            void setLogMessageCallback(const LogMessageCallbackFunction& func);

            /**
             * \brief Returns the currently configured log-message callback.
             * \return A \c const reference to the log-message callback.
             */
            const LogMessageCallbackFunction& getLogMessageCallback() const;

            /**
             * \brief Sets up the driver for \a molgraph with the default rotatable bond perception.
             * \param molgraph The input molecular graph.
             * \return A ConfGen::ReturnCode value reporting the outcome of the setup.
             */
            unsigned int setup(const Chem::MolecularGraph& molgraph);

            /**
             * \brief Sets up the driver for \a molgraph using only the bonds whose corresponding bit is set in \a bond_mask as rotatable.
             * \param molgraph The input molecular graph.
             * \param bond_mask The bit mask of rotatable bonds (one bit per bond of \a molgraph).
             * \return A ConfGen::ReturnCode value reporting the outcome of the setup.
             */
            unsigned int setup(const Chem::MolecularGraph& molgraph, const Util::BitSet& bond_mask);

            /**
             * \brief Removes all stored input coordinates.
             */
            void clearInputCoordinates();

            /**
             * \brief Removes all input coordinates of the fragment at index \a frag_idx.
             * \param frag_idx The zero-based fragment index.
             */
            void clearInputCoordinates(std::size_t frag_idx);

            /**
             * \brief Adds \a coords as a new starting conformation that the driver will torsion-drive.
             * \param coords The input 3D coordinates.
             */
            void addInputCoordinates(const Math::Vector3DArray& coords);

            /**
             * \brief Adds \a coords as a new starting conformation restricted to the fragment at index \a frag_idx.
             * \param coords The input 3D coordinates of the fragment.
             * \param frag_idx The zero-based fragment index.
             */
            void addInputCoordinates(const Math::Vector3DArray& coords, std::size_t frag_idx);

            /**
             * \brief Adds the conformer data \a conf_data as a new starting conformation restricted to the fragment at index \a frag_idx.
             * \param conf_data The input conformer data.
             * \param frag_idx The zero-based fragment index.
             */
            void addInputCoordinates(const ConformerData& conf_data, std::size_t frag_idx);

            /**
             * \brief Adds the conformer data shared pointer \a conf_data as a new starting conformation restricted to the fragment at index \a frag_idx.
             * \param conf_data The input conformer data.
             * \param frag_idx The zero-based fragment index.
             */
            void addInputCoordinates(const ConformerData::SharedPointer& conf_data, std::size_t frag_idx);

            /**
             * \brief Returns the number of fragments produced by the rotatable bond decomposition.
             * \return The fragment count.
             */
            std::size_t getNumFragments() const;

            /**
             * \brief Returns the fragment at index \a idx.
             * \param idx The zero-based fragment index.
             * \return A \c const reference to the fragment.
             * \throw Base::IndexError if the number of fragments is zero or \a idx is not in the range [0, getNumFragments() - 1].
             */
            const Chem::Fragment& getFragment(std::size_t idx) const;

            /**
             * \brief Runs the torsion-driving conformer enumeration.
             * \return A ConfGen::ReturnCode value reporting the outcome of the generation.
             */
            unsigned int generateConformers();

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
            typedef std::unique_ptr<TorsionDriverImpl> ImplementationPointer;

            ImplementationPointer impl;
        };
    } // namespace ConfGen
} // namespace CDPL

#endif // CDPL_CONFGEN_TORSIONDRIVER_HPP
