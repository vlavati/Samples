import QtQuick 2.6
import QtQuick.Window 2.2
import com.mycompany.qmlasync 1.0

Window {
    visible: true
    property CViewModel viewModel: CViewModel {
        onStarted: animation.start()
        onStopped: animation.stop()
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            Qt.quit();
        }
    }

    Text {
        id: text
        text: qsTr("Hello World")
        anchors.centerIn: parent
        transform: Rotation {
            id: rotation
            angle: 0
            origin.x: text.width/2
            origin.y: text.height/2
        }
        MouseArea {
            anchors.centerIn: parent
            width: Math.max(parent.width, parent.height)
            height: width
            onClicked: viewModel.startAsync()
        }

        SequentialAnimation {
            id: animation
            loops: Animation.Infinite
            RotationAnimation {
                direction: RotationAnimation.Clockwise
                target: rotation
                property: "angle"
                to: 180
            }
            RotationAnimation {
                direction: RotationAnimation.Clockwise
                target: rotation
                property: "angle"
                to: 0
            }
        }
    }
}
