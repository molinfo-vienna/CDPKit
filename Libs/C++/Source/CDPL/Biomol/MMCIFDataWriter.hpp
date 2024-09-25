/* 
 * MMCIFDataWriter.hpp 
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


#ifndef CDPL_BIOMOL_MMCIFDATAWRITER_HPP
#define CDPL_BIOMOL_MMCIFDATAWRITER_HPP

#include <iosfwd>
#include <unordered_set>
#include <vector>

#include "CDPL/Biomol/MMCIFData.hpp"
#include "CDPL/Biomol/ResidueDictionary.hpp"
#include "CDPL/Biomol/MMCIFDataProcessingFunction.hpp"

#include "CDPL/Internal/StringUtilities.hpp"


namespace CDPL
{

    namespace Base
    {

        class DataIOBase;
    }

    namespace Biomol
    {

        class MMCIFDataWriter
        {

          public:
            MMCIFDataWriter(const Base::DataIOBase& io_base):
                ioBase(io_base), numOutDataBlocks(0) {}

            bool writeMolecularGraph(std::ostream& os, const Chem::MolecularGraph& molgraph);

          private:
            typedef std::unordered_set<const std::string*,
                                       Internal::StringPtrHashFunc,
                                       Internal::StringPtrCmpFunc>  AtomIdSet;
            
            void init(std::ostream& os);

            bool genMacromoleculeData(const Chem::MolecularGraph& molgraph);
            bool genAtomSiteData(const Chem::MolecularGraph& molgraph);
    
            void genChemCompData(const Chem::MolecularGraph& molgraph);
            void genChemCompAtomsData(const Chem::MolecularGraph& molgraph, const std::string& comp_id);
            void genChemCompBondsData(const Chem::MolecularGraph& molgraph, const std::string& comp_id);

            std::string getChemCompId(const Chem::MolecularGraph& molgraph);
            
            void setDataBlockId(const Chem::MolecularGraph& molgraph);

            const std::string& createUniqueAtomId(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph,
                                                  const AtomIdSet& id_set, std::string& id) const;

            typedef ResidueDictionary::SharedPointer ResDictPointer;
            typedef std::vector<const Chem::Atom*>   AtomList;

            const Base::DataIOBase&     ioBase;
            ResDictPointer              resDictionary;
            MMCIFDataProcessingFunction dataPostprocFunc;
            bool                        strictErrorChecking;
            MMCIFData                   mmCIFData;
            std::size_t                 numOutDataBlocks;
            bool                        outputAsChemComp;
            AtomList                    atomSites;
            std::string                 tmpString;
            AtomIdSet                   chemCompAtomIds[2];
        };
    } // namespace Biomol
} // namespace CDPL

#endif // CDPL_BIOMOL_MMCIFDATAWRITER_HPP
