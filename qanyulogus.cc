#include <QAction>
#include <QComboBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QStatusBar>
#include <QTableView>
#include <QToolBar>
#include <QVBoxLayout>

#include "qanyulogus.hh"

QAnyulogus::QAnyulogus() :
  file_name(""), saved(true)
{
  // Title
  setTitle();

  // Initial size
  resize(640, 480);

  // Actions
  openAction = new QAction(QIcon(":/images/fileopen.png"), tr("Megnyit�s"), this);
  openAction->setShortcut(tr("Ctrl+O"));
  openAction->setStatusTip(tr("Megnyit egy QAnyul�gus f�jlt."));
  connect(openAction, SIGNAL(triggered()), this, SLOT(openPressed()));

  saveAction = new QAction(QIcon(":/images/filesave.png"), tr("Ment�s"), this);
  saveAction->setShortcut(tr("Ctrl+S"));
  saveAction->setStatusTip(tr("Elmenti a QAnyul�gus f�jlt."));
  connect(saveAction, SIGNAL(triggered()), this, SLOT(savePressed()));

  newAction = new QAction(QIcon(":/images/linenew.png"), tr("�j sor"), this);
  newAction->setShortcut(tr("Ctrl+N"));
  newAction->setStatusTip(tr("�j bejegyz�st nyit a katal�gusban."));
  connect(newAction, SIGNAL(triggered()), this, SLOT(newPressed()));

  deleteAction = new QAction(QIcon(":/images/linedelete.png"), tr("Sor t�rl�se"), this);
  deleteAction->setShortcut(tr("Ctrl+D"));
  deleteAction->setStatusTip(tr("Kit�r�l egy bejegyz�st a katal�gusb�l."));
  connect(deleteAction, SIGNAL(triggered()), this, SLOT(deletePressed()));

  printAction = new QAction(QIcon(":/images/fileprint.png"), tr("Nyomtat�s"), this);
  printAction->setShortcut(tr("Ctrl+P"));
  printAction->setStatusTip(tr("Kinyomtatja a katal�gust."));
  connect(printAction, SIGNAL(triggered()), this, SLOT(printPressed()));

  helpAction = new QAction(QIcon(":/images/help.png"), tr("Seg�ts�g"), this);
  helpAction->setShortcut(tr("Ctrl+H"));
  helpAction->setStatusTip(tr("Haszn�lati utas�t�s �s egy�b inform�ci�k."));
  connect(helpAction, SIGNAL(triggered()), this, SLOT(helpPressed()));

  // Toolbar
  toolbar = addToolBar(tr("Eszk�zt�r"));
  toolbar->addAction(openAction);
  toolbar->addAction(saveAction);
  toolbar->addAction(newAction);
  toolbar->addAction(deleteAction);
  toolbar->addAction(printAction);
  toolbar->addAction(helpAction);

  // Main Widgets
  table = new QTableView;
  searchLabel = new QLabel(tr("Keres�s:"));
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

  // Status bar
  setStatusBar(new QStatusBar);

  // Connections
}

void QAnyulogus::openPressed()
{
}

void QAnyulogus::savePressed()
{
  if(saved)
    return;

  // TODO

  saved = true;
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

void QAnyulogus::helpPressed() const
{
}

void QAnyulogus::setTitle()
{
  QString new_title = QString("QAnyul�gus") + (file_name != "" ? " - " : "")
    + file_name + (!saved ? "*" : "");
}

bool QAnyulogus::openFile(QString filename)
{
  return true;
}

void QAnyulogus::closeEvent(QCloseEvent *event)
{
  if(saved)
    event->accept();
  else {
    int ret = QMessageBox::warning(this, tr("Kil�p�s"),
				   tr("Nem mentetted el a katal�gust."),
				   QMessageBox::Save | QMessageBox::Discard |
				   QMessageBox::Cancel, QMessageBox::Save);
    switch(ret) {
    case QMessageBox::Cancel: event->ignore(); break;
    case QMessageBox::Save: savePressed();
    default: event->accept();
    }
  }
}
