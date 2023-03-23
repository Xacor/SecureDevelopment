// Copyright (C) 2022 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs.quickimpl

ColorInputsImpl {
    id: root

    hexInput: hex
    redInput: rgbRed
    greenInput: rgbGreen
    blueInput: rgbBlue
    rgbAlphaInput: rgbAlpha
    hsvHueInput: hsvHue
    hsvSaturationInput: hsvSaturation
    valueInput: hsvValue
    hsvAlphaInput: hsvAlpha
    hslHueInput: hslHue
    hslSaturationInput: hslSaturation
    lightnessInput: hslLightness
    hslAlphaInput: hslAlpha

    implicitWidth: content.implicitWidth
    implicitHeight: content.implicitHeight

    TextMetrics {
        id: fourM
        text: "MMMM"
        font: colorSystemComboBox.font
    }

    RowLayout {
        id: content
        anchors.fill: parent
        spacing: 12

        ComboBox {
            id: colorSystemComboBox
            objectName: "colorSystemComboBox"
            editable: false
            flat: true
            background.implicitWidth: 0
            implicitContentWidthPolicy: ComboBox.WidestTextWhenCompleted
            implicitWidth: implicitContentWidth + leftPadding + rightPadding // Workaround QTBUG-106098
            model: ListModel {
                ListElement {
                    name: qsTr("Hex")
                }
                ListElement {
                    name: qsTr("RGB")
                }
                ListElement {
                    name: qsTr("HSV")
                }
                ListElement {
                    name: qsTr("HSL")
                }
            }
        }

        StackLayout {
            objectName: "colorParameters"
            currentIndex: colorSystemComboBox.currentIndex

            Layout.fillWidth: true

            TextField {
                id: hex
                horizontalAlignment: Qt.AlignLeft
                text: root.color
                maximumLength: 9
                validator: RegularExpressionValidator {
                    regularExpression: root.showAlpha ? /^#[0-9A-f]{6}(?:[0-9A-f]{2})?$/ : /^#[0-9A-f]{6}$/
                }
                Layout.fillWidth: true
            }

            RowLayout {
                TextField {
                    id: rgbRed
                    horizontalAlignment: Qt.AlignHCenter
                    text: root.red
                    maximumLength: 3
                    validator: IntValidator {
                        bottom: 0
                        top: 999
                    }
                    implicitWidth: fourM.width + leftPadding + rightPadding
                    Layout.fillWidth: true
                }
                TextField {
                    id: rgbGreen
                    horizontalAlignment: Qt.AlignHCenter
                    text: root.green
                    maximumLength: 3
                    validator: IntValidator {
                        bottom: 0
                        top: 999
                    }
                    implicitWidth: fourM.width + leftPadding + rightPadding
                    Layout.fillWidth: true
                }
                TextField {
                    id: rgbBlue
                    horizontalAlignment: Qt.AlignHCenter
                    text: root.blue
                    maximumLength: 3
                    validator: IntValidator {
                        bottom: 0
                        top: 999
                    }
                    implicitWidth: fourM.width + leftPadding + rightPadding
                    Layout.fillWidth: true
                }
                TextField {
                    id: rgbAlpha
                    horizontalAlignment: Qt.AlignHCenter
                    text: Math.round(root.alpha * 100).toString() + "%"
                    maximumLength: 4
                    validator: RegularExpressionValidator {
                        regularExpression: /^[0-9]{0,3}%?$/
                    }
                    implicitWidth: fourM.width + leftPadding + rightPadding
                    Layout.fillWidth: true
                }
            }

            RowLayout {
                TextField {
                    id: hsvHue
                    horizontalAlignment: Qt.AlignHCenter
                    text: Math.round(root.hue * 360).toString() + "°"
                    maximumLength: 4
                    validator: RegularExpressionValidator {
                        regularExpression: /^[0-9]{0,3}°?$/
                    }
                    implicitWidth: fourM.width + leftPadding + rightPadding
                    Layout.fillWidth: true
                }
                TextField {
                    id: hsvSaturation
                    horizontalAlignment: Qt.AlignHCenter
                    text: Math.round(root.hsvSaturation * 100).toString() + "%"
                    maximumLength: 4
                    validator: RegularExpressionValidator {
                        regularExpression: /^[0-9]{0,3}%?$/
                    }
                    implicitWidth: fourM.width + leftPadding + rightPadding
                    Layout.fillWidth: true
                }
                TextField {
                    id: hsvValue
                    horizontalAlignment: Qt.AlignHCenter
                    text: Math.round(root.value * 100).toString() + "%"
                    maximumLength: 4
                    validator: RegularExpressionValidator {
                        regularExpression: /^[0-9]{0,3}%?$/
                    }
                    implicitWidth: fourM.width + leftPadding + rightPadding
                    Layout.fillWidth: true
                }
                TextField {
                    id: hsvAlpha
                    horizontalAlignment: Qt.AlignHCenter
                    text: Math.round(root.alpha * 100).toString() + "%"
                    maximumLength: 4
                    validator: RegularExpressionValidator {
                        regularExpression: /^[0-9]{0,3}%?$/
                    }
                    implicitWidth: fourM.width + leftPadding + rightPadding
                    Layout.fillWidth: true
                }
            }

            RowLayout {
                TextField {
                    id: hslHue
                    horizontalAlignment: Qt.AlignHCenter
                    text: Math.round(root.hue * 360).toString() + "°"
                    maximumLength: 4
                    validator: RegularExpressionValidator {
                        regularExpression: /^[0-9]{0,3}°?$/
                    }
                    implicitWidth: fourM.width + leftPadding + rightPadding
                    Layout.fillWidth: true
                }
                TextField {
                    id: hslSaturation
                    horizontalAlignment: Qt.AlignHCenter
                    text: Math.round(root.hslSaturation * 100).toString() + "%"
                    maximumLength: 4
                    validator: RegularExpressionValidator {
                        regularExpression: /^[0-9]{0,3}%?$/
                    }
                    implicitWidth: fourM.width + leftPadding + rightPadding
                    Layout.fillWidth: true
                }
                TextField {
                    id: hslLightness
                    horizontalAlignment: Qt.AlignHCenter
                    text: Math.round(root.lightness * 100).toString() + "%"
                    maximumLength: 4
                    validator: RegularExpressionValidator {
                        regularExpression: /^[0-9]{0,3}%?$/
                    }
                    implicitWidth: fourM.width + leftPadding + rightPadding
                    Layout.fillWidth: true
                }
                TextField {
                    id: hslAlpha
                    horizontalAlignment: Qt.AlignHCenter
                    text: Math.round(root.alpha * 100).toString() + "%"
                    maximumLength: 4
                    validator: RegularExpressionValidator {
                        regularExpression: /^[0-9]{0,3}%?$/
                    }
                    implicitWidth: fourM.width + leftPadding + rightPadding
                    Layout.fillWidth: true
                }
            }
        }
    }
}
