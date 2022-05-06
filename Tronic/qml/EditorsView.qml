import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0
import "Singleton.js" as Singleton
import "DriveEditor.js" as DriveEditor

Item {
    id: editorsView
    signal activate
    onActivate: {
        if (active) {
            editorLoader.sourceComponent = null
        }
        if (Singleton.model === null)
            return
        var editor = Singleton.model.editor
        if (editor === null || editor === undefined)
            return
        if (editor.id === 1) {
            editorLoader.sourceComponent = driveEditor
        }
        if (editor.id === 2) {
            editorLoader.sourceComponent = groupEditor
        }
    }

    Component {
        id: driveEditor
        DriveEditor {
        }
    }
    Component {
        id: groupEditor
        GroupEditor {
        }
    }

    GroupBox {
        anchors.fill: parent
        title: qsTr("Editor")
        Loader {
            id: editorLoader
            anchors.fill: parent
        }
    }
}
