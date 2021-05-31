#include <napi.h>
#include "SourceHighlight.h"
#include <iostream>
#include <sstream>

SourceHighlight::SourceHighlight(const Napi::CallbackInfo& callbackInfo) : Napi::ObjectWrap<SourceHighlight>(callbackInfo) {
}

Napi::Object SourceHighlight::Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "SourceHighlight", {
        InstanceMethod("initialize", &SourceHighlight::initialize),
        InstanceMethod("highlight", &SourceHighlight::highlight)
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
        Napi::RangeError::New(env, "Expected 3 arguments!");
        return Napi::Value();
    }

    bool isStringStreamHighlight = info[0].IsBuffer();
    bool isFileHighlight = info[0].IsString() && info[1].IsString();

    if (!isFileHighlight && !isStringStreamHighlight) {
        Napi::TypeError::New(env, "Input and output must both be buffers or strings!");
        return Napi::Value();
    }

    if (!info[2].IsString()) {
        Napi::TypeError::New(env, "inputLang/inputFileName expected to be a string!");
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

// Initialize native add-on
Napi::Object Init (Napi::Env env, Napi::Object exports) {
    SourceHighlight::Init(env, exports);
    return exports;
}

NODE_API_MODULE(sourcehighlight, Init);