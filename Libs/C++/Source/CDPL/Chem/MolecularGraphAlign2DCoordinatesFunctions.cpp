/* 
 * MolecularGraphAlign2DCoordinatesFunctions.cpp 
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

#include <cmath>

#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/AtomContainerFunctions.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/AtomMapping.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/UtilityFunctions.hpp"
#include "CDPL/Chem/BondStereoFlag.hpp"
#include "CDPL/Chem/SubstructureSearch.hpp"
#include "CDPL/Chem/CommonConnectedSubstructureSearch.hpp"
#include "CDPL/Math/KabschAlgorithm.hpp"


using namespace CDPL; 


namespace
{

    double calcError(const Math::DMatrix& ref_coords_mtx, const Math::DMatrix& algnd_coords_mtx, const Math::Matrix3D& xform)
    {
        auto err = 0.0;
        auto num_atoms = ref_coords_mtx.getSize2();
     
        for (std::size_t i = 0; i < num_atoms; i++) {
            auto trans_x = algnd_coords_mtx(0, i) * xform(0, 0) + algnd_coords_mtx(1, i) * xform(0, 1) + xform(0, 2);
            auto trans_y = algnd_coords_mtx(0, i) * xform(1, 0) + algnd_coords_mtx(1, i) * xform(1, 1) + xform(1, 2);
            auto d_x = (trans_x - ref_coords_mtx(0, i));
            auto d_y = (trans_y - ref_coords_mtx(1, i));
            
            err += d_x * d_x + d_y * d_y;
        }

        return std::sqrt(err / num_atoms);
    }

    void flipBondStereo(Chem::MolecularGraph& molgraph)
    {
        using namespace Chem;
        
        for (auto& bond : molgraph.getBonds()) {
            if (!has2DStereoFlag(bond))
                continue;

            switch (get2DStereoFlag(bond)) {

                case BondStereoFlag::UP:
                    set2DStereoFlag(bond, BondStereoFlag::DOWN);
                    continue;

                case BondStereoFlag::REVERSE_UP:
                    set2DStereoFlag(bond, BondStereoFlag::REVERSE_DOWN);
                    continue;

                case BondStereoFlag::DOWN:
                    set2DStereoFlag(bond, BondStereoFlag::UP);
                    continue;

                case BondStereoFlag::REVERSE_DOWN:
                    set2DStereoFlag(bond, BondStereoFlag::REVERSE_UP);
            }
        }
    }

    class DefAtomMatchExpression :
        public Chem::MatchExpression<Chem::Atom, Chem::MolecularGraph>
    {

      public:
        bool operator()(const Chem::Atom& query_atom, const Chem::MolecularGraph&,
                        const Chem::Atom& target_atom, const Chem::MolecularGraph&,
                        const Base::Any&) const
        {
            return Chem::atomTypesMatch(getType(query_atom), getType(target_atom));
        }
    };

    class DefBondMatchExpression :
        public Chem::MatchExpression<Chem::Bond, Chem::MolecularGraph>
    {

      public:
        bool operator()(const Chem::Bond& query_bond, const Chem::MolecularGraph&,
                        const Chem::Bond& target_bond, const Chem::MolecularGraph&,
                        const Base::Any&) const
        {
            return ((getOrder(query_bond) == getOrder(target_bond)) ||
                    getAromaticityFlag(query_bond) || getAromaticityFlag(target_bond));
        }
    };
}

bool Chem::align2DCoordinates(MolecularGraph& molgraph, const AtomContainer& atoms, const Math::Vector2DArray& ref_coords, bool fix_bond_stereo)
{
    auto num_atoms = atoms.getNumAtoms();
    
    if (num_atoms == 0)
        return false;

    Math::DMatrix ref_coords_mtx(2, num_atoms);
    Math::DMatrix algnd_coords_mtx(2, num_atoms);
    
    for (std::size_t i = 0; i < num_atoms; i++) {
        auto& atom = atoms.getAtom(i);

        column(ref_coords_mtx, i) = ref_coords[i];
        column(algnd_coords_mtx, i) = get2DCoordinates(atom);
    }

    Math::KabschAlgorithm<double> kabsch_algo;
     
    if (!kabsch_algo.align(algnd_coords_mtx, ref_coords_mtx))
        return false;

    Math::Matrix3D xform1 = kabsch_algo.getTransform();
    auto error1 = calcError(ref_coords_mtx, algnd_coords_mtx, xform1);

    for (std::size_t i = 0; i < num_atoms; i++)
        algnd_coords_mtx(0, i) = -algnd_coords_mtx(0, i);

    if (!kabsch_algo.align(algnd_coords_mtx, ref_coords_mtx))
        return false;

    Math::Matrix3D xform2 = kabsch_algo.getTransform();

    if (calcError(ref_coords_mtx, algnd_coords_mtx, xform2) < error1) {
        xform2(0, 0) = -xform2(0, 0);
        xform2(1, 0) = -xform2(1, 0);

        if (fix_bond_stereo)
            flipBondStereo(molgraph);
    
        transform2DCoordinates(molgraph, xform2);

    } else
        transform2DCoordinates(molgraph, xform1);

    return true;
}

bool Chem::align2DCoordinates(MolecularGraph& molgraph, const AtomMapping& ref_atom_mpg, bool fix_bond_stereo)
{
    auto num_ref_atoms = ref_atom_mpg.getSize();
    
    if (num_ref_atoms == 0)
        return false;
    
    Math::DMatrix ref_coords_mtx(2, num_ref_atoms);
    Math::DMatrix algnd_coords_mtx(2, num_ref_atoms);
    std::size_t i = 0;
    
    for (auto [mg_atom, ref_atom] : ref_atom_mpg) {
        if (!mg_atom)
            return false;

        if (!ref_atom)
            return false;
        
        column(ref_coords_mtx, i) = get2DCoordinates(*ref_atom);
        column(algnd_coords_mtx, i++) = get2DCoordinates(*mg_atom);
    }

    Math::KabschAlgorithm<double> kabsch_algo;
     
    if (!kabsch_algo.align(algnd_coords_mtx, ref_coords_mtx))
        return false;

    Math::Matrix3D xform1 = kabsch_algo.getTransform();
    auto error1 = calcError(ref_coords_mtx, algnd_coords_mtx, xform1);
   
    for (i = 0; i < num_ref_atoms; i++)
        algnd_coords_mtx(0, i) = -algnd_coords_mtx(0, i);
  
    if (!kabsch_algo.align(algnd_coords_mtx, ref_coords_mtx))
        return false;

    Math::Matrix3D xform2 = kabsch_algo.getTransform();

    if (calcError(ref_coords_mtx, algnd_coords_mtx, xform2) < error1) {
        xform2(0, 0) = -xform2(0, 0);
        xform2(1, 0) = -xform2(1, 0);

        if (fix_bond_stereo)
            flipBondStereo(molgraph);
    
        transform2DCoordinates(molgraph, xform2);

    } else
        transform2DCoordinates(molgraph, xform1);

    return true;
}

bool Chem::align2DCoordinates(MolecularGraph& molgraph, const MolecularGraph& ref_molgraph, bool use_mcss, bool fix_bond_stereo)
{
    typedef MatchExpression<MolecularGraph> MolGraphMatchExpression;
    
    static const DefAtomMatchExpression::SharedPointer  DEF_ATOM_MATCH_EXPR(new DefAtomMatchExpression());
    static const DefBondMatchExpression::SharedPointer  DEF_BOND_MATCH_EXPR(new DefBondMatchExpression());
    static const MolGraphMatchExpression::SharedPointer DEF_MOLGRAPH_MATCH_EXPR(new MolGraphMatchExpression());
        
    auto num_ref_mg_atoms = ref_molgraph.getNumAtoms();

    if (num_ref_mg_atoms == 0)
        return false;

    Math::KabschAlgorithm<double> kabsch_algo;
    Math::Matrix3D best_xform;
    auto best_error = -1.0;
    bool flipped = false;
    
    if (use_mcss) {
        CommonConnectedSubstructureSearch sub_search(ref_molgraph);

        sub_search.setAtomMatchExpressionFunction([](const Atom& atom) -> auto& {
            if (hasMatchExpression(atom))
                return getMatchExpression(atom);

            return DEF_ATOM_MATCH_EXPR;
        });
        sub_search.setBondMatchExpressionFunction([](const Bond& bond) -> auto& {
            if (hasMatchExpression(bond))
                return getMatchExpression(bond);

            return DEF_BOND_MATCH_EXPR;
        });
        sub_search.setMolecularGraphMatchExpressionFunction([](const MolecularGraph& molgraph) -> auto& {
            if (hasMatchExpression(molgraph))
                return getMatchExpression(molgraph);

            return DEF_MOLGRAPH_MATCH_EXPR;
        });

        if (!sub_search.findMaxMappings(molgraph))
            return false;

        Math::DMatrix ref_coords_mtx;
        Math::DMatrix algnd_coords_mtx;

        for (auto& mg_match : sub_search) {
            auto num_mpd_atoms = mg_match.getAtomMapping().getSize();

            if (num_mpd_atoms < 2)
                continue;

            ref_coords_mtx.resize(2, num_mpd_atoms, false);
            algnd_coords_mtx.resize(2, num_mpd_atoms, false);

            std::size_t i = 0;

            for (auto [ref_atom, mg_atom] : mg_match.getAtomMapping()) {
                column(ref_coords_mtx, i) = get2DCoordinates(*ref_atom);
                column(algnd_coords_mtx, i++) = get2DCoordinates(*mg_atom);
            }

            if (!kabsch_algo.align(algnd_coords_mtx, ref_coords_mtx))
                return false;

            Math::Matrix3D xform = kabsch_algo.getTransform();
            auto error = calcError(ref_coords_mtx, algnd_coords_mtx, xform);

            if ((best_error < 0) || (error < best_error)) {
                best_error = error;
                best_xform = xform;
                flipped = false;
            }

            for (i = 0; i < num_mpd_atoms; i++)
                algnd_coords_mtx(0, i) = -algnd_coords_mtx(0, i);

            if (!kabsch_algo.align(algnd_coords_mtx, ref_coords_mtx))
                return false;

            xform = kabsch_algo.getTransform();
            error = calcError(ref_coords_mtx, algnd_coords_mtx, xform);

            if (error < best_error) {
                best_error = error;
                best_xform = xform;
                flipped = true;
            }
        }
        
    } else {
        SubstructureSearch sub_search(ref_molgraph);

        sub_search.setAtomMatchExpressionFunction([](const Atom& atom) -> auto& {
            if (hasMatchExpression(atom))
                return getMatchExpression(atom);

            return DEF_ATOM_MATCH_EXPR;
        });
        sub_search.setBondMatchExpressionFunction([](const Bond& bond) -> auto& {
            if (hasMatchExpression(bond))
                return getMatchExpression(bond);

            return DEF_BOND_MATCH_EXPR;
        });
        sub_search.setMolecularGraphMatchExpressionFunction([](const MolecularGraph& molgraph) -> auto& {
            if (hasMatchExpression(molgraph))
                return getMatchExpression(molgraph);

            return DEF_MOLGRAPH_MATCH_EXPR;
        });

        if (!sub_search.findMappings(molgraph))
            return false;

        Math::DMatrix ref_coords_mtx(2, num_ref_mg_atoms);
        Math::DMatrix algnd_coords_mtx(2, num_ref_mg_atoms);

        for (auto& mg_match : sub_search) {
            std::size_t i = 0;

            for (auto [ref_atom, mg_atom] : mg_match.getAtomMapping()) {
                column(ref_coords_mtx, i) = get2DCoordinates(*ref_atom);
                column(algnd_coords_mtx, i++) = get2DCoordinates(*mg_atom);
            }

            if (!kabsch_algo.align(algnd_coords_mtx, ref_coords_mtx))
                return false;

            Math::Matrix3D xform = kabsch_algo.getTransform();
            auto error = calcError(ref_coords_mtx, algnd_coords_mtx, xform);

            if ((best_error < 0) || (error < best_error)) {
                best_error = error;
                best_xform = xform;
                flipped = false;
            }

            for (i = 0; i < num_ref_mg_atoms; i++)
                algnd_coords_mtx(0, i) = -algnd_coords_mtx(0, i);

            if (!kabsch_algo.align(algnd_coords_mtx, ref_coords_mtx))
                return false;

            xform = kabsch_algo.getTransform();
            error = calcError(ref_coords_mtx, algnd_coords_mtx, xform);

            if (error < best_error) {
                best_error = error;
                best_xform = xform;
                flipped = true;
            }
        }
    }

    if (best_error < 0.0)
        return false;
    
    if (flipped) {
        best_xform(0, 0) = -best_xform(0, 0);
        best_xform(1, 0) = -best_xform(1, 0);

        if (fix_bond_stereo)
            flipBondStereo(molgraph);
    }

    transform2DCoordinates(molgraph, best_xform);
    return true;
}

bool Chem::align2DCoordinates(MolecularGraph& molgraph, const MolecularGraph& ref_molgraph, const MolecularGraph& ref_substr_ptn, bool fix_bond_stereo)
{
    auto num_ptn_atoms = ref_substr_ptn.getNumAtoms();

    if (num_ptn_atoms == 0)
        return false;
 
    SubstructureSearch sub_search1(ref_substr_ptn);

    if (!sub_search1.findMappings(molgraph))
        return false;

    SubstructureSearch sub_search2(ref_substr_ptn);
    
    if (!sub_search2.findMappings(ref_molgraph))
        return false;

    Math::KabschAlgorithm<double> kabsch_algo;
    Math::DMatrix ref_coords_mtx(2, num_ptn_atoms);
    Math::DMatrix algnd_coords_mtx(2, num_ptn_atoms);
    Math::Matrix3D best_xform;
    auto best_error = -1.0;
    bool flipped = false;

    for (auto& mg_match : sub_search1) {
        for (auto& ref_mg_match : sub_search2) {
            std::size_t i = 0;

            for (auto [ptn_atom, mg_atom] : mg_match.getAtomMapping()) {
                auto ref_atom = ref_mg_match.getAtomMapping()[ptn_atom];

                column(ref_coords_mtx, i) = get2DCoordinates(*ref_atom);
                column(algnd_coords_mtx, i++) = get2DCoordinates(*mg_atom);
            }

            if (!kabsch_algo.align(algnd_coords_mtx, ref_coords_mtx))
                return false;

            Math::Matrix3D xform = kabsch_algo.getTransform();
            auto error = calcError(ref_coords_mtx, algnd_coords_mtx, xform);

            if ((best_error < 0) || (error < best_error)) {
                best_error = error;
                best_xform = xform;
                flipped = false;
            }

            for (i = 0; i < num_ptn_atoms; i++)
                algnd_coords_mtx(0, i) = -algnd_coords_mtx(0, i);
  
            if (!kabsch_algo.align(algnd_coords_mtx, ref_coords_mtx))
                return false;

            xform = kabsch_algo.getTransform();
            error = calcError(ref_coords_mtx, algnd_coords_mtx, xform);
            
            if (error < best_error) {
                best_error = error;
                best_xform = xform;
                flipped = true;
            }
        }
    }

    if (flipped) {
        best_xform(0, 0) = -best_xform(0, 0);
        best_xform(1, 0) = -best_xform(1, 0);

        if (fix_bond_stereo)
            flipBondStereo(molgraph);
    }

    transform2DCoordinates(molgraph, best_xform);
    return true;
}
