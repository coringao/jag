JAG - Arcade Puzzle 2D Game for GNU/Linux
=========================================
 
Puzzle game where the goal is to break all the target pieces in each level
and do this before the time runs out.

Move game pieces using mouse into matches of 3 or more in a straight
line horizontally or vertically.

**Necessary dependencies**
--------------------------

Because JAG is based on QT5 frameworks and SDL2 libraries, all architectures 
that are supported must be able to run the game.

> Updates, additional level packs and schemes can be downloaded
> from [JAG's website](http://jag.xlabsoft.com). Official developers site
> was deactivated at the end of 2016.

**Preferred distribution Debian/Ubuntu**
----------------------------------------

It requires the following **QT5** components and **SDL2** library:

  * Qt5 OpenGL
  * Qt5 X11Extras
  * Qt5 Xml
  * SDL2 library
  * SDL2 Mixer library

**Installation dependency:**

    # apt install qt5-qmake qt5-default qtbase5-dev qtchooser libxrandr-dev libqt5x11extras5-dev libsdl2-dev libsdl2-mixer-dev

When all these dependencies are installed to start compiling the game.

To create the game binary, do it from the source directory.

**Starting compilation:**

    $ qmake
  
    $ make

**Removing compilation:**

    $ make clean

    $ make distclean

The game binary after compilation is in **bin** directory.

    $ ./bin/jag

**License**
-----------

> **JAG** is free software: you can redistribute it and/or modify
> it under the terms of the GNU General Public License as published by
> the Free Software Foundation, either version 3 of the License, or
> any later version.

Many thanks to [XlabSoft & Industrial Infosystems](https://xlabsoft.com),
the originals authors of JAG. Official developers site was deactivated
at the end of 2016.

Copyleft (ɔ) 2009-2012 Developed by **XlabSoft & Industrial Infosystems**

Copyright (C) 2017 Work continued by **Carlos Donizete Froes [a.k.a coringao]**
