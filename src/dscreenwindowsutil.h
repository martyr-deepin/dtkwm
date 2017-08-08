#ifndef DSCREENWINDOWSUTIL_H
#define DSCREENWINDOWSUTIL_H

#include <QObject>
#include <QScreen>

#include  <DObject>

#include "dwindowmanager.h"
#include "dtkwm_global.h"

DWM_BEGIN_NAMESPACE

class DScreenWindowsUtilPrivate;
class LIBDTKWMSHARED_EXPORT DScreenWindowsUtil : public QObject ,
        public DTK_CORE_NAMESPACE::DObject
{
    Q_OBJECT
public:
    static DScreenWindowsUtil *instance(QPoint pos);

    ~DScreenWindowsUtil();

    int getScreenNum() const;
    QRect backgroundRect() const;
    WId rootWindowId() const;
    QScreen* primaryScreen() const;
    QList<QRect> windowsRect() const;
    QStringList windowsName() const;
    bool isPrimayScreen() const;

protected:
    DScreenWindowsUtil(QPoint pos, QObject *parent = 0);

private:
    D_DECLARE_PRIVATE(DScreenWindowsUtil)
};

DWM_END_NAMESPACE

#endif // DSCREENWINDOWSUTIL_H
