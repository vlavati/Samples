import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0
import "Singleton.js" as Singleton
import "DriveEditor.js" as DriveEditor

Item {
    id: driveEditor
    property var drivesModel: ListModel {
    }
    property int driveType: DriveEditor.unknownDriveIndex
    property bool isOn: null
    property bool isRelative: null
    property bool isFreerun: null
    property double endPosition: null
    property var editor: undefined
    property bool isNewDrive: false
    Component.onCompleted: {
        editor = Singleton.model.editor
        DriveEditor.initialize(driveEditor)
    }

    RowLayout {
        anchors.fill: parent
        ColumnLayout {
            Button {
                text: qsTr("Append")
                onClicked: DriveEditor.append(driveEditor)
                enabled: driveEditor.isNewDrive
                         && driveEditor.driveType != DriveEditor.unknownDriveIndex
            }
            Button {
                text: qsTr("Remove")
                onClicked: DriveEditor.remove(driveEditor)
                enabled: !driveEditor.isNewDrive
            }
            Button {
                text: "Teach In"
                onClicked: DriveEditor.teachIn(driveEditor)
                enabled: driveEditor.driveType != DriveEditor.unknownDriveIndex
            }
            Button {
                text: qsTr("Set")
                onClicked: DriveEditor.set(driveEditor)
                enabled: !driveEditor.isNewDrive
            }
            Button {
                text: qsTr("Cancel")
                onClicked: DriveEditor.cancel(driveEditor)
            }
            Item {
                Layout.fillHeight: true
            }
        }
        ColumnLayout {
            GridLayout {
                columns: 2
                flow: GridLayout.LeftToRight
                Label {
                    text: qsTr("Name")
                }
                ComboBox {
                    currentIndex: driveEditor.driveType
                    model: drivesModel
                    onCurrentIndexChanged: if (currentIndex !== DriveEditor.unknownDriveIndex)
                                               driveEditor.driveType = currentIndex
                    textRole: "text"
                    enabled: driveEditor.isNewDrive
                }
                Label {
                    text: "On/Off"
                }
                CheckBox {
                    checkedState: driveEditor.isOn ? Qt.Checked : Qt.Unchecked
                    onCheckedChanged: driveEditor.isOn = checked
                }
                Label {
                    text: qsTr("Relative")
                }
                CheckBox {
                    checkedState: driveEditor.isRelative ? Qt.Checked : Qt.Unchecked
                    onCheckedChanged: driveEditor.isRelative = checked
                }
                Label {
                    text: "Free Run"
                }
                CheckBox {
                    checkedState: driveEditor.isFreerun ? Qt.Checked : Qt.Unchecked
                    onCheckedChanged: driveEditor.isFreerun = checked
                }
                Label {
                    text: "End Pos"
                }
                TextField {
                    validator: DoubleValidator {
                    }
                    text: driveEditor.endPosition
                    onTextChanged: driveEditor.endPosition = text
                }
            }
            Item {
                Layout.fillHeight: true
            }
        }
        ColumnLayout {
            Layout.fillWidth: true
        }
    }
}
