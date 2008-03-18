// QAnyulogus, by Peter Salvi (2008)

#ifndef QANYULOGUS_HH
#define QANYULOGUS_HH

#include <QSplitter>
#include <QString>
#include <QStringList>

class HungarianSortFilterProxyModel;
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

public slots:
  void newPressed();
  void deletePressed();
  void printPressed();
  void setFilterColumn(int column);

private:
  QString createRow(QStringList list);

  QStandardItemModel *model;
  HungarianSortFilterProxyModel *tableProxy;
  QTableView *table;
  QLabel *searchLabel;
  QLineEdit *searchEdit;
  QComboBox *searchCombo;
  HungarianSortFilterProxyModel *searchProxy;
  QTableView *search;
};

#endif	// QANYULOGUS_HH
