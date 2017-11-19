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

#include "gameitem.h"

GameItem::GameItem(quint8 id) :
  myId(id),
  myState(IdleState),
  myXoff(0), myYoff(0),
  myDx(0), myDy(0),
  myOpacity(1)
{
}

void GameItem::idle()
{
  myState = IdleState;
  setOpacity(1);
  myXoff = myYoff = 0;
  myDx = myDy = 0;
}

void GameItem::die()
{
  myState = DyingState;
  setOpacity(1);
  myCount = 5;
}

void GameItem::scheduleDeath()
{
  myState = NotAliveState;
}

void GameItem::born()
{
  myState = BornState;
  setOpacity(0);
  myCount = 5;
}

void GameItem::fall(int dx, int dy)
{
  myState = FallingState;
  setOpacity(1);
  myDx = dx;
  myDy = dy;
  myXoff = myYoff = 0;
  myCount = 5;
}

void GameItem::select()
{
  myState = SelectedState;
  setOpacity(1);
  myCount = 10;
}

void GameItem::advance()
{
  switch (myState)
  {
    case DyingState:
      myOpacity -= 0.2;
      break;

    case FallingState:
      if (!--myCount)
        idle();
      else
      {
        myXoff = -11*myDx*myCount;
        myYoff = -11*myDy*myCount;
      }
      break;

    case BornState:
      myOpacity += 0.2;
      if (!--myCount)
        idle();
      break;

    case SelectedState:
      myOpacity -= 0.05;
      if (!--myCount)
      {
        myOpacity = 1;
        myCount = 10;
      }
      break;

    default: ;
  }
}

