#include "BtnListWidget.h"
#include "DragDropItemWidget.h"

BtnListWidget::BtnListWidget(QWidget *parent, int width_)
	: QWidget(parent)
{
	m_curWidth = width_;
	//test1f();
	test2f();
}

BtnListWidget::~BtnListWidget()
{

}

void BtnListWidget::test1f()
{
	this->setGeometry(QRect(0, 300, 300, 150));

	m_pBtn = new QPushButton(this);
	m_pBtn->setObjectName(QStringLiteral("pushButton"));
	m_pBtn->setGeometry(QRect(20, 20, 200, 30));
	m_pListWidget = new QListWidget(this);
	m_pListWidget->setGeometry(QRect(20, 50, 300, 100));

	QListWidgetItem* item1;
	item1 = new QListWidgetItem("BlueHills", m_pListWidget);//向widget列表中加入一项
	item1 = new QListWidgetItem("Sunset", m_pListWidget);
	item1 = new QListWidgetItem("Water lilies", m_pListWidget);
	item1 = new QListWidgetItem("Himaliya is a good place", m_pListWidget);
	item1 = new QListWidgetItem("Ooty", m_pListWidget);
	item1 = new QListWidgetItem("Hero Honda", m_pListWidget);
	item1 = new QListWidgetItem("www.google.com", m_pListWidget);
	item1 = new QListWidgetItem("orkut.com", m_pListWidget);
	item1 = new QListWidgetItem("sunrise", m_pListWidget);
	item1 = new QListWidgetItem("OVI", m_pListWidget);
	item1 = new QListWidgetItem("Nokia N97", m_pListWidget);
	item1 = new QListWidgetItem("forum.nokia.com", m_pListWidget);
	item1 = new QListWidgetItem("wellcome to Qt", m_pListWidget);
	item1 = new QListWidgetItem("Qt rocks for s60", m_pListWidget);
	item1 = new QListWidgetItem("Symbian c++", m_pListWidget);
	item1 = new QListWidgetItem("5800 Xpress Music", m_pListWidget);
	item1 = new QListWidgetItem("My best Phone", m_pListWidget);
	item1 = new QListWidgetItem("I like N97", m_pListWidget);
	item1 = new QListWidgetItem("Go for 5800", m_pListWidget);
	item1 = new QListWidgetItem("America", m_pListWidget);
}

void BtnListWidget::test2f()
{
	int heightY = 0;

	m_pBtn = new QPushButton(this);
	m_pBtn->setObjectName(QStringLiteral("pushButton"));
	m_pBtn->setGeometry(QRect(0, heightY, m_curWidth, 30));
	heightY += 30;

	DragDropItemWidget* pItemWidget;
	int itemHeight = 30;
	int idx = 0;
	for (; idx < 5; ++idx)
	{
		pItemWidget = new DragDropItemWidget(this, m_curWidth);
		m_itemWidgetVec.push_back(pItemWidget);
		pItemWidget->setGeometry(QRect(0, heightY, m_curWidth, itemHeight));
		heightY += itemHeight;
	}

	this->setGeometry(QRect(0, 0, m_curWidth, heightY));
}

void BtnListWidget::changgeSize(int width_)
{
	QRect pRect;
	pRect = m_pBtn->geometry();
	m_pBtn->setGeometry(pRect.x(), pRect.y(), width_, pRect.height());

	int idx = 0;
	for (; idx < 5; ++idx)
	{
		pRect = m_itemWidgetVec[idx]->geometry();
		m_itemWidgetVec[idx]->changgeSize(width_);
	}

	pRect = this->geometry();
	this->setGeometry(pRect.x(), pRect.y(), width_, pRect.height());
}