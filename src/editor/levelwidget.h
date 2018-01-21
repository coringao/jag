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

#ifndef LEVELWIDGET_H
#define LEVELWIDGET_H

#include <QTableWidget>

class LevelWidget: public QTableWidget
{
    Q_OBJECT

public:
    LevelWidget(QWidget *parent = 0)
        : QTableWidget(parent), m_clicked(false), m_rightclicked(false) {}

    bool isMousePressed()  { return m_clicked || m_rightclicked; }

protected:
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

signals:
    void enteredWidget();
    void leavedWidget();
    void mouseClicked(const QPoint &);
    void mouseRightClicked(const QPoint &);
    void mouseReleased();

private:
    bool m_clicked, m_rightclicked;
};

#endif // LEVELWIDGET_H
