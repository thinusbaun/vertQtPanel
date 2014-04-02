#include "applet.hpp"
#include <QDebug>
#include <QTimer>
#include <QFont>
#include <QFontMetrics>
#include <QTime>

class ClockApplet : public Applet
{
	Q_OBJECT
	private:
		QTimer m_timer;
		QFontMetrics *m_metrics;

	public:
		ClockApplet();
		~ClockApplet();
		QRectF boundingRect() const;
		void paint(QPainter *painter, const QStyleOptionGraphicsItem *style, QWidget *widget);
};
