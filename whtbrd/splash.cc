#include <startup.hh>

Whtbrd_Splash *_splash=NULL;

void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
  _splash->showMessage(msg);
}

Whtbrd_Splash::Whtbrd_Splash()
{
  _splash=this;
  QPixmap pixmap(":/splash2.png");
  splash.setPixmap(pixmap);
  splash.setMask(pixmap.mask());
  splash.show();
  qInstallMessageHandler(myMessageOutput);
  qDebug()<<"debug output redirected";
  // qDebug()<< "should work by now";
}
// hardcoded number of lines
void Whtbrd_Splash::showMessage(const QString &msg) {
  while(_msg.count("\n")>=25) {
    _msg.remove(0,_msg.indexOf("\n")+1);
  }
  _msg+=msg+"\n";
  splash.showMessage(_msg,Qt::AlignLeft|Qt::AlignBottom,Qt::darkGreen);
  splash.show();
}


