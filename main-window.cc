// QAnyulogus, by Peter Salvi (2008)

#include <QAction>
#include <QCloseEvent>
#include <QFileDialog>
#include <QMessageBox>
#include <QStatusBar>
#include <QTextBrowser>
#include <QToolBar>

#include "main-window.hh"

MainWindow::MainWindow(QString filename = "") :
  file_name(""), saved(true)
{
  // Initial size
  resize(800, 600);

  // Central widget
  anyulogus = new QAnyulogus(this);
  setCentralWidget(anyulogus);

  // Actions
  openAction = new QAction(QIcon(":/images/fileopen.png"), tr("Megnyit�s"), this);
  openAction->setShortcut(tr("Ctrl+O"));
  openAction->setStatusTip(tr("Megnyit egy QAnyul�gus f�jlt. (C-o)"));
  connect(openAction, SIGNAL(triggered()), this, SLOT(openPressed()));

  saveAction = new QAction(QIcon(":/images/filesave.png"), tr("Ment�s"), this);
  saveAction->setShortcut(tr("Ctrl+S"));
  saveAction->setStatusTip(tr("Elmenti a QAnyul�gus f�jlt. (C-s)"));
  saveAction->setEnabled(false);
  connect(saveAction, SIGNAL(triggered()), this, SLOT(savePressed()));

  newAction = new QAction(QIcon(":/images/linenew.png"), tr("�j sor"), this);
  newAction->setShortcut(tr("Ctrl+N"));
  newAction->setStatusTip(tr("�j bejegyz�st nyit a katal�gusban. (C-n)"));
  newAction->setEnabled(false);
  connect(newAction, SIGNAL(triggered()), anyulogus, SLOT(newPressed()));

  deleteAction = new QAction(QIcon(":/images/linedelete.png"), tr("Sor t�rl�se"), this);
  deleteAction->setShortcut(tr("Ctrl+D"));
  deleteAction->setStatusTip(tr("Kit�r�l egy bejegyz�st a katal�gusb�l. (C-d)"));
  deleteAction->setEnabled(false);
  connect(deleteAction, SIGNAL(triggered()), anyulogus, SLOT(deletePressed()));

  printAction = new QAction(QIcon(":/images/fileprint.png"), tr("Nyomtat�s"), this);
  printAction->setShortcut(tr("Ctrl+P"));
  printAction->setStatusTip(tr("Kinyomtatja a katal�gust. (C-p)"));
  printAction->setEnabled(false);
  connect(printAction, SIGNAL(triggered()), anyulogus, SLOT(printPressed()));

  helpAction = new QAction(QIcon(":/images/help.png"), tr("Seg�ts�g"), this);
  helpAction->setShortcut(tr("Ctrl+H"));
  helpAction->setStatusTip(tr("Haszn�lati utas�t�s �s egy�b inform�ci�k. (C-h)"));
  connect(helpAction, SIGNAL(triggered()), this, SLOT(helpPressed()));

  // Toolbar
  toolbar = addToolBar(tr("Eszk�zt�r"));
  toolbar->addAction(openAction);
  toolbar->addAction(saveAction);
  toolbar->addAction(newAction);
  toolbar->addAction(deleteAction);
  toolbar->addAction(printAction);
  toolbar->addAction(helpAction);

  // Title
  setTitle();

  // Status bar
  setStatusBar(new QStatusBar);

  if(filename != "")
    openFile(filename);
}

void MainWindow::changeMade()
{
  if(saved) {
    saved = false;
    setTitle();
  }
}

void MainWindow::openPressed()
{
  if(!maybeSave())
    return;

  QString filename =
    QFileDialog::getOpenFileName(this, tr("Megnyit�s"), ".",
				 tr("QAnyul�gus f�jlok (*.anyu)"));
  if(filename != "")
    openFile(filename);
}

bool MainWindow::savePressed()
{
  if(saved)
    return true;

  if(!anyulogus->saveFile(file_name)) {
    QMessageBox::critical(this, "Ment�s sikertelen",
			  "A(z) \"" + file_name +
			  "\" f�jlt nem tudtam elmenteni.");
    return false;
  }

  saved = true;
  setTitle();

  return true;
}

void MainWindow::helpPressed() const
{
  QTextBrowser *browser = new QTextBrowser;
  browser->setSource(QUrl("qrc:/doc/help.html"));
  browser->setWindowTitle(tr("Haszn�lati �tmutat�"));
  browser->resize(640, 480);
  browser->show();
}

void MainWindow::setTitle()
{
  QString new_title = QString("QAnyul�gus");
  if(file_name != "")
    new_title += " - " + file_name.section('/', -1) + (!saved ? "*" : "");
  setWindowTitle(new_title);
  saveAction->setEnabled(!saved);
}

void MainWindow::openFile(QString filename)
{
  if(!anyulogus->openFile(filename)) {
    QMessageBox::critical(this, "A f�jl nem nyithat�",
			  "A f�jl \"" + filename + "\" nem nyithat� meg,\n"
			  "vagy a f�jlban nem minden bejegyz�s hossza azonos.");
    return;
  }

  if(file_name == "") {
    newAction->setEnabled(true);
    deleteAction->setEnabled(true);
    printAction->setEnabled(true);
  }

  file_name = filename;
  saved = true;
  setTitle();
}

bool MainWindow::maybeSave()
{
  if(saved)
    return true;
  int ret = QMessageBox::warning(this, tr("A katal�gus megv�ltozott."),
				 tr("Nem mentetted el a katal�gust."),
				 QMessageBox::Save | QMessageBox::Discard |
				 QMessageBox::Cancel, QMessageBox::Save);
  switch(ret) {
  case QMessageBox::Cancel: return false;
  case QMessageBox::Save: if(!savePressed()) return false;
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
