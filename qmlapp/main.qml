import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import com.mycompany.qmlapp 1.0

Window {
    visible: true

    Button {
        anchors {
            top: parent.top
            right: parent.right
        }
        text: qsTr("Quit")
        onClicked: Qt.quit();
    }


    StackView {
        id: stack
        initialItem: Qt.resolvedUrl("Products.qml")
        anchors.fill: parent
    }
}
