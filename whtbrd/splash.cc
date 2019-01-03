#include <startup.hh>

/**
 * a classic Splash window showing messages from qDebug() on the lower left bottoms
 * messages are scrolling upwards, the number of lines is hard coded
 * after 5 seconds of inactivity, it will hide and deletes itself after 1 minute
 */

// one instance
Whtbrd_Splash * instance=NULL;
QtMessageHandler oldMsgHandler=NULL;

void _addMsg(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
  if(oldMsgHandler)
    oldMsgHandler(type,context,msg);
  if(qApp->closingDown()) {
    // app shuts down and all ui will fail
    qInstallMessageHandler(oldMsgHandler); // revert to default handler
    return;
  }
  if(instance)
    instance->addMsg(msg);
}

Whtbrd_Splash::Whtbrd_Splash()
{
  fromHere("splashing"); // a tracing message
  QPixmap pixmap(":/splash2.png"); // from compiled resources
  setPixmap(pixmap);
  setMask(pixmap.mask()); // transparent corners
  setAttribute(Qt::WA_DeleteOnClose,true); // in case there are not other windows
  show();
  startTimer(1000); // for hiding - end due to idling
}

Whtbrd_Splash::~Whtbrd_Splash() {
  fromHere("deleting splash");
  instance=NULL;
}

void Whtbrd_Splash::init() {
  fromHere("initializing splash");
  if(instance==NULL) {
    instance=new Whtbrd_Splash();
    oldMsgHandler= qInstallMessageHandler(_addMsg); // get debug to show in splash
  }
  qDebug()<< "splash initialized";
}

/**
 * member function that shows text on the splash screen
 */
void Whtbrd_Splash::addMsg(const QString &msg)
{
  idle=0; // reset idle counter
  // removing excess lines
  while(_msg.count("\n")>=25) {
    // in place character removal
    _msg.remove(0,_msg.indexOf("\n")+1);
  }
  _msg+=msg+"\n";
  // suitable place is bottomLeft
  showMessage(_msg,Qt::AlignLeft|Qt::AlignBottom,Qt::darkGreen);
  show(); // in case splash is already hiding, getting it up again
}

/**
 * the splash disappears after 5 seconds
 */
void Whtbrd_Splash::timerEvent(QTimerEvent *event) {
  if(++idle>5) {
    // 5 seconds gone
    if(isVisible()) {
      // fromHere("hiding");
      hide();
    }
    if(idle>60) {
      // fromHere("closing");
      close();
    }
  }
}



