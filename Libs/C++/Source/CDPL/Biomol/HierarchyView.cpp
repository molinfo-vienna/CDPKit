/* 
 * HierarchyView.cpp 
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

#include "CDPL/Biomol/HierarchyView.hpp"
#include "CDPL/Biomol/AtomFunctions.hpp"
#include "CDPL/Biomol/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Base/Exceptions.hpp"


using namespace CDPL; 


Biomol::HierarchyView::HierarchyView(): molGraph(0), initResidues(false), initModels(false) {}

Biomol::HierarchyView::HierarchyView(const Chem::MolecularGraph& molgraph)
{
    build(molgraph);
}

void Biomol::HierarchyView::build(const Chem::MolecularGraph& molgraph)
{
    molGraph = &molgraph;
    initResidues = true;
    initModels = true;
}

const Biomol::ResidueList& Biomol::HierarchyView::getResidues() const
{
    std::lock_guard<std::mutex> lock(initMutex);

    if (!initResidues)
		return residues;

    if (molGraph)
		residues.extract(*molGraph);

    initResidues = false;

    return residues;
}

std::size_t Biomol::HierarchyView::getNumModels() const
{
	initModelList();

	return models.size();
}

const Biomol::HierarchyViewModel& Biomol::HierarchyView::getModel(std::size_t idx) const
{
	initModelList();

	if (idx >= models.size())
		throw Base::IndexError("HierarchyView: model index out of bounds");

	return *models[idx];
}

bool Biomol::HierarchyView::hasModelWithNumber(std::size_t num) const
{
	initModelList();

	return (idToModelMap.find(num) != idToModelMap.end());
}

const Biomol::HierarchyViewModel& Biomol::HierarchyView::getModelByNumber(std::size_t num) const
{
	initModelList();

	IDToModelMap::const_iterator it = idToModelMap.find(num);

	if (it != idToModelMap.end())
		return *it->second;

	throw Base::ItemNotFound("HierarchyView: model with specified number not found");
}

Biomol::HierarchyView::ConstModelIterator Biomol::HierarchyView::getModelsBegin() const
{
	initModelList();

	return ConstModelIterator(models.begin());
}

Biomol::HierarchyView::ConstModelIterator Biomol::HierarchyView::getModelsEnd() const
{
	initModelList();

	return ConstModelIterator(models.end());
}

Biomol::HierarchyView::ConstModelIterator Biomol::HierarchyView::begin() const
{
	initModelList();

	return ConstModelIterator(models.begin());
}

Biomol::HierarchyView::ConstModelIterator Biomol::HierarchyView::end() const
{
	initModelList();

	return ConstModelIterator(models.end());
}

void Biomol::HierarchyView::initModelList() const
{
    std::lock_guard<std::mutex> lock(initMutex);

    if (!initModels)
		return;

	models.clear();
	idToModelMap.clear();

	if (!molGraph) {
		initModels = false;
		return;
	}

	using namespace Chem;

	for (MolecularGraph::ConstAtomIterator a_it = molGraph->getAtomsBegin(), a_end = molGraph->getAtomsEnd(); a_it != a_end; ++a_it) {
		const Atom& atom = *a_it;
		std::size_t model_no = getModelNumber(atom);

		IDToModelMap::iterator m_it = idToModelMap.find(model_no);

		if (m_it != idToModelMap.end()) {
			m_it->second->addAtom(atom);
			continue;
		}

		ModelPtr model_ptr(new HierarchyViewModel());

		setModelNumber(*model_ptr, model_no);

		model_ptr->addAtom(atom);

		models.push_back(model_ptr);
		idToModelMap.insert(IDToModelMap::value_type(model_no, model_ptr));
	}

	for (ModelList::iterator m_it = models.begin(), m_end = models.end(); m_it != m_end; ++m_it) {
		HierarchyViewModel& model = **m_it;

		for (std::size_t i = 0, num_atoms = model.getNumAtoms(); i < num_atoms; i++) {
			const Atom& atom = model.getAtom(i);
			Atom::ConstAtomIterator a_it = atom.getAtomsBegin();

			for (Atom::ConstBondIterator b_it = atom.getBondsBegin(), b_end = atom.getBondsEnd(); b_it != b_end; ++b_it, ++a_it) {
				const Bond& bond = *b_it;

				if (model.containsBond(bond))
					continue;

				if (!model.containsAtom(*a_it))
					continue;

				if (!molGraph->containsBond(bond))
					continue;

				model.addBond(bond);
			}
		}
	}

    initModels = false;
}
