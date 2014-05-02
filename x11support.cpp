#include "x11support.h"
//
////
//// Code copied from https://github.com/MadFishTheOne/qtpanel/tree/qt5 
//// Sorry ^^
//// I must refactor this code...
//
X11Support* X11Support::m_instance = NULL;

X11Support::X11Support()
{
  m_instance = this;
  m_connection = reinterpret_cast<xcb_connection_t*>(QGuiApplication::platformNativeInterface()->nativeResourceForWindow("connection", NULL));
}

void X11Support::setNetWmStrut(long long unsigned int id)
{
  QString a("_NET_WM_WINDOW_TYPE");
  QString b("_NET_WM_WINDOW_TYPE_DOCK");
  xcb_atom_t t = atom(b);
  xcb_change_property(connection(), XCB_PROP_MODE_REPLACE, id, atom(a), XCB_ATOM_ATOM, 32, 1, &t);
//NAPISAĆ!a
}
xcb_atom_t X11Support::atom(const QString& name)
{
  if(!m_instance->m_cachedAtoms.contains(name))
  {
    xcb_atom_t atom = 0;
    xcb_intern_atom_cookie_t cookie = xcb_intern_atom(connection(), 0, name.toLatin1().length(), name.toLatin1().data());
    xcb_intern_atom_reply_t* reply = xcb_intern_atom_reply(connection(), cookie, NULL);
    if(reply != NULL)
    {
      atom = reply->atom;
      free(reply);
    }
    m_instance->m_cachedAtoms[name] = atom;
  }
  return m_instance->m_cachedAtoms[name];
}
xcb_connection_t* X11Support::connection()
{
  return m_connection;
}
