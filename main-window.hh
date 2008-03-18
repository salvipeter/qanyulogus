// QAnyulogus, by Peter Salvi (2008)

#ifndef MAIN_WINDOW_HH
#define MAIN_WINDOW_HH

#include <QMainWindow>

#include "qanyulogus.hh"

class QAction;
class QToolbar;

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow();
  void openFile(QString filename);

public slots:
  void changeMade();
  void openPressed();
  bool savePressed();
  void helpPressed() const;

private:
  void setTitle();
  bool maybeSave();
  void closeEvent(QCloseEvent *event);

  // GUI variables
  QToolBar *toolbar;
  QAction *openAction;
  QAction *saveAction;
  QAction *newAction;
  QAction *deleteAction;
  QAction *printAction;
  QAction *helpAction;
  QAnyulogus *anyulogus;

  // Internal variables
  QString file_name;
  bool saved;
};

#endif	// MAIN_WINDOW_HH
