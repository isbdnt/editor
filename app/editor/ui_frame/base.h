#pragma once

#include "../include.h"
#include "imgui.h"

class UIState;
class UIClass;
class UIFrame;

enum class DirectEnum {
    kU, kD, kL, kR, LENGTH
};

//  �ؼ��б�
enum class UITypeEnum {
    kTREE,                  //  ����
    kIMAGE,                 //  ͼƬ
    kBUTTON,                //  ��ť
    kLAYOUT,                //  ����
    kWINDOW,                //  ����
    kEDITBOX,               //  �༭��
    kTEXTBOX,               //  �ı���
    kCOMBOBOX,              //  ������
    kUICONVAS,              //  UI����
    kGLCONVAS,              //  GL����
};

//  �ؼ��б�
static const std::string WIDGET_TREE = "Tree";
static const std::string WIDGET_IMAGE = "Image";
static const std::string WIDGET_BUTTON = "Button";
static const std::string WIDGET_LAYOUT = "Layout";
static const std::string WIDGET_WINDOW = "Window";
static const std::string WIDGET_EDITBOX = "EditBox";
static const std::string WIDGET_TEXTBOX = "TextBox";
static const std::string WIDGET_ComboBox = "ComboBox";
static const std::string WIDGET_UICANVAS = "UICanvas";
static const std::string WIDGET_GLCANVAS = "GLCanvas";

//  �ؼ�״̬
enum class UIStateEnum {
    kDISABLED,              //  ����
    kNORMAL,                //  ����
    kOVER,                  //  ����
    kPRESSED,               //  ����
    kSELECTED_DISABLED,     //  ѡ�н�ֹ
    kSELECTED_NORMAL,       //  ѡ������
    kSELECTED_OVER,         //  ѡ������
    kSELECTED_PRESSED,      //  ѡ�а���
    LENGTH,
};

//  �ؼ�����
enum class UIAlignEnum {
    kDEFAULT,               //  ��������
    kSTRETCH,               //  ����
    kCENTER,                //  ����
    kLEFT_TOP,              //  ����ͣ��
    kLEFT_BOTTOM,           //  ����ͣ��
    kLEFT_VSTRETCH,         //  ��ͣ��,     ��ֱ����
    kLEFT_VCENTER,          //  ��ͣ��,     ��ֱ����
    kRIGHT_TOP,             //  ����ͣ��
    kRIGHT_BOTTOM,          //  ����ͣ��
    kRIGHT_VSTRETCH,        //  ��ͣ��,     ��ֱ����
    kRIGHT_VCENTER,         //  ��ͣ��,     ��ֱ����
    kHSTRETCH_TOP,          //  ��ͣ��,     ˮƽ����
    kHSTRETCH_BOTTOM,       //  ��ͣ��,     ˮƽ����
    kHSTRETCH_VSTRETCH,     //  ˮƽ����,   ��ֱ����
    kHSTRETCH_VCENTER,      //  ��ֱ����,   ˮƽ����
    kHCENTER_TOP,           //  ��ͣ��,     ˮƽ����
    kHCENTER_BOTTOM,        //  ��ͣ��,     ��ֱ����
    kHCENTER_VSTRETCH,      //  ˮƽ����,   ��ֱ����
    kHCENTER_VCENTER,       //  ˮƽ����,   ��ֱ����
    LENGTH,
};

//  �ַ���ת��������
inline bool S2B(const std::string & s) { return s == "ok"; }
inline int S2I(const std::string & s) { return std::stoi(s); }
inline float S2F(const std::string & s) { return std::stof(s); }

inline glm::vec2 S2V2(const std::string & s)
{
    auto arr = string_tool::Split(s, " ");
    ASSERT_LOG(arr.size() == 2, "Arr Length: {0}!", arr.size());
    return glm::vec2(S2F(arr.at(0)), S2F(arr.at(1)));
}

inline glm::vec3 S2V3(const std::string & s)
{
    auto arr = string_tool::Split(s, " ");
    ASSERT_LOG(arr.size() == 3, "Arr Length: {0}!", arr.size());
    return glm::vec3(S2F(arr.at(0)), S2F(arr.at(1)), S2F(arr.at(2)));
}

inline glm::vec3 S2V4(const std::string & s)
{
    auto arr = string_tool::Split(s, " ");
    ASSERT_LOG(arr.size() == 4, "Arr Length: {0}!", arr.size());
    return glm::vec4(S2F(arr.at(0)), S2F(arr.at(1)), S2F(arr.at(2)), S2F(arr.at(3)));
}

//  �Զ������� Get/Set
using CustomData = std::map<std::string, std::any>;

//  ��ȡ����
#define __REG_GET_DATA(T, K, def)                                          \
    inline const T & __GetData##K(const CustomData & data)                 \
    {                                                                      \
        static T tmp = def;                                                \
        auto it = data.find(#K);                                           \
        if (it == data.end()) return tmp;                                  \
        return std::any_cast<const T &>(it->second);                       \
    }

//  ��������
#define __REG_SET_DATA(T, K)                                               \
    inline void __SetData##K(CustomData & data, const T & val)             \
    {                                                                      \
        data[#K] = val;                                                    \
    }

__REG_GET_DATA(bool,            WindowIsNav,            false               )   //  �е�����
__REG_SET_DATA(bool,            WindowIsNav                                 )
__REG_GET_DATA(bool,            WindowIsSize,           false               )   //  ��������
__REG_SET_DATA(bool,            WindowIsSize                                )
__REG_GET_DATA(bool,            WindowIsMove,           false               )   //  �����ƶ�
__REG_SET_DATA(bool,            WindowIsMove                                )
__REG_GET_DATA(bool,            WindowIsTitleBar,       false               )   //  �б�����
__REG_SET_DATA(bool,            WindowIsTitleBar                            )
__REG_GET_DATA(bool,            WindowIsCollapse,       false               )   //  ��������
__REG_SET_DATA(bool,            WindowIsCollapse                            )
__REG_GET_DATA(bool,            WindowIsScrollBar,      false               )   //  �й�����
__REG_SET_DATA(bool,            WindowIsScrollBar                           )
__REG_GET_DATA(bool,            WindowIsFullScreen,     false               )   //  ����ȫ��
__REG_SET_DATA(bool,            WindowIsFullScreen                          )
__REG_GET_DATA(bool,            LayoutIsShowBorder,     false               )   //  ��ʾ�߿�
__REG_SET_DATA(bool,            LayoutIsShowBorder                          )
__REG_GET_DATA(float,           LayoutBorderNumber,     1                   )   //  �߿����
__REG_SET_DATA(float,           LayoutBorderNumber                          )
__REG_GET_DATA(int,             Align,                  0                   )   //  ����
__REG_SET_DATA(int,             Align                                       )
__REG_GET_DATA(glm::vec4,       Color,                  glm::vec4()         )   //  ��ɫ
__REG_SET_DATA(glm::vec4,       Color                                       )
__REG_GET_DATA(glm::vec4,       Move,                   glm::vec4()         )   //  ��λ
__REG_SET_DATA(glm::vec4,       Move                                        )
__REG_GET_DATA(std::string,     Name,                   std::string()       )   //  ����
__REG_SET_DATA(std::string,     Name                                        )
__REG_GET_DATA(std::string,     Tips,                   std::string()       )   //  ��ʾ
__REG_SET_DATA(std::string,     Tips                                        )
__REG_GET_DATA(std::string,     Skin,                   std::string()       )   //  Ƥ��
__REG_SET_DATA(std::string,     Skin                                        )
__REG_GET_DATA(std::string,     Title,                  std::string()       )   //  ����
__REG_SET_DATA(std::string,     Title                                       )
__REG_GET_DATA(bool,            Enabled,                true                )   //  ����
__REG_SET_DATA(bool,            Enabled                                     )
__REG_GET_DATA(bool,            Visible,                true                )   //  �ɼ�
__REG_SET_DATA(bool,            Visible                                     )
__REG_GET_DATA(bool,            EnabledKey,             false               )   //  ���ü���
__REG_SET_DATA(bool,            EnabledKey                                  )
__REG_GET_DATA(bool,            EnabledMouse,           false               )   //  �������
__REG_SET_DATA(bool,            EnabledMouse                                )
__REG_GET_DATA(glm::vec4,       Origin,                 glm::vec4()         )   //  ԭʼ��λ
__REG_SET_DATA(glm::vec4,       Origin                                      )
__REG_GET_DATA(glm::vec4,       Margin,                 glm::vec4()         )   //  �߾�
__REG_SET_DATA(glm::vec4,       Margin                                      )

#define GET_DATA(data, K)         __GetData##K(data)
#define SET_DATA(data, K, val)    __SetData##K(data, val)

//  ��������
template <class T>
void __ParseData(CustomData & data, const std::string & key, const std::string & val)
{
    if constexpr (std::is_same_v<T, int>) { data.emplace(key, S2I(val)); }
    else if constexpr (std::is_same_v<T, bool>) { data.emplace(key, S2B(val)); }
    else if constexpr (std::is_same_v<T, float>) { data.emplace(key, S2F(val)); }
    else if constexpr (std::is_same_v<T, std::string>) { data.emplace(key, (val)); }
    else if constexpr (std::is_same_v<T, glm::vec2>) { data.emplace(key, S2V2(val)); }
    else if constexpr (std::is_same_v<T, glm::vec3>) { data.emplace(key, S2V3(val)); }
    else if constexpr (std::is_same_v<T, glm::vec4>) { data.emplace(key, S2V4(val)); }
    else { static_assert(false); }
}

#define __REG_PARSE_DATA(data, key, val, T, K)     if (#K == key) __ParseData<T>(data, key, val)

inline void PARSE_DATA(CustomData & data, const std::string & key, const std::string & val)
{
    __REG_PARSE_DATA(data, key, val, bool,            WindowIsNav);
    __REG_PARSE_DATA(data, key, val, bool,            WindowIsSize);
    __REG_PARSE_DATA(data, key, val, bool,            WindowIsMove);
    __REG_PARSE_DATA(data, key, val, bool,            WindowIsTitleBar);
    __REG_PARSE_DATA(data, key, val, bool,            WindowIsCollapse);
    __REG_PARSE_DATA(data, key, val, bool,            WindowIsScrollBar);
    __REG_PARSE_DATA(data, key, val, bool,            WindowIsFullScreen);
    __REG_PARSE_DATA(data, key, val, bool,            LayoutIsShowBorder);
    __REG_PARSE_DATA(data, key, val, float,           LayoutBorderNumber);
    __REG_PARSE_DATA(data, key, val, int,             Align);
    __REG_PARSE_DATA(data, key, val, glm::vec4,       Color);
    __REG_PARSE_DATA(data, key, val, glm::vec4,       Move);
    __REG_PARSE_DATA(data, key, val, std::string,     Name);
    __REG_PARSE_DATA(data, key, val, std::string,     Tips);
    __REG_PARSE_DATA(data, key, val, std::string,     Skin);
    __REG_PARSE_DATA(data, key, val, std::string,     Title);
    __REG_PARSE_DATA(data, key, val, bool,            Enabled);
    __REG_PARSE_DATA(data, key, val, bool,            Visible);
    __REG_PARSE_DATA(data, key, val, bool,            EnabledKey);
    __REG_PARSE_DATA(data, key, val, bool,            EnabledMouse);
    __REG_PARSE_DATA(data, key, val, glm::vec4,       Origin);
    __REG_PARSE_DATA(data, key, val, glm::vec4,       Margin);
}
