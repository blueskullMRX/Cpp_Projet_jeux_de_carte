#include "table.h"

Table::Table(Scene *sc):Hand::Hand(sc)
{
    qreal x=sc->width();
    qreal y=sc->height();
    qInfo() << x << "," << y;
    for(int i=0 ; i<6 ; i++) emptyPos.push_back(QPointF(-x*0.291 + i*x*0.116,y*0.105));
    for(int i=0 ; i<6 ; i++) emptyPos.push_back(QPointF(-x*0.291 + i*x*0.116,-y*0.105));
    srand(time(0));
    for(int i=1 ; i< rand() ; i++) std::random_shuffle(emptyPos.begin(),emptyPos.end());
}

void Table::fillPos(QPointF pos)
{
    for(int i=0 ; i<12 ; i++)
    {
        if(emptyPos[i]==pos)
        {
        emptyPos.removeAt(i);
        emptyPos.squeeze();
        usedPos.push_back(pos);
        break;
        }
    }
}
void Table::freePos(QPointF pos){
    for(int i=0 ; i<usedPos.length() ; i++)
    {
        if(usedPos[i]==pos)
        {
        usedPos.removeAt(i);
        usedPos.squeeze();
        emptyPos.push_back(pos);
        break;
        }
    }

}




