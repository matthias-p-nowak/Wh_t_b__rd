#include <workbench.hh>
/**
 * MainWindow 
 */


#define C_SECTION_NAME "mainwindow"

MainWindow * MainWindow::instance=NULL;
QtMessageHandler oldMsgHandler=NULL;
/**
 * a normal C function that is a message handler for Qt's log
 * add to log system by getInstance
 */
void addMsg(QtMsgType type, const QMessageLogContext &context, const QString &msg) {
  if(oldMsgHandler)
    oldMsgHandler(type,context,msg);
  // when the app is closing, displaying messages on screen will fail
  if(qApp->closingDown()) {
    // the widget stuff will fail
    qInstallMessageHandler(0); // back to default
    return;
  }
  MainWindow::getInstance()->showMessage(msg);
}

/**
 * creates some of the widgets, others are postponed
 */
MainWindow::MainWindow() {
  qDebug() << "main window created";
  setMinimumSize(300,200); // just in case
  // restoring from previous runs
  QSettings settings(this);
  settings.beginGroup(C_SECTION_NAME);
  restoreGeometry(settings.value("geometry").toByteArray());
  restoreState(settings.value("windowState").toByteArray());

  // ----- creating menus -----
  auto fileMenu = menuBar()->addMenu("&File");
  fileMenu->addAction("&Open",this,&MainWindow::dummy,QKeySequence("Ctrl+O"));
  fileMenu->addAction("&Save",this,&MainWindow::dummy,QKeySequence("Ctrl+S"));
  fileMenu->addAction("Save &as...",this,&MainWindow::dummy);
  fileMenu->addSeparator();
  fileMenu->addAction("&Quit",this,&MainWindow::closeMain,QKeySequence("Ctrl+Q"));
  //
  auto cmdMenu=menuBar()->addMenu("&Commands");  
  //
  auto toolMenu= menuBar()->addMenu("&Tools");
  toolMenu->addAction("&FullScreen",this,&MainWindow::fullScreen,QKeySequence("F5"));
  toolMenu->addAction("Add &plugin",this,&MainWindow::dummy);
  // -----
  // TODO set the central widget, 
  // TODO add toolbars
  // 
  setCentralWidget(new Preview());
  // ----- postponing other actions -----
  QTimer::singleShot(0, this, &MainWindow::doIdleWork);
}

MainWindow::~MainWindow() {
  instance=NULL;
}

/**
 * singleton pattern
 * creates instance and adds the log handler
 */
MainWindow * MainWindow::getInstance() {
  if(!instance) {
    qDebug()<< "creating mainwindow instance";
    instance=new MainWindow();
    qInstallMessageHandler(0); // remove splash - go back to default
    oldMsgHandler=qInstallMessageHandler(addMsg);
  }
  return instance;
}

void MainWindow::closeEvent(QCloseEvent *event) {
  // ----- saving for restore -----
  QSettings settings(this);
  settings.beginGroup(C_SECTION_NAME);
  settings.setValue("geometry", saveGeometry());
  settings.setValue("windowState",saveState());
  instance=NULL;
  QMainWindow::closeEvent(event);
}

// actions can't call closeEvent
void MainWindow::closeMain(bool triggered){
  qApp->closeAllWindows();
}

void MainWindow::doIdleWork() {
  // TODO: advance this one
  // - prepare next meme
  qDebug()<<"doing idle work";
  // TODO open arguments as presentations
}

/**
 * only as a placeholder
 */
void MainWindow::dummy(bool triggered) {
  qDebug()<<"dummy called";
}

/**
 * for actions that trigger full screen
 */
void MainWindow::fullScreen(bool _ignored){
  qDebug()<<"fullscreen";
  fullScreenWidget.showFullScreen();
}

/**
 * Debug messages are shown in the status bar for 2 seconds
 */
void MainWindow::showMessage(QString msg) {
  statusBar()->showMessage(msg,2000);
}

/**
 * Main window reacts to menu items and key strokes
 */
void MainWindow::keyPressEvent(QKeyEvent *event){
  qDebug()<< QString("got a key '%1' %2").arg(event->text()).arg(event->key());
  
  QMainWindow::keyPressEvent(event);
}
