#include "clockapplet.hpp"

ClockApplet::ClockApplet() : Applet()
{
	m_metrics = new QFontMetrics(QFont());
	side = false;
	connect(&m_timer, SIGNAL(timeout()), this, SLOT(updateTime()));
	m_timer.start(1234);
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
	//Applet::paint( painter, style, widget);
	QString tmp = QTime::currentTime().toString("hhmm");
	for(int i=3;i>0;i--)
	{
	    
		tmp = tmp.insert(i, "\n");
	}
	//QFont font = painter->font();
	//font.setBold(true);
	//painter->setFont(font);
	painter->setPen(Qt::white);
	painter->drawText(boundingRect(),Qt::AlignCenter,  tmp); 
}

void ClockApplet::updateTime()
{
	update();
}
