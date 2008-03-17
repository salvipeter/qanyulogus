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

public slots:
  void openPressed();
  void savePressed();
  void newPressed();
  void deletePressed();
  void printPressed() const;
  void helpPressed() const;

private:
  void setTitle();
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
