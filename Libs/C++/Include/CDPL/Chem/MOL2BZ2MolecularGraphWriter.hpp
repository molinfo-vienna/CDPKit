/* 
 * MOL2BZ2MolecularGraphWriter.hpp 
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
 * \brief Declaration of type CDPL::Chem::MOL2BZ2MolecularGraphWriter.
 */

#ifndef CDPL_CHEM_MOL2BZ2MOLECULARGRAPHWRITER_HPP
#define CDPL_CHEM_MOL2BZ2MOLECULARGRAPHWRITER_HPP

#include "CDPL/Chem/MOL2MolecularGraphWriter.hpp"
#include "CDPL/Util/CompressedDataWriter.hpp"


namespace CDPL
{

    namespace Chem
    {

        typedef Util::CompressedDataWriter<MOL2MolecularGraphWriter, Util::BZip2OStream> MOL2BZ2MolecularGraphWriter;
    }
} // namespace CDPL

#endif // CDPL_CHEM_MOL2BZ2MOLECULARGRAPHWRITER_HPP
