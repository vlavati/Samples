import QtQuick 2.0
import "Singleton.js" as Singleton

ListModel {
    id: scenarioStaticModel
    property int selectedCue: -1
    property int selectedGroup: -1
    property int highlightedGroup: -1
    property var drives: DrivesStaticModel {
    }
    property var editor: null
    property var editorsView: null
    onSelectedCueChanged: {
        Singleton.toggleEditor(null)
        selectedGroup = -1
    }
    onSelectedGroupChanged: {
        console.log("selectedGroup=", selectedGroup)
    }
    onEditorChanged: if (editorsView !== null)
                         editorsView.activate()
    ListElement {
        cueId: 1
        cuePos: 1
        cueName: "First Cue"
        groups: [
            ListElement {
                groupName: "Stone wall"
                deadName: "Stage level"
                groupMode: 1
                joystickColor: "blue"
                joystickMaxSpeed: 0.8
                rampStart: 1.5
                rampStop: 1.8
                rampSame: false
                drives: [
                    ListElement {
                        isOn: true
                        isRelative: false
                        isFreerun: true
                        driveId: 101
                        driveName: "spare1"
                        driveState: "ok"
                        driveStateText: "WfDM"
                        currentPosition: 20000
                        endPosition: 0
                        endPositionFreeRun: true
                        movingDirection: 0 //0 - up, 1 - down, 2 - on top, 3 - on bottom
                    },
                    ListElement {
                        isOn: true
                        isRelative: false
                        isFreerun: true
                        driveId: 101
                        driveName: "spare1"
                        driveState: "ok"
                        driveStateText: "WfDM"
                        currentPosition: 20000
                        endPosition: 0
                        endPositionFreeRun: true
                        movingDirection: 0 //0 - up, 1 - down, 2 - on top, 3 - on bottom
                    },
                    ListElement {
                        isOn: true
                        isRelative: false
                        isFreerun: true
                        driveId: 101
                        driveName: "spare1"
                        driveState: "ok"
                        driveStateText: "WfDM"
                        currentPosition: 20000
                        endPosition: 0
                        endPositionFreeRun: true
                        movingDirection: 0 //0 - up, 1 - down, 2 - on top, 3 - on bottom
                    },
                    ListElement {
                        isOn: true
                        isRelative: false
                        isFreerun: true
                        driveId: 101
                        driveName: "spare1"
                        driveState: "ok"
                        driveStateText: "WfDM"
                        currentPosition: 20000
                        endPosition: 0
                        endPositionFreeRun: true
                        movingDirection: 0 //0 - up, 1 - down, 2 - on top, 3 - on bottom
                    },
                    ListElement {
                        isOn: true
                        isRelative: false
                        isFreerun: true
                        driveId: 101
                        driveName: "spare1"
                        driveState: "ok"
                        driveStateText: "WfDM"
                        currentPosition: 20000
                        endPosition: 0
                        endPositionFreeRun: true
                        movingDirection: 0 //0 - up, 1 - down, 2 - on top, 3 - on bottom
                    },
                    ListElement {
                        isOn: true
                        isRelative: false
                        isFreerun: true
                        driveId: 101
                        driveName: "spare1"
                        driveState: "ok"
                        driveStateText: "WfDM"
                        currentPosition: 20000
                        endPosition: 0
                        endPositionFreeRun: true
                        movingDirection: 0 //0 - up, 1 - down, 2 - on top, 3 - on bottom
                    },
                    ListElement {
                        isOn: true
                        isRelative: false
                        isFreerun: true
                        driveId: 101
                        driveName: "spare1"
                        driveState: "ok"
                        driveStateText: "WfDM"
                        currentPosition: 20000
                        endPosition: 0
                        endPositionFreeRun: true
                        movingDirection: 0 //0 - up, 1 - down, 2 - on top, 3 - on bottom
                    },
                    ListElement {
                        isOn: true
                        isRelative: false
                        isFreerun: true
                        driveId: 101
                        driveName: "spare1"
                        driveState: "ok"
                        driveStateText: "WfDM"
                        currentPosition: 20000
                        endPosition: 0
                        endPositionFreeRun: true
                        movingDirection: 0 //0 - up, 1 - down, 2 - on top, 3 - on bottom
                    },
                    ListElement {
                        isOn: true
                        isRelative: false
                        isFreerun: true
                        driveId: 101
                        driveName: "spare1"
                        driveState: "ok"
                        driveStateText: "WfDM"
                        currentPosition: 20000
                        endPosition: 0
                        endPositionFreeRun: true
                        movingDirection: 0 //0 - up, 1 - down, 2 - on top, 3 - on bottom
                    },
                    ListElement {
                        isOn: true
                        isRelative: false
                        isFreerun: true
                        driveId: 101
                        driveName: "spare1"
                        driveState: "ok"
                        driveStateText: "WfDM"
                        currentPosition: 20000
                        endPosition: 0
                        endPositionFreeRun: true
                        movingDirection: 0 //0 - up, 1 - down, 2 - on top, 3 - on bottom
                    },
                    ListElement {
                        isOn: true
                        isRelative: false
                        isFreerun: true
                        driveId: 101
                        driveName: "spare1"
                        driveState: "ok"
                        driveStateText: "WfDM"
                        currentPosition: 20000
                        endPosition: 0
                        endPositionFreeRun: true
                        movingDirection: 0 //0 - up, 1 - down, 2 - on top, 3 - on bottom
                    },
                    ListElement {
                        isOn: true
                        isRelative: false
                        isFreerun: true
                        driveId: 101
                        driveName: "spare1"
                        driveState: "ok"
                        driveStateText: "WfDM"
                        currentPosition: 20000
                        endPosition: 0
                        endPositionFreeRun: true
                        movingDirection: 0 //0 - up, 1 - down, 2 - on top, 3 - on bottom
                    },
                    ListElement {
                        isOn: true
                        isRelative: false
                        isFreerun: true
                        driveId: 101
                        driveName: "spare1"
                        driveState: "ok"
                        driveStateText: "WfDM"
                        currentPosition: 20000
                        endPosition: 0
                        endPositionFreeRun: true
                        movingDirection: 0 //0 - up, 1 - down, 2 - on top, 3 - on bottom
                    },
                    ListElement {
                        isOn: true
                        isRelative: false
                        isFreerun: true
                        driveId: 101
                        driveName: "spare2"
                        driveState: "ok"
                        driveStateText: "WfDM"
                        currentPosition: 24000
                        endPosition: 10000
                        endPositionFreeRun: false
                        movingDirection: 2 //0 - up, 1 - down, 2 - on top, 3 - on bottom
                    }
                ]
            },
            ListElement {
                groupName: "Stone wall2"
                deadName: "Stage level"
                groupMode: 2
                joystickColor: "green"
                joystickMaxSpeed: 0.3
                rampStart: 1.5
                rampStop: 1.8
                rampSame: true
                drives: [
                    ListElement {
                        isOn: true
                        isRelative: false
                        isFreerun: true
                        driveId: 101
                        driveName: "spare3"
                        driveState: "ok"
                        driveStateText: "WfDM"
                        currentPosition: 12000
                        endPosition: 0
                        endPositionFreeRun: false
                        movingDirection: 3 //0 - up, 1 - down, 2 - on top, 3 - on bottom
                    },
                    ListElement {
                        isOn: true
                        isRelative: false
                        isFreerun: true
                        driveId: 132
                        driveName: "spare4"
                        driveState: "bad"
                        driveStateText: "Unknown"
                        currentPosition: 24000
                        endPosition: 3000
                        endPositionFreeRun: true
                        movingDirection: 1 //0 - up, 1 - down, 2 - on top, 3 - on bottom
                    }
                ]
            },
            ListElement {
                groupName: "Stone wall3"
                deadName: "Stage level"
                groupMode: 1
                joystickColor: "blue"
                joystickMaxSpeed: 0.8
                rampStart: 1.5
                rampStop: 1.8
                rampSame: false
                drives: [
                    ListElement {
                        isOn: true
                        isRelative: false
                        isFreerun: true
                        driveId: -1
                        driveName: "spare1"
                        driveState: "ok"
                        driveStateText: "WfDM"
                        currentPosition: 20000
                        endPosition: 0
                        endPositionFreeRun: true
                        movingDirection: 0 //0 - up, 1 - down, 2 - on top, 3 - on bottom
                    }
                ]
            },
            ListElement {
                groupName: "Stone wall4"
                deadName: "Stage level"
                groupMode: 1
                joystickColor: "blue"
                joystickMaxSpeed: 0.8
                rampStart: 1.5
                rampStop: 1.8
                rampSame: false
                drives: [
                    ListElement {
                        isOn: true
                        isRelative: false
                        isFreerun: true
                        driveId: 101
                        driveName: "spare1"
                        driveState: "ok"
                        driveStateText: "WfDM"
                        currentPosition: 20000
                        endPosition: 0
                        endPositionFreeRun: true
                        movingDirection: 0 //0 - up, 1 - down, 2 - on top, 3 - on bottom
                    }
                ]
            },
            ListElement {
                groupName: "Stone wall5"
                deadName: "Stage level"
                groupMode: 1
                joystickColor: "blue"
                joystickMaxSpeed: 0.8
                rampStart: 1.5
                rampStop: 1.8
                rampSame: false
                drives: [
                    ListElement {
                        isOn: true
                        isRelative: false
                        isFreerun: true
                        driveId: 101
                        driveName: "spare1"
                        driveState: "ok"
                        driveStateText: "WfDM"
                        currentPosition: 20000
                        endPosition: 0
                        endPositionFreeRun: true
                        movingDirection: 0 //0 - up, 1 - down, 2 - on top, 3 - on bottom
                    }
                ]
            },
            ListElement {
                groupName: "Stone wall6"
                deadName: "Stage level"
                groupMode: 1
                joystickColor: "blue"
                joystickMaxSpeed: 0.8
                rampStart: 1.5
                rampStop: 1.8
                rampSame: false
                drives: [
                    ListElement {
                        isOn: true
                        isRelative: false
                        isFreerun: true
                        driveId: 101
                        driveName: "spare1"
                        driveState: "ok"
                        driveStateText: "WfDM"
                        currentPosition: 20000
                        endPosition: 0
                        endPositionFreeRun: true
                        movingDirection: 0 //0 - up, 1 - down, 2 - on top, 3 - on bottom
                    }
                ]
            },
            ListElement {
                groupName: "Stone wall7"
                deadName: "Stage level"
                groupMode: 1
                joystickColor: "blue"
                joystickMaxSpeed: 0.8
                rampStart: 1.5
                rampStop: 1.8
                rampSame: false
                drives: [
                    ListElement {
                        isOn: true
                        isRelative: false
                        isFreerun: true
                        driveId: 101
                        driveName: "spare1"
                        driveState: "ok"
                        driveStateText: "WfDM"
                        currentPosition: 20000
                        endPosition: 0
                        endPositionFreeRun: true
                        movingDirection: 0 //0 - up, 1 - down, 2 - on top, 3 - on bottom
                    }
                ]
            },
            ListElement {
                groupName: "Stone wall8"
                deadName: "Stage level"
                groupMode: 1
                joystickColor: "blue"
                joystickMaxSpeed: 0.8
                rampStart: 1.5
                rampStop: 1.8
                rampSame: false
                drives: [
                    ListElement {
                        isOn: true
                        isRelative: false
                        isFreerun: true
                        driveId: 101
                        driveName: "spare1"
                        driveState: "ok"
                        driveStateText: "WfDM"
                        currentPosition: 20000
                        endPosition: 0
                        endPositionFreeRun: true
                        movingDirection: 0 //0 - up, 1 - down, 2 - on top, 3 - on bottom
                    }
                ]
            }
        ]
    }
    ListElement {
        cueId: 2
        cuePos: 2
        cueName: "Second Cue"
        groups: []
    }
}
