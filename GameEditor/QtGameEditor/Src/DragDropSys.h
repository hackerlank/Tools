#ifndef __DRAGDROPSYS_H
#define __DRAGDROPSYS_H

#include "GameEditor.h"

class QGraphicsItem;
class BuildFactory;
class QPoint;
class BezierCurveItem;

class DragDropSys
{
protected:
	bool m_startDrag;
	QGraphicsItem* m_pDragItem;
	BezierCurveItem* m_pBezierCurveItem;

public:
	DragDropSys();
	~DragDropSys();

	void startDrag(QPoint* pStartPt);
	void stopDrag();
	void drog();

	BezierCurveItem* getBezierCurveItem();
	bool getStartDrag();
};

#endif // DRAGDROPSYS_H