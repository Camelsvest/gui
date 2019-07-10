#ifndef _REGISTERED_WND_CLASS_H_
#define _REGISTERED_WND_CLASS_H_

#include <string>
#include <list>

class RegisteredWndClasses;

class WndClassItem {
    friend class RegisteredWndClasses;
public:
    WndClassItem();
    WndClassItem(const char *pszWndClassName);
    virtual ~WndClassItem();

    inline int addRef();
    inline int release();
    inline int getRefCount();

    WndClassItem& operator= (WndClassItem &item);
    WndClassItem& operator= (const char *pszWndClassName);
    
private:
    std::string m_classItem;
    int m_refCount;
};

class RegisteredWndClasses {
public:
    static RegisteredWndClasses* getInstance();

    int addRefWndClass(const char *pszWndClassName);
    int releaseWndClass(const char *pszWndClassName);
    
protected:
    RegisteredWndClasses();
    virtual ~RegisteredWndClasses();

    std::list<WndClassItem>::iterator findWndClass(const char *pszWndClassName);
    
private:   
    std::list<WndClassItem>    m_wndClassesList;
};
#endif
