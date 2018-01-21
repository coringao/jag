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

#include "gamescene.h"
#include "gameitem.h"
#include "gamemenu.h"
#include "gametools.h"
#include "gamebonus.h"
#include "gameprofile.h"
#include "gamestat.h"

#include <QGraphicsSceneMouseEvent>

////////////////////////////////////////////////////////////////////////////////

void GameScene::keyPressEvent ( QKeyEvent * keyEvent )
{
  if (!menu->isActive())
  {
    switch (keyEvent->key())
    {
      case Qt::Key_Escape:
      {
          if (gameBonus->isActive())
          {
            gameBonus->hideBonusMenu(this);
            break;
          }

          if (stat_active)
          {
            if (stat->code == STAT_GAME_WON)
            {
              exitToMainMenu();
              break;
            }

            runNextLevel();
            break;
          }

          pauseGame();
          break;
      }

#if 0
      // that's only for debugging reasons
      case Qt::Key_1:
      case Qt::Key_2:
      case Qt::Key_3:
      case Qt::Key_4:
      case Qt::Key_5:
      case Qt::Key_6:
      case Qt::Key_7:
      case Qt::Key_8:
      {
          int id = keyEvent->key() - Qt::Key_1;
          if (activeItems.count() <= id)
            return;
          id = activeItems.at(id);
          gameBonus->addItemScore(id,100);
          break;
      }

      case Qt::Key_9:
        score += 1000;
        toolset->addScore(1000);
        break;

      case Qt::Key_W:
        levelWon();
        break;

//      case Qt::Key_X:
//        level = max_level;
//        gameProfile->currentPlayer()->level = level;
//        levelWon();
//        break;

      case Qt::Key_F:
        time = 2;
        break;

      case Qt::Key_H:
        hintAvailableMoves();
        break;

      case Qt::Key_J:
        hintMove = false;
        break;
#endif
      default:;
    }
  }
  else {
      QGraphicsScene::keyPressEvent(keyEvent);
  }
}

////////////////////////////////////////////////////////////////////////////////

void GameScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
  QGraphicsScene::mousePressEvent(mouseEvent);
  if (mouseEvent->isAccepted())
    return;

  mouseEvent->accept();

  // click on menu shortcuts
  if (mouseEvent->button() == Qt::LeftButton)
      menu->checkMenuMouseActions(mouseEvent->scenePos().toPoint());

  if (inputDisabled || paintState)
    return;

  if (mouseEvent->button() == Qt::LeftButton)
  {
    // lets add more randomness
    qsrand(QDateTime::currentDateTime().toTime_t());

    // find position
    lastClickPos = mouseEvent->scenePos();
  }
}

////////////////////////////////////////////////////////////////////////////////

void GameScene::mouseMoveEvent ( QGraphicsSceneMouseEvent *mouseEvent )
{
  QGraphicsScene::mouseMoveEvent(mouseEvent);
  if (mouseEvent->isAccepted())
    return;

  // scene
  cursorPos = mouseEvent->scenePos();

  mouseEvent->accept();

  if (inputDisabled || paintState)
    return;

  // simulate a click when mouse is moved with left button pressed while in selection mode
  if (mouseEvent->buttons() & Qt::LeftButton && moveState == MS_SELECTED && !toolset->current())
  {
    // find position
    lastClickPos = mouseEvent->scenePos();
    return;
  }

  // check for hovers
  QPoint pos = cursorPos.toPoint();
  if (toolset->checkMouseHover(pos))
    return;
  if (gameBonus->checkMouseHover(pos))
    return;

  removeHint();
}

