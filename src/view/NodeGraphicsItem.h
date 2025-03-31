#ifndef NODEGRAPHICSITEM_H
#define NODEGRAPHICSITEM_H

#include <QGraphicsItem>
#include "../model/LogicGate.h"
#include <QGraphicsScene>

namespace view {
    class PinGraphicsItem;

    class NodeGraphicsItem : public QObject, public QGraphicsItem {
        Q_OBJECT
        Q_INTERFACES(QGraphicsItem)
    public:
        NodeGraphicsItem(model::LogicGate* gate);
        ~NodeGraphicsItem();

        // Required QGraphicsItem overrides
        QRectF boundingRect() const override;
        void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;

        // Pin management
        PinGraphicsItem* findPinItem(model::Pin* pin);

        // Getters
        model::LogicGate* getGate() const;

        // Add missing pin accessor methods
        std::vector<PinGraphicsItem*> getAllPinItems() const;
        void updateDisplayText(const QString& text);
        void updatePinVisuals();

        signals:
            void pinSelected(PinGraphicsItem* pinItem);
            void positionChanged(NodeGraphicsItem* node);

    protected:
        // QGraphicsItem event handlers
        void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
        void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
        void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
        QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

    private:
        model::LogicGate* gate;
        QRectF rect;
        std::vector<PinGraphicsItem*> inputPinItems;
        std::vector<PinGraphicsItem*> outputPinItems;

        void createPinItems();
        void updatePinPositions();
        QColor getGateColor() const;
    };
}

#endif //NODEGRAPHICSITEM_H