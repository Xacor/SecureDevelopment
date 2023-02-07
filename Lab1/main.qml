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

    background: Rectangle {
        anchors.fill: parrent.fill
        color: "grey"
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
            anchors.horizontalCenter: parent.horizontalCenter
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
            anchors.top: passwordField.bottom
            anchors.topMargin: 5
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
}
