/* 
 * QueryTwoPointPharmacophore.hpp 
 *
 * This file is part of the Pharmical Data Processing Toolkit
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


#ifndef CDPL_PHARM_QUERYTWOPOINTPHARMACOPHORE_HPP
#define CDPL_PHARM_QUERYTWOPOINTPHARMACOPHORE_HPP

#include "CDPL/Pharm/TwoPointPharmacophore.hpp"


namespace CDPL
{

    namespace Pharm
    {

        class QueryTwoPointPharmacophore : public TwoPointPharmacophore
        {

          public:
            QueryTwoPointPharmacophore(const Feature& ftr1, const Feature& ftr2);

            double getFeature1Tolerance() const
            {
                return ftr1Tol;
            }

            double getFeature2Tolerance() const
            {
                return ftr2Tol;
            }

          private:
            double ftr1Tol;
            double ftr2Tol;
        };
    } // namespace Pharm
} // namespace CDPL

#endif // CDPL_PHARM_QUERYTWOPOINTPHARMACOPHORE_HPP
