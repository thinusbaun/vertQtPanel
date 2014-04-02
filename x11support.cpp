#include "x11support.h"
#include <X11/Xlib.h>
#include <X11/Xatom.h>

X11Support::X11Support()
{
}

void X11Support::setNetWmStrut(long long unsigned int id)
{
    Display *display = XOpenDisplay(NULL);
    Atom tmp = XInternAtom(display, "_NET_WM_WINDOW_TYPE_DOCK", False);
    XChangeProperty(display, id, XInternAtom(display,"_NET_WM_WINDOW_TYPE", False)
                    ,XA_ATOM, 32, PropModeReplace, (const unsigned char*)&tmp, 1);
    XFlush(display);
    XMapWindow(display, id);
}
