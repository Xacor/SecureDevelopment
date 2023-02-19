import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15

import Account 1.0

Page {
    id: formPage
    signal accountCreated

    ColumnLayout {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        TextField {
            id: siteField
            Layout.alignment: Qt.AlignHCenter
            Layout.preferredWidth: 200
            Layout.preferredHeight: 40

            focus: true
            placeholderText: qsTr("Site")
            verticalAlignment: Text.AlignVCenter
            font.pointSize: 12

        }
        TextField {
            id: usernameField
            Layout.alignment: Qt.AlignHCenter
            Layout.preferredWidth: 200
            Layout.preferredHeight: 40

            focus: true
            placeholderText: qsTr("Username")
            verticalAlignment: Text.AlignVCenter
            font.pointSize: 12

        }
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
            text: qsTr("Создать")
            font.pointSize: 12
            onClicked: function() {
                accountList.appendItem(siteField.text, usernameField.text, passwordField.text)
                siteField.text = qsTr("")
                usernameField.text = qsTr("")
                passwordField.text = qsTr("")
                formPage.accountCreated()
            }
        }
    }

}
