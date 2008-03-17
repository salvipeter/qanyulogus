#ifndef QANYULOGUS_HH
#define QANYULOGUS_HH

#include <QMainWindow>

class QAction;
class QComboBox;
class QLabel;
class QLineEdit;
class QString;
class QTableView;
class QToolbar;

class QAnyulogus : public QMainWindow
{
  Q_OBJECT

public:
  QAnyulogus();

public slots:
  void openPressed();
  void savePressed();
  void newPressed();
  void deletePressed();
  void printPressed() const;
  void helpPressed() const;

private:
  void setTitle();
  bool openFile(QString filename);
  void closeEvent(QCloseEvent *event);

  // GUI variables
  QToolBar *toolbar;
  QAction *openAction;
  QAction *saveAction;
  QAction *newAction;
  QAction *deleteAction;
  QAction *printAction;
  QAction *helpAction;
  QTableView *table;
  QLabel *searchLabel;
  QLineEdit *searchEdit;
  QComboBox *searchCombo;
  QTableView *search;

  // Internal variables
  QString file_name;
  bool saved;
};

#endif	// QANYULOGUS_HH
