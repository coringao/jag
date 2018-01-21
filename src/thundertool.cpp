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

#include "thundertool.h"
#include "gameitem.h"
#include "gamesound.h"
#include "gamebonus.h"

#include "scene_if.h"

ThunderTool::ThunderTool(int x, int y, int score) : GameTool(x,y, score, "cross")
{
  bonusInfo = new BonusInfo(1000, myPixmap, tr("Row Blaster"),
                            tr("Removes items in a row"));
}

GameTool::ToolAction ThunderTool::checkItemState(int row, int col)
{
  int tr = myToolset->toolRow(), tc = myToolset->toolCol();

  PlaceInfo &pi1 = scene->data(tr,tc);
  if (pi1.empty())
    return ToolOutOfRange;

  if (row == tr)
  {
    PlaceInfo &pi = scene->data(row,col);
    if (pi.itemCanBeHighlighted())
    {
      if (!pi1.itemCanBeHighlighted())
        return ToolInactive;

      return ToolActive;
    }
    if (!pi.empty())
      return ToolInactive;
  }

  return ToolOutOfRange;
}


bool ThunderTool::checkItemClick(int row, int col)
{
  PlaceInfo &pi = scene->data(row,col);

  if (!pi.itemCanBeHighlighted())
    return false;

  int cx = -1;
  for (int j = 0; j < scene->numCols(); j++)
  {
    PlaceInfo &pi = scene->data(row,j);

    if (pi.itemCanBeHighlighted())
    {
      scene->removeAndCountItem(row,j);

      scene->createPixmapPopup(scene->col2x(j), scene->row2y(row), 0, 5*cx, myPixmap, 5);
    }

    cx = -cx;
  }

  sndEngine->playSound(GameSound::sndRow);

  return true;
}

