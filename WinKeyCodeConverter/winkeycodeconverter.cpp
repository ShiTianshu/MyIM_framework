#include "winkeycodeconverter.h"
#include "windows.h"

static const int keyMap[256] = {
    0,0,0,0,0,0,0,0,Qt::Key_Backspace,Qt::Key_Tab,
    0,0,Qt::Key_Clear,Qt::Key_Return,0,0,Qt::Key_Shift,Qt::Key_Control,Qt::Key_Menu,Qt::Key_Pause,
    Qt::Key_CapsLock,0,0,0,0,0,0,Qt::Key_Escape,0,0,
    0,0,Qt::Key_Space,Qt::Key_PageUp,Qt::Key_PageDown,Qt::Key_End,Qt::Key_Home,Qt::Key_Left,Qt::Key_Up,Qt::Key_Right,
    Qt::Key_Down,0,Qt::Key_Print,0,0,Qt::Key_Insert,Qt::Key_Delete,Qt::Key_Help,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,Qt::Key_A,Qt::Key_B,Qt::Key_C,Qt::Key_D,Qt::Key_E,
    Qt::Key_F,Qt::Key_G,Qt::Key_H,Qt::Key_I,Qt::Key_J,Qt::Key_K,Qt::Key_L,Qt::Key_M,Qt::Key_N,Qt::Key_O,
    Qt::Key_P,Qt::Key_Q,Qt::Key_R,Qt::Key_S,Qt::Key_T,Qt::Key_U,Qt::Key_V,Qt::Key_W,Qt::Key_X,Qt::Key_Y,
    Qt::Key_Z,Qt::Key_Meta,Qt::Key_Meta,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,Qt::Key_F1,Qt::Key_F2,Qt::Key_F3,Qt::Key_F4,Qt::Key_F5,Qt::Key_F6,Qt::Key_F7,Qt::Key_F8,
    Qt::Key_F9,Qt::Key_F10,Qt::Key_F11,Qt::Key_F12,Qt::Key_F13,Qt::Key_F14,Qt::Key_F15,Qt::Key_F16,Qt::Key_F17,Qt::Key_F18,
    Qt::Key_F19,Qt::Key_F20,Qt::Key_F21,Qt::Key_F22,Qt::Key_F23,Qt::Key_F24,0,0,0,0,
    0,0,0,0,Qt::Key_NumLock,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    Qt::Key_Shift,Qt::Key_Shift,Qt::Key_Control,Qt::Key_Control,Qt::Key_Menu,Qt::Key_Menu,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,Qt::Key_Semicolon,Qt::Key_Plus,Qt::Key_Comma,Qt::Key_Minus,
    Qt::Key_Period,Qt::Key_Slash,Qt::Key_QuoteLeft,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,Qt::Key_BracketLeft,
    Qt::Key_Backslash,Qt::Key_BracketRight,Qt::Key_Apostrophe,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0
};

WinKeyCodeConverter* GetInstance(QString modId)
{
    return new WinKeyCodeConverter(modId);
}

WinKeyCodeConverter::WinKeyCodeConverter(QString modId):
    IProc(modId)
{
    this->name = "WinKeyCodeConverter";
}

WinKeyCodeConverter::~WinKeyCodeConverter()
{

}

/**
 * @brief WinKeyCodeConverter::execute
 * 把vkCode转化成QtKey，如果该键不在输入法中使用，则keycode=0, accepted=false
 * 否则keycode为转化之后的值，accepted由后续的处理器决定。
 * @param pic
 */
void WinKeyCodeConverter::execute(InputContext *pic)
{
    uint keycode = pic->keycode;
    if (keycode > 256)
    {
        throw QString ("无效的键值");
    }
    int key = keyMap[keycode];
    if (!key)
    {
        // 不需要的按键
        pic->accepted = false;
        pic->key = 0;
    }
    else
    {
        pic->accepted = true;
        pic->key = key;
    }
    qDebug() << (int)pic->key;
}

void WinKeyCodeConverter::initialize(const QMap<QString, QVariant> &)
{

}
