/* 
 * PMLFeatureContainerWriter.hpp 
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
 * \brief Definition of the class CDPL::Pharm::PMLFeatureContainerWriter.
 */

#ifndef CDPL_PHARM_PMLFEATURECONTAINERWRITER_HPP
#define CDPL_PHARM_PMLFEATURECONTAINERWRITER_HPP

#include <memory>
#include <iosfwd>

#include "CDPL/Pharm/APIPrefix.hpp"
#include "CDPL/Base/DataWriter.hpp"


namespace CDPL
{

    namespace Pharm
    {

        class PMLDataWriter;
        class FeatureContainer;

        /**
         * \brief A writer for feature container data in the native I/O format of <em>LigandScout</em>.
         */
        class CDPL_PHARM_API PMLFeatureContainerWriter : public Base::DataWriter<FeatureContainer>
        {

          public:
            /**
             * \brief Constructs a \c %PMLFeatureContainerWriter instance that will write data of feature containers to the output
             *        stream \a os.
             * \param os The output stream to write to.
             */
            PMLFeatureContainerWriter(std::ostream& os);

            /**
             * \brief Destructor.
             */
            ~PMLFeatureContainerWriter();

            /**
             * \brief Writes data of the feature container \a cntnr to the output stream specified in the constructor.
             * \param cntnr The feature container to write.
             * \return A reference to itself.
             */
            Base::DataWriter<FeatureContainer>& write(const FeatureContainer& cntnr);

            void close();

            operator const void*() const;

            bool operator!() const;

          private:
            typedef std::auto_ptr<PMLDataWriter> PMLDataWriterPtr;

            PMLFeatureContainerWriter(const PMLFeatureContainerWriter&);

            PMLFeatureContainerWriter& operator=(const PMLFeatureContainerWriter&);

            std::ostream&    output;
            bool             state;
            PMLDataWriterPtr writer;
        };
    } // namespace Pharm
} // namespace CDPL

#endif // CDPL_PHARM_PMLFEATURECONTAINERWRITER_HPP
