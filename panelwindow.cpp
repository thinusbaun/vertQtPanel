#include "panelwindow.hpp"
#include <X11/Xlib.h>
#include "desktopapplet.hpp"
#include "clockapplet.hpp"
#include <X11/Xatom.h>

PanelWidget::PanelWidget(QWidget *parent) : QWidget(parent)
{
	qDebug() << "panelWidget" << this;
	this->setStyleSheet("border-style:none;");
	this->resize(16,800);
	m_layout = new QGridLayout();
	this->setLayout(m_layout);
	m_layout->setMargin(0);
	m_layout->setContentsMargins(0,0,0,0);
	m_scene = new QGraphicsScene(this);
	m_view = new QGraphicsView(this);
	m_view->setScene(m_scene);
	m_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	m_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	m_view->setAlignment(Qt::AlignTop);
	m_view->setFixedSize(16,800);
	m_view->setSceneRect(0,0,16,800);
	m_layout->addWidget(m_view);
    Display *display = XOpenDisplay(NULL);
    Atom tmp = XInternAtom(display, "_NET_WM_WINDOW_TYPE_DOCK", False);
    XChangeProperty(display, winId(), XInternAtom(display,"_NET_WM_WINDOW_TYPE", False)
                    ,XA_ATOM, 32, PropModeReplace, (const unsigned char*)&tmp, 1);
    XFlush(display);
    XMapWindow(display, winId());
	addItem(new DesktopApplet());
	addItem(new ClockApplet());

}

PanelWidget::~PanelWidget()
{

}

void PanelWidget::addItem(Applet *item)
{
	m_applets.append(item);
	m_scene->addItem(m_applets.last());
	int y=0;
	for(int i=0;i<m_applets.length()-1; i++)
	{
		QRectF tmp = m_applets[i]->boundingRect();
		y += tmp.height();
	}
	m_applets.last()->setPos(0,y);
}

