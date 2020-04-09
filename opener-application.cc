#include <QFileOpenEvent>

#include "main-window.hh"
#include "opener-application.hh"

OpenerApplication::OpenerApplication(int &argc, char **argv) :
  QApplication(argc, argv)
{
}

bool OpenerApplication::event(QEvent *event)
{
  if(event->type() == QEvent::FileOpen){
    mainWindow->openFile(static_cast<QFileOpenEvent *>(event)->file());
    return true;
  } else
    return QApplication::event(event);
}
