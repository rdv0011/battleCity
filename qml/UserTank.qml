import QtQuick 2.3

Item {
    id: userTank
    x: modelData.positionX
    y: modelData.positionY
    width: modelData.width
    height: modelData.height
    focus: true

    AnimatedSprite {
        id: userTankSprite
        anchors.centerIn: parent
        width: modelData.width
        height: modelData.height
        source: modelData.objectImagePath
        frameCount: 2
        frameRate: 10
        paused: true
        rotation: modelData.rotation
    }

    Keys.onPressed: {
        if (event.key === Qt.Key_Right) {
            modelData.movingDirection = "Right"
            userTankSprite.paused = false;
            event.accepted = true;
         }
         else if (event.key === Qt.Key_Down) {
            modelData.movingDirection = "Down"
            userTankSprite.paused = false;
            event.accepted = true;
         }
         else if (event.key === Qt.Key_Left) {
            modelData.movingDirection = "Left"
            userTankSprite.paused = false;
            event.accepted = true;
         }
         else if (event.key === Qt.Key_Up) {
            modelData.movingDirection = "Up"
            userTankSprite.paused = false;
            event.accepted = true;
         }
         else if (event.key === Qt.Key_Space) {
            modelData.controlKeyPressed = Qt.Key_Space
            event.accepted = true;
         }
    }

    Keys.onReleased: {
        modelData.movingDirection = "None"
        userTankSprite.paused = true;
        event.accepted = true;
    }
}
