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

#include "randomkilltool.h"
#include "gamesound.h"
#include "gamebonus.h"

#include "scene_if.h"

RandomKillTool::RandomKillTool(int x, int y, int score) : GameTool(x,y, score, "bolt")
{
  bonusInfo = new BonusInfo(1000, myPixmap, tr("Bolt"),
                            tr("Randomly removes items from the field"));
}

bool RandomKillTool::checkToolClick()
{
  if (myProgress++ == 10)
  {
    myProgress = 0;
    return false;
  }

  // skip every 2nd frame
  if (myProgress & 1)
    return true;


  const PlaceInfo *data = scene->data();

  const int max = MAX_COLS*MAX_ROWS;
  QList<int> list;

  for (int i = 0; i < max; i++)
  {
    if (data[i].itemCanBeHighlighted())
      list.append(i);
  }

  for (int i = 0; i < 5; i++)
  {
    int i1 = list.at(qrand() % list.count());
    list.removeAt(i1);

    int row = i1 / MAX_COLS;
    int col = i1 % MAX_COLS;

    scene->removeAndCountItem(row, col);

    scene->createPixmapPopup(scene->col2x(col), scene->row2y(row), 0, 5, myPixmap, 5);
//    scene->createPixmapPopup(scene->col2x(col), scene->row2y(row), 0, -5, myPixmap, 5);
  }

  sndEngine->playSound(GameSound::sndRandomKill);

  return true;
}

