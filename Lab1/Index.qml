import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15

Page {
    id: indexPage

    signal addBtnClicked
    signal copyToClipboard(id: int, role: int)

    ColumnLayout {
        anchors.fill: parent

        TextField {
            id: searchField

            Layout.fillWidth: true
            Layout.preferredHeight: 40
            padding: 5
            placeholderText: qsTr("Поиск")
            font.pixelSize: 16
            onDisplayTextChanged: filterModel.onSearchInputChanged(displayText)

        }

        Rectangle {
            id: btnBlock

            Layout.fillWidth: true
            Layout.preferredHeight: 50
            color: Material.backgroundColor
            Button {
                id: addBtn
                text: qsTr("Добавить")
                height: parent.height
                onClicked: {indexPage.addBtnClicked()}
            }

            Button {
                id: delBtn
                text: qsTr("Удалить")
                height: parent.height
                anchors.left: addBtn.right
                onClicked: accountList.removeItem()
            }
        }

        ListView {
            id: listview

            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.margins: 5
            width: parent.width
            height: parent.height
            ScrollBar.vertical: ScrollBar { }

            model: filterModel

            delegate: Rectangle {
                id: delegateRect
                width: listview.width
                height: 50
                color: Material.background
                RowLayout {
                    width: listview.width

                    Label {
                        id: site
                        text: model.site
                        font.pixelSize: 16
                        verticalAlignment: Text.AlignVCenter

                        Layout.fillHeight: true
                        Layout.fillWidth: true
                    }
                    Button {
                        id: username
                        text: qsTr("•").repeat(Math.floor(Math.random() * 10) + 1)
                        font.pixelSize: 26
                        background: Pane
                        Layout.fillHeight: true
                        Layout.preferredWidth: parent.width * 0.3

                        ToolTip.timeout: 2500
                        onClicked: function(){
                            ToolTip.show(qsTr("Логин скопирован в буфер обмена"))
                            indexPage.copyToClipboard(model.row, 1)
                        }
                    }
                    Button  {
                        id: password
                        text: qsTr("•").repeat(Math.floor(Math.random() * 10) + 6)
                        font.pixelSize: 26
                        background: Pane
                        Layout.fillHeight: true
                        Layout.preferredWidth: parent.width * 0.3

                        ToolTip.timeout: 2500
                        onClicked:  function(){
                            ToolTip.show(qsTr("Пароль скопирован в буфер обмена"))
                            indexPage.copyToClipboard(model.row, 2)
                        }
                    }
                    CheckBox {
                        checked: model.deleted
                        onClicked: model.deleted = checked
                        Layout.fillHeight: true
                    }
                }
            }
        }
    }
}

