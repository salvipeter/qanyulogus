// QAnyulogus, by Peter Salvi (2008)

#include <iostream>

#include <QtGui>

#include "main-window.hh"
#include "opener-application.hh"

int main(int argc, char *argv[])
{
  OpenerApplication app(argc, argv);

  MainWindow window;
  app.setMainWindow(&window);

#ifndef DISABLE_COMMAND_LINE
  if(argc > 2) {
    std::cout << "Usage: " << argv[0] << " [filename]" << std::endl;
    return 1;
  }

  if(argc == 2)
    window.openFile(argv[1]);
#endif // DISABLE_COMMAND_LINE

  window.show();
  return app.exec();
}
