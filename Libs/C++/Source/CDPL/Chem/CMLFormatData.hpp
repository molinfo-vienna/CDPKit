/* 
 * CMLFormatData.hpp
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


#ifndef CDPL_CHEM_CMLFORMATDATA_HPP
#define CDPL_CHEM_CMLFORMATDATA_HPP

#include <string>


namespace CDPL
{

    namespace Chem
    {

        namespace CML
        {

            const std::string HEADER =
                "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                "<cml xmlns=\"http://www.xml-cml.org/schema\" xmlns:convention=\"http://www.xml-cml.org/convention/\" "
                "convention=\"convention:molecular\">\n";
            const std::string FOOTER = "</cml>\n";

            namespace Element
            {

                const std::string CML         = "cml";
                const std::string MOLECULE    = "molecule";
                const std::string FORMULA     = "formula";
                const std::string PROPERTY    = "property";
                const std::string LABEL       = "label";
                const std::string NAME        = "name";
                const std::string SPECTRUM    = "spectrum";
                const std::string ATOM_ARRAY  = "atomArray";
                const std::string ATOM        = "atom";
                const std::string ATOM_PARITY = "atomParity";
                const std::string BOND_ARRAY  = "bondArray";
                const std::string BOND        = "bond";
                const std::string BOND_STEREO = "bondStereo";
                const std::string SCALAR      = "scalar";
            } // namespace Element

            namespace Attribute
            {

                const std::string ID                = "id";
                const std::string FORMAL_CHARGE     = "formalCharge";
                const std::string SPIN_MULTIPLICITY = "spinMultiplicity";
                const std::string CHIRALITY         = "chirality";
                const std::string COUNT             = "count";
                const std::string CONCISE           = "concise";
                const std::string INLINE            = "inline";
                const std::string TITLE             = "title";
                const std::string DICT_REF          = "dictRef";
                const std::string UNIT              = "units";
                const std::string DATA_TYPE         = "dataType";
                const std::string ELEMENT_TYPE      = "elementType";
                const std::string X2                = "x2";
                const std::string Y2                = "y2";
                const std::string X3                = "x3";
                const std::string Y3                = "y3";
                const std::string Z3                = "z3";
                const std::string ISOTOPE           = "isotopeNumber";
                const std::string REF_ATOMS4        = "atomRefs4";
                const std::string REF_ATOMS2        = "atomRefs2";
                const std::string ORDER             = "order";
                
            } // namespace Attribute

        } // namespace CML
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_CMLFORMATDATA_HPP
