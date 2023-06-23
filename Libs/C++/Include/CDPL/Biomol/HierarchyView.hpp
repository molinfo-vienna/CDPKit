/* 
 * HierarchyView.hpp 
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
 * \brief Definition of the class CDPL::Biomol::HierarchyView.
 */

#ifndef CDPL_BIOMOL_HIERARCHYVIEW_HPP
#define CDPL_BIOMOL_HIERARCHYVIEW_HPP

#include <cstddef>
#include <vector>
#include <unordered_map>
#include <mutex>
#include <memory>

#include <boost/iterator/indirect_iterator.hpp>

#include "CDPL/Biomol/APIPrefix.hpp"
#include "CDPL/Biomol/HierarchyViewModel.hpp"
#include "CDPL/Biomol/ResidueList.hpp"


namespace CDPL 
{

    namespace Biomol
    {

		/**
		 * \brief A datastructure allowing a hierarchical view on biological macromolecules.
		 */
		class CDPL_BIOMOL_API HierarchyView
		{

			typedef std::shared_ptr<HierarchyViewModel> ModelPtr;
			typedef std::vector<ModelPtr> ModelList;

		  public:
			/**	
			 * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %HierarchyView instances.
			 */
			typedef std::shared_ptr<HierarchyView> SharedPointer;

			typedef boost::indirect_iterator<ModelList::const_iterator, const HierarchyViewModel> ConstModelIterator;

			/**
			 * \brief Constructs an empty \c %HierarchyView instance.
			 */
			HierarchyView();

			/**
			 * \brief Constructs a \c %HierarchyView instance for the molecular graph \a molgraph.
			 * \param molgraph The molecular graph for which to build the hierarchy view.
			 */
			HierarchyView(const Chem::MolecularGraph& molgraph);

			const ResidueList& getResidues() const;

			std::size_t getNumModels() const;

			const HierarchyViewModel& getModel(std::size_t idx) const;

			bool hasModelWithNumber(std::size_t num) const;

			const HierarchyViewModel& getModelByNumber(std::size_t num) const;

			ConstModelIterator getModelsBegin() const;

			ConstModelIterator getModelsEnd() const;

			ConstModelIterator begin() const;

			ConstModelIterator end() const;

			/**
			 * \brief Build the hierarchy view for the molecular graph \a molgraph.
			 * \param molgraph The molecular graph for which to build the hierarchy view.
			 */
			void build(const Chem::MolecularGraph& molgraph);

		  private:
			void initModelList() const;
		
			typedef std::unordered_map<std::size_t, ModelPtr> IDToModelMap;

			const Chem::MolecularGraph* molGraph;
			mutable ResidueList         residues;
			mutable ModelList           models;
			mutable IDToModelMap        idToModelMap;
			mutable bool                initResidues;
			mutable bool                initModels;
			mutable std::mutex          initMutex;
		};
    }
}

#endif // CDPL_BIOMOL_HIERARCHYVIEW_HPP
