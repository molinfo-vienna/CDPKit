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
 * \brief Definition of the class CDPL::ConfGen::TorsionDriver.
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
    }

    namespace ConfGen 
    {

        class TorsionDriverImpl;

        class CDPL_CONFGEN_API TorsionDriver
        {

          public:
            typedef boost::indirect_iterator<ConformerDataArray::const_iterator, const ConformerData> ConstConformerIterator;
            typedef boost::indirect_iterator<ConformerDataArray::const_iterator, ConformerData> ConformerIterator;

            TorsionDriver();

            ~TorsionDriver();
    
            const TorsionDriverSettings& getSettings() const;

            TorsionDriverSettings& getSettings();

            void clearTorsionLibraries();

            void addTorsionLibrary(const TorsionLibrary::SharedPointer& lib);

            void setAbortCallback(const CallbackFunction& func);

            const CallbackFunction& getAbortCallback() const;

            void setTimeoutCallback(const CallbackFunction& func);

            const CallbackFunction& getTimeoutCallback() const;

            void setLogMessageCallback(const LogMessageCallbackFunction& func);

            const LogMessageCallbackFunction& getLogMessageCallback() const;

            unsigned int setup(const Chem::MolecularGraph& molgraph);
            unsigned int setup(const Chem::MolecularGraph& molgraph, const Util::BitSet& bond_mask);

            void clearInputCoordinates();
            void clearInputCoordinates(std::size_t frag_idx);

            void addInputCoordinates(const Math::Vector3DArray& coords);
            void addInputCoordinates(const Math::Vector3DArray& coords, std::size_t frag_idx);
            void addInputCoordinates(const ConformerData& conf_data, std::size_t frag_idx);
            void addInputCoordinates(const ConformerData::SharedPointer& conf_data, std::size_t frag_idx);

            std::size_t getNumFragments() const;

            const Chem::Fragment& getFragment(std::size_t idx) const;

            unsigned int generateConformers();

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
            TorsionDriver(const TorsionDriver&);

            TorsionDriver& operator=(const TorsionDriver&);

            typedef std::auto_ptr<TorsionDriverImpl> ImplementationPointer;

            ImplementationPointer impl;
        };
    }
}

#endif // CDPL_CONFGEN_TORSIONDRIVER_HPP
