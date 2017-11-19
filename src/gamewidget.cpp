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

#include "gamewidget.h"

#include "gamescene.h"
#include "gamesound.h"
#include "gameprofile.h"
#include "gamemenu.h"

#include "displaywrapper.h"

#include "scaler.h"

QString GameWidget::resourcePath;

GameWidget::GameWidget(const QString &respath, QWidget *parent)
    : QGraphicsView(parent)
{
  resourcePath = respath;

  qsrand(QTime::currentTime().msec());

  setWindowTitle(GameName);

  // create sound engine
  sndEngine = new GameSound();
  connect(sndEngine, SIGNAL(musicFinished()), this, SLOT(playRandomMusic()));

  // create and load profile
  gameProfile = new GameProfile(this);
  gameProfile->loadProfile();

  // play music if enabled
  playRandomMusic();


  // use acceleration
  if (gameProfile->isAccelerated())
    setViewport(new QGLWidget());

  setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);

  setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  // create and setup scene
  scene = new GameScene(this);
  setScene(scene);

  // setup window
  connect(scene->gameMenu(), SIGNAL(menuVideoModeChanged()),
          this, SLOT(setVideoMode()));

  // switch to the screen if possible
  PlayerInfo *pl = gameProfile->currentPlayer();
  //move(pl->x, pl->y);

  // check if it is out of the screen?
  QSize extra;
  QDesktopWidget desktop;
  for (int ff = 0; ff < desktop.screenCount(); ff++ )
     extra += desktop.screenGeometry(ff).size();
  if (pl->x >= extra.width())
    pl->x = extra.width()-100;
  if (pl->y >= extra.height())
    pl->y = extra.height()-100;
  if (pl->y < 0)
    pl->y = 0;

  move(pl->x, pl->y);

  setVideoMode();
}

GameWidget::~GameWidget()
{
  gameProfile->setWindowPos(x(),y());
  gameProfile->setScreen(QDesktopWidget().screenNumber(this));
  gameProfile->saveProfile();

  delete sndEngine;
  delete gameProfile;

  QApplication::quit();
}

void GameWidget::closeEvent(QCloseEvent *event)
{
    if (!scene->confirmExit())
        event->ignore();
}

void GameWidget::drawBackground ( QPainter * painter, const QRectF & rect )
{
  painter->fillRect(rect, Qt::black);

  scene->drawBackground(painter, rect);
}

void GameWidget::keyPressEvent ( QKeyEvent * keyEvent )
{
  scene->keyPressEvent(keyEvent);
}

void GameWidget::focusOutEvent ( QFocusEvent * event )
{
  QWidget::focusOutEvent(event);

  scene->pauseGame();
}

void GameWidget::setVideoMode()
{
  // setup scaler
  scaler->rescale(gameProfile->screenWidth(), gameProfile->screenHeight());

  // restore video mode (to avoid any issues)
  DisplayWrapper::restoreVideoMode();
  showNormal();
  QApplication::processEvents();

  if (gameProfile->isFullscreen())
  {
    // set full screen mode
    if (!DisplayWrapper::switchVideoMode(WIDTH,HEIGHT,0,true))
    {
        qDebug() << "Unable to change resolution.";
    }

    showFullScreen();
  }
  else
  {
    PlayerInfo *pl = gameProfile->currentPlayer();
    if (pl->y < 0)
      pl->y = 0;
    move(pl->x, pl->y);
  }

  // resize window
  setFixedSize(WIDTH,HEIGHT);
  setSceneRect(1, 1, WIDTH-2, HEIGHT-2);

  // update profile mode
  gameProfile->setVideoMode(WIDTH, HEIGHT);

  // invoke graphics update
  scene->initGraphics();
}

void GameWidget::playRandomMusic()
{
  QStringList ext; ext << "*.mp3" << "*.wav" << "*.mod" << "*.mid";
  QString path(resourcePath + "/music");
  QStringList entryList = QDir(path).entryList(ext);
//  qDebug() << entryList;
  if (entryList.count())
  {
    int r = qrand() % entryList.count();
//    qDebug() << path + "/" + entryList.at(r);
    sndEngine->loadMusic(path + "/" + entryList.at(r));
    sndEngine->playMusic();
  }
}
