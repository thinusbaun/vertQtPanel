#include "applet.hpp"
#include <QDebug>
#include <QProcess>
#include <QString>
#include <QApplication>
#include "panelwindow.hpp"
#include <QVector>
#include <QChar>

enum
{
	DESKTOP_URGENT,
	DESKTOP_THIS_FULL,
	DESKTOP_THIS_CLEAR,
	DESKTOP_FULL,
	DESKTOP_CLEAR
};

class DesktopApplet : public Applet
{
	Q_OBJECT
	private:
		int numOfDesktops;
		QProcess *m_process;
		QProcess *m_changeProcess;
		QVector<unsigned int> m_desktops;
		unsigned int m_mode;

	public:
		DesktopApplet(QGraphicsItem *parent = 0);
		~DesktopApplet();
		QRectF boundingRect() const;
		void paint(QPainter *painter, const QStyleOptionGraphicsItem *style, QWidget *widget);
		void mousePressEvent(QGraphicsSceneMouseEvent *event);
		void wheelEvent(QGraphicsSceneWheelEvent *event);
	public slots:
		void readLine();

};
