#ifndef POINTSET_H
#define POINTSET_H

#include <QMap>
#include <QList>
#include <QPointF>
class PointSet
{
public:
    PointSet();
    ~PointSet();
    QList<QPointF> getPoint_B();
    QList<QPointF> getPoint_T();
    void addPoint(char Type,int PanID,QPointF points);
private:
    QMap<int,int> B_Position;
    QMap<int,int> T_Position;

    QList<QPointF> Point_B;
    QList<QPointF> Point_T;
};

#endif // POINTSET_H
