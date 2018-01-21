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

#include "levelwidget.h"
#include <QMouseEvent>

void LevelWidget::enterEvent(QEvent *event)
{
    emit enteredWidget();
    m_clicked = false;
    m_rightclicked = false;

    QTableWidget::enterEvent(event);
}

void LevelWidget::leaveEvent(QEvent *event)
{
    emit leavedWidget();
    m_clicked = false;
    m_rightclicked = false;

    QTableWidget::leaveEvent(event);
}

void LevelWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (m_clicked)
        emit mouseClicked(event->pos());
    else if (m_rightclicked)
        emit mouseRightClicked(event->pos());

    QTableWidget::mouseMoveEvent(event);
}

void LevelWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_clicked = true;
        emit mouseClicked(event->pos());
    }
    else if (event->button() == Qt::RightButton) {
        m_rightclicked = true;
        emit mouseRightClicked(event->pos());
    }

    QTableWidget::mousePressEvent(event);
}

void LevelWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_clicked = false;
        emit mouseReleased();
    }
    else if (event->button() == Qt::RightButton) {
        m_rightclicked = false;
        emit mouseReleased();
    }

    QTableWidget::mouseReleaseEvent(event);
}
