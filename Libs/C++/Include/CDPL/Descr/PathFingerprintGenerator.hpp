/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PathFingerprintGenerator.hpp 
 *
 * Implementation of Daylight style Path Fingerprints
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
 * \brief Definition of the class CDPL::Descr::PathFingerprintGenerator.
 */

#ifndef CDPL_DESCR_PATHFINGERPRINTGENERATOR_HPP
#define CDPL_DESCR_PATHFINGERPRINTGENERATOR_HPP

#include <cstddef>
#include <cstdint>
#include <vector>

#include <boost/function.hpp>
#include <boost/random/linear_congruential.hpp>

#include "CDPL/Descr/APIPrefix.hpp"
#include "CDPL/Chem/AtomPropertyFlag.hpp"
#include "CDPL/Chem/BondPropertyFlag.hpp"
#include "CDPL/Util/BitSet.hpp"


namespace CDPL 
{

	namespace Chem
	{

		class MolecularGraph;
		class Atom;
		class Bond;
	}

	namespace Descr
	{

		/**
		 * \brief PathFingerprintGenerator.
		 * \see [\ref DTPFP]
		 */
		class CDPL_DESCR_API PathFingerprintGenerator
		{

		public:
			/**
			 * \brief Specifies the default set of atomic properties considered in the generation
			 *        of atom descriptors by PathFingerprintGenerator::DefAtomDescriptorFunction.
			 */
			static constexpr unsigned int DEF_ATOM_PROPERTY_FLAGS = 
				Chem::AtomPropertyFlag::TYPE | Chem::AtomPropertyFlag::ISOTOPE | Chem::AtomPropertyFlag::FORMAL_CHARGE |
				Chem::AtomPropertyFlag::AROMATICITY;

			/**
			 * \brief Specifies the default set of bond properties considered in the generation
			 *        of bond descriptors by PathFingerprintGenerator::DefBondDescriptorFunction.
			 */
			static constexpr unsigned int DEF_BOND_PROPERTY_FLAGS = 
				Chem::BondPropertyFlag::ORDER | Chem::BondPropertyFlag::AROMATICITY | Chem::BondPropertyFlag::TOPOLOGY;

			/**
			 * \brief The default functor for the generation of atom descriptors.
			 */
			class CDPL_DESCR_API DefAtomDescriptorFunctor
			{

			public:
				/**
				 * \brief Constructs the atom descriptor functor object for the specified set of atomic properties.
				 *
				 * The \a flags argument is an OR combination of the constants defined in namespace
				 * Chem::AtomPropertyFlag. Supported property flags are:
				 *  - Chem::AtomPropertyFlag::TYPE
				 *  - Chem::AtomPropertyFlag::ISOTOPE
				 *  - Chem::AtomPropertyFlag::AROMATICITY
				 *  - and Chem::AtomPropertyFlag::FORMAL_CHARGE
				 *
				 * \param flags Specifies the set of considered atomic properties.
				 */
				DefAtomDescriptorFunctor(unsigned int flags = DEF_ATOM_PROPERTY_FLAGS):
					flags(flags) {}
 
				/**
				 * \brief Generates a descriptor for the argument atom.
				 *
				 * The generated descriptor depends on the set of considered atomic properties that has been
				 * specified in the constructor.
				 *
				 * \param atom The atom for which to generate the descriptor.
				 * \return The generated atom descriptor.
				 */
				std::uint64_t operator()(const Chem::Atom& atom) const;

			private:
				unsigned int flags;
			};

			/**
			 * \brief The default functor for the generation of bond descriptors.
			 */
			class CDPL_DESCR_API DefBondDescriptorFunctor
			{

			public:
				/**
				 * \brief Constructs the bond descriptor functor object for the specified set of bond properties.
				 *
				 * The \a flags argument is an OR combination of the constants defined in namespace
				 * Chem::BondPropertyFlag. Supported property flags are:
				 *  - Chem::BondPropertyFlag::ORDER
				 *  - Chem::BondPropertyFlag::TOPOLOGY
				 *  - and Chem::BondPropertyFlag::AROMATICITY
				 *
				 * \param flags Specifies the set of considered bond properties.
				 */
				DefBondDescriptorFunctor(unsigned int flags = DEF_BOND_PROPERTY_FLAGS): 
					flags(flags) {}

				/**
				 * \brief Generates a descriptor for the argument bond.
				 *
				 * The generated descriptor depends on the set of considered bond properties that has been
				 * specified in the constructor.
				 *
				 * \param bond The bond for which to generate the descriptor.
				 * \return The generated bond descriptor.
				 */
				std::uint64_t operator()(const Chem::Bond& bond) const;

			private:
				unsigned int flags;
			};

			/**
			 * \brief Type of the generic functor class used to store user-defined functions or function objects
			 *        for the generation of atom descriptors.
			 *
			 * Functions or function objects for the generation of atom descriptors are required to take
			 * the atom (as a \c const reference to Chem::Atom) as argument and return the descriptor as
			 * an integer of type std::uint64_t. For details refer to the <em>Boost.Function</em> documentation [\ref BFUN]. 
			 */
			typedef boost::function1<std::uint64_t, const Chem::Atom&> AtomDescriptorFunction;

			/**
			 * \brief Type of the generic functor class used to store user-defined functions or function objects
			 *        for the generation of bond descriptors.
			 *
			 * Functions or function objects for the generation of bond descriptors are required to take
			 * the bond (as a \c const reference to Chem::Bond) as argument and return the descriptor as
			 * an integer of type std::uint64_t. For details refer to the <em>Boost.Function</em> documentation [\ref BFUN]. 
			 */
			typedef boost::function1<std::uint64_t, const Chem::Bond&> BondDescriptorFunction;

			/**
			 * \brief Constructs the \c %PathFingerprintGenerator instance.
			 */
			PathFingerprintGenerator();

			/**
			 * \brief Constructs the \c %PathFingerprintGenerator instance and generates the fingerprint of the
			 *        molecular graph \a molgraph.
			 * \param molgraph The molecular graph for which to generate the fingerprint.
			 * \param fp The generated fingerprint.
			 */
			PathFingerprintGenerator(const Chem::MolecularGraph& molgraph, Util::BitSet& fp);

			/**
			 * \brief Allows to specify a custom function for the generation of atom descriptors.
			 * \param func A PathFingerprintGenerator::AtomDescriptorFunction instance that wraps the target function.
			 * \note By default, atom descriptors are generated by PathFingerprintGenerator::DefAtomDescriptorFunctor.
			 */
			void setAtomDescriptorFunction(const AtomDescriptorFunction& func);

			/**
			 * \brief Allows to specify a custom function for the generation of bond descriptors.
			 * \param func A PathFingerprintGenerator::BondDescriptorFunction instance that wraps the target function.
			 * \note By default, bond descriptors are generated by PathFingerprintGenerator::DefBondDescriptorFunctor.
			 */
			void setBondDescriptorFunction(const BondDescriptorFunction& func);

			/**
			 * \brief Allows to specify the minimum length a path must have to contribute to the generated fingerprint.
			 *
			 * Any path whose length (in number of bonds) is lower than the specified minimum length will not be represented by a
			 * corresponding bit in the generated fingerprint.
			 *
			 * \param min_length The minimum path length in number of bonds.
			 * \note By default, the minimum path length is set to \e 0. 
			 */
			void setMinPathLength(std::size_t min_length);

			/**
			 * \brief Returns the minimum length a path must have to contribute to the generated fingerprint.
			 * \return The minimum path length in number of bonds.
			 * \see setMinPathLength()
			 */
			std::size_t getMinPathLength() const;

			/**
			 * \brief Allows to specify the maximum considered path length.
			 *
			 * Any path whose length (in number of bonds) is greater than the specified maximum length will not be represented by a
			 * corresponding bit in the generated fingerprint.
			 *
			 * \param max_length The maximum path length in number of bonds.
			 * \note By default, the maximum considered path length is \e 5. 
			 */
			void setMaxPathLength(std::size_t max_length);

			/**
			 * \brief Returns the maximum considered path length.
			 * \return The maximum path length in number of bonds.
			 * \see setMaxPathLength()
			 */
			std::size_t getMaxPathLength() const;

			/**
			 * \brief Allows to specify the desired fingerprint size.
			 * \param num_bits The desired fingerprint size in number of bits.
			 * \note By default, the generated fingerprints are \e 1024 bits wide.
			 */
			void setNumBits(std::size_t num_bits);

			/**
			 * \brief Returns the size of the generated fingerprints.
			 * \return The fingerprint size in number of bits.
			 */
			std::size_t getNumBits() const;

			/**
			 * \brief Generates the fingerprint of the molecular graph \a molgraph.
			 * \param molgraph The molecular graph for which to generate the fingerprint.
			 * \param fp The generated fingerprint.
			 */
			void generate(const Chem::MolecularGraph& molgraph, Util::BitSet& fp);

		private:
			void calcFingerprint(const Chem::MolecularGraph&, Util::BitSet&);

			void growPath(const Chem::Atom&, Util::BitSet&);

			std::size_t calcBitIndex();

			typedef std::vector<std::size_t> IndexList;
			typedef std::vector<std::uint64_t> UInt64Array;

			const Chem::MolecularGraph*  molGraph;
			std::size_t                  numBits;
			std::size_t                  minPathLength;
			std::size_t                  maxPathLength;
			AtomDescriptorFunction       atomDescriptorFunc;
			BondDescriptorFunction       bondDescriptorFunc;
			Util::BitSet                 visBondMask;
			UInt64Array                  atomDescriptors;
			UInt64Array                  bondDescriptors;
			IndexList                    atomPath;
			IndexList                    bondPath;
			UInt64Array                  fwdPathDescriptor;
			UInt64Array                  revPathDescriptor;
			boost::rand48                randGenerator;
		}; 
	}
}

#endif // CDPL_DESCR_PATHFINGERPRINTGENERATOR_HPP
