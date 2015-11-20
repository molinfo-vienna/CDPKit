/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomTypeFunctions.cpp 
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


#include "StaticInit.hpp"

#include <boost/unordered_map.hpp>

#include "CDPL/Chem/AtomTypeFunctions.hpp"
#include "CDPL/Chem/AtomType.hpp"


namespace 
{

	struct IsotopeData
	{

		std::size_t isotope;
		double      weight;
	};

	struct AtomTypeData
	{

		std::string        symbol;
		std::string        name;
		std::size_t        mostAbundantIso;
		double             averageWeight;
		std::size_t        iupacGroup;
		bool               isMetal;
		bool               isNonMetal;
		const int          valenceStates[8];
		double             vdwRadius;
		const double       covalentRadii[3];
		double             allredRochowEneg;
		const IsotopeData* isotopeData;
	};

	const IsotopeData HIsoData[] = { 
		{ 1, 1.0078503 }, { 2, 2.01410178 }, { 0, 0.0 } 
	};

	const IsotopeData HeIsoData[] = { 
		{ 3, 3.0160293 }, { 4, 4.00260323 }, { 0, 0.0 } 
	};

	const IsotopeData LiIsoData[] = { 
		{ 6, 6.015122 }, { 7, 7.016003 }, { 0, 0.0 } 
	};

	const IsotopeData BeIsoData[] = { 
		{ 9, 9.0121822 }, { 0, 0.0 } 
	};

	const IsotopeData BIsoData[] = { 
		{ 10, 10.0129372 }, { 11, 11.0093056 }, { 0, 0.0 } 
	};

	const IsotopeData CIsoData[] = { 
		{ 12, 12.0 }, { 13, 13.00335483 }, { 0, 0.0 } 
	};

	const IsotopeData NIsoData[] = { 
		{ 14, 14.003074 }, { 15, 15.00010896 }, { 0, 0.0 } 
	};

	const IsotopeData OIsoData[] = { 
		{ 16, 15.99491462 }, { 17, 16.9991314 }, { 18, 17.99916 }, { 0, 0.0 } 
	};

	const IsotopeData FIsoData[] = { 
		{ 19, 18.9984032 }, { 0, 0.0 } 
	};

	const IsotopeData NeIsoData[] = { 
		{ 20, 19.992434 }, { 21, 20.993841}, { 22, 21.991382 }, { 0, 0.0 } 
	};

	const IsotopeData NaIsoData[] = { 
		{ 23, 22.989767 }, { 0, 0.0 } 
	};

	const IsotopeData MgIsoData[] = { 
		{ 24, 23.985042 }, { 25, 24.985837 }, { 26, 25.982594 }, { 0, 0.0 } 
	};

	const IsotopeData AlIsoData[] = { 
		{ 27, 26.981538 }, { 0, 0.0 } 
	};

	const IsotopeData SiIsoData[] = { 
		{ 28, 27.976927 }, { 29, 28.976494 }, { 30, 29.97377 }, { 0, 0.0 } 
	};

	const IsotopeData PIsoData[] = { 
		{ 31, 30.973762 }, { 0, 0.0 } 
	};

	const IsotopeData SIsoData[] = { 
		{ 32, 31.9720705 }, { 33, 32.9714583 }, { 34, 33.9678685 }, { 36, 35.9670808 }, { 0, 0.0 } 
	};

	const IsotopeData ClIsoData[] = { 
		{ 35, 34.96885272 }, { 37, 36.9659026 }, { 0, 0.0 } 
	};

	const IsotopeData ArIsoData[] = { 
		{ 36, 35.967546 }, { 38, 37.962732 }, { 40, 39.962384 }, { 0, 0.0 } 
	};

	const IsotopeData KIsoData[] = { 
		{ 39, 38.963708 }, { 40, 39.9640022 }, { 41, 40.961827 }, { 0, 0.0 } 
	};

	const IsotopeData CaIsoData[] = { 
		{ 40, 39.962592 }, { 42, 41.958618 }, { 43, 42.958767 }, { 44, 43.955481 }, 
		{ 46, 15.953687 }, { 48, 47.952535 }, { 0, 0.0 } 
	};

	const IsotopeData ScIsoData[] = { 
		{ 45, 44.95591 }, { 0, 0.0 } 
	};

	const IsotopeData TiIsoData[] = { 
		{ 46, 45.95263 }, { 47, 46.951764 }, { 48, 47.947947 }, { 49, 48.947871 }, 
		{ 50, 49.944792 }, { 0, 0.0 } 
	};

	const IsotopeData VIsoData[] = { 
		{ 50, 49.947162 }, { 51, 50.943962 }, { 0, 0.0 } 
	};

	const IsotopeData CrIsoData[] = { 
		{ 50, 49.946047 }, { 52, 51.940511 }, { 53, 52.940652 }, { 54, 53.938884 }, { 0, 0.0 } 
	};

	const IsotopeData MnIsoData[] = { 
		{ 55, 54.938048 }, { 0, 0.0 } 
	};

	const IsotopeData FeIsoData[] = { 
		{ 54, 53.939613 }, { 56, 55.93494 }, { 57, 56.935396 }, { 58, 57.933278 }, { 0, 0.0 } 
	};

	const IsotopeData CoIsoData[] = { 
		{ 59, 58.933198 }, { 0, 0.0 } 
	};

	const IsotopeData NiIsoData[] = { 
		{ 58, 57.935346 }, { 60, 59.930788 }, { 61, 60.931053 }, { 62, 61.928346 }, 
		{ 64, 63.927968 }, { 0, 0.0 } 
	};

	const IsotopeData CuIsoData[] = { 
		{ 63, 62.929599 }, { 65, 64.927792 }, { 0, 0.0 } 
	};

	const IsotopeData ZnIsoData[] = { 
		{ 64, 63.929144 }, { 66, 65.926035 }, { 67, 66.927129 }, { 68, 67.924846 }, 
		{ 70, 69.925324 }, { 0, 0.0 } 
	};

	const IsotopeData GaIsoData[] = { 
		{ 69, 68.92558 }, { 71, 70.924703 }, { 0, 0.0 } 
	};

	const IsotopeData GeIsoData[] = { 
		{ 70, 69.924249 }, { 72, 71.922079 }, { 73, 72.923462 }, { 74, 73.921177 }, 
		{ 76, 75.921401 }, { 0, 0.0 } 
	};

	const IsotopeData AsIsoData[] = { 
		{ 75, 74.921594 }, { 0, 0.0 } 
	};

	const IsotopeData SeIsoData[] = { 
		{ 74, 73.922474 }, { 76, 75.919212 }, { 77, 76.919912 }, { 78, 77.917307 }, 
		{ 80, 79.916519 }, { 82, 81.916697 }, { 0, 0.0 } 
	};

	const IsotopeData BrIsoData[] = { 
		{ 79, 78.918336 }, { 81, 80.91629 }, { 0, 0.0 } 
	};

	const IsotopeData KrIsoData[] = { 
		{ 78, 77.9204 }, { 80, 79.91638 }, { 82, 81.91348 }, { 83, 82.914137 }, 
		{ 84, 83.911509 }, { 86, 85.910615 }, { 0, 0.0 } 
	};

	const IsotopeData RbIsoData[] = { 
		{ 85, 84.911794 }, { 87, 86.909186 }, { 0, 0.0 } 
	};

	const IsotopeData SrIsoData[] = { 
		{ 84, 83.913429 }, { 86, 85.909266 }, { 87, 86.908883 }, { 88, 87.905618 }, { 0, 0.0 } 
	};

	const IsotopeData YIsoData[] = { 
		{ 89, 88.905848 }, { 0, 0.0 } 
	};

	const IsotopeData ZrIsoData[] = { 
		{ 90, 89.904702 }, { 91, 90.905643 }, { 92, 91.905038 }, { 94, 93.906314 }, 
		{ 96, 95.908275 }, { 0, 0.0 } 
	};

	const IsotopeData NbIsoData[] = { 
		{ 93, 92.906376 }, { 0, 0.0 } 
	};

	const IsotopeData MoIsoData[] = { 
		{ 92, 91.906807 }, { 94, 93.905085 }, { 95, 94.905841 }, { 96, 95.904678 }, 
		{ 97, 96.90602 }, { 98, 97.905407 }, { 100, 99.90748 }, { 0, 0.0 } 
	};

	const IsotopeData RuIsoData[] = { 
		{ 96, 95.9076 }, { 98, 97.90529 }, { 99, 98.905939 }, { 100, 99.90422 }, 
		{ 101, 100.905582 }, { 102, 101.904349 }, { 104, 103.905429 }, { 0, 0.0 } 
	};

	const IsotopeData RhIsoData[] = { 
		{ 103, 102.905503 }, { 0, 0.0 } 
	};

	const IsotopeData PdIsoData[] = { 
		{ 102, 101.90562 }, { 104, 103.90403 }, { 105, 104.90508 }, { 106, 105.90348 }, 
		{ 108, 107.903894 }, { 110, 109.90516 }, { 0, 0.0 } 
	};

	const IsotopeData AgIsoData[] = { 
		{ 107, 106.90509 }, { 109, 108.904755 }, { 0, 0.0 } 
	};

	const IsotopeData CdIsoData[] = { 
		{ 106, 105.90546 }, { 108, 107.90418 }, { 110, 109.903005 }, { 111, 110.904182 }, 
		{ 112, 111.902758 }, { 113, 112.904402 }, { 114, 113.903358 }, { 116, 115.904756 }, { 0, 0.0 } 
	};

	const IsotopeData InIsoData[] = { 
		{ 113, 112.90406 }, { 115, 114.903876 }, { 0, 0.0 } 
	};

	const IsotopeData SnIsoData[] = { 
		{ 112, 111.90482 }, { 114, 113.902761 }, { 115, 114.903345 }, { 116, 115.901743 }, 
		{ 117, 116.902953 }, { 118, 117.901606 }, { 119, 118.903309 }, { 120, 119.902197 }, 
		{ 122, 121.90344 }, { 124, 123.905274 }, { 0, 0.0 } 
	};

	const IsotopeData SbIsoData[] = { 
		{ 121, 120.90382 }, { 123, 122.904215 }, { 0, 0.0 } 
	};

	const IsotopeData TeIsoData[] = { 
		{ 120, 119.90404 }, { 122, 121.903052}, { 123, 122.904271 }, { 124, 123.902818 }, 
		{ 125, 124.904429 }, { 126, 125.90331 }, { 128, 127.904464 }, { 130, 129.906229 }, { 0, 0.0 } 
	};

	const IsotopeData IIsoData[] = { 
		{ 127, 126.904475 }, { 0, 0.0 } 
	};

	const IsotopeData XeIsoData[] = { 
		{ 124, 123.905894 }, { 126, 125.90427 }, { 128, 127.903531 }, { 129, 128.90478 }, 
		{ 130, 129.903509 }, { 131, 130.905069 }, { 132, 131.904141 }, { 134, 133.9054 }, 
		{ 136, 135.90722 }, { 0, 0.0 } 
	};

	const IsotopeData CsIsoData[] = { 
		{ 133, 132.90544 }, { 0, 0.0 } 
	};
	
	const IsotopeData BaIsoData[] = { 
		{ 130, 129.90629 }, { 132, 131.90504 }, { 134, 133.90449 }, { 135, 134.90567 }, 
		{ 136, 135.90456 }, { 137, 136.90582 }, { 138, 137.90524 }, { 0, 0.0 } 
	};

	const IsotopeData LaIsoData[] = { 
		{ 138, 137.90711 }, { 139, 138.906347 }, { 0, 0.0 } 
	};

	const IsotopeData CeIsoData[] = { 
		{ 136, 135.90714 }, { 138, 137.90599 }, { 140, 139.905434 }, { 142, 141.909241 }, { 0, 0.0 } 
	};

	const IsotopeData PrIsoData[] = { 
		{ 141, 140.90768 }, { 0, 0.0 } 
	};

	const IsotopeData NdIsoData[] = { 
		{ 142, 141.907719 }, { 143, 142.90981 }, { 144, 143.910083 }, { 145, 144.91257 }, 
		{ 146, 145.913113 }, { 148, 147.916889 }, { 150, 149.920888 }, { 0, 0.0 } 
	};

	const IsotopeData SmIsoData[] = { 
		{ 144, 143.911997 }, { 147, 146.914894 }, { 148, 147.914819 }, { 149, 148.917181 }, 
		{ 150, 149.917273 }, { 152, 151.919729 }, { 154, 153.922206 }, { 0, 0.0 } 
	};

	const IsotopeData EuIsoData[] = { 
		{ 151, 150.919846 }, { 153, 152.921226 }, { 0, 0.0 } 
	};

	const IsotopeData GdIsoData[] = { 
		{ 152, 151.919788 }, { 154, 153.920862 }, { 155, 154.922619 }, { 156, 155.922119 }, 
		{ 157, 156.923957 }, { 158, 157.9241 }, { 160, 159.92705 }, { 0, 0.0 } 
	};

	const IsotopeData TbIsoData[] = { 
		{ 159, 158.925344 }, { 0, 0.0 } 
	};

	const IsotopeData DyIsoData[] = { 
		{ 156, 155.92428 }, { 158, 157.924403 }, { 160, 159.925194 }, { 161, 160.926931 }, 
		{ 162, 161.926796 }, { 163, 162.928729 }, { 164, 163.929173 }, { 0, 0.0 } 
	};

	const IsotopeData HoIsoData[] = { 
		{ 165, 164.93032 }, { 0, 0.0 } 
	};

	const IsotopeData ErIsoData[] = { 
		{ 162, 161.928776 }, { 164, 163.929199 }, { 166, 165.930292 }, { 167, 166.932047 }, 
		{ 168, 167.93237 }, { 170, 169.935463 }, { 0, 0.0 } 
	};

	const IsotopeData TmIsoData[] = { 
		{ 169, 168.934213 }, { 0, 0.0 } 
	};

	const IsotopeData YbIsoData[] = { 
		{ 168, 167.933897 }, { 170, 169.934761 }, { 171, 170.936325 }, { 172, 171.93638 }, 
		{ 173, 172.938209 }, { 174, 173.938861 }, { 176, 175.942565 }, { 0, 0.0 } 
	};

	const IsotopeData LuIsoData[] = { 
		{ 175, 174.940771 }, { 176, 175.94268 }, { 0, 0.0 } 
	};

	const IsotopeData HfIsoData[] = { 
		{ 174, 173.940042 }, { 176, 175.941404 }, { 177, 176.943219 }, { 178, 177.943697 }, 
		{ 179, 178.945813 }, { 180, 179.946548 }, { 0, 0.0 } 
	};

	const IsotopeData TaIsoData[] = { 
		{ 180, 179.947462 }, { 181, 180.947994 }, { 0, 0.0 } 
	};

	const IsotopeData WIsoData[] = { 
		{ 180, 179.946702 }, { 182, 181.948202 }, { 183, 182.950221 }, { 184, 183.950929 }, 
		{ 186, 185.954358 }, { 0, 0.0 } 
	};

	const IsotopeData ReIsoData[] = { 
		{ 185, 184.952952 }, { 187, 186.955747 }, { 0, 0.0 } 
	};

	const IsotopeData OsIsoData[] = { 
		{ 184, 183.952487 }, { 186, 185.953835 }, { 187, 186.955744 }, { 188, 187.955832 }, 
		{ 189, 188.958140 }, { 190, 189.958439 }, { 192, 191.961469 }, { 0, 0.0 } 
	};

	const IsotopeData IrIsoData[] = { 
		{191, 190.960585 }, { 193, 192.962916 }, { 0, 0.0 } 
	};

	const IsotopeData PtIsoData[] = { 
		{ 190, 189.959920 }, { 192, 191.961027 }, { 194, 193.962655 }, { 195, 194.964766 }, 
		{ 196, 195.964926 }, { 198, 197.967867 }, { 0, 0.0 } 
	};

	const IsotopeData AuIsoData[] = { 
		{ 197, 196.966543 }, { 0, 0.0 } 
	};

	const IsotopeData HgIsoData[] = { 
		{ 196, 195.965806 }, { 198, 197.966743 }, { 199, 198.968254 }, { 200, 199.968300 }, 
		{ 201, 200.970276 }, { 202, 201.970617 }, { 204, 203.973467 }, { 0, 0.0 } 
	};

	const IsotopeData TlIsoData[] = { 
		{ 203, 202.972320 }, { 205, 204.974401 }, { 0, 0.0 } 
	};

	const IsotopeData PbIsoData[] = { 
		{ 204, 203.973020 }, { 206, 205.974440 }, { 207, 206.975871 }, { 208, 207.976627 }, { 0, 0.0 } 
	};

	const IsotopeData BiIsoData[] = { 
		{ 209, 208.980373 }, { 0, 0.0 } 
	};

	const IsotopeData ThIsoData[] = { 
		{ 232, 232.038051 }, { 0, 0.0 } 
	};

	const IsotopeData UIsoData[] = { 
		{ 234, 234.040947 }, { 235, 235.043924 }, { 238, 239.050785 }, { 0, 0.0 } 
	};

	const AtomTypeData atomTypeData[] = {
		{ "",   "",             0,   0,          0,  false, false, { -1 },                      0,    { 0,    0,    0 },    0.0,  0         },
		{ "H",  "Hydrogen",     1,   1.00794,    1,  false, true,  { 1, -1 },                   1.2,  { 0.32, 0,    0 },    2.2,  HIsoData  },
		{ "He", "Helium",       4,   4.002602,   18, false, true,  { -1 },                      1.4,  { 0.46, 0,    0 },    0,    HeIsoData }, 
		{ "Li", "Lithium",      7,   6.941,      1,  true,  false, { 1, -1 },                   1.82, { 1.33, 1.24, 0 },    1.0,  LiIsoData }, 
		{ "Be", "Beryllium",    9,   9.012182,   2,  true,  false, { 2, -1 },                   1.7,  { 1.02, 0.90, 0.85 }, 1.5,  BeIsoData }, 
		{ "B",  "Boron",        11,  10.811,     13, true,  true,  { 3, -1 },                   2.08, { 0.85, 0.78, 0.73 }, 2.0,  BIsoData  }, 
		{ "C",  "Carbon",       12,  12.0107,    14, false, true,  { 4, 2, -1 },                1.7,  { 0.75, 0.67, 0.60 }, 2.5,  CIsoData  },
		{ "N",  "Nitrogen",     14,  14.0067,    15, false, true,  { 3, 2, 1, -1 },             1.55, { 0.71, 0.60, 0.54 }, 3.1,  NIsoData  }, 
		{ "O",  "Oxygen",       16,  15.9994,    16, false, true,  { 2, -1 },                   1.52, { 0.63, 0.57, 0.53 }, 3.5,  OIsoData  }, 
		{ "F",  "Fluorine",     19,  18.9984032, 17, false, true,  { 1, -1 },                   1.47, { 0.64, 0.59, 0.53 }, 4.1,  FIsoData  }, 
		{ "Ne", "Neon",         20,  20.1797,    18, false, true,  { -1 },                      1.54, { 0.67, 0.96, 0 },    0,    NeIsoData },
		{ "Na", "Sodium",       23,  22.98977,   1,  true,  false, { 1, -1 },                   2.27, { 1.55, 1.60, 0 },    1.0,  NaIsoData },
		{ "Mg", "Magnesium",    24,  24.3050,    2,  true,  false, { 2, -1 },                   1.73, { 1.39, 1.32, 1.27 }, 1.2,  MgIsoData },
		{ "Al", "Aluminium",    27,  26.981538,  13, true,  false, { 3, -1 },                   2.05, { 1.26, 1.13, 1.11 }, 1.5,  AlIsoData },
		{ "Si", "Silicon",      28,  28.0855,    14, true,  true,  { 4, 2, -1 },                2.1,  { 1.16, 1.07, 1.02 }, 1.7,  SiIsoData },
		{ "P",  "Phosphorus",   31,  30.973761,  15, false, true,  { 3, 5, -1 },                1.8,  { 1.11, 1.02, 0.94 }, 2.1,  PIsoData  },
		{ "S",  "Sulfur",       32,  32.065,     16, false, true,  { 2, 4, 6, -1 },             1.8,  { 1.03, 0.94, 0.95 }, 2.4,  SIsoData  },
		{ "Cl", "Chlorine",     35,  35.453,     17, false, true,  { 1, 3, 5, 7, 2, 4, -1 },    1.75, { 0.99, 0.95, 0.93 }, 2.8,  ClIsoData },
		{ "Ar", "Argon",        40,  39.948,     18, false, true,  { -1 },                      1.88, { 0.96, 1.07, 0.96 }, 0,    ArIsoData },
		{ "K",  "Potassium",    39,  39.0983,    1,  true,  false, { 1, -1 },                   2.75, { 1.96, 1.93, 0 },    0.9,  KIsoData  },  
		{ "Ca", "Calcium",      40,  40.078,     2,  true,  false, { 2, -1 },                   1.97, { 1.71, 1.47, 1.33 }, 1.0,  CaIsoData },  
		{ "Sc", "Scandium",     45,  44.95591,   3,  true,  false, { 3, -1 },                   1.7,  { 1.48, 1.16, 1.14 }, 1.2,  ScIsoData },
		{ "Ti", "Titanium",     48,  47.867,     4,  true,  false, { 2, 3, 4, -1 },             1.7,  { 1.36, 1.17, 1.08 }, 1.3,  TiIsoData },
		{ "V",  "Vanadium",     51,  50.9415,    5,  true,  false, { 2, 3, 4, 5, -1 },          1.7,  { 1.34, 1.12, 1.06 }, 1.5,  VIsoData  },
		{ "Cr", "Chromium",     52,  51.9961,    6,  true,  false, { 2, 3, 6, -1 },             1.7,  { 1.22, 1.11, 1.03 }, 1.6,  CrIsoData },
		{ "Mn", "Manganese",    55,  54.938049,  7,  true,  false, { 2, 4, 7, 3, 6, -1 },       1.7,  { 1.19, 1.05, 1.03 }, 1.6,  MnIsoData },
		{ "Fe", "Iron",         56,  55.845,     8,  true,  false, { 2, 3, 4, 6, -1 },          1.7,  { 1.16, 1.09, 1.02 }, 1.6,  FeIsoData },
		{ "Co", "Cobalt",       59,  58.9332,    9,  true,  false, { 2, 3, 4, -1 },             1.7,  { 1.11, 1.03, 0.96 }, 1.7,  CoIsoData },
		{ "Ni", "Nickel",       58,  58.6934,    10, true,  false, { 2, 1, 3, 4, -1 },          1.63, { 1.10, 1.01, 1.01 }, 1.8,  NiIsoData },
		{ "Cu", "Copper",       63,  63.546,     11, true,  false, { 1, 2, 3, -1 },             1.4,  { 1.12, 1.15, 1.20 }, 1.8,  CuIsoData },
		{ "Zn", "Zinc",         64,  65.409,     12, true,  false, { 2, -1 },                   1.39, { 1.18, 1.20, 0 },    1.7,  ZnIsoData },
		{ "Ga", "Gallium",      69,  69.723,     13, true,  false, { 3, 2, -1 },                1.87, { 1.24, 1.17, 1.21 }, 1.8,  GaIsoData },
		{ "Ge", "Germanium",    74,  72.64,      14, true,  true,  { 4, 2, -1 },                1.7,  { 1.21, 1.11, 1.14 }, 2.0,  GeIsoData },
		{ "As", "Arsenic",      75,  74.9216,    15, true,  true,  { 3, 5, 2, -1 },             1.85, { 1.21, 1.14, 1.06 }, 2.2,  AsIsoData },
		{ "Se", "Selenium",     80,  78.96,      16, true,  true,  { 2, 4, 6, -1 },             1.9,  { 1.16, 1.07, 1.07 }, 2.5,  SeIsoData },
		{ "Br", "Bromine",      79,  79.904,     17, false, true,  { 1, 5, 3, 4, -1 },          1.85, { 1.14, 1.09, 1.10 }, 2.7,  BrIsoData },
		{ "Kr", "Krypton",      84,  83.798,     18, false, true,  { -1 },                      2.02, { 1.17, 1.21, 1.08 }, 0,    KrIsoData },
		{ "Rb", "Rubidium",     85,  85.4678,    1,  true,  false, { 1, -1 },                   1.7,  { 2.10, 2.02, 0 },    0.9,  RbIsoData },
		{ "Sr", "Strontium",    88,  87.62,      2,  true,  false, { 2, -1 },                   1.7,  { 1.85, 1.57, 1.39 }, 1.0,  SrIsoData },
		{ "Y" , "Yttrium",      89,  88.90585,   3,  true,  false, { 3, -1 },                   1.7,  { 1.63, 1.30, 1.24 }, 1.1,  YIsoData  },
		{ "Zr", "Zirconium",    90,  91.224,     4,  true,  false, { 4, 2, 3, -1 },             1.7,  { 1.54, 1.27, 1.21 }, 1.2,  ZrIsoData },
		{ "Nb", "Niobium",      93,  92.90638,   5,  true,  false, { 3, 5, 2, 4, -1 },          1.7,  { 1.47, 1.25, 1.16 }, 1.2,  NbIsoData },
		{ "Mo", "Molybdenum",   98,  95.94,      6,  true,  false, { 3, 6, 2, 4, 5, -1 },       1.7,  { 1.38, 1.21, 1.13 }, 1.3,  MoIsoData },
		{ "Tc", "Technetium",   98,  98.0,       7,  true,  false, { 6, -1 },                   1.7,  { 1.28, 1.20, 1.10 }, 1.4,  0         },
		{ "Ru", "Ruthenium",    102, 101.07,     8,  true,  false, { 3, 4, 8, 2, 6, 7, -1 },    1.7,  { 1.25, 1.14, 1.03 }, 1.4,  RuIsoData },
		{ "Rh", "Rhodium",      103, 102.9055,   9,  true,  false, { 4, 2, 3, 6, -1 },          1.7,  { 1.25, 1.10, 1.06 }, 1.5,  RhIsoData },
		{ "Pd", "Palladium",    106, 106.42,     10, true,  false, { 2, 4, 6, -1 },             1.63, { 1.20, 1.17, 1.12 }, 1.4,  PdIsoData },
		{ "Ag", "Silver",       107, 107.8682,   11, true,  false, { 1, 2, 3, -1 },             1.72, { 1.28, 1.39, 1.37 }, 1.4,  AgIsoData },
		{ "Cd", "Cadmium",      114, 112.411,    12, true,  false, { 2, 1, -1 },                1.58, { 1.36, 1.44, 0 },    1.5,  CdIsoData },
		{ "In", "Indium",       115, 114.818,    13, true,  false, { 3, 1, 2, -1 },             1.93, { 1.42, 1.36, 1.46 }, 1.5,  InIsoData },
		{ "Sn", "Tin",          120, 118.710,    14, true,  false, { 4, 2, -1 },                2.17, { 1.40, 1.30, 1.32 }, 1.7,  SnIsoData },
		{ "Sb", "Antimony",     121, 121.760,    15, true,  true,  { 3, 5, 4, -1 },             2.2,  { 1.40, 1.33, 1.27 }, 1.8,  SbIsoData },
		{ "Te", "Tellurium",    130, 127.60,     16, true,  true,  { 2, 4, 6, -1 },             2.06, { 1.36, 1.28, 1.21 }, 2.0,  TeIsoData },
		{ "I" , "Iodine",       127, 126.90447,  17, false, true,  { 1, 5, 7, 3, 4, -1 },       1.98, { 1.33, 1.29, 1.25 }, 2.2,  IIsoData  },
		{ "Xe", "Xenon",        132, 131.293,    18, false, true,  { -1 },                      2.16, { 1.31, 1.35, 1.22 }, 0,    XeIsoData },
		{ "Cs", "Caesium",      133, 132.90545,  1,  true,  false, { 1, -1 },                   1.7,  { 2.32, 2.09, 0 },    0.9,  CsIsoData },
		{ "Ba", "Barium",       138, 137.327,    2,  true,  false, { 2, -1 },                   1.7,  { 1.96, 1.61, 1.49 }, 1.0,  BaIsoData },
		{ "La", "Lanthanum",    139, 138.9055,   3,  true,  false, { 3, -1 },                   1.7,  { 1.80, 1.39, 1.39 }, 1.1,  LaIsoData },
		{ "Ce", "Cerium",       140, 140.116,    3,  true,  false, { 3, 4, -1 },                1.7,  { 1.63, 1.37, 1.31 }, 1.1,  CeIsoData },
		{ "Pr", "Praseodymium", 141, 140.90765,  3,  true,  false, { 3, -1 },                   1.7,  { 1.76, 1.38, 1.28 }, 1.1,  PrIsoData },
		{ "Nd", "Neodymium",    144, 144.24,     3,  true,  false, { 3, 4, -1 },                1.7,  { 1.74, 1.37, 0 },    1.1,  NdIsoData },
		{ "Pm", "Promethium",   147, 145.0,      3,  true,  false, { 3, -1 },                   1.7,  { 1.73, 1.35, 0 },    1.1,  0         },
		{ "Sm", "Samarium",     152, 150.36,     3,  true,  false, { 3, 2, -1 },                1.7,  { 1.72, 1.34, 0 },    1.1,  SmIsoData },
		{ "Eu", "Europium",     153, 151.964,    3,  true,  false, { 3, 2, -1 },                1.7,  { 1.68, 1.34, 0 },    1.0,  EuIsoData },
		{ "Gd", "Gadolinium",   158, 157.25,     3,  true,  false, { 3, -1 },                   1.7,  { 1.69, 1.35, 1.32 }, 1.1,  GdIsoData },
		{ "Tb", "Terbium",      159, 158.92534,  3,  true,  false, { 3, 4, -1 },                1.7,  { 1.68, 1.35, 0 },    1.1,  TbIsoData },
		{ "Dy", "Dysprosium",   164, 162.50,     3,  true,  false, { 3, -1 },                   1.7,  { 1.67, 1.33, 0 },    1.1,  DyIsoData },
		{ "Ho", "Holmium",      165, 164.93032,  3,  true,  false, { 3, -1 },                   1.7,  { 1.66, 1.33, 0 },    1.1,  HoIsoData },
		{ "Er", "Erbium",       166, 167.259,    3,  true,  false, { 3, -1 },                   1.7,  { 1.65, 1.33, 0 },    1.1,  ErIsoData },
		{ "Tm", "Thulium",      169, 168.93421,  3,  true,  false, { 3, 2, -1 },                1.7,  { 1.64, 1.31, 0 },    1.1,  TmIsoData },
		{ "Yb", "Ytterbium",    174, 173.04,     3,  true,  false, { 3, 2, -1 },                1.7,  { 1.70, 1.29, 0 },    1.1,  YbIsoData },
		{ "Lu", "Lutetium",     175, 174.967,    3,  true,  false, { 3, -1 },                   1.7,  { 1.62, 1.31, 1.31 }, 1.1,  LuIsoData },
		{ "Hf", "Hafnium",      178, 178.49,     4,  true,  false, { 4, -1 },                   1.7,  { 1.52, 1.28, 1.22 }, 1.2,  HfIsoData },
		{ "Ta", "Tantalum",     181, 180.9479,   5,  true,  false, { 5, 3, 4, -1 },             1.7,  { 1.46, 1.26, 1.19 }, 1.3,  TaIsoData },
		{ "W" , "Tungsten",     184, 183.84,     6,  true,  false, { 6, 2, 3, 4, 5, -1 },       1.7,  { 1.37, 1.20, 1.15 }, 1.4,  WIsoData  },
		{ "Re", "Rhenium",      187, 186.207,    7,  true,  false, { 2, 4, 6, 7, 1, 3, 5, -1 }, 1.7,  { 1.31, 1.19, 1.10 }, 1.5,  ReIsoData },
		{ "Os", "Osmium",       192, 190.23,     8,  true,  false, { 3, 4, 6, 8, 2, -1 },       1.7,  { 1.29, 1.16, 1.09 }, 1.5,  OsIsoData },
		{ "Ir", "Iridium",      193, 192.217,    9,  true,  false, { 3, 4, 6, 1, 2, -1 },       1.7,  { 1.22, 1.15, 1.07 }, 1.6,  IrIsoData },
		{ "Pt", "Platinum",     195, 195.078,    10, true,  false, { 2, 4, 6, 1, 3, -1 },       1.75, { 1.23, 1.12, 1.10 }, 1.4,  PtIsoData },
		{ "Au", "Gold",         197, 196.96655,  11, true,  false, { 1, 3, 2, -1 },             1.44, { 1.24, 1.21, 1.23 }, 1.4,  AuIsoData },
		{ "Hg", "Mercury",      202, 200.59,     12, true,  false, { 1, 2, -1 },                1.49, { 1.33, 1.42, 0 },    1.4,  HgIsoData },
		{ "Tl", "Thallium",     205, 204.3833,   13, true,  false, { 1, 3, 2, -1 },             1.69, { 1.44, 1.42, 1.50 }, 1.4,  TlIsoData },
		{ "Pb", "Lead",         208, 207.2,      14, true,  false, { 2, 4, -1 },                2.02, { 1.44, 1.35, 1.37 }, 1.6,  PbIsoData },
		{ "Bi", "Bismuth",      209, 208.98038,  15, true,  false, { 3, 2, 4, 5, -1 },          1.7,  { 1.51, 1.41, 1.35 }, 1.7,  BiIsoData },
		{ "Po", "Polonium",     209, 209.0,      16, true,  true,  { 2, 4, 6, -1 },             1.7,  { 1.45, 1.35, 1.29 }, 1.8,  0         },
		{ "At", "Astatine",     219, 210.0,      17, true,  true,  { -1 },                      1.7,  { 1.47, 1.38, 1.38 }, 2.0,  0         },
		{ "Rn", "Radon",        222, 222.0,      18, false, true,  { -1 },                      1.7,  { 1.42, 1.45, 1.33 }, 0,    0         },
		{ "Fr", "Francium",     223, 223.0,      1,  true,  false, { -1 },                      1.7,  { 2.23, 2.18, 0 },    0.9,  0         },
		{ "Ra", "Radium",       226, 226.0,      2,  true,  false, { 2, -1 },                   1.7,  { 2.01, 1.73, 1.59 }, 1.0,  0         },
		{ "Ac", "Actinium",     227, 227.0,      3,  true,  false, { 3, -1 },                   1.7,  { 1.86, 1.53, 1.40 }, 1.0,  0         },
		{ "Th", "Thorium",      232, 232.0381,   3,  true,  false, { 4, -1 },                   1.7,  { 1.75, 1.43, 1.36 }, 1.1,  ThIsoData },
		{ "Pa", "Protactinium", 231, 231.03588,  3,  true,  false, { 5, -1 },                   1.7,  { 1.69, 1.38, 1.29 }, 1.1,  0         },
		{ "U",  "Uranium",      298, 238.02891,  3,  true,  false, { 3, 4, 6, 2, 5, -1 },       1.86, { 1.70, 1.34, 1.18 }, 1.2,  UIsoData  },
		{ "Np", "Neptunium",    237, 237.0,      3,  true,  false, { -1 },                      1.7,  { 1.71, 1.36, 1.16 }, 1.2,  0         },
		{ "Pu", "Plutonium",    244, 244.0,      3,  true,  false, { -1 },                      1.7,  { 1.72, 1.35, 0 },    1.2,  0         },
		{ "Am", "Americium",    243, 243.0,      3,  true,  false, { -1 },                      1.7,  { 1.66, 1.35, 0 },    1.2,  0         },
		{ "Cm", "Curium",       247, 247.0,      3,  true,  false, { -1 },                      1.7,  { 1.66, 1.36, 0 },    1.2,  0         },
		{ "Bk", "Berkelium",    247, 247.0,      3,  true,  false, { -1 },                      1.7,  { 1.68, 1.39, 0 },    1.2,  0         },
		{ "Cf", "Californium",  251, 251.0,      3,  true,  false, { -1 },                      1.7,  { 1.68, 1.40, 0 },    1.2,  0         },
		{ "Es", "Einsteinium",  252, 252.0,      3,  true,  false, { -1 },                      1.7,  { 1.65, 1.40, 0 },    1.2,  0         },
		{ "Fm", "Fermium",      257, 257.0,      3,  true,  false, { -1 },                      1.7,  { 1.67, 0,    0 },    1.2,  0         },
		{ "Md", "Mendelevium",  258, 258.0,      3,  true,  false, { -1 },                      1.7,  { 1.73, 1.39, 0 },    1.2,  0         },
		{ "No", "Nobelium",     259, 259.0,      3,  true,  false, { -1 },                      1.7,  { 1.76, 0,    0 },    0,    0         },
		{ "Lr", "Lawrencium",   262, 262.0,      3,  true,  false, { -1 },                      1.7,  { 1.61, 1.41, 0 },    0,    0         },
		{ "Rf", "Rutherfordium",261, 261.0,      4,  true,  false, { -1 },                      1.7,  { 1.57, 1.40, 1.31 }, 0,    0         },
		{ "Db", "Dubnium",      262, 262.0,      5,  true,  false, { -1 },                      1.7,  { 1.49, 1.36, 1.26 }, 0,    0         },
		{ "Sg", "Seaborgium",   266, 266.0,      6,  true,  false, { -1 },                      1.7,  { 1.43, 1.28, 1.21 }, 0,    0         },
		{ "Bh", "Bohrium",      264, 264.0,      7,  true,  false, { -1 },                      1.7,  { 1.41, 1.28, 1.19 }, 0,    0         },
		{ "Hs", "Hassium",      269, 277.0,      8,  true,  false, { -1 },                      1.7,  { 1.34, 1.25, 1.18 }, 0,    0         },
		{ "Mt", "Meitnerium",   268, 268.0,      9,  true,  false, { -1 },                      1.7,  { 1.29, 1.25, 1.13 }, 0,    0         },
		{ "A",  "",             0,   0,          0,  false, false, { -1 },                      0,    { 0,    0,    0 },    0,    0         },
		{ "AH", "",             0,   0,          0,  false, false, { -1 },                      0,    { 0,    0,    0 },    0,    0         },
		{ "Q",  "",             0,   0,          0,  false, false, { -1 },                      0,    { 0,    0,    0 },    0,    0         },
		{ "QH", "",             0,   0,          0,  false, false, { -1 },                      0,    { 0,    0,    0 },    0,    0         },
		{ "M",  "",             0,   0,          0,  false, false, { -1 },                      0,    { 0,    0,    0 },    0,    0         },
		{ "MH", "",             0,   0,          0,  false, false, { -1 },                      0,    { 0,    0,    0 },    0,    0         },
		{ "X",  "",             0,   0,          0,  false, false, { -1 },                      0,    { 0,    0,    0 },    0,    0         },
		{ "XH", "",             0,   0,          0,  false, false, { -1 },                      0,    { 0,    0,    0 },    0,    0         },
		{ "*",  "",             0,   0,          0,  false, false, { -1 },                      0,    { 0,    0,    0 },    0,    0         },
	};

	inline const AtomTypeData* getAtomTypeData(unsigned int type)
	{
		return (type >= sizeof(atomTypeData) / sizeof(AtomTypeData) ? atomTypeData : atomTypeData + type);
	}

	typedef boost::unordered_map<std::string, unsigned int> SymbolToTypeMap;

	SymbolToTypeMap symbolToTypeMap;

	struct InitSymbolToTypeMap 
	{

		InitSymbolToTypeMap() {
			for (unsigned int i = 0; i < sizeof(atomTypeData) / sizeof(AtomTypeData); i++)
				symbolToTypeMap[atomTypeData[i].symbol] = i;
		}

	} initSymbolToTypeMap;
}


using namespace CDPL;


const std::string& Chem::getAtomTypeSymbol(unsigned int type, std::size_t iso) 
{
	static const std::string DEUTERIUM_SYM = "D";
	static const std::string TRITIUM_SYM   = "T";

	if (type == AtomType::H) {
		
		switch (iso) {

		case 2:
			return DEUTERIUM_SYM;

		case 3:
			return TRITIUM_SYM;
		}
	}

	return getAtomTypeData(type)->symbol;
}

const std::string& Chem::getElementName(unsigned int type, std::size_t iso) 
{
	static const std::string DEUTERIUM_NAME = "Deuterium";
	static const std::string TRITIUM_NAME = "Tritium";

	if (type == AtomType::H) {
		
		switch (iso) {

		case 2:
			return DEUTERIUM_NAME;

		case 3:
			return TRITIUM_NAME;
		}
	}

	return getAtomTypeData(type)->name;
}

unsigned int Chem::getAtomType(const std::string& sym) 
{
	static const std::string DEUTERIUM_SYM = "D";
	static const std::string TRITIUM_SYM   = "T";

	if (sym == DEUTERIUM_SYM || sym == TRITIUM_SYM)
		return 1;

	SymbolToTypeMap::const_iterator it = symbolToTypeMap.find(sym);

	if (it == symbolToTypeMap.end())
		return AtomType::UNKNOWN;

	return (*it).second;
}

std::size_t Chem::getMostAbundantIsotope(unsigned int type) 
{
	 return getAtomTypeData(type)->mostAbundantIso;
}

std::size_t Chem::getIUPACGroup(unsigned int type) 
{
	 return getAtomTypeData(type)->iupacGroup;
}

double Chem::getAtomicWeight(unsigned int type, std::size_t iso) 
{
	const AtomTypeData* data = getAtomTypeData(type);

	if (iso == 0)
		return data->averageWeight;

	if (!data->isotopeData)
		return iso;

	for (const IsotopeData* item = data->isotopeData; item->isotope > 0; item++)
		if (item->isotope == iso)
			return item->weight;

	return iso;
}

const int* Chem::getValenceStates(unsigned int type)
{
	return getAtomTypeData(type)->valenceStates;
}

std::size_t Chem::getNumValenceElectrons(unsigned int type)
{	
	std::size_t iupac_group = getAtomTypeData(type)->iupacGroup;

	return (iupac_group < 3 ? iupac_group : iupac_group > 12 ? iupac_group - 10 : iupac_group);
}

double Chem::getVdWRadius(unsigned int type) 
{
	return getAtomTypeData(type)->vdwRadius;
}

double Chem::getCovalentRadius(unsigned int type, std::size_t order) 
{
	if (order < 1 || order > 3)
		return 0.0;

	return getAtomTypeData(type)->covalentRadii[order - 1];
}

double Chem::getAllredRochowElectronegativity(unsigned int type) 
{
	return getAtomTypeData(type)->allredRochowEneg;
}

bool Chem::isChemicalElement(unsigned int type) 
{
	return (type > 0 && type <= AtomType::MAX_ATOMIC_NO);
}

bool Chem::isMainGroupElement(unsigned int type) 
{
	std::size_t iupac_group = getAtomTypeData(type)->iupacGroup;

	return (iupac_group > 0 && (iupac_group < 3 || iupac_group > 12));
}

bool Chem::isTransitionMetal(unsigned int type) 
{
	std::size_t iupac_group = getAtomTypeData(type)->iupacGroup;

	return (iupac_group >= 3 && iupac_group <= 12);
}

bool Chem::isMetal(unsigned int type) 
{
	return getAtomTypeData(type)->isMetal;
}

bool Chem::isSemiMetal(unsigned int type) 
{
	const AtomTypeData* data = getAtomTypeData(type);

	return (data->isMetal && data->isNonMetal);
}

bool Chem::isNonMetal(unsigned int type) 
{
	return getAtomTypeData(type)->isNonMetal;
}

bool Chem::isHalogen(unsigned int type) 
{
	return (getAtomTypeData(type)->iupacGroup == 17);
}

bool Chem::isNobleGas(unsigned int type) 
{
	return (getAtomTypeData(type)->iupacGroup == 18);
}
