#include <QtCore>
#include <QApplication>
#include <QDialog>
#include <QWidget>
#include <QGridLayout>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QtGui>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include "x11support.h"
#include "panelwindow.hpp"

class item : public QGraphicsItem
{
	public:
		item()
		{
		};
		QRectF boundingRect() const
		{
			return QRectF(0,0,15,15);
		};
		void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
		{
			QBrush br(Qt::red);
			painter->fillRect(boundingRect(), br);
			painter->drawRect(boundingRect());
		}
		void mousePressEvent(QGraphicsSceneMouseEvent *event)
		{
			qDebug() << event->pos();
			QGraphicsItem::mousePressEvent(event);
		}
};

class panel : public QWidget
{
	public:
		panel() : QWidget()
		{
			this->resize(15,800);
			this->setMinimumSize(16,100);
	Display *display = XOpenDisplay(NULL);
	Atom tmp = XInternAtom(display, "_NET_WM_WINDOW_TYPE_DOCK", False);
	XChangeProperty(display, winId(), XInternAtom(display,"_NET_WM_WINDOW_TYPE", False)
					,XA_ATOM, 32, PropModeReplace, (const unsigned char*)&tmp, 1);
	XFlush(display);
	XMapWindow(display, winId());
		};
};

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	PanelWidget dialog;
	//dialog.setStyleSheet("border-style: none; background-color: #2b2f38");
	qDebug() << dialog.winId();
	X11Support::setNetWmStrut(dialog.winId());
	//QGridLayout *lay = new QGridLayout();
	//dialog.setLayout(lay);
	//QGraphicsView *view = new QGraphicsView();
	//QGraphicsScene *scene = new QGraphicsScene();
	//view->setScene(scene);
	//view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	//view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	//lay->addWidget(view);
	//lay->setMargin(0);
	//lay->setContentsMargins(QMargins(0,0,0,0));
	//view->setAlignment(Qt::AlignTop);
	//item *it = new item();
	//scene->addItem(it);
	//item *itt = new item();
	//scene->addItem(itt);
	//itt->setPos(0,15);
	//lay->setSpacing(0);
	////view->setSceneRect(0,0,16,800);
	dialog.show();
	return app.exec();
}
