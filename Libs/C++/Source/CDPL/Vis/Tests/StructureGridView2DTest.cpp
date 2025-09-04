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
#include "CDPL/Vis/DefaultAtomColorTable.hpp"
#include "CDPL/Vis/ControlParameterFunctions.hpp"
#include "CDPL/Chem/BasicMolecule.hpp"
#include "CDPL/Chem/MoleculeReader.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Base/Exceptions.hpp"


BOOST_AUTO_TEST_CASE(StructureGridView2DTest)
{
    using namespace CDPL;
    using namespace Vis;
    using namespace Chem;

    StructureGridView2D view;
    BasicMolecule mol;
    MoleculeReader mol_reader(std::string(std::getenv("CDPKIT_TEST_DATA_DIR")) + "/ChEMBLStandardizerTestData.sdf");

    for (std::size_t i = 0; i < 3; i++) {
        for (std::size_t j = 0; j < 3; j++) {
            BOOST_CHECK(mol_reader.read(mol));

            initSubstructureSearchTarget(mol, false);
            calcTopologicalDistanceMatrix(mol, false);
            
            BOOST_CHECK(!view(i, j).hasStructure());

            view(i, j).setStructure(mol);

            BOOST_CHECK(view(i, j).hasStructure());
            BOOST_CHECK(!view(i, j).hasText());
            BOOST_CHECK(!view(i, j).hasAnyText());

            view(i, j).setText("#" + std::to_string(i * 3 + j + 1));

            BOOST_CHECK(view(i, j).hasText());
            BOOST_CHECK(view(i, j).hasAnyText());
        }
    }

    Vis::setAtomColorTableParameter(view(1, 1), ColorTable::SharedPointer(new DefaultAtomColorTable()));
    Vis::setGridViewTextFontParameter(view(2, 2), Font("Serif", 12.0, true));
    Vis::setGridViewTextColorParameter(view(0, 0), Color::RED);
    Vis::setBackgroundBrushParameter(view, Brush(Color::GRAY, Brush::DIAG_CROSS_PATTERN));

//---

    BOOST_CHECK(view.getCellWidth() == StructureGridView2D::DEF_CELL_WIDTH);
    BOOST_CHECK(view.getCellHeight() == StructureGridView2D::DEF_CELL_HEIGHT);
    BOOST_CHECK(view.getNumRows() == 3);
    BOOST_CHECK(view.getNumColumns() == 3);
    
//---

#ifdef HAVE_CAIRO
# ifdef HAVE_CAIRO_PNG_SUPPORT
    BOOST_CHECK(view.write("StructureGridView2DTest_01.png"));
# endif

# ifdef HAVE_CAIRO_PDF_SUPPORT
    BOOST_CHECK(view.write("StructureGridView2DTest_01.pdf", "pDf"));
# endif

# ifdef HAVE_CAIRO_PS_SUPPORT
    BOOST_CHECK(view.write("StructureGridView2DTest_01.ps", DataFormat::PS));
# endif

# ifdef HAVE_CAIRO_SVG_SUPPORT
    std::ofstream ofs1("StructureGridView2DTest_01.svg", std::ostream::out | std::ostream::trunc);

    BOOST_CHECK(view.write(ofs1, "Svg"));
# endif

# ifdef HAVE_CAIRO_PNG_SUPPORT

    view.resize(4, 4);

    BOOST_CHECK(view.getNumRows() == 4);
    BOOST_CHECK(view.getNumColumns() == 4);
    BOOST_CHECK(!view(3, 3).hasStructure());
    BOOST_CHECK(!view(3, 3).hasAnyText());

    BOOST_CHECK(view.write("StructureGridView2DTest_02_resize_4x4.png"));

//---

    view(0, 3).setText("<b>LEFT | TOP</i>", Alignment::LEFT | Alignment::TOP);

    BOOST_CHECK(view(0, 3).hasAnyText());
    BOOST_CHECK(!view(0, 3).hasText());
    BOOST_CHECK(!view(0, 3).hasText(Alignment::H_CENTER | Alignment::TOP));
    BOOST_CHECK(view(0, 3).hasText(Alignment::LEFT | Alignment::TOP));
    BOOST_CHECK(!view(0, 3).hasStructure());
    
    view(1, 3).setText("<i>H_CENTER | TOP</i>", Alignment::H_CENTER | Alignment::TOP);
    view(2, 3).setText("<u>RIGHT | TOP</u>", Alignment::RIGHT | Alignment::TOP);
    view(0, 3).setText("LEFT | <sup>V</>_<color g='1'>CENTER</>", Alignment::LEFT | Alignment::V_CENTER);
    view(1, 3).setText("<o>H_CENTER</> | V_CENTER", Alignment::H_CENTER | Alignment::V_CENTER);
    view(2, 3).setText("<s>RIGHT |</> V_CENTER", Alignment::RIGHT | Alignment::V_CENTER);
    view(0, 3).setText("LEFT | B<sub>O</>TTOM", Alignment::LEFT | Alignment::BOTTOM);
    view(1, 3).setText("<color b='1'>H_CENTER | BOTTOM</>", Alignment::H_CENTER | Alignment::BOTTOM);

    BOOST_CHECK(view(1, 3).hasAnyText());
    BOOST_CHECK(view(1, 3).hasText());
    BOOST_CHECK(view(1, 3).hasText(Alignment::H_CENTER | Alignment::BOTTOM));
    BOOST_CHECK(!view(1, 3).hasText(Alignment::LEFT | Alignment::TOP));
    BOOST_CHECK(!view(1, 3).hasStructure());

    view(2, 3).setText("RIGHT | BOTTOM", Alignment::RIGHT | Alignment::BOTTOM);

    BOOST_CHECK_THROW(view(2, 3).setText("", Alignment::RIGHT), Base::ValueError);
    BOOST_CHECK_THROW(view(2, 3).setText("", Alignment::TOP), Base::ValueError);
    BOOST_CHECK_THROW(view(2, 3).setText("<dsf>", Alignment::NONE), Base::ValueError);
    BOOST_CHECK_THROW(view(2, 3).setText("<dsf>", Alignment::RIGHT | Alignment::BOTTOM), Base::ValueError);

    BOOST_CHECK(view(2, 3).getText(Alignment::RIGHT | Alignment::BOTTOM) == "RIGHT | BOTTOM");

    std::ofstream ofs2("StructureGridView2DTest_03_setText_var_cells.png", std::ostream::out | std::ostream::binary | std::ostream::trunc);
     
    BOOST_CHECK(view.write(ofs2, DataFormat::PNG));
    
//---

    BOOST_CHECK(view(2, 0).hasStructure());

    view(2, 0).clearStructure();

    BOOST_CHECK(!view(2, 0).hasStructure());

    BOOST_CHECK(view.write("StructureGridView2DTest_04_clearStructure@2_0.png"));

//---

    BOOST_CHECK(view(2, 0).hasText());
    BOOST_CHECK(view(2, 0).hasAnyText());

    view(2, 0).clearText();

    BOOST_CHECK(!view(2, 0).hasText());
    BOOST_CHECK(!view(2, 0).hasAnyText());

    BOOST_CHECK(view.write("StructureGridView2DTest_05_clearText@2_0.png"));

//---

    BOOST_CHECK(!view(2, 3).hasText());
    BOOST_CHECK(view(2, 3).hasText(Alignment::RIGHT | Alignment::V_CENTER));
    BOOST_CHECK(view(2, 3).hasAnyText());

    view(2, 3).clearText();

    BOOST_CHECK(!view(2, 3).hasText());
    BOOST_CHECK(view(2, 3).hasText(Alignment::RIGHT | Alignment::V_CENTER));
    BOOST_CHECK(view(2, 3).hasAnyText());

    view(2, 3).clearText(Alignment::RIGHT | Alignment::V_CENTER);

    BOOST_CHECK(!view(2, 3).hasText());
    BOOST_CHECK(!view(2, 3).hasText(Alignment::RIGHT | Alignment::V_CENTER));
    BOOST_CHECK(view(2, 3).hasAnyText());

    BOOST_CHECK(view.write("StructureGridView2DTest_06_clearText_R_VC@2_3.png"));

//---

    BOOST_CHECK(!view(2, 3).hasText());
    BOOST_CHECK(view(2, 3).hasText(Alignment::RIGHT | Alignment::TOP));
    BOOST_CHECK(view(2, 3).hasAnyText());

    view(2, 3).clearAllText();

    BOOST_CHECK(!view(2, 3).hasText(Alignment::RIGHT | Alignment::TOP));
    BOOST_CHECK(!view(2, 3).hasAnyText());

    BOOST_CHECK(view.write("StructureGridView2DTest_07_clearAllText@2_3.png"));

//---

    Rectangle2D bbox;

    view.getModelBounds(bbox);

    BOOST_CHECK(bbox.getWidth() == 4 * StructureGridView2D::DEF_CELL_WIDTH);
    BOOST_CHECK(bbox.getHeight() == 4 * StructureGridView2D::DEF_CELL_HEIGHT);

    setGridViewBorderPenParameter(view, Pen(Color::BLUE, 2.0));
                
    BOOST_CHECK(view.write("StructureGridView2DTest_08_border_pen.png"));

    view.getModelBounds(bbox);

    BOOST_CHECK(bbox.getWidth() == 4 * StructureGridView2D::DEF_CELL_WIDTH + 2.0);
    BOOST_CHECK(bbox.getHeight() == 4 * StructureGridView2D::DEF_CELL_HEIGHT + 2.0);

//---

    setGridViewRowSeparatorPenParameter(view, Pen(Color::GREEN, 3.0, Pen::DASH_LINE));
                
    BOOST_CHECK(view.write("StructureGridView2DTest_09_row_sep_pen.png"));

    view.getModelBounds(bbox);

    BOOST_CHECK(bbox.getWidth() == 4 * StructureGridView2D::DEF_CELL_WIDTH + 3.0);
    BOOST_CHECK(bbox.getHeight() == 4 * StructureGridView2D::DEF_CELL_HEIGHT + 2.0);

//---

    setGridViewColumnSeparatorPenParameter(view, Pen(Color::RED, 3.0, Pen::DOT_LINE));
                
    BOOST_CHECK(view.write("StructureGridView2DTest_10_col_sep_pen.png"));

    view.getModelBounds(bbox);

    BOOST_CHECK(bbox.getWidth() == 4 * StructureGridView2D::DEF_CELL_WIDTH + 3.0);
    BOOST_CHECK(bbox.getHeight() == 4 * StructureGridView2D::DEF_CELL_HEIGHT + 3.0);

//---

    setGridViewMarginParameter(view, 10.0);
                
    BOOST_CHECK(view.write("StructureGridView2DTest_11_margin_10.png"));

    view.getModelBounds(bbox);

    BOOST_CHECK(bbox.getWidth() == 4 * StructureGridView2D::DEF_CELL_WIDTH + 3.0 + 20.0);
    BOOST_CHECK(bbox.getHeight() == 4 * StructureGridView2D::DEF_CELL_HEIGHT + 3.0 + 20.0);

//---

    setGridViewCellPaddingParameter(view, 10.0);
                
    BOOST_CHECK(view.write("StructureGridView2DTest_12_cell_padding_10.png"));

    view.getModelBounds(bbox);

    BOOST_CHECK(bbox.getWidth() == 4 * StructureGridView2D::DEF_CELL_WIDTH + 3.0 + 20.0);
    BOOST_CHECK(bbox.getHeight() == 4 * StructureGridView2D::DEF_CELL_HEIGHT + 3.0 + 20.0);

//---

    setGridViewTextFontParameter(view, Font("Serif", 12.0));
                
    BOOST_CHECK(view.write("StructureGridView2DTest_13_font_serif_12.png"));

    view.getModelBounds(bbox);

    BOOST_CHECK(bbox.getWidth() == 4 * StructureGridView2D::DEF_CELL_WIDTH + 3.0 + 20.0);
    BOOST_CHECK(bbox.getHeight() == 4 * StructureGridView2D::DEF_CELL_HEIGHT + 3.0 + 20.0);

//---

    setGridViewTextColorParameter(view, Color::MAGENTA);
                
    BOOST_CHECK(view.write("StructureGridView2DTest_14_text_color_magenta.png"));

    view.getModelBounds(bbox);

    BOOST_CHECK(bbox.getWidth() == 4 * StructureGridView2D::DEF_CELL_WIDTH + 3.0 + 20.0);
    BOOST_CHECK(bbox.getHeight() == 4 * StructureGridView2D::DEF_CELL_HEIGHT + 3.0 + 20.0);

//---

    BOOST_CHECK(!view(1, 0).hasText(Alignment::TOP | Alignment::H_CENTER));
    
    view(1, 0).setText("TOP <color r='1'><b><s>TEXT</></></>", Alignment::TOP | Alignment::H_CENTER);

    BOOST_CHECK(view(1, 0).hasText(Alignment::TOP | Alignment::H_CENTER));
    
    BOOST_CHECK(view.write("StructureGridView2DTest_15_setText_T_HC@1_0.png"));

//---

    setGridViewTextFontParameter(view(1, 0), Font("", 10.0));
    
    BOOST_CHECK(view.write("StructureGridView2DTest_16_set_def_font@1_0.png"));

//---

    setOutputScalingFactorParameter(view, 2.0);
                
    BOOST_CHECK(view.write("StructureGridView2DTest_17_output_scaling_fact_2.png"));

    view.getModelBounds(bbox);

    BOOST_CHECK(bbox.getWidth() == 4 * StructureGridView2D::DEF_CELL_WIDTH + 3.0 + 20.0);
    BOOST_CHECK(bbox.getHeight() == 4 * StructureGridView2D::DEF_CELL_HEIGHT + 3.0 + 20.0);

//---

    view.setCellSize(200.0, 200.0);

    BOOST_CHECK(view.getCellWidth() == 200.0);
    BOOST_CHECK(view.getCellHeight() == 200.0);
    
    BOOST_CHECK(view.write("StructureGridView2DTest_18_setCellSize_200x200.png"));

    view.getModelBounds(bbox);

    BOOST_CHECK(bbox.getWidth() == 4 * 200.0 + 3.0 + 20.0);
    BOOST_CHECK(bbox.getHeight() == 4 * 200.0 + 3.0 + 20.0);

//---

    BOOST_CHECK(!view(1, 1).hasText(Alignment::TOP | Alignment::H_CENTER));
             
    view(1, 1) = view(1, 0);

    BOOST_CHECK(view(1, 0).hasText(Alignment::TOP | Alignment::H_CENTER));
    
    BOOST_CHECK(view.write("StructureGridView2DTest_19_cell_1_1_ass_1_0.png"));
    
//---

    StructureGridView2D view2(view);
     
    view2.getModelBounds(bbox);

    BOOST_CHECK(bbox.getWidth() == 4 * 200.0 + 3.0 + 20.0);
    BOOST_CHECK(bbox.getHeight() == 4 * 200.0 + 3.0 + 20.0);
    
    BOOST_CHECK(view2.write("StructureGridView2DTest_20_copy_ctor.png"));

//---

    StructureGridView2D view3;
     
    view3.getModelBounds(bbox);

    BOOST_CHECK(bbox.getWidth() == 0.0);
    BOOST_CHECK(bbox.getHeight() == 0.0);

    BOOST_CHECK(view3.getNumRows() == 0);
    BOOST_CHECK(view3.getNumColumns() == 0);

    BOOST_CHECK(view3.getCellWidth() == StructureGridView2D::DEF_CELL_WIDTH);
    BOOST_CHECK(view3.getCellHeight() == StructureGridView2D::DEF_CELL_HEIGHT);
    
    view3 = view;

    view3.getModelBounds(bbox);

    BOOST_CHECK(bbox.getWidth() == 4 * 200.0 + 3.0 + 20.0);
    BOOST_CHECK(bbox.getHeight() == 4 * 200.0 + 3.0 + 20.0);

    BOOST_CHECK(view3.getNumRows() == 4);
    BOOST_CHECK(view3.getNumColumns() == 4);
    
    BOOST_CHECK(view3.write("StructureGridView2DTest_21_copy_ass.png"));

//---

    view3.resize(3, 2);

    view3.getModelBounds(bbox);

    BOOST_CHECK(bbox.getWidth() == 2 * 200.0 + 3.0 + 20.0);
    BOOST_CHECK(bbox.getHeight() == 3 * 200.0 + 3.0 + 20.0);

    BOOST_CHECK(view3.getNumRows() == 3);
    BOOST_CHECK(view3.getNumColumns() == 2);
    
    BOOST_CHECK(view3.write("StructureGridView2DTest_22_resize_3x2.png"));

//---

    view3.resize(4, 3);

    view3.getModelBounds(bbox);

    BOOST_CHECK(bbox.getWidth() == 3 * 200.0 + 3.0 + 20.0);
    BOOST_CHECK(bbox.getHeight() == 4 * 200.0 + 3.0 + 20.0);

    BOOST_CHECK(view3.getNumRows() == 4);
    BOOST_CHECK(view3.getNumColumns() == 3);
    
    BOOST_CHECK(view3.write("StructureGridView2DTest_23_resize_4x3.png"));

//---

    view3.clearAllText();

    view3.getModelBounds(bbox);

    BOOST_CHECK(bbox.getWidth() == 3 * 200.0 + 3.0 + 20.0);
    BOOST_CHECK(bbox.getHeight() == 4 * 200.0 + 3.0 + 20.0);

    BOOST_CHECK(view3.getNumRows() == 4);
    BOOST_CHECK(view3.getNumColumns() == 3);
    
    BOOST_CHECK(view3.write("StructureGridView2DTest_24_clearAllText.png"));

//---

    view3.clearStructures();

    view3.getModelBounds(bbox);

    BOOST_CHECK(bbox.getWidth() == 3 * 200.0 + 3.0 + 20.0);
    BOOST_CHECK(bbox.getHeight() == 4 * 200.0 + 3.0 + 20.0);

    BOOST_CHECK(view3.getNumRows() == 4);
    BOOST_CHECK(view3.getNumColumns() == 3);
    
    BOOST_CHECK(view3.write("StructureGridView2DTest_25_clearStructures.png"));
    
# endif // HAVE_CAIRO_PNG_SUPPORT
#endif // HAVE_CAIRO
}
