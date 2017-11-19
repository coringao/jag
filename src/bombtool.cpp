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

#include "bombtool.h"
#include "gameitem.h"
#include "gamesound.h"
#include "gamebonus.h"

#include "scene_if.h"

BombTool::BombTool(int x, int y, int score) : GameTool(x,y, score, "bomb")
{
  bonusInfo = new BonusInfo(1000, myPixmap, tr("Bomb"),
                            tr("Explodes a region of 9 cells"));
}

GameTool::ToolAction BombTool::checkItemState(int row, int col)
{
  int tr = myToolset->toolRow(), tc = myToolset->toolCol();

  PlaceInfo &pi = scene->data(tr,tc);
  if (pi.empty())
    return ToolOutOfRange;

  if (row >= tr-1 && row <= tr+1 && col >= tc-1 && col <= tc+1)
  {
    PlaceInfo &pi = scene->data(row,col);
    if (pi.itemCanBeHighlighted())
      return ToolActive;
    if (!pi.empty())
      return ToolInactive;
  }

  return ToolOutOfRange;
}


bool BombTool::checkItemClick(int row, int col)
{
  PlaceInfo &pi = scene->data(row,col);

  if (!pi.itemCanBeHighlighted())
    return false;

  int imax = qMin(scene->numRows()-1,row+1);
  int jmax = qMin(scene->numCols()-1,col+1);

  int rx = -1;

  for (int i = qMax(0,row-1); i <= imax; i++, rx++)
  {
    int cx = -1;

    for (int j = qMax(0,col-1); j <= jmax; j++, cx++)
    {
      PlaceInfo &pi = scene->data(i,j);
      if (pi.itemCanBeHighlighted())
      {
        scene->removeAndCountItem(i,j);

        scene->createPixmapPopup(scene->col2x(j), scene->row2y(i), 5*cx, 5*rx, myPixmap, 5);
      }
    }
  }

  sndEngine->playSound(GameSound::sndBomb);

  return true;
}
