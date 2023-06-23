/* 
 * MOL2FormatData.hpp 
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


#ifndef CDPL_CHEM_MOL2FORMATDATA_HPP
#define CDPL_CHEM_MOL2FORMATDATA_HPP

#include <string>

#include "CDPL/Chem/SybylAtomType.hpp"
#include "CDPL/Chem/SybylBondType.hpp"
#include "CDPL/Chem/MOL2ChargeType.hpp"
#include "CDPL/Chem/MOL2MoleculeType.hpp"


namespace CDPL
{

	namespace Chem
	{
		
		namespace MOL2
		{
		
			const char END_OF_LINE               = '\n';
			const char COMMENT_PREFIX            = '#';
			const char RTI_PREFIX                = '@';
			const char LINE_CONT_MARKER          = '\\';

			const std::string EMPTY_STRING_FIELD = "****";

			const std::string MOLECULE_RTI       = "@<TRIPOS>MOLECULE";
			const std::string COMMENT_RTI        = "@<TRIPOS>COMMENT";
			const std::string ATOM_RTI           = "@<TRIPOS>ATOM";
			const std::string BOND_RTI           = "@<TRIPOS>BOND";
			const std::string SUBSTRUCTURE_RTI   = "@<TRIPOS>SUBSTRUCTURE";

			struct TypeToString
			{

				unsigned int type;
				std::string  string;
			};

			const TypeToString ATOM_TYPE_STRINGS[] = {
			
				{ SybylAtomType::C_3    , "C.3"   },
				{ SybylAtomType::C_2    , "C.2"   },
				{ SybylAtomType::C_1    , "C.1"   },
				{ SybylAtomType::C_ar   , "C.ar"  },
				{ SybylAtomType::C_cat  , "C.cat" },
 				{ SybylAtomType::N_3    , "N.3"   },
				{ SybylAtomType::N_2    , "N.2"   },
				{ SybylAtomType::N_1    , "N.1"   },
				{ SybylAtomType::N_ar   , "N.ar"  },
				{ SybylAtomType::N_am   , "N.am"  },
				{ SybylAtomType::N_pl3  , "N.pl3" },
				{ SybylAtomType::N_4    , "N.4"   },
				{ SybylAtomType::O_3    , "O.3"   },
				{ SybylAtomType::O_2    , "O.2"   },
				{ SybylAtomType::O_co2  , "O.co2" },
				{ SybylAtomType::O_spc  , "O.spc" },
				{ SybylAtomType::O_t3p  , "O.tp3" },
				{ SybylAtomType::S_3    , "S.3"   },
				{ SybylAtomType::S_2    , "S.2"   },
				{ SybylAtomType::S_O    , "S.O"   },
				{ SybylAtomType::S_O2   , "S.O2"  },
				{ SybylAtomType::S_O2   , "S.1"   },
				{ SybylAtomType::H      , "H"     },
				{ SybylAtomType::H_spc  , "H.spc" },
				{ SybylAtomType::H_t3p  , "H.tp3" },
				{ SybylAtomType::P_3    , "P.3"   },
				{ SybylAtomType::F      , "F"     },
				{ SybylAtomType::LP     , "LP"    },
				{ SybylAtomType::Du     , "Du"    },
				{ SybylAtomType::Du_C   , "Du.C"  },
				{ SybylAtomType::Any    , "Any"   },
				{ SybylAtomType::Hal    , "Hal"   },
				{ SybylAtomType::Het    , "Het"   },
				{ SybylAtomType::Hev    , "Hev"   },
				{ SybylAtomType::Li     , "Li"    },
				{ SybylAtomType::Na     , "Na"    },
				{ SybylAtomType::Mg     , "Mg"    },
				{ SybylAtomType::Al     , "Al"    },
				{ SybylAtomType::Si     , "Si"    },
				{ SybylAtomType::K      , "K"     },
				{ SybylAtomType::Ca     , "Ca"    },
				{ SybylAtomType::Cr_th  , "Cr.th" },
				{ SybylAtomType::Cr_oh  , "Cr.oh" },
				{ SybylAtomType::Mn     , "Mn"    },
				{ SybylAtomType::Fe     , "Fe"    },
				{ SybylAtomType::Co_oh  , "Co.oh" },
				{ SybylAtomType::Cu     , "Cu"    },
				{ SybylAtomType::Zn     , "Zn"    },
				{ SybylAtomType::Se     , "Se"    },
				{ SybylAtomType::Mo     , "Mo"    },
				{ SybylAtomType::Sn     , "Sn"    },
				{ SybylAtomType::Cl     , "Cl"    },
				{ SybylAtomType::Br     , "Br"    },
				{ SybylAtomType::I      , "I"     },
				{ SybylAtomType::B      , "B"     },
				{ SybylAtomType::Pt     , "Pt"    }
			};

			const TypeToString BOND_TYPE_STRINGS[] = {

				{ SybylBondType::SINGLE       , "1"  },
				{ SybylBondType::DOUBLE       , "2"  },
				{ SybylBondType::TRIPLE       , "3"  },
				{ SybylBondType::AROMATIC     , "ar" },
				{ SybylBondType::AMIDE        , "am" },
				{ SybylBondType::DUMMY        , "du" },
				{ SybylBondType::NOT_CONNECTED, "nc" },
				{ SybylBondType::UNKNOWN      , "un" }
			};

			const TypeToString MOLECULE_TYPE_STRINGS[] = {

				{ MOL2MoleculeType::SMALL       , "SMALL"        },
				{ MOL2MoleculeType::BIOPOLYMER  , "BIOPOLYMER"   },
				{ MOL2MoleculeType::PROTEIN     , "PROTEIN"      },
				{ MOL2MoleculeType::NUCLEIC_ACID, "NUCLEIC_ACID" },
				{ MOL2MoleculeType::SACCHARIDE  , "SACCHARIDE"   }
			};

			const TypeToString CHARGE_TYPE_STRINGS[] = {

				{ MOL2ChargeType::NO_CHARGES, "NO_CHARGES"       },
				{ MOL2ChargeType::DEL_RE    , "DEL_RE"           },
				{ MOL2ChargeType::GASTEIGER , "GASTEIGER"        },
				{ MOL2ChargeType::GAST_HUCK , "GAST_HUCK"        },
				{ MOL2ChargeType::HUCKEL    , "HUCKEL"           },
				{ MOL2ChargeType::PULLMAN   , "PULLMAN"          }, 
				{ MOL2ChargeType::GAUSS80   , "GAUSS80_CHARGES"  }, 
				{ MOL2ChargeType::AMPAC     , "AMPAC_CHARGES"    },
				{ MOL2ChargeType::MULLIKEN  , "MULLIKEN_CHARGES" }, 
				{ MOL2ChargeType::DICT      , "DICT_CHARGES"     }, 
				{ MOL2ChargeType::MMFF94    , "MMFF94_CHARGES"   },
				{ MOL2ChargeType::USER      , "USER_CHARGES"     }
			};
		}
	}
}

#endif // CDPL_CHEM_MOL2FORMATDATA_HPP
