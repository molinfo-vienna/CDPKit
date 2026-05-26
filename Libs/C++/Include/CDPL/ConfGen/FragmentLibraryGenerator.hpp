/* 
 * FragmentLibraryGenerator.hpp 
 *
 * This file is part of the ConfGenical Data Processing Toolkit
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
 * \brief Definition of class CDPL::ConfGen::FragmentLibraryGenerator.
 */

#ifndef CDPL_CONFGEN_FRAGMENTLIBRARYGENERATOR_HPP
#define CDPL_CONFGEN_FRAGMENTLIBRARYGENERATOR_HPP

#include <sstream>

#include "CDPL/ConfGen/APIPrefix.hpp"
#include "CDPL/ConfGen/FragmentLibrary.hpp"
#include "CDPL/ConfGen/CanonicalFragment.hpp"
#include "CDPL/ConfGen/FragmentConformerGenerator.hpp"
#include "CDPL/Chem/SMILESMolecularGraphWriter.hpp"


namespace CDPL
{

    namespace ConfGen
    {

        /**
         * \brief Driver for populating a ConfGen::FragmentLibrary with conformers of canonicalized
         *        molecular fragments.
         *
         * For each input fragment the generator constructs the corresponding ConfGen::CanonicalFragment,
         * computes its hash code and SMILES string, generates a representative conformer ensemble using
         * ConfGen::FragmentConformerGenerator and stores the result as a new FragmentLibraryEntry in
         * the associated FragmentLibrary. Already-present entries (identified by hash code) are skipped.
         */
        class CDPL_CONFGEN_API FragmentLibraryGenerator
        {

          public:
            /**
             * \brief Constructs the \c %FragmentLibraryGenerator instance without an associated fragment library.
             */
            FragmentLibraryGenerator();

            /**
             * \brief Constructs the \c %FragmentLibraryGenerator instance and associates it with \a lib.
             * \param lib The fragment library to populate.
             */
            FragmentLibraryGenerator(const FragmentLibrary::SharedPointer& lib);

            FragmentLibraryGenerator(const FragmentLibraryGenerator&) = delete;

            FragmentLibraryGenerator& operator=(const FragmentLibraryGenerator&) = delete;

            /**
             * \brief Sets the fragment library to populate.
             * \param lib The new fragment library.
             */
            void setFragmentLibrary(const FragmentLibrary::SharedPointer& lib);

            /**
             * \brief Returns the currently associated fragment library.
             * \return A \c const reference to the fragment library smart pointer.
             */
            const FragmentLibrary::SharedPointer& getFragmentLibrary() const;

            /**
             * \brief Returns a reference to the fragment conformer-generation settings.
             * \return A reference to the settings.
             */
            FragmentConformerGeneratorSettings& getSettings();

            /**
             * \brief Returns a \c const reference to the fragment conformer-generation settings.
             * \return A \c const reference to the settings.
             */
            const FragmentConformerGeneratorSettings& getSettings() const;

            /**
             * \brief Sets the callback invoked periodically to allow conformer generation to be aborted.
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
             * \brief Sets the callback that receives log messages produced during fragment processing.
             * \param func The log-message callback.
             */
            void setLogMessageCallback(const LogMessageCallbackFunction& func);

            /**
             * \brief Returns the currently configured log-message callback.
             * \return A \c const reference to the log-message callback.
             */
            const LogMessageCallbackFunction& getLogMessageCallback() const;

            /**
             * \brief Adds a library entry for the fragment \a frag of the parent molecular graph \a parent.
             * \param frag The fragment to add.
             * \param parent The parent molecular graph the fragment was derived from.
             * \return A status code defined in ConfGen::ReturnCode.
             */
            unsigned int process(const Chem::MolecularGraph& frag, const Chem::MolecularGraph& parent);

            /**
             * \brief Returns the number of conformers generated during the last process() call.
             * \return The number of generated conformers.
             */
            std::size_t getNumGeneratedConformers() const;

            /**
             * \brief Returns the hash code of the library entry created during the last process() call.
             * \return The hash code of the library entry.
             */
            std::uint64_t getLibraryEntryHashCode() const;

          private:
            FragmentLibraryEntry::SharedPointer addNewLibraryEntry(const Chem::MolecularGraph& frag, const Chem::MolecularGraph& parent);

            void removeNewLibraryEntry() const;

            void init();

            FragmentLibrary::SharedPointer   fragLib;
            CanonicalFragment                canonFrag;
            FragmentConformerGenerator       fragConfGen;
            std::ostringstream               smilesStream;
            Chem::SMILESMolecularGraphWriter smilesGen;
            std::size_t                      numGenConfs;
        };
    } // namespace ConfGen
} // namespace CDPL

#endif // CDPL_CONFGEN_FRAGMENTLIBRARYGENERATOR_HPP
