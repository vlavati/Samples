import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0

TableView {
    id: cueView
    //implicitWidth: parent.width

    //    TableViewColumn {
    //        width: cueView.width*0.1
    //        delegate: Component {
    //            Button {
    //                anchors.fill: parent
    //                opacity: (model.get(styleData.row).cueId===-1)? 1.0: 0.0
    //                text: "+"
    //            }
    //        }
    //    }
    TableViewColumn {
        title: qsTr("Id")
        width: cueView.width * 0.1
        role: "cueId"
    }
    TableViewColumn {
        title: qsTr("Pos")
        width: cueView.width * 0.1
        role: "cuePos"
    }
    TableViewColumn {
        title: qsTr("Name")
        width: cueView.width * 0.7
        role: "cueName"
    }
    onCurrentRowChanged: cueView.model.selectedCue = currentRow
}
