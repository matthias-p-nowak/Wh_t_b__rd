#include <workbench.hh>

using namespace std;


class CommandSelectionWidgetList: public QListWidget {
private:
  CommandSelectionWidget *parent;
  QString selSoFar;

public:
  CommandSelectionWidgetList(CommandSelectionWidget *_parent):QListWidget(_parent) {
    parent=_parent;
  };

  void keyPressEvent(QKeyEvent *event) {
    if(event->matches(QKeySequence::Cancel))
      parent->reject();
    QString txt;
    for(QChar c: event->text()) {
      if(c.isLetterOrNumber())
        txt+=c;
    }
    if(!txt.isEmpty()) {
      selSoFar+=txt;
      int i=0;
      while(i < count()) {
        auto row=item(i);
        txt=row->text();
        auto stdtxt=txt.toStdString();
        int f=0;
        for(QChar c: selSoFar) {
          auto ch=c.toLatin1();
          f=txt.indexOf(c,f,Qt::CaseInsensitive);
          if(f<0) {
            delete row;
            break;
          }
        }
        if(f<0)
          continue;
        ++i;
      }
      switch(count()) {
      case 0:
        parent->reject();
        break;
      case 1: {
        auto row=item(0);
        parent->execCmd(row->text());
        parent->accept();
      }
      break;
      default:
        // continue with next stroke
        break;
      }
    }
  }

};



CommandSelectionWidget::CommandSelectionWidget(QWidget *parent):
  QDialog(parent)
{
  setWindowTitle("select command");
  setAttribute(Qt::WA_DeleteOnClose);
  setToolTip("just start typing letters of the desired item");
  setSizeGripEnabled(true);
  auto layout=new QVBoxLayout(this);
  layout->setContentsMargins(0,0,0,0);
  cswl=new CommandSelectionWidgetList(this);
  layout->addWidget(cswl);
  connect(cswl,&QListWidget::itemActivated,this,&CommandSelectionWidget::itemSelected);
  connect(cswl,&QListWidget::itemClicked,this,&CommandSelectionWidget::itemSelected);
  
}

CommandSelectionWidget::~CommandSelectionWidget() {
  fromHere("destroying command selection widget");
}

void CommandSelectionWidget::fill() {
  cswl->clear();
  list<Whtbrd_Cmd *> cmds;
  Whtbrd_Cmd::getCmds(cmds);
  for(auto cmd : cmds) {
    auto wli=new QListWidgetItem(QString::fromStdString(cmd->name),cswl);
    cswl->addItem(wli);
  }
}

void CommandSelectionWidget::execCmd(QString cmdText) {
  list<Whtbrd_Cmd *> cmds;
  Whtbrd_Cmd::getCmds(cmds);
  for(auto cmd : cmds) {
    auto an=QString::fromStdString(cmd->name);
    if(an==cmdText) {
      recentObjects(cmd);
      cmd->exec();
      close();
      return;
    }
  }
}

void CommandSelectionWidget::itemSelected(QListWidgetItem *item){
  QString txt=item->text();
  qDebug()<< "item " << txt << " selected, calling execCmd";
  execCmd(txt);
}
