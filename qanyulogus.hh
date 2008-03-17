// QAnyulogus, by Peter Salvi (2008)
//
// Time-stamp: <2008.03.17., 17:56:01 (salvi)>

#ifndef QANYULOGUS_HH
#define QANYULOGUS_HH

#include <QSplitter>
#include <QString>
#include <QStringList>

class QStandardItemModel;
class QComboBox;
class QLabel;
class QLineEdit;
class QTableView;

class QAnyulogus : public QSplitter
{
  Q_OBJECT

public:
  QAnyulogus(QWidget *parent);
  bool openFile(QString filename);
  bool saveFile(QString filename);

private:
  QString createRow(QStringList list);

  // GUI variables
  QStandardItemModel *model;
  QTableView *table;
  QLabel *searchLabel;
  QLineEdit *searchEdit;
  QComboBox *searchCombo;
  QTableView *search;
};

#endif	// QANYULOGUS_HH
