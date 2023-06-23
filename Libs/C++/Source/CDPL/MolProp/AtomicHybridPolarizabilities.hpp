/* 
 * AtomicHybridPolarizabilities.hpp 
 *
 * Atomic hybrid polarizabilities used for the calculation of 
 * the mean molecular polarizability and effective atom polarizability 
 * (K. J. Miller, J. Am. Chem. Soc. 1990, 112, 8533-8542))
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


#ifndef CDPL_MOLPROP_ATOMICHYBRIDPOLARIZABILITIES_HPP
#define CDPL_MOLPROP_ATOMICHYBRIDPOLARIZABILITIES_HPP


namespace CDPL 
{

    namespace MolProp 
    {

        namespace AtomicHybridPolarizability
        {

            const double H          = 0.387;

            const double F          = 0.296;
            const double Cl         = 2.315;
            const double Br         = 3.013;
            const double I          = 5.415;

            const double CTE        = 1.061;
            const double CTR        = 1.352;
            const double CBR        = 1.896;
            const double CDI        = 1.283;
            const double C_DEFAULT  = (CTE + CTR + CBR + CDI) * 0.25;

            const double NTE        = 0.964;
            const double NTR2       = 1.030;
            const double NPI2       = 1.090;
            const double NDI        = 0.956;
            const double N_DEFAULT  = (NTE + NTR2 + NPI2 + NDI) * 0.25;

            const double OTE        = 0.637;
            const double OTR4       = 0.569;
            const double OPI2       = 0.274;
            const double O_DEFAULT  = (OTE + OTR4 + OPI2) / 3.0;

            const double STE        = 3.000;
            const double STR4       = 3.729;
            const double SPI2       = 2.700;
            const double S_DEFAULT  = STE;

            const double PTE        = 1.538;

            const double DEFAULT    = (H + F + Cl + Br + I + C_DEFAULT 
                                       + N_DEFAULT + O_DEFAULT + S_DEFAULT + PTE) / 10.0;
        }
    }
}

#endif // CDPL_MOLPROP_ATOMICHYBRIDPOLARIZABILITIES_HPP
