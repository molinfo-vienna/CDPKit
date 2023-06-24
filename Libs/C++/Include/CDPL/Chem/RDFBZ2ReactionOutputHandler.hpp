/* 
 * RDFBZ2ReactionOutputHandler.hpp 
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
 * \brief Definition of the class CDPL::Chem::RDFBZ2ReactionOutputHandler.
 */

#ifndef CDPL_CHEM_RDFBZ2REACTIONOUTPUTHANDLER_HPP
#define CDPL_CHEM_RDFBZ2REACTIONOUTPUTHANDLER_HPP

#include "CDPL/Chem/DataFormat.hpp"
#include "CDPL/Chem/RDFBZ2ReactionWriter.hpp"
#include "CDPL/Util/DefaultDataOutputHandler.hpp"


namespace CDPL
{

    namespace Chem
    {

        /**
         * \brief A handler for the output of bzip2-compressed reaction data in the <em>MDL RD-File</em> [\ref CTFILE] format.
         */
        typedef Util::DefaultDataOutputHandler<RDFBZ2ReactionWriter, DataFormat::RDF_BZ2> RDFBZ2ReactionOutputHandler;
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_RDFBZ2REACTIONOUTPUTHANDLER_HPP
