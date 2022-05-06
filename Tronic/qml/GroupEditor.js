Qt.include("Singleton.js")

function append(groupEditor)
{
    var newGroup = {
        "groupName": groupEditor.name,
        "deadName": "Stage level",
        "groupMode": 0,
        "joystickColor": groupEditor.joysticksModel.get(groupEditor.joystickIndex).color,
        "joystickMaxSpeed": groupEditor.joystickMaxSpeed,
        "rampStart": groupEditor.rampStart,
        "rampStop": groupEditor.rampStop,
        "rampSame": groupEditor.rampSame,
        "drives": [ { driveId: -1 } ]
    };
    Singleton.model.get(groupEditor.editor.selectedCue).groups.append(newGroup);
    Singleton.toggleEditor(null);
}
