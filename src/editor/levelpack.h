/*
 *
 * This file is part of JAG, Puzzle game where the goal is to break all
 * the target pieces in each level and do this before the time runs out.
 *
 * Many thanks to XlabSoft & Ind. Infosystems, the originals authors of JAG.
 *
 * Copyright holder 2009-2012 Developed by XlabSoft & Industrial Infosystems
 * Work continued by 2017-2018 Carlos Donizete Froes [a.k.a coringao]
 *
 * JAG is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * JAG is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with JAG. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef LEVELPACK_H
#define LEVELPACK_H

#include <QDialog>
#include "ui_levelpack.h"

class LevelPackDialog : public QDialog {
    Q_OBJECT

public:
    LevelPackDialog(QWidget *parent = 0);

    int exec();

    QString packFileName()   { return ui.lePackFile->text(); }
    QString authorText()     { return ui.leAuthor->text(); }
    QString packNameText()   { return ui.lePackName->text(); }
    QString commentText()    { return ui.leComment->text(); }

    QStringList files();

private:
    Ui::LevelPackDialog ui;
    int m_result;
    QString author, packname, comment;

    void updateNavigation();
    void updateLevelsGroup();
    QString checkPathForDialog(const QString &path);

private slots:
    void on_bCancel_clicked()   { m_result = 0; close(); }
    void on_bNext_clicked();
    void on_bPrev_clicked();

    void on_bBrowse_clicked();
    void on_bUp_clicked();
    void on_bDown_clicked();
    void on_bRemove_clicked();
    void on_bClear_clicked();

    void on_bBrowsePackFile_clicked();
};

#endif // LEVELPACK_H
