Qt.include("Singleton.js")

function append(groupView)
{
    groupView.editorNew.selectedCue = Singleton.model.selectedCue;
    Singleton.toggleEditor(groupView.editorNew);
}

function remove(groupView)
{
    var selectedIndex = groupView.model.selectedGroup;
    groupView.model.selectedGroup = -1;
    groupView.model.get(groupView.model.selectedCue).groups.remove(selectedIndex);
}
