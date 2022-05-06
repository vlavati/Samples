Qt.include("Singleton.js")

var unknownDriveIndex = 0;

function initialize(driveEditor) {
    console.log("initialize", driveEditor.editor.driveIndex)
    driveEditor.drivesModel.clear();
    var index = unknownDriveIndex;
    driveEditor.drivesModel.append({
                                     text: "",
                                     id: -1
                                 });
    for(var d=0; d<Singleton.model.drives.count; d++)
    {
        driveEditor.drivesModel.append({
                                         text:Singleton.model.drives.get(d).driveName,
                                         id:Singleton.model.drives.get(d).driveId
                                     });
        if (Singleton.getEditedDrive(driveEditor.editor).driveId === Singleton.model.drives.get(d).driveId)
            index = d+1;
    }
    driveEditor.driveType = index;
    driveEditor.isOn = Singleton.getEditedDrive(driveEditor.editor).isOn;
    driveEditor.isRelative = Singleton.getEditedDrive(driveEditor.editor).isRelative;
    driveEditor.isFreerun = Singleton.getEditedDrive(driveEditor.editor).isFreerun;
    driveEditor.endPosition = Singleton.getEditedDrive(driveEditor.editor).endPosition;
    driveEditor.isNewDrive = (index==unknownDriveIndex)? true: false;
}

function set(driveEditor) {
    Singleton.getEditedDrive(driveEditor.editor).isOn = driveEditor.isOn;
    Singleton.getEditedDrive(driveEditor.editor).isRelative = driveEditor.isRelative;
    Singleton.getEditedDrive(driveEditor.editor).isFreerun = driveEditor.isFreerun;
    Singleton.getEditedDrive(driveEditor.editor).endPosition = driveEditor.endPosition;
}

function cancel(driveEditor)
{
    Singleton.toggleEditor(null);
}

function remove(driveEditor)
{
    Singleton.model.get(driveEditor.editor.selectedCue).groups.get(driveEditor.editor.selectedGroup).drives.remove(driveEditor.editor.driveIndex)
    Singleton.toggleEditor(null);
}

function teachIn(driveEditor)
{
    driveEditor.endPosition = Singleton.model.drives.get(driveEditor.driveType-1).currentPosition;
}

function append(driveEditor)
{
    var newDrive = {
        "isOn": driveEditor.isOn,
        "isRelative": driveEditor.isRelative,
        "isFreerun": driveEditor.isFreerun,
        "driveId": Singleton.model.drives.get(driveEditor.driveType-1).driveId,
        "driveName": "spare1",
        "driveState": "ok",
        "driveStateText": "WfDM",
        "currentPosition": 20000,
        "endPosition": driveEditor.endPosition,
        "endPositionFreeRun": true,
        "movingDirection": 0
    };
    Singleton.model.get(driveEditor.editor.selectedCue).groups.get(driveEditor.editor.selectedGroup).drives.insert(driveEditor.editor.driveIndex, newDrive);
    driveEditor.isNewDrive = false;
}
