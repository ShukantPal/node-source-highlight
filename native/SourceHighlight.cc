#include <napi.h>
#include "SourceHighlight.h"
#include <iostream>
#include <srchilite/highlightbuilderexception.h>
#include <srchilite/ioexception.h>
#include <srchilite/parserexception.h>
#include <srchilite/sourcehighlight.h>
#include <sstream>

SourceHighlight::SourceHighlight(const Napi::CallbackInfo& info) :
    Napi::ObjectWrap<SourceHighlight>(info),
    instance(info.Length() < 1 ? "" : (std::string) info[0].As<Napi::String>()) {}

Napi::Object SourceHighlight::Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "SourceHighlight", {
        InstanceMethod("initialize", &SourceHighlight::initialize),
        InstanceMethod("highlight", &SourceHighlight::highlight),
        InstanceMethod("checkLangDef", &SourceHighlight::checkLangDef),
        InstanceMethod("checkOutLangDef", &SourceHighlight::checkOutLangDef),
        InstanceMethod("setDataDir", &SourceHighlight::setDataDir),
        InstanceMethod("setStyleFile", &SourceHighlight::setStyleFile),
        InstanceMethod("setStyleCssFile", &SourceHighlight::setStyleCssFile),
        InstanceMethod("setStyleDefaultFile", &SourceHighlight::setStyleDefaultFile),
        InstanceMethod("setTitle", &SourceHighlight::setTitle),
        InstanceMethod("setInputLang", &SourceHighlight::setInputLang),
        InstanceMethod("setCss", &SourceHighlight::setCss),
        InstanceMethod("setHeaderFileName", &SourceHighlight::setHeaderFileName),
        InstanceMethod("setFooterFileName", &SourceHighlight::setFooterFileName),
        InstanceMethod("setOutputDir", &SourceHighlight::setOutputDir)
    });

    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);

    exports.Set("SourceHighlight", func);

    return exports;
}

Napi::Value SourceHighlight::initialize(const Napi::CallbackInfo &info) {
    this->instance.initialize();
    std::cout << "NOTE: You do not need to initialize SourceHighlight manually!\n";

    return Napi::Value();
}

Napi::Value SourceHighlight::highlight(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    int length = info.Length();

    if (length != 3) {
        Napi::RangeError::New(env, "Expected 3 arguments!").ThrowAsJavaScriptException();
        return Napi::Value();
    }

    bool isStringStreamHighlight = info[0].IsBuffer();
    bool isFileHighlight = info[0].IsString() && info[1].IsString();

    if (!isFileHighlight && !isStringStreamHighlight) {
        Napi::TypeError::New(env, "Input and output must both be buffers or strings!").ThrowAsJavaScriptException();
        return Napi::Value();
    }

    if (!info[2].IsString()) {
        Napi::TypeError::New(env, "inputLang/inputFileName expected to be a string!").ThrowAsJavaScriptException();
        return Napi::Value();
    }

    if (isFileHighlight) {
        std::string input = (std::string) info[0].As<Napi::String>();
        std::string output = (std::string) info[1].As<Napi::String>();
        std::string inputLang = (std::string) info[2].As<Napi::String>();

        this->instance.highlight(input, output, inputLang);

        return Napi::Value();
    } else {
        Napi::Buffer<char> input = info[0].As<Napi::Buffer<char>>();
        std::string inputLang = (std::string) info[1].As<Napi::String>();
        std::string inputFileName = (std::string) info[2].As<Napi::String>();
        std::stringstream inputStream;
        std::stringstream outputStream;

        for (size_t i = 0; i < input.Length(); i++) {
            inputStream << input.Data()[i];
        }

        this->instance.highlight(inputStream, outputStream, inputLang, inputFileName);

        return Napi::Value::From<std::string>(env, outputStream.str());
    }
}

Napi::Value SourceHighlight::checkLangDef(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if (info.Length() < 1 || !info[0].IsString()) {
        Napi::TypeError::New(
            info.Env(),
            "SourceHighlight.prototype.checkLangDef langFile must be a string"
        ).ThrowAsJavaScriptException();
        return Napi::Value();
    }

    std::string langFile = (std::string) info[0].As<Napi::String>();

    try {
        this->instance.checkLangDef(langFile);
    } catch (const srchilite::HighlightBuilderException& e) {
        Napi::Error error = Napi::Error::New(env);

        error.Set("filename", Napi::Value::From(env, e.filename));
        error.Set("line", Napi::Value::From(env, e.line));
        error.ThrowAsJavaScriptException();
    } catch (const srchilite::ParserException& e) {
        Napi::Error error = Napi::Error::New(env, e.message);

        error.Set("additional", Napi::Value::From(env, e.additional));
        error.Set("filename",  Napi::Value::From(env, e.filename));
        error.Set("line", Napi::Value::From(env, e.line));
        error.ThrowAsJavaScriptException();
    } catch (const srchilite::IOException e) {
        Napi::Error error = Napi::Error::New(env, e.message);

        std::cout << "IOEXCEPTION";

        error.Set("filename", Napi::Value::From(env, e.filename));
        error.ThrowAsJavaScriptException();
    } catch (const std::exception& e) {
        Napi::Error::New(env, std::string(e.what())).ThrowAsJavaScriptException();
    }

    return info.Env().Undefined();
}

Napi::Value SourceHighlight::checkOutLangDef(const Napi::CallbackInfo& info) {
    if (info.Length() < 1 || !info[0].IsString()) {
        Napi::TypeError::New(
            info.Env(),
            "SourceHighlight.prototype.checkOutLangDef outLangDef must be a string"
        ).ThrowAsJavaScriptException();
        return Napi::Value();
    }

    std::string outLangDef = (std::string) info[0].As<Napi::String>();

    try {
        this->instance.checkOutLangDef(outLangDef);
    } catch (const std::exception e) {
        Napi::Error::New(info.Env(), std::string(e.what())).ThrowAsJavaScriptException();
        return Napi::Value();
    }

    return info.Env().Undefined();
}

Napi::Value SourceHighlight::setDataDir(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if (info.Length() < 1 || !info[0].IsString()) {
        Napi::TypeError::New(env, "SourceHighlight.prototype.setDataDir dataDir must be a string").ThrowAsJavaScriptException();
        return Napi::Value();
    }

    this->instance.setDataDir((std::string) info[0].As<Napi::String>());
    return info.Env().Undefined();
}

Napi::Value SourceHighlight::setStyleFile(const Napi::CallbackInfo& info) {
    if (info.Length() < 1 || !info[0].IsString()) {
        Napi::TypeError::New(info.Env(), "SourceHighlight.prototype.setStyleFile dataDir must be a string").ThrowAsJavaScriptException();
        return Napi::Value();
    }

    this->instance.setStyleFile((std::string) info[0].As<Napi::String>());
    return info.Env().Undefined();
}

Napi::Value SourceHighlight::setStyleCssFile(const Napi::CallbackInfo& info) {
    if (info.Length() < 1 || !info[0].IsString()) {
        Napi::TypeError::New(info.Env(), "SourceHighlight.prototype.setStyleCssFile styleFile must be a string").ThrowAsJavaScriptException();
        return Napi::Value();
    }

    this->instance.setStyleCssFile((std::string) info[0].As<Napi::String>());
    return info.Env().Undefined();
}

Napi::Value SourceHighlight::setStyleDefaultFile(const Napi::CallbackInfo& info) {
    if (info.Length() < 1 || !info[0].IsString()) {
        Napi::TypeError::New(info.Env(), "SourceHighlight.prototype.setStyleDefaultFile styleFile must be a string").ThrowAsJavaScriptException();
        return Napi::Value();
    }

    this->instance.setStyleDefaultFile((std::string) info[0].As<Napi::String>());
    return info.Env().Undefined();
}

Napi::Value SourceHighlight::setTitle(const Napi::CallbackInfo& info) {
    if (info.Length() < 1 || !info[0].IsString()) {
        Napi::TypeError::New(info.Env(), "SourceHighlight.prototype.setTitle title must be a string");
        return Napi::Value();
    }

    this->instance.setTitle((std::string) info[0].As<Napi::String>());
    return info.Env().Undefined();
}

Napi::Value SourceHighlight::setInputLang(const Napi::CallbackInfo& info) {
    if (info.Length() < 1 || !info[0].IsString()) {
        Napi::TypeError::New(info.Env(), "SourceHighlight.prototype.setInputLang inputLang must be a string");
        return Napi::Value();
    }

    this->instance.setInputLang((std::string) info[0].As<Napi::String>());
    return info.Env().Undefined();
}

Napi::Value SourceHighlight::setCss(const Napi::CallbackInfo& info) {
    if (info.Length() < 1 || !info[0].IsString()) {
        Napi::TypeError::New(info.Env(), "SourceHighlight.prototype.setCss css must be a string");
        return Napi::Value();
    }

    this->instance.setCss((std::string) info[0].As<Napi::String>());
    return info.Env().Undefined();
}

Napi::Value SourceHighlight::setHeaderFileName(const Napi::CallbackInfo& info) {
    if (info.Length() < 1 || !info[0].IsString()) {
        Napi::TypeError::New(info.Env(), "SourceHighlight.prototype.setHeaderFileName h must be a string");
        return Napi::Value();
    }

    this->instance.setHeaderFileName((std::string) info[0].As<Napi::String>());
    return info.Env().Undefined();
}

Napi::Value SourceHighlight::setFooterFileName(const Napi::CallbackInfo& info) {
    if (info.Length() < 1 || !info[0].IsString()) {
        Napi::TypeError::New(info.Env(), "SourceHighlight.prototype.setFooterFileName f must be a string");
        return Napi::Value();
    }

    this->instance.setFooterFileName((std::string) info[0].As<Napi::String>());
    return info.Env().Undefined();
}

Napi::Value SourceHighlight::setOutputDir(const Napi::CallbackInfo& info) {
    if (info.Length() < 1 || !info[0].IsString()) {
        Napi::TypeError::New(info.Env(), "SourceHighlight.prototype.setOutputDir outputDir must be a string");
        return Napi::Value();
    }

    this->instance.setOutputDir((std::string) info[0].As<Napi::String>());
    return info.Env().Undefined();
}

// Initialize native add-on
Napi::Object Init (Napi::Env env, Napi::Object exports) {
    SourceHighlight::Init(env, exports);
    return exports;
}

NODE_API_MODULE(sourcehighlight, Init);