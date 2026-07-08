/* 
 * TorsionCategory.hpp 
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
 * \brief Definition of class CDPL::ConfGen::TorsionCategory.
 */

#ifndef CDPL_CONFGEN_TORSIONCATEGORY_HPP
#define CDPL_CONFGEN_TORSIONCATEGORY_HPP

#include <string>
#include <cstddef>

#include <boost/ptr_container/ptr_vector.hpp>

#include "CDPL/ConfGen/APIPrefix.hpp"
#include "CDPL/ConfGen/TorsionRule.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"


namespace CDPL
{

    namespace ConfGen
    {

        /**
         * \brief Represents a node of a hierarchical torsion library.
         *
         * Nodes are named, central bond specific categories that can hold child categories as well as torsion rules.
         */
        class CDPL_CONFGEN_API TorsionCategory
        {

            typedef boost::ptr_vector<TorsionCategory> CategoryList;
            typedef boost::ptr_vector<TorsionRule>     RuleList;

          public:
            /**
             * \brief A mutable iterator over the child categories.
             */
            typedef CategoryList::iterator       CategoryIterator;

            /**
             * \brief A constant iterator over the child categories.
             */
            typedef CategoryList::const_iterator ConstCategoryIterator;

            /**
             * \brief A mutable iterator over the contained rules.
             */
            typedef RuleList::iterator           RuleIterator;

            /**
             * \brief A constant iterator over the contained rules.
             */
            typedef RuleList::const_iterator     ConstRuleIterator;

            /**
             * \brief Constructs an empty \c %TorsionCategory instance.
             */
            TorsionCategory();

            /**
             * \brief Virtual destructor.
             */
            virtual ~TorsionCategory() {}

            /**
             * \brief Returns the category name.
             * \return A \c const reference to the category name.
             */
            const std::string& getName() const;

            /**
             * \brief Sets the category name.
             * \param name The new name.
             */
            void setName(const std::string& name);

            /**
             * \brief Returns the \e SMARTS match pattern describing the bonds that belong to this category.
             * \return A \c const reference to the \e SMARTS match pattern.
             */
            const std::string& getMatchPatternString() const;

            /**
             * \brief Sets the \e SMARTS match pattern describing the bonds that belong to this category.
             * \param ptn_str The new \e SMARTS match pattern.
             */
            void setMatchPatternString(const std::string& ptn_str);

            /**
             * \brief Returns the match pattern molecular graph used to perceive the bonds that belong to this category.
             * \return A \c const shared pointer to the match pattern molecular graph.
             */
            const Chem::MolecularGraph::SharedPointer& getMatchPattern() const;

            /**
             * \brief Sets the match pattern molecular graph used to perceive the bonds that belong to this category.
             * \param ptn The new match pattern molecular graph.
             */
            void setMatchPattern(const Chem::MolecularGraph::SharedPointer& ptn);

            /**
             * \brief Returns the atom type of the first central bond atom required by this category.
             * \return The atom type (Chem::AtomType value).
             */
            unsigned int getBondAtom1Type() const;

            /**
             * \brief Sets the atom type of the first central bond atom required by this category.
             * \param type The new atom type (Chem::AtomType value).
             */
            void setBondAtom1Type(unsigned int type);

            /**
             * \brief Returns the atom type of the second central bond atom required by this category.
             * \return The atom type (Chem::AtomType value).
             */
            unsigned int getBondAtom2Type() const;

            /**
             * \brief Sets the atom type of the second central bond atom required by this category.
             * \param type The new atom type (Chem::AtomType value).
             */
            void setBondAtom2Type(unsigned int type);

            /**
             * \brief Creates and appends a new empty child category.
             * \return A reference to the newly added child category.
             */
            TorsionCategory& addCategory();

            /**
             * \brief Appends a copy of \a cat as a child category.
             * \param cat The child category to copy.
             * \return A reference to the newly added child category.
             */
            TorsionCategory& addCategory(const TorsionCategory& cat);

            /**
             * \brief Creates and appends a new empty torsion rule.
             * \return A reference to the newly added rule.
             */
            TorsionRule& addRule();

            /**
             * \brief Appends a copy of \a rule as a contained torsion rule.
             * \param rule The torsion rule to copy.
             * \return A reference to the newly added rule.
             */
            TorsionRule& addRule(const TorsionRule& rule);

            /**
             * \brief Returns the number of child categories.
             * \param recursive If \c true, the count includes all descendant categories.
             * \return The child category count.
             */
            std::size_t getNumCategories(bool recursive = false) const;

            /**
             * \brief Returns the number of contained torsion rules.
             * \param recursive If \c true, the count includes rules of all descendant categories.
             * \return The torsion-rule count.
             */
            std::size_t getNumRules(bool recursive = false) const;

            /**
             * \brief Returns the child category at index \a idx.
             * \param idx The zero-based child category index.
             * \return A reference to the child category.
             * \throw Base::IndexError if \a idx is not in the range [0, getNumCategories()).
             */
            TorsionCategory& getCategory(std::size_t idx);

            /**
             * \brief Returns the child category at index \a idx.
             * \param idx The zero-based child category index.
             * \return A \c const reference to the child category.
             * \throw Base::IndexError if \a idx is not in the range [0, getNumCategories()).
             */
            const TorsionCategory& getCategory(std::size_t idx) const;

            /**
             * \brief Returns the torsion rule at index \a idx.
             * \param idx The zero-based rule index.
             * \return A reference to the rule.
             * \throw Base::IndexError if \a idx is not in the range [0, getNumRules()).
             */
            TorsionRule& getRule(std::size_t idx);

            /**
             * \brief Returns the torsion rule at index \a idx.
             * \param idx The zero-based rule index.
             * \return A \c const reference to the rule.
             * \throw Base::IndexError if \a idx is not in the range [0, getNumRules()).
             */
            const TorsionRule& getRule(std::size_t idx) const;

            /**
             * \brief Removes the child category at index \a idx.
             * \param idx The zero-based child category index.
             * \throw Base::IndexError if \a idx is not in the range [0, getNumCategories()).
             */
            void removeCategory(std::size_t idx);

            /**
             * \brief Removes the torsion rule at index \a idx.
             * \param idx The zero-based rule index.
             * \throw Base::IndexError if \a idx is not in the range [0, getNumRules()).
             */
            void removeRule(std::size_t idx);

            /**
             * \brief Removes the child category referenced by \a it.
             * \param it Iterator referencing the child category to remove.
             */
            void removeCategory(const CategoryIterator& it);

            /**
             * \brief Removes the torsion rule referenced by \a it.
             * \param it Iterator referencing the rule to remove.
             */
            void removeRule(const RuleIterator& it);

            /**
             * \brief Returns a mutable iterator pointing to the first child category.
             * \return A mutable iterator pointing to the first child category.
             */
            CategoryIterator getCategoriesBegin();

            /**
             * \brief Returns a mutable iterator pointing one past the last child category.
             * \return A mutable iterator pointing one past the last child category.
             */
            CategoryIterator getCategoriesEnd();

            /**
             * \brief Returns a constant iterator pointing to the first child category.
             * \return A constant iterator pointing to the first child category.
             */
            ConstCategoryIterator getCategoriesBegin() const;

            /**
             * \brief Returns a constant iterator pointing one past the last child category.
             * \return A constant iterator pointing one past the last child category.
             */
            ConstCategoryIterator getCategoriesEnd() const;

            /**
             * \brief Returns a mutable iterator pointing to the first contained rule.
             * \return A mutable iterator pointing to the first rule.
             */
            RuleIterator getRulesBegin();

            /**
             * \brief Returns a mutable iterator pointing one past the last contained rule.
             * \return A mutable iterator pointing one past the last rule.
             */
            RuleIterator getRulesEnd();

            /**
             * \brief Returns a constant iterator pointing to the first contained rule.
             * \return A constant iterator pointing to the first rule.
             */
            ConstRuleIterator getRulesBegin() const;

            /**
             * \brief Returns a constant iterator pointing one past the last contained rule.
             * \return A constant iterator pointing one past the last rule.
             */
            ConstRuleIterator getRulesEnd() const;

            /**
             * \brief Swaps the contents of this category with \a cat.
             * \param cat The other category.
             */
            void swap(TorsionCategory& cat);

            /**
             * \brief Removes all child categories and contained rules and resets the pattern/atom type data.
             */
            void clear();

          private:
            void checkCategoryIndex(std::size_t idx, bool it) const;

            void checkRuleIndex(std::size_t idx, bool it) const;

            std::string                         name;
            std::string                         matchPatternStr;
            Chem::MolecularGraph::SharedPointer matchPattern;
            unsigned int                        bondAtom1Type;
            unsigned int                        bondAtom2Type;
            RuleList                            rules;
            CategoryList                        categories;
        };
    } // namespace ConfGen
} // namespace CDPL

#endif // CDPL_CONFGEN_TORSIONCATEGORY_HPP
