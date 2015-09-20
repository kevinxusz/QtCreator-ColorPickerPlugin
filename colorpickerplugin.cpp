#include "colorpickerplugin.h"

// Qt includes
#include <QMenu>

// QtCreator includes
#include <extensionsystem/pluginmanager.h>

#include <coreplugin/actionmanager/actioncontainer.h>
#include <coreplugin/actionmanager/actionmanager.h>
#include <coreplugin/editormanager/editormanager.h>
#include <coreplugin/editormanager/ieditor.h>

#include <texteditor/texteditor.h>

// Plugin includes
#include "colorpickerconstants.h"
#include "colorwatcher.h"

using namespace Core;
using namespace TextEditor;

namespace ColorPicker {
namespace Internal {


////////////////////////// ColorPickerPlugin //////////////////////////

ColorPickerPlugin::ColorPickerPlugin() :
    m_colorWatcher(new ColorWatcher(this))
{
}

bool ColorPickerPlugin::initialize(const QStringList & /* arguments */, QString * /* errorMessage */)
{
    // Register the plugin actions
    ActionContainer *toolsContainer = ActionManager::actionContainer(Core::Constants::M_TOOLS);

    ActionContainer *myContainer = ActionManager::createMenu("ColorPicker");
    QMenu *myMenu = myContainer->menu();
    myMenu->setTitle(tr("&ColorPicker"));
    myMenu->setEnabled(true);

    QAction *triggerColorEditAction = new QAction(tr("Trigger Color Edit"), this);
    Command *command = ActionManager::registerAction(triggerColorEditAction,
                                                     Constants::TRIGGER_COLOR_EDIT);
    command->setDefaultKeySequence(QKeySequence(tr("Ctrl+Alt+C")));

    myContainer->addAction(command);

    connect(triggerColorEditAction, &QAction::triggered,
            this, &ColorPickerPlugin::onColorEditTriggered);

    toolsContainer->addMenu(myContainer);

    return true;
}

void ColorPickerPlugin::extensionsInitialized()
{
}

void ColorPickerPlugin::onColorEditTriggered()
{
    IEditor *currentEditor = EditorManager::instance()->currentEditor();
    if (!currentEditor)
        return;

    TextEditorWidget *editorWidget = qobject_cast<TextEditorWidget *>(currentEditor->widget());

    if (editorWidget)
        m_colorWatcher->processCurrentTextCursor(editorWidget);
}


} // namespace Internal
} // namespace ColorPicker
