#include "displaywrapper.h"

#include <QDesktopWidget>
#include <QFile>
#include <QProcess>

DisplayWrapper DisplayWrapper::dwrapper;

#ifdef Q_OS_WIN32

DisplayWrapper::DisplayWrapper() : base_widget(0)
{
}

DisplayWrapper::~DisplayWrapper()
{
}

void DisplayWrapper::dw_init(bool filter, int minWidth, int minHeight)
{
  base_height = base_width = 0;
  base_bpp = 0;

  DEVMODE devmode;
  DWORD modenum = 0;
  VideoModeInfo mode;

  modes.clear();
  modeNames.clear();

  // get current display
  wchar_t *device = NULL;
  DISPLAY_DEVICE display_device;
  display_device.cb = sizeof(DISPLAY_DEVICE);

  if (base_widget)
  {
    QDesktopWidget desktop;
    int screen = desktop.screenNumber(base_widget);
    if (screen >= 0)
    {
      if (EnumDisplayDevices(NULL, screen, &display_device, 0))
      {
        device = display_device.DeviceName;
        //qDebug() << QString::fromWCharArray(device);
      }
    }
  }

  // enumerate display modes
  while (EnumDisplaySettings(device, modenum, &devmode))
  {
    if (devmode.dmPelsWidth >= minWidth && devmode.dmPelsHeight >= minHeight)
    {
      modeNames.append(QString("%1 x %2")
                       .arg(devmode.dmPelsWidth)
                       .arg(devmode.dmPelsHeight)
                       );

      mode.width = devmode.dmPelsWidth;
      mode.height = devmode.dmPelsHeight;
      mode.bpp = devmode.dmBitsPerPel;
      modes.append(mode);
    }
    modenum++;
  }

  if (filter)
    modeNames.removeDuplicates();
}

bool DisplayWrapper::dw_switchMode(int w, int h, int bpp, bool fs)
{
  DEVMODE originalMode;
  originalMode.dmSize = sizeof(originalMode);

  EnumDisplaySettings(0,
            ENUM_CURRENT_SETTINGS,
            &originalMode);

  DEVMODE newMode = originalMode;

  bool downgrade = false;

  // Changing the settings
  newMode.dmPelsWidth = (uint)w;
  newMode.dmPelsHeight = (uint)h;
  if (bpp > 0)
    newMode.dmBitsPerPel = (uint)bpp;
  else {
    newMode.dmBitsPerPel = 32;
    downgrade = true;
  }

  DWORD flags = 0;
  if (fs) flags |= CDS_FULLSCREEN;
  long res = ChangeDisplaySettings(&newMode, flags);
  if (res == DISP_CHANGE_SUCCESSFUL) return true;

  if (downgrade)
  {
    // 24
    newMode.dmBitsPerPel = 24;
    res = ChangeDisplaySettings(&newMode, flags);
    if (res == DISP_CHANGE_SUCCESSFUL) return true;

    // 16
    newMode.dmBitsPerPel = 16;
    res = ChangeDisplaySettings(&newMode, flags);
    if (res == DISP_CHANGE_SUCCESSFUL) return true;

    // 8
    newMode.dmBitsPerPel = 8;
    res = ChangeDisplaySettings(&newMode, flags);
    if (res == DISP_CHANGE_SUCCESSFUL) return true;
  }

  return false;
}

void DisplayWrapper::dw_restoreMode()
{
  ChangeDisplaySettings(0,0);
}

VideoModeInfo DisplayWrapper::dw_currentMode()
{
  DEVMODE devmode;
  EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &devmode);
  VideoModeInfo mode;
  mode.width = devmode.dmPelsWidth;
  mode.height = devmode.dmPelsHeight;
  mode.bpp = devmode.dmBitsPerPel;
  return mode;
}

#else

DisplayWrapper::DisplayWrapper()
{
  base_height = base_width = 0;
  base_bpp = 0;
}

DisplayWrapper::~DisplayWrapper()
{
}

bool DisplayWrapper::readScreenSubSection(QTextStream &ts, QString &xmodes, int &depth)
{
  depth = 0;
  xmodes = "";
  QString line,tmp;

  do {
    line = ts.readLine().simplified();

    if (line.startsWith("Depth"))
    {
      QTextStream str(&line);
      str >> tmp >> depth;
      continue;
    }

    if (line.startsWith("Modes"))
    {
      xmodes = line;
      continue;
    }

  } while  (!ts.atEnd() && line != "EndSection");

  return xmodes.isEmpty() ? false : true;
}

void DisplayWrapper::parseModes(QString &modes, QList<QPair<int,int> > &xmodes)
{
  xmodes.clear();

  QTextStream str(&modes);

  QString mode;
  str >> mode;  // remove section name

  while (!str.atEnd())
  {
    str >> mode;
    mode = mode.remove("\"");

    QRegExp rx("(\\d+)\\D(\\d+)");
    rx.setMinimal(false);
    int pos = rx.indexIn(mode);
    if (pos >= 0)
    {
      int w = rx.cap(1).toInt();
      int h = rx.cap(2).toInt();
      xmodes.append(QPair<int,int>(w,h));
    }
  }
}

bool DisplayWrapper::readScreenXconf(QList<QPair<int,int> > &xmodes, int &depth)
{
  depth = 0;
  xmodes.clear();
  QString modes;
  QString line;

  // open xorg.conf file
  QFile xconf("/etc/X11/xorg.conf");
  if (!xconf.open(QFile::ReadOnly))
    return false;

  //puts("reading xorg.conf...");

  QTextStream ts(&xconf);
  while (!ts.atEnd())
  {
    line = ts.readLine().simplified();

    if (line == "Section \"Screen\"")
    {
      //  puts("reading screen section...");

      while (!ts.atEnd() && (line != "EndSection"))
      {
        line = ts.readLine().simplified();

        //printf("%s\n", line.toAscii().constData());

        if (line == "SubSection \"Display\"")
        {
          int sDepth;
          QString sModes;

          //puts("reading display section...");

          if (readScreenSubSection(ts, sModes, sDepth))
          {
            //  printf("Modes %s\n Depth %d\n", sModes.toAscii().constData(), sDepth);

            if (sDepth > depth)
            {
              depth = sDepth;
              modes = sModes;
            }
          }
        }

      }

      if (modes.isEmpty())
        return false;

      // parse modes
      parseModes(modes, xmodes);

      return true;
    }
  }

  return false;
}


void DisplayWrapper::dw_init(bool filter, int minWidth, int minHeight)
{
  VideoModeInfo mode;

  int num_sizes;
  //Rotation original_rotation;

  Display *dpy = XOpenDisplay(NULL);
  //Window root = RootWindow(dpy, 0);
  XRRScreenSize *xrrs = XRRSizes(dpy, 0, &num_sizes);
  //
  //     GET CURRENT RESOLUTION AND FREQUENCY
  //
  //XRRScreenConfiguration *conf = XRRGetScreenInfo(dpy, root);
  //short original_rate = XRRConfigCurrentRate(conf);
  //SizeID original_size_id = XRRConfigCurrentConfiguration(conf, &original_rotation);

  XCloseDisplay(dpy);

  for (int i = 0; i < num_sizes; i++)
  {
    int width = xrrs[i].width;
    int height = xrrs[i].height;

    if (width >= minWidth && height >= minHeight)
    {
      modeNames.append(QString("%1 x %2")
                       .arg(width)
                       .arg(height)
                       );

      mode.width = width;
      mode.height = height;
      mode.bpp = 32;  // #### How to know BPP from XRandr ???
      modes.append(mode);
    }
  }

  if (filter)
    modeNames.removeDuplicates();

  // if not empty -> then ok
  if (!modeNames.empty())
    return;

  // else check xorg

  QList<QPair<int,int> > xmodes;
  int depth = 0;
  if (readScreenXconf(xmodes, depth))
  {
//      printf("XMODES READ %d\n", xmodes.count());

    for (int i = 0; i < xmodes.count(); i++)
    {
      int width = xmodes.at(i).first;
      int height = xmodes.at(i).second;

//      printf("%s\n",QString("%1 x %2")
//                       .arg(width)
//                       .arg(height).toAscii().constData());

      if (width >= minWidth && height >= minHeight)
      {
        modeNames.append(QString("%1 x %2")
                         .arg(width)
                         .arg(height)
                         );

        mode.width = width;
        mode.height = height;
        mode.bpp = depth;
        modes.append(mode);
      }
    }

    if (filter)
      modeNames.removeDuplicates();

    return;
  }

}

bool DisplayWrapper::dw_switchMode(int w, int h, int /*bpp*/, bool /*fs*/)
{
  if (!base_height || !base_width)
  {
    XRRScreenConfiguration * info = XRRGetScreenInfo (QX11Info::display(), QX11Info::appRootWindow());
    if (!info)
      return false;

    int numSizes;
    XRRScreenSize * sizes = XRRConfigSizes(info, &numSizes);
    if (!numSizes)
      return false;

    base_width = sizes->width;
    base_height = sizes->height;

    XRRFreeScreenConfigInfo(info);
  }

  QStringList args; args << "--size" << QString("%1x%2").arg(w).arg(h);
  QProcess::execute("xrandr", args);

  return true;
}

void DisplayWrapper::dw_restoreMode()
{
  if (base_height && base_width)
    dw_switchMode(base_width, base_height, base_bpp, true);
}

#endif
