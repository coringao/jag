###############################################################################
#  
# * This file is part of JAG, Puzzle game where the goal is to break all
# * the target pieces in each level and do this before the time runs out.
# *
# * Many thanks to XlabSoft & Ind. Infosystems, the originals authors of JAG.
# *
# * Copyright holder 2009-2012 Developed by XlabSoft & Industrial Infosystems
# * Work continued by 2017-2018 Carlos Donizete Froes [a.k.a coringao]
# *
# * JAG is free software: you can redistribute it and/or modify it under
# * the terms of the GNU General Public License as published by the
# * Free Software Foundation, either version 3 of the License,
# * or any later version.
#
###############################################################################

QT += gui core widgets xml x11extras
TARGET = jag-editor
TEMPLATE = app

unix: {
	target.path = /usr/games/
	INSTALLS += target
	datas.path = /usr/share/games/jag/editor/
	datas.files = images
	INSTALLS += datas
}

TEMPLATE = app
SOURCES += main.cpp \
	mainwindow.cpp \
	levelwidget.cpp \
	levelpack.cpp
HEADERS += mainwindow.h \
	defines.h \
	levelwidget.h \
	levelpack.h
FORMS += mainwindow.ui \
	levelpack.ui
RESOURCES += editor.qrc
