#include "panelwindow.hpp"
#include "desktopapplet.hpp"
#include "clockapplet.hpp"
#include "ldmapplet.hpp"

PanelWidget::PanelWidget(QWidget *parent) : QWidget(parent)
{
	this->setStyleSheet("border-style:none; background-color:#2b3039;");
	this->resize(16,800);
	m_layout = new QGridLayout();
	this->setLayout(m_layout);
	m_layout->setMargin(0);
	m_layout->setContentsMargins(0,0,0,0);
	m_scene = new QGraphicsScene(this);
	m_view = new QGraphicsView(this);
	m_view->setScene(m_scene);
	m_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	m_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	m_view->setAlignment(Qt::AlignTop);
	m_view->setFixedSize(16,800);
	m_view->setSceneRect(0,0,16,800);
	m_layout->addWidget(m_view);
//TOTAJ USTAWIENIE OKNA
	addItem(new DesktopApplet());
	addItem(new ClockApplet());

}

PanelWidget::~PanelWidget()
{

}

void PanelWidget::addItem(Applet *item)
{
	m_applets.append(item);
	m_scene->addItem(m_applets.last());
	int y=0;
	int downy=800;
	for(int i=0;i<m_applets.length()-1; i++)
	{
		QRectF tmp = m_applets[i]->boundingRect();
		if (m_applets[i]->side)
		{
			y += tmp.height();
		} else
		{
			downy -= tmp.height();
		}
	}
	if (m_applets.last()->side)
	{
		m_applets.last()->setPos(0,y);
	} else
	{
		m_applets.last()->setPos(0,downy-m_applets.last()->boundingRect().height());
	}

}

