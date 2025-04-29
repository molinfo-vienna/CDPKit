/* 
 * ReactionFunctions.hpp 
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
 * \brief Declaration of functions that operate on Chem::Reaction instances.
 */

#ifndef CDPL_VIS_REACTIONFUNCTIONS_HPP
#define CDPL_VIS_REACTIONFUNCTIONS_HPP

#include "CDPL/Vis/APIPrefix.hpp"


namespace CDPL
{

    namespace Chem
    {

        class Reaction;
    }

    namespace Vis
    {

        class Color;
        class SizeSpecification;

        CDPL_VIS_API unsigned int getArrowStyle(const Chem::Reaction& rxn);

        CDPL_VIS_API void setArrowStyle(Chem::Reaction& rxn, unsigned int style);

        CDPL_VIS_API bool hasArrowStyle(const Chem::Reaction& rxn);

        CDPL_VIS_API void clearArrowStyle(Chem::Reaction& rxn);


        CDPL_VIS_API const Color& getArrowColor(const Chem::Reaction& rxn);

        CDPL_VIS_API void setArrowColor(Chem::Reaction& rxn, const Color& color);

        CDPL_VIS_API bool hasArrowColor(const Chem::Reaction& rxn);

        CDPL_VIS_API void clearArrowColor(Chem::Reaction& rxn);


        CDPL_VIS_API const SizeSpecification& getArrowLength(const Chem::Reaction& rxn);

        CDPL_VIS_API void setArrowLength(Chem::Reaction& rxn, const SizeSpecification& length);

        CDPL_VIS_API bool hasArrowLength(const Chem::Reaction& rxn);

        CDPL_VIS_API void clearArrowLength(Chem::Reaction& rxn);


        CDPL_VIS_API const SizeSpecification& getArrowHeadLength(const Chem::Reaction& rxn);

        CDPL_VIS_API void setArrowHeadLength(Chem::Reaction& rxn, const SizeSpecification& length);

        CDPL_VIS_API bool hasArrowHeadLength(const Chem::Reaction& rxn);

        CDPL_VIS_API void clearArrowHeadLength(Chem::Reaction& rxn);


        CDPL_VIS_API const SizeSpecification& getArrowHeadWidth(const Chem::Reaction& rxn);

        CDPL_VIS_API void setArrowHeadWidth(Chem::Reaction& rxn, const SizeSpecification& width);

        CDPL_VIS_API bool hasArrowHeadWidth(const Chem::Reaction& rxn);

        CDPL_VIS_API void clearArrowHeadWidth(Chem::Reaction& rxn);


        CDPL_VIS_API const SizeSpecification& getArrowShaftWidth(const Chem::Reaction& rxn);

        CDPL_VIS_API void setArrowShaftWidth(Chem::Reaction& rxn, const SizeSpecification& width);

        CDPL_VIS_API bool hasArrowShaftWidth(const Chem::Reaction& rxn);

        CDPL_VIS_API void clearArrowShaftWidth(Chem::Reaction& rxn);


        CDPL_VIS_API const SizeSpecification& getArrowLineWidth(const Chem::Reaction& rxn);

        CDPL_VIS_API void setArrowLineWidth(Chem::Reaction& rxn, const SizeSpecification& width);

        CDPL_VIS_API bool hasArrowLineWidth(const Chem::Reaction& rxn);

        CDPL_VIS_API void clearArrowLineWidth(Chem::Reaction& rxn);


        CDPL_VIS_API unsigned int getComponentLayout(const Chem::Reaction& rxn);

        CDPL_VIS_API void setComponentLayout(Chem::Reaction& rxn, unsigned int layout);

        CDPL_VIS_API bool hasComponentLayout(const Chem::Reaction& rxn);

        CDPL_VIS_API void clearComponentLayout(Chem::Reaction& rxn);


        CDPL_VIS_API unsigned int getComponentLayoutDirection(const Chem::Reaction& rxn);

        CDPL_VIS_API void setComponentLayoutDirection(Chem::Reaction& rxn, unsigned int dir);

        CDPL_VIS_API bool hasComponentLayoutDirection(const Chem::Reaction& rxn);

        CDPL_VIS_API void clearComponentLayoutDirection(Chem::Reaction& rxn);


        CDPL_VIS_API const SizeSpecification& getComponentMargin(const Chem::Reaction& rxn);

        CDPL_VIS_API void setComponentMargin(Chem::Reaction& rxn, const SizeSpecification& margin);

        CDPL_VIS_API bool hasComponentMargin(const Chem::Reaction& rxn);

        CDPL_VIS_API void clearComponentMargin(Chem::Reaction& rxn);


        CDPL_VIS_API bool getShowReactants(const Chem::Reaction& rxn);

        CDPL_VIS_API void setShowReactants(Chem::Reaction& rxn, bool show);

        CDPL_VIS_API bool hasShowReactants(const Chem::Reaction& rxn);

        CDPL_VIS_API void clearShowReactants(Chem::Reaction& rxn);


        CDPL_VIS_API bool getShowAgents(const Chem::Reaction& rxn);

        CDPL_VIS_API void setShowAgents(Chem::Reaction& rxn, bool show);

        CDPL_VIS_API bool hasShowAgents(const Chem::Reaction& rxn);

        CDPL_VIS_API void clearShowAgents(Chem::Reaction& rxn);


        CDPL_VIS_API bool getShowProducts(const Chem::Reaction& rxn);

        CDPL_VIS_API void setShowProducts(Chem::Reaction& rxn, bool show);

        CDPL_VIS_API bool hasShowProducts(const Chem::Reaction& rxn);

        CDPL_VIS_API void clearShowProducts(Chem::Reaction& rxn);


        CDPL_VIS_API unsigned int getAgentAlignment(const Chem::Reaction& rxn);

        CDPL_VIS_API void setAgentAlignment(Chem::Reaction& rxn, unsigned int alignment);

        CDPL_VIS_API bool hasAgentAlignment(const Chem::Reaction& rxn);

        CDPL_VIS_API void clearAgentAlignment(Chem::Reaction& rxn);


        CDPL_VIS_API unsigned int getAgentLayout(const Chem::Reaction& rxn);

        CDPL_VIS_API void setAgentLayout(Chem::Reaction& rxn, unsigned int layout);

        CDPL_VIS_API bool hasAgentLayout(const Chem::Reaction& rxn);

        CDPL_VIS_API void clearAgentLayout(Chem::Reaction& rxn);


        CDPL_VIS_API unsigned int getAgentLayoutDirection(const Chem::Reaction& rxn);

        CDPL_VIS_API void setAgentLayoutDirection(Chem::Reaction& rxn, unsigned int dir);

        CDPL_VIS_API bool hasAgentLayoutDirection(const Chem::Reaction& rxn);

        CDPL_VIS_API void clearAgentLayoutDirection(Chem::Reaction& rxn);


        CDPL_VIS_API const Color& getPlusSignColor(const Chem::Reaction& rxn);

        CDPL_VIS_API void setPlusSignColor(Chem::Reaction& rxn, const Color& color);

        CDPL_VIS_API bool hasPlusSignColor(const Chem::Reaction& rxn);

        CDPL_VIS_API void clearPlusSignColor(Chem::Reaction& rxn);


        CDPL_VIS_API const SizeSpecification& getPlusSignSize(const Chem::Reaction& rxn);

        CDPL_VIS_API void setPlusSignSize(Chem::Reaction& rxn, const SizeSpecification& size);

        CDPL_VIS_API bool hasPlusSignSize(const Chem::Reaction& rxn);

        CDPL_VIS_API void clearPlusSignSize(Chem::Reaction& rxn);


        CDPL_VIS_API const SizeSpecification& getPlusSignLineWidth(const Chem::Reaction& rxn);

        CDPL_VIS_API void setPlusSignLineWidth(Chem::Reaction& rxn, const SizeSpecification& width);

        CDPL_VIS_API bool hasPlusSignLineWidth(const Chem::Reaction& rxn);

        CDPL_VIS_API void clearPlusSignLineWidth(Chem::Reaction& rxn);


        CDPL_VIS_API bool getShowPlusSigns(const Chem::Reaction& rxn);

        CDPL_VIS_API void setShowPlusSigns(Chem::Reaction& rxn, bool show);

        CDPL_VIS_API bool hasShowPlusSigns(const Chem::Reaction& rxn);

        CDPL_VIS_API void clearShowPlusSigns(Chem::Reaction& rxn);

        /*
         * \since 1.3
         */
        CDPL_VIS_API void prepareFor2DVisualization(Chem::Reaction& rxn);

    } // namespace Vis
} // namespace CDPL

#endif // CDPL_VIS_REACTIONFUNCTIONS_HPP
