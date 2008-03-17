#ifndef QANYULOGUS_HH
#define QANYULOGUS_HH

#include <QWidget>

class QComboBox;
class QLabel;
class QLineEdit;
class QString;
class QTableView;

class QAnyulogus : public QWidget
{
  Q_OBJECT

public:
  QAnyulogus();

private:
  bool openFile(QString filename);

  // GUI variables
  QTableView *table;
  QLabel *searchLabel;
  QLineEdit *searchEdit;
  QComboBox *searchCombo;
  QTableView *search;

  // Internal variables
};

#endif	// QANYULOGUS_HH
