/* 
 * ScreeningResult.hpp
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


#ifndef SIMSEARCH_SCREENINGRESULT_HPP
#define SIMSEARCH_SCREENINGRESULT_HPP


namespace SimSearch
{

    class ScreeningResult
    {

      public:
        double getScore() const
        {
            return 0; // TODO
        }

        std::size_t getReferenceShapeSetIndex() const
        {
            return 0; // TODO
        }

        void setReferenceShapeSetIndex(std::size_t idx)
        {
            // TODO
        }

        std::size_t getReferenceShapeIndex() const
        {
            return 0; // TODO
        }

        void setReferenceShapeIndex(std::size_t idx)
        {
            // TODO
        }

        std::size_t getAlignedShapeIndex() const
        {
            return 0; // TODO
        }

        void setAlignedShapeIndex(std::size_t idx)
        {
            // TODO
        }

      private:
    };
} // namespace SimSearch

#endif // SIMSEARCH_SCREENINGRESULT_HPP
