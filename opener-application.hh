#ifndef OPENER_APPLICATION_HH
#define OPENER_APPLICATION_HH

#include <QApplication>

class MainWindow;

class OpenerApplication : public QApplication
{
  Q_OBJECT

public:
  OpenerApplication(int argc, char *argv[]);
  void setMainWindow(MainWindow *mw) { mainWindow = mw; }

protected:
  bool event(QEvent *);

private:
  void loadFile(const QString &fileName);

  MainWindow *mainWindow;
};

#endif	// OPENER_APPLICATION_HH
