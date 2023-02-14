import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ApplicationWindow {
    id: root
    width: 720
    height: 480
    visible: true
    title: qsTr("Password Manager")

    StackView {
        id: stack
        anchors.fill: parent
        initialItem: loginPage
    }

    Login {
        id: loginPage
    }

    Index {
        id: index
    }

    Connections {
        target: loginPage
        function onSuccessLogIn() {
            stack.push(index)
        }
    }


}
