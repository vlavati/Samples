import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0
import "Singleton.js" as Singleton
import "GroupEditor.js" as GroupEditor

Item {
    id: groupEditor
    property var joysticksModel: ListModel {
        ListElement {
            jId: 1
            color: "red"
        }
        ListElement {
            jId: 2
            color: "green"
        }
        ListElement {
            jId: 3
            color: "blue"
        }
    }
    property string name: "default name"
    property int joystickIndex: 0
    property int groupMode: 0
    property double joystickMaxSpeed: 0.0
    property double rampStart: 0.0
    property double rampStop: 0.0
    property bool rampSame: false
    property var editor: undefined
    Component.onCompleted: {
        editor = Singleton.model.editor
    }
    RowLayout {
        anchors.fill: parent
        ColumnLayout {
            Button {
                text: qsTr("Append")
                onClicked: GroupEditor.append(groupEditor)
            }
            Button {
                text: qsTr("Cancel")
                onClicked: Singleton.toggleEditor(null)
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
                TextField {
                    text: groupEditor.name
                    onTextChanged: groupEditor.name = text
                }
                Label {
                    text: qsTr("Joystick")
                }
                ComboBox {
                    currentIndex: groupEditor.joystickIndex
                    model: groupEditor.joysticksModel
                    onCurrentIndexChanged: groupEditor.joystickIndex = currentIndex
                    textRole: "color"
                }
                Label {
                    text: qsTr("JoystickMaxSpeed")
                }
                TextField {
                    validator: DoubleValidator {
                    }
                    text: groupEditor.joystickMaxSpeed
                    onTextChanged: groupEditor.joystickMaxSpeed = text
                }
                Label {
                    text: "Ramp Start"
                }
                TextField {
                    validator: DoubleValidator {
                    }
                    text: groupEditor.rampStart
                    onTextChanged: groupEditor.rampStart = text
                }
                Label {
                    text: "Ramp Stop"
                }
                TextField {
                    validator: DoubleValidator {
                    }
                    text: groupEditor.rampStop
                    onTextChanged: groupEditor.rampStop = text
                }
                Label {
                    text: "Ramp Same"
                }
                CheckBox {
                    checkedState: groupEditor.rampSame ? Qt.Checked : Qt.Unchecked
                    onCheckedChanged: groupEditor.rampSame = checked
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
