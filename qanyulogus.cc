#include <QComboBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTableView>
#include <QVBoxLayout>

#include "qanyulogus.hh"

QAnyulogus::QAnyulogus()
{
  table = new QTableView;
  searchLabel = new QLabel(tr("Keresés:"));
  searchEdit = new QLineEdit;
  searchCombo = new QComboBox;
  search = new QTableView;

  // Layout
  QHBoxLayout *hbl = new QHBoxLayout;
  hbl->addWidget(searchLabel);
  hbl->addWidget(searchEdit);
  hbl->addWidget(searchCombo);
  QVBoxLayout *vbl = new QVBoxLayout;
  vbl->addWidget(table);
  vbl->addLayout(hbl);
  vbl->addWidget(search);
  setLayout(vbl);
}

bool QAnyulogus::openFile(QString filename)
{
  return true;
}
