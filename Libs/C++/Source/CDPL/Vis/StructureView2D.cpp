/* 
 * StructureView2D.cpp 
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

#include <algorithm>
#include <limits>
#include <cmath>
#include <iterator>
#include <functional>

#include "CDPL/Vis/StructureView2D.hpp"
#include "CDPL/Vis/Renderer2D.hpp"

#include "CDPL/Vis/Brush.hpp"
#include "CDPL/Vis/ColorTable.hpp"
#include "CDPL/Vis/FontMetrics.hpp"
#include "CDPL/Vis/SizeAdjustment.hpp"
#include "CDPL/Vis/Alignment.hpp"
#include "CDPL/Vis/AtomFunctions.hpp"
#include "CDPL/Vis/BondFunctions.hpp"
#include "CDPL/Vis/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/Fragment.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/StereoDescriptor.hpp"
#include "CDPL/Chem/AtomContainerFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/BondStereoFlag.hpp"
#include "CDPL/Chem/AtomConfiguration.hpp"
#include "CDPL/Chem/BondConfiguration.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Chem/ReactionCenterStatus.hpp"
#include "CDPL/Chem/Atom2DCoordinatesCalculator.hpp"
#include "CDPL/Chem/BondStereoFlagCalculator.hpp"
#include "CDPL/MolProp/AtomFunctions.hpp"
#include "CDPL/Math/AffineTransform.hpp"

#include "StructureView2DParameters.hpp"


using namespace CDPL;


namespace
{

    const double WEDGE_TAIL_HEAD_WIDTH_RATIO      = 0.15;
    const double H_COUNT_HOR_ALIGNMENT_PREFERENCE = 0.5;

    const double MIN_BOND_ANGLE                   = M_PI * 30.0 / 180.0;
    const double MAX_BOND_ANGLE                   = M_PI * 150.0 / 180.0;

    const char RADICAL_ELECTRON_SYMBOL            = '.';

    const char LEFT_AAM_ID_LABEL_DELIMEITER       = '<';
    const char RIGHT_AAM_ID_LABEL_DELIMEITER      = '>';

    const char LEFT_QUERY_INFO_DELIMITER          = '[';
    const char RIGHT_QUERY_INFO_DELIMITER         = ']';

    const char BOND_IS_REACTION_CENTER_SYMBOL     = '#';
    const char BOND_NOT_A_REACTION_CENTER_SYMBOL  = 'X';
    const char DEFAULT_ATOM_SYMBOL                = '?';

    const std::size_t MAX_LINE_CACHE_SIZE          = 10000;
    const std::size_t MAX_POLYLINE_CACHE_SIZE      = 1000;
    const std::size_t MAX_POLYGON_CACHE_SIZE       = 1000;
    const std::size_t MAX_LINE_SEG_LIST_CACHE_SIZE = 1000;
    const std::size_t MAX_POINT_LIST_CACHE_SIZE    = 1000;
    const std::size_t MAX_TEXT_LABEL_CACHE_SIZE    = 8000;
}


Vis::StructureView2D::StructureView2D(const Chem::MolecularGraph* molgraph): 
    parameters(new StructureView2DParameters(*this)), fontMetrics(0), fontMetricsChanged(true), 
    reactionContext(false), hasAtomCoords(false), lineCache(MAX_LINE_CACHE_SIZE),
    polylineCache(MAX_POLYLINE_CACHE_SIZE), polygonCache(MAX_POLYGON_CACHE_SIZE),
    lineSegListCache(MAX_LINE_SEG_LIST_CACHE_SIZE), pointListCache(MAX_POINT_LIST_CACHE_SIZE),
    textLabelCache(MAX_TEXT_LABEL_CACHE_SIZE)
{
    setStructure(molgraph);
}

Vis::StructureView2D::StructureView2D(bool): 
    parameters(new StructureView2DParameters(*this)), origStructure(0), fontMetrics(0), 
    structureChanged(true), fontMetricsChanged(true), reactionContext(true), 
    hasAtomCoords(false), lineCache(MAX_LINE_CACHE_SIZE), polylineCache(MAX_POLYLINE_CACHE_SIZE),
    polygonCache(MAX_POLYGON_CACHE_SIZE), lineSegListCache(MAX_LINE_SEG_LIST_CACHE_SIZE), 
    pointListCache(MAX_POINT_LIST_CACHE_SIZE), textLabelCache(MAX_TEXT_LABEL_CACHE_SIZE) 
{}

Vis::StructureView2D::~StructureView2D() {}

void Vis::StructureView2D::render(Renderer2D& renderer)
{
    if (!origStructure)
        return;

    init();

    if (structure->getNumAtoms() == 0)
        return;

    renderer.saveState();

    paintBackground(renderer);
    renderGraphicsPrimitives(renderer);

    renderer.restoreState();
}

void Vis::StructureView2D::setStructure(const Chem::MolecularGraph* molgraph)
{
    origStructure = molgraph;
    
    structureChanged = true;
}

const Chem::MolecularGraph* Vis::StructureView2D::getStructure() const
{
    return origStructure;
}

void Vis::StructureView2D::setFontMetrics(FontMetrics* font_metrics)
{
    fontMetrics = font_metrics;
    fontMetricsChanged = true;
}

Vis::FontMetrics* Vis::StructureView2D::getFontMetrics() const
{
    return fontMetrics;
}

void Vis::StructureView2D::getModelBounds(Rectangle2D& bounds)
{
    if (!origStructure) { 
        bounds.reset();
        return;
    }

    init();

    if (structure->getNumAtoms() == 0) { 
        bounds.reset();
        return;
    }

    bounds = outputStructureBounds;

    bounds.translate(viewTranslations[1]);
    bounds.scale(viewScalingFactor);
    bounds.translate(viewTranslations[0]);
}

void Vis::StructureView2D::init()
{
    if (!(structureChanged || fontMetricsChanged || parameters->coordinatesChanged() 
          || parameters->explicitHVisibilityChanged() || parameters->propertyVisibilityChanged()
          || parameters->graphicsAttributeChanged() || parameters->viewportChanged() 
          || parameters->alignmentChanged() || parameters->sizeAdjustmentChanged() 
          || parameters->stdBondLengthChanged()))
        return;

    if (structureChanged)
        setHasAtomCoordsFlag();

    if (structureChanged || parameters->explicitHVisibilityChanged() || parameters->propertyVisibilityChanged()
        || parameters->coordinatesChanged()) {

        prepareStructureData();
        initInputAtomPosTable();
    }

    if (structureChanged || parameters->coordinatesChanged() || parameters->explicitHVisibilityChanged() 
        || parameters->stdBondLengthChanged() || parameters->propertyVisibilityChanged())
        calcStdBondLengthScalingFactor();

    if (structureChanged || parameters->coordinatesChanged() || parameters->explicitHVisibilityChanged()
        || fontMetricsChanged || parameters->propertyVisibilityChanged() || parameters->graphicsAttributeChanged())
        calcInputStructureBounds();

    if (structureChanged || fontMetricsChanged || parameters->coordinatesChanged() 
        || parameters->explicitHVisibilityChanged() || parameters->viewportChanged() 
        || parameters->sizeAdjustmentChanged() || parameters->stdBondLengthChanged() 
        || parameters->propertyVisibilityChanged() || parameters->graphicsAttributeChanged()) {

        calcViewportAdjustmentScalingFactor();
        calcOutputAtomCoords();

        initOutputBondLineTable();
        initTextLabelBounds();

        freeGraphicsPrimitives();

        createAtomPrimitives();
        createBondPrimitives();

        calcOutputStructureBounds();
        calcViewTransforms();

    } else if (parameters->alignmentChanged())
        calcViewTransforms();

    structureChanged      = false;
    fontMetricsChanged    = false;

    parameters->clearChangeFlags();
}

void Vis::StructureView2D::paintBackground(Renderer2D& renderer) const
{
    if (reactionContext || !parameters->eraseBackground())
        return;

    renderer.setPen(Pen::NO_LINE);
    renderer.setBrush(parameters->getBackgroundColor());

    Rectangle2D rect = (parameters->getViewport().isDefined() ? parameters->getViewport() : outputStructureBounds);

    renderer.drawRectangle(rect.getMin()(0), rect.getMin()(1), rect.getWidth(), rect.getHeight());
}

void Vis::StructureView2D::renderGraphicsPrimitives(Renderer2D& renderer) const
{
    Math::Matrix3D xform(prod(prod(Math::TranslationMatrix<double>(3, viewTranslations[0](0), viewTranslations[0](1)),
                                   Math::ScalingMatrix<double>(3, viewScalingFactor, viewScalingFactor)), 
                              Math::TranslationMatrix<double>(3, viewTranslations[1](0), viewTranslations[1](1))));

    renderer.transform(xform);

    std::for_each(drawList.rbegin(), drawList.rend(), 
                  std::bind(&GraphicsPrimitive2D::render, std::placeholders::_1, std::ref(renderer)));
}

void Vis::StructureView2D::initTextLabelBounds()
{
    using namespace std::placeholders;
    
    std::size_t num_atoms = structure->getNumAtoms();
        
    if (num_atoms > atomLabelBounds.size())
        atomLabelBounds.resize(num_atoms);

    std::for_each(atomLabelBounds.begin(), atomLabelBounds.begin() + num_atoms,
                  std::bind(&RectangleList::clear, _1));

    std::size_t num_bonds = structure->getNumBonds();

    if (num_bonds > bondLabelBounds.size())
        bondLabelBounds.resize(num_bonds);

    std::for_each(bondLabelBounds.begin(), bondLabelBounds.begin() + num_bonds,
                  std::bind(&Rectangle2D::reset, _1));
}

void Vis::StructureView2D::createAtomPrimitives()
{
    using namespace Chem;

    if (!fontMetrics)
        return;

    std::for_each(structure->getAtomsBegin(), structure->getAtomsEnd(),
                  std::bind(static_cast<void (StructureView2D::*)(const Chem::Atom&)>
                            (&StructureView2D::createAtomPrimitives), this, std::placeholders::_1));
}

#define CREATE_ATOM_LABEL(font, text, pos, label_brect)          \
    label = allocTextLabelPrimitive();                           \
                                                                 \
    label->setFont(font);                                        \
    label->setText(text);                                        \
    label->setPosition(pos);                                     \
                                                                 \
    drawList.push_back(label);                                   \
                                                                 \
    label_brect.translate(pos);                                  \
    label_brect.addMargin(activeLabelMargin, activeLabelMargin); \
                                                                 \
    atomLabelBounds[atom_idx].push_back(label_brect)

void Vis::StructureView2D::createAtomPrimitives(const Chem::Atom& atom)
{
    std::size_t h_count = getHydrogenCount(atom);
    std::size_t rad_elec_count = (parameters->showRadicalElectrons() ? getUnpairedElectronCount(atom) : 0);
    std::size_t aam_id = (parameters->showAtomReactionInfos() ? getAtomMappingID(atom) : 0);
    std::string symbol = getSymbol(atom);
    std::size_t isotope = (parameters->showIsotopes() ? getIsotope(atom) : 0);
    long charge = (parameters->showCharges() ? getFormalCharge(atom) : 0);
    std::string qry_info_str = (parameters->showAtomQueryInfos() ? hasMatchExpressionString(atom) ? getMatchExpressionString(atom) : "" : "");

    if (!qry_info_str.empty()) {
        qry_info_str.insert(0, 1, LEFT_QUERY_INFO_DELIMITER);
        qry_info_str.push_back(RIGHT_QUERY_INFO_DELIMITER);

    } else if (symbol.empty())
        symbol.push_back(DEFAULT_ATOM_SYMBOL);

    Rectangle2D total_brect;

    if (MolProp::getExplicitBondCount(atom, *structure) != 0 && isotope == 0 && charge == 0 && h_count == 0 && 
        rad_elec_count == 0 && qry_info_str.empty() && !parameters->showCarbons() && symbol == "C") {

        if (aam_id > 0) {
            setupLabelMargin(atom);
            setupPen(atom);
            setupSecondaryLabelFont(atom);

            createAtomMappingLabelPrimitive(atom, aam_id, total_brect);
        }

        return;
    }

    setupLabelMargin(atom);
    setupPen(atom);
    setupLabelFont(atom);

    if (isotope > 0 || h_count > 1 || aam_id > 0 || charge != 0 || rad_elec_count > 8)
        setupSecondaryLabelFont(atom);

    double baseline = 0.0;

    if (symbol.empty() && !qry_info_str.empty())
        baseline = createAtomQueryInfoLabelPrimitive(atom, qry_info_str, total_brect);
    else
        baseline = createAtomSymbolLabelPrimitive(atom, symbol, total_brect);

    if (rad_elec_count > 0 && rad_elec_count <= 8)
        createRadicalElectronPrimitives(atom, rad_elec_count, total_brect);

    if (isotope > 0)
        createAtomIsotopeLabelPrimitive(atom, isotope, total_brect);

    if (charge != 0 || rad_elec_count > 8)
        createAtomChargeLabelPrimitive(atom, charge, rad_elec_count, total_brect);

    if (h_count > 0)
        createAtomHCountLabelPrimitives(atom, h_count, baseline, total_brect);

    if (!symbol.empty() && !qry_info_str.empty())
        createAtomQueryInfoLabelPrimitive(atom, qry_info_str, baseline, total_brect);

    if (aam_id > 0)
        createAtomMappingLabelPrimitive(atom, aam_id, total_brect);
}

double Vis::StructureView2D::createAtomQueryInfoLabelPrimitive(const Chem::Atom& atom, const std::string& qry_info_str, 
                                                               Rectangle2D& total_brect)
{
    fontMetrics->setFont(activeLabelFont);

    std::size_t atom_idx = structure->getAtomIndex(atom);

    const Math::Vector2D& atom_pos = outputAtomCoords[atom_idx];

    fontMetrics->getBounds(qry_info_str, total_brect);

    Math::Vector2D brect_ctr;
    total_brect.getCenter(brect_ctr);

    Math::Vector2D label_pos = atom_pos - brect_ctr;

    Rectangle2D test_brect = total_brect;
    test_brect.translate(label_pos);
    
    double lowest_cong_fact = calcCongestionFactor(test_brect, atom);

    Rectangle2D first_char_brect;
    fontMetrics->getBounds(qry_info_str[0], first_char_brect);

    first_char_brect.getCenter(brect_ctr);

    Math::Vector2D test_pos;

    test_pos(0) = atom_pos(0) - brect_ctr(0);
    test_pos(1) = label_pos(1);

    test_brect = total_brect;
    test_brect.translate(test_pos);

    double cong_fact = calcCongestionFactor(test_brect, atom);

    if (cong_fact < lowest_cong_fact) {
        label_pos = test_pos;
        lowest_cong_fact = cong_fact;
    }
    
    test_pos(0) = atom_pos(0) - total_brect.getMax()(0) + fontMetrics->getWidth(*qry_info_str.rbegin()) * 0.5;

    test_brect = total_brect;
    test_brect.translate(test_pos);

    if (calcCongestionFactor(test_brect, atom) < lowest_cong_fact)
        label_pos = test_pos;

    TextLabelPrimitive2D* label;

    CREATE_ATOM_LABEL(activeLabelFont, qry_info_str, label_pos, total_brect);

    return label_pos(1);
}

void Vis::StructureView2D::createAtomQueryInfoLabelPrimitive(const Chem::Atom& atom, const std::string& qry_info_str, 
                                                             double baseline, Rectangle2D& total_brect)
{
    fontMetrics->setFont(activeLabelFont);

    std::size_t atom_idx = structure->getAtomIndex(atom);

    Rectangle2D label_brect;
    fontMetrics->getBounds(qry_info_str, label_brect);

    Math::Vector2D right_pos;
    Math::Vector2D left_pos;

    right_pos(0) = total_brect.getMax()(0) - label_brect.getMin()(0);
    right_pos(1) = baseline;

    left_pos(0) = total_brect.getMin()(0) - label_brect.getMax()(0);
    left_pos(1) = baseline;

    Rectangle2D right_brect = label_brect;
    Rectangle2D left_brect = label_brect;

    right_brect.translate(right_pos);
    left_brect.translate(left_pos);
    
    Math::Vector2D label_pos = (calcCongestionFactor(left_brect, atom) < calcCongestionFactor(right_brect, atom) ? 
                          left_pos : right_pos);

    TextLabelPrimitive2D* label;

    CREATE_ATOM_LABEL(activeLabelFont, qry_info_str, label_pos, label_brect);

    total_brect.addRectangle(label_brect);
}

double Vis::StructureView2D::createAtomSymbolLabelPrimitive(const Chem::Atom& atom, const std::string& symbol, 
                                                            Rectangle2D& total_brect)
{
    fontMetrics->setFont(activeLabelFont);
    fontMetrics->getBounds(symbol, total_brect);

    Rectangle2D first_char_brect;
    fontMetrics->getBounds(symbol[0], first_char_brect);

    Math::Vector2D brect_ctr;
    first_char_brect.getCenter(brect_ctr);

    std::size_t atom_idx = structure->getAtomIndex(atom);

    Math::Vector2D label_pos = outputAtomCoords[atom_idx] - brect_ctr;

    TextLabelPrimitive2D* label;

    CREATE_ATOM_LABEL(activeLabelFont, symbol, label_pos, total_brect);

    return label_pos(1);
}

void Vis::StructureView2D::createAtomIsotopeLabelPrimitive(const Chem::Atom& atom, std::size_t isotope, 
                                                           Rectangle2D& total_brect)
{
    fontMetrics->setFont(activeSecondaryLabelFont);

    std::string iso_str = std::to_string(isotope);

    std::size_t atom_idx = structure->getAtomIndex(atom);
    const Rectangle2D& sym_brect = atomLabelBounds[atom_idx][0];

    Rectangle2D label_brect;
    fontMetrics->getBounds(iso_str, label_brect);

    Math::Vector2D label_pos;

    label_pos(0) = total_brect.getMin()(0) - label_brect.getMax()(0);
    label_pos(1) = sym_brect.getMin()(1) + fontMetrics->getAscent() * 0.5;

    TextLabelPrimitive2D* label;

    CREATE_ATOM_LABEL(activeSecondaryLabelFont, iso_str, label_pos, label_brect);

    total_brect.addRectangle(label_brect);
}

void Vis::StructureView2D::createAtomChargeLabelPrimitive(const Chem::Atom& atom, long charge, std::size_t rad_elec_count, 
                                                          Rectangle2D& total_brect)
{
    fontMetrics->setFont(activeSecondaryLabelFont);

    std::string charge_str;

    if (charge != 0) {
        if (charge > 0) {
            if (charge > 1)
                charge_str.append(std::to_string(charge));

            charge_str.push_back('+');

        } else {
            if (charge < -1)
                charge_str.append(std::to_string(-charge));

            charge_str.push_back('-');
        }
    }

    if (rad_elec_count > 8) {
        charge_str.append(std::to_string(rad_elec_count));
        charge_str.push_back(RADICAL_ELECTRON_SYMBOL);
    }

    std::size_t atom_idx = structure->getAtomIndex(atom);
    const Rectangle2D& sym_brect = atomLabelBounds[atom_idx][0];

    Rectangle2D label_brect;
    fontMetrics->getBounds(charge_str, label_brect);

    Math::Vector2D label_pos;

    label_pos(0) = total_brect.getMax()(0) - label_brect.getMin()(0);
    label_pos(1) = sym_brect.getMin()(1) + fontMetrics->getAscent() * 0.5;

    TextLabelPrimitive2D* label;

    CREATE_ATOM_LABEL(activeSecondaryLabelFont, charge_str, label_pos, label_brect);

    total_brect.addRectangle(label_brect);
}

void Vis::StructureView2D::createAtomHCountLabelPrimitives(const Chem::Atom& atom, std::size_t h_count, double baseline, 
                                                           Rectangle2D& total_brect)
{
    fontMetrics->setFont(activeLabelFont);

    Rectangle2D h_label_brect;

    fontMetrics->getBounds('H', h_label_brect);

    std::string h_count_str;

    Rectangle2D count_label_brect;
    Math::Vector2D count_label_shift;

    Rectangle2D union_brect = h_label_brect;

    if (h_count > 1) {
        h_count_str = std::to_string(h_count);
    
        fontMetrics->setFont(activeSecondaryLabelFont);
        fontMetrics->getBounds(h_count_str, count_label_brect);

        count_label_shift(0) = h_label_brect.getMax()(0) - count_label_brect.getMin()(0) + activeLabelMargin; 
        count_label_shift(1) = fontMetrics->getAscent() * 0.5;

        union_brect.setMax(count_label_brect.getMax() + count_label_shift);
    }

    std::size_t atom_idx = structure->getAtomIndex(atom);

    const Math::Vector2D& atom_pos = outputAtomCoords[atom_idx];

    Math::Vector2D label_pos;

    Math::Vector2D brect_ctr;
    h_label_brect.getCenter(brect_ctr);

    label_pos(0) = total_brect.getMax()(0) - union_brect.getMin()(0);
    label_pos(1) = baseline;

    Rectangle2D test_brect = union_brect;
    test_brect.translate(label_pos);
    
    std::size_t num_atom_nbrs = MolProp::getExplicitBondCount(atom, *structure);

    double lowest_cong_fact = calcCongestionFactor(test_brect, atom) * (num_atom_nbrs < 2 ? H_COUNT_HOR_ALIGNMENT_PREFERENCE : 1.0);

    Math::Vector2D test_pos;

    test_pos(0) = total_brect.getMin()(0) - union_brect.getMax()(0);
    test_pos(1) = baseline;

    test_brect = union_brect;
    test_brect.translate(test_pos);

    double cong_fact = calcCongestionFactor(test_brect, atom) * (num_atom_nbrs < 2 ? H_COUNT_HOR_ALIGNMENT_PREFERENCE : 1.0);

    if (cong_fact < lowest_cong_fact) {
        label_pos = test_pos;
        lowest_cong_fact = cong_fact;
    }
    
    if (num_atom_nbrs > 0) { 
        test_pos(0) = atom_pos(0) - brect_ctr(0);
        test_pos(1) = total_brect.getMin()(1) - union_brect.getMax()(1);
    
        test_brect = union_brect;
        test_brect.translate(test_pos);

        cong_fact = calcCongestionFactor(test_brect, atom);

        if (cong_fact < lowest_cong_fact) {
            label_pos = test_pos;
            lowest_cong_fact = cong_fact;
        }

        test_pos(1) = total_brect.getMax()(1) - union_brect.getMin()(1);

        test_brect = union_brect;
        test_brect.translate(test_pos);

        if (calcCongestionFactor(test_brect, atom) < lowest_cong_fact)
            label_pos = test_pos;
    }

    TextLabelPrimitive2D* label;
    
    CREATE_ATOM_LABEL(activeLabelFont, "H", label_pos, h_label_brect);

    total_brect.addRectangle(h_label_brect);

    if (h_count > 1) {
        label_pos += count_label_shift;

        CREATE_ATOM_LABEL(activeSecondaryLabelFont, h_count_str, label_pos, count_label_brect);

        total_brect.addRectangle(count_label_brect);
    }
}

#define CREATE_SINGLE_POINT                            \
    point_brect.translate(point_pos);                  \
                                                       \
    points->addElement(point_pos);                     \
                                                       \
    atomLabelBounds[atom_idx].push_back(point_brect);  \
    total_brect.addRectangle(point_brect)
 
#define CREATE_DOUBLE_POINT(idx)                                                                                 \
    point_brect.translate(point_pos);                                                                            \
                                                                                                                 \
    points->addElement(point_pos);                                                                               \
                                                                                                                 \
    atomLabelBounds[atom_idx].push_back(point_brect);                                                            \
    total_brect.addRectangle(point_brect);                                                                       \
                                                                                                                 \
    point_pos(idx) += 2.0 * dbl_point_ctr_offs;                                                                  \
                                                                                                                 \
    points->addElement(point_pos);                                                                               \
                                                                                                                 \
    point_brect.translate(Math::vec(idx == 0 ? 2.0 * dbl_point_ctr_offs : 0.0, idx == 0 ? 0.0 : 2.0 * dbl_point_ctr_offs)); \
                                                                                                                 \
    atomLabelBounds[atom_idx].push_back(point_brect);                                                            \
    total_brect.addRectangle(point_brect)

void Vis::StructureView2D::createRadicalElectronPrimitives(const Chem::Atom& atom, std::size_t elec_count, Rectangle2D& total_brect)
{
    double point_diam = getElectronDotSize(atom);
    double dbl_point_ctr_offs = point_diam * 1.5;
    double point_pos_dx = total_brect.getWidth() * 0.5 + point_diam * 0.5;
    double point_pos_dy = total_brect.getHeight() * 0.5 + point_diam * 0.5;
    double pt_bounds_half_width = point_diam * 0.5 + activeLabelMargin;

    std::size_t atom_idx = structure->getAtomIndex(atom);

    Math::Vector2D alignment_ref;
    total_brect.getCenter(alignment_ref);

    Math::Vector2D point_pos;
    Rectangle2D point_brect;

    PointListPrimitive2D* points = allocPointListPrimitive();

    if (elec_count >= 1) {
        point_brect.setBounds(-pt_bounds_half_width, -pt_bounds_half_width, pt_bounds_half_width, pt_bounds_half_width);

        if (elec_count == 1) {
            point_pos(0) = alignment_ref(0); 
            point_pos(1) = alignment_ref(1) - point_pos_dy; 

            CREATE_SINGLE_POINT;

        } else {
            point_pos(0) = alignment_ref(0) - dbl_point_ctr_offs; 
            point_pos(1) = alignment_ref(1) - point_pos_dy; 

            CREATE_DOUBLE_POINT(0);
        }
    }

    if (elec_count >= 3) {
        point_brect.setBounds(-pt_bounds_half_width, -pt_bounds_half_width, pt_bounds_half_width, pt_bounds_half_width);

        if (elec_count == 3) {
            point_pos(0) = alignment_ref(0) - point_pos_dx; 
            point_pos(1) = alignment_ref(1);

            CREATE_SINGLE_POINT;

        } else {
            point_pos(0) = alignment_ref(0) - point_pos_dx; 
            point_pos(1) = alignment_ref(1) - dbl_point_ctr_offs;
            
            CREATE_DOUBLE_POINT(1);
        }
    }

    if (elec_count >= 5) {
        point_brect.setBounds(-pt_bounds_half_width, -pt_bounds_half_width, pt_bounds_half_width, pt_bounds_half_width);

        if (elec_count == 5) {
            point_pos(0) = alignment_ref(0); 
            point_pos(1) = alignment_ref(1) + point_pos_dy; 

            CREATE_SINGLE_POINT;

        } else {
            point_pos(0) = alignment_ref(0) - dbl_point_ctr_offs; 
            point_pos(1) = alignment_ref(1) + point_pos_dy; 

            CREATE_DOUBLE_POINT(0);
        }
    }

    if (elec_count >= 7) {
        point_brect.setBounds(-pt_bounds_half_width, -pt_bounds_half_width, pt_bounds_half_width, pt_bounds_half_width);

        if (elec_count == 7) {
            point_pos(0) = alignment_ref(0) + point_pos_dx; 
            point_pos(1) = alignment_ref(1);

            CREATE_SINGLE_POINT;

        } else {
            point_pos(0) = alignment_ref(0) + point_pos_dx; 
            point_pos(1) = alignment_ref(1) - dbl_point_ctr_offs;

            CREATE_DOUBLE_POINT(1);
        }
    }

    points->setPen(Pen(activePen.getColor(), point_diam));

    drawList.push_back(points);
}

void Vis::StructureView2D::createAtomMappingLabelPrimitive(const Chem::Atom& atom, std::size_t aam_id, 
                                                           const Rectangle2D& total_brect)
{
    fontMetrics->setFont(activeSecondaryLabelFont);

    std::string id_str;

    id_str.push_back(LEFT_AAM_ID_LABEL_DELIMEITER);
    id_str.append(std::to_string(aam_id));
    id_str.push_back(RIGHT_AAM_ID_LABEL_DELIMEITER);

    Rectangle2D label_brect;

    fontMetrics->getBounds(id_str, label_brect);

    std::size_t atom_idx = structure->getAtomIndex(atom);

    const RectangleList& atom_label_brects = atomLabelBounds[atom_idx];
    const Math::Vector2D& atom_pos = outputAtomCoords[atom_idx];

    Math::Vector2D label_pos;

    Math::Vector2D brect_ctr;
    label_brect.getCenter(brect_ctr);

    TextLabelPrimitive2D* label;
    
    if (atom_label_brects.empty()) {
        label_pos = atom_pos - brect_ctr;
    
        CREATE_ATOM_LABEL(activeSecondaryLabelFont, id_str, label_pos, label_brect);
        return;
    }

    label_pos(0) = atom_pos(0) - brect_ctr(0);
    label_pos(1) = total_brect.getMin()(1) - label_brect.getMax()(1);

    Rectangle2D test_brect = label_brect;
    test_brect.translate(label_pos);
    
    double lowest_cong_fact = calcCongestionFactor(test_brect, atom);

    Math::Vector2D test_pos;

    test_pos(0) = total_brect.getMin()(0) - label_brect.getMax()(0);
    test_pos(1) = atom_pos(1) - brect_ctr(1);

    test_brect = label_brect;
    test_brect.translate(test_pos);

    double cong_fact = calcCongestionFactor(test_brect, atom);

    if (cong_fact < lowest_cong_fact) {
        label_pos = test_pos;
        lowest_cong_fact = cong_fact;
    }
    
    test_pos(0) = atom_pos(0) - brect_ctr(0);
    test_pos(1) = total_brect.getMax()(1) - label_brect.getMin()(1);
    
    test_brect = label_brect;
    test_brect.translate(test_pos);

    cong_fact = calcCongestionFactor(test_brect, atom);

    if (cong_fact < lowest_cong_fact) {
        label_pos = test_pos;
        lowest_cong_fact = cong_fact;
    }

    test_pos(0) = total_brect.getMax()(0) - label_brect.getMin()(0);
    test_pos(1) = atom_pos(1) - brect_ctr(1);

    test_brect = label_brect;
    test_brect.translate(test_pos);

    if (calcCongestionFactor(test_brect, atom) < lowest_cong_fact)
        label_pos = test_pos;
    
    CREATE_ATOM_LABEL(activeSecondaryLabelFont, id_str, label_pos, label_brect);
}

void Vis::StructureView2D::createBondPrimitives()
{
    using namespace Chem;

    bool with_bond_labels = (fontMetrics && (parameters->showBondQueryInfos() || parameters->showBondReactionInfos())); 

    Line2D ctr_line;

    MolecularGraph::ConstBondIterator bonds_end = structure->getBondsEnd();

    for (MolecularGraph::ConstBondIterator it = structure->getBondsBegin(); it != bonds_end; ++it) {
        const Bond& bond = *it;

        if (!structure->containsAtom(bond.getBegin()) || !structure->containsAtom(bond.getEnd()))
            continue;

        ctr_line = outputBondLines[structure->getBondIndex(bond)];

        if (!clipLineAgainstAtomBounds(ctr_line, bond))
            continue;

        setupPen(bond);

        int asym_shift_dir = 0;
        std::size_t order = getBondOrder(bond);

        if (order == 0) {
            if (with_bond_labels)
                createBondLabelPrimitives(bond, ctr_line, 0);

            createUndefOrderBondPrimitives(bond, ctr_line);

        } else {
            switch (order) {
                
                case 1:
                    if (with_bond_labels)
                        createBondLabelPrimitives(bond, ctr_line, 0);

                    createSingleBondPrimitives(bond, ctr_line);
                    break;

                case 2:
                    asym_shift_dir = getBondAsymmetryShiftDirection(bond);

                    if (with_bond_labels)
                        createBondLabelPrimitives(bond, ctr_line, asym_shift_dir);

                    createDoubleBondPrimitives(bond, ctr_line, asym_shift_dir);
                    break;

                case 3:
                    if (with_bond_labels)
                        createBondLabelPrimitives(bond, ctr_line, 0);

                    createTripleBondPrimitives(bond, ctr_line);
            }
        }

        if (parameters->showBondReactionInfos())
            createBondRxnCenterPrimitives(bond, ctr_line, asym_shift_dir);
    }
}

#define CREATE_BOND_LABEL(text, pos, brect)            \
    label = allocTextLabelPrimitive();                 \
                                                       \
    label->setFont(activeLabelFont);                   \
    label->setText(text);                              \
    label->setPosition(pos);                           \
                                                       \
    drawList.push_back(label);                         \
                                                       \
    brect.translate(pos);                              \
    brect.addMargin(activeLabelMargin, activeLabelMargin)

void Vis::StructureView2D::createBondLabelPrimitives(const Chem::Bond& bond, const Line2D& ctr_line, int asym_shift_dir)
{
    double baseline = 0.0;

    if (parameters->showBondReactionInfos())
        baseline = createBondRxnInfoLabelPrimitive(bond, ctr_line, asym_shift_dir);

    if (parameters->showBondQueryInfos())
        createBondQueryInfoLabelPrimitive(bond, ctr_line, asym_shift_dir, baseline);
}

double Vis::StructureView2D::createBondRxnInfoLabelPrimitive(const Chem::Bond& bond, const Line2D& ctr_line, int asym_shift_dir)
{
    using namespace Chem;

    std::string rxn_info;

    switch (getReactionCenterStatus(bond)) {
        
        case ReactionCenterStatus::NO_CENTER:
            rxn_info.push_back(BOND_NOT_A_REACTION_CENTER_SYMBOL);
            break;

        case ReactionCenterStatus::IS_CENTER:
            rxn_info.push_back(BOND_IS_REACTION_CENTER_SYMBOL);
            break;

        default:
            return 0.0;
    }

    setupLabelMargin(bond);
    setupLabelFont(bond);

    fontMetrics->setFont(activeLabelFont);

    std::size_t bond_idx = structure->getBondIndex(bond);

    Rectangle2D& label_brect = bondLabelBounds[bond_idx];

    fontMetrics->getBounds(rxn_info, label_brect);

    Math::Vector2D label_pos;
    ctr_line.getCenter(label_pos);

    if (asym_shift_dir != 0) {
        Math::Vector2D perp_line_dir;
        ctr_line.getCCWPerpDirection(perp_line_dir);

        label_pos -= perp_line_dir * getLineSpacing(bond) * 0.5 * asym_shift_dir; 
    }

    Math::Vector2D brect_ctr;
    label_brect.getCenter(brect_ctr);

    label_pos -= brect_ctr;

    TextLabelPrimitive2D* label;

    CREATE_BOND_LABEL(rxn_info, label_pos, label_brect);

    return label_pos(1);
}

void Vis::StructureView2D::createBondQueryInfoLabelPrimitive(const Chem::Bond& bond, const Line2D& ctr_line, 
                                                             int asym_shift_dir, double baseline)
{
    std::string qry_info_str = (hasMatchExpressionString(bond) ? getMatchExpressionString(bond) : "");

    if (qry_info_str.empty())
        return;

    qry_info_str.insert(0, 1, LEFT_QUERY_INFO_DELIMITER);
    qry_info_str.push_back(RIGHT_QUERY_INFO_DELIMITER);

    std::size_t bond_idx = structure->getBondIndex(bond);

    Rectangle2D& total_brect = bondLabelBounds[bond_idx];
    TextLabelPrimitive2D* label;

    if (!total_brect.isDefined()) {
        setupLabelMargin(bond);
        setupLabelFont(bond);

        fontMetrics->setFont(activeLabelFont);

        Math::Vector2D bond_ctr_pos;
        ctr_line.getCenter(bond_ctr_pos);

        if (asym_shift_dir != 0) {
            Math::Vector2D perp_line_dir;
            ctr_line.getCCWPerpDirection(perp_line_dir);

            bond_ctr_pos -= perp_line_dir * getLineSpacing(bond) * 0.5 * asym_shift_dir; 
        }

        fontMetrics->getBounds(qry_info_str, total_brect);

        Math::Vector2D brect_ctr;
        total_brect.getCenter(brect_ctr);

        Math::Vector2D label_pos = bond_ctr_pos - brect_ctr;

        Rectangle2D test_brect = total_brect;
        test_brect.translate(label_pos);
    
        double lowest_cong_fact = calcCongestionFactor(test_brect, bond);

        Rectangle2D first_char_brect;
        fontMetrics->getBounds(qry_info_str[0], first_char_brect);

        first_char_brect.getCenter(brect_ctr);

        Math::Vector2D test_pos;

        test_pos(0) = bond_ctr_pos(0) - brect_ctr(0);
        test_pos(1) = label_pos(1);

        test_brect = total_brect;
        test_brect.translate(test_pos);

        double cong_fact = calcCongestionFactor(test_brect, bond);

        if (cong_fact < lowest_cong_fact) {
            label_pos = test_pos;
            lowest_cong_fact = cong_fact;
        }
    
        test_pos(0) = bond_ctr_pos(0) - total_brect.getMax()(0) + fontMetrics->getWidth(*qry_info_str.rbegin()) * 0.5;

        test_brect = total_brect;
        test_brect.translate(test_pos);

        if (calcCongestionFactor(test_brect, bond) < lowest_cong_fact)
            label_pos = test_pos;

        CREATE_BOND_LABEL(qry_info_str, label_pos, total_brect);
        return;
    }

    Rectangle2D label_brect;
    fontMetrics->getBounds(qry_info_str, label_brect);

    Math::Vector2D right_pos;
    Math::Vector2D left_pos;

    right_pos(0) = total_brect.getMax()(0) - label_brect.getMin()(0);
    right_pos(1) = baseline;

    left_pos(0) = total_brect.getMin()(0) - label_brect.getMax()(0);
    left_pos(1) = baseline;

    Rectangle2D left_brect = label_brect;
    Rectangle2D right_brect = label_brect;

    right_brect.translate(right_pos);
    left_brect.translate(left_pos);
    
    if (calcCongestionFactor(left_brect, bond) < calcCongestionFactor(right_brect, bond)) {
        CREATE_BOND_LABEL(qry_info_str, left_pos, label_brect);
        total_brect.addRectangle(label_brect);

    } else {
        CREATE_BOND_LABEL(qry_info_str, right_pos, label_brect);
        total_brect.addRectangle(label_brect);
    }
}

void Vis::StructureView2D::createUndefOrderBondPrimitives(const Chem::Bond& bond, const Line2D& ctr_line)
{
    LinePrimitive2D* line = allocLinePrimitive(false);

    line->setPoints(ctr_line.getBegin(), ctr_line.getEnd());
    line->setPen(Pen(activePen.getColor(), activePen.getWidth(), Pen::DOT_LINE));

    clipLineAgainstBondLabel(line, structure->getBondIndex(bond));
}

void Vis::StructureView2D::createSingleBondPrimitives(const Chem::Bond& bond, const Line2D& ctr_line)
{
    if (!parameters->showStereoBonds()) {
        createPlainSingleBondPrimitives(bond, ctr_line);
        return;
    }

    using namespace Chem;

    switch (getBondStereoFlag(bond, *structure)) {

        case BondStereoFlag::REVERSE_UP:
            createUpSingleBondPrimitives(bond, ctr_line, true);
            return;

        case BondStereoFlag::UP:
            createUpSingleBondPrimitives(bond, ctr_line, false);
            return;

        case BondStereoFlag::REVERSE_DOWN:
            createDownSingleBondPrimitives(bond, ctr_line, true);
            return;

        case BondStereoFlag::DOWN:
            createDownSingleBondPrimitives(bond, ctr_line, false);
            return;

        case BondStereoFlag::REVERSE_EITHER:
            createEitherSingleBondPrimitives(bond, ctr_line, true);
            return;

        case BondStereoFlag::EITHER:
            createEitherSingleBondPrimitives(bond, ctr_line, false);
            return;

        default:
            createPlainSingleBondPrimitives(bond, ctr_line);
    }
}

void Vis::StructureView2D::createUpSingleBondPrimitives(const Chem::Bond& bond, const Line2D& ctr_line, bool reverse_up)
{
    double wedge_width = getWedgeWidth(bond) * 0.5;

    Math::Vector2D start_wedge_crnr_vec;

    ctr_line.getCCWPerpDirection(start_wedge_crnr_vec);
    
    start_wedge_crnr_vec *= wedge_width;
    Math::Vector2D end_wedge_crnr_vec = start_wedge_crnr_vec;

    if (!reverse_up)
        start_wedge_crnr_vec *= WEDGE_TAIL_HEAD_WIDTH_RATIO;
    else
        end_wedge_crnr_vec *= WEDGE_TAIL_HEAD_WIDTH_RATIO;

    Line2D wedge_side1(ctr_line.getBegin() + start_wedge_crnr_vec, ctr_line.getEnd() + end_wedge_crnr_vec);
    Line2D wedge_side2(ctr_line.getBegin() - start_wedge_crnr_vec, ctr_line.getEnd() - end_wedge_crnr_vec);

    std::size_t atom1_idx = structure->getAtomIndex(bond.getBegin());
    bool atom1_visible = !atomLabelBounds[atom1_idx].empty();

    if (!atom1_visible) {
        extendUpBondWedgeSides(bond, bond.getBegin(), wedge_side1, wedge_side2, true, reverse_up);

    } else {
        if (!clipLineAgainstAtomBounds(wedge_side1, atom1_idx, true))
            return;

        if (!clipLineAgainstAtomBounds(wedge_side2, atom1_idx, true))
            return;    
    }

    std::size_t atom2_idx = structure->getAtomIndex(bond.getEnd());
    bool atom2_visible = !atomLabelBounds[atom2_idx].empty();

    if (!atom2_visible) {
        extendUpBondWedgeSides(bond, bond.getEnd(), wedge_side1, wedge_side2, false, reverse_up);

    } else {
        if (!clipLineAgainstAtomBounds(wedge_side1, atom2_idx, false))
            return;

        if (!clipLineAgainstAtomBounds(wedge_side2, atom2_idx, false))
            return;    
    }

    std::size_t bond_idx = structure->getBondIndex(bond);

    const Rectangle2D& label_brect = bondLabelBounds[bond_idx];

    if (label_brect.isDefined()) {
        Line2D clipped_ctr_line = ctr_line;
        Math::Vector2D inters_pt;

        bool pt1_visible = !label_brect.containsPoint(ctr_line.getBegin());
        bool pt2_visible = !label_brect.containsPoint(ctr_line.getEnd());

        if (pt1_visible) {
            if (pt2_visible) {
                if (clipped_ctr_line.clipEndAgainstRectangle(label_brect)) {
                    Line2D cut_line;

                    cut_line.setBegin(clipped_ctr_line.getEnd() + (reverse_up ? start_wedge_crnr_vec : end_wedge_crnr_vec));
                    cut_line.setEnd(clipped_ctr_line.getEnd() - (reverse_up ? start_wedge_crnr_vec : end_wedge_crnr_vec));

                    Line2D wedge_side11 = wedge_side1;
                    Line2D wedge_side21 = wedge_side2;

                    wedge_side1.getIntersectionPoint(cut_line, inters_pt);
                    wedge_side1.setEnd(inters_pt);

                    wedge_side2.getIntersectionPoint(cut_line, inters_pt);
                    wedge_side2.setEnd(inters_pt);

                    clipped_ctr_line.setEnd(ctr_line.getEnd());
                    clipped_ctr_line.clipBeginAgainstRectangle(label_brect);

                    cut_line.setBegin(clipped_ctr_line.getBegin() + (reverse_up ? start_wedge_crnr_vec : end_wedge_crnr_vec));
                    cut_line.setEnd(clipped_ctr_line.getBegin() - (reverse_up ? start_wedge_crnr_vec : end_wedge_crnr_vec));

                    PolygonPrimitive2D* wedge = allocPolygonPrimitive();

                    wedge_side11.getIntersectionPoint(cut_line, inters_pt);

                    wedge->addElement(inters_pt);
                    wedge->addElement(wedge_side11.getEnd());

                    if (!atom2_visible && MolProp::getExplicitBondCount(bond.getEnd(), *structure) > 2)
                        wedge->addElement(ctr_line.getEnd());

                    wedge->addElement(wedge_side21.getEnd());

                    wedge_side21.getIntersectionPoint(cut_line, inters_pt);

                    wedge->addElement(inters_pt);

                    drawList.push_back(wedge);

                    atom2_visible = true;
                }

            } else {
                clipped_ctr_line.clipEndAgainstRectangle(label_brect);
                clipped_ctr_line.setBegin(clipped_ctr_line.getEnd() + (reverse_up ? start_wedge_crnr_vec : end_wedge_crnr_vec));
                clipped_ctr_line.setEnd(clipped_ctr_line.getEnd() - (reverse_up ? start_wedge_crnr_vec : end_wedge_crnr_vec));

                wedge_side1.getIntersectionPoint(clipped_ctr_line, inters_pt);
                wedge_side1.setEnd(inters_pt);

                wedge_side2.getIntersectionPoint(clipped_ctr_line, inters_pt);
                wedge_side2.setEnd(inters_pt);

                atom2_visible = true;
            }

        } else if (pt2_visible) {
            clipped_ctr_line.clipBeginAgainstRectangle(label_brect);
            clipped_ctr_line.setEnd(clipped_ctr_line.getBegin() + (reverse_up ? start_wedge_crnr_vec : end_wedge_crnr_vec));
            clipped_ctr_line.setBegin(clipped_ctr_line.getBegin() - (reverse_up ? start_wedge_crnr_vec : end_wedge_crnr_vec));

            wedge_side1.getIntersectionPoint(clipped_ctr_line, inters_pt);
            wedge_side1.setBegin(inters_pt);

            wedge_side2.getIntersectionPoint(clipped_ctr_line, inters_pt);
            wedge_side2.setBegin(inters_pt);

            atom1_visible = true;

        } else
            return;
    }

    PolygonPrimitive2D* wedge = allocPolygonPrimitive();

    if (!atom1_visible && MolProp::getExplicitBondCount(bond.getBegin(), *structure) > 2)
        wedge->addElement(ctr_line.getBegin());

    wedge->addElement(wedge_side1.getBegin());
    wedge->addElement(wedge_side1.getEnd());

    if (!atom2_visible && MolProp::getExplicitBondCount(bond.getEnd(), *structure) > 2)
        wedge->addElement(ctr_line.getEnd());

    wedge->addElement(wedge_side2.getEnd());
    wedge->addElement(wedge_side2.getBegin());

    drawList.push_back(wedge);
}

void Vis::StructureView2D::extendUpBondWedgeSides(const Chem::Bond& bond, const Chem::Atom& atom, Line2D& wedge_side1, 
                                                  Line2D& wedge_side2, bool pt1, bool reverse_up) const
{
    using namespace Chem;

    if (MolProp::getExplicitBondCount(atom, *structure) == 2) {
        Atom::ConstAtomIterator nbr_atoms_end = atom.getAtomsEnd();
        Atom::ConstBondIterator b_it = atom.getBondsBegin();
        const Bond* nbr_bond = 0;

        for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(); a_it != nbr_atoms_end; ++a_it, ++b_it) {
            if (!structure->containsBond(*b_it) || !structure->containsAtom(*a_it))
                continue;

            if (&*b_it != &bond) {
                nbr_bond = &*b_it;
                break;
            }
        }

        if (!nbr_bond)
            return;

        Line2D nbr_bond_line = outputBondLines[structure->getBondIndex(*nbr_bond)];

        if (clipLineAgainstAtomBounds(nbr_bond_line, *nbr_bond)) {
            std::size_t order = getBondOrder(*nbr_bond);
            unsigned int stereo = (order == 1 ? getBondStereoFlag(*nbr_bond, *structure) : BondStereoFlag::PLAIN);

            bool reverse_nbr_stereo = (stereo == BondStereoFlag::REVERSE_UP || stereo == BondStereoFlag::REVERSE_DOWN || 
                                       stereo == BondStereoFlag::REVERSE_EITHER);

            double bond_angle = calcBondAngle(bond, *nbr_bond);

            if (order == 1 && (stereo == BondStereoFlag::UP || stereo == BondStereoFlag::DOWN ||
                               stereo == BondStereoFlag::EITHER || reverse_nbr_stereo)) {

                bool head_head_or_tail_tail = (&bond.getBegin() == &nbr_bond->getBegin() || &bond.getEnd() == &nbr_bond->getEnd());

                if (head_head_or_tail_tail) {
                    if (reverse_up == reverse_nbr_stereo) {
                        if (bond_angle < MIN_BOND_ANGLE)
                            return;

                    } else if (bond_angle < MIN_BOND_ANGLE || bond_angle > MAX_BOND_ANGLE) 
                        return;

                } else  {
                    if (reverse_up != reverse_nbr_stereo) {
                        if (bond_angle < MIN_BOND_ANGLE)
                            return;

                    } else if (bond_angle < MIN_BOND_ANGLE || bond_angle > MAX_BOND_ANGLE) 
                        return;
                }

                double wedge_width = getWedgeWidth(*nbr_bond) * 0.5;

                Math::Vector2D nbr_start_wedge_crnr_vec;
                nbr_bond_line.getCCWPerpDirection(nbr_start_wedge_crnr_vec);
    
                if (head_head_or_tail_tail)
                    nbr_start_wedge_crnr_vec *= -wedge_width;
                else
                    nbr_start_wedge_crnr_vec *= wedge_width;

                Math::Vector2D nbr_end_wedge_crnr_vec = nbr_start_wedge_crnr_vec;

                if (!reverse_nbr_stereo)
                    nbr_start_wedge_crnr_vec *= WEDGE_TAIL_HEAD_WIDTH_RATIO;
                else
                    nbr_end_wedge_crnr_vec *= WEDGE_TAIL_HEAD_WIDTH_RATIO;

                Line2D nbr_wedge_side1(nbr_bond_line.getBegin() + nbr_start_wedge_crnr_vec, nbr_bond_line.getEnd() +
                                       nbr_end_wedge_crnr_vec);
                Line2D nbr_wedge_side2(nbr_bond_line.getBegin() - nbr_start_wedge_crnr_vec, nbr_bond_line.getEnd() -
                                       nbr_end_wedge_crnr_vec);

                Math::Vector2D side1_inters_pt;
                Math::Vector2D side2_inters_pt;

                if (!wedge_side1.getIntersectionPoint(nbr_wedge_side1, side1_inters_pt)) 
                    side1_inters_pt = (&atom == &nbr_bond->getBegin() ?
                                       nbr_wedge_side1.getBegin() : nbr_wedge_side1.getEnd());

                if (!wedge_side2.getIntersectionPoint(nbr_wedge_side2, side2_inters_pt))
                    side2_inters_pt = (&atom == &nbr_bond->getBegin() ? 
                                       nbr_wedge_side2.getBegin() : nbr_wedge_side2.getEnd());

                if (pt1) {
                    wedge_side1.setBegin(side1_inters_pt);
                    wedge_side2.setBegin(side2_inters_pt);

                } else {
                    wedge_side1.setEnd(side1_inters_pt);
                    wedge_side2.setEnd(side2_inters_pt);
                }

            } else if (bond_angle > MIN_BOND_ANGLE && bond_angle < MAX_BOND_ANGLE) {
                Math::Vector2D inters_pt1;
                Math::Vector2D inters_pt2;

                if (wedge_side1.getIntersectionPoint(nbr_bond_line, inters_pt1) &&
                    wedge_side2.getIntersectionPoint(nbr_bond_line, inters_pt2)) {

                    if (pt1) {
                        wedge_side1.setBegin(inters_pt1);
                        wedge_side2.setBegin(inters_pt2);
                    
                    } else {
                        wedge_side1.setEnd(inters_pt1);
                        wedge_side2.setEnd(inters_pt2);
                    }
                }
            }
        }

    } else {
        extendWedgeSideToNeighborBonds(wedge_side1, bond, atom, pt1);
        extendWedgeSideToNeighborBonds(wedge_side2, bond, atom, pt1);
    }
}

void Vis::StructureView2D::extendWedgeSideToNeighborBonds(Line2D& line, const Chem::Bond& bond, 
                                                          const Chem::Atom& atom, bool pt1) const
{
    using namespace Chem;

    double min_line_len = std::numeric_limits<double>::max();
    bool inters_on_nbr_line = false;

    Math::Vector2D inters_pt;

    Atom::ConstAtomIterator nbr_atoms_end = atom.getAtomsEnd();
    Atom::ConstBondIterator b_it = atom.getBondsBegin();

    for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(); a_it != nbr_atoms_end; ++a_it, ++b_it) {
        const Bond& nbr_bond = *b_it;

        if (&bond == &nbr_bond)
            continue;

        if (!structure->containsAtom(*a_it) || !structure->containsBond(nbr_bond))
            continue;

        const Line2D& nbr_bond_line = outputBondLines[structure->getBondIndex(nbr_bond)];

        line.getIntersectionPoint(nbr_bond_line, inters_pt);

        double line_len = (pt1 ? norm2(inters_pt - line.getEnd()) : norm2(inters_pt - line.getBegin()));

        if (nbr_bond_line.containsPoint(inters_pt)) {
            if (inters_on_nbr_line && line_len >= min_line_len)
                continue;

            inters_on_nbr_line = true;

        } else if (!inters_on_nbr_line && line.containsPoint(inters_pt)) {
            if (line_len >= min_line_len)
                continue;

        } else
            continue;

        if (pt1) 
            line.setBegin(inters_pt);
        else
            line.setEnd(inters_pt);

        min_line_len = line_len;
    }
}

void Vis::StructureView2D::createDownSingleBondPrimitives(const Chem::Bond& bond, const Line2D& ctr_line, bool reverse_down)
{
    double end_wedge_width = getWedgeWidth(bond) * 0.5;
    double start_wedge_width = end_wedge_width * WEDGE_TAIL_HEAD_WIDTH_RATIO;

    if (reverse_down)
        std::swap(end_wedge_width, start_wedge_width);

    double hash_dist = getHashSpacing(bond);
    std::size_t num_hashes = std::size_t(std::ceil(ctr_line.getLength() / hash_dist));
    double hash_len_inc = (end_wedge_width - start_wedge_width) / num_hashes;

    Math::Vector2D hash_pos_shift;
    ctr_line.getDirection(hash_pos_shift);

    hash_pos_shift *= hash_dist;

    Math::Vector2D perp_bond_dir;
    ctr_line.getCCWPerpDirection(perp_bond_dir);

    Math::Vector2D hash_pos = ctr_line.getBegin();
    Math::Vector2D hash_pos_perp_shift;

    double hash_len = start_wedge_width;

    LineSegmentListPrimitive2D* hashes = allocLineSegListPrimitive();

    std::size_t bond_idx = structure->getBondIndex(bond);

    const Rectangle2D& label_brect = bondLabelBounds[bond_idx];

    if (label_brect.isDefined()) {
        Math::Vector2D hash_pt1;
        Math::Vector2D hash_pt2;

        for (std::size_t i = 0; i < num_hashes; i++, hash_len += hash_len_inc, hash_pos += hash_pos_shift) {
            hash_pos_perp_shift = perp_bond_dir * hash_len;

            hash_pt1 = hash_pos + hash_pos_perp_shift;

            if (label_brect.containsPoint(hash_pt1))
                continue;

            hash_pt2 = hash_pos - hash_pos_perp_shift;

            if (label_brect.containsPoint(hash_pt2))
                continue;

            hashes->addElement(hash_pt1);
            hashes->addElement(hash_pt2);
        }

    } else {
        for (std::size_t i = 0; i < num_hashes; i++, hash_len += hash_len_inc, hash_pos += hash_pos_shift) {
            hash_pos_perp_shift = perp_bond_dir * hash_len;

            hashes->addElement(hash_pos + hash_pos_perp_shift);
            hashes->addElement(hash_pos - hash_pos_perp_shift);
        }
    }

    drawList.push_back(hashes);
}

void Vis::StructureView2D::createEitherSingleBondPrimitives(const Chem::Bond& bond, const Line2D& ctr_line, bool reverse_either)
{
    double end_wedge_width = getWedgeWidth(bond) * 0.5;
    double start_wedge_width = end_wedge_width * WEDGE_TAIL_HEAD_WIDTH_RATIO;

    if (reverse_either)
        std::swap(end_wedge_width, start_wedge_width);

    double hash_dist = getHashSpacing(bond);
    std::size_t num_hashes = std::size_t(std::ceil(ctr_line.getLength() / hash_dist));
    double hash_len_inc = (end_wedge_width - start_wedge_width) / num_hashes;

    Math::Vector2D hash_pos_shift;
    ctr_line.getDirection(hash_pos_shift);

    hash_pos_shift *= hash_dist;

    Math::Vector2D perp_bond_dir;
    ctr_line.getCCWPerpDirection(perp_bond_dir);

    Math::Vector2D hash_pos = ctr_line.getBegin();
    Math::Vector2D hash_pos_perp_shift;

    double hash_len = start_wedge_width;

    PolylinePrimitive2D* line_chain = allocPolylinePrimitive();

    line_chain->addElement(hash_pos);

    drawList.push_back(line_chain);

    std::size_t bond_idx = structure->getBondIndex(bond);

    const Rectangle2D& label_brect = bondLabelBounds[bond_idx];

    if (label_brect.isDefined()) {
        std::size_t i;

        for (i = 0; i < num_hashes; i++, hash_len += hash_len_inc, hash_pos += hash_pos_shift) {
            if (label_brect.containsPoint(hash_pos))
                break;

            hash_pos_perp_shift = perp_bond_dir * hash_len;

            if ((i % 2) == 0)
                line_chain->addElement(hash_pos + hash_pos_perp_shift);
            else
                line_chain->addElement(hash_pos - hash_pos_perp_shift);
        }

        line_chain->addElement(hash_pos);

        for ( ; i < num_hashes && label_brect.containsPoint(hash_pos); i++, hash_len += hash_len_inc, hash_pos += hash_pos_shift);

        if (i == num_hashes)
            return;

        line_chain = allocPolylinePrimitive();

        line_chain->addElement(hash_pos - hash_pos_shift);

        drawList.push_back(line_chain);

        for ( ; i < num_hashes; i++, hash_len += hash_len_inc, hash_pos += hash_pos_shift) {
            hash_pos_perp_shift = perp_bond_dir * hash_len;

            if ((i % 2) == 0)
                line_chain->addElement(hash_pos + hash_pos_perp_shift);
            else
                line_chain->addElement(hash_pos - hash_pos_perp_shift);
        }

    } else {
        for (std::size_t i = 0; i < num_hashes; i++, hash_len += hash_len_inc, hash_pos += hash_pos_shift) {
            hash_pos_perp_shift = perp_bond_dir * hash_len;

            if ((i % 2) == 0)
                line_chain->addElement(hash_pos + hash_pos_perp_shift);
            else
                line_chain->addElement(hash_pos - hash_pos_perp_shift);
        }
    }

    line_chain->addElement(ctr_line.getEnd());
}

void Vis::StructureView2D::createPlainSingleBondPrimitives(const Chem::Bond& bond, const Line2D& ctr_line)
{
    LinePrimitive2D* line = allocLinePrimitive();

    line->setPoints(ctr_line.getBegin(), ctr_line.getEnd());

    clipLineAgainstBondLabel(line, structure->getBondIndex(bond));
}

void Vis::StructureView2D::createDoubleBondPrimitives(const Chem::Bond& bond, const Line2D& ctr_line, int asym_shift_dir)
{
    using namespace Chem;

    bool either_stereo = false;

    if (parameters->showStereoBonds()) {
        unsigned int stereo = getBondStereoFlag(bond, *structure);
        either_stereo = (stereo == BondStereoFlag::EITHER || stereo == BondStereoFlag::REVERSE_EITHER);
    }

    if (asym_shift_dir == 0) 
        createSymDoubleBondPrimitives(bond, either_stereo, ctr_line);
    else
        createAsymDoubleBondPrimitives(bond, either_stereo, ctr_line, asym_shift_dir);
}

void Vis::StructureView2D::createSymDoubleBondPrimitives(const Chem::Bond& bond, bool either_stereo, const Line2D& ctr_line)
{
    Math::Vector2D line_shift;
    ctr_line.getCCWPerpDirection(line_shift);

    line_shift *= getLineSpacing(bond) * 0.5;    

    LinePrimitive2D* bond_line1 = allocLinePrimitive();
    LinePrimitive2D* bond_line2 = allocLinePrimitive();

    if (either_stereo) {
        bond_line1->setPoints(ctr_line.getBegin() + line_shift, ctr_line.getEnd() - line_shift);
        bond_line2->setPoints(ctr_line.getBegin() - line_shift, ctr_line.getEnd() + line_shift);

    } else {
        bond_line1->setPoints(ctr_line.getBegin() + line_shift, ctr_line.getEnd() + line_shift);
        bond_line2->setPoints(ctr_line.getBegin() - line_shift, ctr_line.getEnd() - line_shift);
    }

    std::size_t atom1_idx = structure->getAtomIndex(bond.getBegin());
    std::size_t atom2_idx = structure->getAtomIndex(bond.getEnd());

    bool atom1_visible = !atomLabelBounds[atom1_idx].empty();
    bool atom2_visible = !atomLabelBounds[atom2_idx].empty();

    bool draw_line1 = true;

    if (atom1_visible)
        draw_line1 = clipLineAgainstAtomBounds(*bond_line1, atom1_idx, true);
    else
        extendBondLineToNeighborBonds(*bond_line1, bond, bond.getBegin(), true);
    
    if (draw_line1) {
        if (atom2_visible)
            draw_line1 = clipLineAgainstAtomBounds(*bond_line1, atom2_idx, false);
        else
            extendBondLineToNeighborBonds(*bond_line1, bond, bond.getEnd(), false);
    }

    bool draw_line2 = true;

    if (atom1_visible)
        draw_line2 = clipLineAgainstAtomBounds(*bond_line2, atom1_idx, true);
    else
        extendBondLineToNeighborBonds(*bond_line2, bond, bond.getBegin(), true);

    if (draw_line2) {
        if (atom2_visible)
            draw_line2 = clipLineAgainstAtomBounds(*bond_line2, atom2_idx, false);
        else
            extendBondLineToNeighborBonds(*bond_line2, bond, bond.getEnd(), false);
    }

    std::size_t bond_idx = structure->getBondIndex(bond);

    if (draw_line1)
        clipLineAgainstBondLabel(bond_line1, bond_idx);

    if (draw_line2)
        clipLineAgainstBondLabel(bond_line2, bond_idx);
}

void Vis::StructureView2D::createAsymDoubleBondPrimitives(const Chem::Bond& bond, bool either_stereo, const Line2D& ctr_line, 
                                                          int asym_shift_dir)
{
    Math::Vector2D line_shift;
    ctr_line.getCCWPerpDirection(line_shift);

    line_shift *= getLineSpacing(bond) * asym_shift_dir;    

    LinePrimitive2D* bond_line1 = allocLinePrimitive();
    LinePrimitive2D* bond_line2 = allocLinePrimitive();

    bond_line1->setPoints(ctr_line.getBegin(), ctr_line.getEnd());
    bond_line2->setPoints(ctr_line.getBegin() - line_shift, ctr_line.getEnd() - line_shift);

    std::size_t atom1_idx = structure->getAtomIndex(bond.getBegin());
    std::size_t atom2_idx = structure->getAtomIndex(bond.getEnd());

    std::size_t atom1_bnd_cnt = MolProp::getExplicitBondCount(bond.getBegin(), *structure);
    std::size_t atom2_bnd_cnt = MolProp::getExplicitBondCount(bond.getEnd(), *structure);

    bool atom1_visible = !atomLabelBounds[atom1_idx].empty();
    bool atom2_visible = !atomLabelBounds[atom2_idx].empty();

    double trim_len = getDoubleBondTrimLength(bond);

    bool draw_line2 = true;

    if (atom1_visible)
        draw_line2 = clipLineAgainstAtomBounds(*bond_line2, atom1_idx, true);

    else {
        clipLineAgainstNeighborBonds(*bond_line2, bond, bond.getBegin(), true);

        if (atom1_bnd_cnt > 1)
            draw_line2 = trimLine(*bond_line2, trim_len, true);
    }

    if (draw_line2) {
        if (atom2_visible)
            draw_line2 = clipLineAgainstAtomBounds(*bond_line2, atom2_idx, false);

        else {
            clipLineAgainstNeighborBonds(*bond_line2, bond, bond.getEnd(), false);

            if (atom2_bnd_cnt > 1)
                draw_line2 = trimLine(*bond_line2, trim_len, false);
        }
    }

    if (either_stereo && draw_line2) {
        Math::Vector2D tmp = bond_line1->getEnd();

        bond_line1->setEnd(bond_line2->getEnd());
        bond_line2->setEnd(tmp);
    }

    std::size_t bond_idx = structure->getBondIndex(bond);

    clipLineAgainstBondLabel(bond_line1, bond_idx);

    if (draw_line2) 
        clipLineAgainstBondLabel(bond_line2, bond_idx);
}

void Vis::StructureView2D::createTripleBondPrimitives(const Chem::Bond& bond, const Line2D& ctr_line)
{
    Math::Vector2D line_shift;
    ctr_line.getCCWPerpDirection(line_shift);

    line_shift *= getLineSpacing(bond);    

    LinePrimitive2D* bond_line1 = allocLinePrimitive();
    LinePrimitive2D* bond_line2 = allocLinePrimitive();
    LinePrimitive2D* bond_line3 = allocLinePrimitive();

    bond_line1->setPoints(ctr_line.getBegin(), ctr_line.getEnd());
    bond_line2->setPoints(ctr_line.getBegin() - line_shift, ctr_line.getEnd() - line_shift);
    bond_line3->setPoints(ctr_line.getBegin() + line_shift, ctr_line.getEnd() + line_shift);

    std::size_t atom1_idx = structure->getAtomIndex(bond.getBegin());
    std::size_t atom2_idx = structure->getAtomIndex(bond.getEnd());

    std::size_t atom1_bnd_cnt = MolProp::getExplicitBondCount(bond.getBegin(), *structure);
    std::size_t atom2_bnd_cnt = MolProp::getExplicitBondCount(bond.getEnd(), *structure);

    bool atom1_visible = !atomLabelBounds[atom1_idx].empty();
    bool atom2_visible = !atomLabelBounds[atom2_idx].empty();

    double trim_len = getTripleBondTrimLength(bond);

    bool draw_line2 = true;

    if (atom1_visible)
        draw_line2 = clipLineAgainstAtomBounds(*bond_line2, atom1_idx, true);

    else {
        clipLineAgainstNeighborBonds(*bond_line2, bond, bond.getBegin(), true);

        if (atom1_bnd_cnt > 1)
            draw_line2 = trimLine(*bond_line2, trim_len, true);
    }

    if (draw_line2) {
        if (atom2_visible)
            draw_line2 = clipLineAgainstAtomBounds(*bond_line2, atom2_idx, false);

        else {
            clipLineAgainstNeighborBonds(*bond_line2, bond, bond.getEnd(), false);

            if (atom2_bnd_cnt > 1)
                draw_line2 = trimLine(*bond_line2, trim_len, false);
        }
    }

    bool draw_line3 = true;

    if (atom1_visible)
        draw_line3 = clipLineAgainstAtomBounds(*bond_line3, atom1_idx, true);

    else {
        clipLineAgainstNeighborBonds(*bond_line3, bond, bond.getBegin(), true);

        if (atom1_bnd_cnt > 1)
            draw_line3 = trimLine(*bond_line3, trim_len, true);
    }

    if (draw_line3) {
        if (atom2_visible)
            draw_line3 = clipLineAgainstAtomBounds(*bond_line3, atom2_idx, false);

        else {
            clipLineAgainstNeighborBonds(*bond_line3, bond, bond.getEnd(), false);

            if (atom2_bnd_cnt > 1)
                draw_line3 = trimLine(*bond_line3, trim_len, false);
        }
    }

    std::size_t bond_idx = structure->getBondIndex(bond);

    clipLineAgainstBondLabel(bond_line1, bond_idx);

    if (draw_line2)
        clipLineAgainstBondLabel(bond_line2, bond_idx);

    if (draw_line3)
        clipLineAgainstBondLabel(bond_line3, bond_idx);
}

void Vis::StructureView2D::createBondRxnCenterPrimitives(const Chem::Bond& bond, const Line2D& ctr_line, int asym_shift_dir)
{
    using namespace Chem;

    unsigned int rxn_ctr_status = getReactionCenterStatus(bond);

    rxn_ctr_status &= (ReactionCenterStatus::BOND_MADE | ReactionCenterStatus::BOND_BROKEN | 
                       ReactionCenterStatus::BOND_ORDER_CHANGE);

    if (rxn_ctr_status == 0)
        return;

    std::size_t bond_idx = structure->getBondIndex(bond);

    Math::Vector2D ctr_pos;
    ctr_line.getCenter(ctr_pos);

    Math::Vector2D perp_line_dir;
    ctr_line.getCCWPerpDirection(perp_line_dir);

    Math::Vector2D pt_shift1 = perp_line_dir * getRxnCenterLineLength(bond) * 0.5;

    if (asym_shift_dir != 0) 
        ctr_pos -= perp_line_dir * getLineSpacing(bond) * 0.5 * asym_shift_dir; 

    if ((rxn_ctr_status & ReactionCenterStatus::BOND_ORDER_CHANGE) != 0) {
        LinePrimitive2D* mark_line1 = allocLinePrimitive();

        mark_line1->setBegin(ctr_pos + pt_shift1);
        mark_line1->setEnd(ctr_pos - pt_shift1);
        
        clipLineAgainstBondLabel(mark_line1, bond_idx);
    }

    if ((rxn_ctr_status & (ReactionCenterStatus::BOND_MADE | ReactionCenterStatus::BOND_BROKEN)) == 0)
        return;

    Math::Vector2D line_dir;
    ctr_line.getDirection(line_dir);

    Math::Vector2D pt_shift2 = line_dir * getRxnCenterLineSpacing(bond);

    LinePrimitive2D* mark_line2 = allocLinePrimitive();

    mark_line2->setBegin(ctr_pos - pt_shift2 + pt_shift1);
    mark_line2->setEnd(ctr_pos - pt_shift2 - pt_shift1);

    LinePrimitive2D* mark_line3 = allocLinePrimitive();

    mark_line3->setBegin(ctr_pos + pt_shift2 + pt_shift1);
    mark_line3->setEnd(ctr_pos + pt_shift2 - pt_shift1);

    clipLineAgainstBondLabel(mark_line2, bond_idx);
    clipLineAgainstBondLabel(mark_line3, bond_idx);
}

int Vis::StructureView2D::getBondAsymmetryShiftDirection(const Chem::Bond& bond) const
{
    using namespace Chem;

    const Atom* bond_atoms[2] = { &bond.getBegin(), &bond.getEnd() };

    std::size_t num_atom1_nbrs = MolProp::getExplicitBondCount(*bond_atoms[0], *structure);
    std::size_t num_atom2_nbrs = MolProp::getExplicitBondCount(*bond_atoms[1], *structure);

    if (num_atom1_nbrs <= 1 && num_atom2_nbrs <= 1)
        return 0;

    if ((num_atom1_nbrs <= 1 && num_atom2_nbrs >= 3) || (num_atom2_nbrs <= 1 && num_atom1_nbrs >= 3))
        return 0;

    double weight_sym = 0.0;    
    
    const Line2D& bond_line = outputBondLines[structure->getBondIndex(bond)];

    for (std::size_t i = 0; i < 2; i++) {
        Atom::ConstAtomIterator nbr_atoms_end = bond_atoms[i]->getAtomsEnd();
        Atom::ConstBondIterator b_it = bond_atoms[i]->getBondsBegin();

        for (Atom::ConstAtomIterator a_it = bond_atoms[i]->getAtomsBegin(); a_it != nbr_atoms_end; ++a_it, ++b_it) {
            const Bond& nbr_bond = *b_it;

            if (&bond == &nbr_bond)
                continue;

            if (!structure->containsAtom(*a_it) || !structure->containsBond(nbr_bond))
                continue;

            bool ring_bond = getRingFlag(nbr_bond);
            double bond_weight = 1.0;

            if (ring_bond) {
                try    {
                    if (getAromaticityFlag(nbr_bond))
                        bond_weight = 100.0;
                    else
                        bond_weight = 10.0;

                } catch (const Base::Exception& e) {}
            }

            const Math::Vector2D& nbr_atom_pos = outputAtomCoords[structure->getAtomIndex(nbr_bond.getNeighbor(*bond_atoms[i]))];

            if (bond_line.getDistance(nbr_atom_pos) > 0.0)
                weight_sym += bond_weight;
            else
                weight_sym -= bond_weight;
        }
    }

    return (weight_sym < 0.0 ? int(-1) : int(1));
}

bool Vis::StructureView2D::trimLine(Line2D& line, double trim_len, bool pt1) const
{
    if (line.getLength() <= trim_len)
        return false;

    Math::Vector2D trim_vec;

    line.getDirection(trim_vec);

    if (pt1) {
        trim_vec *= trim_len;
        line.translateBegin(trim_vec);

    } else {
        trim_vec *= -trim_len;
        line.translateEnd(trim_vec);
    }

    return true;
}

bool Vis::StructureView2D::clipLineAgainstAtomBounds(Line2D& line, const Chem::Bond& bond) const
{
    return (clipLineAgainstAtomBounds(line, structure->getAtomIndex(bond.getBegin()), true)
            && clipLineAgainstAtomBounds(line, structure->getAtomIndex(bond.getEnd()), false));
}

bool Vis::StructureView2D::clipLineAgainstAtomBounds(Line2D& line, std::size_t atom_idx, bool pt1) const
{
    const RectangleList& atom_label_brects = atomLabelBounds[atom_idx];
    RectangleList::const_iterator brects_end = atom_label_brects.end();
    
    for (RectangleList::const_iterator it = atom_label_brects.begin(); it != brects_end; ++it) {
        const Rectangle2D& brect = *it;

        if (pt1) {
            if (brect.containsPoint(line.getEnd()))
                return false;

            line.clipBeginAgainstRectangle(brect);

        } else {
            if (brect.containsPoint(line.getBegin()))
                return false;

            line.clipEndAgainstRectangle(brect);
        }
    }

    return true;
}

void Vis::StructureView2D::extendBondLineToNeighborBonds(Line2D& line, const Chem::Bond& bond, const Chem::Atom& atom, bool pt1) const
{
    using namespace Chem;

    double min_line_len = std::numeric_limits<double>::max();
    Math::Vector2D inters_pt;

    Atom::ConstAtomIterator nbr_atoms_end = atom.getAtomsEnd();
    Atom::ConstBondIterator b_it = atom.getBondsBegin();

    for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(); a_it != nbr_atoms_end; ++a_it, ++b_it) {
        const Bond& nbr_bond = *b_it;

        if (&bond == &nbr_bond)
            continue;

        if (!structure->containsAtom(*a_it) || !structure->containsBond(nbr_bond))
            continue;

        const Line2D& nbr_bond_line = outputBondLines[structure->getBondIndex(nbr_bond)];

        line.getIntersectionPoint(nbr_bond_line, inters_pt);

        if (!nbr_bond_line.containsPoint(inters_pt))
            continue;

        double line_len = (pt1 ? norm2(inters_pt - line.getEnd()) : norm2(inters_pt - line.getBegin()));

        if (line_len < min_line_len) {
            min_line_len = line_len;

            if (pt1) 
                line.setBegin(inters_pt);
            else
                line.setEnd(inters_pt);
        }
    }
}

void Vis::StructureView2D::clipLineAgainstNeighborBonds(Line2D& line, const Chem::Bond& bond, const Chem::Atom& atom,
                                                           bool pt1) const
{
    using namespace Chem;

    Atom::ConstAtomIterator nbr_atoms_end = atom.getAtomsEnd();
    Atom::ConstBondIterator b_it = atom.getBondsBegin();

    for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(); a_it != nbr_atoms_end; ++a_it, ++b_it) {
        const Bond& nbr_bond = *b_it;

        if (&bond == &nbr_bond)
            continue;

        if (!structure->containsAtom(*a_it) || !structure->containsBond(nbr_bond))
            continue;

        const Line2D& nbr_bond_line = outputBondLines[structure->getBondIndex(nbr_bond)];

        if (pt1) 
            line.clipBeginAgainstLineSeg(nbr_bond_line);
        else
            line.clipEndAgainstLineSeg(nbr_bond_line);
    }
}

void Vis::StructureView2D::clipLineAgainstBondLabel(LinePrimitive2D* line, std::size_t bond_idx)
{
    const Rectangle2D& label_brect = bondLabelBounds[bond_idx];

    if (!label_brect.isDefined()) {
        drawList.push_back(line);
        return;
    }

    bool pt1_visible = !label_brect.containsPoint(line->getBegin());
    bool pt2_visible = !label_brect.containsPoint(line->getEnd());

    if (pt1_visible) {
        if (pt2_visible) {
            Math::Vector2D saved_pt2 = line->getEnd();

            if (!line->clipEndAgainstRectangle(label_brect)) {
                drawList.push_back(line);

            } else {
                LinePrimitive2D* line2 = allocLinePrimitive();

                line2->setPen(line->getPen());
                line2->setBegin(line->getEnd());
                line2->setEnd(saved_pt2);
                line2->clipBeginAgainstRectangle(label_brect);

                drawList.push_back(line);
                drawList.push_back(line2);
            }

        } else {
            line->clipEndAgainstRectangle(label_brect);

            drawList.push_back(line);
        }

    } else if (pt2_visible) {
        line->clipBeginAgainstRectangle(label_brect);

        drawList.push_back(line);
    }
}

double Vis::StructureView2D::calcCongestionFactor(const Rectangle2D& brect, const Base::PropertyContainer& cntnr) const
{
    using namespace Chem;

    double congestion_fact = 0.0;

    Math::Vector2D diff;
    Math::Vector2D brect_ctr;
    Math::Vector2D tmp;

    brect.getCenter(brect_ctr);

    std::size_t i = 0;
    MolecularGraph::ConstAtomIterator atoms_end = structure->getAtomsEnd();

    for (MolecularGraph::ConstAtomIterator a_it = structure->getAtomsBegin(); a_it != atoms_end; ++a_it, i++) {
        const Atom& atom = *a_it;

        if (&atom == &cntnr)
            continue;

        diff = outputAtomCoords[i] - brect_ctr;
        congestion_fact += 1.0 / innerProd(diff, diff);

        const RectangleList& atom_label_brects = atomLabelBounds[i];
        RectangleList::const_iterator brects_end = atom_label_brects.end();

        for (RectangleList::const_iterator br_it = atom_label_brects.begin(); br_it != brects_end; ++br_it) {
            const Rectangle2D& label_brect = *br_it;

            if (brect.intersectsRectangle(label_brect))
                congestion_fact += 1000.0;
            
            label_brect.getCenter(diff);

            diff -= brect_ctr;
            congestion_fact += 1.0 / innerProd(diff, diff);
        }
    }

    i = 0;
    MolecularGraph::ConstBondIterator bonds_end = structure->getBondsEnd();

    for (MolecularGraph::ConstBondIterator b_it = structure->getBondsBegin(); b_it != bonds_end; ++b_it, i++) {
        const Bond& bond = *b_it;

        if (&bond == &cntnr)
            continue;

        if (!structure->containsAtom(bond.getBegin()) || !structure->containsAtom(bond.getEnd()))
            continue;

        outputBondLines[i].getCenter(diff);

        diff -= brect_ctr;
        congestion_fact += 1.0 / innerProd(diff, diff);

        const Rectangle2D& label_brect = bondLabelBounds[i];

        if (!label_brect.isDefined())
            continue;

        if (brect.intersectsRectangle(label_brect))
            congestion_fact += 1000.0;
            
        label_brect.getCenter(diff);

        diff -= brect_ctr;
        congestion_fact += 1.0 / innerProd(diff, diff);
    }

    return congestion_fact;
}

double Vis::StructureView2D::calcBondAngle(const Chem::Bond& bond1, const Chem::Bond& bond2) const
{
    const Line2D& ctr_line1 = outputBondLines[structure->getBondIndex(bond1)];
    const Line2D& ctr_line2 = outputBondLines[structure->getBondIndex(bond2)];

    Math::Vector2D line1_dir;
    ctr_line1.getDirection(line1_dir);

    Math::Vector2D line2_dir;
    ctr_line2.getDirection(line2_dir);

    double dot_prod = innerProd(line1_dir, line2_dir);

    if (&bond1.getBegin() != &bond2.getBegin() && &bond1.getEnd() != &bond2.getEnd())
        dot_prod *= -1.0;

    return std::acos(dot_prod);
}

double Vis::StructureView2D::calcInputBondLength(const Chem::Bond& bond) const
{
    return norm2(inputAtomCoords[structure->getAtomIndex(bond.getBegin())] 
                  - inputAtomCoords[structure->getAtomIndex(bond.getEnd())]);
}

std::size_t Vis::StructureView2D::getHydrogenCount(const Chem::Atom& atom) const
{
    using namespace Chem;

    if (MolProp::getExplicitBondCount(atom, *structure) != 0 && !parameters->showHydrogenCounts()) {
        if (!parameters->showNonCarbonHydrogenCounts())
            return 0;

        if (getType(atom) == AtomType::C)
            return 0;
    }

    try {
        return (MolProp::getExplicitAtomCount(atom, *origStructure, AtomType::H) - 
                MolProp::getExplicitAtomCount(atom, *structure, AtomType::H) + 
                calcImplicitHydrogenCount(atom, *origStructure));

    } catch (const Base::Exception& e) {
        return 0;
    }
}

void Vis::StructureView2D::prepareStructureData()
{
    using namespace Chem;

    if (parameters->showExplicitHydrogens()) {
        structure = origStructure;
        return;
    }

    if (!hDepleteStructure.get())
        hDepleteStructure.reset(new Fragment());
    
    structure = hDepleteStructure.get();

    *hDepleteStructure = *origStructure;

    bool calc_atom_coords = parameters->useCalculatedAtomCoords() || !hasAtomCoords;
    std::size_t num_atoms = structure->getNumAtoms();
    bool modified = false;

    for (std::size_t i = 0; i < num_atoms; i++) {
        const Atom& atom = structure->getAtom(i);
        
        if (getType(atom) == AtomType::H)
            continue;

        bool check_stereo_flag = false;
        bool remove_one_h = false;
        std::size_t exp_bond_count = MolProp::getExplicitBondCount(atom, *structure);

        try {
            if (exp_bond_count == 2 &&
                MolProp::calcExplicitValence(atom, *structure) == 3 &&
                MolProp::getExplicitAtomCount(atom, *structure, AtomType::H) == 1 &&
                calcImplicitHydrogenCount(atom, *structure) == 0) {

                bool has_db_geom = false;

                Atom::ConstBondIterator bonds_end = atom.getBondsEnd();
                Atom::ConstAtomIterator a_it = atom.getAtomsBegin();

                for (Atom::ConstBondIterator b_it = atom.getBondsBegin(); b_it != bonds_end; ++b_it, ++a_it) {
                    const Bond& bond = *b_it;

                    if (!structure->containsBond(bond))
                        continue;

                    const Atom& nbr_atom = *a_it;
                
                    if (!structure->containsAtom(nbr_atom))
                        continue;

                    if (getBondOrder(bond) != 2)
                        continue;

                    const StereoDescriptor& stereo_desc = getStereoDescriptor(bond);
                    unsigned int config = stereo_desc.getConfiguration();

                    if (stereo_desc.isValid(bond) 
                        && (config == BondConfiguration::CIS || config == BondConfiguration::TRANS || config == BondConfiguration::EITHER)) {
                        has_db_geom = true;
                        break;
                    }
                }

                if (has_db_geom)
                    continue;
            }

            if (parameters->showStereoBonds()) {
                const StereoDescriptor& stereo_desc = getStereoDescriptor(atom);
                unsigned int config = stereo_desc.getConfiguration();

                if (stereo_desc.isValid(atom) 
                    && (config == AtomConfiguration::R || config == AtomConfiguration::S || config == AtomConfiguration::EITHER)) {

                    if (calc_atom_coords) {
                        if (config != AtomConfiguration::EITHER && (!hasStereoCenterFlag(atom) || getStereoCenterFlag(atom))) {
                            if (exp_bond_count < 4)
                                continue;

                            remove_one_h = true;
                        }

                    } else {
                        bool has_flagged_bnd = false;

                        for (Atom::ConstBondIterator it = atom.getBondsBegin(), end = atom.getBondsEnd(); it != end; ++it)
                            if (get2DStereoFlag(*it) != BondStereoFlag::PLAIN) {
                                has_flagged_bnd = true;
                                break;
                            }

                        if (has_flagged_bnd) {
                            check_stereo_flag = true;

                            if (config != AtomConfiguration::EITHER)  {
                                if (exp_bond_count < 4)
                                    continue;

                                remove_one_h = true;
                            }
                        }
                    }
                }
            }

        } catch (const Base::Exception& e) {}

        Atom::ConstBondIterator bonds_end = atom.getBondsEnd();
        Atom::ConstAtomIterator a_it = atom.getAtomsBegin();

        for (Atom::ConstBondIterator b_it = atom.getBondsBegin(); b_it != bonds_end; ++b_it, ++a_it) {
            const Bond& bond = *b_it;

            if (!structure->containsBond(bond))
                continue;

            const Atom& nbr_atom = *a_it;

            if (!structure->containsAtom(nbr_atom))
                continue;

            if (getType(nbr_atom) != AtomType::H)
                continue;
            
            if (parameters->showIsotopes() && getIsotope(nbr_atom) > 0)
                continue;
                    
            if (parameters->showAtomReactionInfos() && getAtomMappingID(nbr_atom) > 0)
                continue;
        
            if (parameters->showCharges() && getFormalCharge(nbr_atom) != 0)
                continue;

            if (parameters->showRadicalElectrons() && getUnpairedElectronCount(nbr_atom) > 0)
                continue;

            if (check_stereo_flag && get2DStereoFlag(bond) != BondStereoFlag::PLAIN)
                continue;

            if (MolProp::getExplicitBondCount(nbr_atom, *structure) > 1)
                continue;

            std::size_t nbr_atom_idx = structure->getAtomIndex(nbr_atom);

            if (nbr_atom_idx < i)
                i--;

            hDepleteStructure->removeAtom(nbr_atom_idx);
            modified = true;
            num_atoms--;

            if (remove_one_h)
                break;
        }
    }

    if (modified) {
        perceiveComponents(*hDepleteStructure, true);
        calcTopologicalDistanceMatrix(*hDepleteStructure, true);
    }
}

void Vis::StructureView2D::initInputAtomPosTable()
{
    if (!parameters->useCalculatedAtomCoords() && hasAtomCoords) {
        inputAtomCoords.clear();
        get2DCoordinates(*structure, inputAtomCoords);

    } else {
        if (structureChanged || parameters->explicitHVisibilityChanged() || parameters->propertyVisibilityChanged() ||
            calcInputAtomCoords.isEmpty() || calcBondStereoFlags.isEmpty()) {

            Chem::Atom2DCoordinatesCalculator(*structure, calcInputAtomCoords);

            Chem::BondStereoFlagCalculator sto_flag_calc;

            sto_flag_calc.setAtom2DCoordinatesFunction(std::bind(static_cast<const Math::Vector2D& (Math::Vector2DArray::*)(std::size_t) const>(&Math::Vector2DArray::getElement), 
                                                                 std::ref(calcInputAtomCoords), std::bind(&Chem::MolecularGraph::getAtomIndex, structure, std::placeholders::_1)));
            sto_flag_calc.calculate(*structure, calcBondStereoFlags);
        }

        inputAtomCoords = calcInputAtomCoords;
    }

    Math::Vector2DArray::ElementIterator coords_end = inputAtomCoords.getElementsEnd();

    for (Math::Vector2DArray::ElementIterator it = inputAtomCoords.getElementsBegin(); it != coords_end; ++it) {
        Math::Vector2D& pos = *it;

        pos(1) = -pos(1);
    }
}

void Vis::StructureView2D::calcViewTransforms()
{
    viewScalingFactor = 1.0;

    const Rectangle2D& viewport = parameters->getViewport();

    if (!viewport.isDefined()) {
        viewTranslations[0].clear();
        viewTranslations[1].clear();
        return;
    }

    Math::Vector2D op_brect_ctr;
    outputStructureBounds.getCenter(op_brect_ctr);

    viewTranslations[1] = op_brect_ctr * -1.0;

    double op_x_dim = outputStructureBounds.getWidth();
    double op_y_dim = outputStructureBounds.getHeight();

    if (op_x_dim * op_y_dim != 0.0) {
        double vp_x_dim = viewport.getWidth();
        double vp_y_dim = viewport.getHeight();

        switch (parameters->getSizeAdjustment()) {

            case SizeAdjustment::BEST_FIT: {
                if (structure->getNumAtoms() > 1) {
                    double x_dim_ratio = vp_x_dim / op_x_dim;
                    double y_dim_ratio = vp_y_dim / op_y_dim;

                    viewScalingFactor = std::min(x_dim_ratio, y_dim_ratio); 
                    break;
                }
            }

            case SizeAdjustment::IF_REQUIRED: {
                double x_dim_ratio = vp_x_dim / op_x_dim;
                double y_dim_ratio = vp_y_dim / op_y_dim;

                if (x_dim_ratio >= 1.0 && y_dim_ratio >= 1.0)
                    break;
            
                viewScalingFactor = std::min(x_dim_ratio, y_dim_ratio); 
            }

            default:
                break;
        }
    }

    Math::Vector2D vp_ctr;
    viewport.getCenter(vp_ctr);

    switch (parameters->getAlignment() & Alignment::H_ALIGNMENT_MASK) {

        case Alignment::H_CENTER:
            viewTranslations[0][0] = vp_ctr[0];
            break;

        case Alignment::LEFT:
            viewTranslations[0][0] = viewport.getMin()[0] + op_x_dim * viewScalingFactor * 0.5;
            break;

        case Alignment::RIGHT:
            viewTranslations[0][0] = viewport.getMax()[0] - op_x_dim * viewScalingFactor * 0.5;
            break;

        default:
            viewTranslations[0][0] = op_brect_ctr[0];
    }

    switch (parameters->getAlignment() & Alignment::V_ALIGNMENT_MASK) {

        case Alignment::V_CENTER:
            viewTranslations[0][1] = vp_ctr[1];
            return;

        case Alignment::TOP:
            viewTranslations[0][1] = viewport.getMin()[1] + op_y_dim * viewScalingFactor * 0.5;
            return;

        case Alignment::BOTTOM:
            viewTranslations[0][1] = viewport.getMax()[1] - op_y_dim * viewScalingFactor * 0.5;
            return;

        default:
            viewTranslations[0][1] = op_brect_ctr[1];
    }
}

double Vis::StructureView2D::calcAvgInputBondLength() const
{
    using namespace Chem;

    if (structure->getNumBonds() == 0)
        return 0.0;

    double avg_len = 0.0;
    std::size_t num_bonds = 0;

    MolecularGraph::ConstBondIterator bonds_end = structure->getBondsEnd();

    for (MolecularGraph::ConstBondIterator it = structure->getBondsBegin(); it != bonds_end; ++it) {
        if (!structure->containsAtom(it->getBegin()) || !structure->containsAtom(it->getEnd()))
            continue;

        avg_len += calcInputBondLength(*it);
        num_bonds++;
    }

    if (num_bonds == 0)
        return 0.0;

    return (avg_len / num_bonds);
}

void Vis::StructureView2D::calcStdBondLengthScalingFactor()
{
    if (parameters->getStdBondLength() > 0.0) {
        double avg_len = calcAvgInputBondLength();

        if (avg_len != 0.0) {
            stdBondLengthScalingFactor = parameters->getStdBondLength() / avg_len;
            return;
        }
    }

    stdBondLengthScalingFactor = 1.0;    
}

void Vis::StructureView2D::calcViewportAdjustmentScalingFactor()
{
    viewportAdjustmentScalingFactor = 1.0;

    const Rectangle2D& viewport = parameters->getViewport();

    if (!viewport.isDefined() || inputStructureBounds.getArea() == 0.0)
        return;

    double vp_x_dim = viewport.getWidth();
    double vp_y_dim = viewport.getHeight();
    
    double st_x_dim = inputStructureBounds.getWidth() * stdBondLengthScalingFactor;
    double st_y_dim = inputStructureBounds.getHeight() * stdBondLengthScalingFactor;

    switch (parameters->getSizeAdjustment()) {

        case SizeAdjustment::IF_REQUIRED: {
            double x_dim_ratio = vp_x_dim / st_x_dim;
            double y_dim_ratio = vp_y_dim / st_y_dim;

            if (x_dim_ratio >= 1.0 && y_dim_ratio >= 1.0)
                return;
            
            viewportAdjustmentScalingFactor = std::min(x_dim_ratio, y_dim_ratio); 
            return;
        }

        case SizeAdjustment::BEST_FIT: {
            double x_dim_ratio = vp_x_dim / st_x_dim;
            double y_dim_ratio = vp_y_dim / st_y_dim;

            viewportAdjustmentScalingFactor = std::min(x_dim_ratio, y_dim_ratio); 
        }

        default:
            return;
    }
}

void Vis::StructureView2D::calcInputStructureBounds()
{
    std::size_t num_atoms = structure->getNumAtoms();

    if (num_atoms == 1 && parameters->getViewport().isDefined()) {
        viewportAdjustmentScalingFactor = 1.0;

        calcOutputAtomCoords();

        freeGraphicsPrimitives();
    
        initTextLabelBounds();
        createAtomPrimitives();

        calcOutputStructureBounds();

        inputStructureBounds = outputStructureBounds;

    } else {
        inputStructureBounds.reset();

        for (std::size_t i = 0; i < num_atoms; i++) 
            inputStructureBounds.addPoint(inputAtomCoords[i]);
    }
}

void Vis::StructureView2D::calcOutputStructureBounds()
{
    outputStructureBounds = inputStructureBounds;
    outputStructureBounds.scale(stdBondLengthScalingFactor * viewportAdjustmentScalingFactor);

    if (!fontMetrics)
        return;

    std::size_t num_atoms = structure->getNumAtoms();

    for (std::size_t i = 0; i < num_atoms; i++)
        std::for_each(atomLabelBounds[i].begin(), atomLabelBounds[i].end(),
                      std::bind(&Rectangle2D::addRectangle, std::ref(outputStructureBounds), std::placeholders::_1));

    std::size_t num_bonds = structure->getNumBonds();

    for (std::size_t i = 0; i < num_bonds; i++) {
        const Rectangle2D& label_brect = bondLabelBounds[i];

        if (!label_brect.isDefined())
            continue;

        outputStructureBounds.addRectangle(label_brect);
    }
}

void Vis::StructureView2D::calcOutputAtomCoords()
{
    using namespace Chem;

    std::size_t num_atoms = structure->getNumAtoms();

    if (num_atoms > outputAtomCoords.getSize())
        outputAtomCoords.resize(num_atoms);

    double total_scale_fac = stdBondLengthScalingFactor * viewportAdjustmentScalingFactor;

    for (std::size_t i = 0; i < num_atoms; i++) {
        outputAtomCoords[i] = inputAtomCoords[i];
        outputAtomCoords[i] *= total_scale_fac;
    }
}

void Vis::StructureView2D::initOutputBondLineTable()
{
    using namespace Chem;

    std::size_t num_bonds = structure->getNumBonds();

    if (num_bonds > outputBondLines.size())
        outputBondLines.resize(num_bonds);

    std::size_t i = 0;
    MolecularGraph::ConstBondIterator bonds_end = structure->getBondsEnd();

    for (MolecularGraph::ConstBondIterator it = structure->getBondsBegin(); it != bonds_end; ++it, i++) {
        const Bond& bond = *it;

        if (!structure->containsAtom(bond.getBegin()) || !structure->containsAtom(bond.getEnd()))
            continue;

        const Math::Vector2D& atom1_pos = outputAtomCoords[structure->getAtomIndex(bond.getBegin())];
        const Math::Vector2D& atom2_pos = outputAtomCoords[structure->getAtomIndex(bond.getEnd())];

        Line2D& line = outputBondLines[i];

        line.setBegin(atom1_pos);
        line.setEnd(atom2_pos);
    }
}

unsigned int Vis::StructureView2D::getBondStereoFlag(const Chem::Bond& bond, const Chem::MolecularGraph& molgraph) const
{
    try {
        if (parameters->useCalculatedAtomCoords() || !hasAtomCoords) 
            return calcBondStereoFlags[molgraph.getBondIndex(bond)];

        return get2DStereoFlag(bond);

    } catch (const Base::Exception& e) {
        return Chem::BondStereoFlag::PLAIN;
    }
}

std::size_t Vis::StructureView2D::getBondOrder(const Chem::Bond& bond) const
{
    if (!hasOrder(bond))
        return 0;

    switch (getOrder(bond)) {
        
        case 1:
            return 1;

        case 2:
            return 2;

        case 3:
            return 3;

        default:
            return 0;
    }
}

void Vis::StructureView2D::setHasAtomCoordsFlag()
{
    hasAtomCoords = hasCoordinates(*origStructure, 2);
}

double Vis::StructureView2D::getLineWidth(const Chem::Bond& bond) const
{    
    if (hasLineWidth(bond))
        return calcOutputSize(bond, Vis::getLineWidth(bond));

    if (hasBondLineWidth(*structure))
        return calcOutputSize(bond, getBondLineWidth(*structure));

    return calcOutputSize(bond, parameters->getBondLineWidth());
}

double Vis::StructureView2D::getRxnCenterLineLength(const Chem::Bond& bond) const
{
    if (hasReactionCenterLineLength(bond))
        return calcOutputSize(bond, getReactionCenterLineLength(bond));

    if (hasReactionCenterLineLength(*structure))
        return calcOutputSize(bond, getReactionCenterLineLength(*structure));

    return calcOutputSize(bond, parameters->getReactionCenterLineLength());
}

double Vis::StructureView2D::getRxnCenterLineSpacing(const Chem::Bond& bond) const
{
    if (hasReactionCenterLineSpacing(bond))
        return calcOutputSize(bond, getReactionCenterLineSpacing(bond));

    if (hasReactionCenterLineSpacing(*structure))
        return calcOutputSize(bond, getReactionCenterLineSpacing(*structure));

    return calcOutputSize(bond, parameters->getReactionCenterLineSpacing());
}

double Vis::StructureView2D::getDoubleBondTrimLength(const Chem::Bond& bond) const
{
    if (hasDoubleBondTrimLength(bond))
        return calcOutputSize(bond, Vis::getDoubleBondTrimLength(bond));

    if (hasDoubleBondTrimLength(*structure))
        return calcOutputSize(bond, Vis::getDoubleBondTrimLength(*structure));

    return calcOutputSize(bond, parameters->getDoubleBondTrimLength());
}

double Vis::StructureView2D::getTripleBondTrimLength(const Chem::Bond& bond) const
{
    if (hasTripleBondTrimLength(bond))
        return calcOutputSize(bond, Vis::getTripleBondTrimLength(bond));

    if (hasTripleBondTrimLength(*structure))
        return calcOutputSize(bond, Vis::getTripleBondTrimLength(*structure));

    return calcOutputSize(bond, parameters->getTripleBondTrimLength());
}

double Vis::StructureView2D::getLineSpacing(const Chem::Bond& bond) const
{
    if (hasLineSpacing(bond))
        return calcOutputSize(bond,  Vis::getLineSpacing(bond));

    if (hasBondLineSpacing(*structure))
        return calcOutputSize(bond, getBondLineSpacing(*structure));

    return calcOutputSize(bond, parameters->getBondLineSpacing());
}

double Vis::StructureView2D::getWedgeWidth(const Chem::Bond& bond) const
{
    if (hasStereoBondWedgeWidth(bond))
        return calcOutputSize(bond, getStereoBondWedgeWidth(bond));

    if (hasStereoBondWedgeWidth(*structure))
        return calcOutputSize(bond, getStereoBondWedgeWidth(*structure));

    return calcOutputSize(bond, parameters->getStereoBondWedgeWidth());
}

double Vis::StructureView2D::getHashSpacing(const Chem::Bond& bond) const
{
    if (hasStereoBondHashSpacing(bond))
        return calcOutputSize(bond, getStereoBondHashSpacing(bond));

    if (hasStereoBondHashSpacing(*structure))
        return calcOutputSize(bond, getStereoBondHashSpacing(*structure));

    return calcOutputSize(bond, parameters->getStereoBondHashSpacing());
}

double Vis::StructureView2D::getLabelSize(const Chem::Bond& bond) const
{
    return calcOutputSize(getLabelSizeSpec(bond));
}

const Vis::Color& Vis::StructureView2D::getColor(const Chem::Bond& bond) const
{
    if (hasColor(bond))
        return  Vis::getColor(bond);

    if (hasBondColor(*structure))
        return getBondColor(*structure);

    return parameters->getBondColor();
}

const Vis::Font& Vis::StructureView2D::getLabelFont(const Chem::Bond& bond) const
{
    if (hasLabelFont(bond))
        return  Vis::getLabelFont(bond);

    if (hasBondLabelFont(*structure))
        return getBondLabelFont(*structure);

    return parameters->getBondLabelFont();
}

const Vis::SizeSpecification& Vis::StructureView2D::getLabelSizeSpec(const Chem::Bond& bond) const
{
    if (hasLabelSize(bond))
        return Vis::getLabelSize(bond);

    if (hasBondLabelSize(*structure))
        return getBondLabelSize(*structure);

    return parameters->getBondLabelSize();
}

const Vis::SizeSpecification& Vis::StructureView2D::getLabelMarginSpec(const Chem::Bond& bond) const
{
    if (hasLabelMargin(bond))
        return getLabelMargin(bond);

    if (hasBondLabelMargin(*structure))
        return getBondLabelMargin(*structure);

    return parameters->getBondLabelMargin();
}

void Vis::StructureView2D::setupLabelMargin(const Chem::Bond& bond)
{
    const SizeSpecification& margin = getLabelMarginSpec(bond);

    if (!margin.isRelative())
        activeLabelMargin = calcOutputSize(margin);
    else
        activeLabelMargin = calcOutputSize(margin.getValue() * getLabelSizeSpec(bond).getValue(), margin);
}

void Vis::StructureView2D::setupPen(const Chem::Bond& bond)
{
    activePen.setColor(getColor(bond));
    activePen.setWidth(getLineWidth(bond));
    activePen.setLineStyle(Pen::SOLID_LINE);
}

void Vis::StructureView2D::setupLabelFont(const Chem::Bond& bond)
{
    activeLabelFont = getLabelFont(bond);
    activeLabelFont.setSize(getLabelSize(bond));
}

//--------

double Vis::StructureView2D::getLabelSize(const Chem::Atom& atom) const
{
    return calcOutputSize(getLabelSizeSpec(atom));
}

double Vis::StructureView2D::getSecondaryLabelSize(const Chem::Atom& atom) const
{
    return calcOutputSize(atom, getSecondaryLabelSizeSpec(atom));
}

double Vis::StructureView2D::getElectronDotSize(const Chem::Atom& atom) const
{
    return calcOutputSize(atom, getElectronDotSizeSpec(atom));
}

const Vis::Color& Vis::StructureView2D::getColor(const Chem::Atom& atom) const
{
    if (hasColor(atom))
        return Vis::getColor(atom);

    const Color& def_color = hasAtomColor(*structure) ? getAtomColor(*structure) : parameters->getAtomColor();

    if (hasAtomColorTable(*structure)) 
        return getAtomColorTable(*structure)->getValue(getType(atom), def_color);
    
    if (!parameters->getAtomColorTable())
        return def_color;

    return parameters->getAtomColorTable()->getValue(getType(atom), def_color);
}

const Vis::Font& Vis::StructureView2D::getLabelFont(const Chem::Atom& atom) const
{
    if (hasLabelFont(atom))
        return Vis::getLabelFont(atom);

    if (hasAtomLabelFont(*structure))
        return getAtomLabelFont(*structure);

    return parameters->getAtomLabelFont();
}

const Vis::Font& Vis::StructureView2D::getSecondaryLabelFont(const Chem::Atom& atom) const
{
    if (hasSecondaryLabelFont(atom))
        return Vis::getSecondaryLabelFont(atom);

    if (hasSecondaryAtomLabelFont(*structure))
        return getSecondaryAtomLabelFont(*structure);

    return parameters->getSecondaryAtomLabelFont();
}

const Vis::SizeSpecification& Vis::StructureView2D::getLabelSizeSpec(const Chem::Atom& atom) const
{
    if (hasLabelSize(atom))
        return Vis::getLabelSize(atom);

    if (hasAtomLabelSize(*structure))
        return getAtomLabelSize(*structure);

    return parameters->getAtomLabelSize();
}

const Vis::SizeSpecification& Vis::StructureView2D::getSecondaryLabelSizeSpec(const Chem::Atom& atom) const
{
    if (hasSecondaryLabelSize(atom))
        return Vis::getSecondaryLabelSize(atom);

    if (hasSecondaryAtomLabelSize(*structure))
        return getSecondaryAtomLabelSize(*structure);

    return parameters->getSecondaryAtomLabelSize();
}

const Vis::SizeSpecification& Vis::StructureView2D::getElectronDotSizeSpec(const Chem::Atom& atom) const
{
    if (hasRadicalElectronDotSize(atom))
        return getRadicalElectronDotSize(atom);

    if (hasRadicalElectronDotSize(*structure))
        return getRadicalElectronDotSize(*structure);

    return parameters->getRadicalElectronDotSize();
}

const Vis::SizeSpecification& Vis::StructureView2D::getLabelMarginSpec(const Chem::Atom& atom) const
{
    if (hasLabelMargin(atom))
        return getLabelMargin(atom);

    if (hasAtomLabelMargin(*structure))
        return getAtomLabelMargin(*structure);

    return parameters->getAtomLabelMargin();
}

void Vis::StructureView2D::setupLabelMargin(const Chem::Atom& atom)
{
    activeLabelMargin = calcOutputSize(atom, getLabelMarginSpec(atom));
}

void Vis::StructureView2D::setupPen(const Chem::Atom& atom)
{
    activePen.setColor(getColor(atom));
}

void Vis::StructureView2D::setupLabelFont(const Chem::Atom& atom)
{
    activeLabelFont = getLabelFont(atom);
    activeLabelFont.setSize(getLabelSize(atom));
}

void Vis::StructureView2D::setupSecondaryLabelFont(const Chem::Atom& atom)
{
    activeSecondaryLabelFont = getSecondaryLabelFont(atom);
    activeSecondaryLabelFont.setSize(getSecondaryLabelSize(atom));
}

double Vis::StructureView2D::calcOutputSize(const Chem::Bond& bond, const SizeSpecification& size_spec) const
{    
    if (!size_spec.isRelative())
        return calcOutputSize(size_spec);

    return calcOutputSize(size_spec.getValue() * calcInputBondLength(bond), size_spec);
}

double Vis::StructureView2D::calcOutputSize(const Chem::Atom& atom, const SizeSpecification& size_spec) const
{    
    if (!size_spec.isRelative())
        return calcOutputSize(size_spec);

    return calcOutputSize(size_spec.getValue() * getLabelSizeSpec(atom).getValue(), size_spec);
}

double Vis::StructureView2D::calcOutputSize(const SizeSpecification& size_spec) const
{
    return calcOutputSize(size_spec.getValue(), size_spec);
}

double Vis::StructureView2D::calcOutputSize(double size, const SizeSpecification& size_spec) const
{
    if (size_spec.followsInputScaling()) {
        if (size_spec.followsOutputScaling())
            return (size * stdBondLengthScalingFactor * viewportAdjustmentScalingFactor);

        return (size * stdBondLengthScalingFactor);
    }

    if (size_spec.followsOutputScaling())
        return (size * viewportAdjustmentScalingFactor);

    return size;
}

void Vis::StructureView2D::freeGraphicsPrimitives()
{
    lineCache.putAll();
    polylineCache.putAll();
    polygonCache.putAll();
    lineSegListCache.putAll();
    pointListCache.putAll();
    textLabelCache.putAll();

    drawList.clear();
}

Vis::LinePrimitive2D* Vis::StructureView2D::allocLinePrimitive(bool set_pen)
{
    LinePrimitive2D* prim = lineCache.getRaw();

    if (set_pen)
        prim->setPen(activePen);

    return prim;
}

Vis::PolylinePrimitive2D* Vis::StructureView2D::allocPolylinePrimitive()
{
    PolylinePrimitive2D* prim = polylineCache.getRaw();

    prim->clear();
    prim->setPen(activePen);

    return prim;
}

Vis::PolygonPrimitive2D* Vis::StructureView2D::allocPolygonPrimitive()
{
    PolygonPrimitive2D* prim = polygonCache.getRaw();

    prim->clear();
    prim->setPen(activePen);
    prim->setBrush(activePen.getColor());

    return prim;
}

Vis::LineSegmentListPrimitive2D* Vis::StructureView2D::allocLineSegListPrimitive()
{
    LineSegmentListPrimitive2D* prim = lineSegListCache.getRaw();

    prim->clear();
    prim->setPen(activePen);

    return prim;
}

Vis::PointListPrimitive2D* Vis::StructureView2D::allocPointListPrimitive()
{
    PointListPrimitive2D* prim = pointListCache.getRaw();

    prim->clear();

    return prim;
}

Vis::TextLabelPrimitive2D* Vis::StructureView2D::allocTextLabelPrimitive()
{
    TextLabelPrimitive2D* prim = textLabelCache.getRaw();

    prim->setPen(activePen.getColor());

    return prim;
}
