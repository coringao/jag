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

#include "mixertool.h"
#include "gamesound.h"
#include "gamebonus.h"

#include "scene_if.h"

MixerTool::MixerTool(int x, int y, int score) : GameTool(x,y, score, "random")
{
  bonusInfo = new BonusInfo(1000, myPixmap, tr("Mixer"),
                            tr("Randomly mixes items in the field"));
}

bool MixerTool::checkToolClick()
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

  for (int i = 0; i < 20; i++)
  {
    int i1 = list.at(qrand() % list.count());
    list.removeAt(i1);

    int row1 = i1 / MAX_COLS;
    int col1 = i1 % MAX_COLS;

    quint8 id1 = data[i1].item->id();
    quint8 id2;
    do {
      id2 = scene->randomItemId();
    } while (id2 == id1);
    data[i1].item->setId(id2);

    scene->createPixmapPopup(scene->col2x(col1), scene->row2y(row1), 0, 5, myPixmap, 5);
  }

  sndEngine->playSound(GameSound::sndMixer);

  return true;
}

