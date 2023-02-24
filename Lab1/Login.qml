import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

Page {
    id: loginPage

    signal successLogIn()
    signal login(string password)

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
            Label {
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
            echoMode: TextInput.Password
            verticalAlignment: Text.AlignVCenter
            font.pointSize: 12

        }

        Button {
            Layout.alignment: Qt.AlignHCenter
            Layout.preferredWidth: 200
            Layout.preferredHeight: 40
            text: qsTr("Вход")
            font.pointSize: 12
            onClicked: loginPage.login(passwordField.text)
        }

        Connections {
            target: lm
            function onPwdChecked(ok) {
                if (ok) {
                    loginPage.successLogIn();
                    return;
                }
                popup.open()
            }
        }
    }
}
