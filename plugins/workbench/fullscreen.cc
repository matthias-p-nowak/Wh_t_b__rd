#include <workbench.hh>

Whtbrd_Show* thisShow=NULL;

FullScreen::FullScreen() {
  QPalette pal = palette();
  pal.setColor(QPalette::Background, Qt::white);
  setAutoFillBackground(true);
  setPalette(pal);
}

void FullScreen::paintEvent(QPaintEvent *event) {
  auto rect=event->rect();
}

bool FullScreen::event(QEvent *e) {
  if (e->type() == QEvent::WindowActivate) {
    qDebug() << "full screen activated";
    for(auto b: recentObjects())
    {
      auto ws=dynamic_cast2<Whtbrd_Show>(b);
      if(ws) {
        if(thisShow)
          {
            thisShow->disconnect(this);
          }
        thisShow=ws;
        connect(thisShow,&Whtbrd_Show::showMeme,this,&FullScreen::showMeme);
        qDebug()<<"got a show";
        break;
      }
    }
    showMeme();
  }
  return QWidget::event(e);
}

void FullScreen::keyPressEvent(QKeyEvent *event) {
  auto key=event->key();
  switch(key) {
  case Qt::Key_Space:
  case Qt::Key_Down:
  case Qt::Key_Enter:
  case Qt::Key_Return:
  case Qt::Key_PageDown:
    if(thisShow)
      thisShow->showNext();
    break;
  case Qt::Key_Up:
  case Qt::Key_Backspace:
  case Qt::Key_PageUp:
    if(thisShow)
      thisShow->showPrevious();
    break;
  case Qt::Key_Left:
    if(thisShow)
      thisShow->showPreviousSlot();
    break;
  case Qt::Key_Right:
    if(thisShow)
      thisShow->showNextSlot();
  default:
    hide();
    break;
  }
}

void FullScreen::showMeme(){
  if(! isVisible())
    return;
  fromHere("showing a new meme`");
}
