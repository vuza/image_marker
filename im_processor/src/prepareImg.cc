#include <nan.h>
#include <string>
#include "prepareImg.h"
#include "lib/im_processor_api.h"

using v8::Function;
using v8::Local;
using v8::Value;
using Nan::AsyncQueueWorker;
using Nan::AsyncWorker;
using Nan::Callback;
using Nan::HandleScope;
using Nan::New;
using Nan::Null;
using Nan::To;

class PrepareImgWorker : public AsyncWorker {
public:
    PrepareImgWorker(Callback *callback, std::string imgPath)
            : AsyncWorker(callback), imgPath(imgPath) {
        im_processor_api = new Im_processor_api();
    }

    ~PrepareImgWorker() { }

    void Execute() {
        imgMatrix = im_processor_api->prepareImg(imgPath);
    }

    void HandleOKCallback() {
        HandleScope scope;

        Local <Value> argv[] = {
                Null(),
                Nan::New<v8::String>(imgMatrix.c_str(), imgMatrix.length()).ToLocalChecked()
        };

        callback->Call(2, argv);
    }

private:
    std::string imgPath;
    std::string imgMatrix;

    Im_processor_api *im_processor_api;
};

NAN_METHOD(PrepareImg) {
        std::string imgPath(*v8::String::Utf8Value(info[0]->ToString()));

        Callback *callback = new Callback(info[4].As<Function>());

        AsyncQueueWorker(new PrepareImgWorker(callback, imgPath));
}
