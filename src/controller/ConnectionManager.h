#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H

#include <QObject>
#include <QGraphicsScene>
#include <vector>
#include "../view/PinGraphicsItem.h"
#include "../view/NodeGraphicsItem.h"
#include "../view/ConnectionGraphicsItem.h" // Add this include
#include "../model/Circuit.h"

namespace controller {
    class ConnectionManager : public QObject {
        Q_OBJECT

    public:
        ConnectionManager(QGraphicsScene* scene, QObject* parent = nullptr);
        ~ConnectionManager();

        // Pin selection and connection handling
        void handlePinClicked(view::PinGraphicsItem* pin);
        void confirmConnection();
        void cancelSelection();

        bool hasSelection() const;
        bool canConnect() const;

        // Creates visual connection item
        view::ConnectionGraphicsItem* createConnectionGraphicsItem(
            model::Connection* connection,
            view::PinGraphicsItem* sourcePin,
            view::PinGraphicsItem* targetPin);

        public slots:
            void onPinSelected(view::PinGraphicsItem* pin);
        void updatePinVisuals();
        void positionChanged(view::NodeGraphicsItem* node);

        signals:
            void connectionCreated(view::ConnectionGraphicsItem* connection);

    private:
        QGraphicsScene* scene;
        std::vector<view::PinGraphicsItem*> selectedPins;
        view::PinGraphicsItem* startPin = nullptr;
        model::Circuit* circuit = nullptr;
    };
}

#endif // CONNECTIONMANAGER_H