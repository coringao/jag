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

#include "twintool.h"
#include "gamesound.h"
#include "gamebonus.h"

#include "scene_if.h"

TwinTool::TwinTool(int x, int y, int score) : GameTool(x,y, score, "twins")
{
  bonusInfo = new BonusInfo(1000, myPixmap, tr("Twin Blaster"),
                            tr("Removes all the identical items from the field"));
}

GameTool::ToolAction TwinTool::checkItemState(int row, int col)
{
  PlaceInfo &pi = scene->data(row,col);
  PlaceInfo &pi1 = scene->data(myToolset->toolRow(), myToolset->toolCol());

  if (pi.itemCanBeHighlighted() && pi1.itemCanBeHighlighted())
  {
    if (pi1.item->id() == pi.item->id())
      return ToolActive;
  }

  return ToolOutOfRange;
}

bool TwinTool::checkItemClick(int row, int col)
{
  PlaceInfo &pi = scene->data(row,col);
  if (pi.itemCanBeHighlighted())
  {
    quint8 id = pi.item->id();
    int rows = scene->numRows();
    int cols = scene->numCols();

    for (int i = 0; i < rows; i++)
    {
      for (int j = 0; j < cols; j++)
      {
        PlaceInfo &pi1 = scene->data(i,j);
        if (pi1.itemCanBeHighlighted())
        {
          if (pi1.item->id() == id)
          {
            // remove block
            scene->removeAndCountItem(i,j);

            //scene->createPixmapPopup(scene->col2x(j), scene->row2y(i), 0, 5, myPixmap, 5);
            scene->createPixmapPopup(scene->col2x(j), scene->row2y(i), 0, -5, myPixmap, 5);
          }
        }
      }
    }

    sndEngine->playSound(GameSound::sndTwin);

    return true;
  }

  return false;
}
