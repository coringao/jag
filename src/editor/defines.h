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

#ifndef DEFINES_H
#define DEFINES_H

#include <QtCore>

const quint32 NoPlace         = 0;
const quint32 PlaceConcrete   = ((quint32)1) << 0;

const quint32 Target1         = ((quint32)1) << 1;
const quint32 Target2         = ((quint32)1) << 2;

const quint32 Targets         = Target1 | Target2;

const quint32 Block1          = ((quint32)1) << 3;
const quint32 Block2          = ((quint32)1) << 4;

const quint32 Blocks          = Block1 | Block2;

const quint32 ItemStart       = ((quint32)1) << 5;
const quint32 ItemAppear      = ((quint32)1) << 6;

const quint32 SelectMode      = ((quint32)1) << 7;

#endif // DEFINES_H
