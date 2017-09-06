/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * CDFInteractionScoreGridWriter.hpp 
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
 * \brief Definition of the class CDPL::Pharm::CDFInteractionScoreGridWriter.
 */

#ifndef CDPL_PHARM_CDFINTERACTIONSCOREGRIDWRITER_HPP
#define CDPL_PHARM_CDFINTERACTIONSCOREGRIDWRITER_HPP

#include <memory>

#include "CDPL/Pharm/APIPrefix.hpp"
#include "CDPL/Base/DataWriter.hpp"


namespace CDPL 
{

	namespace Pharm
	{

		class CDFInteractionScoreGridDataWriter;
		class InteractionScoreGrid;

		/**
		 * \addtogroup CDPL_PHARM_CDF_IO
		 * @{
		 */

		/**
		 * \brief A writer for interaction score grid data in the native I/O format of the <em>CDPL</em>.
		 */
		class CDPL_PHARM_API CDFInteractionScoreGridWriter : public Base::DataWriter<InteractionScoreGrid>
		{

		public:
			/**
			 * \brief Constructs a \c %CDFInteractionScoreGridWriter instance that will write data of interaction score grids to the output
			 *        stream \a os.
			 * \param os The output stream to write to.
			 */
			CDFInteractionScoreGridWriter(std::ostream& os);

			/**
			 * \brief Destructor.
			 */
			~CDFInteractionScoreGridWriter();

			/**
			 * \brief Writes data of the interaction score grid \a grid to the output stream specified in the constructor.
			 * \param cntnr The interaction score grid to write.
			 * \return A reference to itself.
			 */
			Base::DataWriter<InteractionScoreGrid>& write(const InteractionScoreGrid& grid);

			operator const void*() const;
			bool operator!() const;

		private:
			typedef std::auto_ptr<CDFInteractionScoreGridDataWriter> CDFDataWriterPtr;

			CDFInteractionScoreGridWriter(const CDFInteractionScoreGridWriter&);

			std::ostream&    output;
			bool             state;
			CDFDataWriterPtr writer;
		};

		/**
		 * @}
		 */
	}
}

#endif // CDPL_PHARM_CDFINTERACTIONSCOREGRIDWRITER_HPP
