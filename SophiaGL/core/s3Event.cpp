#include <core/s3Event.h>
#include <core/log/s3Log.h>
#include <app/s3Utils.h>

s3MouseEvent::s3MouseEvent(s3MouseType type, s3MouseTriggerType triggerType, int x, int y, int offsetX, int offsetY, float scroll, bool control, bool shift, bool alt)
    : type(type), triggerType(triggerType), x(x), y(y), offsetX(offsetX), offsetY(offsetY), scroll(scroll), control(control), shift(shift), alt(alt)
{}

void s3MouseEvent::print() const
{
    s3Log::debug("MouseType: %s, TriggerType: %s, X / Y / offsetX / offsetY: %d / %d / %d / %d, Scroll: %f, Control / Shift / Alt: %d / %d / %d\n",
                 s3EnumUtil(s3MouseType).toString(type).c_str(), 
                 s3EnumUtil(s3MouseTriggerType).toString(triggerType).c_str(),
                 x, y, offsetX, offsetY,
                 scroll,
                 control, shift, alt);
}

s3KeyEvent::s3KeyEvent(s3KeyType keyType, s3KeyTriggerType triggerType, std::string key, bool control, bool shift, bool alt)
    : keyType(keyType), triggerType(triggerType), key(key), control(control), shift(shift), alt(alt)
{
}

void s3KeyEvent::print() const
{
    s3Log::debug("KeyType: %s, TriggerType: %s, Key: %s, Control / Shift / Alt: %d / %d / %d\n", 
                 s3EnumUtil(s3KeyType).toString(keyType).c_str(),
                 s3EnumUtil(s3KeyTriggerType).toString(triggerType).c_str(),
                 key.c_str(), 
                 control, shift, alt);
}
