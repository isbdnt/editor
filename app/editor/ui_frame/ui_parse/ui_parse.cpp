#include "ui_parse.h"
#include "../ui_state/ui_state.h"
#include "../ui_class/ui_class.h"

UIClass * UIParser::Parse(const std::string & url)
{
    auto json = mmc::JsonValue::FromFile(url);
    ASSERT_LOG(json, "Parse: {0}", url);
    return Parse(json);
}

UIClass * UIParser::Parse(const mmc::JsonValue::Value json)
{
    auto object = CreateObject(json->At("__Property", "Type")->ToString());
    ASSERT_LOG(object != nullptr, "");
    Parse__Property(json, object);
    Parse__Children(json, object);
    return object;
}

void UIParser::Parse__Property(const mmc::JsonValue::Value json, UIClass * object)
{
    for (auto ele : json->At("__Property"))
    {
        ASSERT_LOG(ele.mValue->GetType() == mmc::JsonValue::Type::kSTRING, "{0}", ele.mKey);
        PARSE_DATA(object->GetState<UIState>().mData, ele.mKey, ele.mValue->ToString());
    }
}

void UIParser::Parse__Children(const mmc::JsonValue::Value json, UIClass * object)
{
    for (auto ele : json->At("__Children"))
    {
        object->AddChild(Parse(ele.mValue));
    }
}

UIClass * UIParser::CreateObject(const std::string & type)
{
    if      (type == WIDGET_TREE) {}
    else if (type == WIDGET_IMAGE) {}
    else if (type == WIDGET_BUTTON) {}
    else if (type == WIDGET_LAYOUT) { return new UIClassLayout(new UIStateLayout()); }
    else if (type == WIDGET_WINDOW) { return new UIClassWindow(new UIStateWindow()); }
    else if (type == WIDGET_EDITBOX) {}
    else if (type == WIDGET_TEXTBOX) {}
    else if (type == WIDGET_ComboBox) {}
    else if (type == WIDGET_UICANVAS) {}
    else if (type == WIDGET_GLCANVAS) {}
    else { ASSERT_LOG(false, "Error Type: {0}!", type); }
    return nullptr;
}