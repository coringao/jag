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

#include "scaler.h"

#include <QDesktopWidget>

Scaler *scaler = 0;

void Scaler::init()
{
  scaler = new Scaler();
}

Scaler::Scaler()
{
  rescale(1024,768);
}

void Scaler::rescale(int w, int h)
{
  // read actual screen size
  if (w == 0 || h == 0)
  {
    QDesktopWidget dw;
    w = dw.width();
    h = dw.height();
  }

  win_w = w;  cw = (float)win_w/1024.0;
  win_h = h;  ch = (float)win_h/768.0;

  m_x56 = (int)(cw*56);  m_y56 = (int)(ch*56);
  m_x48 = (int)(cw*48);  m_y48 = (int)(ch*48);

  m_x100 = (int)(cw*100);
  m_x900 = (int)(cw*900);
  m_x910 = (int)(cw*910);
  m_y20 = (int)(ch*20);
}
