/* 
 * Main.cpp 
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


#include <iostream>
#include <exception>

#include <QApplication>
#include <QStringList>

#include "MainWindow.hpp"


namespace
{

	class ChOXApplication : public QApplication
	{

	public:
		ChOXApplication(int& argc, char** argv): QApplication(argc, argv) {}

		bool notify(QObject *receiver_, QEvent *event_) {
			try {
				return QApplication::notify(receiver_, event_);
		
			} catch (const std::exception &e) {
				std::cerr << "An Exception was caught: " << e.what() << std::endl;
			}
     
			return false;
		}
	};
}

int main(int argc, char** argv)
{
	ChOXApplication app(argc, argv);

	QCoreApplication::setOrganizationName("CDPKit");
    QCoreApplication::setOrganizationDomain("cdpkit.org");
    QCoreApplication::setApplicationName("ChOX");

    ChOX::MainWindow* main_win = new ChOX::MainWindow(0);

	app.connect(&app, SIGNAL(lastWindowClosed()), &app, SLOT(quit()));

    main_win->show();

	if (app.arguments().size() > 1) {
		QStringList file_names;

		for (int i = 1; i < app.arguments().size(); i++)
			file_names.push_back(app.arguments().at(i));

		main_win->openFiles(file_names);
	}

    return app.exec();
}
