import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0
import QtQuick.Controls.Styles 1.1

Rectangle {
    id: singleCueView
    height: defaultItem.height
    width: parent.width
    color: "red"
    //(index%2 === 0)? TableViewStyle.backgroundColor: TableViewStyle.alternateBackgroundColor
    property int buttonWidth: 40
    signal select
    states: [
        State {
            when: cueId !== -1 && singleCueView.ListView.isCurrentItem
            name: "selected"
            PropertyChanges {
                target: selectedItem
                opacity: 1.0
                z: 1
                enabled: true
            }
            PropertyChanges {
                target: singleCueView
                height: selectedItem.height
            }
            PropertyChanges {
                target: defaultItem
                opacity: 0.0
                z: 0.0
                enabled: false
            }
        },
        State {
            when: cueId === -1
            name: "new"
            PropertyChanges {
                target: newItem
                opacity: 1.0
                z: 1
                enabled: true
            }
            PropertyChanges {
                target: singleCueView
                height: newItem.height
            }
            PropertyChanges {
                target: defaultItem
                opacity: 0.0
                z: 0.0
                enabled: false
            }
        }
    ]
    TextField {
        readOnly: true
        id: defaultItem
        opacity: 1.0
        enabled: true
        z: 1.0
        text: (cueName !== undefined) ? cueName : ""
        MouseArea {
            anchors.fill: parent
            onClicked: singleCueView.select()
        }
    }
    RowLayout {
        id: selectedItem
        opacity: 0.0
        enabled: false
        z: 0.0
        ColumnLayout {
            TextField {
                readOnly: true
                text: (cueName !== undefined) ? cueName : ""
                MouseArea {
                    anchors.fill: parent
                    onClicked: singleCueView.select()
                }
            }
            RowLayout {
                spacing: 0
                Button {
                    text: qsTr("Up")
                    implicitWidth: buttonWidth
                }
                Button {
                    text: qsTr("Down")
                    implicitWidth: buttonWidth
                }
                Button {
                    text: qsTr("Copy")
                    implicitWidth: buttonWidth
                }
                Button {
                    text: qsTr("Paste")
                    implicitWidth: buttonWidth
                }
                Button {
                    text: qsTr("Save")
                    implicitWidth: buttonWidth
                }
                Button {
                    text: qsTr("Delete")
                    implicitWidth: buttonWidth
                }
            }
        }
    }
    Button {
        id: newItem
        opacity: 0.0
        enabled: false
        z: 0.0
        text: "+"
        implicitWidth: buttonWidth
    }
}
