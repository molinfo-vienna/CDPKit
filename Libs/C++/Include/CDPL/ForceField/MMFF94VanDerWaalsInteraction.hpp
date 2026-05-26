/* 
 * MMFF94VanDerWaalsInteraction.hpp 
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
 * \brief Definition of class CDPL::ForceField::MMFF94VanDerWaalsInteraction.
 */

#ifndef CDPL_FORCEFIELD_MMFF94VANDERWAALSINTERACTION_HPP
#define CDPL_FORCEFIELD_MMFF94VANDERWAALSINTERACTION_HPP

#include <cstddef>
#include <cmath>


namespace CDPL
{

    namespace ForceField
    {

        /**
         * \brief A single MMFF94 Van der Waals interaction between two non-bonded atoms.
         *
         * The MMFF94 Van der Waals form is a buffered 14-7 potential
         * \f$ E_{vdW} = \varepsilon_{IJ} \left( \frac{1.07 R_{IJ}}{r + 0.07 R_{IJ}} \right)^7 \left( \frac{1.12 R_{IJ}^7}{r^7 + 0.12 R_{IJ}^7} - 2 \right) \f$
         * with combined parameters \f$ R_{IJ} \f$ and \f$ \varepsilon_{IJ} \f$. The constructor performs the
         * MMFF94 combining rules using the per-atom polarizabilities, effective electron numbers and the
         * MMFF94-defined "factor A", "factor G", buffered combining "factor B" and donor/acceptor scaling
         * factors; the resulting \f$ R_{IJ} \f$, \f$ \varepsilon_{IJ} \f$ and the precomputed \f$ R_{IJ}^7 \f$
         * are stored.
         */
        class MMFF94VanDerWaalsInteraction
        {

          public:
            /** \brief MMFF94 hydrogen-bond donor/acceptor classification of an atom (for the donor/acceptor scaling of the vdW combining rule). */
            enum HDonorAcceptorType
            {

                /** \brief The atom is neither a hydrogen-bond donor nor an acceptor. */
                NONE,
                /** \brief The atom is a hydrogen-bond donor. */
                DONOR,
                /** \brief The atom is a hydrogen-bond acceptor. */
                ACCEPTOR
            };

            /**
             * \brief Constructs the Van der Waals interaction record and pre-computes the combined MMFF94 parameters.
             * \param atom1_idx The zero-based index of the first atom.
             * \param atom2_idx The zero-based index of the second atom.
             * \param atom_pol1 The atomic polarizability \f$ \alpha_i \f$ of the first atom.
             * \param eff_el_num1 The effective electron number \f$ N_i \f$ of the first atom.
             * \param fact_a1 The MMFF94 "factor A" of the first atom (used in \f$ R_I = A_i \alpha_i^p \f$).
             * \param fact_g1 The MMFF94 "factor G" of the first atom (well-depth coefficient).
             * \param don_acc_type1 The hydrogen-bond donor/acceptor classification of the first atom.
             * \param atom_pol2 The atomic polarizability \f$ \alpha_j \f$ of the second atom.
             * \param eff_el_num2 The effective electron number \f$ N_j \f$ of the second atom.
             * \param fact_a2 The MMFF94 "factor A" of the second atom.
             * \param fact_g2 The MMFF94 "factor G" of the second atom.
             * \param don_acc_type2 The hydrogen-bond donor/acceptor classification of the second atom.
             * \param expo The MMFF94 polarizability exponent \e p.
             * \param fact_b The MMFF94 combining "factor B".
             * \param beta The MMFF94 combining factor \f$ \beta \f$.
             * \param fact_darad The donor-acceptor scaling factor applied to \f$ R_{IJ} \f$.
             * \param fact_daeps The donor-acceptor scaling factor applied to \f$ \varepsilon_{IJ} \f$.
             */
            MMFF94VanDerWaalsInteraction(std::size_t atom1_idx, std::size_t atom2_idx,
                                         double atom_pol1, double eff_el_num1, double fact_a1, double fact_g1,
                                         HDonorAcceptorType don_acc_type1, double atom_pol2, double eff_el_num2,
                                         double fact_a2, double fact_g2, HDonorAcceptorType don_acc_type2,
                                         double expo, double fact_b, double beta, double fact_darad, double fact_daeps):
                atom1Idx(atom1_idx),
                atom2Idx(atom2_idx)
            {

                bool have_don     = false;
                bool have_don_acc = false;

                switch (don_acc_type1) {

                    case DONOR:
                        have_don     = true;
                        have_don_acc = (don_acc_type2 == ACCEPTOR);
                        break;

                    case ACCEPTOR:
                        have_don_acc = (don_acc_type2 == DONOR);
                        have_don     = have_don_acc;
                        break;

                    default:
                        have_don = (don_acc_type2 == DONOR);
                        break;
                }

                double rII = fact_a1 * std::pow(atom_pol1, expo);
                double rJJ = fact_a2 * std::pow(atom_pol2, expo);
                double gIJ = (rII - rJJ) / (rII + rJJ);

                rIJ = 0.5 * (rII + rJJ);

                if (!have_don)
                    rIJ += rIJ * fact_b * (1.0 - std::exp(-beta * gIJ * gIJ));

                eIJ = 181.16 * fact_g1 * fact_g2 * atom_pol1 * atom_pol2 / (std::pow(atom_pol1 / eff_el_num1, 0.5) + std::pow(atom_pol2 / eff_el_num2, 0.5)) * std::pow(rIJ, -6.0);

                if (have_don_acc) {
                    rIJ *= fact_darad;
                    eIJ *= fact_daeps;
                }

                rIJPow7 = std::pow(rIJ, 7.0);
            }

            /**
             * \brief Returns the zero-based index of the first atom.
             * \return The first atom index.
             */
            std::size_t getAtom1Index() const
            {
                return atom1Idx;
            }

            /**
             * \brief Returns the zero-based index of the second atom.
             * \return The second atom index.
             */
            std::size_t getAtom2Index() const
            {
                return atom2Idx;
            }

            /**
             * \brief Returns the combined well-depth parameter \f$ \varepsilon_{IJ} \f$.
             * \return The well-depth \f$ \varepsilon_{IJ} \f$ (in kcal/mol).
             */
            double getEIJ() const
            {
                return eIJ;
            }

            /**
             * \brief Returns the combined minimum-energy distance \f$ R_{IJ} \f$.
             * \return The minimum-energy distance \f$ R_{IJ} \f$ (in &Aring;).
             */
            double getRIJ() const
            {
                return rIJ;
            }

            /**
             * \brief Returns the pre-computed seventh power of \f$ R_{IJ} \f$ (used by the calculator to avoid recomputation).
             * \return The value \f$ R_{IJ}^7 \f$.
             */
            double getRIJPow7() const
            {
                return rIJPow7;
            }

          private:
            std::size_t atom1Idx;
            std::size_t atom2Idx;
            double      eIJ;
            double      rIJ;
            double      rIJPow7;
        };
    } // namespace ForceField
} // namespace CDPL

#endif // CDPL_FORCEFIELD_MMFF94VANDERWAALSINTERACTION_HPP
