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

#include "unblocktool.h"
#include "gameitem.h"
#include "gamesound.h"
#include "gamebonus.h"

#include "scene_if.h"

UnblockTool::UnblockTool(int x, int y, int score) : GameTool(x, y, score, "unblock")
{
  bonusInfo = new BonusInfo(1000, myPixmap, tr("Unblocker"),
                            tr("Removes single block from item"));
}

GameTool::ToolAction UnblockTool::checkItemState(int row, int col)
{
  if (row == myToolset->toolRow() && col == myToolset->toolCol())
  {
    PlaceInfo &pi = scene->data(row,col);
    if (pi.itemCanBeHighlighted() && pi.hasBlock())
      return ToolActive;
    if (!pi.empty())
      return ToolInactive;
  }

  return ToolOutOfRange;
}

bool UnblockTool::checkItemClick(int row, int col)
{
  PlaceInfo &pi = scene->data(row,col);
  if (pi.itemCanBeHighlighted() && pi.hasBlock())
  {
    // remove block
    scene->removeBlock(pi,row,col);

    scene->createPixmapPopup(scene->col2x(col), scene->row2y(row), 0, 5, myPixmap, 5);
    scene->createPixmapPopup(scene->col2x(col), scene->row2y(row), 0, -5, myPixmap, 5);

//    sndEngine->playSound(GameSound::sndUnblock);

    return true;
  }

  return false;
}
