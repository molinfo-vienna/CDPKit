/* 
 * BasicReaction.cpp 
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

#include <algorithm>
#include <iterator>
#include <functional>
#include <string>

#include "CDPL/Chem/BasicReaction.hpp"
#include "CDPL/Chem/ReactionRole.hpp"
#include "CDPL/Base/Exceptions.hpp"


namespace
{

    constexpr std::size_t MAX_COMPONENT_CACHE_SIZE = 100;
}


using namespace CDPL;


Chem::BasicReaction::BasicReaction(): 
    compCache(MAX_COMPONENT_CACHE_SIZE), agentsStartIdx(0), productsStartIdx(0) 
{
    compCache.setCleanupFunction(&BasicMolecule::clear);
}

Chem::BasicReaction::BasicReaction(const BasicReaction& rxn): 
    Reaction(rxn), compCache(MAX_COMPONENT_CACHE_SIZE), agentsStartIdx(0), productsStartIdx(0)
{
    compCache.setCleanupFunction(&BasicMolecule::clear);

    copyComponents(rxn);
    invokeCopyPostprocessingFunctions(rxn);
}

Chem::BasicReaction::BasicReaction(const Reaction& rxn): 
    Reaction(rxn), compCache(MAX_COMPONENT_CACHE_SIZE), agentsStartIdx(0), productsStartIdx(0)
{
    compCache.setCleanupFunction(&BasicMolecule::clear);

    copyComponents(rxn);
    invokeCopyPostprocessingFunctions(rxn);
}

Chem::BasicReaction::~BasicReaction() {}

unsigned int Chem::BasicReaction::getComponentRole(const Molecule& mol) const
{
    ComponentList::const_iterator it = std::find_if(components.begin(), components.end(), 
                                                    std::bind(std::equal_to<const Molecule*>(),
                                                              std::bind(&ComponentPtr::get, std::placeholders::_1), &mol));

    if (it == components.end())
        return ReactionRole::NONE;

    std::size_t idx = it - components.begin();

    if (idx < agentsStartIdx)
        return ReactionRole::REACTANT;

    if (idx < productsStartIdx)
        return ReactionRole::AGENT;

    return ReactionRole::PRODUCT;
}

std::size_t Chem::BasicReaction::getComponentIndex(const Molecule& mol) const
{
    ComponentList::const_iterator it = std::find_if(components.begin(), components.end(), 
                                                    std::bind(std::equal_to<const Molecule*>(),
                                                              std::bind(&ComponentPtr::get, std::placeholders::_1), &mol));

    if (it == components.end())
        throw Base::ItemNotFound("BasicReaction: molecule is not a component of this reaction");

    return (it - components.begin());
}
    
bool Chem::BasicReaction::containsComponent(const Molecule& mol) const
{
    return (std::find_if(components.begin(), components.end(), 
                         std::bind(std::equal_to<const Molecule*>(),
                                   std::bind(&ComponentPtr::get, std::placeholders::_1), &mol)) != components.end());
}

void Chem::BasicReaction::clear()
{
    clearComponents();
    clearProperties();
}
        
std::size_t Chem::BasicReaction::getNumComponents() const
{
    return components.size();
}

std::size_t Chem::BasicReaction::getNumComponents(unsigned int role) const
{
    switch (role) {

        case ReactionRole::REACTANT:
            return agentsStartIdx;

        case ReactionRole::AGENT:
            return (productsStartIdx - agentsStartIdx);

        case ReactionRole::PRODUCT:
            return (components.size() - productsStartIdx);
    
        default:
            throw Base::ValueError("BasicReaction: invalid reaction role");
    }
}

Chem::BasicReaction::ConstComponentIterator Chem::BasicReaction::getComponentsBegin() const
{
    return components.begin();
}

Chem::BasicReaction::ConstComponentIterator Chem::BasicReaction::getComponentsEnd() const
{
    return components.end();
}

Chem::BasicReaction::ComponentIterator Chem::BasicReaction::getComponentsBegin() 
{
    return components.begin();
}

Chem::BasicReaction::ComponentIterator Chem::BasicReaction::getComponentsEnd() 
{
    return components.end();
}

Chem::BasicReaction::ConstComponentIterator Chem::BasicReaction::getComponentsBegin(unsigned int role) const
{
    switch (role) {

        case ReactionRole::REACTANT:
            return getReactantsBegin();

        case ReactionRole::AGENT:
            return getAgentsBegin();

        case ReactionRole::PRODUCT:
            return getProductsBegin();
    
        default:
            throw Base::ValueError("BasicReaction: invalid reaction role");
    }
}

Chem::BasicReaction::ConstComponentIterator Chem::BasicReaction::getComponentsEnd(unsigned int role) const
{
    switch (role) {

        case ReactionRole::REACTANT:
            return getReactantsEnd();

        case ReactionRole::AGENT:
            return getAgentsEnd();

        case ReactionRole::PRODUCT:
            return getProductsEnd();
    
        default:
            throw Base::ValueError("BasicReaction: invalid reaction role");
    }
}

Chem::BasicReaction::ComponentIterator Chem::BasicReaction::getComponentsBegin(unsigned int role)
{
    switch (role) {

        case ReactionRole::REACTANT:
            return getReactantsBegin();

        case ReactionRole::AGENT:
            return getAgentsBegin();

        case ReactionRole::PRODUCT:
            return getProductsBegin();
    
        default:
            throw Base::ValueError("BasicReaction: invalid reaction role");
    }
}

Chem::BasicReaction::ComponentIterator Chem::BasicReaction::getComponentsEnd(unsigned int role)
{
    switch (role) {

        case ReactionRole::REACTANT:
            return getReactantsEnd();

        case ReactionRole::AGENT:
            return getAgentsEnd();

        case ReactionRole::PRODUCT:
            return getProductsEnd();
    
        default:
            throw Base::ValueError("BasicReaction: invalid reaction role");
    }
}

const Chem::BasicMolecule& Chem::BasicReaction::getComponent(std::size_t idx) const
{
    if (idx >= components.size())
        throw Base::IndexError("BasicReaction: component index out of bounds");

    return *components[idx];
}

Chem::BasicMolecule& Chem::BasicReaction::getComponent(std::size_t idx)
{
    if (idx >= components.size())
        throw Base::IndexError("BasicReaction: component index out of bounds");

    return *components[idx];
}

const Chem::BasicMolecule& Chem::BasicReaction::getComponent(std::size_t idx, unsigned int role) const
{
    switch (role) {

        case ReactionRole::REACTANT:
            return getReactant(idx);

        case ReactionRole::AGENT:
            return getAgent(idx);

        case ReactionRole::PRODUCT:
            return getProduct(idx);
    
        default:
            throw Base::ValueError("BasicReaction: invalid reaction role");
    }
}

Chem::BasicMolecule& Chem::BasicReaction::getComponent(std::size_t idx, unsigned int role)
{
    switch (role) {

        case ReactionRole::REACTANT:
            return getReactant(idx);

        case ReactionRole::AGENT:
            return getAgent(idx);

        case ReactionRole::PRODUCT:
            return getProduct(idx);
    
        default:
            throw Base::ValueError("BasicReaction: invalid reaction role");
    }
}

void Chem::BasicReaction::swapComponentRoles(unsigned int role1, unsigned int role2)
{
    for (int i = 0; i < 2; i++) {
        switch (i == 0 ? role1 : role2) {
        
            case ReactionRole::REACTANT:
            case ReactionRole::AGENT:
            case ReactionRole::PRODUCT:
                break;
    
            default:
                throw Base::ValueError(std::string("BasicReaction: invalid reaction role for argument ") + (i == 0 ? "1" : "2"));
        }
    }

    if (role1 == role2)
        return;

    ComponentList new_comp_list;

    new_comp_list.reserve(components.size());

    int new_reactant_role = ReactionRole::REACTANT;

    if (role1 == ReactionRole::REACTANT)
        new_reactant_role = role2;
    else if (role2 == ReactionRole::REACTANT)
        new_reactant_role = role1;

    std::size_t new_num_reactants = getNumComponents(new_reactant_role);

    std::copy(getComponentsBegin(new_reactant_role).base(), getComponentsEnd(new_reactant_role).base(),
              std::back_inserter(new_comp_list));

    int new_agent_role = ReactionRole::AGENT;

    if (role1 == ReactionRole::AGENT)
        new_agent_role = role2;
    else if (role2 == ReactionRole::AGENT)
        new_agent_role = role1;

    std::size_t new_num_agents = getNumComponents(new_agent_role);

    std::copy(getComponentsBegin(new_agent_role).base(), getComponentsEnd(new_agent_role).base(),
              std::back_inserter(new_comp_list));

    int new_product_role = ReactionRole::PRODUCT;

    if (role1 == ReactionRole::PRODUCT)
        new_product_role = role2;
    else if (role2 == ReactionRole::PRODUCT)
        new_product_role = role1;

    std::copy(getComponentsBegin(new_product_role).base(), getComponentsEnd(new_product_role).base(),
              std::back_inserter(new_comp_list));

    components.swap(new_comp_list);

    agentsStartIdx = new_num_reactants;
    productsStartIdx = agentsStartIdx + new_num_agents;
}

Chem::BasicMolecule& Chem::BasicReaction::addComponent(unsigned int role)
{
    return addComponent(role, 0);
}

Chem::BasicMolecule& Chem::BasicReaction::addComponent(unsigned int role, const Molecule& mol)
{
    return addComponent(role, &mol);
}

void Chem::BasicReaction::removeComponent(std::size_t idx)
{
    if (idx >= components.size())
        throw Base::IndexError("BasicReaction: component index out of bounds");
    
    components.erase(components.begin() + idx);

    if (idx < agentsStartIdx) {
        agentsStartIdx--;
        productsStartIdx--;

    } else if (idx < productsStartIdx)
        productsStartIdx--;
}

Chem::BasicReaction::ComponentIterator Chem::BasicReaction::removeComponent(const ComponentIterator& it)
{
    const ComponentList::iterator& base = it.base();

    if (base < components.begin() || base >= components.end())
        throw Base::RangeError("BasicReaction: component iterator out of valid range");

    std::size_t idx = base - components.begin();
    ComponentList::iterator rit = components.erase(base);

    if (idx < agentsStartIdx) {
        agentsStartIdx--;
        productsStartIdx--;

    } else if (idx < productsStartIdx)
        productsStartIdx--;

    return rit;
}

void Chem::BasicReaction::removeComponent(std::size_t idx, unsigned int role)
{
    switch (role) {

        case ReactionRole::REACTANT:
            removeReactant(idx);
            return;

        case ReactionRole::AGENT:
            removeAgent(idx);
            return;

        case ReactionRole::PRODUCT:
            removeProduct(idx);
            return;
    
        default:
            throw Base::ValueError("BasicReaction: invalid reaction role");
    }
}

void Chem::BasicReaction::removeComponents(unsigned int role)
{
    switch (role) {

        case ReactionRole::REACTANT:
            removeReactants();
            return;

        case ReactionRole::AGENT:
            removeAgents();
            return;

        case ReactionRole::PRODUCT:
            removeProducts();
            return;

        default:
            throw Base::ValueError("BasicReaction: invalid reaction role");
    }
}

Chem::Reaction::SharedPointer Chem::BasicReaction::clone() const
{
    return Reaction::SharedPointer(new BasicReaction(*this));
}

Chem::BasicReaction& Chem::BasicReaction::operator=(const BasicReaction& rxn)
{
    if (this == &rxn)
        return *this;

    copy(rxn);

    return *this;
}

void Chem::BasicReaction::copy(const BasicReaction& rxn)
{
    if (this == &rxn)
        return;

    clearComponents();
    copyComponents(rxn);
    copyProperties(rxn);
    invokeCopyPostprocessingFunctions(rxn);
}

void Chem::BasicReaction::copy(const Reaction& rxn)
{
    if (this == &rxn)
        return;

    clearComponents();
    copyComponents(rxn);
    copyProperties(rxn);
    invokeCopyPostprocessingFunctions(rxn);
}

const Chem::BasicMolecule& Chem::BasicReaction::getReactant(std::size_t idx) const
{
    if (idx >= agentsStartIdx)
        throw Base::IndexError("BasicReaction: reactant index out of bounds");

    return getComponent(idx);
}

Chem::BasicMolecule& Chem::BasicReaction::getReactant(std::size_t idx)
{    
    if (idx >= agentsStartIdx)
        throw Base::IndexError("BasicReaction: reactant index out of bounds");

    return getComponent(idx);
}

const Chem::BasicMolecule& Chem::BasicReaction::getAgent(std::size_t idx) const
{
    idx += agentsStartIdx;

    if (idx >= productsStartIdx)
        throw Base::IndexError("BasicReaction: agent index out of bounds");

    return getComponent(idx);
}

Chem::BasicMolecule& Chem::BasicReaction::getAgent(std::size_t idx)
{
    idx += agentsStartIdx;

    if (idx >= productsStartIdx)
        throw Base::IndexError("BasicReaction: agent index out of bounds");

    return getComponent(idx);
}

const Chem::BasicMolecule& Chem::BasicReaction::getProduct(std::size_t idx) const
{
    idx += productsStartIdx;

    if (idx >= components.size())
        throw Base::IndexError("BasicReaction: product index out of bounds");

    return getComponent(idx);
}

Chem::BasicMolecule& Chem::BasicReaction::getProduct(std::size_t idx)
{
    idx += productsStartIdx;

    if (idx >= components.size())
        throw Base::IndexError("BasicReaction: product index out of bounds");

    return getComponent(idx);
}

Chem::BasicReaction::ConstComponentIterator Chem::BasicReaction::getReactantsBegin() const
{
    return components.begin();
}

Chem::BasicReaction::ConstComponentIterator Chem::BasicReaction::getReactantsEnd() const
{
    return (components.begin() + agentsStartIdx);
}

Chem::BasicReaction::ComponentIterator Chem::BasicReaction::getReactantsBegin() 
{
    return components.begin();
}

Chem::BasicReaction::ComponentIterator Chem::BasicReaction::getReactantsEnd() 
{
    return (components.begin() + agentsStartIdx);
}

Chem::BasicReaction::ConstComponentIterator Chem::BasicReaction::getAgentsBegin() const
{
    return (components.begin() + agentsStartIdx);
}

Chem::BasicReaction::ConstComponentIterator Chem::BasicReaction::getAgentsEnd() const
{
    return (components.begin() + productsStartIdx);
}

Chem::BasicReaction::ComponentIterator Chem::BasicReaction::getAgentsBegin() 
{
    return (components.begin() + agentsStartIdx);
}

Chem::BasicReaction::ComponentIterator Chem::BasicReaction::getAgentsEnd() 
{
    return (components.begin() + productsStartIdx);
}

Chem::BasicReaction::ConstComponentIterator Chem::BasicReaction::getProductsBegin() const
{
    return (components.begin() + productsStartIdx);
}

Chem::BasicReaction::ConstComponentIterator Chem::BasicReaction::getProductsEnd() const
{
    return components.end();
}

Chem::BasicReaction::ComponentIterator Chem::BasicReaction::getProductsBegin() 
{
    return (components.begin() + productsStartIdx);
}

Chem::BasicReaction::ComponentIterator Chem::BasicReaction::getProductsEnd() 
{
    return components.end();
}

void Chem::BasicReaction::removeReactant(std::size_t idx)
{
    if (idx >= agentsStartIdx)
        throw Base::IndexError("BasicReaction: reactant index out of bounds");

    components.erase(components.begin() + idx);

    agentsStartIdx--;
    productsStartIdx--;
}

void Chem::BasicReaction::removeAgent(std::size_t idx)
{
    idx += agentsStartIdx;

    if (idx >= productsStartIdx)
        throw Base::IndexError("BasicReaction: agent index out of bounds");

    components.erase(components.begin() + idx);

    productsStartIdx--;
}

void Chem::BasicReaction::removeProduct(std::size_t idx)
{
    idx += productsStartIdx;

    if (idx >= components.size())
        throw Base::IndexError("BasicReaction: product index out of bounds");

    components.erase(components.begin() + idx);
}

void Chem::BasicReaction::removeReactants()
{
    if (agentsStartIdx == 0)
        return;

    components.erase(components.begin(), components.begin() + agentsStartIdx);

    productsStartIdx -= agentsStartIdx;
    agentsStartIdx = 0;
}

void Chem::BasicReaction::removeAgents()
{
    if (productsStartIdx - agentsStartIdx == 0)
        return;

    components.erase(components.begin() + agentsStartIdx, components.begin() + productsStartIdx);

    productsStartIdx = agentsStartIdx;
}

void Chem::BasicReaction::removeProducts()
{
    if (components.size() - productsStartIdx == 0)
        return;

    components.erase(components.begin() + productsStartIdx, components.end());
}

Chem::BasicMolecule& Chem::BasicReaction::addComponent(unsigned int role, const Molecule* mol)
{
    switch (role) {

        case ReactionRole::REACTANT:
            return addReactant(mol);

        case ReactionRole::AGENT:
            return addAgent(mol);

        case ReactionRole::PRODUCT:
            return addProduct(mol);
    
        default:
            throw Base::ValueError("BasicReaction: invalid reaction role");
    }
}

Chem::BasicMolecule& Chem::BasicReaction::addReactant(const Molecule* mol)
{
    ComponentPtr comp = allocComponent(mol);

    components.insert(components.begin() + agentsStartIdx, comp);

    agentsStartIdx++;
    productsStartIdx++;

    return *comp;
}

Chem::BasicMolecule& Chem::BasicReaction::addAgent(const Molecule* mol)
{
    ComponentPtr comp = allocComponent(mol);

    components.insert(components.begin() + productsStartIdx, comp);

    productsStartIdx++;

    return *comp;
}

Chem::BasicMolecule& Chem::BasicReaction::addProduct(const Molecule* mol)
{
    ComponentPtr comp = allocComponent(mol);

    components.push_back(comp);

    return *comp;
}

void Chem::BasicReaction::clearComponents()
{
    components.clear();

    agentsStartIdx = 0;
    productsStartIdx = 0;
}

void Chem::BasicReaction::copyComponents(const BasicReaction& rxn)
{
    components.reserve(rxn.components.size());

    ComponentList::const_iterator comps_end = rxn.components.end();

    for (ComponentList::const_iterator it = rxn.components.begin(); it != comps_end; ++it) 
        components.push_back(allocComponent(it->get()));

    agentsStartIdx = rxn.agentsStartIdx;
    productsStartIdx = rxn.productsStartIdx;
}

void Chem::BasicReaction::copyComponents(const Reaction& rxn)
{
    components.reserve(rxn.getNumComponents());

    Reaction::ConstComponentIterator comps_end = rxn.getComponentsEnd();

    for (Reaction::ConstComponentIterator it = rxn.getComponentsBegin(); it != comps_end; ++it) 
        components.push_back(allocComponent(&*it));

    agentsStartIdx = rxn.getNumComponents(ReactionRole::REACTANT);
    productsStartIdx = agentsStartIdx + rxn.getNumComponents(ReactionRole::AGENT);
}

Chem::BasicReaction::ComponentPtr Chem::BasicReaction::allocComponent(const Molecule* mol)
{
    ComponentPtr comp = compCache.get();

    if (mol)
        comp->copy(*mol);

    return comp;
}
