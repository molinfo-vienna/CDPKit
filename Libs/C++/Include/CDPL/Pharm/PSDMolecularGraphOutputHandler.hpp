/* 
 * PSDMolecularGraphOutputHandler.hpp 
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
 * \brief Definition of class CDPL::Pharm::PSDMolecularGraphOutputHandler.
 */

#ifndef CDPL_PHARM_PSDMOLECULARGRAPHOUTPUTHANDLER_HPP
#define CDPL_PHARM_PSDMOLECULARGRAPHOUTPUTHANDLER_HPP

#include "CDPL/Pharm/APIPrefix.hpp"
#include "CDPL/Base/DataOutputHandler.hpp"


namespace CDPL
{

    namespace Chem
    {

        class MolecularGraph;
    }

    namespace Pharm
    {

        /**
     * \brief A handler for the output of molecular graph dara in the PSD-format of the <em>CDPL</em>.
     */
        class CDPL_PHARM_API PSDMolecularGraphOutputHandler : public Base::DataOutputHandler<Chem::MolecularGraph>
        {

          public:
            const Base::DataFormat& getDataFormat() const;

            WriterType::SharedPointer createWriter(std::ostream& os) const;

            WriterType::SharedPointer createWriter(const std::string& file_name, std::ios_base::openmode mode) const;
        };
    } // namespace Pharm
} // namespace CDPL

#endif // CDPL_PHARM_PSDMOLECULARGRAPHOUTPUTHANDLER_HPP
