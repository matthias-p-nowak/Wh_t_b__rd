#ifndef INC_absEc4Sdks5
#define INC_absEc4Sdks5

#include <startup.hh> // only needed when generating moc files

class Whtbrd_Splash: public QSplashScreen{
private:
  Whtbrd_Splash();
  ~Whtbrd_Splash();
  static Whtbrd_Splash *instance;
  QString _msg;
  int idle=0;
  int idleTimer;
  void _addMsg(const QString &msg);
  void timerEvent(QTimerEvent *event);
public:
  static void init();
  static void addMsg(QtMsgType type, const QMessageLogContext &context, const QString &msg);
};

#endif
