/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * SystematicConformerGeneratorImpl.hpp 
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

/**
 * \file
 * \brief Definition of the class CDPL::ConfGen::SystematicConformerGeneratorImpl.
 */

#ifndef CDPL_CONFGEN_SYSTEMATICCONFORMERGENERATORIMPL_HPP
#define CDPL_CONFGEN_SYSTEMATICCONFORMERGENERATORIMPL_HPP

#include <vector>

#include <boost/timer/timer.hpp>

#include "CDPL/ConfGen/SystematicConformerGenerator.hpp"
#include "CDPL/ConfGen/FragmentConformerGenerator.hpp"
#include "CDPL/Math/VectorArray.hpp"

#include "FragmentTreeNode.hpp"


namespace CDPL 
{

    namespace ConfGen 
    {
	
		class SystematicConformerGeneratorImpl 
		{

		public:
			typedef SystematicConformerGenerator::Settings Settings;
			typedef SystematicConformerGenerator::Status Status;

			SystematicConformerGeneratorImpl();

			void applySettings(const Settings& settings);

			const Settings& getSettings() const;

			Status generate(const Chem::MolecularGraph& molgraph);

		private:
			SystematicConformerGeneratorImpl(const SystematicConformerGeneratorImpl&);

			SystematicConformerGeneratorImpl& operator=(const SystematicConformerGeneratorImpl&);

			void init();

			void freeVector3DArrays();

			void buildTree(const Chem::MolecularGraph& molgraph);

			bool setFragmentCoordinates();

			bool timeoutExceeded() const;

			bool applyExistingCoordinates(FragmentTreeNode& node);
			bool applyFragmentLibraryCoordinates(FragmentTreeNode& node);
			bool generateFragmentCoordinates(FragmentTreeNode& node);

			void genChainBuildFragmentSubtrees();

			void getFragmentLinkBonds(const Chem::MolecularGraph& molgraph);
			void getRotatableBonds(const Chem::MolecularGraph& molgraph);

			Math::Vector3DArray::SharedPointer allocVector3DArray();
			void freeVector3DArray(const Math::Vector3DArray::SharedPointer& vec_array);

			typedef FragmentTreeNode::BondList BondList;
			typedef FragmentTreeNode::NodeList NodeList;
			typedef std::vector<Math::Vector3DArray::SharedPointer> Vector3DArrayList;

			Settings                               settings;
			FragmentTreeNode                       fragTree;
			BondList                               bonds;
			NodeList                               buildFragNodes; 
			FragmentConformerGenerator             fragConfGen;
			boost::timer::cpu_timer                timer;
			Vector3DArrayList                      allocCoordArrays;
			Vector3DArrayList                      freeCoordArrays;
		};
    }
}

#endif // CDPL_CONFGEN_SYSTEMATICCONFORMERGENERATORIMPL_HPP
