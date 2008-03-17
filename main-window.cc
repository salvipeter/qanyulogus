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
    QFileDialog::getOpenFileName(this, tr("Megnyit�s"), ".",
				 tr("QAnyul�gus f�jlok (*.anyu)"));
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
  QString new_title = QString("QAnyul�gus");
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
  int ret = QMessageBox::warning(this, tr("Kil�p�s"),
				 tr("Nem mentetted el a katal�gust."),
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
