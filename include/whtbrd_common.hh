#ifndef INC_C6vuk8SMxn2
#define INC_C6vuk8SMxn2

/**
 * Wh.t.b..rd's general include file
 */

#include <QObject>
#include <QtPlugin>
#include <set>
#include <typeinfo>

/**
 * Macro that helps finding origins of messages
 */
#define fromHere(msg) printf("%s:%d: %s\n",__FILE__,__LINE__,msg)

/**
 * Plugins in Qt have an instance object which implements certain interfaces
 */
class IWhtbrdPlugin: public QObject {
  public:
  // a virtual destructor is included in QObject
  // there is no guarantee in which order startup is called, use a 
  // QTimer::singleShot to postpone more advanced initializations
  virtual void startup()=0;
};
#define IWhtbrdPluginName "org.whtbrd.plugin/1.0"
Q_DECLARE_INTERFACE(IWhtbrdPlugin, IWhtbrdPluginName)

/**
 * derive all classes for customized downcasting from
 *  ": virtual public Base"
 * all it is needed is a class with 1 virtual function
 */
class Base {
public:
  virtual ~Base(){};
};

/**
 * Provides a customized version of dynamic_cast from C++.
 * 
 * Reason: the complexity of multiple inheritance in C++ makes the normal
 * downcast quite expensive when compared to C#, which stores a list of 
 * implemented interfaces and classes in the runtime information.
 * 
 * Function: this class uses the dynamic_cast from C++ but caches the result.
 * In case of a cache hit, a simple static_cast is enough.
 * 
 */
template<class T> T* dynamic_cast2(Base *p){
  // the following are one set for each used T
  static std::set<size_t> positive;
  static std::set<size_t> negative;
  // getting an id from the RTTI
  size_t t=typeid(p).hash_code();
  // Cache hits?
  if(positive.count(t))
    return static_cast<T*>(p);
  if(negative.count(t))
    return NULL;
  // let C++ do it's job - we don't reinvent the wheel
  T *n=dynamic_cast<T*>(p);
  // updating cache
  if(n)
    positive.insert(t);
  else
    negative.insert(t);
 return n; 
}

#endif
