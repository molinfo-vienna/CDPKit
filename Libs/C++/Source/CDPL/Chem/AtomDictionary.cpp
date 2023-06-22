/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomDictionary.cpp 
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

#include <functional>

#include <boost/algorithm/string.hpp>

#include "CDPL/Chem/AtomDictionary.hpp"
#include "CDPL/Chem/AtomType.hpp"


using namespace CDPL;


namespace 
{

    struct IsotopeData
    {

		std::size_t isotope;
		double      weight;
    };

    struct AtomDictData
    {

		unsigned int       type;
		std::size_t        isotope;
		std::string        symbol;
		std::string        name;
		std::size_t        mostAbundantIso;
		double             averageWeight;
		std::size_t        iupacGroup;
		std::size_t        period;
		bool               isMetal;
		bool               isNonMetal;
		const int          valenceStates[8];
		double             vdwRadius;
		const double       covalentRadii[3];
		double             allredRochowEneg;
		const IsotopeData* isotopeData;
    };

    const IsotopeData H_IsoData[] = { 
    { 1, 1.0078503 }, { 2, 2.01410178 }, { 0, 0.0 } 
    };

    const IsotopeData He_IsoData[] = { 
    { 3, 3.0160293 }, { 4, 4.00260323 }, { 0, 0.0 } 
    };

    const IsotopeData Li_IsoData[] = { 
    { 6, 6.015122 }, { 7, 7.016003 }, { 0, 0.0 } 
    };

    const IsotopeData Be_IsoData[] = { 
    { 9, 9.0121822 }, { 0, 0.0 } 
    };

    const IsotopeData B_IsoData[] = { 
    { 10, 10.0129372 }, { 11, 11.0093056 }, { 0, 0.0 } 
    };

    const IsotopeData C_IsoData[] = { 
    { 12, 12.0 }, { 13, 13.00335483 }, { 0, 0.0 } 
    };

    const IsotopeData N_IsoData[] = { 
    { 14, 14.003074 }, { 15, 15.00010896 }, { 0, 0.0 } 
    };

    const IsotopeData O_IsoData[] = { 
    { 16, 15.99491462 }, { 17, 16.9991314 }, { 18, 17.99916 }, { 0, 0.0 } 
    };

    const IsotopeData F_IsoData[] = { 
    { 19, 18.9984032 }, { 0, 0.0 } 
    };

    const IsotopeData Ne_IsoData[] = { 
    { 20, 19.992434 }, { 21, 20.993841}, { 22, 21.991382 }, { 0, 0.0 } 
    };

    const IsotopeData Na_IsoData[] = { 
    { 23, 22.989767 }, { 0, 0.0 } 
    };

    const IsotopeData Mg_IsoData[] = { 
    { 24, 23.985042 }, { 25, 24.985837 }, { 26, 25.982594 }, { 0, 0.0 } 
    };

    const IsotopeData Al_IsoData[] = { 
    { 27, 26.981538 }, { 0, 0.0 } 
    };

    const IsotopeData Si_IsoData[] = { 
    { 28, 27.976927 }, { 29, 28.976494 }, { 30, 29.97377 }, { 0, 0.0 } 
    };

    const IsotopeData P_IsoData[] = { 
    { 31, 30.973762 }, { 0, 0.0 } 
    };

    const IsotopeData S_IsoData[] = { 
    { 32, 31.9720705 }, { 33, 32.9714583 }, { 34, 33.9678685 }, { 36, 35.9670808 }, { 0, 0.0 } 
    };

    const IsotopeData Cl_IsoData[] = { 
    { 35, 34.96885272 }, { 37, 36.9659026 }, { 0, 0.0 } 
    };

    const IsotopeData Ar_IsoData[] = { 
    { 36, 35.967546 }, { 38, 37.962732 }, { 40, 39.962384 }, { 0, 0.0 } 
    };

    const IsotopeData K_IsoData[] = { 
    { 39, 38.963708 }, { 40, 39.9640022 }, { 41, 40.961827 }, { 0, 0.0 } 
    };

    const IsotopeData Ca_IsoData[] = { 
    { 40, 39.962592 }, { 42, 41.958618 }, { 43, 42.958767 }, { 44, 43.955481 }, 
    { 46, 15.953687 }, { 48, 47.952535 }, { 0, 0.0 } 
    };

    const IsotopeData Sc_IsoData[] = { 
    { 45, 44.95591 }, { 0, 0.0 } 
    };

    const IsotopeData Ti_IsoData[] = { 
    { 46, 45.95263 }, { 47, 46.951764 }, { 48, 47.947947 }, { 49, 48.947871 }, 
    { 50, 49.944792 }, { 0, 0.0 } 
    };

    const IsotopeData V_IsoData[] = { 
    { 50, 49.947162 }, { 51, 50.943962 }, { 0, 0.0 } 
    };

    const IsotopeData Cr_IsoData[] = { 
    { 50, 49.946047 }, { 52, 51.940511 }, { 53, 52.940652 }, { 54, 53.938884 }, { 0, 0.0 } 
    };

    const IsotopeData Mn_IsoData[] = { 
    { 55, 54.938048 }, { 0, 0.0 } 
    };

    const IsotopeData Fe_IsoData[] = { 
    { 54, 53.939613 }, { 56, 55.93494 }, { 57, 56.935396 }, { 58, 57.933278 }, { 0, 0.0 } 
    };

    const IsotopeData Co_IsoData[] = { 
    { 59, 58.933198 }, { 0, 0.0 } 
    };

    const IsotopeData Ni_IsoData[] = { 
    { 58, 57.935346 }, { 60, 59.930788 }, { 61, 60.931053 }, { 62, 61.928346 }, 
    { 64, 63.927968 }, { 0, 0.0 } 
    };

    const IsotopeData Cu_IsoData[] = { 
    { 63, 62.929599 }, { 65, 64.927792 }, { 0, 0.0 } 
    };

    const IsotopeData Zn_IsoData[] = { 
    { 64, 63.929144 }, { 66, 65.926035 }, { 67, 66.927129 }, { 68, 67.924846 }, 
    { 70, 69.925324 }, { 0, 0.0 } 
    };

    const IsotopeData Ga_IsoData[] = { 
    { 69, 68.92558 }, { 71, 70.924703 }, { 0, 0.0 } 
    };

    const IsotopeData Ge_IsoData[] = { 
    { 70, 69.924249 }, { 72, 71.922079 }, { 73, 72.923462 }, { 74, 73.921177 }, 
    { 76, 75.921401 }, { 0, 0.0 } 
    };

    const IsotopeData As_IsoData[] = { 
    { 75, 74.921594 }, { 0, 0.0 } 
    };

    const IsotopeData Se_IsoData[] = { 
    { 74, 73.922474 }, { 76, 75.919212 }, { 77, 76.919912 }, { 78, 77.917307 }, 
    { 80, 79.916519 }, { 82, 81.916697 }, { 0, 0.0 } 
    };

    const IsotopeData Br_IsoData[] = { 
    { 79, 78.918336 }, { 81, 80.91629 }, { 0, 0.0 } 
    };

    const IsotopeData Kr_IsoData[] = { 
    { 78, 77.9204 }, { 80, 79.91638 }, { 82, 81.91348 }, { 83, 82.914137 }, 
    { 84, 83.911509 }, { 86, 85.910615 }, { 0, 0.0 } 
    };

    const IsotopeData Rb_IsoData[] = { 
    { 85, 84.911794 }, { 87, 86.909186 }, { 0, 0.0 } 
    };

    const IsotopeData Sr_IsoData[] = { 
    { 84, 83.913429 }, { 86, 85.909266 }, { 87, 86.908883 }, { 88, 87.905618 }, { 0, 0.0 } 
    };

    const IsotopeData Y_IsoData[] = { 
    { 89, 88.905848 }, { 0, 0.0 } 
    };

    const IsotopeData Zr_IsoData[] = { 
    { 90, 89.904702 }, { 91, 90.905643 }, { 92, 91.905038 }, { 94, 93.906314 }, 
    { 96, 95.908275 }, { 0, 0.0 } 
    };

    const IsotopeData Nb_IsoData[] = { 
    { 93, 92.906376 }, { 0, 0.0 } 
    };

    const IsotopeData Mo_IsoData[] = { 
    { 92, 91.906807 }, { 94, 93.905085 }, { 95, 94.905841 }, { 96, 95.904678 }, 
    { 97, 96.90602 }, { 98, 97.905407 }, { 100, 99.90748 }, { 0, 0.0 } 
    };

    const IsotopeData Ru_IsoData[] = { 
    { 96, 95.9076 }, { 98, 97.90529 }, { 99, 98.905939 }, { 100, 99.90422 }, 
    { 101, 100.905582 }, { 102, 101.904349 }, { 104, 103.905429 }, { 0, 0.0 } 
    };

    const IsotopeData Rh_IsoData[] = { 
    { 103, 102.905503 }, { 0, 0.0 } 
    };

    const IsotopeData Pd_IsoData[] = { 
    { 102, 101.90562 }, { 104, 103.90403 }, { 105, 104.90508 }, { 106, 105.90348 }, 
    { 108, 107.903894 }, { 110, 109.90516 }, { 0, 0.0 } 
    };

    const IsotopeData Ag_IsoData[] = { 
    { 107, 106.90509 }, { 109, 108.904755 }, { 0, 0.0 } 
    };

    const IsotopeData Cd_IsoData[] = { 
    { 106, 105.90546 }, { 108, 107.90418 }, { 110, 109.903005 }, { 111, 110.904182 }, 
    { 112, 111.902758 }, { 113, 112.904402 }, { 114, 113.903358 }, { 116, 115.904756 }, { 0, 0.0 } 
    };

    const IsotopeData In_IsoData[] = { 
    { 113, 112.90406 }, { 115, 114.903876 }, { 0, 0.0 } 
    };

    const IsotopeData Sn_IsoData[] = { 
    { 112, 111.90482 }, { 114, 113.902761 }, { 115, 114.903345 }, { 116, 115.901743 }, 
    { 117, 116.902953 }, { 118, 117.901606 }, { 119, 118.903309 }, { 120, 119.902197 }, 
    { 122, 121.90344 }, { 124, 123.905274 }, { 0, 0.0 } 
    };

    const IsotopeData Sb_IsoData[] = { 
    { 121, 120.90382 }, { 123, 122.904215 }, { 0, 0.0 } 
    };

    const IsotopeData Te_IsoData[] = { 
    { 120, 119.90404 }, { 122, 121.903052}, { 123, 122.904271 }, { 124, 123.902818 }, 
    { 125, 124.904429 }, { 126, 125.90331 }, { 128, 127.904464 }, { 130, 129.906229 }, { 0, 0.0 } 
    };

    const IsotopeData I_IsoData[] = { 
    { 127, 126.904475 }, { 0, 0.0 } 
    };

    const IsotopeData Xe_IsoData[] = { 
    { 124, 123.905894 }, { 126, 125.90427 }, { 128, 127.903531 }, { 129, 128.90478 }, 
    { 130, 129.903509 }, { 131, 130.905069 }, { 132, 131.904141 }, { 134, 133.9054 }, 
    { 136, 135.90722 }, { 0, 0.0 } 
    };

    const IsotopeData Cs_IsoData[] = { 
    { 133, 132.90544 }, { 0, 0.0 } 
    };
	
    const IsotopeData Ba_IsoData[] = { 
    { 130, 129.90629 }, { 132, 131.90504 }, { 134, 133.90449 }, { 135, 134.90567 }, 
    { 136, 135.90456 }, { 137, 136.90582 }, { 138, 137.90524 }, { 0, 0.0 } 
    };

    const IsotopeData La_IsoData[] = { 
    { 138, 137.90711 }, { 139, 138.906347 }, { 0, 0.0 } 
    };

    const IsotopeData Ce_IsoData[] = { 
    { 136, 135.90714 }, { 138, 137.90599 }, { 140, 139.905434 }, { 142, 141.909241 }, { 0, 0.0 } 
    };

    const IsotopeData Pr_IsoData[] = { 
    { 141, 140.90768 }, { 0, 0.0 } 
    };

    const IsotopeData Nd_IsoData[] = { 
    { 142, 141.907719 }, { 143, 142.90981 }, { 144, 143.910083 }, { 145, 144.91257 }, 
    { 146, 145.913113 }, { 148, 147.916889 }, { 150, 149.920888 }, { 0, 0.0 } 
    };

    const IsotopeData Sm_IsoData[] = { 
    { 144, 143.911997 }, { 147, 146.914894 }, { 148, 147.914819 }, { 149, 148.917181 }, 
    { 150, 149.917273 }, { 152, 151.919729 }, { 154, 153.922206 }, { 0, 0.0 } 
    };

    const IsotopeData Eu_IsoData[] = { 
    { 151, 150.919846 }, { 153, 152.921226 }, { 0, 0.0 } 
    };

    const IsotopeData Gd_IsoData[] = { 
    { 152, 151.919788 }, { 154, 153.920862 }, { 155, 154.922619 }, { 156, 155.922119 }, 
    { 157, 156.923957 }, { 158, 157.9241 }, { 160, 159.92705 }, { 0, 0.0 } 
    };

    const IsotopeData Tb_IsoData[] = { 
    { 159, 158.925344 }, { 0, 0.0 } 
    };

    const IsotopeData Dy_IsoData[] = { 
    { 156, 155.92428 }, { 158, 157.924403 }, { 160, 159.925194 }, { 161, 160.926931 }, 
    { 162, 161.926796 }, { 163, 162.928729 }, { 164, 163.929173 }, { 0, 0.0 } 
    };

    const IsotopeData Ho_IsoData[] = { 
    { 165, 164.93032 }, { 0, 0.0 } 
    };

    const IsotopeData Er_IsoData[] = { 
    { 162, 161.928776 }, { 164, 163.929199 }, { 166, 165.930292 }, { 167, 166.932047 }, 
    { 168, 167.93237 }, { 170, 169.935463 }, { 0, 0.0 } 
    };

    const IsotopeData Tm_IsoData[] = { 
    { 169, 168.934213 }, { 0, 0.0 } 
    };

    const IsotopeData Yb_IsoData[] = { 
    { 168, 167.933897 }, { 170, 169.934761 }, { 171, 170.936325 }, { 172, 171.93638 }, 
    { 173, 172.938209 }, { 174, 173.938861 }, { 176, 175.942565 }, { 0, 0.0 } 
    };

    const IsotopeData Lu_IsoData[] = { 
    { 175, 174.940771 }, { 176, 175.94268 }, { 0, 0.0 } 
    };

    const IsotopeData Hf_IsoData[] = { 
    { 174, 173.940042 }, { 176, 175.941404 }, { 177, 176.943219 }, { 178, 177.943697 }, 
    { 179, 178.945813 }, { 180, 179.946548 }, { 0, 0.0 } 
    };

    const IsotopeData Ta_IsoData[] = { 
    { 180, 179.947462 }, { 181, 180.947994 }, { 0, 0.0 } 
    };

    const IsotopeData W_IsoData[] = { 
    { 180, 179.946702 }, { 182, 181.948202 }, { 183, 182.950221 }, { 184, 183.950929 }, 
    { 186, 185.954358 }, { 0, 0.0 } 
    };

    const IsotopeData Re_IsoData[] = { 
    { 185, 184.952952 }, { 187, 186.955747 }, { 0, 0.0 } 
    };

    const IsotopeData Os_IsoData[] = { 
    { 184, 183.952487 }, { 186, 185.953835 }, { 187, 186.955744 }, { 188, 187.955832 }, 
    { 189, 188.958140 }, { 190, 189.958439 }, { 192, 191.961469 }, { 0, 0.0 } 
    };

    const IsotopeData Ir_IsoData[] = { 
    {191, 190.960585 }, { 193, 192.962916 }, { 0, 0.0 } 
    };

    const IsotopeData Pt_IsoData[] = { 
    { 190, 189.959920 }, { 192, 191.961027 }, { 194, 193.962655 }, { 195, 194.964766 }, 
    { 196, 195.964926 }, { 198, 197.967867 }, { 0, 0.0 } 
    };

    const IsotopeData Au_IsoData[] = { 
    { 197, 196.966543 }, { 0, 0.0 } 
    };

    const IsotopeData Hg_IsoData[] = { 
    { 196, 195.965806 }, { 198, 197.966743 }, { 199, 198.968254 }, { 200, 199.968300 }, 
    { 201, 200.970276 }, { 202, 201.970617 }, { 204, 203.973467 }, { 0, 0.0 } 
    };

    const IsotopeData Tl_IsoData[] = { 
    { 203, 202.972320 }, { 205, 204.974401 }, { 0, 0.0 } 
    };

    const IsotopeData Pb_IsoData[] = { 
    { 204, 203.973020 }, { 206, 205.974440 }, { 207, 206.975871 }, { 208, 207.976627 }, { 0, 0.0 } 
    };

    const IsotopeData Bi_IsoData[] = { 
    { 209, 208.980373 }, { 0, 0.0 } 
    };

    const IsotopeData Th_IsoData[] = { 
    { 232, 232.038051 }, { 0, 0.0 } 
    };

    const IsotopeData U_IsoData[] = { 
    { 234, 234.040947 }, { 235, 235.043924 }, { 238, 239.050785 }, { 0, 0.0 } 
    };

    const AtomDictData builtinDictData[] = {
    { Chem::AtomType::H,  0, "H",  "Hydrogen",     1,   1.00794,    1,  1, false, true,  { 1, -1 },                   1.2,  { 0.32, 0,    0 },    2.2,  H_IsoData  },
    { Chem::AtomType::H,  1, "H",  "Hydrogen",     1,   1.00794,    1,  1, false, true,  { 1, -1 },                   1.2,  { 0.32, 0,    0 },    2.2,  H_IsoData  },
    { Chem::AtomType::H,  2, "D",  "Deuterium",    1,   1.00794,    1,  1, false, true,  { 1, -1 },                   1.2,  { 0.32, 0,    0 },    2.2,  H_IsoData  },
    { Chem::AtomType::H,  3, "T",  "Tritium",      1,   1.00794,    1,  1, false, true,  { 1, -1 },                   1.2,  { 0.32, 0,    0 },    2.2,  H_IsoData  },
    { Chem::AtomType::He, 0, "He", "Helium",       4,   4.002602,   18, 1, false, true,  { -1 },                      1.4,  { 0.46, 0,    0 },    0,    He_IsoData }, 
    { Chem::AtomType::Li, 0, "Li", "Lithium",      7,   6.941,      1,  2, true,  false, { 1, -1 },                   1.82, { 1.33, 1.24, 0 },    1.0,  Li_IsoData }, 
    { Chem::AtomType::Be, 0, "Be", "Beryllium",    9,   9.012182,   2,  2, true,  false, { 2, -1 },                   1.53, { 1.02, 0.90, 0.85 }, 1.5,  Be_IsoData }, 
    { Chem::AtomType::B,  0, "B",  "Boron",        11,  10.811,     13, 2, true,  true,  { 3, -1 },                   1.92, { 0.85, 0.78, 0.73 }, 2.0,  B_IsoData  }, 
    { Chem::AtomType::C,  0, "C",  "Carbon",       12,  12.0107,    14, 2, false, true,  { 4, 2, -1 },                1.7,  { 0.75, 0.67, 0.60 }, 2.5,  C_IsoData  },
    { Chem::AtomType::N,  0, "N",  "Nitrogen",     14,  14.0067,    15, 2, false, true,  { 3, 2, 1, -1 },             1.55, { 0.71, 0.60, 0.54 }, 3.1,  N_IsoData  }, 
    { Chem::AtomType::O,  0, "O",  "Oxygen",       16,  15.9994,    16, 2, false, true,  { 2, -1 },                   1.52, { 0.63, 0.57, 0.53 }, 3.5,  O_IsoData  }, 
    { Chem::AtomType::F,  0, "F",  "Fluorine",     19,  18.9984032, 17, 2, false, true,  { 1, -1 },                   1.47, { 0.64, 0.59, 0.53 }, 4.1,  F_IsoData  }, 
    { Chem::AtomType::Ne, 0, "Ne", "Neon",         20,  20.1797,    18, 2, false, true,  { -1 },                      1.54, { 0.67, 0.96, 0 },    0,    Ne_IsoData },
    { Chem::AtomType::Na, 0, "Na", "Sodium",       23,  22.98977,   1,  3, true,  false, { 1, -1 },                   2.27, { 1.55, 1.60, 0 },    1.0,  Na_IsoData },
    { Chem::AtomType::Mg, 0, "Mg", "Magnesium",    24,  24.3050,    2,  3, true,  false, { 2, -1 },                   1.73, { 1.39, 1.32, 1.27 }, 1.2,  Mg_IsoData },
    { Chem::AtomType::Al, 0, "Al", "Aluminium",    27,  26.981538,  13, 3, true,  false, { 3, -1 },                   1.84, { 1.26, 1.13, 1.11 }, 1.5,  Al_IsoData },
    { Chem::AtomType::Si, 0, "Si", "Silicon",      28,  28.0855,    14, 3, true,  true,  { 4, 2, -1 },                2.1,  { 1.16, 1.07, 1.02 }, 1.7,  Si_IsoData },
    { Chem::AtomType::P,  0, "P",  "Phosphorus",   31,  30.973761,  15, 3, false, true,  { 3, 5, -1 },                1.8,  { 1.11, 1.02, 0.94 }, 2.1,  P_IsoData  },
    { Chem::AtomType::S,  0, "S",  "Sulfur",       32,  32.065,     16, 3, false, true,  { 2, 4, 6, -1 },             1.8,  { 1.03, 0.94, 0.95 }, 2.4,  S_IsoData  },
    { Chem::AtomType::Cl, 0, "Cl", "Chlorine",     35,  35.453,     17, 3, false, true,  { 1, 3, 5, 7, 2, 4, -1 },    1.75, { 0.99, 0.95, 0.93 }, 2.8,  Cl_IsoData },
    { Chem::AtomType::Ar, 0, "Ar", "Argon",        40,  39.948,     18, 3, false, true,  { -1 },                      1.88, { 0.96, 1.07, 0.96 }, 0,    Ar_IsoData },
    { Chem::AtomType::K,  0, "K",  "Potassium",    39,  39.0983,    1,  4, true,  false, { 1, -1 },                   2.75, { 1.96, 1.93, 0 },    0.9,  K_IsoData  },  
    { Chem::AtomType::Ca, 0, "Ca", "Calcium",      40,  40.078,     2,  4, true,  false, { 2, -1 },                   2.31, { 1.71, 1.47, 1.33 }, 1.0,  Ca_IsoData },  
    { Chem::AtomType::Sc, 0, "Sc", "Scandium",     45,  44.95591,   3,  4, true,  false, { 3, -1 },                   1.7,  { 1.48, 1.16, 1.14 }, 1.2,  Sc_IsoData },
    { Chem::AtomType::Ti, 0, "Ti", "Titanium",     48,  47.867,     4,  4, true,  false, { 2, 3, 4, -1 },             1.7,  { 1.36, 1.17, 1.08 }, 1.3,  Ti_IsoData },
    { Chem::AtomType::V,  0, "V",  "Vanadium",     51,  50.9415,    5,  4, true,  false, { 2, 3, 4, 5, -1 },          1.7,  { 1.34, 1.12, 1.06 }, 1.5,  V_IsoData  },
    { Chem::AtomType::Cr, 0, "Cr", "Chromium",     52,  51.9961,    6,  4, true,  false, { 2, 3, 6, -1 },             1.7,  { 1.22, 1.11, 1.03 }, 1.6,  Cr_IsoData },
    { Chem::AtomType::Mn, 0, "Mn", "Manganese",    55,  54.938049,  7,  4, true,  false, { 2, 4, 7, 3, 6, -1 },       1.7,  { 1.19, 1.05, 1.03 }, 1.6,  Mn_IsoData },
    { Chem::AtomType::Fe, 0, "Fe", "Iron",         56,  55.845,     8,  4, true,  false, { 2, 3, 4, 6, -1 },          1.7,  { 1.16, 1.09, 1.02 }, 1.6,  Fe_IsoData },
    { Chem::AtomType::Co, 0, "Co", "Cobalt",       59,  58.9332,    9,  4, true,  false, { 2, 3, 4, -1 },             1.7,  { 1.11, 1.03, 0.96 }, 1.7,  Co_IsoData },
    { Chem::AtomType::Ni, 0, "Ni", "Nickel",       58,  58.6934,    10, 4, true,  false, { 2, 1, 3, 4, -1 },          1.63, { 1.10, 1.01, 1.01 }, 1.8,  Ni_IsoData },
    { Chem::AtomType::Cu, 0, "Cu", "Copper",       63,  63.546,     11, 4, true,  false, { 1, 2, 3, -1 },             1.4,  { 1.12, 1.15, 1.20 }, 1.8,  Cu_IsoData },
    { Chem::AtomType::Zn, 0, "Zn", "Zinc",         64,  65.409,     12, 4, true,  false, { 2, -1 },                   1.39, { 1.18, 1.20, 0 },    1.7,  Zn_IsoData },
    { Chem::AtomType::Ga, 0, "Ga", "Gallium",      69,  69.723,     13, 4, true,  false, { 3, 2, -1 },                1.87, { 1.24, 1.17, 1.21 }, 1.8,  Ga_IsoData },
    { Chem::AtomType::Ge, 0, "Ge", "Germanium",    74,  72.64,      14, 4, true,  true,  { 4, 2, -1 },                2.11, { 1.21, 1.11, 1.14 }, 2.0,  Ge_IsoData },
    { Chem::AtomType::As, 0, "As", "Arsenic",      75,  74.9216,    15, 4, true,  true,  { 3, 5, 2, -1 },             1.85, { 1.21, 1.14, 1.06 }, 2.2,  As_IsoData },
    { Chem::AtomType::Se, 0, "Se", "Selenium",     80,  78.96,      16, 4, true,  true,  { 2, 4, 6, -1 },             1.9,  { 1.16, 1.07, 1.07 }, 2.5,  Se_IsoData },
    { Chem::AtomType::Br, 0, "Br", "Bromine",      79,  79.904,     17, 4, false, true,  { 1, 5, 3, 4, -1 },          1.85, { 1.14, 1.09, 1.10 }, 2.7,  Br_IsoData },
    { Chem::AtomType::Kr, 0, "Kr", "Krypton",      84,  83.798,     18, 4, false, true,  { -1 },                      2.02, { 1.17, 1.21, 1.08 }, 0,    Kr_IsoData },
    { Chem::AtomType::Rb, 0, "Rb", "Rubidium",     85,  85.4678,    1,  5, true,  false, { 1, -1 },                   3.03, { 2.10, 2.02, 0 },    0.9,  Rb_IsoData },
    { Chem::AtomType::Sr, 0, "Sr", "Strontium",    88,  87.62,      2,  5, true,  false, { 2, -1 },                   2.49, { 1.85, 1.57, 1.39 }, 1.0,  Sr_IsoData },
    { Chem::AtomType::Y,  0, "Y" , "Yttrium",      89,  88.90585,   3,  5, true,  false, { 3, -1 },                   1.7,  { 1.63, 1.30, 1.24 }, 1.1,  Y_IsoData  },
    { Chem::AtomType::Zr, 0, "Zr", "Zirconium",    90,  91.224,     4,  5, true,  false, { 4, 2, 3, -1 },             1.7,  { 1.54, 1.27, 1.21 }, 1.2,  Zr_IsoData },
    { Chem::AtomType::Nb, 0, "Nb", "Niobium",      93,  92.90638,   5,  5, true,  false, { 3, 5, 2, 4, -1 },          1.7,  { 1.47, 1.25, 1.16 }, 1.2,  Nb_IsoData },
    { Chem::AtomType::Mo, 0, "Mo", "Molybdenum",   98,  95.94,      6,  5, true,  false, { 3, 6, 2, 4, 5, -1 },       1.7,  { 1.38, 1.21, 1.13 }, 1.3,  Mo_IsoData },
    { Chem::AtomType::Tc, 0, "Tc", "Technetium",   98,  98.0,       7,  5, true,  false, { 6, -1 },                   1.7,  { 1.28, 1.20, 1.10 }, 1.4,  0          },
    { Chem::AtomType::Ru, 0, "Ru", "Ruthenium",    102, 101.07,     8,  5, true,  false, { 3, 4, 8, 2, 6, 7, -1 },    1.7,  { 1.25, 1.14, 1.03 }, 1.4,  Ru_IsoData },
    { Chem::AtomType::Rh, 0, "Rh", "Rhodium",      103, 102.9055,   9,  5, true,  false, { 4, 2, 3, 6, -1 },          1.7,  { 1.25, 1.10, 1.06 }, 1.5,  Rh_IsoData },
    { Chem::AtomType::Pd, 0, "Pd", "Palladium",    106, 106.42,     10, 5, true,  false, { 2, 4, 6, -1 },             1.63, { 1.20, 1.17, 1.12 }, 1.4,  Pd_IsoData },
    { Chem::AtomType::Ag, 0, "Ag", "Silver",       107, 107.8682,   11, 5, true,  false, { 1, 2, 3, -1 },             1.72, { 1.28, 1.39, 1.37 }, 1.4,  Ag_IsoData },
    { Chem::AtomType::Cd, 0, "Cd", "Cadmium",      114, 112.411,    12, 5, true,  false, { 2, 1, -1 },                1.58, { 1.36, 1.44, 0 },    1.5,  Cd_IsoData },
    { Chem::AtomType::In, 0, "In", "Indium",       115, 114.818,    13, 5, true,  false, { 3, 1, 2, -1 },             1.93, { 1.42, 1.36, 1.46 }, 1.5,  In_IsoData },
    { Chem::AtomType::Sn, 0, "Sn", "Tin",          120, 118.710,    14, 5, true,  false, { 4, 2, -1 },                2.17, { 1.40, 1.30, 1.32 }, 1.7,  Sn_IsoData },
    { Chem::AtomType::Sb, 0, "Sb", "Antimony",     121, 121.760,    15, 5, true,  true,  { 3, 5, 4, -1 },             2.06, { 1.40, 1.33, 1.27 }, 1.8,  Sb_IsoData },
    { Chem::AtomType::Te, 0, "Te", "Tellurium",    130, 127.60,     16, 5, true,  true,  { 2, 4, 6, -1 },             2.06, { 1.36, 1.28, 1.21 }, 2.0,  Te_IsoData },
    { Chem::AtomType::I,  0, "I" , "Iodine",       127, 126.90447,  17, 5, false, true,  { 1, 5, 7, 3, 4, -1 },       1.98, { 1.33, 1.29, 1.25 }, 2.2,  I_IsoData  },
    { Chem::AtomType::Xe, 0, "Xe", "Xenon",        132, 131.293,    18, 5, false, true,  { -1 },                      2.16, { 1.31, 1.35, 1.22 }, 0,    Xe_IsoData },
    { Chem::AtomType::Cs, 0, "Cs", "Caesium",      133, 132.90545,  1,  6, true,  false, { 1, -1 },                   3.43, { 2.32, 2.09, 0 },    0.9,  Cs_IsoData },
    { Chem::AtomType::Ba, 0, "Ba", "Barium",       138, 137.327,    2,  6, true,  false, { 2, -1 },                   2.68, { 1.96, 1.61, 1.49 }, 1.0,  Ba_IsoData },
    { Chem::AtomType::La, 0, "La", "Lanthanum",    139, 138.9055,   3,  6, true,  false, { 3, -1 },                   1.7,  { 1.80, 1.39, 1.39 }, 1.1,  La_IsoData },
    { Chem::AtomType::Ce, 0, "Ce", "Cerium",       140, 140.116,    3,  6, true,  false, { 3, 4, -1 },                1.7,  { 1.63, 1.37, 1.31 }, 1.1,  Ce_IsoData },
    { Chem::AtomType::Pr, 0, "Pr", "Praseodymium", 141, 140.90765,  3,  6, true,  false, { 3, -1 },                   1.7,  { 1.76, 1.38, 1.28 }, 1.1,  Pr_IsoData },
    { Chem::AtomType::Nd, 0, "Nd", "Neodymium",    144, 144.24,     3,  6, true,  false, { 3, 4, -1 },                1.7,  { 1.74, 1.37, 0 },    1.1,  Nd_IsoData },
    { Chem::AtomType::Pm, 0, "Pm", "Promethium",   147, 145.0,      3,  6, true,  false, { 3, -1 },                   1.7,  { 1.73, 1.35, 0 },    1.1,  0          },
    { Chem::AtomType::Sm, 0, "Sm", "Samarium",     152, 150.36,     3,  6, true,  false, { 3, 2, -1 },                1.7,  { 1.72, 1.34, 0 },    1.1,  Sm_IsoData },
    { Chem::AtomType::Eu, 0, "Eu", "Europium",     153, 151.964,    3,  6, true,  false, { 3, 2, -1 },                1.7,  { 1.68, 1.34, 0 },    1.0,  Eu_IsoData },
    { Chem::AtomType::Gd, 0, "Gd", "Gadolinium",   158, 157.25,     3,  6, true,  false, { 3, -1 },                   1.7,  { 1.69, 1.35, 1.32 }, 1.1,  Gd_IsoData },
    { Chem::AtomType::Tb, 0, "Tb", "Terbium",      159, 158.92534,  3,  6, true,  false, { 3, 4, -1 },                1.7,  { 1.68, 1.35, 0 },    1.1,  Tb_IsoData },
    { Chem::AtomType::Dy, 0, "Dy", "Dysprosium",   164, 162.50,     3,  6, true,  false, { 3, -1 },                   1.7,  { 1.67, 1.33, 0 },    1.1,  Dy_IsoData },
    { Chem::AtomType::Ho, 0, "Ho", "Holmium",      165, 164.93032,  3,  6, true,  false, { 3, -1 },                   1.7,  { 1.66, 1.33, 0 },    1.1,  Ho_IsoData },
    { Chem::AtomType::Er, 0, "Er", "Erbium",       166, 167.259,    3,  6, true,  false, { 3, -1 },                   1.7,  { 1.65, 1.33, 0 },    1.1,  Er_IsoData },
    { Chem::AtomType::Tm, 0, "Tm", "Thulium",      169, 168.93421,  3,  6, true,  false, { 3, 2, -1 },                1.7,  { 1.64, 1.31, 0 },    1.1,  Tm_IsoData },
    { Chem::AtomType::Yb, 0, "Yb", "Ytterbium",    174, 173.04,     3,  6, true,  false, { 3, 2, -1 },                1.7,  { 1.70, 1.29, 0 },    1.1,  Yb_IsoData },
    { Chem::AtomType::Lu, 0, "Lu", "Lutetium",     175, 174.967,    3,  6, true,  false, { 3, -1 },                   1.7,  { 1.62, 1.31, 1.31 }, 1.1,  Lu_IsoData },
    { Chem::AtomType::Hf, 0, "Hf", "Hafnium",      178, 178.49,     4,  6, true,  false, { 4, -1 },                   1.7,  { 1.52, 1.28, 1.22 }, 1.2,  Hf_IsoData },
    { Chem::AtomType::Ta, 0, "Ta", "Tantalum",     181, 180.9479,   5,  6, true,  false, { 5, 3, 4, -1 },             1.7,  { 1.46, 1.26, 1.19 }, 1.3,  Ta_IsoData },
    { Chem::AtomType::W,  0, "W" , "Tungsten",     184, 183.84,     6,  6, true,  false, { 6, 2, 3, 4, 5, -1 },       1.7,  { 1.37, 1.20, 1.15 }, 1.4,  W_IsoData  },
    { Chem::AtomType::Re, 0, "Re", "Rhenium",      187, 186.207,    7,  6, true,  false, { 2, 4, 6, 7, 1, 3, 5, -1 }, 1.7,  { 1.31, 1.19, 1.10 }, 1.5,  Re_IsoData },
    { Chem::AtomType::Os, 0, "Os", "Osmium",       192, 190.23,     8,  6, true,  false, { 3, 4, 6, 8, 2, -1 },       1.7,  { 1.29, 1.16, 1.09 }, 1.5,  Os_IsoData },
    { Chem::AtomType::Ir, 0, "Ir", "Iridium",      193, 192.217,    9,  6, true,  false, { 3, 4, 6, 1, 2, -1 },       1.7,  { 1.22, 1.15, 1.07 }, 1.6,  Ir_IsoData },
    { Chem::AtomType::Pt, 0, "Pt", "Platinum",     195, 195.078,    10, 6, true,  false, { 2, 4, 6, 1, 3, -1 },       1.75, { 1.23, 1.12, 1.10 }, 1.4,  Pt_IsoData },
    { Chem::AtomType::Au, 0, "Au", "Gold",         197, 196.96655,  11, 6, true,  false, { 1, 3, 2, -1 },             1.66, { 1.24, 1.21, 1.23 }, 1.4,  Au_IsoData },
    { Chem::AtomType::Hg, 0, "Hg", "Mercury",      202, 200.59,     12, 6, true,  false, { 1, 2, -1 },                1.55, { 1.33, 1.42, 0 },    1.4,  Hg_IsoData },
    { Chem::AtomType::Tl, 0, "Tl", "Thallium",     205, 204.3833,   13, 6, true,  false, { 1, 3, 2, -1 },             1.96, { 1.44, 1.42, 1.50 }, 1.4,  Tl_IsoData },
    { Chem::AtomType::Pb, 0, "Pb", "Lead",         208, 207.2,      14, 6, true,  false, { 2, 4, -1 },                2.02, { 1.44, 1.35, 1.37 }, 1.6,  Pb_IsoData },
    { Chem::AtomType::Bi, 0, "Bi", "Bismuth",      209, 208.98038,  15, 6, true,  false, { 3, 2, 4, 5, -1 },          2.07, { 1.51, 1.41, 1.35 }, 1.7,  Bi_IsoData },
    { Chem::AtomType::Po, 0, "Po", "Polonium",     209, 209.0,      16, 6, true,  true,  { 2, 4, 6, -1 },             1.97, { 1.45, 1.35, 1.29 }, 1.8,  0          },
    { Chem::AtomType::At, 0, "At", "Astatine",     219, 210.0,      17, 6, true,  true,  { -1 },                      2.02, { 1.47, 1.38, 1.38 }, 2.0,  0          },
    { Chem::AtomType::Rn, 0, "Rn", "Radon",        222, 222.0,      18, 6, false, true,  { -1 },                      2.2,  { 1.42, 1.45, 1.33 }, 0,    0          },
    { Chem::AtomType::Fr, 0, "Fr", "Francium",     223, 223.0,      1,  7, true,  false, { -1 },                      3.48, { 2.23, 2.18, 0 },    0.9,  0          },
    { Chem::AtomType::Ra, 0, "Ra", "Radium",       226, 226.0,      2,  7, true,  false, { 2, -1 },                   2.83,  { 2.01, 1.73, 1.59 }, 1.0,  0          },
    { Chem::AtomType::Ac, 0, "Ac", "Actinium",     227, 227.0,      3,  7, true,  false, { 3, -1 },                   1.7,  { 1.86, 1.53, 1.40 }, 1.0,  0          },
    { Chem::AtomType::Th, 0, "Th", "Thorium",      232, 232.0381,   3,  7, true,  false, { 4, -1 },                   1.7,  { 1.75, 1.43, 1.36 }, 1.1,  Th_IsoData },
    { Chem::AtomType::Pa, 0, "Pa", "Protactinium", 231, 231.03588,  3,  7, true,  false, { 5, -1 },                   1.7,  { 1.69, 1.38, 1.29 }, 1.1,  0          },
    { Chem::AtomType::U,  0, "U",  "Uranium",      298, 238.02891,  3,  7, true,  false, { 3, 4, 6, 2, 5, -1 },       1.86, { 1.70, 1.34, 1.18 }, 1.2,  U_IsoData  },
    { Chem::AtomType::Np, 0, "Np", "Neptunium",    237, 237.0,      3,  7, true,  false, { -1 },                      1.7,  { 1.71, 1.36, 1.16 }, 1.2,  0          },
    { Chem::AtomType::Pu, 0, "Pu", "Plutonium",    244, 244.0,      3,  7, true,  false, { -1 },                      1.7,  { 1.72, 1.35, 0 },    1.2,  0          },
    { Chem::AtomType::Am, 0, "Am", "Americium",    243, 243.0,      3,  7, true,  false, { -1 },                      1.7,  { 1.66, 1.35, 0 },    1.2,  0          },
    { Chem::AtomType::Cm, 0, "Cm", "Curium",       247, 247.0,      3,  7, true,  false, { -1 },                      1.7,  { 1.66, 1.36, 0 },    1.2,  0          },
    { Chem::AtomType::Bk, 0, "Bk", "Berkelium",    247, 247.0,      3,  7, true,  false, { -1 },                      1.7,  { 1.68, 1.39, 0 },    1.2,  0          },
    { Chem::AtomType::Cf, 0, "Cf", "Californium",  251, 251.0,      3,  7, true,  false, { -1 },                      1.7,  { 1.68, 1.40, 0 },    1.2,  0          },
    { Chem::AtomType::Es, 0, "Es", "Einsteinium",  252, 252.0,      3,  7, true,  false, { -1 },                      1.7,  { 1.65, 1.40, 0 },    1.2,  0          },
    { Chem::AtomType::Fm, 0, "Fm", "Fermium",      257, 257.0,      3,  7, true,  false, { -1 },                      1.7,  { 1.67, 0,    0 },    1.2,  0          },
    { Chem::AtomType::Md, 0, "Md", "Mendelevium",  258, 258.0,      3,  7, true,  false, { -1 },                      1.7,  { 1.73, 1.39, 0 },    1.2,  0          },
    { Chem::AtomType::No, 0, "No", "Nobelium",     259, 259.0,      3,  7, true,  false, { -1 },                      1.7,  { 1.76, 0,    0 },    0,    0          },
    { Chem::AtomType::Lr, 0, "Lr", "Lawrencium",   262, 262.0,      3,  7, true,  false, { -1 },                      1.7,  { 1.61, 1.41, 0 },    0,    0          },
    { Chem::AtomType::Ru, 0, "Rf", "Rutherfordium",261, 261.0,      4,  7, true,  false, { -1 },                      1.7,  { 1.57, 1.40, 1.31 }, 0,    0          },
    { Chem::AtomType::Db, 0, "Db", "Dubnium",      262, 262.0,      5,  7, true,  false, { -1 },                      1.7,  { 1.49, 1.36, 1.26 }, 0,    0          },
    { Chem::AtomType::Sg, 0, "Sg", "Seaborgium",   266, 266.0,      6,  7, true,  false, { -1 },                      1.7,  { 1.43, 1.28, 1.21 }, 0,    0          },
    { Chem::AtomType::Bh, 0, "Bh", "Bohrium",      264, 264.0,      7,  7, true,  false, { -1 },                      1.7,  { 1.41, 1.28, 1.19 }, 0,    0          },
    { Chem::AtomType::Hs, 0, "Hs", "Hassium",      269, 277.0,      8,  7, true,  false, { -1 },                      1.7,  { 1.34, 1.25, 1.18 }, 0,    0          },
    { Chem::AtomType::Mt, 0, "Mt", "Meitnerium",   268, 268.0,      9,  7, true,  false, { -1 },                      1.7,  { 1.29, 1.25, 1.13 }, 0,    0          },
    { Chem::AtomType::A,  0, "A",  "",             0,   0,          0,  0, false, false, { -1 },                      0,    { 0,    0,    0 },    0,    0          },
    { Chem::AtomType::AH, 0, "AH", "",             0,   0,          0,  0, false, false, { -1 },                      0,    { 0,    0,    0 },    0,    0          },
    { Chem::AtomType::Q,  0, "Q",  "",             0,   0,          0,  0, false, false, { -1 },                      0,    { 0,    0,    0 },    0,    0          },
    { Chem::AtomType::QH, 0, "QH", "",             0,   0,          0,  0, false, false, { -1 },                      0,    { 0,    0,    0 },    0,    0          },
    { Chem::AtomType::M,  0, "M",  "",             0,   0,          0,  0, false, false, { -1 },                      0,    { 0,    0,    0 },    0,    0          },
    { Chem::AtomType::MH, 0, "MH", "",             0,   0,          0,  0, false, false, { -1 },                      0,    { 0,    0,    0 },    0,    0          },
    { Chem::AtomType::X,  0, "X",  "",             0,   0,          0,  0, false, false, { -1 },                      0,    { 0,    0,    0 },    0,    0          },
    { Chem::AtomType::XH, 0, "XH", "",             0,   0,          0,  0, false, false, { -1 },                      0,    { 0,    0,    0 },    0,    0          },
    { Chem::AtomType::ANY,0, "*",  "",             0,   0,          0,  0, false, false, { -1 },                      0,    { 0,    0,    0 },    0,    0          }
    };

    Chem::AtomDictionary::SharedPointer builtinDictionary(new Chem::AtomDictionary());
	const Chem::AtomDictionary::Entry   DEF_ENTRY;

	struct Init
	{

		Init() {
			builtinDictionary->loadDefaults();
		}

	} init;
}


Chem::AtomDictionary::SharedPointer Chem::AtomDictionary::defaultDict = builtinDictionary;


Chem::AtomDictionary::Entry::Entry():
	atomType(AtomType::UNKNOWN),
	isotope(0),
	symbol(),
	name(),
	mostAbundantIso(0),
	avgWeight(0.0),
	iupacGroup(0),
	isMet(false),
	isNonMet(false),
	valenceStates(),
	vdwRadius(0.0),
	allredRochowEneg(0.0),
	isoMassMap()	
{
	covalentRadii[0] = 0.0;
	covalentRadii[1] = 0.0;
	covalentRadii[2] = 0.0;
}

Chem::AtomDictionary::Entry::Entry(unsigned int atom_type, std::size_t iso, const std::string& sym,
								   const std::string& name, std::size_t most_abdt_iso, double avg_weight,
								   std::size_t iupac_grp, std::size_t period, bool metal, bool non_metal, const Util::STArray& val_states,
								   double vdw_rad, const double cov_radii[3], double ar_eneg, const IsotopeMassMap& iso_masses):
	atomType(atom_type),
	isotope(iso),
	symbol(sym),
	name(name),
	mostAbundantIso(most_abdt_iso),
	avgWeight(avg_weight),
	iupacGroup(iupac_grp),
	period(period),
	isMet(metal),
	isNonMet(non_metal),
	valenceStates(val_states),
	vdwRadius(vdw_rad),
	allredRochowEneg(ar_eneg),
	isoMassMap(iso_masses)	
{
	covalentRadii[0] = cov_radii[0];
	covalentRadii[1] = cov_radii[1];
	covalentRadii[2] = cov_radii[2];
}

unsigned int Chem::AtomDictionary::Entry::getType() const
{
	return atomType;
}

std::size_t Chem::AtomDictionary::Entry::getIsotope() const
{
	return isotope;
}

const std::string& Chem::AtomDictionary::Entry::getSymbol() const
{
	return symbol;
}

const std::string& Chem::AtomDictionary::Entry::getName() const
{
	return name;
}

std::size_t Chem::AtomDictionary::Entry::getMostAbundantIsotope() const
{
	return mostAbundantIso;
}

double Chem::AtomDictionary::Entry::getAverageWeight() const
{
	return avgWeight;
}

std::size_t Chem::AtomDictionary::Entry::getIUPACGroup() const
{
	return iupacGroup;
}

std::size_t Chem::AtomDictionary::Entry::getPeriod() const
{
	return period;
}

bool Chem::AtomDictionary::Entry::isMetal() const
{
	return isMet;
}

bool Chem::AtomDictionary::Entry::isNonMetal() const
{
	return isNonMet;
}

const Util::STArray& Chem::AtomDictionary::Entry::getValenceStates() const
{
	return valenceStates;
}

double Chem::AtomDictionary::Entry::getVdWRadius() const
{
	return vdwRadius;
}

double Chem::AtomDictionary::Entry::getCovalentRadius(std::size_t order) const
{
	if (order > 3 || order < 1)
		return 0.0;

	return covalentRadii[order - 1];
}

double Chem::AtomDictionary::Entry::getAllredRochowElectronegativity() const
{
	return allredRochowEneg;
}

const Chem::AtomDictionary::Entry::IsotopeMassMap& Chem::AtomDictionary::Entry::getIsotopeMasses() const
{
	return isoMassMap;
}


void Chem::AtomDictionary::addEntry(const Entry& entry)
{
	EntryLookupTable::key_type key(entry.getType(), entry.getIsotope());

	entries.insert(EntryLookupTable::value_type(key, entry));
	strictSymToTypeTable.insert(SymbolToTypeLookupTable::value_type(entry.getSymbol(), entry.getType()));
	nonstrictSymToTypeTable.insert(SymbolToTypeLookupTable::value_type(boost::to_upper_copy(entry.getSymbol()), entry.getType()));
}

bool Chem::AtomDictionary::containsEntry(unsigned int type, std::size_t isotope) const
{
	EntryLookupTable::key_type key(type, isotope);
	EntryLookupTable::const_iterator it = entries.find(key);

	return (it != entries.end());
}

void Chem::AtomDictionary::removeEntry(unsigned int type, std::size_t isotope)
{
	EntryLookupTable::iterator it = entries.find(EntryLookupTable::key_type(type, isotope));

	if (it == entries.end())
		return;

	strictSymToTypeTable.erase(it->second.getSymbol());
	nonstrictSymToTypeTable.erase(boost::to_upper_copy(it->second.getSymbol()));
	entries.erase(it);
}
			
const Chem::AtomDictionary::Entry& Chem::AtomDictionary::getEntry(unsigned int type, std::size_t isotope) const
{
	EntryLookupTable::key_type key(type, isotope);
	EntryLookupTable::const_iterator it = entries.find(key);

	if (it != entries.end())
		return it->second;

	return DEF_ENTRY;
}

void Chem::AtomDictionary::clear()
{
	entries.clear();
	strictSymToTypeTable.clear();
	nonstrictSymToTypeTable.clear();
}

std::size_t Chem::AtomDictionary::getNumEntries() const
{
	return entries.size();
}
			
Chem::AtomDictionary::ConstEntryIterator Chem::AtomDictionary::getEntriesBegin() const
{
	return ConstEntryIterator(entries.begin(), std::bind(&EntryLookupTable::value_type::second, std::placeholders::_1));
}

Chem::AtomDictionary::ConstEntryIterator Chem::AtomDictionary::getEntriesEnd() const
{
	return ConstEntryIterator(entries.end(), std::bind(&EntryLookupTable::value_type::second, std::placeholders::_1));
}

Chem::AtomDictionary::ConstEntryIterator Chem::AtomDictionary::begin() const
{
	return ConstEntryIterator(entries.begin(), std::bind(&EntryLookupTable::value_type::second, std::placeholders::_1));
}

Chem::AtomDictionary::ConstEntryIterator Chem::AtomDictionary::end() const
{
	return ConstEntryIterator(entries.end(), std::bind(&EntryLookupTable::value_type::second, std::placeholders::_1));
}

void Chem::AtomDictionary::loadDefaults()
{
	Util::STArray val_states;
	Entry::IsotopeMassMap iso_masses;

	for (std::size_t i = 0; i < sizeof(builtinDictData) / sizeof(AtomDictData); i++) {
		const AtomDictData& data = builtinDictData[i];

		val_states.clear();
		iso_masses.clear();

		for (std::size_t j = 0; data.valenceStates[j] != -1; j++)
			val_states.addElement(data.valenceStates[j]);
	
		if (data.isotopeData) {
			for (std::size_t j = 0; data.isotopeData[j].isotope != 0; j++)
				iso_masses.insertEntry(data.isotopeData[j].isotope, data.isotopeData[j].weight);
		}

		addEntry(Entry(data.type, data.isotope, data.symbol, data.name,
					   data.mostAbundantIso, data.averageWeight, data.iupacGroup, data.period,
					   data.isMetal, data.isNonMetal, val_states, data.vdwRadius,
					   data.covalentRadii, data.allredRochowEneg, iso_masses));
	}
}

void Chem::AtomDictionary::set(const SharedPointer& dict)
{
	defaultDict = (!dict ? builtinDictionary : dict);
}

const Chem::AtomDictionary::SharedPointer& Chem::AtomDictionary::get()
{
    return defaultDict;
}

const std::string& Chem::AtomDictionary::getSymbol(unsigned int type, std::size_t iso) 
{
    return defaultDict->getEntry(type, iso).getSymbol();
}

const std::string& Chem::AtomDictionary::getName(unsigned int type, std::size_t iso) 
{
    return defaultDict->getEntry(type, iso).getName();
}

unsigned int Chem::AtomDictionary::getType(const std::string& sym, bool strict) 
{
	if (strict) {
		SymbolToTypeLookupTable::const_iterator it = defaultDict->strictSymToTypeTable.find(sym);

		if (it == defaultDict->strictSymToTypeTable.end())
			return AtomType::UNKNOWN;

		return it->second;
	}

	SymbolToTypeLookupTable::const_iterator it = defaultDict->nonstrictSymToTypeTable.find(boost::to_upper_copy(sym));

	if (it == defaultDict->nonstrictSymToTypeTable.end())
		return AtomType::UNKNOWN;

	return it->second;
}

std::size_t Chem::AtomDictionary::getMostAbundantIsotope(unsigned int type) 
{
    return defaultDict->getEntry(type, 0).getMostAbundantIsotope();
}

std::size_t Chem::AtomDictionary::getIUPACGroup(unsigned int type) 
{
    return defaultDict->getEntry(type, 0).getIUPACGroup();
}

std::size_t Chem::AtomDictionary::getPeriod(unsigned int type) 
{
    return defaultDict->getEntry(type, 0).getPeriod();
}

double Chem::AtomDictionary::getAtomicWeight(unsigned int type, std::size_t iso) 
{
    const Entry& entry = defaultDict->getEntry(type, 0);

    if (iso == 0)
		return entry.getAverageWeight();

    const Entry::IsotopeMassMap& iso_masses = entry.getIsotopeMasses();
    Entry::IsotopeMassMap::ConstEntryIterator it = iso_masses.getEntry(iso);

    if (it != iso_masses.getEntriesEnd())
		return it->second;

    return iso;
}

const Util::STArray& Chem::AtomDictionary::getValenceStates(unsigned int type)
{
    return defaultDict->getEntry(type, 0).getValenceStates();
}

std::size_t Chem::AtomDictionary::getNumValenceElectrons(unsigned int type)
{	
    std::size_t iupac_group = defaultDict->getEntry(type, 0).getIUPACGroup();

    return (iupac_group < 3 ? iupac_group : iupac_group > 12 ? iupac_group - 10 : iupac_group);
}

double Chem::AtomDictionary::getVdWRadius(unsigned int type) 
{
    return defaultDict->getEntry(type, 0).getVdWRadius();
}

double Chem::AtomDictionary::getCovalentRadius(unsigned int type, std::size_t order) 
{
    return defaultDict->getEntry(type, 0).getCovalentRadius(order);
}

double Chem::AtomDictionary::getAllredRochowElectronegativity(unsigned int type) 
{
    return defaultDict->getEntry(type, 0).getAllredRochowElectronegativity();
}

bool Chem::AtomDictionary::isChemicalElement(unsigned int type) 
{
    return (type > 0 && type <= AtomType::MAX_ATOMIC_NO);
}

bool Chem::AtomDictionary::isMainGroupElement(unsigned int type) 
{
    std::size_t iupac_group = defaultDict->getEntry(type, 0).getIUPACGroup();

    return (iupac_group > 0 && (iupac_group < 3 || iupac_group > 12));
}

bool Chem::AtomDictionary::isTransitionMetal(unsigned int type) 
{
    std::size_t iupac_group = defaultDict->getEntry(type, 0).getIUPACGroup();

    return (iupac_group >= 3 && iupac_group <= 12);
}

bool Chem::AtomDictionary::isMetal(unsigned int type) 
{
    return defaultDict->getEntry(type, 0).isMetal();
}

bool Chem::AtomDictionary::isSemiMetal(unsigned int type) 
{
    const Entry& entry = defaultDict->getEntry(type, 0);

    return (entry.isMetal() && entry.isNonMetal());
}

bool Chem::AtomDictionary::isNonMetal(unsigned int type) 
{
    return defaultDict->getEntry(type, 0).isNonMetal();
}

bool Chem::AtomDictionary::isHalogen(unsigned int type) 
{
    return (defaultDict->getEntry(type, 0).getIUPACGroup() == 17);
}

bool Chem::AtomDictionary::isNobleGas(unsigned int type) 
{
    return (defaultDict->getEntry(type, 0).getIUPACGroup() == 18);
}
