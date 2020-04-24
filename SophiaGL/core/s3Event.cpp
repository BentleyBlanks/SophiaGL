#include <core/s3Event.h>
#include <core/log/s3Log.h>
#include <app/s3Utils.h>

s3MouseEvent::s3MouseEvent(s3ButtonType type, s3TriggerType triggerType, int x, int y, int offsetX, int offsetY, float scroll, bool control, bool shift, bool alt)
    : type(type), triggerType(triggerType), x(x), y(y), offsetX(offsetX), offsetY(offsetY), scroll(scroll), control(control), shift(shift), alt(alt)
{}

void s3MouseEvent::print() const
{
    //s3Log::debug("ButtonType: %s, TriggerType: %s, X / Y / offsetX / offsetY: %d / %d / %d / %d, Scroll: %f, Control / Shift / Alt: %d / %d / %d\n",
    //             s3EnumUtil(s3ButtonType).toString(type).c_str(), 
    //             s3EnumUtil(s3TriggerType).toString(triggerType).c_str(),
    //             x, y, offsetX, offsetY,
    //             scroll,
    //             control, shift, alt);
}

s3KeyEvent::s3KeyEvent(s3CodeType keyType, s3TriggerType triggerType, unsigned int key, bool control, bool shift, bool alt)
    : keyType(keyType), triggerType(triggerType), key(key), control(control), shift(shift), alt(alt)
{
}

void s3KeyEvent::print() const
{
    //s3Log::debug("CodeType: %s, TriggerType: %s, Key: %d, Control / Shift / Alt: %d / %d / %d\n", 
    //             s3EnumUtil(s3CodeType).toString(keyType).c_str(),
    //             s3EnumUtil(s3TriggerType).toString(triggerType).c_str(),
    //             key, 
    //             control, shift, alt);
}
