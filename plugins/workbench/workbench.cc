#include <workbench.hh>

using namespace std;

/**
 * simply get the main window open
 */
void WorkbenchPlugin::startup(){
  qDebug()<<"workbench starting up";
  setObjectName("workbench");
  MainWindow *mw=MainWindow::getInstance();
  mw->show();
  new EditCommand();
}

