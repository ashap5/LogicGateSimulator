#ifndef CONNECTIONGRAPHICSITEM_H
#define CONNECTIONGRAPHICSITEM_H

#include <QGraphicsItem>
#include <QGraphicsPathItem>
#include <QPainterPath>
#include "../model/Connection.h"

namespace view {
    class PinGraphicsItem;

    class ConnectionGraphicsItem : public QGraphicsPathItem {
    public:
        ConnectionGraphicsItem(model::Connection* connection, 
                              PinGraphicsItem* sourcePin, 
                              PinGraphicsItem* targetPin);
        
        // Required QGraphicsItem overrides
        QRectF boundingRect() const override;
        void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
        
        // Connection management
        model::Connection* getConnection() const;
        PinGraphicsItem* getSourcePin() const;
        PinGraphicsItem* getTargetPin() const;
        
        // Path updates
        void updatePath();
        
    protected:
        void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
        
    private:
        model::Connection* connection;
        PinGraphicsItem* sourcePin;
        PinGraphicsItem* targetPin;
        QPainterPath path;
        
        // Helper methods
        QPainterPath createConnectionPath(const QPointF& start, const QPointF& end) const;
    };
}

#endif //CONNECTIONGRAPHICSITEM_H