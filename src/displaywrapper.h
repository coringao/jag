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

#ifndef DISPLAYWRAPPER_H
#define DISPLAYWRAPPER_H

#include <QStringList>
#include <QWidget>
#include <QTextStream>
#include <X11/Xlib.h>
#include <X11/extensions/Xrandr.h>
#include <QX11Info>

struct VideoModeInfo
{
  int width, height;
  int bpp;
};

class DisplayWrapper
{
public:
  DisplayWrapper();
  ~DisplayWrapper();

  static void init(bool filter=true, int minWidth=800, int minHeight=600)
  { dwrapper.dw_init(filter,minWidth,minHeight); }

  static bool switchVideoMode(int w, int h, int bpp, bool fs)
  { return dwrapper.dw_switchMode(w,h,bpp,fs); }

  static void restoreVideoMode()
  { dwrapper.dw_restoreMode(); }

  static const QStringList& listModes() { return dwrapper.modeNames; }

  static VideoModeInfo currentVideoMode() { return dwrapper.dw_currentMode(); }

  static void setBaseWidget(QWidget *widget) { dwrapper.base_widget = widget; }

private:
  bool dw_switchMode(int w, int h, int bpp, bool fs);
  void dw_restoreMode();
  void dw_init(bool filter, int minWidth, int minHeight);
  VideoModeInfo dw_currentMode();

  bool readScreenSubSection(QTextStream &ts, QString &xmodes, int &depth);
  void parseModes(QString &modes, QList<QPair<int,int> > &xmodes);
  bool readScreenXconf(QList<QPair<int,int> > &xmodes, int &depth);

  static DisplayWrapper dwrapper;

  QWidget *base_widget;
  int base_width, base_height, base_bpp;

  QStringList modeNames;
  QList<VideoModeInfo> modes;
};

#endif // DISPLAYWRAPPER_H
