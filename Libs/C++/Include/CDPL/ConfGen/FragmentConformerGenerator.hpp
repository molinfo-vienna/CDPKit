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
 * \brief Definition of the class CDPL::ConfGen::FragmentConformerGenerator.
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

        class CDPL_CONFGEN_API FragmentConformerGenerator
        {

          public:
            typedef boost::indirect_iterator<ConformerDataArray::const_iterator, const ConformerData> ConstConformerIterator;
            typedef boost::indirect_iterator<ConformerDataArray::const_iterator, ConformerData>       ConformerIterator;

            FragmentConformerGenerator();

            FragmentConformerGenerator(const FragmentConformerGenerator&) = delete;

            ~FragmentConformerGenerator();

            FragmentConformerGenerator& operator=(const FragmentConformerGenerator&) = delete;

            FragmentConformerGeneratorSettings& getSettings();

            const FragmentConformerGeneratorSettings& getSettings() const;

            void setAbortCallback(const CallbackFunction& func);

            const CallbackFunction& getAbortCallback() const;

            void setTimeoutCallback(const CallbackFunction& func);

            const CallbackFunction& getTimeoutCallback() const;

            void setLogMessageCallback(const LogMessageCallbackFunction& func);

            const LogMessageCallbackFunction& getLogMessageCallback() const;

            unsigned int generate(const Chem::MolecularGraph& molgraph);

            unsigned int generate(const Chem::MolecularGraph& molgraph, unsigned int frag_type);

            /*
             * \since 1.1
             */
            unsigned int generate(const Chem::MolecularGraph& molgraph, const Chem::MolecularGraph& fixed_substr,
                                  const Math::Vector3DArray& fixed_substr_coords);

            /*
             * \since 1.1
             */
            unsigned int generate(const Chem::MolecularGraph& molgraph, unsigned int frag_type,
                                  const Chem::MolecularGraph& fixed_substr,
                                  const Math::Vector3DArray& fixed_substr_coords);

            void setConformers(Chem::MolecularGraph& molgraph) const;

            std::size_t getNumConformers() const;

            const ConformerData& getConformer(std::size_t idx) const;

            ConformerData& getConformer(std::size_t idx);

            ConstConformerIterator getConformersBegin() const;

            ConstConformerIterator getConformersEnd() const;

            ConformerIterator getConformersBegin();

            ConformerIterator getConformersEnd();

            ConstConformerIterator begin() const;

            ConstConformerIterator end() const;

            ConformerIterator begin();

            ConformerIterator end();

          private:
            typedef std::unique_ptr<FragmentConformerGeneratorImpl> ImplementationPointer;

            ImplementationPointer impl;
        };
    } // namespace ConfGen
} // namespace CDPL

#endif // CDPL_CONFGEN_FRAGMENTCONFORMERGENERATOR_HPP
