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

#ifndef CONSTTOOLS_H
#define CONSTTOOLS_H

#include "gametools.h"

#include <QPixmap>
#include <QPainter>

////////////////////////////////////////////////////////////////////////////////

class ConstBonus : public GameTool
{
  Q_OBJECT
public:
  ConstBonus(int x, int y, int score, const QString &resource);
  virtual ~ConstBonus() {}

  virtual ToolType type() const { return ConstTool; }

  inline int value() const { return bonusValue; }
  inline void setValue(int val) { bonusValue = val; }

protected:
  QPixmap smallPixmap;
  int bonusValue;
};

////////////////////////////////////////////////////////////////////////////////

class MagBonus : public ConstBonus
{
    Q_OBJECT
public:
    MagBonus(int x, int y, int score);
    virtual ~MagBonus() {}

    virtual bool checkToolClick();
    virtual void advanceAndPaint(QPainter &p, int currentScore);
};

////////////////////////////////////////////////////////////////////////////////

class TimerBonus : public ConstBonus
{
    Q_OBJECT
public:
    TimerBonus(int x, int y, int score);
    virtual ~TimerBonus() {}

    virtual bool checkToolClick();
    virtual void advanceAndPaint(QPainter &p, int currentScore);
};

////////////////////////////////////////////////////////////////////////////////

class ScoreBonus : public ConstBonus
{
    Q_OBJECT
public:
    ScoreBonus(int x, int y, int score);
    virtual ~ScoreBonus() {}

    virtual bool checkToolClick();
    virtual void advanceAndPaint(QPainter &p, int currentScore);
};

////////////////////////////////////////////////////////////////////////////////

class ClockBonus : public ConstBonus
{
    Q_OBJECT
public:
    ClockBonus(int x, int y, int score);
    virtual ~ClockBonus() {}

    virtual bool checkToolClick();
    virtual void advanceAndPaint(QPainter &p, int currentScore);
};

////////////////////////////////////////////////////////////////////////////////

#endif // CONSTTOOLS_H
