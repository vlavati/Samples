import QtQuick 2.0
import QtQuick.Controls 1.4
import com.mycompany.qmlapp 1.0

Item {
    id: products
    property CProductsViewModel viewModel
    Component.onCompleted: viewModel = g_factory.get("products", products)

    Text {
        text: qsTr("Products: ") + viewModel.str
        anchors.centerIn: parent
        Component.onCompleted: console.log("Creating products")
    }

    Button {
        anchors {
            bottom: parent.bottom
            right: parent.right
        }
        text: qsTr("Edit")
        onClicked: stack.push(Qt.resolvedUrl("Edit.qml"))
    }
}
