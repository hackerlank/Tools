#ifndef __MAINWINDOW_H
#define __MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QAction>
#include <QMenu>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QToolBar>
#include <QTextEdit>
#include <QMainWindow>
#include <QString>
#include <QMenuBar>

#include "GameEditor.h"
#include <Ogre.h>

class LogWidget;
class ProjectWidget;
class CenterTabWidget;
class DragWidget;
class ExplorerWidget;

class EventHandlingOgreWidget;

namespace Ui
{
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

	void createMenus();
	void createActions();
	void createToolBars();
	void loadFile(QString fileName);

public slots:
	void slotNewFile();
	void slotOpenFile();
	//void slotSaveFile();
	void update(void);

private:
	QMenu *fileMenu;
	QMenu *editMenu;
	QMenu *aboutMenu;
	QString fileName;

	QToolBar *fileTool;
	QToolBar *editTool;

	QAction *fileOpenAction;
	QAction *fileNewAction;
	QAction *fileSaveAction;
	QAction *exitAction;
	QAction *copyAction;
	QAction *cutAction;
	QAction *pasteAction;
	QAction *aboutAction;

	QTextEdit *text;

private:
	Aaa m_aaa;
	Ui::MainWindow *m_ui;

	ProjectWidget* m_projectWidget;
	CenterTabWidget* m_centerTabWidget;
	LogWidget* m_logWidget;
	DragWidget* m_dragWidget;
	ExplorerWidget* m_pExplorerWidget;

	EventHandlingOgreWidget* mOgreWidget;
	QTimer* mAutoUpdateTimer;
	bool mAutoUpdateEnabled;

private:
	void connectAction();
	void createDockWidget();
	void testWidget();
	void initHiddenRenderWindow();
};

#endif // MAINWINDOW_H