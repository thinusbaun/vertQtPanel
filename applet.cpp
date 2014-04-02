#include "applet.hpp"

Applet::Applet(QGraphicsItem *parent) : QObject(), QGraphicsItem(parent)
{
	side = true;
	setAcceptHoverEvents(true);
}

QRectF Applet::boundingRect() const
{
	return QRectF(0,10,15,15);
}

void Applet::paint(QPainter *painter, const QStyleOptionGraphicsItem *style, QWidget *widget)
{

	QBrush br(Qt::green);
	painter->fillRect(boundingRect(), br);
	painter->drawRect(boundingRect());

}

void Applet::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
	qDebug() << "hover in";
}

void Applet::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{
	qDebug() << "hover out";
}
