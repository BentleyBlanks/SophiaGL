#include <core/s3Event.h>
#include <core/log/s3Log.h>
#include <app/s3Utils.h>

s3MouseEvent::s3MouseEvent(s3ButtonType type, s3TriggerType triggerType, int x, int y, int offsetX, int offsetY, float scroll, bool control, bool shift)
    : type(type), triggerType(triggerType), x(x), y(y), offsetX(offsetX), offsetY(offsetY), scroll(scroll), control(control), shift(shift)
{}

void s3MouseEvent::print() const
{

}

//void s3MouseEvent::print(int state) const
//{
//    s3Log::debug("%s type: %s, pos: [%d, %d], offset: [%d, %d], scroll: %.1f, control: %s, shift: %s\n",
//        s3MouseStateToString((s3MouseState) state).c_str(), 
//        s3MouseTypeToString(type).c_str(), x, y, offsetX, offsetY, scroll, s3ToString(control).c_str(), s3ToString(shift).c_str());
//}

//void s3KeyEvent::print(int state) const
//{
//    if(key == 0)
//        s3Log::debug("%s code: %s, key: , control: %s, shift: %s, alt: %s\n",
//        s3KeyStateToString((s3KeyState) state).c_str(), 
//        s3KeyTypeToString(keyType).c_str(), s3ToString(control).c_str(), s3ToString(shift).c_str(), s3ToString(alt).c_str());
//    else
//        s3Log::debug("%s code: %s, key: %c, control: %s, shift: %s, alt: %s\n", 
//        s3KeyStateToString((s3KeyState)state).c_str(), 
//        s3KeyTypeToString(keyType).c_str(), (unsigned char) key, s3ToString(control).c_str(), s3ToString(shift).c_str(), s3ToString(alt).c_str());
//}

s3KeyEvent::s3KeyEvent(s3KeyType keyType, s3TriggerType triggerType, unsigned int key, bool control, bool shift, bool alt)
    : keyType(keyType), triggerType(triggerType), key(key), control(control), shift(shift), alt(alt)
{

}

void s3KeyEvent::print() const
{

}