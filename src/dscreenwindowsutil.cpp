#include <QApplication>
#include <QDesktopWidget>
#include <QScreen>

#include <DObjectPrivate>

#include "dscreenwindowsutil.h"

DWM_BEGIN_NAMESPACE
DScreenWindowsUtil* screenWindowsUtil = nullptr;

class DScreenWindowsUtilPrivate : public DTK_CORE_NAMESPACE::DObjectPrivate
{
public:
    DScreenWindowsUtilPrivate(DScreenWindowsUtil* parent)
        : DObjectPrivate(parent){}

    mutable bool isPrimaryScreen;
    mutable QRect backgroundRect;
    mutable int screenNum;
    mutable WId rootWindowId;
    mutable QScreen* primaryScreen;
    mutable DWindowManager* xcbWindowManager;
};

DScreenWindowsUtil::~DScreenWindowsUtil()
{
    D_DC(DScreenWindowsUtil);
    Q_UNUSED(d);
}

DScreenWindowsUtil* DScreenWindowsUtil::instance(QPoint pos)
{
    if (!screenWindowsUtil)
    {
        screenWindowsUtil = new DScreenWindowsUtil(pos);
    }

    return  screenWindowsUtil;
}

DScreenWindowsUtil::DScreenWindowsUtil(QPoint pos, QObject *parent)
    : QObject(parent),
      DObject(*new DScreenWindowsUtilPrivate(this))
{
    D_DC(DScreenWindowsUtil);
    d->isPrimaryScreen = true;
    QList<QScreen*> screenList = qApp->screens();
    d->screenNum = qApp->desktop()->screenNumber(pos);
    d->rootWindowId = qApp->desktop()->screen(d->screenNum)->winId();
    d->primaryScreen = screenList[d->screenNum];

    if (d->screenNum != 0 && d->screenNum < screenList.length())
    {
        d->backgroundRect = screenList[d->screenNum]->geometry();
    } else {
        d->backgroundRect = qApp->primaryScreen()->geometry();
    }

    d->isPrimaryScreen = qApp->primaryScreen()->geometry().contains(pos);

    d->xcbWindowManager = new DWindowManager;
    d->xcbWindowManager->setRootWindowRect(d->backgroundRect);
}

QList<QRect> DScreenWindowsUtil::windowsRect() const
{
    D_DC(DScreenWindowsUtil);

    QList<QRect> windowRect;
    if (d->isPrimaryScreen) {
        QList<xcb_window_t> windows = d->xcbWindowManager->getWindows();
        for (int i = 0; i < windows.length(); i++) {
            WindowRect  wr = d->xcbWindowManager->adjustRectInScreenArea(
                        d->xcbWindowManager->getWindowRect(windows[i]));
            windowRect.append(QRect(wr.x, wr.y, wr.width, wr.height));
        }
    } else {
        windowRect.append(d->backgroundRect);
    }

    return windowRect;
}

QStringList DScreenWindowsUtil::windowsName() const
{
    D_DC(DScreenWindowsUtil);

    QStringList windowNameList;

    if (d->isPrimaryScreen) {
        QList<xcb_window_t> windows = d->xcbWindowManager->getWindows();
        for (int i = 0; i < windows.length(); i++) {
            QString  wn = d->xcbWindowManager->getWindowClass(windows[i]);
            windowNameList.append(wn);
        }
    } else {
        windowNameList.append("");
    }

    return windowNameList;
}

int DScreenWindowsUtil::getScreenNum() const
{
    D_DC(DScreenWindowsUtil);
    return d->screenNum;
}

QRect DScreenWindowsUtil::backgroundRect() const
{
    D_DC(DScreenWindowsUtil);
    return d->backgroundRect;
}

WId DScreenWindowsUtil::rootWindowId() const
{
    D_DC(DScreenWindowsUtil);
    return d->rootWindowId;
}

QScreen* DScreenWindowsUtil::primaryScreen() const
{
    D_DC(DScreenWindowsUtil);
    return d->primaryScreen;
}

bool DScreenWindowsUtil::isPrimayScreen() const
{
    D_DC(DScreenWindowsUtil);
    return d->isPrimaryScreen;
}

DWM_END_NAMESPACE
