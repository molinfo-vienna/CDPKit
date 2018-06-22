/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * TwoPointPharmacophore.hpp 
 *
 * This file is part of the Pharmical Data Processing Toolkit
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


#ifndef CDPL_PHARM_TWOPOINTPHARMACOPHORE_HPP
#define CDPL_PHARM_TWOPOINTPHARMACOPHORE_HPP


namespace CDPL 
{

    namespace Pharm
    {

		class Feature;

		class TwoPointPharmacophore
		{

		public:
			TwoPointPharmacophore(const Feature& ftr1, const Feature& ftr2);

			TwoPointPharmacophore(unsigned int ftr1_type, unsigned int ftr2_type, double ftr_dist):
				ftr1Type(ftr1_type), ftr2Type(ftr2_type), ftrDistance(ftr_dist) {}

			unsigned int getFeature1Type() const {
				return ftr1Type;
			}

			unsigned int getFeature2Type() const {
				return ftr2Type;
			}

			double getFeatureDistance() const {
				return ftrDistance;
			}

		private:
			unsigned int ftr1Type;
			unsigned int ftr2Type;
			double       ftrDistance;
		};
    }
}

#endif // CDPL_PHARM_TWOPOINTPHARMACOPHORE_HPP
