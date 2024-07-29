/* 
 * MMCIFData.hpp 
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
 * \brief Definition of the class CDPL::Biomol::MMCIFData.
 */

#ifndef CDPL_BIOMOL_MMCIFDATA_HPP
#define CDPL_BIOMOL_MMCIFDATA_HPP

#include <cstddef>
#include <string>
#include <string_view>
#include <vector>
#include <memory>

#include "CDPL/Biomol/APIPrefix.hpp"


namespace CDPL
{

    namespace Biomol
    {

        /**
         * \brief A data structure for the storage of imported MMCIF data (see [\ref MMCIF]).
         */
        class CDPL_BIOMOL_API MMCIFData
        {

          public:
            typedef std::shared_ptr<MMCIFData> SharedPointer;

            class CDPL_BIOMOL_API Category
            {

              public:
                Category(const std::string_view& name):
                    name(name) {}

                const std::string& getName() const
                {
                    return name;
                }
                // TODO
              private:
                std::string name;
            };

          private:
            typedef std::vector<Category> CategoryList;
            
          public:
            typedef CategoryList::const_iterator ConstCategoryIterator;

            typedef CategoryList::iterator CategoryIterator;

            void clear();

            std::size_t getNumCategories() const;

            bool isEmpty() const;
            
            bool hasCategory(const std::string_view& name) const;
            
            Category& getCategory(std::size_t index);
            
            const Category& getCategory(std::size_t index) const;

            Category& getCategory(const std::string_view& name);
            
            const Category& getCategory(const std::string_view& name) const;

            ConstCategoryIterator findCategory(const std::string_view& name) const;

            CategoryIterator findCategory(const std::string_view& name);
            
            Category& addCategory(const std::string_view& name);

            void removeCategory(const CategoryIterator& it);

            bool removeCategory(const std::string_view& name);

            void removeCategory(std::size_t index);

            ConstCategoryIterator getCategoriesBegin() const;

            CategoryIterator getCategoriesBegin();

            ConstCategoryIterator getCategoriesEnd() const;

            CategoryIterator getCategoriesEnd();

            ConstCategoryIterator begin() const;

            CategoryIterator begin();

            ConstCategoryIterator end() const;

            CategoryIterator end();

          private:
            CategoryList categories;
        };
    } // namespace Biomol
} // namespace CDPL

#endif // CDPL_BIOMOL_MMCIFDATA_HPP
