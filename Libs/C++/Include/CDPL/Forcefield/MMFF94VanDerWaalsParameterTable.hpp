/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MMFF94VanDerWaalsParameterTable.hpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2010 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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
 * \brief Definition of the class CDPL::Forcefield::MMFF94VanDerWaalsParameterTable.
 */

#ifndef CDPL_FORCEFIELD_MMFF94VANDERWAALSPARAMETERTABLE_HPP
#define CDPL_FORCEFIELD_MMFF94VANDERWAALSPARAMETERTABLE_HPP

#include <iosfwd>

#include <boost/shared_ptr.hpp>
#include <boost/unordered_map.hpp>
#include <boost/function.hpp>
#include <boost/iterator/transform_iterator.hpp>

#include "CDPL/Forcefield/APIPrefix.hpp"


namespace CDPL 
{

    namespace Forcefield 
    {

		/**
		 * \addtogroup CDPL_FORCEFIELD_PARAMETER_TABLES
		 * @{
		 */

		class CDPL_FORCEFIELD_API MMFF94VanDerWaalsParameterTable
		{

		  public:
			class Entry;

		  private:
			typedef boost::unordered_map<unsigned int, Entry> DataStorage;

		  public:
			typedef boost::shared_ptr<MMFF94VanDerWaalsParameterTable> SharedPointer;
	
			enum HDonorAcceptorType 
			{
			
			    NONE,
				DONOR,
				ACCEPTOR
			};	

			class CDPL_FORCEFIELD_API Entry
			{

			  public:
				Entry(unsigned int atom_type, double atom_pol, double eff_el_num, double scale_fac1, double scale_fac2, 
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
				double getScalingFactorA() const;
  
				/**
				 * \brief Returns the scaling factor G parameter.
				 * \return The scaling factor G
				 */
				double getScalingFactorG() const;
  
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
				double             scalingFact1;
				double             scaleingFact2;
				HDonorAcceptorType donAccType;
			};			

			typedef boost::transform_iterator<boost::function1<const Entry&, const DataStorage::value_type&>, 
											  DataStorage::const_iterator> ConstEntryIterator;

			typedef boost::transform_iterator<boost::function1<Entry&, DataStorage::value_type&>, 
											  DataStorage::iterator> EntryIterator;
	
			MMFF94VanDerWaalsParameterTable();

			void addEntry(unsigned int atom_type, double atom_pol, double eff_el_num, double scale_fac1, double scale_fac2, 
						  HDonorAcceptorType don_acc_type);

			const Entry& getEntry(unsigned int atom_type) const;

			void clear();

			bool removeEntry(unsigned int atom_type);

			EntryIterator removeEntry(const EntryIterator& it);

			ConstEntryIterator getEntriesBegin() const;

			ConstEntryIterator getEntriesEnd() const;
	
			EntryIterator getEntriesBegin();

			EntryIterator getEntriesEnd();

			void setPEXP(double value);

			void setAFACT(double value);

			void setBFACT(double value);

			void setDARAD(double value);

			void setDAEPS(double value);

			/**
			 * \brief Returns the PEXP value used in the calculation of van der Waals
			 *        interaction energies.
			 * \return The PEXP value.
			 */
			double getPEXP() const;
    
			/**
			 * \brief Returns the AFACT value used in the calculation of van der Waals
			 *        interaction energies.
			 * \return The AFACT value.
			 */
			double getAFACT() const;
  
			/**
			 * \brief Returns the BFACT value used in the calculation of van der Waals
			 *        interaction energies.
			 * \return The BFACT value.
			 */
			double getBFACT() const;
   
			/**
			 * \brief Returns the DARAD value used in the calculation of van der Waals
			 *        interaction energies.
			 * \return The DARAD value.
			 */
			double getDARAD() const;
   
			/**
			 * \brief Returns the DAEPS value used in the calculation of van der Waals
			 *        interaction energies.
			 * \return The DAEPS value.
			 */
			double getDAEPS() const;

			void load(std::istream& is);

			void loadDefaults();

			static void set(const SharedPointer& table);

			static const SharedPointer& get();

		  private:
			static SharedPointer defaultTable;
			DataStorage          entries;
			double               PEXP;
			double               AFACT;
			double               BFACT;
			double               DARAD;
			double               DAEPS;
		};
    
		/**
		 * @}
		 */
    }
}

#endif // CDPL_FORCEFIELD_MMFF94VANDERWAALSPARAMETERTABLE_HPP
