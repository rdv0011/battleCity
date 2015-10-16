import QtQuick 2.3

Item {
    id: projectile
    x: modelData.positionX
    y: modelData.positionY
    width: modelData.width
    height: modelData.height

    Image {
        id: projectileImage
        anchors.centerIn: parent
        width: modelData.width
        height: modelData.height
        source: modelData.objectImagePath
        rotation: modelData.rotation
    }
}

