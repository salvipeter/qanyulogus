// QAnyulogus, by Peter Salvi (2008)

#include <iostream>

#include <QtGui>

#include "main-window.hh"
#include "opener-application.hh"

int main(int argc, char *argv[])
{
  OpenerApplication app(argc, argv);

  if(argc > 2) {
    std::cout << "Usage: " << argv[0] << " [filename]" << std::endl;
    return 1;
  }

  MainWindow window;
  app.setMainWindow(&window);

  if(argc == 2)
    window.openFile(argv[1]);

  window.show();
  return app.exec();
}
