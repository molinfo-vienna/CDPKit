/* 
 * BondContainer.hpp 
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
 * \brief Definition of the class CDPL::Chem::BondContainer.
 */

#ifndef CDPL_CHEM_BONDCONTAINER_HPP
#define CDPL_CHEM_BONDCONTAINER_HPP

#include <cstddef>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/BondCompareFunction.hpp"
#include "CDPL/Util/IndexedElementIterator.hpp"


namespace CDPL
{

    namespace Chem
    {

        class Bond;

        /**
         * \brief A common interface for data-structures that support a random access to stored Chem::Bond instances.
         *
         * Implementations have to guarantee that a given Chem::Bond object is stored only once and its index is unique amongst
         * all contained Chem::Bond instances. Otherwise algorithms that rely on this behaviour may not work correctly!
         */
        class CDPL_CHEM_API BondContainer
        {

            class ConstBondAccessor;
            class BondAccessor;

          public:
            /**
             * \brief A constant random access iterator used to iterate over the stored \c const Chem::Bond objects.
             */
            typedef Util::IndexedElementIterator<const Bond, ConstBondAccessor> ConstBondIterator;

            /**
             * \brief A mutable random access iterator used to iterate over the stored Chem::Bond objects.
             */
            typedef Util::IndexedElementIterator<Bond, BondAccessor> BondIterator;

            /**
             * \brief Returns the number of stored Chem::Bond objects.
             * \return The number of stored Chem::Bond objects.
             */
            virtual std::size_t getNumBonds() const = 0;

            /**
             * \brief Returns a \c const reference to the Chem::Bond instance at index \a idx.
             * \param idx The zero-based index of the Chem::Bond instance to return.
             * \return A \c const reference to the Chem::Bond instance at the specified index.
             * \throw Base::IndexError if the container is empty or \a idx is not in the range [0, getNumBonds() - 1].
             */
            virtual const Bond& getBond(std::size_t idx) const = 0;

            /**
             * \brief Returns a non-\c const reference to the bond at index \a idx.
             * \param idx The zero-based index of the Chem::Bond instance to return.
             * \return A non-\c const reference to the bond at the specified index.
             * \throw Base::IndexError if the number of bonds is zero or \a idx is not in the range [0, getNumBonds() - 1].
             */
            virtual Bond& getBond(std::size_t idx) = 0;

            /**
             * \brief Returns a constant iterator pointing to the beginning of the stored \c const Chem::Bond objects.
             * \return A constant iterator pointing to the beginning of the stored \c const Chem::Bond objects.
             */
            ConstBondIterator getBondsBegin() const;

            /**
             * \brief Returns a constant iterator pointing to the end of the stored \c const Chem::Bond objects.
             * \return A constant iterator pointing to the end of the stored \c const Chem::Bond objects.
             */
            ConstBondIterator getBondsEnd() const;

            /**
             * \brief Returns a mutable iterator pointing to the beginning of the stored Chem::Bond objects.
             * \return A mutable iterator pointing to the beginning of the stored Chem::Bond objects.
             */
            BondIterator getBondsBegin();

            /**
             * \brief Returns a mutable iterator pointing to the end of the stored Chem::Bond objects.
             * \return A mutable iterator pointing to the end of the stored Chem::Bond objects.
             */
            BondIterator getBondsEnd();

            /**
             * \brief Returns a constant iterator pointing to the beginning of the stored \c const Chem::Bond objects.
             * \return A constant iterator pointing to the beginning of the stored \c const Chem::Bond objects.
             */
            ConstBondIterator begin() const;

            /**
             * \brief Returns a constant iterator pointing to the end of the stored \c const Chem::Bond objects.
             * \return A constant iterator pointing to the end of the stored \c const Chem::Bond objects.
             */
            ConstBondIterator end() const;

            /**
             * \brief Returns a mutable iterator pointing to the beginning of the stored Chem::Bond objects.
             * \return A mutable iterator pointing to the beginning of the stored Chem::Bond objects.
             */
            BondIterator begin();

            /**
             * \brief Returns a mutable iterator pointing to the end of the stored Chem::Bond objects.
             * \return A mutable iterator pointing to the end of the stored Chem::Bond objects.
             */
            BondIterator end();

            /**
             * \brief Tells whether the specified Chem::Bond instance is stored in this container.
             * \param bond The Chem::Bond instance to look for.
             * \return \c true if \a bond is stored in the container, and \c false otherwise.
             */
            virtual bool containsBond(const Bond& bond) const = 0;

            /**
             * \brief Returns the index of the specified Chem::Bond instance in this container.
             * \param bond The Chem::Bond instance for which to return the index.
             * \return The zero-based index of the specified Chem::Bond instance.
             * \throw Base::ItemNotFound if the specified Chem::Bond instance could not be found.
             */
            virtual std::size_t getBondIndex(const Bond& bond) const = 0;

            /**
              * \brief Orders the stored bonds according to criteria implemented by the provided bond comparison function.
              * \param func The bond comparison function implementing the applied ordering criteria.
              */
            virtual void orderBonds(const BondCompareFunction& func) = 0;

          protected:
            /**
             * \brief Virtual destructor.
             */
            virtual ~BondContainer() {}

            /**
             * \brief Assignment operator.
             * \param cntnr The other container to copy.
             * \return A reference to itself.
             */
            BondContainer& operator=(const BondContainer& cntnr);

          private:
            class CDPL_CHEM_API ConstBondAccessor
            {

              public:
                ConstBondAccessor(const BondAccessor& accessor):
                    container(accessor.container) {}

                ConstBondAccessor(const BondContainer* cntnr):
                    container(cntnr) {}

                const Bond& operator()(std::size_t idx) const
                {
                    return container->getBond(idx);
                }

                bool operator==(const ConstBondAccessor& accessor) const
                {
                    return (container == accessor.container);
                }

                ConstBondAccessor& operator=(const BondAccessor& accessor)
                {
                    container = accessor.container;
                    return *this;
                }

              private:
                const BondContainer* container;
            };

            class CDPL_CHEM_API BondAccessor
            {

                friend class ConstBondAccessor;

              public:
                BondAccessor(BondContainer* cntnr):
                    container(cntnr) {}

                Bond& operator()(std::size_t idx) const
                {
                    return container->getBond(idx);
                }

                bool operator==(const BondAccessor& accessor) const
                {
                    return (container == accessor.container);
                }

              private:
                BondContainer* container;
            };
        };
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_BONDCONTAINER_HPP
