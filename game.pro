###############################################################################
# *
# * This file is part of JAG, Puzzle game where the goal is to break all
# * the target pieces in each level and do this before the time runs out.
# *
# * Many thanks to XlabSoft & Ind. Infosystems, the originals authors of JAG.
# *
# * Copyright holder 2009-2012 Developed by XlabSoft & Industrial Infosystems
# * Work continued by 2017 Carlos Donizete Froes [a.k.a coringao]
# *	
# * JAG is free software: you can redistribute it and/or modify
# * it under the terms of the GNU General Public License as published by
# * the Free Software Foundation, either version 3 of the License, or
# * any later version.
# *
# * JAG is distributed in the hope that it will be useful,
# * but WITHOUT ANY WARRANTY; without even the implied warranty of
# * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# * GNU General Public License for more details.
# *
# * You should have received a copy of the GNU General Public License
# * along with JAG. If not, see <http://www.gnu.org/licenses/>.
# *
###############################################################################

QT += gui opengl xml x11extras
TARGET = ./bin/jag
TEMPLATE = app

LIBS += -lX11 -lSDL2 -lSDL2_mixer -lXrandr

OBJECTS_DIR += src
MOC_DIR += src
RCC_DIR += src
UI_DIR += src

SOURCES += src/main.cpp \
	src/gamewidget.cpp \
	src/gamescene.cpp \
	src/gameitem.cpp \
	src/gamepaint.cpp \
	src/gamecontrol.cpp \
	src/baseitem.cpp \
	src/gamemenu.cpp \
	src/gametools.cpp \
	src/hammertool.cpp \
	src/bighammertool.cpp \
	src/bombtool.cpp \
	src/gamesound.cpp \
	src/menucontrol.cpp \
	src/gameprofile.cpp \
	src/thundertool.cpp \
	src/smallhammertool.cpp \
	src/clocktool.cpp \
	src/gamestock.cpp \
	src/randomkilltool.cpp \
	src/mixertool.cpp \
	src/unblocktool.cpp \
	src/twintool.cpp \
	src/displaywrapper.cpp \
	src/gamebonus.cpp \
	src/gamestatics.cpp \
	src/gamestat.cpp \
	src/gamebackground.cpp \
	src/consttools.cpp \
	src/gamexml.cpp \
	src/scaler.cpp
HEADERS += src/gamewidget.h \
	src/gamescene.h \
	src/defines.h \
	src/gameitem.h \
	src/baseitem.h \
	src/gamemenu.h \
	src/gametools.h \
	src/hammertool.h \
	src/bighammertool.h \
	src/bombtool.h \
	src/gamesound.h \
	src/gameprofile.h \
	src/thundertool.h \
	src/smallhammertool.h \
	src/clocktool.h \
	src/gamestock.h \
	src/randomkilltool.h \
	src/mixertool.h \
	src/unblocktool.h \
	src/twintool.h \
	src/displaywrapper.h \
	src/gamebonus.h \
	src/scene_if.h \
	src/gamestat.h \
	src/gamebackground.h \
	src/consttools.h \
	src/scaler.h \
	src/version.h
RESOURCES += src/resources.qrc
FORMS += src/menu.ui
TRANSLATIONS += data/lang/jag_ru.ts
