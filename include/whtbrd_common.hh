#ifndef INC_C6vuk8SMxn2
#define INC_C6vuk8SMxn2

#include <QtPlugin>
#include <QLinkedList>
#include <QObject>

#define fromHere(msg) printf("%s:%d: %s\n",__FILE__,__LINE__,msg)

class IWhtbrdPlugin: public QObject {
  public:
  virtual ~IWhtbrdPlugin(){}
  virtual void startup(QLinkedList<QObject *> &plugins)=0;
};

#define IWhtbrdPluginName "org.whtbrd.plugin/1.0"

Q_DECLARE_INTERFACE(IWhtbrdPlugin, IWhtbrdPluginName)

#endif
