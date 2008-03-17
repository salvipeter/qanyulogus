#include <QAction>
#include <QCloseEvent>
#include <QFileDialog>
#include <QMessageBox>
#include <QStatusBar>
#include <QToolBar>

#include "main-window.hh"

MainWindow::MainWindow(QString filename = "") :
  file_name(""), saved(true)
{
  // Title
  setTitle();

  // Initial size
  resize(640, 480);

  // Actions
  openAction = new QAction(QIcon(":/images/fileopen.png"), tr("Megnyitás"), this);
  openAction->setShortcut(tr("Ctrl+O"));
  openAction->setStatusTip(tr("Megnyit egy QAnyulógus fájlt."));
  connect(openAction, SIGNAL(triggered()), this, SLOT(openPressed()));

  saveAction = new QAction(QIcon(":/images/filesave.png"), tr("Mentés"), this);
  saveAction->setShortcut(tr("Ctrl+S"));
  saveAction->setStatusTip(tr("Elmenti a QAnyulógus fájlt."));
  connect(saveAction, SIGNAL(triggered()), this, SLOT(savePressed()));

  newAction = new QAction(QIcon(":/images/linenew.png"), tr("Új sor"), this);
  newAction->setShortcut(tr("Ctrl+N"));
  newAction->setStatusTip(tr("Új bejegyzést nyit a katalógusban."));
  connect(newAction, SIGNAL(triggered()), this, SLOT(newPressed()));

  deleteAction = new QAction(QIcon(":/images/linedelete.png"), tr("Sor törlése"), this);
  deleteAction->setShortcut(tr("Ctrl+D"));
  deleteAction->setStatusTip(tr("Kitöröl egy bejegyzést a katalógusból."));
  connect(deleteAction, SIGNAL(triggered()), this, SLOT(deletePressed()));

  printAction = new QAction(QIcon(":/images/fileprint.png"), tr("Nyomtatás"), this);
  printAction->setShortcut(tr("Ctrl+P"));
  printAction->setStatusTip(tr("Kinyomtatja a katalógust."));
  connect(printAction, SIGNAL(triggered()), this, SLOT(printPressed()));

  helpAction = new QAction(QIcon(":/images/help.png"), tr("Segítség"), this);
  helpAction->setShortcut(tr("Ctrl+H"));
  helpAction->setStatusTip(tr("Használati utasítás és egyéb információk."));
  connect(helpAction, SIGNAL(triggered()), this, SLOT(helpPressed()));

  // Toolbar
  toolbar = addToolBar(tr("Eszköztár"));
  toolbar->addAction(openAction);
  toolbar->addAction(saveAction);
  toolbar->addAction(newAction);
  toolbar->addAction(deleteAction);
  toolbar->addAction(printAction);
  toolbar->addAction(helpAction);

  anyulogus = new QAnyulogus;
  setCentralWidget(anyulogus);

  // Status bar
  setStatusBar(new QStatusBar);

  if(filename != "")
    openFile(filename);
}

void MainWindow::openPressed()
{
  QString filename =
    QFileDialog::getOpenFileName(this, tr("Megnyitás"), ".",
				 tr("QAnyulógus fájlok (*.anyu)"));
  if(filename != "")
    openFile(filename);
}

void MainWindow::savePressed()
{
  if(saved)
    return;

  // TODO

  saved = true;
  setTitle();
}

void MainWindow::newPressed()
{
}

void MainWindow::deletePressed()
{
}

void MainWindow::printPressed() const
{
}

void MainWindow::helpPressed() const
{
}

void MainWindow::setTitle()
{
  QString new_title = QString("QAnyulógus");
  if(file_name != "")
    new_title += " - " + file_name.section('/', -1) + (!saved ? "*" : "");
  setWindowTitle(new_title);
}

void MainWindow::openFile(QString filename)
{
  if(!maybeSave())
    return;

  // TODO

  file_name = filename;
  saved = true;
  setTitle();
}

bool MainWindow::maybeSave()
{
  if(saved)
    return true;
  int ret = QMessageBox::warning(this, tr("Kilépés"),
				 tr("Nem mentetted el a katalógust."),
				 QMessageBox::Save | QMessageBox::Discard |
				 QMessageBox::Cancel, QMessageBox::Save);
  switch(ret) {
  case QMessageBox::Cancel: return false;
  case QMessageBox::Save: savePressed();
  default: return true;
  }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
  if(maybeSave())
    event->accept();
  else
    event->ignore();
}
