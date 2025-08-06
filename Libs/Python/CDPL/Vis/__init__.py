## 
# __init__.py 
#
# This file is part of the Chemical Data Processing Toolkit
#
# Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2 of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program; see the file COPYING. If not, write to
# the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
# Boston, MA 02111-1307, USA.
##


from __future__ import absolute_import

import CDPL
import CDPL.Base
import CDPL.Chem
import CDPL.Pharm

from ._vis import *

# IPython rich object representation display support
if CDPL.HAVE_CAIRO_SVG_SUPPORT:
    def _molGraphToSVG(molgraph: CDPL.Chem.MolecularGraph) -> str:
        os = CDPL.Base.StringIOStream()
        svg_writer = SVGMolecularGraphWriter(os)
        mol = CDPL.Chem.BasicMolecule(molgraph)

        prepareFor2DVisualization(mol)
        setAtomColorTableParameter(svg_writer, AtomColorTable.ELEMENT_COLORS_2D)
        setShowExplicitHydrogensParameter(svg_writer, True)

        svg_writer.write(mol)
        svg_writer.close()
        
        return os.getvalue()

    def _reactionToSVG(rxn: CDPL.Chem.Reaction) -> str:
        os = CDPL.Base.StringIOStream()
        svg_writer = SVGReactionWriter(os)
        rnx = CDPL.Chem.BasicReaction(rxn)

        prepareFor2DVisualization(rxn)
        setAtomColorTableParameter(svg_writer, AtomColorTable.ELEMENT_COLORS_2D)
        setShowExplicitHydrogensParameter(svg_writer, True)

        svg_writer.write(rxn)
        svg_writer.close()
        
        return os.getvalue()
    
    CDPL.Chem.MolecularGraph._repr_svg_ = _molGraphToSVG
    CDPL.Chem.Reaction._repr_svg_ = _reactionToSVG
