/* 
 * AtomDictionary.hpp 
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
 * \brief Definition of the class CDPL::Chem::AtomDictionary.
 */

#ifndef CDPL_CHEM_ATOMDICTIONARY_HPP
#define CDPL_CHEM_ATOMDICTIONARY_HPP

#include <cstddef>
#include <string>
#include <utility>
#include <unordered_map>
#include <memory>
#include <functional>

#include <boost/iterator/transform_iterator.hpp>
#include <boost/functional/hash.hpp>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Util/Array.hpp"
#include "CDPL/Util/Map.hpp"


namespace CDPL 
{

    namespace Chem 
    {

        /**
         * \brief A global dictionary for the lookup of meta-data associated with the atom
         *        types defined in namespace Chem::AtomType
         */ 
        class CDPL_CHEM_API AtomDictionary
        {

          public:
            class CDPL_CHEM_API Entry
            {

              public:
                typedef Util::Map<std::size_t, double> IsotopeMassMap;

                Entry();

                Entry(unsigned int atom_type, std::size_t iso, const std::string& sym,
                      const std::string& name, std::size_t most_abdt_iso, double avg_weight,
                      std::size_t iupac_grp, std::size_t period, bool metal, bool non_metal, const Util::STArray& val_states,
                      double vdw_rad, const double cov_radii[3], double ar_eneg, const IsotopeMassMap& iso_masses);

                unsigned int getType() const;

                std::size_t getIsotope() const;

                const std::string& getSymbol() const;

                const std::string& getName() const;

                std::size_t getMostAbundantIsotope() const;

                double getAverageWeight() const;

                std::size_t getIUPACGroup() const;

                std::size_t getPeriod() const;

                bool isMetal() const;

                bool isNonMetal() const;

                const Util::STArray& getValenceStates() const;

                double getVdWRadius() const;

                double getCovalentRadius(std::size_t order) const;

                double getAllredRochowElectronegativity() const;

                const IsotopeMassMap& getIsotopeMasses() const;
                
              private:
                unsigned int       atomType;
                std::size_t        isotope;
                std::string        symbol;
                std::string        name;
                std::size_t        mostAbundantIso;
                double             avgWeight;
                std::size_t        iupacGroup;
                std::size_t        period;
                bool               isMet;
                bool               isNonMet;
                Util::STArray      valenceStates;
                double             vdwRadius;
                double             covalentRadii[3];
                double             allredRochowEneg;
                IsotopeMassMap     isoMassMap;
            };

          private:
            typedef std::unordered_map<std::pair<unsigned int, std::size_t>, Entry, boost::hash<std::pair<unsigned int, std::size_t> > > EntryLookupTable;
            typedef std::unordered_map<std::string, unsigned int> SymbolToTypeLookupTable;

          public:
            typedef std::shared_ptr<AtomDictionary> SharedPointer;

            typedef boost::transform_iterator<std::function<const Entry&(const EntryLookupTable::value_type&)>, 
                                              EntryLookupTable::const_iterator> ConstEntryIterator;
            
            void addEntry(const Entry& entry);

            bool containsEntry(unsigned int type, std::size_t isotope) const;

            void removeEntry(unsigned int type, std::size_t isotope);
            
            const Entry& getEntry(unsigned int type, std::size_t isotope) const;

            void clear();

            std::size_t getNumEntries() const;
            
            ConstEntryIterator getEntriesBegin() const;

            ConstEntryIterator getEntriesEnd() const;

            ConstEntryIterator begin() const;

            ConstEntryIterator end() const;
            
            void loadDefaults();

            static void set(const SharedPointer& dict);

            static const SharedPointer& get();

            /**
             * \brief Returns the symbol that is associated with the specified atom type and isotope.
             *
             * The \a isotope argument has only an effect for hydrogen whose isotopes have different symbols
             * (D for \e Deuterium and T for \e Tritium).
             *
             * \param type The atom type.
             * \param isotope The mass number of the isotope, or \e 0 if not specified.
             * \return The atom type symbol, or an empty string if the symbol for the specified type and isotope is not
             *         available.
             */
            static const std::string& getSymbol(unsigned int type, std::size_t isotope = 0);

            /**
             * \brief Returns the name of the chemical element that is associated with the specified atom type
             *        and isotope.
             *
             * The \a isotope argument has only an effect for hydrogen whose isotopes are named differently
             * (\e Deuterium and \e Tritium).
             *
             * \param type The atom type specifying the chemical element.
             * \param isotope The mass number of the element's isotope, or \e 0 if not specified.
             * \return The name of the element isotope, or an empty string if \a type does not specify a
             *         supported chemical element.
             */
            static const std::string& getName(unsigned int type, std::size_t isotope = 0);

            /**
             * \brief Returns the numeric atom type that is associated with the specified atom type symbol.
             * \param symbol The atom type symbol.
             * \param strict If \c true, dictionary symbols strictly have to match the argument symbol. Otherwise, 
             *               the symbols will be converted to upper-case before their comparison.
             * \return The numeric atom type, or AtomType::UNKNOWN if \a symbol does not specify a
             *         supported atom type.
             */
            static unsigned int getType(const std::string& symbol, bool strict = false);

            /**
             * \brief Returns the mass number of the most abundant isotope of the chemical element specified by
             *        \a type.
             * \param type The atom type specifying the chemical element.
             * \return The mass number of the most abundant isotope of the element, or \e 0 if \a type
             *         does not specify a supported chemical element.
             */
            static std::size_t getMostAbundantIsotope(unsigned int type);

            /**
             * \brief Returns the IUPAC group of the chemical element specified by \a type.
             * \param type The atom type specifying the chemical element.
             * \return The IUPAC group of the element, or \e 0 if \a type
             *         does not specify a supported chemical element.
             */
            static std::size_t getIUPACGroup(unsigned int type);

            /**
             * \brief Returns the period number of the chemical element specified by \a type.
             * \param type The atom type specifying the chemical element.
             * \return The period of the element, or \e 0 if \a type
             *         does not specify a supported chemical element.
             */
            static std::size_t getPeriod(unsigned int type);

            /**
             * \brief Returns the number of valence electrons of the chemical element specified by \a type.
             * \param type The atom type specifying the chemical element.
             * \return The number of valence electrons, or \e 0 if \a type
             *         does not specify a supported chemical element.
             */
            static std::size_t getNumValenceElectrons(unsigned int type);

            /**
             * \brief Returns the standard atomic weight or the relative isotopic mass of an isotope of the
             *        chemical element specified by \a type.
             *
             * If the element isotope is left unspecified, i.e. the argument \a isotope is zero, then the standard
             * atomic weight of the chemical element will be returned.
             * If an isotope is specified and the exact relative isotopic mass of the specified isotope is not available, the
             * relative isotopic mass is approximated by the provided mass number of the isotope.
             *
             * \param type The atom type specifying the chemical element.
             * \param isotope The mass number of the element's isotope, or \e 0 if not specified.
             * \return The relative isotopic mass of the specified element isotope, or the standard atomic weight of
             *         the element if \a isotope is zero.
             */
            static double getAtomicWeight(unsigned int type, std::size_t isotope = 0);

            /**
             * \brief Returns the <em>van der Waals</em> radius of the chemical element specified by \a type.
             * \param type The atom type specifying the chemical element.
             * \return The <em>van der Waals</em> radius, or \e 0.0 if \a type
             *         does not specify a supported chemical element.
             */
            static double getVdWRadius(unsigned int type);

            /**
             * \brief Returns the covalent radius of the chemical element specified by \a type for the given bond order.
             * \param type The atom type specifying the chemical element.
             * \param order The bond order.
             * \return The covalent radius for the specified bond order, or \e 0.0 if \a type
             *         does not specify a supported chemical element, \a order is not valid or the radius is unknown.
             */
            static double getCovalentRadius(unsigned int type, std::size_t order = 1);

            /**
             * \brief Returns the <em>Allred-Rochow</em> electronegativity of the chemical element specified
             *        by \a type.
             * \param type The atom type specifying the chemical element.
             * \return The <em>Allred-Rochow</em> electronegativity, or \e 0.0 if the electronegativity of the
             *         specified element is not available.
             */
            static double getAllredRochowElectronegativity(unsigned int type);

            /**
             * \brief Returns an array with the valence states of the chemical element specified by \a type.
             * \param type The atom type specifying the chemical element.
             * \return An array with the valence states of the specified chemical element.
             */
            static const Util::STArray& getValenceStates(unsigned int type);
            
            /**
             * \brief Tells whether the specified atom type represents a chemical element.
             * \param type The atom type.
             * \return \c true if \a type specifies a chemical element, and \c false otherwise.
             */
            static bool isChemicalElement(unsigned int type);

            /**
             * \brief Tells whether the chemical element specified by \a type is a main group element.
             * \param type The atom type specifying the chemical element.
             * \return \c true if \a type specifies a main group element, and \c false otherwise.
             */
            static bool isMainGroupElement(unsigned int type);

            /**
             * \brief Tells whether the chemical element specified by \a type is a transition metal.
             * \param type The atom type specifying the chemical element.
             * \return \c true if \a type specifies a transition metal, and \c false otherwise.
             */
            static bool isTransitionMetal(unsigned int type);

            /**
             * \brief Tells whether the chemical element specified by \a type is a metal.
             * \param type The atom type specifying the chemical element.
             * \return \c true if \a type specifies a metal, and \c false otherwise.
             */
            static bool isMetal(unsigned int type);

            /**
             * \brief Tells whether the chemical element specified by \a type is a semi-metal.
             * \param type The atom type specifying the chemical element.
             * \return \c true if \a type specifies a semi-metal, and \c false otherwise.
             */
            static bool isSemiMetal(unsigned int type);

            /**
             * \brief Tells whether the chemical element specified by \a type is a non-metal.
             * \param type The atom type specifying the chemical element.
             * \return \c true if \a type specifies a non-metal, and \c false otherwise.
             */
            static bool isNonMetal(unsigned int type);

            /**
             * \brief Tells whether the chemical element specified by \a type is a halogen.
             * \param type The atom type specifying the chemical element.
             * \return \c true if \a type specifies a halogen, and \c false otherwise.
             */
            static bool isHalogen(unsigned int type);

            /**
             * \brief Tells whether the chemical element specified by \a type is a noble gas.
             * \param type The atom type specifying the chemical element.
             * \return \c true if \a type specifies a noble gas, and \c false otherwise.
             */
            static bool isNobleGas(unsigned int type);

          private:
            static SharedPointer     defaultDict;
            EntryLookupTable         entries;
            SymbolToTypeLookupTable  strictSymToTypeTable;
            SymbolToTypeLookupTable  nonstrictSymToTypeTable;
        };
    };
}

#endif // CDPL_CHEM_ATOMDICTIONARY_HPP
