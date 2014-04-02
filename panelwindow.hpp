#ifndef PANELWINDOW_HPP
#define PANELWINDOW_HPP
#include <QWidget>
#include <QVector>
#include <QGridLayout>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QDebug>
#include "x11support.h"
#include "applet.hpp"

class PanelWidget : public QWidget
{
Q_OBJECT
	private:
	QGraphicsScene *m_scene;
	QGraphicsView *m_view;
	QGridLayout *m_layout;
	QVector<Applet*> m_applets;
	public:
	PanelWidget(QWidget *parent = 0);
	void addItem(Applet *item);
	~PanelWidget();
};
#endif
