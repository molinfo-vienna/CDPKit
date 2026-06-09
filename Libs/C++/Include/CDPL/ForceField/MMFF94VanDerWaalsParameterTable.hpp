/* 
 * MMFF94VanDerWaalsParameterTable.hpp 
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
 * \brief Definition of class CDPL::ForceField::MMFF94VanDerWaalsParameterTable.
 */

#ifndef CDPL_FORCEFIELD_MMFF94VANDERWAALSPARAMETERTABLE_HPP
#define CDPL_FORCEFIELD_MMFF94VANDERWAALSPARAMETERTABLE_HPP

#include <iosfwd>
#include <cstddef>
#include <unordered_map>
#include <memory>
#include <functional>

#include <boost/iterator/transform_iterator.hpp>

#include "CDPL/ForceField/APIPrefix.hpp"
#include "CDPL/ForceField/MMFF94VanDerWaalsInteraction.hpp"


namespace CDPL
{

    namespace ForceField
    {

        /**
         * \brief Lookup table mapping numeric MMFF94 atom types to per-atom type Van der Waals parameters
         *        (atomic polarizability, effective electron number, scaling factors A/G, and H-donor/-acceptor classification).
         *
         * In addition to the per-atom type entries, the table also stores the five global scalar parameters
         * (exponent, B, beta, DARAD, DAEPS) used by the buffered 14-7 MMFF94 Van der Waals energy expression.
         */
        class CDPL_FORCEFIELD_API MMFF94VanDerWaalsParameterTable
        {

          public:
            class Entry;

          private:
            typedef std::unordered_map<unsigned int, Entry> DataStorage;

          public:
            /** \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %MMFF94VanDerWaalsParameterTable instances. */
            typedef std::shared_ptr<MMFF94VanDerWaalsParameterTable> SharedPointer;
            /** \brief Alias for the H-donor/-acceptor classification enum defined on MMFF94VanDerWaalsInteraction. */
            typedef MMFF94VanDerWaalsInteraction::HDonorAcceptorType HDonorAcceptorType;

            /**
             * \brief A single per-atom type Van der Waals parameter record.
             */
            class CDPL_FORCEFIELD_API Entry
            {

              public:
                /**
                 * \brief Constructs an empty (uninitialized) \c %Entry instance.
                 */
                Entry();

                /**
                 * \brief Constructs an \c %Entry for the numeric MMFF94 atom type \a atom_type.
                 * \param atom_type The numeric MMFF94 atom type.
                 * \param atom_pol The atomic polarizability parameter.
                 * \param eff_el_num The Slater-Kirkwood effective number of valence electrons.
                 * \param fact_a The scaling factor \c A.
                 * \param fact_g The scaling factor \c G.
                 * \param don_acc_type The H-donor/-acceptor classification of the atom type.
                 */
                Entry(unsigned int atom_type, double atom_pol, double eff_el_num, double fact_a, double fact_g,
                      HDonorAcceptorType don_acc_type);

                /**
                 * \brief Returns the numeric MMFF94 atom type of the entry.
                 * \return The numeric atom type.
                 */
                unsigned int getAtomType() const;

                /**
                 * \brief Returns the atomic polarizability parameter.
                 * \return The atomic polarizability.
                 */
                double getAtomicPolarizability() const;

                /**
                 * \brief Returns the Slater-Kirkwood effective number of valence electrons parameter.
                 * \return The Slater-Kirkwood effective number of valence electrons.
                 */
                double getEffectiveElectronNumber() const;

                /**
                 * \brief Returns the scaling factor A parameter.
                 * \return The scaling factor A.
                 */
                double getFactorA() const;

                /**
                 * \brief Returns the scaling factor G parameter.
                 * \return The scaling factor G
                 */
                double getFactorG() const;

                /**
                 * \brief Returns the H-donor/-acceptor classification associated with the numeric MMFF94 atom type.
                 * \return The H-donor/-acceptor classification.
                 */
                HDonorAcceptorType getHDonorAcceptorType() const;

                /**
                 * \brief Tells whether the entry holds initialized data.
                 * \return \c true if the entry was constructed with explicit values, and \c false if it is the empty default.
                 */
                operator bool() const;

              private:
                unsigned int       atomType;
                double             polarizability;
                double             effElNumber;
                double             factA;
                double             factG;
                HDonorAcceptorType donAccType;
                bool               initialized;
            };

            /** \brief A constant iterator over the entries of the table. */
            typedef boost::transform_iterator<std::function<const Entry&(const DataStorage::value_type&)>,
                                              DataStorage::const_iterator>
                ConstEntryIterator;

            /** \brief A mutable iterator over the entries of the table. */
            typedef boost::transform_iterator<std::function<Entry&(DataStorage::value_type&)>,
                                              DataStorage::iterator>
                EntryIterator;

            /**
             * \brief Constructs an empty \c %MMFF94VanDerWaalsParameterTable instance.
             */
            MMFF94VanDerWaalsParameterTable();

            /**
             * \brief Adds (or overwrites) the entry for the numeric MMFF94 atom type \a atom_type.
             * \param atom_type The numeric MMFF94 atom type.
             * \param atom_pol The atomic polarizability parameter.
             * \param eff_el_num The Slater-Kirkwood effective number of valence electrons.
             * \param fact_a The scaling factor \c A.
             * \param fact_g The scaling factor \c G.
             * \param don_acc_type The H-donor/-acceptor classification of the atom type.
             */
            void addEntry(unsigned int atom_type, double atom_pol, double eff_el_num, double fact_a, double fact_g,
                          HDonorAcceptorType don_acc_type);

            /**
             * \brief Returns the entry for the numeric MMFF94 atom type \a atom_type.
             * \param atom_type The numeric MMFF94 atom type.
             * \return A \c const reference to the matching entry, or to an uninitialized entry (whose <tt>operator bool()</tt> returns \c false) if no match exists.
             */
            const Entry& getEntry(unsigned int atom_type) const;

            /**
             * \brief Returns the number of entries in the table.
             * \return The entry count.
             */
            std::size_t getNumEntries() const;

            /**
             * \brief Removes all entries from the table.
             */
            void clear();

            /**
             * \brief Removes the entry for the numeric MMFF94 atom type \a atom_type.
             * \param atom_type The numeric MMFF94 atom type.
             * \return \c true if a matching entry was removed, and \c false if no such entry existed.
             */
            bool removeEntry(unsigned int atom_type);

            /**
             * \brief Removes the entry pointed to by the iterator \a it.
             * \param it An iterator pointing to the entry to remove.
             * \return An iterator pointing to the entry immediately following the removed one.
             */
            EntryIterator removeEntry(const EntryIterator& it);

            /**
             * \brief Returns a constant iterator pointing to the beginning of the entry list.
             * \return A constant iterator to the first entry.
             */
            ConstEntryIterator getEntriesBegin() const;

            /**
             * \brief Returns a constant iterator pointing one past the last entry.
             * \return A constant iterator to the end of the entry list.
             */
            ConstEntryIterator getEntriesEnd() const;

            /**
             * \brief Returns a mutable iterator pointing to the beginning of the entry list.
             * \return A mutable iterator to the first entry.
             */
            EntryIterator getEntriesBegin();

            /**
             * \brief Returns a mutable iterator pointing one past the last entry.
             * \return A mutable iterator to the end of the entry list.
             */
            EntryIterator getEntriesEnd();

            /**
             * \brief Returns a constant iterator pointing to the beginning of the entry list (alias of getEntriesBegin()).
             * \return A constant iterator to the first entry.
             */
            ConstEntryIterator begin() const;

            /**
             * \brief Returns a constant iterator pointing one past the last entry (alias of getEntriesEnd()).
             * \return A constant iterator to the end of the entry list.
             */
            ConstEntryIterator end() const;

            /**
             * \brief Returns a mutable iterator pointing to the beginning of the entry list (alias of getEntriesBegin()).
             * \return A mutable iterator to the first entry.
             */
            EntryIterator begin();

            /**
             * \brief Returns a mutable iterator pointing one past the last entry (alias of getEntriesEnd()).
             * \return A mutable iterator to the end of the entry list.
             */
            EntryIterator end();

            /**
             * \brief Sets the global exponent used in the buffered 14-7 Van der Waals energy expression.
             * \param value The new exponent value.
             */
            void setExponent(double value);

            /**
             * \brief Sets the global \e beta value used in the buffered 14-7 Van der Waals energy expression.
             * \param value The new \e beta value.
             */
            void setBeta(double value);

            /**
             * \brief Sets the global \e B factor used in the buffered 14-7 Van der Waals energy expression.
             * \param value The new \e B factor value.
             */
            void setFactorB(double value);

            /**
             * \brief Sets the global \e DARAD factor used in the buffered 14-7 Van der Waals energy expression.
             * \param value The new \e DARAD factor value.
             */
            void setFactorDARAD(double value);

            /**
             * \brief Sets the global \e DAEPS factor used in the buffered 14-7 Van der Waals energy expression.
             * \param value The new \e DAEPS factor value.
             */
            void setFactorDAEPS(double value);

            /**
             * \brief Returns the exponent used in the calculation of Van der Waals
             *        interaction energies.
             * \return The exponent.
             */
            double getExponent() const;

            /**
             * \brief Returns the value of the \e B factor used in the calculation of Van der Waals
             *        interaction energies.
             * \return The value of the \e B factor.
             */
            double getFactorB() const;

            /**
             * \brief Returns the value of \e beta used in the calculation of Van der Waals
             *        interaction energies.
             * \return The value of \e beta.
             */
            double getBeta() const;

            /**
             * \brief Returns the value of the \e DARAD factor used in the calculation of Van der Waals
             *        interaction energies.
             * \return The value of the \e DARAD factor.
             */
            double getFactorDARAD() const;

            /**
             * \brief Returns the value of the \e DAEPS factor used in the calculation of Van der Waals
             *        interaction energies.
             * \return The value of the \e DAEPS factor.
             */
            double getFactorDAEPS() const;

            /**
             * \brief Loads table entries from the input stream \a is.
             * \param is The input stream to read from.
             */
            void load(std::istream& is);

            /**
             * \brief Loads the built-in default Van der Waals parameter entries and global scalar parameters.
             */
            void loadDefaults();

            /**
             * \brief Replaces the process-wide default table by \a table.
             * \param table The new default table (a \c nullptr resets to the built-in default).
             */
            static void set(const SharedPointer& table);

            /**
             * \brief Returns the process-wide default table (lazily initialized on first call).
             * \return A \c const reference to the default table shared pointer.
             */
            static const SharedPointer& get();

          private:
            static SharedPointer defaultTable;
            DataStorage          entries;
            double               exponent;
            double               factB;
            double               beta;
            double               factDARAD;
            double               factDAEPS;
        };
    } // namespace ForceField
} // namespace CDPL

#endif // CDPL_FORCEFIELD_MMFF94VANDERWAALSPARAMETERTABLE_HPP
