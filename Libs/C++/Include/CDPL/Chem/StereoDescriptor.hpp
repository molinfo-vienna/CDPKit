/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * StereoDescriptor.hpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2020 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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
 * \brief Definition of the type CDPL::Chem::StereoDescriptor.
 */

#ifndef CDPL_CHEM_STEREODESCRIPTOR_HPP
#define CDPL_CHEM_STEREODESCRIPTOR_HPP

#include <cstddef>

#include "CDPL/Chem/APIPrefix.hpp"


namespace CDPL 
{

	namespace Chem
	{

		class Atom;
		class Bond;

		/**
		 * \brief A data structure for the storage and retrieval of stereochemical information about atoms and bonds.
		 *
		 * The stereochemistry of atoms and bonds is definded by an ordered list of reference atoms 
		 * and an integer constant that describes the spatial configuration of the reference atoms.
		 * Requirements on the specification of the reference atom list and the way the associated
		 * steric configuration has to be interpreted both depend on the primary type of the stereocenter
		 * (if atom or bond) and, for atom centers, also on the number and geometric arrangement of the
		 * reference atoms. The following basic types of atom and bond stereocenters are currently supported:
		 * 
		 * - <em>Atoms with four neighbors in tetrahedral arrangement:</em><br><br>
		 * 	The four neighbor atoms serve as reference atoms. Their steric configuration is determined by looking
		 *  along the bond from the center atom (stereocenter) to the <em>4</em>th reference atom. If the
		 *  direction of travel from reference atom \e 1 over atom \e 2 to atom \e 3 is \e clockwise (see
		 *  <em>Fig. 1a</em>), the configuration flag is assigned the value AtomConfiguration::R, and 
		 *  AtomConfiguration::S, if the reference atoms <em>1</em>, \e 2 and \e 3 are arranged in
		 *  \e counterclockwise direction (<em>Fig. 1b</em>).
		 *
		 * <table align="center" cellpadding="30">
		 * <tr align="center" valign="middle">
		 * <td>\image html tetrahedral_stereo_r.png "Fig. 1a: R-Configuration"</td>
		 * <td>\image html tetrahedral_stereo_s.png "Fig. 1b: S-Configuration"</td>
		 * </tr>
		 * </table>
		 *
		 * - <em>Atoms with three neighbors in pyramidal arrangement:</em><br><br>
		 * 	The neighbor atoms correspond to the first three atoms in the reference atom list. The <em>4</em>th
		 *  reference atom denotes the central atom. The configuration is determined by looking along the line from the
		 *  center atom to a projected point (represented by a blue sphere in figure \e 2a and \e 2b) which is obtained by adding
		 *  the bond vectors from each neighbor atom to the central atom. Like before, if the direction of
		 *  travel from reference atom \e 1 over atom \e 2 to atom \e 3 is \e clockwise (see <em>Fig. 2a</em>), the
		 *  configuration flag is assigned the value AtomConfiguration::R, and AtomConfiguration::S, if the reference
		 *  atoms <em>1</em>, \e 2 and \e 3 are arranged in a \e counterclockwise fashion (<em>Fig. 2b</em>).
		 *
		 * <table align="center" cellpadding="30">
		 * <tr align="center" valign="middle">
		 * <td>\image html pyramidal_stereo_r.png "Fig. 2a: R-Configuration"</td>
		 * <td>\image html pyramidal_stereo_s.png "Fig. 2b: S-Configuration"</td>
		 * </tr>
		 * </table>
		 *
		 * - <em>Non-terminal double bonds:</em><br>
		 *  As shown in figure \e 3a and \e 3b, the four reference atoms form a path with three consecutive bonds where atoms \e 2
		 *  and \e 3 are part of the central double bond. Atom \e 1 is the connected atom of the first double bond ligand,
		 *  and atom \e 4 the connected atom of the second ligand. If reference atoms \e 1 and \e 4 lie on the same
		 *  side of the double bond (see <em>Fig. 3a</em>), the configuration flag is assigned the value BondConfiguration::CIS,
		 *  and BondConfiguration::TRANS, if they are on opposite sides f the bond (<em>Fig. 3b</em>).
		 *
		 * <table align="center" cellpadding="30">
		 * <tr align="center" valign="middle">
		 * <td>\image html bond_stereo_cis.png "Fig. 3a: Cis-Configuration"</td>
		 * <td>\image html bond_stereo_trans.png "Fig. 3b: Trans-Configuration"</td>
		 * </tr>
		 * </table>
		 */
		class CDPL_CHEM_API StereoDescriptor
		{

		public:
			/**
			 * \brief Constructs a \c %StereoDescriptor instance that specifies the configuration \a config
			 *        but stores no reference atoms.
			 * \param config A constant specifying the configuration of the central atoms.
			 */
			StereoDescriptor(unsigned int config);

			/**
			 * \brief Constructs a copy of the \c %StereoDescriptor instance \a descr.
			 * \param descr The \c %StereoDescriptor instance to copy.
			 */
			StereoDescriptor(const StereoDescriptor& descr);
	
			/**
			 * \brief Constructs a \c %StereoDescriptor instance that specifies a configuration of \a config
			 *        for three reference atoms.
			 * \param config A constant specifying the configuration of the reference atoms.
			 * \param atom1 The first reference atom.
			 * \param atom2 The second reference atom.
			 * \param atom3 The third reference atom.
			 */
			StereoDescriptor(unsigned int config, const Atom& atom1, 
							 const Atom& atom2, const Atom& atom3);

			/**
			 * \brief Constructs a \c %StereoDescriptor instance that specifies a configuration of \a config
			 *        for four reference atoms.
			 * \param config A flag specifying the configuration of the reference atoms.
			 * \param atom1 The first reference atom.
			 * \param atom2 The second reference atom.
			 * \param atom3 The third reference atom.
			 * \param atom4 The fourth reference atom.
			 */
			StereoDescriptor(unsigned int config, const Atom& atom1, const Atom& atom2, 
							 const Atom& atom3, const Atom& atom4);

			/**
			 * \brief Returns the number of specified reference atoms.
			 * \return The number of specified reference atoms.
			 */
			std::size_t getNumReferenceAtoms() const;
	
			/**
			 * \brief Returns the configuration of the reference atoms.
			 * \return A constant specifying the configuration of the reference atoms.
			 */
			unsigned int getConfiguration() const;
	
			/**
			 * \brief Sets the configuration of the reference atoms to \a config.
			 * \param config A constant specifying the configuration of the reference atoms.
			 */
			void setConfiguration(unsigned int config);

			/**
			 * \brief Returns an array of pointers to the stored reference atoms.
			 * \return An array of pointers to the stored reference atoms.
			 */
			const Atom* const* getReferenceAtoms() const;

			/**
			 * \brief Assignment operator.
			 * \param descr The \c %StereoDescriptor instance to copy.
			 * \return A reference to itself.
			 */
			StereoDescriptor& operator=(const StereoDescriptor& descr);

			/**
			 * \brief Tells wheter this \c %StereoDescriptor instance is valid for the specified center atom.
			 *
			 * The method checks if the number of reference atoms is at least 3, the reference atoms are distinct 
			 * and if every reference atom is connected to the argument atom.
			 *
			 * \param atom The stereogenic center atom.
			 * \return \c true if valid, \c false otherwise.
			 */
			bool isValid(const Atom& atom) const;

			/**
			 * \brief Tells wheter this \c %StereoDescriptor instance is valid for the specified center bond.
			 *
			 * The method checks if the number of reference atoms is 4, the reference atoms are distinct,
			 * the specified bond connects reference atoms 2 and 3 and if reference atoms 1 and 4 are connected
			 * to reference atom 2 and 3, respectively.
			 *
			 * \param bond The stereogenic center bond.
			 * \return \c true if valid, \c false otherwise.
			 */
			bool isValid(const Bond& bond) const;

			/**
			 * \brief Tells if an odd or even number of atom transpositions is required to achieve
			 *        the same ordering of reference and argument atoms.
			 * \param atom1 The first atom.
			 * \param atom2 The second atom.
			 * \param atom3 The third atom.
			 * \return \c 1 if an \e odd number of transpositions is required, \c 2 if an \e even number of transpositions is required and
			 *         \c 0 if the argument atoms do not match the stored reference atoms.
			 */
			unsigned int getPermutationParity(const Atom& atom1, const Atom& atom2, 
											  const Atom& atom3) const;

			/**
			 * \brief Tells if an odd or even number of atom transpositions is required to achieve
			 *        the same ordering of reference and argument atoms.
			 * \param atom1 The first atom.
			 * \param atom2 The second atom.
			 * \param atom3 The third atom.
			 * \param atom4 The fourth atom.
			 * \return \c 1 if an \e odd number of transpositions is required, \c 2 if an \e even number of transpositions is required and
			 *         \c 0 if the argument atoms do not match the stored reference atoms.
			 */
			unsigned int getPermutationParity(const Atom& atom1, const Atom& atom2, 
											  const Atom& atom3, const Atom& atom4) const;

		private:
			const Atom*  refAtoms[4];
			std::size_t  numRefAtoms;
			unsigned int config;
		};
	}
}

#endif // CDPL_CHEM_STEREODESCRIPTOR_HPP
