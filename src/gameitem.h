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

#ifndef GAMEITEM_H
#define GAMEITEM_H

#include "defines.h"


class GameItem
{
  public:
    enum ItemState { IdleState, NotAliveState, DyingState, FallingState, BornState,
                     SelectedState };

    GameItem(quint8 id);

    inline quint8 id() const { return myId; }
    inline void setId(quint8 newid) { myId = newid; }

    inline int dx() const { return myXoff; }
    inline int dy() const { return myYoff; }

    inline qreal opacity() const { return myOpacity; }
    inline void setOpacity(qreal val) { myOpacity = val; }

    void advance();

    void idle();
    inline bool isIdle() const { return myState == IdleState; }

    void die();
    inline bool isDying() const { return myState == DyingState; }

    void scheduleDeath();
    inline bool isNotAlive() const { return myState == NotAliveState; }

    void fall(int dx, int dy);
    inline bool isFalling() const { return myState == FallingState; }

    void born();
    inline bool isBorning() const { return myState == BornState; }

    void select();
    inline bool isSelected() const { return myState == SelectedState; }

  protected:

    quint8 myId;
    ItemState myState;

    int myCount;

    int myXoff, myYoff;
    int myDx, myDy;

    qreal myOpacity;
};

#endif // GAMEITEM_H
