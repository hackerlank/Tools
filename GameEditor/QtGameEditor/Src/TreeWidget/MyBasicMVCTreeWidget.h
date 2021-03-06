#ifndef __MyBasicMVCTreeWidget_H
#define __MyBasicMVCTreeWidget_H

#include "QtIncAll.h"

class MyBasicTreeView;
class MyBasicFileSystemModel;

class MyBasicMVCTreeWidget
{
protected:
	MyBasicTreeView* m_pTreeView;
	MyBasicFileSystemModel* m_pModel;

public:
	MyBasicMVCTreeWidget(QWidget *parent = 0);
	MyBasicTreeView* getTreeViewPtr();
	void add2Layout(QHBoxLayout* layout);
	void add2Splitter(QSplitter * splitter);
	QModelIndex currentIndex() const;
	QFileInfo fileInfo(const QModelIndex &aindex) const;
};

#endif