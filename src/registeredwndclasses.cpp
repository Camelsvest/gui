#include "registeredwndclasses.h"

WndClassItem::WndClassItem()
    : m_refCount(0)
{
}

WndClassItem::WndClassItem(const char *pszWndClassName)
    : m_classItem(pszWndClassName)
    , m_refCount(0)
{
}


WndClassItem::~WndClassItem()
{
}

int WndClassItem::addRef()
{
    return ++m_refCount;
}

int WndClassItem::release()
{
    return --m_refCount;
}

int WndClassItem::getRefCount()
{
    return m_refCount;
}

WndClassItem& WndClassItem::operator= (WndClassItem &item)
{
    m_classItem = item.m_classItem;
    m_refCount = item.m_refCount;

    return *this;
}

WndClassItem& WndClassItem::operator= (const char *pszWndClassName)
{
    m_classItem = pszWndClassName;
    m_refCount = 0;
    
    return *this;
}

RegisteredWndClasses* RegisteredWndClasses::getInstance()
{
    static RegisteredWndClasses *instance = NULL;

    if (instance == NULL)
        instance = new RegisteredWndClasses;

    return instance;
}

RegisteredWndClasses::RegisteredWndClasses()
{
}

RegisteredWndClasses::~RegisteredWndClasses()
{
}

int RegisteredWndClasses::addRefWndClass(const char *pszWndClassName)
{
    int refCount;
    std::list<WndClassItem>::iterator itera;
    
    itera = findWndClass(pszWndClassName);
    if (itera != m_wndClassesList.end())
    {
        WndClassItem& item = *itera;
        refCount = item.addRef();
    }
    else
    {        
        WndClassItem item = pszWndClassName;
        refCount = item.addRef(); 

        m_wndClassesList.push_back(item);
    }

    return refCount;
}


int RegisteredWndClasses::releaseWndClass(const char *pszWndClassName)
{
    int refCount;    
    std::list<WndClassItem>::iterator itera;
    
    itera = findWndClass(pszWndClassName);
    if (itera != m_wndClassesList.end())
    {
        WndClassItem& item = *itera;
        refCount = item.release();

        if (refCount <= 0)
        {
            m_wndClassesList.erase(itera);
        }
    }
    else
    {
        refCount = -1;        
    }

    return refCount;
}

std::list<WndClassItem>::iterator RegisteredWndClasses::findWndClass(const char *pszWndClassName)
{
    std::list<WndClassItem>::iterator itera;

    for (itera = m_wndClassesList.begin(); itera != m_wndClassesList.end(); itera++)
    {
        WndClassItem& item = *itera;
        if ( 0 == item.m_classItem.compare(pszWndClassName) )
            break;
    }

    return itera;
}


