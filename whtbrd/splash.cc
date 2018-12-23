#include <startup.hh>

Whtbrd_Splash::Whtbrd_Splash()
{
  fromHere("splashing");
  QPixmap pixmap(":/splash2.png");
  setPixmap(pixmap);
  setMask(pixmap.mask());
  show();
  // qInstallMessageHandler(myMessageOutput);
  qInstallMessageHandler(addMsg);
  setAttribute(Qt::WA_DeleteOnClose,true);
  setAttribute(Qt::WA_QuitOnClose,true);
  idleTimer=startTimer(500);
  setWindowOpacity(0.01);
}

Whtbrd_Splash::~Whtbrd_Splash() {
  fromHere("deleting splash");
  qInstallMessageHandler(NULL); // reset to default
  instance=NULL;
}

void Whtbrd_Splash::init() {
  fromHere("initializing splash");
  if(instance==NULL) {
    instance=new Whtbrd_Splash();
  }
  qDebug()<< "splash initialized";
}

Whtbrd_Splash * Whtbrd_Splash::instance=NULL;

void Whtbrd_Splash::addMsg(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
  instance->_addMsg(msg);
}
void Whtbrd_Splash::_addMsg(const QString &msg)
{
  idle=0;
  while(_msg.count("\n")>=25) {
    _msg.remove(0,_msg.indexOf("\n")+1);
  }
  _msg+=msg+"\n";
  showMessage(_msg,Qt::AlignLeft|Qt::AlignBottom,Qt::darkGreen);
  show();
  std::cout << msg.toStdString()<<std::endl;
}

void Whtbrd_Splash::timerEvent(QTimerEvent *event) {
  if(++idle>20) {
    if(isVisible()) {
      fromHere("hiding");
      hide();
    }
    if(idle>20) {
      fromHere("closing");
      close();
    }
  }
}


