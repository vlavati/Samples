.pragma library

var model = null;

function getDrive(id) {
    for(var d = 0; d < model.drives.count; d++)
    {
       if (model.drives.get(d).driveId===id)
           return model.drives.get(d);
    }
    return {"driveName":"unknown"};
}

function toggleEditor(editor) {
    if (!isEqualEditor(model.editor ,editor))
        model.editor = editor;
    else
        model.editor = null;
}

function getEditedDrive(editor)
{
    return model.get(editor.selectedCue).groups.get(editor.selectedGroup).drives.get(editor.driveIndex);
}

function isEqualEditor(editor1, editor2)
{
    if (editor1 === editor2)
        return true;
    if (editor1 === null || editor2 === null)
        return false;
    if (editor1.id === editor2.id)
    {
        if (editor1.id===1)
            return isEqualDriveEditor(editor1, editor2);
    }
    return false;
}

function isEqualDriveEditor(editor1, editor2)
{
    if (editor1.driveIndex !== editor2.driveIndex)
        return false;
    if (editor1.selectedGroup !== editor2.selectedGroup)
        return false;
    if (editor1.selectedCue !== editor2.selectedCue)
        return false;
    return true;
}
