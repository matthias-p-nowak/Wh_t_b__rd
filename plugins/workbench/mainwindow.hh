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

class MainWindow: public QMainWindow {

public:
  static MainWindow *getInstance();
  virtual ~MainWindow();
  void showMessage(QString msg);
  void keyPressEvent(QKeyEvent *event) override;
 
private:
  static MainWindow *instance;
  MainWindow();

public slots:
  void closeEvent(QCloseEvent *event);
  void closeMain(bool triggered=true);
  void doIdleWork();
  void dummy(bool triggered=true);
  void fullScreen(bool triggered=true);

};
#endif
