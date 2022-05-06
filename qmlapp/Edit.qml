import QtQuick 2.0
import QtQuick.Controls 1.4
import com.mycompany.qmlapp 1.0

Item {
    id: edit
    property CEditViewModel viewModel
    Component.onCompleted: viewModel = g_factory.get("edit", edit)

    Text {
        text: qsTr("Editor: ") + viewModel.str
        anchors.centerIn: parent
        Component.onCompleted: console.log("Creating editor")
    }

    Button {
        anchors {
            bottom: parent.bottom
            left: parent.left
        }
        text: qsTr("Back")
        onClicked: stack.pop()
    }
}
