#include "clockapplet.hpp"

ClockApplet::ClockApplet() : Applet()
{
	m_metrics = new QFontMetrics(QFont());
}

ClockApplet::~ClockApplet()
{
	delete m_metrics;
}


QRectF ClockApplet::boundingRect() const
{
	return QRectF(0,0,15, 4*m_metrics->height());
}

void ClockApplet::paint(QPainter *painter, const QStyleOptionGraphicsItem *style, QWidget *widget)
{
	Applet::paint( painter, style, widget);
	QString tmp = QTime::currentTime().toString("hhmm");
	for(int i=3;i>0;i--)
	{
		tmp = tmp.insert(i, "\n");
	}
	painter->setPen(Qt::black);
	painter->drawText(boundingRect(),Qt::AlignCenter,  tmp); 
}
