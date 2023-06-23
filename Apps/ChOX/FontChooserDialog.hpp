/* 
 * FontChooserDialog.hpp 
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


#ifndef CHOX_FONTCHOOSERDIALOG_HPP
#define CHOX_FONTCHOOSERDIALOG_HPP

#include <QDialog>

#include "CDPL/Vis/Font.hpp"
#include "CDPL/Vis/SizeSpecification.hpp"


namespace ChOX
{

    class FontChooserDialog : public QDialog
    {

        Q_OBJECT

    public:
        FontChooserDialog(QWidget*, CDPL::Vis::Font&, CDPL::Vis::SizeSpecification&, const CDPL::Vis::SizeSpecification* = 0, 
                          bool = true, bool = true, Qt::WindowFlags = 0);

    private slots:
        void applyChanges();

    private:
        void init(bool, bool);

        CDPL::Vis::Font&                    font;
        CDPL::Vis::Font                     tmpFont;
        CDPL::Vis::SizeSpecification&       sizeSpec;
        CDPL::Vis::SizeSpecification        tmpSizeSpec;
        const CDPL::Vis::SizeSpecification* parentSizeSpec;
    };
}

#endif // CHOX_FONTCHOOSERDIALOG_HPP
