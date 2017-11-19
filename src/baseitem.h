/*
 *
 * This file is part of JAG, Puzzle game where the goal is to break all
 * the target pieces in each level and do this before the time runs out.
 *
 * Many thanks to XlabSoft & Ind. Infosystems, the originals authors of JAG.
 *
 * Copyright holder 2009-2012 Developed by XlabSoft & Industrial Infosystems
 * Work continued by 2017 Carlos Donizete Froes [a.k.a coringao]
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

#ifndef BASEITEM_H
#define BASEITEM_H

#include <QPainter>
#include <QString>

////////////////////////////////////////////////////////////////////////////////

class BaseItem
{
public:
  BaseItem(qreal opacity, int steps);
  virtual ~BaseItem() {}

  virtual bool advance() = 0;

  virtual void paint(QPainter &painter) = 0;

protected:
  qreal myOpacity, op_step;
  int myStep;
};

////////////////////////////////////////////////////////////////////////////////

class PixmapItem : public BaseItem
{
public:
    PixmapItem(int x, int y, int dx, int dy, const QPixmap &pm, int steps);
    virtual ~PixmapItem() {}

    bool advance();

    void paint(QPainter &painter);

protected:
    int myX, myY;
    int myDx, myDy;
    QPixmap myPixmap;
};

////////////////////////////////////////////////////////////////////////////////

class TextItem : public BaseItem
{
public:
    TextItem(QRect rect, const QString &text, int textFlags, const QFont &font, QColor color,
             qreal opacity, int staysteps, int steps, int dx = 0, int dy = 0);
    virtual ~TextItem() {}

    virtual bool advance();

    virtual void paint(QPainter &painter);

protected:
    QRect myRect;
    QString myText;
    int myFlags;
    QFont myFont;
    QColor myColor;
    int myStaySteps;
    int myDx, myDy;
};

////////////////////////////////////////////////////////////////////////////////

#endif // BASEITEM_H
