#include "desktopapplet.hpp"

DesktopApplet::DesktopApplet(QGraphicsItem *parent) : Applet(parent)
{
	side = true;
	numOfDesktops=10;
	m_process = new QProcess();
	m_changeProcess = new QProcess();
	connect(m_process, SIGNAL(readyReadStandardOutput()), this, SLOT(readLine()));
	QStringList arguments;
	arguments << "control" << "--subscribe";
	m_process->start("bspc" , arguments);
}

DesktopApplet::~DesktopApplet()
{
}

QRectF DesktopApplet::boundingRect() const
{
	return QRectF(0,0,16,16*(numOfDesktops+1));
}

void DesktopApplet::readLine()
{
	QString line = m_process->readLine();
	QStringList sList = line.split(":");
	m_desktops.clear();
	for(int i=1;i<sList.length()-1;i++)
	{

		char tmp = sList[i].toLatin1().data()[0];
		switch (tmp)
		{
			case 'u': 
				m_desktops.append(DESKTOP_URGENT);
			break;
			case 'f':
				m_desktops.append(DESKTOP_CLEAR);
			break;
			case 'F':
				m_desktops.append(DESKTOP_THIS_CLEAR);
			break;
			case 'o':
				m_desktops.append(DESKTOP_FULL);
			break;
			case 'O':
				m_desktops.append(DESKTOP_THIS_FULL);
			break;
		}
	}

	m_mode = sList.last() == QString("Ltiled\n") ? 1: 0;

	qDebug() << m_desktops << m_mode;
	update();
}

void DesktopApplet::paint(QPainter *painter, const QStyleOptionGraphicsItem *style, QWidget *widget)
{
	painter->setRenderHint(QPainter::Antialiasing);
	for (int i=0; i<numOfDesktops;i++)
	{
		painter->setPen(Qt::NoPen);
		if (m_desktops[i] == DESKTOP_THIS_CLEAR || m_desktops[i] == DESKTOP_THIS_FULL)
		{
			painter->setBrush(QBrush(Qt::green));
		} else if (m_desktops[i] == DESKTOP_CLEAR)
		{
			painter->setBrush(QBrush(Qt::gray));
		} else if (m_desktops[i] == DESKTOP_FULL)
		{
			painter->setBrush(QBrush(Qt::blue));
		} else
		{
			painter->setBrush(QBrush(Qt::red));
		}
		painter->drawEllipse(QRectF(0,i*16,16,16));
	}
	painter->setPen(Qt::black);
	if (m_mode)
	{
    	painter->drawText(QRectF(0,numOfDesktops*16,16,16), Qt::AlignCenter, "T");
	} else
	{
    	painter->drawText(QRectF(0,numOfDesktops*16,16,16), Qt::AlignCenter, "M");
	}

}
void DesktopApplet::mousePressEvent(QGraphicsSceneMouseEvent	*event)
{
	if(event->button() == 1)
	{
		m_changeProcess->start("bspc", QStringList() << "desktop" << "-f" << "^"+QString::number((event->pos().y()/16)+1));
		m_changeProcess->waitForFinished();
		QWidget *widget= QApplication::topLevelWidgets().at(0);
		widget->showNormal();
		widget->raise();
		widget->activateWindow();
	}
}

void DesktopApplet::wheelEvent(QGraphicsSceneWheelEvent *event)
{
	if (event->delta() > 0)
	{
		m_changeProcess->start("bspc", QStringList() << "desktop" << "-f" << "next");
		m_changeProcess->waitForFinished();
	} else
	{
		m_changeProcess->start("bspc", QStringList() << "desktop" << "-f" << "prev");
		m_changeProcess->waitForFinished();
	}
	QWidget *widget= QApplication::topLevelWidgets().at(0);
	widget->showNormal();
	widget->raise();
	widget->activateWindow();
}
