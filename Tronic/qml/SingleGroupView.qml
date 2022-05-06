import QtQuick 2.0
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0
import "Singleton.js" as Singleton

GroupBox {
    title: groupName
    width: parent.width
    height: 80
    property bool highlighted: Singleton.model.highlightedGroup === index
    RowLayout {
        anchors.fill: parent
        RadioButton {
            checked: Singleton.model.selectedGroup === index
            MouseArea {
                anchors.fill: parent
                onClicked: Singleton.model.selectedGroup = index
            }
        }
        TextField {
            text: joystickColor
        }
        TextField {
            text: joystickMaxSpeed
        }
        TextField {
            text: rampStart
        }
        TextField {
            text: index
        }
        DriveListView {
            Layout.fillHeight: true
            Layout.fillWidth: true
            model: drives
            groupIndex: index
        }
    }
    MouseArea {
        z: (highlighted) ? -1 : 1
        enabled: (highlighted) ? false : true
        id: activationArea
        anchors.fill: parent
        hoverEnabled: true
        onPositionChanged: {
            Singleton.model.highlightedGroup = index
        }
        Rectangle {
            anchors.fill: parent
            opacity: 0.2
            color: "red"
        }
    }
    Component.onDestruction: {
        Singleton.toggleEditor(null)
        Singleton.model.highlightedGroup = -1
    }
}
