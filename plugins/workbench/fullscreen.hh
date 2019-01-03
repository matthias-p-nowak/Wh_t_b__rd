#ifndef INC_tckQFMyVkGj
#define INC_tckQFMyVkGj

class FullScreen: public QWidget {
public:
  FullScreen();
  void keyPressEvent(QKeyEvent *event) override;
  void paintEvent(QPaintEvent *event) ;
  bool event(QEvent *e);
public slots:
  void showMeme();
};


#endif
