#ifndef INC_C6vuk8SMxn2
#define INC_C6vuk8SMxn2

#include <QLinkedList>
#include <QObject>
#include <QtPlugin>
#include <set>
#include <typeinfo>

#define fromHere(msg) printf("%s:%d: %s\n",__FILE__,__LINE__,msg)

class IWhtbrdPlugin: public QObject {
  public:
  virtual ~IWhtbrdPlugin(){}
  virtual void startup(QLinkedList<QObject *> &plugins)=0;
};

#define IWhtbrdPluginName "org.whtbrd.plugin/1.0"
Q_DECLARE_INTERFACE(IWhtbrdPlugin, IWhtbrdPluginName)

/**
 * derive all classes with ": virtual public Base"
 */
class Base {
public:
  virtual ~Base(){};
};

template<class T> T* dynamic_cast2(Base *p){
  static std::set<size_t> positive;
  static std::set<size_t> negative;
  size_t t=typeid(p).hash_code();
  if(positive.count(t))
    return static_cast<T*>(p);
  if(negative.count(t))
    return NULL;
  T *n=dynamic_cast<T*>(p);
  if(n)
    positive.insert(t);
  else
    negative.insert(t);
 return n; 
}

#endif
