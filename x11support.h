#ifndef X11SUPPORT_H
#define X11SUPPORT_H
#include <xcb/xcb.h>
#include <xcb/xcb_icccm.h>
#include <QGuiApplication>
#include <qpa/qplatformnativeinterface.h>

class X11Support
{
public:
    X11Support();
    void setNetWmStrut(long long unsigned int id);
    xcb_atom_t atom(const QString& name);
    static X11Support* m_instance;
    xcb_connection_t* m_connection;
    xcb_connection_t* connection();
    QMap<QString, xcb_atom_t> m_cachedAtoms;
};

#endif // X11SUPPORT_H
