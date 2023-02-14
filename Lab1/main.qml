import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ApplicationWindow {
    id: root
    width: 1280
    height: 720
    visible: true
    title: qsTr("Password Manager")

    StackView {
        id: stack
        anchors.fill: parent
        initialItem: loginPage
    }

    Login {
        id: loginPage
        objectName: "LoginPage"
    }

    Index {
        id: index
    }

    Connections {
        target: loginPage
        function onSuccessLogIn() {
            console.log("success")
            stack.push(index)
        }
    }


}
