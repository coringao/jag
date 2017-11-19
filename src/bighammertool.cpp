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

#include "bighammertool.h"
#include "gameitem.h"
#include "gamesound.h"
#include "gamebonus.h"

#include "scene_if.h"

BigHammerTool::BigHammerTool(int x, int y, int score) : GameTool(x, y, score, "big_star")
{
  bonusInfo = new BonusInfo(1000, myPixmap, tr("Super Star"),
                            tr("Acts like a star but twice powerful (2 actions at a time)"));
}

GameTool::ToolAction BigHammerTool::checkItemState(int row, int col)
{
  if (row == myToolset->toolRow() && col == myToolset->toolCol())
  {
    PlaceInfo &pi = scene->data(row,col);
    if (pi.itemCanBeHighlighted())
      return ToolActive;
    if (!pi.empty())
      return ToolInactive;
  }

  return ToolOutOfRange;
}

bool BigHammerTool::checkItemClick(int row, int col)
{
  PlaceInfo &pi = scene->data(row,col);
  if (pi.itemCanBeHighlighted())
  {
    // this only schedules a removal
    scene->removeAndCountItem(row,col);

    scene->createPixmapPopup(scene->col2x(col), scene->row2y(row), 0, 5, myPixmap, 5);
    scene->createPixmapPopup(scene->col2x(col), scene->row2y(row), 0, -5, myPixmap, 5);

    // and 2nd hit
    if (pi.itemCanBeHighlighted() || pi.item->isNotAlive())
    {
      // set item to unprocessed
      pi.setUnprocessed();
      scene->removeAndCountItem(row,col);
    }

    sndEngine->playSound(GameSound::sndBigHammer);

    return true;
  }

  return false;
}
