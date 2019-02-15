#include "taskGUI.h"

namespace taskPlanerNamespace
{

	taskGUI::taskGUI(QWidget *parent, Qt::WFlags flags)
		: QMainWindow(parent, flags)
	{
		ui.setupUi(this);
		codec = QTextCodec::codecForName("Big5");		

		widget = new QWidget();
		layout = new QGridLayout;

		stateLabel = new QLabel(tr("Robot State: "));
		stateLabel->setFont(QFont("Courier New",20));

		outputLabel = new QLabel(tr("Hello World"));
		outputLabel->setFont(QFont("Courier New",20));

		speakMsg = new QLabel(tr("speakMgr"));
		speakMsg->setFont(QFont("Courier New",20));

		choose1 = new QPushButton(codec->toUnicode("安排行程"));
		choose2 = new QPushButton(codec->toUnicode("視訊電話"));
		choose3 = new QPushButton(codec->toUnicode("拿取咖啡"));
		choose4 = new QPushButton(codec->toUnicode("遞送物品"));
	
		layout->addWidget(stateLabel, 0, 0);
		layout->addWidget(outputLabel, 0, 1);
		layout->addWidget(speakMsg, 1, 0, 1, 2);

		layout->addWidget(choose1, 2, 0, 1, 2);
		layout->addWidget(choose2, 3, 0, 1, 2);
		layout->addWidget(choose3, 4, 0, 1, 2);
		layout->addWidget(choose4, 5, 0, 1, 2);

		//layout->setAlignment(Qt::AlignCenter);
		layout->setSpacing(20);
		layout->setMargin(20);

		choose1->setFont(QFont("Courier New",20));
		choose2->setFont(QFont("Courier New",20));
		choose3->setFont(QFont("Courier New",20));
		choose4->setFont(QFont("Courier New",20));

		connect(choose1, SIGNAL(clicked()), this, SLOT(choose1Event()) );
		connect(choose2, SIGNAL(clicked()), this, SLOT(choose2Event()) );
		connect(choose3, SIGNAL(clicked()), this, SLOT(choose3Event()) );
		connect(choose4, SIGNAL(clicked()), this, SLOT(choose4Event()) );

		/*choose1->hide();
		choose2->hide();
		choose3->hide();
		choose4->hide();*/

		this->setCentralWidget(widget);

		widget->setLayout(layout);
		widget->show();
	}

	taskGUI::~taskGUI()
	{

	}

}
