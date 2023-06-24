/* 
 * MMFF94ParameterData.hpp 
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


#ifndef CDPL_FORCEFIELD_MMFF94PARAMETERDATA_HPP
#define CDPL_FORCEFIELD_MMFF94PARAMETERDATA_HPP

#include <cstddef>


namespace CDPL
{

    namespace ForceField
    {

        namespace MMFF94ParameterData
        {

            extern const char        ANGLE_BENDING_PARAMETERS[];
            extern const std::size_t ANGLE_BENDING_PARAMETERS_LEN;

            extern const char        BOND_STRETCHING_PARAMETERS[];
            extern const std::size_t BOND_STRETCHING_PARAMETERS_LEN;

            extern const char        BOND_STRETCHING_RULE_PARAMETERS[];
            extern const std::size_t BOND_STRETCHING_RULE_PARAMETERS_LEN;

            extern const char        STRETCH_BEND_PARAMETERS[];
            extern const std::size_t STRETCH_BEND_PARAMETERS_LEN;

            extern const char        DEFAULT_STRETCH_BEND_PARAMETERS[];
            extern const std::size_t DEFAULT_STRETCH_BEND_PARAMETERS_LEN;

            extern const char        OUT_OF_PLANE_BENDING_PARAMETERS[];
            extern const std::size_t OUT_OF_PLANE_BENDING_PARAMETERS_LEN;

            extern const char        STATIC_OUT_OF_PLANE_BENDING_PARAMETERS[];
            extern const std::size_t STATIC_OUT_OF_PLANE_BENDING_PARAMETERS_LEN;

            extern const char        STATIC_EXT_OUT_OF_PLANE_BENDING_PARAMETERS[];
            extern const std::size_t STATIC_EXT_OUT_OF_PLANE_BENDING_PARAMETERS_LEN;

            extern const char        TORSION_PARAMETERS[];
            extern const std::size_t TORSION_PARAMETERS_LEN;

            extern const char        STATIC_TORSION_PARAMETERS[];
            extern const std::size_t STATIC_TORSION_PARAMETERS_LEN;

            extern const char        STATIC_REF_TORSION_PARAMETERS[];
            extern const std::size_t STATIC_REF_TORSION_PARAMETERS_LEN;

            extern const char        VAN_DER_WAALS_PARAMETERS[];
            extern const std::size_t VAN_DER_WAALS_PARAMETERS_LEN;

            extern const char        SYMBOLIC_ATOM_TYPE_PATTERNS[];
            extern const std::size_t SYMBOLIC_ATOM_TYPE_PATTERNS_LEN;

            extern const char        AROMATIC_ATOM_TYPE_DEFINITIONS[];
            extern const std::size_t AROMATIC_ATOM_TYPE_DEFINITIONS_LEN;

            extern const char        HYDROGEN_ATOM_TYPE_DEFINITIONS[];
            extern const std::size_t HYDROGEN_ATOM_TYPE_DEFINITIONS_LEN;

            extern const char        SYMBOLIC_TO_NUMERIC_ATOM_TYPE_MAPPING[];
            extern const std::size_t SYMBOLIC_TO_NUMERIC_ATOM_TYPE_MAPPING_LEN;

            extern const char        NUMERIC_TO_PARAMETER_ATOM_TYPE_MAPPING[];
            extern const std::size_t NUMERIC_TO_PARAMETER_ATOM_TYPE_MAPPING_LEN;

            extern const char        ATOM_TYPE_PROPERTIES[];
            extern const std::size_t ATOM_TYPE_PROPERTIES_LEN;

            extern const char        BOND_CHARGE_INCREMENT_PARAMETERS[];
            extern const std::size_t BOND_CHARGE_INCREMENT_PARAMETERS_LEN;

            extern const char        PARTIAL_BOND_CHARGE_INCREMENT_PARAMETERS[];
            extern const std::size_t PARTIAL_BOND_CHARGE_INCREMENT_PARAMETERS_LEN;

            extern const char        FORMAL_ATOM_CHARGE_DEFINITIONS[];
            extern const std::size_t FORMAL_ATOM_CHARGE_DEFINITIONS_LEN;
        } // namespace MMFF94ParameterData
    } // namespace ForceField
} // namespace CDPL

#endif // CDPL_FORCEFIELD_MMFF94PARAMETERDATA_HPP
