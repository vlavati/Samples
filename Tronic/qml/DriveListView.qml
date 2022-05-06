import QtQuick 2.0
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0

ListView {
    id: driveListView
    property int groupIndex: -1
    clip:true
    orientation: Qt.Horizontal
    delegate: SingleDriveView {
        height: parent.height
        width: parent.height
        groupIndex: driveListView.groupIndex
    }
}
