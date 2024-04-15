/* 
 * StructureGridView2DTest.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; see the file COPYING. If not, write to
 * the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */


#include <string>
#include <fstream>

#include <boost/test/auto_unit_test.hpp>

#include "CDPL/Config.hpp"
#include "CDPL/Vis/StructureGridView2D.hpp"
#include "CDPL/Vis/Rectangle2D.hpp"
#include "CDPL/Vis/Color.hpp"
#include "CDPL/Vis/Pen.hpp"
#include "CDPL/Vis/Brush.hpp"
#include "CDPL/Vis/Font.hpp"
#include "CDPL/Vis/DataFormat.hpp"
#include "CDPL/Chem/BasicMolecule.hpp"
#include "CDPL/Chem/MoleculeReader.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"

#include "Utilities.hpp"

#ifdef HAVE_CAIRO 
# ifdef HAVE_CAIRO_PNG_SUPPORT

# include <cairo.h>

# include "CDPL/Vis/CairoPointer.hpp"
# include "CDPL/Vis/CairoRenderer2D.hpp"
# include "CDPL/Vis/CairoFontMetrics.hpp"

# endif // HAVE_CAIRO_PNG_SUPPORT
#endif // HAVE_CAIRO


BOOST_AUTO_TEST_CASE(StructureGridView2DTest)
{
    using namespace CDPL;
    using namespace Vis;
    using namespace Chem;

    StructureGridView2D view;

// TODO
    
#ifdef HAVE_CAIRO 
# ifdef HAVE_CAIRO_PNG_SUPPORT

    BasicMolecule mol;
    MoleculeReader mol_reader(std::string(std::getenv("CDPKIT_TEST_DATA_DIR")) + "/1ke7_ligands.sdf");

    for (std::size_t i = 0; i < 3; i++)
        for (std::size_t j = 0; j < 3; j++) {
            BOOST_CHECK(mol_reader.read(mol));

            initSubstructureSearchTarget(mol, false);

            view(i, j).setStructure(mol);
        }
    
    BOOST_CHECK(view.write("StructureGridView2DTest_1.png"));
    BOOST_CHECK(view.write("StructureGridView2DTest_1.pdf"));
    BOOST_CHECK(view.write("StructureGridView2DTest_1.ps"));
    BOOST_CHECK(view.write("StructureGridView2DTest_1.svg"));
      
# endif // HAVE_CAIRO_PNG_SUPPORT
#endif // HAVE_CAIRO
}
