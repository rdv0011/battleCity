import QtQuick 2.0

Item {
    id: explosion
    x: modelData.positionX
    y: modelData.positionY
    width: modelData.width
    height: modelData.height

    AnimatedSprite {
        id: explosionSprite
        anchors.centerIn: parent
        width: modelData.width
        height: modelData.height
        source: modelData.objectImagePath
        frameCount: 3
        frameRate: 6
        loops: 1
    }

    NumberAnimation on rotation {
        to: 0
        duration: 200

        onRunningChanged: {
            if (!running) {
                modelData.removeObject = modelData.objectId
            }
        }
    }
}


