#ifndef COLORPICKERPLUGIN_H
#define COLORPICKERPLUGIN_H

#include <extensionsystem/iplugin.h>

#include "colorutilities.h"

namespace Core {
class IEditor;
}

namespace ColorPicker {
namespace Internal {

class ColorPickerPluginImpl;
class GeneralSettings;

class ColorPickerPlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QtCreatorPlugin"
                      FILE "ColorPicker.json")

public:
    ColorPickerPlugin();
    ~ColorPickerPlugin();

    virtual bool initialize(const QStringList &arguments,
                            QString *errorMessage);

    virtual void extensionsInitialized();

private slots:
    void onColorEditTriggered();
    void onGeneralSettingsChanged(const GeneralSettings &gs);
    void onColorSelected(const QColor &color, ColorFormat format);
    void onColorChanged(const QColor &color);
    void onOutputFormatChanged(ColorFormat format);

#if defined(WITH_TESTS)
    // The following tests expect that no projects are loaded on start-up.
    void test_addAndReplaceColor();
#endif

private:
    friend class ColorPickerPluginImpl;
    QScopedPointer<ColorPickerPluginImpl> d;
};

} // namespace Internal
} // namespace ColorPicker

#endif // COLORPICKERPLUGIN_H
