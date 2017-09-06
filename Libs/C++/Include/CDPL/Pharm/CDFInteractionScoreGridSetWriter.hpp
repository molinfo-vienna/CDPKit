/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * CDFInteractionScoreGridSetWriter.hpp 
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
 * \brief Definition of the class CDPL::Pharm::CDFInteractionScoreGridSetWriter.
 */

#ifndef CDPL_PHARM_CDFINTERACTIONSCOREGRIDSETWRITER_HPP
#define CDPL_PHARM_CDFINTERACTIONSCOREGRIDSETWRITER_HPP

#include <memory>

#include "CDPL/Pharm/APIPrefix.hpp"
#include "CDPL/Base/DataWriter.hpp"


namespace CDPL 
{

	namespace Pharm
	{

		class CDFInteractionScoreGridSetDataWriter;
		class InteractionScoreGridSet;

		/**
		 * \addtogroup CDPL_PHARM_CDF_IO
		 * @{
		 */

		/**
		 * \brief A writer for interaction score grid set data in the native I/O format of the <em>CDPL</em>.
		 */
		class CDPL_PHARM_API CDFInteractionScoreGridSetWriter : public Base::DataWriter<InteractionScoreGridSet>
		{

		public:
			/**
			 * \brief Constructs a \c %CDFInteractionScoreGridSetWriter instance that will write data of interaction score grids to the output
			 *        stream \a os.
			 * \param os The output stream to write to.
			 */
			CDFInteractionScoreGridSetWriter(std::ostream& os);

			/**
			 * \brief Destructor.
			 */
			~CDFInteractionScoreGridSetWriter();

			/**
			 * \brief Writes data of the interaction score grid set \a grid_set to the output stream specified in the constructor.
			 * \param cntnr The interaction score grid set to write.
			 * \return A reference to itself.
			 */
			Base::DataWriter<InteractionScoreGridSet>& write(const InteractionScoreGridSet& grid_set);

			operator const void*() const;
			bool operator!() const;

		private:
			typedef std::auto_ptr<CDFInteractionScoreGridSetDataWriter> CDFDataWriterPtr;

			CDFInteractionScoreGridSetWriter(const CDFInteractionScoreGridSetWriter&);

			std::ostream&    output;
			bool             state;
			CDFDataWriterPtr writer;
		};

		/**
		 * @}
		 */
	}
}

#endif // CDPL_PHARM_CDFINTERACTIONSCOREGRIDSETWRITER_HPP
