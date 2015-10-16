import QtQuick 2.0

Item {
    id: tile
    width: modelData.width
    height: modelData.height

    Image {
        id: tileBackground
        anchors.centerIn: parent
        source: modelData.objectImagePath
        rotation: modelData.rotation
    }
}

