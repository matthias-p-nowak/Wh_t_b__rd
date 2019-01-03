#ifndef INC_absEc4Sdks5
#define INC_absEc4Sdks5

// #include <startup.hh> // only needed when generating moc files

/**
 * Traditional splash screen with debug messages
 * call Whtbrd_Splash::init() and then forget the splash
 */
class Whtbrd_Splash: public QSplashScreen{
private:
  Whtbrd_Splash();
  ~Whtbrd_Splash();
  // the current set of messages, combined into one string
  QString _msg;
  // counting up idle calls
  int idle=0;
  void timerEvent(QTimerEvent *event);
public:
  // addMsg is public but unusable, because no Whtbrd_Splash object is available
  void addMsg(const QString &msg);
  // creates and shows the splash screen
  static void init();
};

#endif
