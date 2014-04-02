#ifndef APPLET_HPP
#define APPLET_HPP
#include <QDebug>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QBrush>
#include <QPainter>

class Applet : public QObject, public QGraphicsItem
{
	Q_OBJECT
	public:
		Applet(QGraphicsItem *parent= 0);
		QRectF boundingRect() const;
		void paint(QPainter *painter, const QStyleOptionGraphicsItem *style, QWidget *widget);
		void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
		void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);
};
#endif
