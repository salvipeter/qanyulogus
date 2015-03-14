// QAnyulogus, by Peter Salvi (2008)

#include <QAction>
#include <QCloseEvent>
#include <QFileDialog>
#include <QMessageBox>
#include <QStatusBar>
#include <QTextBrowser>
#include <QToolBar>

#include "main-window.hh"

MainWindow::MainWindow() :
  file_name(""), saved(true)
{
  // Initial size
  resize(800, 600);

  // Central widget
  anyulogus = new QAnyulogus(this);
  setCentralWidget(anyulogus);

  // Actions
  openAction = new QAction(QIcon(":/images/fileopen.png"), tr("Megnyitás"), this);
  openAction->setShortcut(tr("Ctrl+O"));
  openAction->setStatusTip(tr("Megnyit egy QAnyulógus fájlt. (C-o)"));
  connect(openAction, SIGNAL(triggered()), this, SLOT(openPressed()));

  saveAction = new QAction(QIcon(":/images/filesave.png"), tr("Mentés"), this);
  saveAction->setShortcut(tr("Ctrl+S"));
  saveAction->setStatusTip(tr("Elmenti a QAnyulógus fájlt. (C-s)"));
  saveAction->setEnabled(false);
  connect(saveAction, SIGNAL(triggered()), this, SLOT(savePressed()));

  exportAction = new QAction(QIcon(":/images/fileexport.png"), tr("Export"), this);
  exportAction->setShortcut(tr("Ctrl+E"));
  exportAction->setStatusTip(tr("Exportál HTML fájlba. (C-e)"));
  exportAction->setEnabled(false);
  connect(exportAction, SIGNAL(triggered()), this, SLOT(exportPressed()));

  newAction = new QAction(QIcon(":/images/linenew.png"), tr("Új sor"), this);
  newAction->setShortcut(tr("Ctrl+N"));
  newAction->setStatusTip(tr("Új bejegyzést nyit a katalógusban. (C-n)"));
  newAction->setEnabled(false);
  connect(newAction, SIGNAL(triggered()), anyulogus, SLOT(newPressed()));

  deleteAction = new QAction(QIcon(":/images/linedelete.png"), tr("Sor törlése"), this);
  deleteAction->setShortcut(tr("Ctrl+D"));
  deleteAction->setStatusTip(tr("Kitöröl egy bejegyzést a katalógusból. (C-d)"));
  deleteAction->setEnabled(false);
  connect(deleteAction, SIGNAL(triggered()), anyulogus, SLOT(deletePressed()));

  printAction = new QAction(QIcon(":/images/fileprint.png"), tr("Nyomtatás"), this);
  printAction->setShortcut(tr("Ctrl+P"));
  printAction->setStatusTip(tr("Kinyomtatja a katalógust. (C-p)"));
  printAction->setEnabled(false);
  connect(printAction, SIGNAL(triggered()), anyulogus, SLOT(printPressed()));

  helpAction = new QAction(QIcon(":/images/help.png"), tr("Segítség"), this);
  helpAction->setShortcut(tr("Ctrl+H"));
  helpAction->setStatusTip(tr("Használati utasítás és egyéb információk. (C-h)"));
  connect(helpAction, SIGNAL(triggered()), this, SLOT(helpPressed()));

  // Toolbar
  toolbar = addToolBar(tr("Eszköztár"));
  toolbar->addAction(openAction);
  toolbar->addAction(saveAction);
  toolbar->addAction(exportAction);
  toolbar->addAction(newAction);
  toolbar->addAction(deleteAction);
  toolbar->addAction(printAction);
  toolbar->addAction(helpAction);

  // Title
  setTitle();

  // Status bar
  setStatusBar(new QStatusBar);
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
    QFileDialog::getOpenFileName(this, tr("Megnyitás"), ".",
				 tr("QAnyulógus fájlok (*.anyu)"));
  if(filename != "")
    openFile(filename);
}

bool MainWindow::savePressed()
{
  if(saved)
    return true;

  if(!anyulogus->saveFile(file_name)) {
    QMessageBox::critical(this, "Mentés sikertelen",
			  "A(z) \"" + file_name +
			  "\" fájlt nem tudtam elmenteni.");
    return false;
  }

  saved = true;
  setTitle();

  return true;
}

void MainWindow::exportPressed()
{
  QString filename =
    QFileDialog::getSaveFileName(this, tr("Exportálás"), ".",
				 tr("HTML fájlok (*.html)"));
  if(filename != "") {
    if(!filename.endsWith("html", Qt::CaseInsensitive))
      filename += ".html";
    if(!anyulogus->exportFile(filename)) {
      QMessageBox::critical(this, "Exportálás sikertelen",
			    "A(z) \"" + file_name +
			    "\" fájlt nem tudtam írni.");
    }
  }
}

void MainWindow::helpPressed() const
{
  QTextBrowser *browser = new QTextBrowser;
  browser->setSource(QUrl("qrc:/doc/help.html"));
  browser->setWindowTitle(tr("Használati útmutató"));
  browser->resize(640, 480);
  browser->show();
}

void MainWindow::setTitle()
{
  QString new_title = QString("QAnyulógus");
  if(file_name != "")
    new_title += " - " + file_name.section('/', -1) + (!saved ? "*" : "");
  setWindowTitle(new_title);
  saveAction->setEnabled(!saved);
}

void MainWindow::openFile(QString filename)
{
  if(!anyulogus->openFile(filename)) {
    QMessageBox::critical(this, "A fájl nem nyitható",
			  "A fájl \"" + filename + "\" nem nyitható meg,\n"
			  "vagy a fájlban nem minden bejegyzés hossza azonos.");
    return;
  }

  if(file_name == "") {
    exportAction->setEnabled(true);
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
  int ret = QMessageBox::warning(this, tr("A katalógus megváltozott."),
				 tr("Nem mentetted el a katalógust."),
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
