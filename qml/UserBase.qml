import QtQuick 2.3

Item {
    id: userBase
    x: modelData.positionX
    y: modelData.positionY
    width: modelData.width
    height: modelData.height

    Image {
        id: userBaseImage
        anchors.centerIn: parent
        source: modelData.objectImagePath
        rotation: modelData.rotation
    }
}
