import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0
import "Singleton.js" as Singleton
import "GroupView.js" as GroupView

GroupBox {
    id: groupView
    property var model: null
    title: qsTr("Groups")
    property var editorNew: {
        return {
            id: 2,
            selectedCue: -1
        }
    }
    ColumnLayout {
        anchors.fill: parent
        RowLayout {
            Button {
                text: "Add group"
                enabled: (groupView.model.selectedCue === -1) ? false : true
                onClicked: GroupView.append(groupView, editorNew)
            }
            Button {
                text: qsTr("Delete")
                enabled: (groupView.model.selectedGroup === -1) ? false : true
                onClicked: GroupView.remove(groupView)
            }
            TextField {
                text: groupView.model.selectedGroup
            }
        }
        ScrollView {
            flickableItem.interactive: true
            Layout.fillHeight: true
            Layout.fillWidth: true
            ListView {
                focus: true
                id: listOfGroups
                anchors.fill: parent
                model: {
                    if (groupView.model.selectedCue === -1)
                        return null
                    return groupView.model.get(
                                groupView.model.selectedCue).groups
                }
                delegate: SingleGroupView {
                }
            }
        }
    }
}
