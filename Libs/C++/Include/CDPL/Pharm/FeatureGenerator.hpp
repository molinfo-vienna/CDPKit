/* 
 * FeatureGenerator.hpp 
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
 * \brief Definition of class CDPL::Pharm::FeatureGenerator.
 */

#ifndef CDPL_PHARM_FEATUREGENERATOR_HPP
#define CDPL_PHARM_FEATUREGENERATOR_HPP

#include <memory>

#include "CDPL/Pharm/APIPrefix.hpp"
#include "CDPL/Chem/Atom3DCoordinatesFunction.hpp"
#include "CDPL/Math/Vector.hpp"


namespace CDPL
{

    namespace Chem
    {

        class MolecularGraph;
    };

    namespace Pharm
    {

        class Pharmacophore;

        /**
         * \brief Abstract base class for generators that perceive one type of pharmacophore feature
         *        (e.g. an aromatic ring or H-bond donor) and append the perceived features to a Pharm::Pharmacophore.
         */
        class CDPL_PHARM_API FeatureGenerator
        {

          public:
            /** \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %FeatureGenerator instances. */
            typedef std::shared_ptr<FeatureGenerator> SharedPointer;

            /**
             * \brief Constructs the \c %FeatureGenerator instance.
             */
            FeatureGenerator();

            /**
             * \brief Virtual destructor.
             */
            virtual ~FeatureGenerator() {}

            /**
             * \brief Specifies a function for the retrieval of atom 3D-coordinates.
             * \param func The atom 3D-coordinates function.
             */
            virtual void setAtom3DCoordinatesFunction(const Chem::Atom3DCoordinatesFunction& func);

            /**
             * \brief Returns the function that was registered for the retrieval of atom 3D-coordinates.
             * \return A \c const reference to the registered atom 3D-coordinates function.
             */
            const Chem::Atom3DCoordinatesFunction& getAtom3DCoordinatesFunction() const;

            /**
             * \brief Perceives pharmacophore features and adds them to the pharmacophore \a pharm.
             * \param molgraph The molecular graph for which to perceive the features.
             * \param pharm The output pharmacophore where to add the generated features.
             */
            virtual void generate(const Chem::MolecularGraph& molgraph, Pharmacophore& pharm) = 0;

            /**
             * \brief Creates a deep copy of the \c %FeatureGenerator instance.
             * \return A smart pointer to the cloned feature generator.
             */
            virtual SharedPointer clone() const = 0;

          protected:
            /**
             * \brief Constructs a copy of the \c %FeatureGenerator instance \a gen.
             * \param gen The \c %FeatureGenerator instance to copy.
             */
            FeatureGenerator(const FeatureGenerator& gen);

            /**
             * \brief Copy assignment operator.
             * \param gen The \c %FeatureGenerator instance to copy.
             * \return A reference to itself.
             */
            FeatureGenerator& operator=(const FeatureGenerator& gen);

          private:
            Chem::Atom3DCoordinatesFunction coordsFunc;
        };
    } // namespace Pharm
} // namespace CDPL

#endif // CDPL_PHARM_FEATUREGENERATOR_HPP
