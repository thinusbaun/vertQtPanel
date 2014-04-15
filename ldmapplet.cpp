#include "ldmapplet.hpp"

LdmApplet::LdmApplet() : Applet()
{
    side = true;
    m_watcher = new QFileSystemWatcher();
    m_watcher->addPath("/media/");
    connect(m_watcher, SIGNAL(directoryChanged(const QString&)), this, SLOT(directoryChanged(const QString)));
    checkIfAnyMounted();
}

LdmApplet::~LdmApplet()
{
    delete m_watcher;
}


QRectF LdmApplet::boundingRect() const
{
	return QRectF(0,0,15, 16);
}

void LdmApplet::paint(QPainter *painter, const QStyleOptionGraphicsItem *style, QWidget *widget)
{
	Applet::paint( painter, style, widget);
}

void LdmApplet::directoryChanged(const QString& path)
{
    checkIfAnyMounted();
    qDebug() << path << m_any_mounted;
}

void LdmApplet::checkIfAnyMounted()
{
    //QDir m_dir = QDir("/media/");
    //if (m_dir.count() == 2)
    //{
	//m_any_mounted = false;
    //} else
    //{
	//m_any_mounted = true;
    //}
    //m_any_mounted = (m_dir.count() == 2) ? false : true;
}

