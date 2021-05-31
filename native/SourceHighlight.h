#ifndef NAPI_SOURCE_HIGHLIGHT_WRAPPER_H
#define NAPI_SOURCE_HIGHLIGHT_WRAPPER_H

#include <napi.h>
#include <srchilite/sourcehighlight.h>

class SourceHighlight : public Napi::ObjectWrap<SourceHighlight> {
  public:
    static Napi::Object Init(Napi::Env env, Napi::Object exports);

    SourceHighlight(const Napi::CallbackInfo& callbackInfo);

    Napi::Value initialize(const Napi::CallbackInfo& info);
    Napi::Value highlight(const Napi::CallbackInfo& info);
    Napi::Value checkLangDef(const Napi::CallbackInfo& langFile);
    Napi::Value checkOutLangDef(const Napi::CallbackInfo& outLangFile);

    Napi::Value setDataDir(const Napi::CallbackInfo& info);
    Napi::Value setStyleFile(const Napi::CallbackInfo& info);
    Napi::Value setStyleCssFile(const Napi::CallbackInfo& info);
    Napi::Value setStyleDefaultFile(const Napi::CallbackInfo& info);
    Napi::Value setTitle(const Napi::CallbackInfo& info);
    Napi::Value setInputLang(const Napi::CallbackInfo& info);
    Napi::Value setCss(const Napi::CallbackInfo& info);
    Napi::Value setHeaderFileName(const Napi::CallbackInfo& info);
    Napi::Value setFooterFileName(const Napi::CallbackInfo& info);
    Napi::Value setOutputDir(const Napi::CallbackInfo& info);
  private:
    srchilite::SourceHighlight instance;
};

#endif