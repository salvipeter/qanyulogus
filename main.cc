#include <QtGui>

#include "qanyulogus.hh"

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  QAnyulogus window;
  window.show();
  return app.exec();
}
