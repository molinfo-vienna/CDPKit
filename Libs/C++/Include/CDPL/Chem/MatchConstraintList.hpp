/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MatchConstraintList.hpp 
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
 * \brief Definition of the class CDPL::Chem::MatchConstraintList.
 */

#ifndef CDPL_CHEM_MATCHCONSTRAINTLIST_HPP
#define CDPL_CHEM_MATCHCONSTRAINTLIST_HPP

#include <utility>
#include <memory>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Base/Any.hpp"
#include "CDPL/Util/Array.hpp"


namespace CDPL
{

	namespace Chem
	{

		/**
		 * \brief MatchConstraint.
		 */
		class CDPL_CHEM_API MatchConstraint
		{
			
		public:
			/**
			 * \brief Defines constants for the specification of relational constraints on the values of query/target attribute
			 *        pairs.
			 */
			enum Relation 
			{

				/**
				 * \brief Specifies that the relation between the query and target attribute value is not constrained.
				 */
				ANY,
 
                /**
				 * \brief Specifies that the value of the query attribute must be less than the corresponding value of the target
				 *        attribute to fulfill the constraint.
				 */
				LESS,
 
                /**
				 * \brief Specifies that the value of the query attribute must be equal to the corresponding value of the target
				 *        attribute to fulfill the constraint.
				 */
				EQUAL,

                 /**
				 * \brief Specifies that the value of the query attribute must be greater than the corresponding value of the target
				 *        attribute to fulfill the constraint.
				 */
				GREATER,
 
                /**
				 * \brief Specifies that the value of the query attribute must be less than or equal to the corresponding value of
				 *        the target attribute to fulfill the constraint.
				 */
				LESS_OR_EQUAL,
 
                /**
				 * \brief Specifies that the value of the query attribute must be greater than or equal to the corresponding value of
				 *        the target attribute to fulfill the constraint.
				 */
				GREATER_OR_EQUAL,
 
                /**
				 * \brief Specifies that the value of the query attribute must not be equal to the corresponding value of the target
				 *        attribute to fulfill the constraint.
				 */
				NOT_EQUAL
			};

			/**
			 * \brief Constructs a \c %MatchConstraint object with the given identifier and relational constraint on the values of matching query/target
			 *        attribute pairs.
			 * \param id The identifier of the match constraint.
			 * \param relation The relational constraint on the values of matching query/target attribute pairs.
			 */
			MatchConstraint(unsigned int id, Relation relation): 
				id(id), relation(relation) {}

			/**
			 * \brief Constructs a \c %MatchConstraint object with the given identifier, relational constraint on the values of matching query/target
			 *        attribute pairs and value of the query attribute.
			 * \param id The identifier of the match constraint.
			 * \param rel The relational constraint on the values of matching query/target attribute pairs.
			 * \param val The value of the query attribute.
			 */
		    template <typename T>
			MatchConstraint(unsigned int id, Relation rel, T&& val): 
		    id(id), relation(rel), value(std::forward<T>(val)) {}
	
			/**
			 * \brief Returns the identifier of the match constraint.
			 * \return The identifier of the match constraint.
			 */
			unsigned int getID() const;

			/**
			 * \brief Sets the match constraint identifier to \a id.
			 * \param id The identifier of the match constraint.
			 */
			void setID(unsigned int id);

			/**
			 * \brief Returns the relational constraint that must be fulfilled by the values of matching query/target attribute pairs.
			 * \return The relational constraint on the values of matching query/target attribute pairs.
			 */
			Relation getRelation() const;

			/**
			 * \brief Sets the relational constraint that must be fulfilled by the values of matching query/target attribute pairs.
			 * \param rel The relational constraint on the values of matching query/target attribute pairs.
			 */
			void setRelation(Relation rel);

			/**
			 * \brief Returns the value of the query attribute.
			 * \return The value of the query attribute.
			 */
			const Base::Any& getValue() const;

			/**
			 * \brief Returns a \c const reference to the value of the query attribute of type \a T.
			 * \return A \c const reference to the value of the stored query attribute.
			 * \throw Base::BadCast if the stored \c %Any instance is empty, or the stored
			 *        value is not of the specified type \a T.
			 */
			template <typename T>
			const T& getValue() const {
				return value.getData<T>();
			}

			/**
			 * \brief Sets the value of the query attribute.
			 * \param val The value of the query attribute.
			 */
		    template <typename T>
		    void setValue(T&& val) {
				value = std::forward<T>(val);
			}
			
			/**
			 * \brief Tells wether a query attribute value has been set.
			 * \return \c true if the value of the query attribute has been set, \c false otherwise.
			 */
			bool hasValue() const;

		private:
			unsigned int id;
			Relation     relation;
			Base::Any    value;
		};

		/**
		 * \brief MatchConstraintList.
		 */
		class CDPL_CHEM_API MatchConstraintList : public Util::Array<MatchConstraint>
		{ 

		public:
			/**
			 * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %MatchConstraintList instances.
			 */
			typedef std::shared_ptr<MatchConstraintList> SharedPointer;

			/**
			 * \brief Defines constants that describe the logical type of the match constraint list.
			 */
			enum Type 
			{

				/**
				 * \brief Specifies that all of the match constraints must be fulfilled. 
				 */
				AND_LIST,

				/**
				 * \brief Specifies that at least one of the match constraints must not be fulfilled.
				 */
				NOT_AND_LIST,

				/**
				 * \brief Specifies that at least one of the match constraints must be fulfilled. 
				 */
				OR_LIST,

				/**
				 * \brief Specifies that all of the match constraints must not be fulfilled.
				 */				
				NOT_OR_LIST
			};

			/**
			 * \brief Constructs a \c %MatchConstraintList object with the specified logical type.
			 * \param type The logical type of the match constraint list.
			 */
			MatchConstraintList(Type type = AND_LIST): type(type) {}

			/**
			 * \brief Returns the logical type of the match constraint list.
			 * \return The logical type of the match constraint list.
			 */
			Type getType() const;

			/**
			 * \brief Sets the logical type of the match constraint list.
			 * \param type The logical type of the match constraint list.
			 */
			void setType(Type type);

			using Util::Array<MatchConstraint>::addElement;

			/**
			 * \brief Appends a new Chem::MatchConstraint element with the given identifier and relational constraint on the values of matching query/target
			 *        attribute pairs.
			 * \param id The identifier of the match constraint.
			 * \param rel The relational constraint on the values of matching query/target attribute pairs.
			 */
			void addElement(unsigned int id, MatchConstraint::Relation rel);

			/**
			 * \brief Appends a new Chem::MatchConstraint element with the given identifier, relational constraint on the values of matching query/target
			 *        attribute pairs and value of the query attribute.
			 * \param id The identifier of the match constraint.
			 * \param rel The relational constraint on the values of matching query/target attribute pairs.
			 * \param val The value of the query attribute.
			 */
			template <typename T>
			void addElement(unsigned int id, MatchConstraint::Relation rel, T&& val) {
				addElement(MatchConstraint(id, rel, std::forward<T>(val)));
			}

		private:
			const char* getClassName() const;

			Type type;
		};
	}
}

#endif // CDPL_CHEM_MATCHCONSTRAINTLIST_HPP
