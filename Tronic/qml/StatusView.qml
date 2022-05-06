import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0

RowLayout {
    id: statusView
    TextField {
        text: "Show Name"
        readOnly: true
    }
    TextField {
        text: "Logged User"
        readOnly: true
    }
    TextField {
        text: "Drive status"
        readOnly: true
    }
    Label {
        Layout.fillWidth: true
    }
}
