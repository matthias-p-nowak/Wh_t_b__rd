#ifndef INC_lyLnyiwtYm6
#define INC_lyLnyiwtYm6

#include <list>
#include <whtbrd_base.hh>

class Whtbrd_Meme;

class Whtbrd_Show: public QObject, public Base {
   Q_OBJECT
public:
  Whtbrd_Show();
  void showNext();
  void showPrevious();
  void showNextSlot();
  void showPreviousSlot();
signals:
  void showMeme();
public slots:
private:
  std::list<Whtbrd_Meme *>memes;
  std::list<Whtbrd_Meme *>::iterator curr_meme;
};

class Whtbrd_Meme: public Base {
  friend Whtbrd_Show;
};

#endif
