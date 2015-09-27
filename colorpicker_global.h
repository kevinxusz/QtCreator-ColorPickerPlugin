#ifndef COLORPICKER_GLOBAL
#define COLORPICKER_GLOBAL

#include <QColor>
#include <QMetaType>

namespace ColorPicker {
namespace Internal {

enum ColorType
{
    RgbType,
    RgbaType,
    HsvType,
    HsvaType,
    HslType,
    HslaType,
    HexType,
    QmlRgbaType,
    QmlHslaType,
    Vec3Type,
    Vec4Type
};

} // namespace Internal
} // namespace ColorPicker

Q_DECLARE_METATYPE(ColorPicker::Internal::ColorType)

#endif // COLORPICKER_GLOBAL

