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

#include "consttools.h"
#include "gamesound.h"
#include "gamewidget.h"
#include "gamestock.h"
#include "gamebonus.h"
#include "scene_if.h"

////////////////////////////////////////////////////////////////////////////////

ConstBonus::ConstBonus(int x, int y, int score, const QString &resource) :
    GameTool(x,y,score),
    bonusValue(0)
{
  myPixmap = QPixmap(GameWidget::getResourcePath() + "/bonus/" + resource + ".png")
             .scaled(X48,Y48, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

  smallPixmap = myPixmap.scaled(DX(16),DY(16), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
}

////////////////////////////////////////////////////////////////////////////////

// this increases bonus timer
TimerBonus::TimerBonus(int x, int y, int score) : ConstBonus(x,y, score, "timer")
{
  bonusInfo = new BonusInfo(tr("Score-Time Bonus"),
                            tr("Gives +1 extra second for every score-time bonus"));
}

bool TimerBonus::checkToolClick()
{
  bonusValue += 2;
  scene->createPixmapPopup(DX(980),DY(160), 0,-1, myPixmap, 20);

  sndEngine->playSound(GameSound::sndBonusGot);
  return true;
}

void TimerBonus::advanceAndPaint(QPainter &p, int currentScore)
{
  if (bonusValue)
  {
    p.setOpacity(1);
    p.setPen(Qt::white);
    p.setFont(gameStock->Font8);

    p.drawPixmap(DX(1000),DY(140), smallPixmap);
    p.drawText(DX(975),DY(140), DX(25),DY(20), Qt::AlignRight, QString("+%1").arg(bonusValue));
  }

    GameTool::advanceAndPaint(p, currentScore);
}

////////////////////////////////////////////////////////////////////////////////

// this increases magnifier
MagBonus::MagBonus(int x, int y, int score) : ConstBonus(x,y, score, "x")
{
  bonusInfo = new BonusInfo(tr("Score-Magnification Bonus"),
                            tr("Increases score magnifier by 1"));
}

bool MagBonus::checkToolClick()
{
  bonusValue += 1;
  scene->createPixmapPopup(DX(980),DY(160), 0,-1, myPixmap, 20);

  sndEngine->playSound(GameSound::sndBonusGot);
  return true;
}

void MagBonus::advanceAndPaint(QPainter &p, int currentScore)
{
  if (bonusValue > 2)
  {
    p.setOpacity(1);
    p.setPen(Qt::white);
    p.setFont(gameStock->Font8);

    p.drawPixmap(DX(1000),DY(160), smallPixmap);
    p.drawText(DX(975),DY(160), DX(25),DY(20), Qt::AlignRight, QString("x%1").arg(bonusValue));
  }

   GameTool::advanceAndPaint(p, currentScore);
}

////////////////////////////////////////////////////////////////////////////////

// this gives +1 to score
ScoreBonus::ScoreBonus(int x, int y, int score) : ConstBonus(x,y, score, "score")
{
  bonusInfo = new BonusInfo(tr("Score Bonus"),
                            tr("Gives +1 extra point for every destroyed target"));
}

bool ScoreBonus::checkToolClick()
{
  bonusValue += 1;
  scene->createPixmapPopup(DX(980),DY(10), 0,-1, myPixmap, 20);

  sndEngine->playSound(GameSound::sndBonusGot);
  return true;
}

void ScoreBonus::advanceAndPaint(QPainter &p, int currentScore)
{
  if (bonusValue)
  {
    p.setOpacity(1);
    p.setPen(Qt::white);
    p.setFont(gameStock->Font8);

    p.drawPixmap(DX(1000),DY(10), smallPixmap);
    p.drawText(DX(975),DY(10), DX(25),DY(20), Qt::AlignRight, QString("+%1").arg(bonusValue));
  }

    GameTool::advanceAndPaint(p, currentScore);
}

////////////////////////////////////////////////////////////////////////////////

// this increases time for level
ClockBonus::ClockBonus(int x, int y, int score) : ConstBonus(x,y, score, "clock")
{
  bonusInfo = new BonusInfo(tr("Time Bonus"),
                            tr("Gives +30 extra seconds for every level"));
}

bool ClockBonus::checkToolClick()
{
  bonusValue += 30;
  scene->createPixmapPopup(DX(980),DY(60), 0,-1, myPixmap, 20);

  sndEngine->playSound(GameSound::sndBonusGot);
  return true;
}

void ClockBonus::advanceAndPaint(QPainter &p, int currentScore)
{
  if (bonusValue)
  {
    p.setOpacity(1);
    p.setPen(Qt::white);
    p.setFont(gameStock->Font8);

    p.drawPixmap(DX(1000),DY(60), smallPixmap);
    p.drawText(DX(975),DY(60), DX(25),DY(20), Qt::AlignRight, QString("+%1").arg(bonusValue));
  }

    GameTool::advanceAndPaint(p, currentScore);
}

////////////////////////////////////////////////////////////////////////////////
