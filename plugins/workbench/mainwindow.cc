/**
 * MainWindow 
 */

#include <workbench.hh>

#define C_SECTION_NAME "mainwindow"

MainWindow * MainWindow::instance=NULL;

void addMsg(QtMsgType type, const QMessageLogContext &context, const QString &msg) {
  if(qApp->closingDown()) {
    // the widget stuff will fail
    qInstallMessageHandler(0);
    qDebug()<<msg;
    return;
  }
  MainWindow::getInstance()->showMessage(msg);
  std::cout << msg.toStdString()<<std::endl;
}

MainWindow::MainWindow() {
  qDebug() << "main window created";
  QSettings settings(this);
  setMinimumSize(300,200);
  settings.beginGroup(C_SECTION_NAME);
  restoreGeometry(settings.value("geometry").toByteArray());
  restoreState(settings.value("windowState").toByteArray());
  qDebug()<<"mainwindow ready";
  QTimer::singleShot(0, this, &MainWindow::doIdleWork);
  //
  auto fileMenu = menuBar()->addMenu("&File");
  fileMenu->addAction("&Open",this,&MainWindow::dummy);
  fileMenu->addAction("&Save",this,&MainWindow::dummy);
  fileMenu->addAction("Save &as...",this,&MainWindow::dummy);
  fileMenu->addSeparator();
  fileMenu->addAction("&Quit",this,&MainWindow::closeMain,QKeySequence("Ctrl+Q"));
  //
  auto cmdMenu=menuBar()->addMenu("&Commands");  
  //
  auto toolMenu= menuBar()->addMenu("&Tools");
  toolMenu->addAction("&FullScreen",this,&MainWindow::fullScreen,QKeySequence("F5"));

}

MainWindow::~MainWindow() {
  instance=NULL;
  qDebug() << "main window destroyed";
}


MainWindow * MainWindow::getInstance() {
  if(!instance) {
    qDebug()<< "creating mainwindow instance";
    instance=new MainWindow();
    qInstallMessageHandler(addMsg);
  }
  return instance;
}

void MainWindow::closeEvent(QCloseEvent *event) {
  QSettings settings(this);
  settings.beginGroup(C_SECTION_NAME);
  settings.setValue("geometry", saveGeometry());
  settings.setValue("windowState",saveState());
  instance=NULL;
  QMainWindow::closeEvent(event);
}

void MainWindow::closeMain(bool triggered){
  qDebug()<< "closing";
  close();
}

void MainWindow::doIdleWork() {
  qDebug()<<"doing idle work";
}

void MainWindow::dummy(bool triggered) {
  qDebug()<<"dummy called";
}

void MainWindow::fullScreen(bool triggered){
  qDebug()<<"fullscreen";
}

void MainWindow::showMessage(QString msg) {
  statusBar()->showMessage(msg,2000);
}

void MainWindow::keyPressEvent(QKeyEvent *event){
  qDebug()<< QString("got a key '%1' %2").arg(event->text()).arg(event->key());
  QMainWindow::keyPressEvent(event);
}
