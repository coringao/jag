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

#include "gamemenu.h"
#include "gameprofile.h"
#include "gamewidget.h"
#include "gamestock.h"

#include "scaler.h"
#include "displaywrapper.h"

#include <QSettings>


MenuWidget::MenuWidget(QWidget *parent) :
    QStackedWidget(parent)
{
    ui.setupUi(this);
    setWindowOpacity(0.7);

    ui.twHall->setColumnWidth(0, 220);
    ui.twHall->horizontalHeader()->setStretchLastSection(true);
    ui.twHall->setRowCount(10);
    for (int i = 0; i < 10; i++) {
        ui.twHall->setItem(i, 0, new QTableWidgetItem(""));
        ui.twHall->setItem(i, 1, new QTableWidgetItem(""));
    }

    // set stylesheet
    QString stylepath = ":/style/style.css";
#ifdef Q_WS_X11
    if (QSysInfo::WindowsVersion >= QSysInfo::WV_VISTA)
        stylepath = ":/style/style_vista.css";
#endif

    QString style = "";
    QFile f(stylepath);
    if (f.open(QIODevice::ReadOnly)) {
        QTextStream ts(&f);
        style = ts.readAll().simplified();
        f.close();
    }
    qApp->setStyleSheet(style);

    // load help file
    QSettings settings("xlabsoft","jag");
    QString lang = settings.value("Language", "").toString();
    QString helpfile = GameWidget::getResourcePath() +
                       "help/index";
    if (!lang.isEmpty())
      helpfile += "_" + lang;
    helpfile += ".htm";

    QString helpstring = "";
    QFile fhelp(helpfile);
    if (!fhelp.open(QIODevice::ReadOnly)) {
        helpfile = GameWidget::getResourcePath() + "help/index.htm";
        fhelp.setFileName(helpfile);
        fhelp.open(QIODevice::ReadOnly);
    }

    QTextStream ts(&fhelp);
    helpstring = ts.readAll().simplified();
    fhelp.close();

    ui.teHelp->setHtml(helpstring);

    connect(this, SIGNAL(currentChanged(int)), this, SLOT(onCurrentChanged(int)));

    setCurrentIndex(MENU_MAIN);
    startAfterSelect = false;
    setMouseTracking(true);

    m_active = false;

    // load video modes
    ui.lwVideoMode->addItems(DisplayWrapper::listModes());

    // init dynamic stuff
    initGraphics();
}

void MenuWidget::initGraphics()
{
    onCurrentChanged(0);

    buttonProfile = QRect(DX(1024 - 800)/2,DY(670), DX(200),DY(30));
    buttonLevelpack = QRect(DX(1024 - 800)/2+DX(200),DY(670), DX(200),DY(30));
}

void MenuWidget::activate(bool en)
{
    m_active = en;
    if (en)
      showNormal();
    else
      hide();
}

void MenuWidget::onCurrentChanged(int)
{
    int dy = HEIGHT < 700 ? Y48 : DY(150);

    //if (gameProfile->isGameStarted())
        move((WIDTH-width())/2, dy);
    //else
    //    move(/*WIDTH-width()-*/DX(50), Y48);
}

QString MenuWidget::selectedLevelPack()
{
    QString qs;
    int row = ui.lwLevels->currentRow();
    if (row >= 0 && row < lpacks.count())
        qs = lpacks.at(row).section('.',0,0);
    else
        qs = gameProfile->currentLevelPack();
    return qs;
}

void MenuWidget::checkMenuMouseActions(const QPoint &pos)
{
    if (isActive() && !gameProfile->isGameStarted()) {
          if (buttonProfile.contains(pos))
              on_bOptProfile_clicked();
          else if (buttonLevelpack.contains(pos))
              on_bOptLevels_clicked();
      }
}


////////////////////////////////////////////////////////////////////////////////
ConfirmDialog::ConfirmDialog(QWidget *parent, Qt::WindowFlags /*f*/):
        QDialog(parent, Qt::FramelessWindowHint)
{
    QVBoxLayout *vbl = new QVBoxLayout();

    vbl->addSpacerItem(new QSpacerItem(1, DY(10)));
    text = new QLabel("");
    text->setAlignment(Qt::AlignCenter);
    vbl->addWidget(text);
    vbl->addSpacerItem(new QSpacerItem(1, DY(10)));

    QHBoxLayout *hbl = new QHBoxLayout();
    QPushButton *bNo = new QPushButton(tr("No"));
    bNo->setFixedHeight(DY(40));
    connect(bNo, SIGNAL(clicked()), this, SLOT(onNoClicked()));
    hbl->addWidget(bNo);
    hbl->addSpacerItem(new QSpacerItem(DX(40), 1));
    QPushButton *bYes = new QPushButton(tr("Yes"));
    bYes->setFixedHeight(DY(40));
    connect(bYes, SIGNAL(clicked()), this, SLOT(onYesClicked()));
    hbl->addWidget(bYes);

    vbl->addLayout(hbl);
    setLayout(vbl);

    setWindowOpacity(0.7);
}

int ConfirmDialog::exec(const QString &qs)
{
    setFixedSize(DX(540), DY(200));
    move((WIDTH-DX(540))/2, (HEIGHT-DY(200))/2);
    text->setFont(gameStock->Font20);

    update();
    QApplication::processEvents();

    m_result = 0;
    text->setText(qs);

    QDialog::exec();
    return m_result;
}

void ConfirmDialog::onNoClicked()
{
    m_result = 0;
    close();
}

void ConfirmDialog::onYesClicked()
{
    m_result = 1;
    close();
}
