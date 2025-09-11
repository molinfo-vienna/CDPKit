/* 
 * MHMOPiChargeCalculator.hpp 
 * 
 * Modified Hueckel Molecular Orbital calculation of various pi electron system properties
 * (according to T. Kleinöder, PhD Thesis, FAU Erlangen-Nuremberg, 2005) 
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

/**
 * \file
 * \brief Definition of class CDPL::MolProp::MHMOPiChargeCalculator.
 */

#ifndef CDPL_MOLPROP_MHMOPICHARGECALCULATOR_HPP
#define CDPL_MOLPROP_MHMOPICHARGECALCULATOR_HPP

#include <vector>
#include <cstddef>
#include <cstdint>
#include <memory>

#include "CDPL/MolProp/APIPrefix.hpp"
#include "CDPL/Chem/ElectronSystemList.hpp"
#include "CDPL/Math/Matrix.hpp"
#include "CDPL/Math/Vector.hpp"
#include "CDPL/Util/BitSet.hpp"


namespace CDPL
{

    namespace Chem
    {

        class MolecularGraph;
        class Bond;
    } // namespace Chem

    namespace MolProp
    {

        class PEOESigmaChargeCalculator;
        
        /**
         * \brief MHMOPiChargeCalculator.
         * \see [\ref MHMO]
         */
        class CDPL_MOLPROP_API MHMOPiChargeCalculator
        {

          public:
            typedef std::shared_ptr<MHMOPiChargeCalculator> SharedPointer;

            MHMOPiChargeCalculator();
            
            MHMOPiChargeCalculator(const Chem::MolecularGraph& molgraph);

            MHMOPiChargeCalculator(const Chem::ElectronSystemList& pi_sys_list, const Chem::MolecularGraph& molgraph);

            MHMOPiChargeCalculator(const MHMOPiChargeCalculator&) = delete;

            ~MHMOPiChargeCalculator();
      
            MHMOPiChargeCalculator& operator=(const MHMOPiChargeCalculator&) = delete;

            void localizedPiBonds(bool localized);

            bool localizedPiBonds() const;

            void calculate(const Chem::MolecularGraph& molgraph);

            void calculate(const Chem::ElectronSystemList& pi_sys_list, const Chem::MolecularGraph& molgraph);

            double getElectronDensity(std::size_t atom_idx) const;

            double getCharge(std::size_t atom_idx) const;

            double getBondOrder(std::size_t bond_idx) const;

            double getEnergy() const;

          private:
            void initAtomPiSysCounts(const Chem::ElectronSystemList& pi_sys_list, const Chem::MolecularGraph& molgraph);
            void initAtomFreeElecCounts(const Chem::ElectronSystemList& pi_sys_list, const Chem::MolecularGraph& molgraph);

            void calcForPiSys(const Chem::ElectronSystem& pi_sys, const Chem::MolecularGraph& molgraph);

            void initAtomPiElecCounts(const Chem::ElectronSystem& pi_sys, const Chem::MolecularGraph& molgraph);

            std::size_t getNumBonds(const Chem::Atom& atom, const Chem::ElectronSystem& pi_sys,
                                    const Chem::MolecularGraph& molgraph) const;

            void getInvolvedBonds(const Chem::ElectronSystem& pi_sys, const Chem::MolecularGraph& molgraph);
            void initHueckelMatrix(const Chem::ElectronSystem& pi_sys, const Chem::MolecularGraph& molgraph);

            void   calcSigmaCharges(const Chem::MolecularGraph& molgraph);
            double getAlpha(const Chem::Atom& atom, const Chem::ElectronSystem& pi_sys, const Chem::MolecularGraph& molgraph) const;
            double getAlphaCorrection(const Chem::Atom& atom, const Chem::ElectronSystem& pi_sys, const Chem::MolecularGraph& molgraph) const;
            double getBeta(const Chem::Bond& bond, const Chem::ElectronSystem& pi_sys, const Chem::MolecularGraph& molgraph) const;

            std::uint64_t getAtomID(const Chem::Atom& atom, const Chem::ElectronSystem& pi_sys, const Chem::MolecularGraph& molgraph) const;
            std::uint64_t getBondID(const Chem::Bond& bond, const Chem::ElectronSystem& pi_sys, const Chem::MolecularGraph& molgraph) const;

            bool diagHueckelMatrix();
            void distElectrons(const Chem::ElectronSystem& pi_sys);
            void updateEnergy();
            void updateAtomElecDensitiesAndCharges(const Chem::ElectronSystem& pi_sys, const Chem::MolecularGraph& molgraph);
            void updateBondElecDensities(const Chem::ElectronSystem& pi_sys, const Chem::MolecularGraph& molgraph);

            double calcElecDensity(std::size_t i, std::size_t j) const;

            struct MODescr
            {

                double energy;
                double coeffVecIndex;
                double elecCount;
            };

            typedef Math::Matrix<double>                       Matrix;
            typedef Math::Vector<double>                       Vector;
            typedef std::vector<const Chem::Bond*>             BondList;
            typedef std::vector<std::size_t>                   CountsArray;
            typedef std::vector<double>                        DoubleArray;
            typedef std::vector<MODescr>                       MODescrArray;
            typedef std::vector<MODescr*>                      MODescrPtrArray;
            typedef std::unique_ptr<PEOESigmaChargeCalculator> PEOECalculatorPtr;

            Matrix            hueckelMatrix;
            Matrix            hmEigenVectors;
            Vector            hmEigenValues;
            BondList          piSysBonds;
            CountsArray       atomPiSysCounts;
            CountsArray       atomFreeElecCounts;
            CountsArray       atomPiElecCounts;
            Util::BitSet      specialAtomTypes;
            MODescrArray      moDescriptors;
            MODescrPtrArray   moDescriptorPtrs;
            bool              locPiBonds;
            DoubleArray       atomElecDensities;
            DoubleArray       bondElecDensities;
            DoubleArray       atomPiCharges;
            double            energy;
            PEOECalculatorPtr peoeCalculatorPtr;
        };
    } // namespace MolProp
} // namespace CDPL

#endif // CDPL_MOLPROP_MHMOPICHARGECALCULATOR_HPP
