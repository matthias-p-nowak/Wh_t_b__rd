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
  MainWindow(); // only getInstance can create main windows

public slots:
  void closeEvent(QCloseEvent *event);
  void closeMain(bool triggered=true);
  void doIdleWork();
  void dummy(bool triggered=true); // dummy slot
  void fullScreen(bool triggered=true);

};
#endif
