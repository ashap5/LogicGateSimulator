#ifndef PINGRAPHICSITEM_H
#define PINGRAPHICSITEM_H

#include <QGraphicsItem>
#include <QObject>
#include "../model/Pin.h"

namespace view {
    class NodeGraphicsItem;

    class PinGraphicsItem : public QObject, public QGraphicsItem {
        Q_OBJECT
        Q_INTERFACES(QGraphicsItem)

    public:
        PinGraphicsItem(model::Pin* pin, NodeGraphicsItem* parentNode);

        // Required QGraphicsItem overrides
        QRectF boundingRect() const override;
        void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;

        // Getters
        model::Pin* getPin() const;
        bool isSelected() const;

        // Selection
        void setSelected(bool selected);

        signals:
            void pinClicked(PinGraphicsItem* pinItem);

    protected:
        void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

    private:
        model::Pin* pin;
        NodeGraphicsItem* parentNode;
        bool selected;
        QRectF rect;

        QColor getPinColor() const;
    };
}

#endif //PINGRAPHICSITEM_H