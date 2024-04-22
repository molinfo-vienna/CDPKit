/* 
 * MMFF94ParameterData.cpp 
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


#include "StaticInit.hpp"

#include "MMFF94ParameterData.hpp"


using namespace CDPL;
using namespace ForceField;

// clang-format off

constexpr char MMFF94ParameterData::ANGLE_BENDING_PARAMETERS[] =
    #include "MMFFANG.PAR.str"
    ;
constexpr std::size_t MMFF94ParameterData::ANGLE_BENDING_PARAMETERS_LEN =
    sizeof(MMFF94ParameterData::ANGLE_BENDING_PARAMETERS) - 1;

constexpr char MMFF94ParameterData::BOND_STRETCHING_PARAMETERS[] =
    #include "MMFFBOND.PAR.str"
    ;
constexpr std::size_t MMFF94ParameterData::BOND_STRETCHING_PARAMETERS_LEN =
    sizeof(MMFF94ParameterData::BOND_STRETCHING_PARAMETERS) - 1;

constexpr char MMFF94ParameterData::BOND_STRETCHING_RULE_PARAMETERS[] =
    #include "MMFFBNDK.PAR.str"
    ;
constexpr std::size_t MMFF94ParameterData::BOND_STRETCHING_RULE_PARAMETERS_LEN =
    sizeof(MMFF94ParameterData::BOND_STRETCHING_RULE_PARAMETERS) - 1;

constexpr char MMFF94ParameterData::STRETCH_BEND_PARAMETERS[] =
    #include "MMFFSTBN.PAR.str"
    ;
constexpr std::size_t MMFF94ParameterData::STRETCH_BEND_PARAMETERS_LEN =
    sizeof(MMFF94ParameterData::STRETCH_BEND_PARAMETERS) - 1;

constexpr char MMFF94ParameterData::DEFAULT_STRETCH_BEND_PARAMETERS[] =
    #include "MMFFDFSB.PAR.str"
    ;
constexpr std::size_t MMFF94ParameterData::DEFAULT_STRETCH_BEND_PARAMETERS_LEN =
    sizeof(MMFF94ParameterData::DEFAULT_STRETCH_BEND_PARAMETERS) - 1;

constexpr char MMFF94ParameterData::OUT_OF_PLANE_BENDING_PARAMETERS[] =
    #include "MMFFOOP.PAR.str"
    ;
constexpr std::size_t MMFF94ParameterData::OUT_OF_PLANE_BENDING_PARAMETERS_LEN =
    sizeof(MMFF94ParameterData::OUT_OF_PLANE_BENDING_PARAMETERS) - 1;

constexpr char MMFF94ParameterData::STATIC_OUT_OF_PLANE_BENDING_PARAMETERS[] =
    #include "MMFFSOOP.PAR.str"
    ;
constexpr std::size_t MMFF94ParameterData::STATIC_OUT_OF_PLANE_BENDING_PARAMETERS_LEN =
    sizeof(MMFF94ParameterData::STATIC_OUT_OF_PLANE_BENDING_PARAMETERS) - 1;

constexpr char MMFF94ParameterData::STATIC_EXT_OUT_OF_PLANE_BENDING_PARAMETERS[] =
    #include "MMFFSXOOP.PAR.str"
    ;
constexpr std::size_t MMFF94ParameterData::STATIC_EXT_OUT_OF_PLANE_BENDING_PARAMETERS_LEN =
    sizeof(MMFF94ParameterData::STATIC_EXT_OUT_OF_PLANE_BENDING_PARAMETERS) - 1;

constexpr char MMFF94ParameterData::TORSION_PARAMETERS[] =
    #include "MMFFTOR.PAR.str"
    ;
constexpr std::size_t MMFF94ParameterData::TORSION_PARAMETERS_LEN =
    sizeof(MMFF94ParameterData::TORSION_PARAMETERS) - 1;

constexpr char MMFF94ParameterData::STATIC_TORSION_PARAMETERS[] =
    #include "MMFFSTOR.PAR.str"
    ;
constexpr std::size_t MMFF94ParameterData::STATIC_TORSION_PARAMETERS_LEN =
    sizeof(MMFF94ParameterData::STATIC_TORSION_PARAMETERS) - 1;

constexpr char MMFF94ParameterData::STATIC_REF_TORSION_PARAMETERS[] =
    #include "MMFFSRTOR.PAR.str"
    ;
constexpr std::size_t MMFF94ParameterData::STATIC_REF_TORSION_PARAMETERS_LEN =
    sizeof(MMFF94ParameterData::STATIC_REF_TORSION_PARAMETERS) - 1;

constexpr char MMFF94ParameterData::VAN_DER_WAALS_PARAMETERS[] =
    #include "MMFFVDW.PAR.str"
    ;
constexpr std::size_t MMFF94ParameterData::VAN_DER_WAALS_PARAMETERS_LEN =
    sizeof(MMFF94ParameterData::VAN_DER_WAALS_PARAMETERS) - 1;

constexpr char MMFF94ParameterData::SYMBOLIC_ATOM_TYPE_PATTERNS[] =
    #include "MMFFSMTP.PAR.str"
    ;
constexpr std::size_t MMFF94ParameterData::SYMBOLIC_ATOM_TYPE_PATTERNS_LEN =
    sizeof(MMFF94ParameterData::SYMBOLIC_ATOM_TYPE_PATTERNS) - 1;

constexpr char MMFF94ParameterData::AROMATIC_ATOM_TYPE_DEFINITIONS[] =
    #include "MMFFAROM.PAR.str"
    ;
constexpr std::size_t MMFF94ParameterData::AROMATIC_ATOM_TYPE_DEFINITIONS_LEN =
    sizeof(MMFF94ParameterData::AROMATIC_ATOM_TYPE_DEFINITIONS) - 1;

constexpr char MMFF94ParameterData::HYDROGEN_ATOM_TYPE_DEFINITIONS[] =
    #include "MMFFHDEF.PAR.str"
    ;
constexpr std::size_t MMFF94ParameterData::HYDROGEN_ATOM_TYPE_DEFINITIONS_LEN =
    sizeof(MMFF94ParameterData::HYDROGEN_ATOM_TYPE_DEFINITIONS) - 1;

constexpr char MMFF94ParameterData::SYMBOLIC_TO_NUMERIC_ATOM_TYPE_MAPPING[] =
    #include "MMFFSYMB.PAR.str"
    ;
constexpr std::size_t MMFF94ParameterData::SYMBOLIC_TO_NUMERIC_ATOM_TYPE_MAPPING_LEN =
    sizeof(MMFF94ParameterData::SYMBOLIC_TO_NUMERIC_ATOM_TYPE_MAPPING) - 1;

constexpr char MMFF94ParameterData::NUMERIC_TO_PARAMETER_ATOM_TYPE_MAPPING[] =
    #include "MMFFDEF.PAR.str"
    ;
constexpr std::size_t MMFF94ParameterData::NUMERIC_TO_PARAMETER_ATOM_TYPE_MAPPING_LEN =
    sizeof(MMFF94ParameterData::NUMERIC_TO_PARAMETER_ATOM_TYPE_MAPPING) - 1;

constexpr char MMFF94ParameterData::ATOM_TYPE_PROPERTIES[] =
    #include "MMFFPROP.PAR.str"
    ;
constexpr std::size_t MMFF94ParameterData::ATOM_TYPE_PROPERTIES_LEN =
    sizeof(MMFF94ParameterData::ATOM_TYPE_PROPERTIES) - 1;

constexpr char MMFF94ParameterData::BOND_CHARGE_INCREMENT_PARAMETERS[] =
    #include "MMFFCHG.PAR.str"
    ;
constexpr std::size_t MMFF94ParameterData::BOND_CHARGE_INCREMENT_PARAMETERS_LEN =
    sizeof(MMFF94ParameterData::BOND_CHARGE_INCREMENT_PARAMETERS) - 1;

constexpr char MMFF94ParameterData::PARTIAL_BOND_CHARGE_INCREMENT_PARAMETERS[] =
    #include "MMFFPBCI.PAR.str"
    ;
constexpr std::size_t MMFF94ParameterData::PARTIAL_BOND_CHARGE_INCREMENT_PARAMETERS_LEN =
    sizeof(MMFF94ParameterData::PARTIAL_BOND_CHARGE_INCREMENT_PARAMETERS) - 1;

constexpr char MMFF94ParameterData::FORMAL_ATOM_CHARGE_DEFINITIONS[] =
    #include "MMFFFCHG.PAR.str"
    ;
constexpr std::size_t MMFF94ParameterData::FORMAL_ATOM_CHARGE_DEFINITIONS_LEN =
    sizeof(MMFF94ParameterData::FORMAL_ATOM_CHARGE_DEFINITIONS) - 1;

// clang-format on
