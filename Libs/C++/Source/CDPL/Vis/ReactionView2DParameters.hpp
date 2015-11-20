/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ReactionView2DParameters.hpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2010 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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


#ifndef CDPL_VIS_REACTIONVIEW2DPARAMETERS_HPP
#define CDPL_VIS_REACTIONVIEW2DPARAMETERS_HPP

#include "CDPL/Vis/Rectangle2D.hpp"
#include "CDPL/Vis/Color.hpp"
#include "CDPL/Vis/Font.hpp"
#include "CDPL/Vis/SizeSpecification.hpp"


namespace CDPL 
{

	namespace Base
	{

		class LookupKey;
		class Variant;
	}

	namespace Vis
	{

		class View2D;

		class ReactionView2DParameters
		{

		public:
			ReactionView2DParameters(View2D&);

			~ReactionView2DParameters();

			const Rectangle2D& getViewport() const;
			unsigned int getAlignment() const;
			unsigned int getSizeAdjustment() const;

			bool eraseBackground() const;
			const Color& getBackgroundColor() const;

			unsigned int getArrowStyle() const;
			const Color& getArrowColor() const;
			const SizeSpecification& getArrowLength() const;
			const SizeSpecification& getArrowHeadLength() const;
			const SizeSpecification& getArrowHeadWidth() const;
			const SizeSpecification& getArrowShaftWidth() const;
			const SizeSpecification& getArrowLineWidth() const;

			unsigned int getComponentLayout() const;
			unsigned int getComponentLayoutDirection() const;
			const SizeSpecification& getComponentMargin() const;
			
			bool showReactants() const;
			bool showAgents() const;
			bool showProducts() const;

			unsigned int getAgentAlignment() const;
			unsigned int getAgentLayout() const;
			unsigned int getAgentLayoutDirection() const;

			const Color& getPlusSignColor() const;
			const SizeSpecification& getPlusSignSize() const;
			const SizeSpecification& getPlusSignLineWidth() const;
			bool showPlusSigns() const;

			bool viewportChanged() const;
			bool alignmentChanged() const;
			bool sizeAdjustmentChanged() const;
			bool componentBoundsChanged() const;
			bool layoutChanged() const;
			bool plusSignSizeChanged() const;
			bool plusSignAttributeChanged() const;
			bool arrowSizeChanged() const;
			bool arrowAttributeChanged() const;
			bool componentVisibilityChanged() const;

			void clearChangeFlags();

		private:
			void parentChanged();
			void parameterChanged(const Base::LookupKey&, Base::Variant);
			void parameterRemoved(const Base::LookupKey&);

			void setViewport(const Rectangle2D&);
			void setAlignment(unsigned int);
			void setSizeAdjustment(unsigned int);

			void eraseBackground(bool);
			void setBackgroundColor(const Color&);

			void setArrowStyle(unsigned int);
			void setArrowColor(const Color&);
			void setArrowLength(const SizeSpecification&);
			void setArrowHeadLength(const SizeSpecification&);
			void setArrowHeadWidth(const SizeSpecification&);
			void setArrowShaftWidth(const SizeSpecification&);
			void setArrowLineWidth(const SizeSpecification&);

			void setComponentLayout(unsigned int);
			void setComponentLayoutDirection(unsigned int);
			void setComponentMargin(const SizeSpecification&);

			void showReactants(bool);
			void showAgents(bool);
			void showProducts(bool);

			void setAgentAlignment(unsigned int);
			void setAgentLayout(unsigned int);
			void setAgentLayoutDirection(unsigned int);

			void setPlusSignColor(const Color&);
			void setPlusSignSize(const SizeSpecification&);
			void setPlusSignLineWidth(const SizeSpecification&);
			void showPlusSigns(bool);

			const View2D&      view;
			Rectangle2D        viewport;
			unsigned int       sizeAdjustment;
			unsigned int       alignment;
			Color              backgroundColor;
			bool               eraseBackgroundFlag;
			unsigned int       arrowStyle;
			Color              arrowColor;
			SizeSpecification  arrowLength;
			SizeSpecification  arrowHeadLength;
			SizeSpecification  arrowHeadWidth;
			SizeSpecification  arrowShaftWidth;
			SizeSpecification  arrowLineWidth;
			unsigned int       componentLayout;
			unsigned int       componentLayoutDirection;
			SizeSpecification  componentMargin;
			bool               showReactantsFlag;
			bool               showAgentsFlag;
			bool               showProductsFlag;
			unsigned int       agentAlignment;		
			unsigned int       agentLayout;
			unsigned int       agentLayoutDirection;
			Color              plusSignColor;
			SizeSpecification  plusSignSize;
			SizeSpecification  plusSignLineWidth;
			bool               showPlusSignsFlag;
			bool               viewportChangedFlag;
			bool               alignmentChangedFlag;
			bool               sizeAdjustmentChangedFlag;
			bool               componentBoundsChangedFlag;
			bool               layoutChangedFlag;
			bool               plusSignSizeChangedFlag;
			bool               plusSignAttributeChangedFlag;
			bool               arrowSizeChangedFlag;
			bool               arrowAttributeChangedFlag;
			bool               componentVisibilityChangedFlag;
		};
	}
}

#endif // CDPL_VIS_REACTIONVIEW2DPARAMETERS_HPP
