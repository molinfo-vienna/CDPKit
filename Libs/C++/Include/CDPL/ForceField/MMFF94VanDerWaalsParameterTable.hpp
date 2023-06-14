/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

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
 * \brief Definition of the class CDPL::ForceField::MMFF94VanDerWaalsParameterTable.
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

		class CDPL_FORCEFIELD_API MMFF94VanDerWaalsParameterTable
		{

		  public:
			class Entry;

		  private:
			typedef std::unordered_map<unsigned int, Entry> DataStorage;

		  public:
			typedef std::shared_ptr<MMFF94VanDerWaalsParameterTable> SharedPointer;
			typedef MMFF94VanDerWaalsInteraction::HDonorAcceptorType HDonorAcceptorType;
	
			class CDPL_FORCEFIELD_API Entry
			{

			  public:
				Entry();

				Entry(unsigned int atom_type, double atom_pol, double eff_el_num, double fact_a, double fact_g, 
					  HDonorAcceptorType don_acc_type);
 
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
				 * Returns the H-donor/-acceptor property associated with the numeric MMFF94 atom type.
				 * \return The H-donor/-acceptor property specifier.
				 */
				HDonorAcceptorType getHDonorAcceptorType() const;

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

			typedef boost::transform_iterator<std::function<const Entry&(const DataStorage::value_type&)>, 
											  DataStorage::const_iterator> ConstEntryIterator;

			typedef boost::transform_iterator<std::function<Entry&(DataStorage::value_type&)>, 
											  DataStorage::iterator> EntryIterator;
	
			MMFF94VanDerWaalsParameterTable();

			void addEntry(unsigned int atom_type, double atom_pol, double eff_el_num, double fact_a, double fact_g, 
						  HDonorAcceptorType don_acc_type);

			const Entry& getEntry(unsigned int atom_type) const;

			std::size_t getNumEntries() const;

			void clear();

			bool removeEntry(unsigned int atom_type);

			EntryIterator removeEntry(const EntryIterator& it);

			ConstEntryIterator getEntriesBegin() const;

			ConstEntryIterator getEntriesEnd() const;
	
			EntryIterator getEntriesBegin();

			EntryIterator getEntriesEnd();

			void setExponent(double value);

			void setBeta(double value);

			void setFactorB(double value);

			void setFactorDARAD(double value);

			void setFactorDAEPS(double value);

			/**
			 * \brief Returns the exponent used in the calculation of van der Waals
			 *        interaction energies.
			 * \return The exponent.
			 */
			double getExponent() const;
    
			/**
			 * \brief Returns the value of the \e B factor used in the calculation of van der Waals
			 *        interaction energies.
			 * \return The value of the \e B factor.
			 */
			double getFactorB() const;
  
			/**
			 * \brief Returns the value of \e beta used in the calculation of van der Waals
			 *        interaction energies.
			 * \return The value of \e beta.
			 */
			double getBeta() const;
   
			/**
			 * \brief Returns the value of the \e DARAD factor used in the calculation of van der Waals
			 *        interaction energies.
			 * \return The value of the \e DARAD factor.
			 */
			double getFactorDARAD() const;
   
			/**
			 * \brief Returns the value of the \e DAEPS factor used in the calculation of van der Waals
			 *        interaction energies.
			 * \return The value of the \e DAEPS factor.
			 */
			double getFactorDAEPS() const;

			void load(std::istream& is);

			void loadDefaults();

			static void set(const SharedPointer& table);

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
    }
}

#endif // CDPL_FORCEFIELD_MMFF94VANDERWAALSPARAMETERTABLE_HPP
