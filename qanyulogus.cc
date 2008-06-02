// QAnyulogus, by Peter Salvi (2008)

#include <QComboBox>
#include <QFile>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QList>
#include <QMessageBox>
#include <QPrinter>
#include <QStandardItemModel>
#include <QStringList>
#include <QTableView>
#include <QTextDocument>
#include <QTextStream>
#include <QVector>

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
  table->setSelectionBehavior(QAbstractItemView::SelectRows);
  table->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);

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
  search->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);

  searchLabel = new QLabel(tr("Keresés:"));
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
  connect(model, SIGNAL(rowsInserted(const QModelIndex &, int, int)),
	  this->parent(), SLOT(changeMade()));
  connect(model, SIGNAL(rowsRemoved(const QModelIndex &, int, int)),
	  this->parent(), SLOT(changeMade()));
  connect(searchEdit, SIGNAL(textEdited(const QString &)), searchProxy,
	  SLOT(setFilterFixedString(const QString &)));
  connect(searchCombo, SIGNAL(activated(int)), this,
	  SLOT(setFilterColumn(int)));
  connect(search, SIGNAL(doubleClicked(const QModelIndex &)),
	  this, SLOT(selectTableElement(const QModelIndex &)));
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

  // Turn off sorting while setting data
  tableProxy->setDynamicSortFilter(false);
  searchProxy->setDynamicSortFilter(false);

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
  tableProxy->setDynamicSortFilter(true);
  searchProxy->setDynamicSortFilter(true);
  table->sortByColumn(0, Qt::AscendingOrder);
  search->sortByColumn(0, Qt::AscendingOrder);

  // Reload to reflect the changes
  tableProxy->setSourceModel(model);
  searchProxy->setSourceModel(model);  

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
  int j = model->rowCount();
  model->insertRow(j);
  for(int i = 0; i < model->columnCount(); ++i)
    model->setItem(j, i, new QStandardItem(""));
  table->scrollTo(tableProxy->mapFromSource(model->item(j)->index()));
  table->selectRow(tableProxy->mapFromSource(model->item(j)->index()).row());
  table->edit(tableProxy->mapFromSource(model->item(j)->index()));
}

void QAnyulogus::deletePressed()
{
  int row = model->itemFromIndex(tableProxy->mapToSource(table->currentIndex()))->row();
  QString message = QString("Tényleg ki akarod törölni a(z) %1. sort?").
    arg(row + 1);
  int ret = QMessageBox::question(dynamic_cast<QWidget *>(parent()),
				  "Törlés", message,
				  QMessageBox::Yes, QMessageBox::No);
  if(ret == QMessageBox::Yes)
    model->removeRow(row);
}

void QAnyulogus::printPressed()
{
  if(QMessageBox::question(this, "Nyomtatás",
			   "Az alsó táblázat tartalmát fogom kinyomtatni.\n"
			   "Mehet?", QMessageBox::No, QMessageBox::Yes)
     == QMessageBox::No)
    return;

  QString str =
    "<html>\n"
    "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" />\n"
    "<head>\n"
    "<title>CD Katalógus</title>\n"
    "</head>\n"
    "<body>\n"
    "<h1>CD Katalógus</h1>\n"
    "<table border=\"1\" align=\"center\">\n";

  int const n = searchProxy->columnCount();
  int const m = searchProxy->rowCount();

  int total_width = 0;
  QVector<int> widths(n);
  for(int i = 0; i < n; ++i) {
    widths[i] = search->columnWidth(i);
    total_width += widths[i];
  }

  // Setup headings
  str += "<tr>";
  for(int i = 0; i < n; ++i) {
    QString heading = searchProxy->headerData(i, Qt::Horizontal,
					      Qt::DisplayRole).toString();
    str += QString("<td width=\"%1%\">%2</td>").
      arg((widths[i] * 100) / total_width).
      arg(heading);
  }
  str += "</tr>\n";

  // Write the data

  for(int j = 0; j < m; ++j) {
    str += "<tr>";
    for(int i = 0; i < n; ++i)
      str += QString("<td>%1</td>").
	arg(searchProxy->itemData(searchProxy->index(j, i))
	    [Qt::DisplayRole].toString());
    str += "</tr>\n";
  }

  str +=
    "</table>\n"
    "</body>\n"
    "</html>\n";

  // Printing
  QTextDocument *d = new QTextDocument;
  QPrinter *printer = new QPrinter;
  d->setHtml(str);
  d->print(printer);
}

void QAnyulogus::setFilterColumn(int column)
{
  searchProxy->setFilterKeyColumn(column);
}

void QAnyulogus::selectTableElement(const QModelIndex &index)
{
  // index shows a row from the searchProxy.
  // We want to set tableProxy to the same row.
  QModelIndex const table_index =
    tableProxy->mapFromSource(searchProxy->mapToSource(index));
  table->scrollTo(table_index);
  table->selectRow(table_index.row());
}
