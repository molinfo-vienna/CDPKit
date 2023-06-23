/* 
 * FontTest.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; see the file COPYING. If not, write to
 * the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */


#include <boost/test/auto_unit_test.hpp>

#include "CDPL/Vis/Font.hpp"


BOOST_AUTO_TEST_CASE(FontTest)
{
	using namespace CDPL;
	using namespace Vis;

	Font f1;

	BOOST_CHECK(f1.getFamily() == "");
	BOOST_CHECK(f1.getSize() == 12.0);
	BOOST_CHECK(f1.isBold() == false);
	BOOST_CHECK(f1.isItalic() == false);
	BOOST_CHECK(f1.isUnderlined() == false);
	BOOST_CHECK(f1.isOverlined() == false);
	BOOST_CHECK(f1.isStrikedOut() == false);
	BOOST_CHECK(f1.hasFixedPitch() == false);

	Font f2("Arial");

	BOOST_CHECK(f2.getFamily() == "Arial");
	BOOST_CHECK(f2.getSize() == 12.0);
	BOOST_CHECK(f2.isBold() == false);
	BOOST_CHECK(f2.isItalic() == false);
	BOOST_CHECK(f2.isUnderlined() == false);
	BOOST_CHECK(f2.isOverlined() == false);
	BOOST_CHECK(f2.isStrikedOut() == false);
	BOOST_CHECK(f2.hasFixedPitch() == false);

	Font f3("Helvetica", -3.0);

	BOOST_CHECK(f3.getFamily() == "Helvetica");
	BOOST_CHECK(f3.getSize() == 0.0);
	BOOST_CHECK(f3.isBold() == false);
	BOOST_CHECK(f3.isItalic() == false);
	BOOST_CHECK(f3.isUnderlined() == false);
	BOOST_CHECK(f3.isOverlined() == false);
	BOOST_CHECK(f3.isStrikedOut() == false);
	BOOST_CHECK(f3.hasFixedPitch() == false);

	Font f4("Serif", 10.0);

	BOOST_CHECK(f4.getFamily() == "Serif");
	BOOST_CHECK(f4.getSize() == 10.0);
	BOOST_CHECK(f4.isBold() == false);
	BOOST_CHECK(f4.isItalic() == false);
	BOOST_CHECK(f4.isUnderlined() == false);
	BOOST_CHECK(f4.isOverlined() == false);
	BOOST_CHECK(f4.isStrikedOut() == false);
	BOOST_CHECK(f4.hasFixedPitch() == false);

//-----

	f4.setFamily("");

	BOOST_CHECK(f4.getFamily() == "");
	BOOST_CHECK(f4.getSize() == 10.0);
	BOOST_CHECK(f4.isBold() == false);
	BOOST_CHECK(f4.isItalic() == false);
	BOOST_CHECK(f4.isUnderlined() == false);
	BOOST_CHECK(f4.isOverlined() == false);
	BOOST_CHECK(f4.isStrikedOut() == false);
	BOOST_CHECK(f4.hasFixedPitch() == false);

	f4.setFamily("Arial Black");

	BOOST_CHECK(f4.getFamily() == "Arial Black");
	BOOST_CHECK(f4.getSize() == 10.0);
	BOOST_CHECK(f4.isBold() == false);
	BOOST_CHECK(f4.isItalic() == false);
	BOOST_CHECK(f4.isUnderlined() == false);
	BOOST_CHECK(f4.isOverlined() == false);
	BOOST_CHECK(f4.isStrikedOut() == false);
	BOOST_CHECK(f4.hasFixedPitch() == false);

	f4.setSize(-0.1);

	BOOST_CHECK(f4.getFamily() == "Arial Black");
	BOOST_CHECK(f4.getSize() == 0.0);
	BOOST_CHECK(f4.isBold() == false);
	BOOST_CHECK(f4.isItalic() == false);
	BOOST_CHECK(f4.isUnderlined() == false);
	BOOST_CHECK(f4.isOverlined() == false);
	BOOST_CHECK(f4.isStrikedOut() == false);
	BOOST_CHECK(f4.hasFixedPitch() == false);

	f4.setSize(11.0);

	BOOST_CHECK(f4.getFamily() == "Arial Black");
	BOOST_CHECK(f4.getSize() == 11.0);
	BOOST_CHECK(f4.isBold() == false);
	BOOST_CHECK(f4.isItalic() == false);
	BOOST_CHECK(f4.isUnderlined() == false);
	BOOST_CHECK(f4.isOverlined() == false);
	BOOST_CHECK(f4.isStrikedOut() == false);
	BOOST_CHECK(f4.hasFixedPitch() == false);

	f4.setBold(true);

	BOOST_CHECK(f4.getFamily() == "Arial Black");
	BOOST_CHECK(f4.getSize() == 11.0);
	BOOST_CHECK(f4.isBold() == true);
	BOOST_CHECK(f4.isItalic() == false);
	BOOST_CHECK(f4.isUnderlined() == false);
	BOOST_CHECK(f4.isOverlined() == false);
	BOOST_CHECK(f4.isStrikedOut() == false);
	BOOST_CHECK(f4.hasFixedPitch() == false);

	f4.setItalic(true);

	BOOST_CHECK(f4.getFamily() == "Arial Black");
	BOOST_CHECK(f4.getSize() == 11.0);
	BOOST_CHECK(f4.isBold() == true);
	BOOST_CHECK(f4.isItalic() == true);
	BOOST_CHECK(f4.isUnderlined() == false);
	BOOST_CHECK(f4.isOverlined() == false);
	BOOST_CHECK(f4.isStrikedOut() == false);
	BOOST_CHECK(f4.hasFixedPitch() == false);

	f4.setUnderlined(true);

	BOOST_CHECK(f4.getFamily() == "Arial Black");
	BOOST_CHECK(f4.getSize() == 11.0);
	BOOST_CHECK(f4.isBold() == true);
	BOOST_CHECK(f4.isItalic() == true);
	BOOST_CHECK(f4.isUnderlined() == true);
	BOOST_CHECK(f4.isOverlined() == false);
	BOOST_CHECK(f4.isStrikedOut() == false);
	BOOST_CHECK(f4.hasFixedPitch() == false);

	f4.setOverlined(true);

	BOOST_CHECK(f4.getFamily() == "Arial Black");
	BOOST_CHECK(f4.getSize() == 11.0);
	BOOST_CHECK(f4.isBold() == true);
	BOOST_CHECK(f4.isItalic() == true);
	BOOST_CHECK(f4.isUnderlined() == true);
	BOOST_CHECK(f4.isOverlined() == true);
	BOOST_CHECK(f4.isStrikedOut() == false);
	BOOST_CHECK(f4.hasFixedPitch() == false);

	f4.setStrikedOut(true);

	BOOST_CHECK(f4.getFamily() == "Arial Black");
	BOOST_CHECK(f4.getSize() == 11.0);
	BOOST_CHECK(f4.isBold() == true);
	BOOST_CHECK(f4.isItalic() == true);
	BOOST_CHECK(f4.isUnderlined() == true);
	BOOST_CHECK(f4.isOverlined() == true);
	BOOST_CHECK(f4.isStrikedOut() == true);
	BOOST_CHECK(f4.hasFixedPitch() == false);

	f4.setFixedPitch(true);

	BOOST_CHECK(f4.getFamily() == "Arial Black");
	BOOST_CHECK(f4.getSize() == 11.0);
	BOOST_CHECK(f4.isBold() == true);
	BOOST_CHECK(f4.isItalic() == true);
	BOOST_CHECK(f4.isUnderlined() == true);
	BOOST_CHECK(f4.isOverlined() == true);
	BOOST_CHECK(f4.isStrikedOut() == true);
	BOOST_CHECK(f4.hasFixedPitch() == true);

//-----

	BOOST_CHECK(f3 != f4);
	BOOST_CHECK(!(f4 == f3));

	f3.setFamily("Arial Black");

	BOOST_CHECK(f3 != f4);
	BOOST_CHECK(!(f3 == f4));

	f3.setSize(11.0);

	BOOST_CHECK(f3 != f4);
	BOOST_CHECK(!(f3 == f4));

	f3.setBold(true);

	BOOST_CHECK(f3 != f4);
	BOOST_CHECK(!(f3 == f4));

	f3.setItalic(true);

	BOOST_CHECK(f3 != f4);
	BOOST_CHECK(!(f3 == f4));

	f3.setUnderlined(true);

	BOOST_CHECK(f3 != f4);
	BOOST_CHECK(!(f3 == f4));

	f3.setOverlined(true);

	BOOST_CHECK(f3 != f4);
	BOOST_CHECK(!(f3 == f4));

	f3.setStrikedOut(true);

	BOOST_CHECK(f3 != f4);
	BOOST_CHECK(!(f3 == f4));

	f3.setFixedPitch(true);

	BOOST_CHECK(f3 == f4);
	BOOST_CHECK(!(f3 != f4));

//-----

	BOOST_CHECK(f3 == f3);
	BOOST_CHECK(!(f3 != f3));

	f3 = f2;

	BOOST_CHECK(f3 != f4);
	BOOST_CHECK(!(f3 == f4));

	BOOST_CHECK(f3 == f2);
	BOOST_CHECK(!(f3 != f2));

	BOOST_CHECK(f2 != f4);
	BOOST_CHECK(!(f2 == f4));
}

