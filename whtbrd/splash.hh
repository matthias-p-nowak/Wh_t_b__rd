#ifndef INCLUDED_201812221
#define INCLUDED_201812221

// #include <startup.hh> // only needed when generating moc files

class Whtbrd_Splash{
private:
  QSplashScreen splash;
  QString _msg;
public:
  Whtbrd_Splash();
  // virtual ~Whtbrd_Splash();
  void showMessage(const QString &msg);
};

#endif
