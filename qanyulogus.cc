// QAnyulogus, by Peter Salvi (2008)
//
// Time-stamp: <2008.03.17., 19:18:18 (salvi)>

#include <QComboBox>
#include <QFile>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QList>
#include <QStandardItemModel>
#include <QStringList>
#include <QTableView>
#include <QTextStream>

#include "hungarian-sort-filter-proxy-model.hh"
#include "qanyulogus.hh"

QAnyulogus::QAnyulogus(QWidget *parent = 0) : QSplitter(parent)
{
  model = new QStandardItemModel;

  tableProxy = new HungarianSortFilterProxyModel;
  tableProxy->setSourceModel(model);
  tableProxy->setSortCaseSensitivity(Qt::CaseInsensitive);
  tableProxy->setDynamicSortFilter(true);

  table = new QTableView;
  table->setAlternatingRowColors(true);
  table->setSortingEnabled(true);
  table->setModel(tableProxy);
  table->setEditTriggers(QAbstractItemView::DoubleClicked);
  table->setSelectionMode(QAbstractItemView::SingleSelection);

  searchProxy = new HungarianSortFilterProxyModel;
  searchProxy->setSourceModel(model);
  searchProxy->setFilterCaseSensitivity(Qt::CaseInsensitive);
  searchProxy->setSortCaseSensitivity(Qt::CaseInsensitive);
  searchProxy->setDynamicSortFilter(true);

  search = new QTableView;
  search->setAlternatingRowColors(true);
  search->setSortingEnabled(true);
  search->setModel(searchProxy);
  search->setEditTriggers(QAbstractItemView::NoEditTriggers);
  search->setSelectionMode(QAbstractItemView::SingleSelection);
  search->setSelectionBehavior(QAbstractItemView::SelectRows);

  searchLabel = new QLabel(tr("Keres�s:"));
  searchEdit = new QLineEdit;
  searchCombo = new QComboBox;

  // Layout
  setOrientation(Qt::Vertical);
  setChildrenCollapsible(false);
  QWidget *box = new QWidget;
  QHBoxLayout *hbl = new QHBoxLayout(box);
  hbl->addWidget(searchLabel);
  hbl->addWidget(searchEdit);
  hbl->addWidget(searchCombo);
  hbl->setSizeConstraint(QLayout::SetMinAndMaxSize);
  addWidget(table);
  addWidget(box);
  addWidget(search);

  // Connections
  connect(model, SIGNAL(itemChanged(QStandardItem *)), this->parent(),
	  SLOT(changeMade()));
  connect(searchEdit, SIGNAL(textEdited(const QString &)), searchProxy,
	  SLOT(setFilterFixedString(const QString &)));
  connect(searchCombo, SIGNAL(activated(int)), this,
	  SLOT(setFilterColumn(int)));
}

bool QAnyulogus::openFile(QString filename)
{
  QFile file(filename);
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    return false;

  QTextStream in(&file);
  in.setCodec("UTF-16LE");

  QList<QStringList> data;

  QString s = in.readLine().replace("**", "*");
  QStringList headings = s.split('*');
  int const n = headings.size();

  while(!in.atEnd()) {
    s = in.readLine().replace("**", "*");
    QStringList const lst = s.split('*');
    if(lst.size() != n)
      return false;
    data.push_back(lst);
  }

  file.close();

  int const m = data.size();

  // Set the tables and the combo box
  model->clear();
  model->setColumnCount(n);
  model->setRowCount(m);
  model->setHorizontalHeaderLabels(headings);
  for(int j = 0; j < m; ++j) {
    QStringList &row = data[j];
    for(int i = 0; i < n; ++i)
      model->setItem(j, i, new QStandardItem(row[i]));
  }
  
  searchCombo->clear();
  searchCombo->addItems(headings);

  return true;
}

QString QAnyulogus::createRow(QStringList list)
{
  int const n = list.size();

  if(n == 0)
    return " ";

  QString result = "";
  for(int i = 0; i < n; ++i) {
    QString const next = list[i].replace('*', "**");
    result += (next == "" ? " " : next);
    if(i != n - 1)
      result += "*";
  }

  return result;
}

bool QAnyulogus::saveFile(QString filename)
{
  QFile file(filename);
  if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    return false;

  QTextStream out(&file);
  out.setCodec("UTF-16LE");

  int const n = model->columnCount();
  int const m = model->rowCount();

  QStringList list;
  for(int i = 0; i < n; ++i)
    list.push_back(model->horizontalHeaderItem(i)->text());
  out << createRow(list) << "\n";
  for(int j = 0; j < m; ++j) {
    for(int i = 0; i < n; ++i)
      list[i] = model->item(j, i)->text();
    out << createRow(list) << "\n";
  }

  file.close();
  return true;
}

void QAnyulogus::newPressed()
{
}

void QAnyulogus::deletePressed()
{
}

void QAnyulogus::printPressed() const
{
}

void QAnyulogus::setFilterColumn(int column)
{
  searchProxy->setFilterKeyColumn(column);
}
