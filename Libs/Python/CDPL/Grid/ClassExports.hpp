/* 
 * ClassExports.hpp 
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


#ifndef CDPL_PYTHON_GRID_CLASSEXPORTS_HPP
#define CDPL_PYTHON_GRID_CLASSEXPORTS_HPP


namespace CDPLPythonGrid
{

	void exportAttributedGrid();
	void exportSpatialGrid();
	void exportRegularGrid();
	void exportRegularGridSet();

	void exportRegularGridReader();
	void exportRegularGridSetReader();
	void exportRegularGridWriter();
	void exportRegularGridSetWriter();
	void exportRegularGridInputHandler();
	void exportRegularGridSetInputHandler();
	void exportRegularGridOutputHandler();
	void exportRegularGridSetOutputHandler();
	void exportRegularGridIOManager();
	void exportRegularGridSetIOManager();

	void exportCDFRegularGridInputHandler();
	void exportCDFRegularGridOutputHandler();
	void exportCDFRegularGridSetInputHandler();
	void exportCDFRegularGridSetOutputHandler();
	void exportCDFRegularGridReader();
	void exportCDFRegularGridWriter();
	void exportCDFRegularGridSetReader();
	void exportCDFRegularGridSetWriter();
}

#endif // CDPL_PYTHON_GRID_CLASSEXPORTS_HPP
