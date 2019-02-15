
#ifndef TASKGUI_H
#define TASKGUI_H

#include <QtGui/QMainWindow>
#include <QLabel>
#include <QKeyEvent>
#include <QMessageBox>
#include <QThread>
#include <QGridLayout>
#include <QWidget>
#include <QTextCodec>
#include <QPushButton>
#include <QFont>
#include "ui_taskGUI.h"

namespace taskPlanerNamespace
{

	class taskGUI : public QMainWindow
	{
		Q_OBJECT

	public:
		taskGUI(QWidget *parent = 0, Qt::WFlags flags = 0);
		~taskGUI();

	private:
		Ui::taskGUIClass ui;

		QTextCodec *codec;

		QWidget *widget;
		QGridLayout *layout;
		QLabel *speakMsg;
		QLabel *stateLabel;
		QLabel *outputLabel;
		QPushButton *choose1;
		QPushButton *choose2;
		QPushButton *choose3;
		QPushButton *choose4;
	};
}

#endif // TASKGUI_H
