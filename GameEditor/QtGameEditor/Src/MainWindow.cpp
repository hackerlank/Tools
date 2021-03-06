#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "LogWidget.h"
#include "ProjectWidget.h"
#include "CenterTabWidget.h"
#include "DragWidget.h"
#include "ExplorerWidget.h"

#include <QtCore/qnamespace.h>
//#include "DraggableFrame.h"
#include "TestQScrollArea1F.h"
#include "TestQSplitter.h"
#include "EventHandlingOgreWidget.h"
#include <Ogre.h>
#include "OgreSys.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent, 0), m_ui(new Ui::MainWindow)
{
	m_ui->setupUi(this);

	//设置主窗口标题
	setWindowTitle(QStringLiteral("游戏编辑器"));
	//text = new QTextEdit(this);
	//setCentralWidget(text);

	//createActions();
	//createMenus();
	//createToolBars();

	connectAction();
	createDockWidget();

	m_aaa.sayHello();

	//testWidget();
	mAutoUpdateTimer = new QTimer;
	QObject::connect(mAutoUpdateTimer, SIGNAL(timeout()), this, SLOT(update()));
	
	mOgreWidget = new EventHandlingOgreWidget(0, 0);
	m_centerTabWidget->addTab(mOgreWidget, QStringLiteral("OgreWidget"));
	g_pGameEditorSys->getOgreSysPtr()->initialise(mOgreWidget->getWinParams(), mOgreWidget->width(), mOgreWidget->height());
	mOgreWidget->resize(mOgreWidget->width(), mOgreWidget->height());
	mAutoUpdateEnabled = true;

	//On the test system, a value of one here gives a high frame rate and still allows
	//event processing to take place. A value of 0 doubles the frame rate but the mouse
	//becomes jumpy. This property is configerable via setAutoUpdateInterval().
	mAutoUpdateTimer->setInterval(1);
	if (mAutoUpdateEnabled)
	{
		mAutoUpdateTimer->start();
	}

	initHiddenRenderWindow();
}

MainWindow::~MainWindow()
{
	//We delete the OgreWidget last because it
	//owns the LogManager (through Qt's mechanism).
	if (mOgreWidget)
	{
		delete mOgreWidget;
		mOgreWidget = 0;
	}
}

void MainWindow::createDockWidget()
{
	m_projectWidget = new ProjectWidget(this);
	this->addDockWidget(Qt::LeftDockWidgetArea, m_projectWidget);

	m_centerTabWidget = new CenterTabWidget(this);
	//this->addDockWidget(Qt::RightDockWidgetArea, m_centerTabWidget);
	setCentralWidget(m_centerTabWidget);

	m_dragWidget = new DragWidget();
	m_centerTabWidget->addTab(m_dragWidget, QStringLiteral("DragWidget"));

	m_logWidget = new LogWidget(this);
	this->addDockWidget(Qt::BottomDockWidgetArea, m_logWidget);

	// 资源管理器窗口
	m_pExplorerWidget = new ExplorerWidget(this);
	this->addDockWidget(Qt::BottomDockWidgetArea, m_pExplorerWidget);

	//setDockOptions(QMainWindow::ForceTabbedDocks);		//设置停靠选项，比如允许动画或是否允许拖放重合成一个tab选项卡类型的部件，枚举值见4
	tabifyDockWidget(m_logWidget, m_pExplorerWidget);		// 重叠这两个窗口，而不是平铺
	m_logWidget->raise();					// 强制显示 m_logWidget 这个窗口

	// 不停靠，直接显示框架窗口
	//m_logWidget = new LogWidget();
	//m_logWidget->show();

	//DraggableFrame* m_draggableFrame = new DraggableFrame();
	//m_draggableFrame->show();
}

void MainWindow::createActions()
{
	//通过图片路径来实现添加Qt资源文件目的
	fileOpenAction = new QAction(QIcon("C:/qt/Mwindow/open.png"),tr("Open"),this);
	fileOpenAction->setShortcut(tr("Ctrl+O"));
	fileOpenAction->setStatusTip(tr("Open a file"));
	connect(fileOpenAction,SIGNAL(triggered()),this,SLOT(slotOpenFile()));

	fileNewAction = new QAction(QIcon("C:/qt/Mwindow/new.png"),tr("New"),this);
	fileNewAction->setShortcut(tr("Ctrl+N"));
	fileNewAction->setStatusTip(tr("new file"));
	connect(fileNewAction,SIGNAL(triggered()),this,SLOT(slotNewFile()));
  
	fileSaveAction = new QAction(QIcon("C:/qt/Mwindow/save.png"),tr("Save"),this);
	fileSaveAction->setShortcut(tr("Ctrl+S"));
	fileNewAction->setStatusTip(tr("save file"));
	connect(fileNewAction,SIGNAL(triggered()),this,SLOT(slotSaveFile()));

	exitAction = new QAction(tr("Exit"),this);
	exitAction->setShortcut(tr("Ctrl+Q"));
	exitAction->setStatusTip(tr("exit"));
	connect(exitAction,SIGNAL(triggered()),this,SLOT(close()));

	cutAction = new QAction(QIcon("C:/qt/Mwindow/cut.png"),tr("Cut"),this);
	cutAction->setShortcut(tr("Ctrl+X"));
	cutAction->setStatusTip(tr("cut to clipboard"));
	connect(cutAction,SIGNAL(triggered()),text,SLOT(cut()));

	copyAction = new QAction(QIcon("C:/qt/Mwindow/copy.png"),tr("Copy"),this);
	copyAction->setShortcut(tr("Ctrl+C"));
	copyAction->setStatusTip(tr("copy to clipboard"));
	connect(copyAction,SIGNAL(triggered()),this,SLOT(copy()));

	pasteAction = new QAction(QIcon("C:/qt/Mwindow/paste.png"),tr("paste"),this);
	pasteAction->setShortcut(tr("Ctrl+V"));
	pasteAction->setStatusTip(tr("paste clipboard to selection"));
	connect(pasteAction,SIGNAL(triggered()),this,SLOT(paste()));

	aboutAction = new QAction(tr("About"),this);
	connect(aboutAction,SIGNAL(triggered()),this,SLOT(slotAbout()));
}

void MainWindow::createMenus()
{
	fileMenu = menuBar()->addMenu(tr("File"));
	fileMenu->addAction(fileNewAction);
	fileMenu->addAction(fileOpenAction);
	fileMenu->addAction(fileSaveAction);
	fileMenu->addAction(exitAction);

	editMenu = menuBar()->addMenu(tr("Edit"));
	editMenu->addAction(copyAction);
	editMenu->addAction(cutAction);
	editMenu->addAction(pasteAction);

	aboutMenu = menuBar()->addMenu(tr("Help"));
	aboutMenu->addAction(aboutAction);
}

void MainWindow::createToolBars()
{
	fileTool = addToolBar("File");
	fileTool->addAction(fileNewAction);
	fileTool->addAction(fileOpenAction);
	fileTool->addAction(fileSaveAction);

	editTool = addToolBar("Edit");
	editTool->addAction(copyAction);
	editTool->addAction(cutAction);
	editTool->addAction(pasteAction);
}

void MainWindow::slotNewFile()
{
	MainWindow *newWin = new MainWindow;
	newWin->show();
}

void MainWindow::slotOpenFile()
{
	fileName = QFileDialog::getOpenFileName(this);
	if(!fileName.isEmpty())
	{
		if(text->document()->isEmpty())
		{
			loadFile(fileName);
		}
		else
		{
			MainWindow *newWin = new MainWindow;
			newWin->show();
			newWin->loadFile(fileName);
		}
	}
}

void MainWindow::loadFile(QString fileName)
{
	printf("file name:%s\n",fileName.data());
	QFile file(fileName);
	if(file.open(QIODevice::ReadOnly|QIODevice::Text))
	{
		QTextStream textStream(&file);
		while(!textStream.atEnd())
		{
			text->append(textStream.readLine());
			printf("read line.\n");
		}
		printf("end\n");
	}
}

void MainWindow::connectAction()
{
	QObject::connect(m_ui->actionOpen, SIGNAL(triggered()), this, SLOT(slotOpenFile()));
}

void MainWindow::testWidget()
{
	//TestQScrollArea1F* ptest = new TestQScrollArea1F;
	//ptest->show();

	TestQSplitter* pTestQSplitter = new TestQSplitter;
}

void MainWindow::update(void)
{
	mOgreWidget->update();
}

void MainWindow::initHiddenRenderWindow()
{
	Ogre::NameValuePairList hiddenParams;

#if defined(Q_OS_MAC) || defined(Q_OS_WIN)
	hiddenParams["externalWindowHandle"] = Ogre::StringConverter::toString((size_t)winId());
#else
#if QT_VERSION < 0x050000
	const QX11Info info = this->x11Info();
	Ogre::String winHandle;
	winHandle = Ogre::StringConverter::toString((unsigned long)(info.display()));
	winHandle += ":";
	winHandle += Ogre::StringConverter::toString((unsigned int)(info.screen()));
	winHandle += ":";
	winHandle += Ogre::StringConverter::toString((unsigned long)(this->winId()));
	winHandle += ":";
	winHandle += Ogre::StringConverter::toString((unsigned long)(info.visual()));

	hiddenParams["externalWindowHandle"] = winHandle;

#elif QT_VERSION >= 0x050100 && defined(Q_WS_X11)
	const QX11Info info = this->x11Info();
	Ogre::String winHandle;
	winHandle = Ogre::StringConverter::toString((unsigned long)(info.display()));
	winHandle += ":";
	winHandle += Ogre::StringConverter::toString((unsigned int)(info.appScreen()));
	winHandle += ":";
	winHandle += Ogre::StringConverter::toString((unsigned long)(this->winId()));

	hiddenParams["externalWindowHandle"] = winHandle;
#else // only for the time between Qt 5.0 and Qt 5.1 when QX11Info was not included
	hiddenParams["externalWindowHandle"] = Ogre::StringConverter::toString((unsigned long)(this->winId()));
#endif
#endif

#if defined(Q_OS_MAC)
	hiddenParams["macAPICocoaUseNSView"] = "true";
	hiddenParams["macAPI"] = "cocoa";
#endif

	hiddenParams["border"] = "none";
	Ogre::RenderWindow* pPrimary = Ogre::Root::getSingletonPtr()->createRenderWindow("Primary1", 1, 1, false, &hiddenParams);
	pPrimary->setVisible(false);
	//pPrimary->setAutoUpdated(false);

	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);

	// Load resources
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}