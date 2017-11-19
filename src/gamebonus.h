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

#ifndef GAMEBONUS_H
#define GAMEBONUS_H

#include <QPixmap>
#include <QString>


#define BONUS_FOR_SECOND  2
#define ITEM_SCORE        1
#define TARGET_SCORE      3



class GameScene;
struct PlayerInfo;
struct LevelPackInfo;


struct ItemBonusInfo
{
  ItemBonusInfo() :
      levelCount(0), totalCount(0), count(0)
  {
  }

  inline void addScore(int score)
  {
    levelCount += score;
    totalCount += score;
    count += score;
  }

  inline void spendScore(int score)
  {
    count -= score;
  }

  int levelCount, totalCount, count;
};


struct BonusInfo
{
  BonusInfo(const QRect &rect, int score = 0,
            const QString &resource = "",
            const QString &name = "", const QString &comment = "");

  BonusInfo(const QRect &rect, int score, const QPixmap &pixmap, const QString &name, const QString &comment);

  BonusInfo(int score, const QPixmap &pixmap, const QString &name, const QString &comment);

  BonusInfo(const QString &name, const QString &comment);

  void initFrom(BonusInfo *source);

  inline bool isEmpty() const { return !score; }
  inline void setEmpty() { score = 0; }

  QRect rect;
  QPixmap pixmap;
  int score;
  QString name, comment;
};


class GameBonus : public QObject
{
    Q_OBJECT
public:
    GameBonus();

    void setupItems(int count);

    void readProfile(LevelPackInfo *lpi, GameScene *scene);
    void writeProfile(LevelPackInfo *lpi);

    void initGraphics(GameScene *scene);

    void addItemScore(int id, int score) { items[id].addScore(score); }

    inline bool isActive() const { return bonusId >= 0; }

    int collectedOnLevel() const;
    int collectedTotal() const;

    void drawBonusMenu(GameScene *scene, QPainter &p);
    void showBonusMenu(GameScene *scene, int idx);
    void hideBonusMenu(GameScene *scene);

    void updateItems(GameScene *scene, QPainter &p);

    void checkMouseActions(GameScene *scene, const QPoint &pos);
    bool checkMouseHover(const QPoint &pos);

private:
    void drawBonusInfo(GameScene *scene, QPainter &p, BonusInfo *info, int idx);

    void activateBonus(GameScene *scene, BonusInfo *info, int idx);

    void updateRects(int cnt);

    int bonusId;
    QList<QRect> bonusRects;

    QList<BonusInfo*> bonusInfo;

    QList<ItemBonusInfo> items;

    int diff;
    bool puzzle;
};

extern GameBonus * gameBonus;

#endif // GAMEBONUS_H
