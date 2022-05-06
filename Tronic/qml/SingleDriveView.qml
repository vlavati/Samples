import QtQuick 2.0
import QtQuick.Controls 1.0

import "Singleton.js" as Singleton

Button {
    property int groupIndex: -1
    property var editor: {
        return {
            id: 1,
            driveIndex: index,
            selectedGroup: groupIndex,
            selectedCue: Singleton.model.selectedCue
        }
    }
    text: (driveId === -1) ? "Add drive" : Singleton.getDrive(driveId).driveName
    onClicked: Singleton.toggleEditor(editor)
}
