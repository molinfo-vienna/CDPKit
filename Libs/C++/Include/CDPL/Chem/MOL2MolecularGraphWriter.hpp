/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MOL2MolecularGraphWriter.hpp 
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
 * \brief Definition of the class CDPL::Chem::MOL2MolecularGraphWriter.
 */

#ifndef CDPL_CHEM_MOL2MOLECULARGRAPHWRITER_HPP
#define CDPL_CHEM_MOL2MOLECULARGRAPHWRITER_HPP

#include <memory>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Base/DataWriter.hpp"


namespace CDPL 
{

	namespace Chem
	{

		class MOL2DataWriter;
		class MolecularGraph;

		/**
		 * \addtogroup CDPL_CHEM_MOL2_IO
		 * @{
		 */

		class CDPL_CHEM_API MOL2MolecularGraphWriter : public Base::DataWriter<MolecularGraph>
		{

		public:
			/**
			 * \brief Constructs a \c %MOL2MolecularGraphWriter instance that will write data of molecular graphs to the output
			 *        stream \a os.
			 * \param os The output stream to write to.
			 */
			MOL2MolecularGraphWriter(std::ostream& os);

			/**
			 * \brief Destructor.
			 */
			~MOL2MolecularGraphWriter();

			/**
			 * \brief Writes data of the molecular graph \a molgraph to the output stream specified in the constructor.
			 * \param molgraph The molecular graph to write.
			 * \return A reference to itself.
			 */
			Base::DataWriter<MolecularGraph>& write(const MolecularGraph& molgraph);

			operator const void*() const;
			bool operator!() const;

		private:
			MOL2MolecularGraphWriter(const MOL2MolecularGraphWriter&);

			MOL2MolecularGraphWriter& operator=(const MOL2MolecularGraphWriter&);

			typedef std::auto_ptr<MOL2DataWriter> MOL2DataWriterPtr;

			std::ostream&     output;
			bool              state;
			MOL2DataWriterPtr writer;
		};

		/**
		 * @}
		 */
	}
}

#endif // CDPL_CHEM_MOL2MOLECULARGRAPHWRITER_HPP
