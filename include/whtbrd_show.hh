#ifndef INC_lyLnyiwtYm6
#define INC_lyLnyiwtYm6

#include <whtbrd_base.hh>

class Whtbrd_Show: public QObject, public Base {
   Q_OBJECT
public:
  Whtbrd_Show();
  void showNext();
signals:
  void showMeme();
public slots:
};
#endif
