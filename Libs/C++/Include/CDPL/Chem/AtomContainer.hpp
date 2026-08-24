/* 
 * AtomContainer.hpp 
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
 * \brief Definition of class CDPL::Chem::AtomContainer.
 */

#ifndef CDPL_CHEM_ATOMCONTAINER_HPP
#define CDPL_CHEM_ATOMCONTAINER_HPP

#include <cstddef>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/Entity3DContainer.hpp"
#include "CDPL/Chem/AtomCompareFunction.hpp"
#include "CDPL/Util/IndexedElementIterator.hpp"


namespace CDPL
{

    namespace Chem
    {

        class Atom;

        /**
         * \brief Common interface for data structures that support a random access to stored Chem::Atom instances.
         *
         * Implementations have to guarantee that a given Chem::Atom object is stored only once and its index is unique amongst
         * all contained Chem::Atom instances. Otherwise algorithms that rely on this behaviour may not work correctly!
         */
        class CDPL_CHEM_API AtomContainer : public Entity3DContainer
        {

            class ConstAtomAccessor;
            class AtomAccessor;

          public:
            /**
             * \brief A constant random access iterator used to iterate over the stored \c const Chem::Atom objects.
             */
            typedef Util::IndexedElementIterator<const Atom, ConstAtomAccessor> ConstAtomIterator;

            /**
             * \brief A mutable random access iterator used to iterate over the stored Chem::Atom objects.
             */
            typedef Util::IndexedElementIterator<Atom, AtomAccessor> AtomIterator;

            /**
             * \brief Returns the number of atoms
             * \return The number of atoms.
             */
            virtual std::size_t getNumAtoms() const = 0;

            /**
             * \brief Returns a \c const reference to the atom at index \a idx.
             * \param idx The zero-based index of the atom to return.
             * \return A \c const reference to the atom at the specified index.
             * \throw Base::IndexError if \a idx is not in the range [0, getNumAtoms()).
             */
            virtual const Atom& getAtom(std::size_t idx) const = 0;

            /**
             * \brief Returns a non-\c const reference to the atom at index \a idx.
             * \param idx The zero-based index of the atom to return.
             * \return A non-\c const reference to the atom at the specified index.
             * \throw Base::IndexError if \a idx is not in the range [0, getNumAtoms()).
             */
            virtual Atom& getAtom(std::size_t idx) = 0;

            /**
             * \brief Returns a constant iterator pointing to the beginning of the stored \c const Chem::Atom objects.
             * \return A constant iterator pointing to the beginning of the stored \c const Chem::Atom objects.
             */
            ConstAtomIterator getAtomsBegin() const;

            /**
             * \brief Returns a constant iterator pointing to the end of the stored \c const Chem::Atom objects.
             * \return A constant iterator pointing to the end of the stored \c const Chem::Atom objects.
             */
            ConstAtomIterator getAtomsEnd() const;

            /**
             * \brief Returns a mutable iterator pointing to the beginning of the stored Chem::Atom objects.
             * \return A mutable iterator pointing to the beginning of the stored Chem::Atom objects.
             */
            AtomIterator getAtomsBegin();

            /**
             * \brief Returns a mutable iterator pointing to the end of the stored Chem::Atom objects.
             * \return A mutable iterator pointing to the end of the stored Chem::Atom objects.
             */
            AtomIterator getAtomsEnd();

            /**
             * \brief Returns a constant iterator pointing to the beginning of the stored \c const Chem::Atom objects.
             * \return A constant iterator pointing to the beginning of the stored \c const Chem::Atom objects.
             */
            ConstAtomIterator begin() const;

            /**
             * \brief Returns a constant iterator pointing to the end of the stored \c const Chem::Atom objects.
             * \return A constant iterator pointing to the end of the stored \c const Chem::Atom objects.
             */
            ConstAtomIterator end() const;

            /**
             * \brief Returns a mutable iterator pointing to the beginning of the stored Chem::Atom objects.
             * \return A mutable iterator pointing to the beginning of the stored Chem::Atom objects.
             */
            AtomIterator begin();

            /**
             * \brief Returns a mutable iterator pointing to the end of the stored Chem::Atom objects.
             * \return A mutable iterator pointing to the end of the stored Chem::Atom objects.
             */
            AtomIterator end();

            /**
             * \brief Tells whether the specified atom is part of the atom sequence.
             * \param atom The atom to look for.
             * \return \c true if \a atom is part of the sequence, and \c false otherwise.
             */
            virtual bool containsAtom(const Atom& atom) const = 0;

            /**
             * \brief Returns the index of the specified atom.
             * \param atom The atom for which to return the index.
             * \return The zero-based index of the specified atom.
             * \throw Base::ItemNotFound if the specified atom could not be found.
             */
            virtual std::size_t getAtomIndex(const Atom& atom) const = 0;

            /**
             * \brief Returns the number of stored Chem::Entity3D objects.
             *
             * Forwards to getNumAtoms() and exists to satisfy the Chem::Entity3DContainer interface.
             *
             * \return The number of contained atoms.
             */
            virtual std::size_t getNumEntities() const;

            /**
             * \brief Returns a \c const reference to the entity at index \a idx.
             *
             * Forwards to getAtom() and exists to satisfy the Chem::Entity3DContainer interface.
             *
             * \param idx The zero-based entity index.
             * \return A \c const reference to the entity at the specified index.
             * \throw Base::IndexError if \a idx is not in the range [0, getNumAtoms()).
             */
            virtual const Chem::Entity3D& getEntity(std::size_t idx) const;

            /**
             * \brief Returns a non-\c const reference to the entity at index \a idx.
             *
             * Forwards to getAtom() and exists to satisfy the Chem::Entity3DContainer interface.
             *
             * \param idx The zero-based entity index.
             * \return A non-\c const reference to the entity at the specified index.
             * \throw Base::IndexError if \a idx is not in the range [0, getNumAtoms()).
             */
            virtual Chem::Entity3D& getEntity(std::size_t idx);

            /**
             * \brief Orders the atoms according to criteria implemented by the provided atom comparison function.
             * \param func The atom comparison function implementing the applied ordering criteria.
             */
            virtual void orderAtoms(const AtomCompareFunction& func) = 0;

            /**
             * \brief Returns a \c const reference to itself.
             * \return A \c const reference to itself.
             */
            const AtomContainer& getAtoms() const
            {
                return *this;
            }

            /**
             * \brief Returns a reference to itself.
             * \return A reference to itself.
             */
            AtomContainer& getAtoms()
            {
                return *this;
            }

          protected:
            /**
             * \brief Virtual destructor.
             */
            virtual ~AtomContainer() {}

            /**
             * \brief Replaces the current set of properties by a copy of the
             *        properties of the container \a cntnr.
             * \param cntnr The container to copy.
             * \return A reference to itself.
             */
            AtomContainer& operator=(const AtomContainer& cntnr);

          private:
            class CDPL_CHEM_API ConstAtomAccessor
            {

              public:
                ConstAtomAccessor(const AtomAccessor& accessor):
                    container(accessor.container) {}

                ConstAtomAccessor(const AtomContainer* cntnr):
                    container(cntnr) {}

                const Atom& operator()(std::size_t idx) const
                {
                    return container->getAtom(idx);
                }

                bool operator==(const ConstAtomAccessor& accessor) const
                {
                    return (container == accessor.container);
                }

                ConstAtomAccessor& operator=(const AtomAccessor& accessor)
                {
                    container = accessor.container;
                    return *this;
                }

              private:
                const AtomContainer* container;
            };

            class CDPL_CHEM_API AtomAccessor
            {

                friend class ConstAtomAccessor;

              public:
                AtomAccessor(AtomContainer* cntnr):
                    container(cntnr) {}

                Atom& operator()(std::size_t idx) const
                {
                    return container->getAtom(idx);
                }

                bool operator==(const AtomAccessor& accessor) const
                {
                    return (container == accessor.container);
                }

              private:
                AtomContainer* container;
            };
        };
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_ATOMCONTAINER_HPP
