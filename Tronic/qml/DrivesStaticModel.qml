import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0

ListModel {
    id: drivesStaticModel
    ListElement {
        driveId: 101
        driveName: "dviglo1"
        driveState: "ok"
        driveStateText: "WfDM"
        currentPosition: 20000
        endPosition: 0
        endPositionFreeRun: true
        movingDirection: 0 //0 - up, 1 - down, 2 - on top, 3 - on bottom
    }
    ListElement {
        driveId: 214
        driveName: "dviglo2"
        driveState: "ok"
        driveStateText: "WfDM"
        currentPosition: 20000
        endPosition: 0
        endPositionFreeRun: true
        movingDirection: 0 //0 - up, 1 - down, 2 - on top, 3 - on bottom
    }
    ListElement {
        driveId: 132
        driveName: "dviglo3"
        driveState: "ok"
        driveStateText: "WfDM"
        currentPosition: 20000
        endPosition: 0
        endPositionFreeRun: true
        movingDirection: 0 //0 - up, 1 - down, 2 - on top, 3 - on bottom
    }
}
