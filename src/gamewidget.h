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

#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QGraphicsView>


class GameScene;


class GameWidget : public QGraphicsView
{
    Q_OBJECT

public:
    GameWidget(const QString &respath, QWidget *parent = 0);
    ~GameWidget();

    static const QString& getResourcePath() { return resourcePath; }

public slots:
    void setVideoMode();
    void playRandomMusic();

protected:
    void closeEvent(QCloseEvent *event);

private:
    void drawBackground(QPainter *painter, const QRectF &rect);
    void keyPressEvent(QKeyEvent *keyEvent);
    void focusOutEvent(QFocusEvent *event);

    GameScene *scene;

    static QString resourcePath;
};

#endif // GAMEWIDGET_H
