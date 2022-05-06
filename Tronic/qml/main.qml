import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0
import "Singleton.js" as Singleton

ApplicationWindow {
    title: qsTr("Tronic")
    width: 1024
    height: 500
    visible: true

    ScenarioStaticModel {
        id: scenarioStaticModel
        Component.onCompleted: Singleton.model = scenarioStaticModel
        editorsView: editorsView
    }

    ColumnLayout {
        anchors.fill: parent
        GroupView {
            id: groupView
            Layout.fillWidth: true
            Layout.fillHeight: true
            model: scenarioStaticModel
        }
        RowLayout {
            CueManager {
                id: cueManager
                Layout.preferredWidth: 300
                Layout.preferredHeight: 200
                model: scenarioStaticModel
            }
            EditorsView {
                id: editorsView
                Layout.fillWidth: true
                Layout.preferredHeight: 200
                //editor: scenarioStaticModel.editor
            }
        }
        StatusView {
            id: statusView
        }
    }
}
