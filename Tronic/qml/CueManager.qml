import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0

GroupBox {
    id: cueManager
    property int buttonWidth: 40
    property var model: null
    title: qsTr("Cues")
    RowLayout {
        anchors.fill: parent
        ColumnLayout {
            Button {
                text: qsTr("New")
                implicitWidth: buttonWidth
                enabled: (cueManager.model.selectedCue === -1) ? false : true
            }
            Button {
                text: qsTr("Up")
                implicitWidth: buttonWidth
                enabled: (cueManager.model.selectedCue === -1) ? false : true
            }
            Button {
                text: qsTr("Down")
                implicitWidth: buttonWidth
                enabled: (cueManager.model.selectedCue === -1) ? false : true
            }
            Button {
                text: qsTr("Save")
                implicitWidth: buttonWidth
                enabled: (cueManager.model.selectedCue === -1) ? false : true
            }
            Button {
                text: qsTr("Delete")
                implicitWidth: buttonWidth
                enabled: (cueManager.model.selectedCue === -1) ? false : true
            }
        }
        CueView {
            Layout.fillWidth: true
            id: cueView
            model: cueManager.model
        }
    }
}
