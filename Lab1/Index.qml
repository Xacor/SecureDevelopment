import QtQuick 2.15
import QtQuick.Controls 2.15

Page {
    id: indexPage
    background: Rectangle {
        color: "grey"
    }

    header: MenuBar {
        background: Rectangle {
            border.color: "black"
        }

        Button {
            id: addBtn
            text: qsTr("Добавить")
        }
        Button {
            text: qsTr("Удалить")
            anchors.left: addBtn.right
        }
    }
}
