#include "pointset.h"

PointSet::PointSet()
{
    B_Position.clear();
    T_Position.clear();

    Point_B.clear();
    Point_T.clear();
}
QList<QPointF> PointSet::getPoint_B(){
    return Point_B;
}
QList<QPointF> PointSet::getPoint_T(){
    return Point_T;
}
void PointSet::addPoint(char Type, int PanID, QPointF points){
    if(Type=='B'){
        if(this->B_Position.find(PanID)!=this->B_Position.end()){
            int position=this->B_Position[PanID];
            this->Point_B[position]=(points);
        }
        else {
            this->B_Position[PanID]=this->Point_B.size();
            this->Point_B.append(points);
        }
    }
    if(Type=='T'){
        if(this->T_Position.find(PanID)!=this->T_Position.end()){
            int position=this->T_Position[PanID];
            this->Point_T[position]=points;
        }
        else {
            this->T_Position[PanID]=this->Point_T.size();
            this->Point_T.append(points);
        }
    }
}
void PointSet::swaps(){
    return;
}
PointSet::~PointSet(){
    B_Position.clear();
    T_Position.clear();

    Point_B.clear();
    Point_T.clear();
}
