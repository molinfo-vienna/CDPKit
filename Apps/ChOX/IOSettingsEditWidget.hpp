/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * IOSettingsEditWidget.hpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2020 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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


#ifndef CHOX_IOSETTINGSEDITWIDGET_HPP
#define CHOX_IOSETTINGSEDITWIDGET_HPP

#include "TabSettingsEditWidget.hpp"


namespace ChOX
{

	class Settings;

	class IOSettingsEditWidget : public TabSettingsEditWidget
	{

		Q_OBJECT

	public:
		IOSettingsEditWidget(QWidget*, Settings&);

	private:
		void init(Settings&);
	};
}

#endif // CHOX_IOSETTINGSEDITWIDGET_HPP