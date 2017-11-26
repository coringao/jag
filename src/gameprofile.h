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

#ifndef GAMEPROFILE_H
#define GAMEPROFILE_H

#include <QStringList>
#include <QObject>
#include <QXmlStreamReader>

#define DIFF_LOW    1
#define DIFF_NORMAL 2
#define DIFF_HARD   3

#define LANG_DEFAULT "English"

struct ItemInfo
{
  ItemInfo() :
      totalCount(0), localCount(0)
  {
  }

  int totalCount, localCount;
};

struct LevelPackInfo
{
  LevelPackInfo(const QString &s) :
      levelpack(s),
      diff(DIFF_NORMAL), mode(0),
      score(0), localScore(0), level(1),
      time_bonus(0), speed_bonus(0), score_bonus(0), speed_mag_bonus(2),
      next_tool(2)  { }

  void init();

  bool isPuzzle() { return mode == 1; }

  QString levelpack;
  int diff, mode;

  // game progress
  int score, localScore, level;
  int time_bonus, speed_bonus, score_bonus, speed_mag_bonus;
  int next_tool;

  QList<ItemInfo> items;
};

struct PlayerInfo
{
    PlayerInfo(const QString &s) :
        name(s), theme("default"),
        currentlevelpack("default"),
        m_fullscreen(false),
        m_width(960), m_height(720),
        musicEnabled(true), soundVolume(80), musicVolume(80),
        x(0), y(0), screen(0)
        { addLevelPack("default"); }

    LevelPackInfo* currentLevelPackInfo();

    void addLevelPack(const QString &levelpack);
    void addLevelPack(LevelPackInfo* lpi);
    void setCurrentLevelPack(const QString &levelpack)
    { addLevelPack(levelpack); currentlevelpack = levelpack; }

    QString name, theme;
    QString currentlevelpack; // levelpack

    // settings
    bool m_fullscreen;
    int m_width, m_height;

    bool musicEnabled;
    int soundVolume, musicVolume;
    int x, y, screen;

    QList<LevelPackInfo*> levelpacks;
};

struct PlayerScore
{
  PlayerScore(const QString &s, int _score) :
      name(s), score(_score)  { }

  QString name;
  int score;
};


class GameProfile : public QObject
{
  Q_OBJECT

public:
    GameProfile(QObject *parent);

    PlayerInfo *currentPlayer();
    void setCurrentPlayer(const QString &name);
    void removePlayer(const QString &name);
    void renamePlayer(const QString &before, const QString &after);

    void saveProfile();
    void loadProfile();

    void loadOldProfile();   // for backward compatibility

    void saveXml();
    void loadXml();
    void readXmlUnknownElement(QXmlStreamReader &xsr);
    void readXmlPlayer(QXmlStreamReader &xsr);
    void readXmlLevelPack(QXmlStreamReader &xsr, PlayerInfo *pl);
    void readXmlLevelItem(QXmlStreamReader &xsr, LevelPackInfo *lpi);

    void setPlayerNames(const QStringList &sl);
    QStringList playerNames();

    void setGameStarted(bool yes = true) { m_started = yes; }
    bool isGameStarted()                 { return m_started; }

    void setGamePaused(bool yes = true)  { m_paused = yes; }
    bool isGamePaused()                  { return m_paused; }

    void scanThemes();
    QStringList themesList()             { return m_themes; }

    void setCurrentTheme(const QString &_theme)  { currentPlayer()->theme = _theme; }
    QString currentTheme()               { return currentPlayer()->theme; }

    void setCurrentLevelPack(const QString &_lp)  { currentPlayer()->setCurrentLevelPack(_lp); }
    QString currentLevelPack()           { return currentPlayer()->currentlevelpack; }
    int levelPackCount(const QString &lp);
    QString levelPackName(const QString &lp);

    void setFullscreen(bool yes = true)  { currentPlayer()->m_fullscreen = yes; }
    bool isFullscreen()                  { return currentPlayer()->m_fullscreen; }

    void setAccelerated(bool yes = true)    { m_accel = yes; }
    bool isAccelerated()                    { return m_accel; }

    inline int screenWidth()            { return currentPlayer()->m_width; }
    inline int screenHeight()           { return currentPlayer()->m_height; }
    inline void setVideoMode(int w, int h)     { currentPlayer()->m_width = w; currentPlayer()->m_height = h; }

    inline void setWindowPos(int xx, int yy) { currentPlayer()->x = xx; currentPlayer()->y = yy; }
    inline void setScreen(int screen) { currentPlayer()->screen = screen; }

//    void addTopTenPlayer(PlayerScore ps);
//  QList<PlayerScore> topTenList()      { return m_topten; }

signals:
  void profileChanged();

private:
    void saveTopTen();
    void loadTopTen();

    int m_current;
    QList<PlayerInfo*> m_players;
//    QList<PlayerScore> m_topten;
    QStringList m_themes;
    QString userPath;

    bool m_started, m_paused, m_accel;
};

extern GameProfile* gameProfile;

#endif // GAMEPROFILE_H
