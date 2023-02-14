import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15

Page {
    id: loginPage

    signal successLogIn()

    background: Rectangle {
        color: "#ffffff"
    }

    Popup {
        id: popup
        anchors.centerIn: Overlay.overlay
        width: 200
        height: 150
        modal: true
        focus: true

        ColumnLayout {
            anchors.fill: parent
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            Text {
                Layout.alignment: Qt.AlignHCenter
                font.pixelSize: 18
                text: "Неверный пароль"
            }
            Button {
                id: okButton
                Layout.preferredWidth: 100
                Layout.preferredHeight: 40
                Layout.alignment: Qt.AlignHCenter
                text: "Ok"
                onClicked: popup.close()
            }

        }
    }

    ColumnLayout {
        id: form
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        TextField {
            id: passwordField
            Layout.alignment: Qt.AlignHCenter
            Layout.preferredWidth: 200
            Layout.preferredHeight: 40

            focus: true
            placeholderText: qsTr("Password")
            placeholderTextColor: "grey"
            echoMode: TextInput.Password
            verticalAlignment: Text.AlignVCenter
            font.pointSize: 12

            background: Rectangle {
                width: parent.width
                height: parent.height
                border.color: "black"
                border.width: 1
            }
        }

        Button {
            Layout.alignment: Qt.AlignHCenter
            Layout.preferredWidth: 200
            Layout.preferredHeight: 40
            background: Rectangle {
                border.color: "black"
                width: parent.width
                height: parent.height
            }
            text: qsTr("Вход")
            font.pointSize: 12
            onClicked: lm.onLogIn(passwordField.text)
        }

        Connections {
            target: lm
            function onPwdAccepted(ok) {
                if (ok) {
                    loginPage.successLogIn();
                } else {
                    popup.open()
                }
            }
        }
    }
}
