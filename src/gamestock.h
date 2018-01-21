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

#ifndef GAMESTOCK_H
#define GAMESTOCK_H

#include <QFont>
#include <QCursor>
#include <QPixmap>
#include <QList>

class GameStock;
extern GameStock *gameStock;

class GameStock
{
public:
    GameStock();

    QFont Font8;
    QFont Font12;
    QFont Font20;
    QFont Font40;
    QFont Font60;

    QCursor GameCursor;

    QPixmap GameLogoBig;
    QPixmap MenuBackground;

    QPixmap Concrete;
    QPixmap Target1;
    QPixmap Target2;
    QPixmap Block1;
    QPixmap Block2;

    QList<QPixmap> Items;

    QPixmap Clock;
    QPixmap Score;

    static void init() { gameStock = new GameStock(); }

    void initGraphics();
};

#endif // GAMESTOCK_H
