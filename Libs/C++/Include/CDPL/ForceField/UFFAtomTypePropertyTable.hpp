/* 
 * UFFAtomTypePropertyTable.hpp 
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
 * \brief Definition of the class CDPL::ForceField::UFFAtomTypePropertyTable.
 */

#ifndef CDPL_FORCEFIELD_UFFATOMTYPEPROPERTYTABLE_HPP
#define CDPL_FORCEFIELD_UFFATOMTYPEPROPERTYTABLE_HPP

#include <cstddef>
#include <string>
#include <unordered_map>
#include <memory>
#include <functional>

#include <boost/iterator/transform_iterator.hpp>

#include "CDPL/ForceField/APIPrefix.hpp"


namespace CDPL
{

    namespace ForceField
    {

        class CDPL_FORCEFIELD_API UFFAtomTypePropertyTable
        {

          public:
            class Entry;

          private:
            typedef std::unordered_map<unsigned int, Entry> DataStorage;

          public:
            typedef std::shared_ptr<UFFAtomTypePropertyTable> SharedPointer;

            class CDPL_FORCEFIELD_API Entry
            {

              public:
                Entry();

                Entry(unsigned int atom_type, const std::string& atom_type_sym, unsigned int atomic_no, double bond_rad,
                      double bond_ang, double vdw_dist, double vdw_energy, double vdw_scale, double eff_charge);

                unsigned int getAtomType() const;

                const std::string& getAtomTypeSymbol() const;

                unsigned int getAtomicNumber() const;

                double getBondRadius() const;

                double getBondAngle() const;

                double getVdWDistance() const;

                double getVdWEnergy() const;

                double getVdWScale() const;

                double getEffectiveCharge() const;

                operator bool() const;

              private:
                unsigned int atomType;
                std::string  atomTypeSym;
                unsigned int atomicNo;
                double       bondRadius;
                double       bondAngle;
                double       vdwDistance;
                double       vdwEnergy;
                double       vdwScale;
                double       effCharge;
                bool         initialized;
            };

            typedef boost::transform_iterator<std::function<const Entry&(const DataStorage::value_type&)>,
                                              DataStorage::const_iterator>
                ConstEntryIterator;

            typedef boost::transform_iterator<std::function<Entry&(DataStorage::value_type&)>,
                                              DataStorage::iterator>
                EntryIterator;

            UFFAtomTypePropertyTable();

            void addEntry(unsigned int atom_type, const std::string& atom_type_sym, unsigned int atomic_no, double bond_rad,
                          double bond_ang, double vdw_dist, double vdw_energy, double vdw_scale, double eff_charge);

            const Entry& getEntry(unsigned int atom_type) const;

            std::size_t getNumEntries() const;

            void clear();

            bool removeEntry(unsigned int atom_type);

            EntryIterator removeEntry(const EntryIterator& it);

            ConstEntryIterator getEntriesBegin() const;

            ConstEntryIterator getEntriesEnd() const;

            EntryIterator getEntriesBegin();

            EntryIterator getEntriesEnd();

            ConstEntryIterator begin() const;

            ConstEntryIterator end() const;

            EntryIterator begin();

            EntryIterator end();

            void loadDefaults();

            static void set(const SharedPointer& table);

            static const SharedPointer& get();

          private:
            static SharedPointer defaultTable;
            DataStorage          entries;
        };
    } // namespace ForceField
} // namespace CDPL

#endif // CDPL_FORCEFIELD_UFFATOMTYPEPROPERTYTABLE_HPP
