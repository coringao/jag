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

#include "baseitem.h"

BaseItem::BaseItem(qreal opacity, int steps) :
    myOpacity(opacity),
    myStep(steps)
{
  op_step = myOpacity/(double)steps;
}


////////////////////////////////////////////////////////////////////////////////

PixmapItem::PixmapItem(int x, int y, int dx, int dy, const QPixmap &pm, int steps) :  BaseItem(1, steps),
    myX(x), myY(y),
    myDx(dx), myDy(dy),
    myPixmap(pm)
{
}

bool PixmapItem::advance()
{
  if (myStep-- <= 0)
    return false;

  myX += myDx;
  myY += myDy;

  myOpacity -= op_step;

  return true;
}

void PixmapItem::paint(QPainter &painter)
{
  painter.setOpacity(myOpacity);
  painter.drawPixmap(myX, myY, myPixmap);
}

////////////////////////////////////////////////////////////////////////////////

TextItem::TextItem(QRect rect, const QString &text, int textFlags, const QFont &font, QColor color,
         qreal opacity, int staysteps, int steps, int dx, int dy) :
  BaseItem(opacity, steps),
  myRect(rect),
  myText(text),
  myFlags(textFlags),
  myFont(font),
  myColor(color),
  myStaySteps(staysteps),
  myDx(dx), myDy(dy)
{
  op_step = myOpacity/(double)steps;
}

bool TextItem::advance()
{
  if (myStaySteps)
  {
    myStaySteps--;
    return true;
  }

  if (myStep-- <= 0)
    return false;

  myRect.moveLeft(myRect.left() + myDx);
  myRect.moveTop(myRect.top() + myDy);

  myOpacity -= op_step;

  return true;
}

void TextItem::paint(QPainter &painter)
{
  painter.setOpacity(myOpacity);
  painter.setFont(myFont);
  painter.setPen(QPen(myColor));
  painter.drawText(myRect, myFlags, myText);
}

