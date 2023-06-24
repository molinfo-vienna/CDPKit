/* 
 * ConnectedSubstructureSet.hpp 
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
 * \brief Definition of the class CDPL::Chem::ConnectedSubstructureSet.
 */

#ifndef CDPL_CHEM_CONNECTEDSUBSTRUCTURESET_HPP
#define CDPL_CHEM_CONNECTEDSUBSTRUCTURESET_HPP

#include <cstddef>
#include <vector>
#include <memory>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/FragmentList.hpp"
#include "CDPL/Util/BitSet.hpp"
#include "CDPL/Util/ObjectPool.hpp"


namespace CDPL
{

    namespace Chem
    {

        /**
         * \brief ConnectedSubstructureSet.
         */
        class CDPL_CHEM_API ConnectedSubstructureSet : public FragmentList
        {

          public:
            /**    
             * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %ConnectedSubstructureSet instances.
             */
            typedef std::shared_ptr<ConnectedSubstructureSet> SharedPointer;

            /**
             * \brief Constructs an empty \c %ConnectedSubstructureSet instance.
             */
            ConnectedSubstructureSet();

            /**
             * \brief Constructs and initialzes a \c %ConnectedSubstructureSet instance for the molecular graph \a molgraph.
             * \param molgraph The molecular graph to search for connected substructures.
             */
            ConnectedSubstructureSet(const MolecularGraph& molgraph);

            /**
             * \brief Specifies the molecular graph that is searched for connected substructures.
             *
             * The current substructure size is reset to zero.
             *
             * \param molgraph The molecular graph to search for connected substructures.
             */
            void reset(const MolecularGraph& molgraph);

            /**
             * \brief Searches the specified molecular graph for connected substructures of the given size.
             * 
             * If a molecular graph has not yet been specified (in the constructor or by a prior call to reset(const Chem::MolecularGraph&)), the
             * method has no effect. Otherwise, all connected substructures of the specified size are added as Chem::Fragment
             * objects to the list of previously found (if any) substructures. If the specified size is zero, substructures
             * of size \e 1 (i.e. the bonds of the molecular graph) will be extracted.
             *
             * \param size The substructure size in terms of number of bonds.
             */
            void findSubstructures(std::size_t size);

            /**
             * \brief Returns the current substructure size in terms of number of bonds.
             *
             * The current substructure size corresponds to the size that was specified in the the last call to findSubstructures().
             * If findSubstructures() has not yet been called, the current substructure size is zero.
             *
             * \return The current substructure size.
             */
            std::size_t getSubstructureSize() const;

          private:
            class SubstructDescriptor;

            typedef Util::ObjectPool<SubstructDescriptor>         SubstructDescriptorCache;
            typedef SubstructDescriptorCache::SharedObjectPointer SubstructDescriptorPtr;

            ConnectedSubstructureSet(const ConnectedSubstructureSet&);

            ConnectedSubstructureSet& operator=(const ConnectedSubstructureSet&);

            void reset();

            void growSubstructDescriptors(std::size_t);
            void createSubstructFragments();

            SubstructDescriptorPtr allocSubstructDescriptor(const Bond&);

            class SubstructDescriptor
            {

              public:
                void init(const MolecularGraph*, const Bond&);

                bool grow(const Util::BitSet&);
                void ungrow();

                Fragment::SharedPointer createFragment() const;

                void copy(const SubstructDescriptor&);

                bool operator<(const SubstructDescriptor&) const;

              private:
                typedef std::vector<const Atom*> AtomList;
                typedef std::vector<std::size_t> BondCountList;

                const MolecularGraph* molGraph;
                Util::BitSet          bondMask;
                AtomList              unsatAtoms;
                BondCountList         atomBondCounts;
                std::size_t           unsatAListIdx;
                std::size_t           nbrBListIdx;
                std::size_t           lastBondIdx;
                bool                  addedAtom;
                const Atom*           startAtom;
            };

            struct SubstructDescriptorLessCmpFunc
            {

                bool operator()(const SubstructDescriptorPtr&, const SubstructDescriptorPtr&) const;
            };

            typedef std::vector<SubstructDescriptorPtr> SubstructDescriptorList;

            SubstructDescriptorCache substructDescrCache;
            SubstructDescriptorList  foundSubstructDescriptors;
            Util::BitSet             bondMask;
            std::size_t              currSubstructSize;
            const MolecularGraph*    molGraph;
        };
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_CONNECTEDSUBSTRUCTURESET_HPP
