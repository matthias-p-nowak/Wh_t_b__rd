#ifndef INC_p3TYy1WJEJ2
#define INC_p3TYy1WJEJ2

#include <QMainWindow>
#include <QMenuBar>
#include <QCloseEvent>
#include <QApplication>
#include <iostream>
#include <QStatusBar>
#include <QSettings>
#include <QTimer>
#include <fullscreen.hh>

/**
 * Main window for Wh.t.b..rd.
 * implements singleton pattern - getInstance
 */
class MainWindow: public QMainWindow {

public:
  static MainWindow *getInstance();
  virtual ~MainWindow();
  void showMessage(QString msg); // for logging in statusbar
  void keyPressEvent(QKeyEvent *event) override;
 
private:
  static MainWindow *instance;
  FullScreen fullScreenWidget;
  MainWindow(); // only getInstance can create main windows

public slots:
  void closeEvent(QCloseEvent *event);
  void closeMain(bool checked=false);
  void doIdleWork();
  void dummy(bool checked=false); // dummy slot
  void fullScreen(bool _ignored);

};
#endif
