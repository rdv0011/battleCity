import QtQuick 2.3

Rectangle {
    property alias mouseArea: mouseArea

    width: boardGrid.width + controlPanel.width + 64
    height: boardGrid.height + 128
    color: "gray"

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        Item {
            x:64
            y:64
            Grid {
                id: boardGrid
                columns: gameBoard.colsCount
                rows: gameBoard.rowsCount
                spacing: 0
                Repeater {
                    model: gameBoard.tiles
                    Tile { }
                }
                Repeater {
			model: gameBoard.userBases
			UserBase { }
		}
		Repeater {
			model: gameBoard.userTanks
			UserTank { }
		}
		Repeater {
			model: gameBoard.enemyTanks
			EnemyTank { }
		}
		Repeater {
			model: gameBoard.projectiles
			Projectile { }
		}
		Repeater {
			model: gameBoard.fragsLast
			EnemyFrag {}
		}
            }
        }
        ControlPanel {
            id: controlPanel
	    x: boardGrid.width + 96
	    y: 96
	    height: parent.height - 128 - 64
	    width: 128
        }
    }
}

