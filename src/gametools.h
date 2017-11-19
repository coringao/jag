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

#ifndef GAMETOOLS_H
#define GAMETOOLS_H

#include <QString>
#include <QPoint>
#include <QPainter>

class GameScene;
class ToolSet;
struct PlaceInfo;
struct BonusInfo;
struct PlayerInfo;
struct LevelPackInfo;

#define ALL_TOOLS   100

class GameTool : public QObject
{
  Q_OBJECT
  friend class ToolSet;

public:
  enum ToolAction { ToolOutOfRange, ToolInactive, ToolActive };
  enum ToolType { ManualTool, AutoTool, ConstTool };

  GameTool(int x, int y, int score);
  GameTool(int x, int y, int score, const QString &resource);
  virtual ~GameTool();

  virtual ToolType type() const { return ManualTool; }

  void setBase(ToolSet *set) { myToolset = set; }
  void setCurrent();

  inline const QPixmap& pixmap() const { return myPixmap; }
  inline void setPixmap(const QPixmap &pm) { myPixmap = pm; }

  inline BonusInfo* info() const { return bonusInfo; }

  inline int score() const { return myScore; }

  inline const QPoint& pos() const { return myPos; }

  inline bool inProgress() const { return myProgress; }

  inline bool isActive() const { return myActive; }
  inline void setActive(bool act = true) { myActive = act; }

  virtual QString hint() const;

  // internal
  virtual void advanceAndPaint(QPainter &p, int currentScore);

  void animateActivation();

  // defined for manual tools
  virtual bool checkItemClick(int /*row*/, int /*col*/) { return false; }
  virtual ToolAction checkItemState(int /*row*/, int /*col*/) { return ToolOutOfRange; }

  // defined for auto tools
  virtual bool checkToolClick() { return false; }

protected:
    QPixmap myPixmap;
    QPoint myPos;
    int myScore;
    ToolSet *myToolset;
    int myProgress;
    bool myActive;
    BonusInfo *bonusInfo;

    static int stage;
};


class ToolSet
{
public:
    ToolSet();
    ~ToolSet();

    inline GameTool* current() { return currentTool; }
    inline GameTool* tool(int idx) { return tools.at(idx); }

    int bonusClock() const;
    int bonusScore() const;
    int bonusTimer() const;
    int bonusMag() const;

    void readProfile(LevelPackInfo *lpi);
    void writeProfile(LevelPackInfo *lpi);

    void initGraphics();

    void addScore(int score);

    void nextToolActivated();
    //int activeToolIndex(int score);
    inline int nextToolIndex() const { return next_tool; }

    void updateTools(QPainter &p);

    inline int toolRow() const { return myOverRow; }
    inline int toolCol() const { return myOverCol; }

    bool checkMouseHover(const QPoint &pos);
    bool checkMouseActions(const QPoint &pos);
    bool checkItemClick(int row, int col);
    GameTool::ToolAction checkItemState(int row, int col);
    void checkMouseMoved(int row, int col);
    void progressCurrent();

    bool isPuzzle() const { return puzzle; }

protected:
    QList<GameTool*> tools;
    int toolScore;
    GameTool *currentTool;
    int myOverRow, myOverCol;
    int next_tool;

    int diff;
    bool puzzle;

    class HammerTool *hammerTool;
    class BigHammerTool *bigHammerTool;
    class SmallHammerTool *smallHammerTool;
    class BombTool *bombTool;
    class ThunderTool *thunderTool;
    class ClockTool *clockTool;
    class RandomKillTool *randomKillTool;
    class MixerTool *mixerTool;
    class UnblockTool *unblockTool;
    class TwinTool *twinTool;
    class MagBonus *magBonus;
    class TimerBonus *timerBonus;
    class ScoreBonus *scoreBonus;
    class ClockBonus *clockBonus;
};

extern ToolSet * toolset;

#endif // GAMETOOLS_H
