// QAnyulogus, by Peter Salvi (2008)
//
// Time-stamp: <2008.03.17., 13:46:40 (salvi)>

#include <iostream>

#include <QtGui>

#include "main-window.hh"

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  if(argc > 2) {
    std::cout << "Usage: " << argv[0] << " [filename]" << std::endl;
    return 1;
  }

  QString const filename = (argc == 2 ? argv[1] : "");
  MainWindow window(filename);
  window.show();
  return app.exec();
}
