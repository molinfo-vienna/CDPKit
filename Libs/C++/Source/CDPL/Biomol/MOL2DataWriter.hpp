/* 
 * MOL2DataWriter.hpp 
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


#ifndef CDPL_BIOMOL_MOL2DATAWRITER_HPP
#define CDPL_BIOMOL_MOL2DATAWRITER_HPP

#include "CDPL/Chem/MOL2DataWriter.hpp"


namespace CDPL
{

    namespace Biomol
    {

        class MOL2DataWriter : public Chem::MOL2DataWriter
        {

          public:
            MOL2DataWriter(const Base::DataIOBase& io_base):
                Chem::MOL2DataWriter(io_base) {}

            static void registerFactoryFunction();
        };
    } // namespace Biomol
} // namespace CDPL

#endif // CDPL_BIOMOL_MOL2DATAWRITER_HPP