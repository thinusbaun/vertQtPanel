#include "applet.hpp"
#include <QDebug>
#include <QTimer>
#include <QFont>
#include <QFontMetrics>
#include <QFileSystemWatcher>
//#include <QDir>

class LdmApplet : public Applet
{
	Q_OBJECT
	private:
	    QFileSystemWatcher *m_watcher;
	    bool m_any_mounted;
	    void checkIfAnyMounted();

	public:
	    LdmApplet();
	    ~LdmApplet();
	    QRectF boundingRect() const;
	    void paint(QPainter *painter, const QStyleOptionGraphicsItem *style, QWidget *widget);
	public slots:
	    void directoryChanged(const QString& path);
};
