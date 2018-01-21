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

#include "gamemenu.h"
#include "gamescene.h"
#include "gameprofile.h"
#include "gamesound.h"
#include "gamewidget.h"

#include "displaywrapper.h"

#include <QSettings>
#include <QMessageBox>
#include <QInputDialog>

void MenuWidget::keyPressEvent(QKeyEvent *keyEvent)
{
    if (isActive()) {
        switch (keyEvent->key()) {
          case Qt::Key_Escape: {
            switch (currentIndex()) {
              case MENU_MAIN:
                  on_bExit_clicked();
                  break;
              case MENU_OPTIONS:
                  on_bOptBack_clicked();
                  break;
              case MENU_PAUSE:
                  on_bPauseBack_clicked();
                  break;
              case MENU_GRAPHICS:
                  on_bGraphicsBack_clicked();
                  break;
              case MENU_AUDIO:
                  on_bAudioBack_clicked();
                  break;
              case MENU_PROFILE:
                  on_bProfileBack_clicked();
                  break;
//              case MENU_HALL:
//                  on_bHallBack_clicked();
//                  break;
              case MENU_HELP:
                  on_bHelpBack_clicked();
                  break;
              case MENU_CREDITS:
                  on_bCreditsBack_clicked();
                  break;
              case MENU_LEVELS:
                  on_bLevelsBack_clicked();
                  break;
              case MENU_LANGUAGE:
                  on_bLangBack_clicked();
                  break;
            }
          }
          break;

       }
       keyEvent->accept();
    }
}

////////////////////////////////////////////////////////////////////////////////
void MenuWidget::on_bNew_clicked()
{
    if (gameProfile->currentPlayer()->name.isEmpty()) {
       // show profile select menu
       startAfterSelect = true;
       on_bOptProfile_clicked();
    }
    else {
       // start new game
       emit menuNew();
    }
}

void MenuWidget::on_bContinue_clicked()
{
    emit menuContinue();
}

void MenuWidget::on_bOptions_clicked()
{
    setCurrentIndex(MENU_OPTIONS);
}

/*
void MenuWidget::on_bHall_clicked()
{
    updateHallOfFame();
    setCurrentIndex(MENU_HALL);
}
*/

void MenuWidget::on_bHelp_clicked()
{
    setCurrentIndex(MENU_HELP);
}

void MenuWidget::on_bCredits_clicked()
{
    setCurrentIndex(MENU_CREDITS);
}

void MenuWidget::on_bExit_clicked()
{
    emit menuExit();
}

void MenuWidget::on_bOptGraphics_clicked()
{
    setCurrentIndex(MENU_GRAPHICS);

    // set themes list
    ui.lwThemes->clear();
    ui.lwThemes->addItems(gameProfile->themesList());
    QList<QListWidgetItem *> found = ui.lwThemes->findItems(gameProfile->currentTheme(), Qt::MatchFixedString);
    if (found.count())
        ui.lwThemes->setCurrentItem(found.at(0));
    else
        ui.lwThemes->setCurrentRow(0);

    // update video modes
    on_pbRefreshGraphicModes_clicked();

    // set video mode
    ui.cbFullscreenMode->setChecked(gameProfile->isFullscreen());

    ui.cbAccel->setChecked(gameProfile->isAccelerated());

    QString mode(QString("%1 x %2")
                 .arg(gameProfile->screenWidth())
                 .arg(gameProfile->screenHeight()));
    QList<QListWidgetItem *> items = ui.lwVideoMode->findItems(mode, Qt::MatchExactly);
    if (items.count())
      ui.lwVideoMode->setCurrentItem(items.first());
}

void MenuWidget::on_bOptSound_clicked()
{
  setCurrentIndex(MENU_AUDIO);

  // sounds
  ui.cbVolumeSound->setValue(gameProfile->currentPlayer()->soundVolume);
  ui.cbMuteSound->setChecked(gameProfile->currentPlayer()->soundVolume == 0);

  // music
  ui.cbVolumeMusic->setValue(gameProfile->currentPlayer()->musicVolume);
  ui.cbMuteMusic->setChecked(!gameProfile->currentPlayer()->musicEnabled);
}

void MenuWidget::on_bOptProfile_clicked()
{
    setCurrentIndex(MENU_PROFILE);
    // set name edit
    QString name = gameProfile->currentPlayer()->name;
    //ui.leName->setText(name.isEmpty() ? tr("Player") : name);
    // set users list
    ui.lwPlayersList->clear();
    ui.lwPlayersList->addItem(tr("[New Player]"));
    ui.lwPlayersList->addItems(gameProfile->playerNames());

    QList<QListWidgetItem *> found = ui.lwPlayersList->findItems(name, Qt::MatchFixedString);
    if (found.count())
        ui.lwPlayersList->setCurrentItem(found.at(0));
    else
        ui.lwPlayersList->setCurrentRow(0);
}

void MenuWidget::on_bOptLevels_clicked()
{
    setCurrentIndex(MENU_LEVELS);

    // levels list
    QStringList ext; ext << "*.lpk";
    lpacks = QDir(GameWidget::getResourcePath() + "levels/").entryList(ext);
    ui.lwLevels->clear();
    for (int i = 0; i < lpacks.count(); i++) {
        QString name = lpacks.at(i).section('.',0,0);
        int cnt = gameProfile->levelPackCount(name);
        QString packname = gameProfile->levelPackName(name);
        ui.lwLevels->addItem(tr("%1 [%2 levels]").arg(packname).arg(cnt));
    }

    QList<QListWidgetItem *> found = ui.lwLevels->findItems(gameProfile->currentLevelPack(), Qt::MatchFixedString);
    if (found.count())
        ui.lwLevels->setCurrentItem(found.at(0));
    else
        ui.lwLevels->setCurrentRow(0);
}

void MenuWidget::on_bOptLanguage_clicked()
{
    setCurrentIndex(MENU_LANGUAGE);

    // languages list
    ui.lwLanguage->clear();
    ui.lwLanguage->addItem(LANG_DEFAULT);

    QSettings settings("xlabsoft","jag");
    QString lang = settings.value("Language", "").toString();
    int index = 0;

    QString langfile = GameWidget::getResourcePath() + "lang/langlist.dat";
    QFile f(langfile);
    if (!f.open(QFile::ReadOnly | QFile::Text))
        return;
    QTextStream ts(&f);

    while (!ts.atEnd()) {
        QString qs = ts.readLine().simplified();
        QString langname = qs.section("::",0,0).simplified();
        if (!langname.isEmpty()) {
            ui.lwLanguage->addItem(langname);
            qs = qs.section("::",1,1).simplified();
            if (qs == lang)
                index = ui.lwLanguage->count() - 1;
        }
    }
    f.close();

    ui.lwLanguage->setCurrentRow(index);
}

void MenuWidget::on_bOptBack_clicked()
{
    setCurrentIndex(MENU_MAIN);
    startAfterSelect = false;
}

void MenuWidget::on_bPauseGraphics_clicked()
{
    on_bOptGraphics_clicked();
}

void MenuWidget::on_bPauseSound_clicked()
{
    on_bOptSound_clicked();
}

void MenuWidget::on_bPauseRestart_clicked()
{
    emit menuRestartLevel();
}

void MenuWidget::on_bPauseAbandon_clicked()
{
    emit menuAbandonGame();
}

void MenuWidget::on_bPauseBack_clicked()
{
    emit menuPauseBack();
}

void MenuWidget::on_pbRefreshGraphicModes_clicked()
{
  // get new modes
  DisplayWrapper::init();

  // load video modes
  ui.lwVideoMode->clear();
  ui.lwVideoMode->addItems(DisplayWrapper::listModes());
}

void MenuWidget::on_bGraphicsOk_clicked()
{
    // apply options
    QListWidgetItem *lwi = ui.lwThemes->currentItem();
    if (lwi) {
        gameProfile->setCurrentTheme(lwi->text());
        emit menuThemeChanged();
    }


    bool fs = ui.cbFullscreenMode->isChecked();

    QString tmp, mode(ui.lwVideoMode->currentItem()->text());
    int w,h; QTextStream ts(&mode); ts >> w >> tmp >> h;

    if (fs != gameProfile->isFullscreen()
      || w != gameProfile->screenWidth()
      || h != gameProfile->screenHeight())
    {
      gameProfile->setFullscreen(fs);
      gameProfile->setVideoMode(w,h);
      emit menuVideoModeChanged();
    }

    bool acc = ui.cbAccel->isChecked();
    if (acc != gameProfile->isAccelerated())
    {
      QMessageBox::information(0, tr("Restart needed"),
                               tr("In order to enable or disable acceleration, please restart JAG"),
                               QMessageBox::Close);
    }
    gameProfile->setAccelerated(acc);

    on_bGraphicsBack_clicked();
}

void MenuWidget::on_bGraphicsBack_clicked()
{
  setCurrentIndex(gameProfile->isGameStarted() ? MENU_PAUSE : MENU_OPTIONS);
}

void MenuWidget::on_bAudioBack_clicked()
{
  setCurrentIndex(gameProfile->isGameStarted() ? MENU_PAUSE : MENU_OPTIONS);
}

void MenuWidget::on_cbVolumeMusic_valueChanged(int val)
{
  sndEngine->setMusicVolume(val);
  gameProfile->currentPlayer()->musicVolume = val;
}

void MenuWidget::on_cbMuteMusic_toggled(bool on)
{
  sndEngine->enableMusic(!on);
  gameProfile->currentPlayer()->musicEnabled = !on;

  ui.cbVolumeMusic->setEnabled(!on);
}

void MenuWidget::on_cbVolumeSound_valueChanged(int val)
{
  sndEngine->setChannelVolume(val);
  gameProfile->currentPlayer()->soundVolume = val;

  sndEngine->playSound(GameSound::sndBomb);
}

void MenuWidget::on_cbMuteSound_toggled(bool on)
{
  ui.cbVolumeSound->setEnabled(!on);

  if (on) {
    sndEngine->setChannelVolume(0);
    gameProfile->currentPlayer()->soundVolume = 0;
  }
  else {
    on_cbVolumeSound_valueChanged(ui.cbVolumeSound->value());
    gameProfile->currentPlayer()->soundVolume = ui.cbVolumeSound->value();
  }
}

void MenuWidget::on_rbArcade_toggled(bool on)
{
    gameProfile->currentPlayer()->currentLevelPackInfo()->mode = on ? 0 : 1;
}

void MenuWidget::on_rbPuzzle_toggled(bool on)
{
    gameProfile->currentPlayer()->currentLevelPackInfo()->mode = on ? 1 : 0;
}

void MenuWidget::on_sliDifficulty_valueChanged(int val)
{
    gameProfile->currentPlayer()->currentLevelPackInfo()->diff = val;
    QString qs;
    switch (val) {
        case 1: qs = tr("Easy"); break;
        case 2: qs = tr("Normal"); break;
        case 3: qs = tr("Hard"); break;
        default: qs = "";
    }
    ui.labelDiff->setText(qs);
}

void MenuWidget::on_bGameStart_clicked()
{
    LevelPackInfo *lpi = gameProfile->currentPlayer()->currentLevelPackInfo();
    lpi->mode = ui.rbArcade->isChecked() ? 0 : 1;
    lpi->diff = ui.sliDifficulty->value();

    emit menuGameStart();
}

void MenuWidget::on_bGameBack_clicked()
{
  setCurrentIndex(MENU_MAIN);
}

void MenuWidget::on_bProfileSelect_clicked()
{
    if (ui.lwPlayersList->currentRow() == 0)
    { // new player clicked
      bool ok;
      QString name = QInputDialog::getText(this, tr("New Player"), tr("Enter new Player name:"),
                            QLineEdit::Normal, tr("Player"), &ok,
                            Qt::FramelessWindowHint);
      if (ok && !name.isEmpty())
      {
        QList<QListWidgetItem *> found = ui.lwPlayersList->findItems(name, Qt::MatchFixedString);
        if (found.isEmpty()) {
            ui.lwPlayersList->addItem(name);
            ui.lwPlayersList->setCurrentRow(ui.lwPlayersList->count()-1);
            gameProfile->setCurrentPlayer(name);
          } else {
            QMessageBox::critical(this, tr("Player exists"),
                                  tr("Cannot create new Player with existing name!"));
          }
      }
    }
    else {
        if (ui.lwPlayersList->currentItem()) {
            QString name = ui.lwPlayersList->currentItem()->text();
            if (!name.isEmpty()) {
                // update video mode
                bool fs = gameProfile->isFullscreen();
                int w = gameProfile->screenWidth();
                int h = gameProfile->screenHeight();

                gameProfile->setCurrentPlayer(name);

                if (fs != gameProfile->isFullscreen()
                  || w != gameProfile->screenWidth() || h != gameProfile->screenHeight())
                    emit menuVideoModeChanged();

                // update sound settings
                sndEngine->setChannelVolume(gameProfile->currentPlayer()->soundVolume);
                sndEngine->setMusicVolume(gameProfile->currentPlayer()->musicVolume);
                sndEngine->enableMusic(gameProfile->currentPlayer()->musicEnabled);

                if (startAfterSelect)
                    emit menuNew();
                else
                    on_bProfileBack_clicked();
            }
        }
    }
}

void MenuWidget::on_bProfileRename_clicked()
{
  if (ui.lwPlayersList->currentRow() > 0)
  {
    bool ok;
    QString name = QInputDialog::getText(this, tr("Rename Player"), tr("Change Player name:"),
                          QLineEdit::Normal, ui.lwPlayersList->currentItem()->text(), &ok,
                          Qt::FramelessWindowHint);
    if (ok && !name.isEmpty())
    {
      QList<QListWidgetItem *> found = ui.lwPlayersList->findItems(name, Qt::MatchFixedString);
      if (found.isEmpty()) {
        gameProfile->renamePlayer(ui.lwPlayersList->currentItem()->text(), name);
        ui.lwPlayersList->currentItem()->setText(name);
      } else {
        QMessageBox::critical(this, tr("Player exists"),
                              tr("Cannot rename to the existing name!"));
      }
    }
  }
}

void MenuWidget::on_bProfileDelete_clicked()
{
    if (ui.lwPlayersList->currentRow() <= 0) return;

    if (QMessageBox::question(this, tr("Remove Player"),
                              tr("Are you sure to remove %1?").arg(ui.lwPlayersList->currentItem()->text()),
                              QMessageBox::Ok, QMessageBox::Cancel) == QMessageBox::Cancel)
      return;

    int row = ui.lwPlayersList->currentRow();
    QListWidgetItem *item = ui.lwPlayersList->takeItem(row);
    if (item) {
        gameProfile->removePlayer(item->text());
        delete item;
    }
    if (row > 0 && row < ui.lwPlayersList->count())
        ui.lwPlayersList->setCurrentRow(row);

}

void MenuWidget::on_bProfileBack_clicked()
{
    setCurrentIndex(MENU_OPTIONS);
}

void MenuWidget::on_lwPlayersList_itemDoubleClicked(QListWidgetItem */*item*/)
{
    on_bProfileSelect_clicked();
}

/*
void MenuWidget::on_bHallBack_clicked()
{
    setCurrentIndex(MENU_MAIN);
}
*/

void MenuWidget::on_bHelpBack_clicked()
{
    setCurrentIndex(MENU_MAIN);
}

void MenuWidget::on_bCreditsBack_clicked()
{
    setCurrentIndex(MENU_MAIN);
}

void MenuWidget::on_bLevelsOk_clicked()
{
    emit menuLevelPack();
}

void MenuWidget::on_bLevelsBack_clicked()
{
    setCurrentIndex(MENU_OPTIONS);
}

void MenuWidget::on_lwLevels_itemDoubleClicked(QListWidgetItem */*item*/)
{
    on_bLevelsOk_clicked();
}

void MenuWidget::on_bLangBack_clicked()
{
    setCurrentIndex(MENU_OPTIONS);
}

void MenuWidget::on_bLangOk_clicked()
{
    QString lang;
    int row = ui.lwLanguage->currentRow();
    if (row >= 0)
        lang = ui.lwLanguage->item(row)->text();

    QString langfile = GameWidget::getResourcePath() + "lang/langlist.dat";
    QFile f(langfile);
    if (!f.open(QFile::ReadOnly | QFile::Text))
        return;
    QTextStream ts(&f);

    QSettings settings("xlabsoft","jag");
    bool found = false;
    while (!ts.atEnd()) {
        QString qs = ts.readLine().simplified();
        QString langname = qs.section("::",0,0).simplified();
        QString langid = qs.section("::",1,1).simplified();
        if (!langname.isEmpty() && langname == lang && !langid.isEmpty()) {
            QString curlang = settings.value("Language", "").toString();
            settings.setValue("Language", langid);
                found = true;
                break;
            }
        }
    f.close();

    if (!found || row == 0)
      settings.setValue("Language", "");

    if (found || row == 0)
      QMessageBox::information(0, tr("Restart needed"),
                               tr("In order to change game language,\n please restart JAG"),
                               QMessageBox::Close);
    on_bLangBack_clicked();
}

void MenuWidget::on_lwLanguage_itemDoubleClicked(QListWidgetItem */*item*/)
{
    on_bLangOk_clicked();
}

////////////////////////////////////////////////////////////////////////////////
void GameScene::on_menuNew()
{
    if (menu->isActive()) {
        // ask confirmation
        if (gameProfile->currentPlayer()->currentLevelPackInfo()->level > 1) {
            menu->hide();
            if (!dconfirm->exec(tr("Current progress will be lost.\nAre you sure you want to start new game?"))) {
                menu->showNormal();
                return;
            }
        }

        menu->setMenuPage(MENU_GAME);
        menu->activate();
    }
}

void GameScene::on_menuContinue()
{
    if (gameProfile->currentPlayer()->currentLevelPackInfo()->level > max_level) return;

    menu->activate(false);
    gameProfile->setGameStarted(true);
    gameProfile->setGamePaused(false);
    if (!initLevel(gameProfile->currentPlayer()->currentLevelPackInfo()->level))
        exitToMainMenu();
}

void GameScene::on_menuExit()
{
    // ask confirmation
    menu->hide();
    if (dconfirm->exec(tr("Are you sure you want to quit JAG?"))) {
        stopGame();
        qApp->quit();
    }
    menu->showNormal();
}

void GameScene::on_menuPauseBack()
{
    menu->activate(false);
    continueGame();
}

void GameScene::on_menuRestartLevel()
{
    menu->hide();
    if (dconfirm->exec(tr("Current level progress will be lost.\nAre you sure you want to restart?")))
    {
        if (!initLevel(gameProfile->currentPlayer()->currentLevelPackInfo()->level))
            exitToMainMenu();
        on_menuPauseBack();
        return;
    }
    menu->showNormal();
}

void GameScene::on_menuAbandonGame()
{
    menu->hide();
    if (dconfirm->exec(tr("Current level progress will be lost.\nAre you sure you want to quit?")))
    {
        // go to main menu
        exitToMainMenu();
    }
    menu->showNormal();
}

void GameScene::on_menuThemeChanged()
{
   myLock = true;
   initTheme();
   drawConcretesOnBackground();
   drawHUDonBackground();
   myLock = false;
}

void GameScene::on_menuGameStart()
{
    menu->activate(false);
    gameProfile->setGameStarted(true);
    gameProfile->setGamePaused(false);
    gameProfile->currentPlayer()->currentLevelPackInfo()->init();
    if (!initLevel(1))
        exitToMainMenu();
}

void GameScene::on_menuLevelPack()
{
    // ask to change levelpack
    menu->hide();
    QString name = menu->selectedLevelPack();
    if (gameProfile->currentLevelPack() != name) {
        if (!dconfirm->exec(tr("Are you sure you want to select this level pack?"))) {
            menu->showNormal();
            return;
        }
        gameProfile->setCurrentLevelPack(name);
        max_level = gameProfile->levelPackCount(gameProfile->currentLevelPack());
        update();
    }
    menu->showNormal();
    menu->setCurrentIndex(MENU_OPTIONS);
}

bool GameScene::confirmExit()
{
    if (gameProfile->isGameStarted())
    {
        pauseGame();
    }
    if (menu->isActive())
        menu->hide();

    if (dconfirm->exec(tr("Any unsaved progress will be lost.\nAre you sure you want to quit JAG?")))
        return true;

    if (menu->isActive())
        menu->showNormal();
    if (gameProfile->isGamePaused()) {
        menu->activate(false);
        continueGame();
    }
    return false;
}
