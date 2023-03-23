import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15

ApplicationWindow {
    id: root
    width: 720
    height: 480
    visible: true
    title: qsTr("Password Manager")



    Material.theme: Material.Dark
    Material.accent: Material.Purple

    StackView {
        id: stack
        anchors.fill: parent
        initialItem: loginPage
    }

    Login {
        id: loginPage
    }

    Form {
        id: form
        visible: false
    }

    Index {
        id: index
        visible: false
    }


    Connections {
        target: loginPage
        function onSuccessLogIn() {
            stack.push(index)
        }

    }

    Connections {
        target: index
        function onAddBtnClicked() {
            stack.push(form)
        }

    }

    Connections {
        target: form
        function onAccountCreated() {
            stack.pop()
        }

    }
}
