import QtQuick 2.3

Item {
    id: controlPanel
    Item {
        id: controlUpperPanel
        anchors.top: parent.top
        anchors.left: parent.left
        Grid {
            id: controlPanelGrid
            columns: 2
            rows: gameBoard.maxFragsCount / 2
            spacing: 0
            Repeater {
                model: gameBoard.frags
                EnemyFrag { }
            }
        }
    }
    Item {
        id: controlLowerPanel
        y: controlPanelGrid.y + controlPanelGrid.height + 64
        anchors.left: parent.left
        Grid {
             id: controlLowerPanelGrid
             columns: 1
             rows: 4
             spacing: 0
             Row {
                 Text {
                     font.family: "Helvetica"
                     font.pointSize: 20
                     smooth: true
                     color: "black"
                     text: "IP"
                 }
             }
             Row {
                 Text {
                     font.family: "Helvetica"
                     font.pointSize: 20
                     smooth: true
                     color: "black"
                     text: gameBoard.fragsCount
                 }
             }
             Row {
                 Text {
                     font.family: "Helvetica"
                     font.pointSize: 20
                     smooth: true
                     color: "black"
                     text: "Flags"
                 }
             }
             Row {
                 Text {
                     font.family: "Helvetica"
                     font.pointSize: 20
                     smooth: true
                     color: "black"
                     text: gameBoard.flagsCount
                 }
             }
         }
     }
}

