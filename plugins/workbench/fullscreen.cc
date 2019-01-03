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
    if(thisShow)
      thisShow->showNext();
    break;
  
  default:
    hide();
    break;
  }
}

void FullScreen::showMeme(){
  fromHere("showing a new meme`");
}
