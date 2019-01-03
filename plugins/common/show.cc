#include <common.hh>

Whtbrd_Show::Whtbrd_Show(){
  curr_meme=memes.begin();
}

void Whtbrd_Show::showNext(){
  fromHere("implement!");
  ++curr_meme;
  emit showMeme();
}
