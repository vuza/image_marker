#include <nan.h>
#include <string>
#include "getImageMatrix.h"
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

class GetImageMatrixWorker : public AsyncWorker {
 public:
  GetImageMatrixWorker(Callback *callback, std::string path)
    : AsyncWorker(callback), path(path), matrix("") {
        im_processor_api = new Im_processor_api();
    }

  ~GetImageMatrixWorker() {}

  void Execute () {
    matrix = im_processor_api->getImageMatrix(path);
  }

  void HandleOKCallback () {
    HandleScope scope;

    Local<Value> argv[] = {
        Null(),
        Nan::New<v8::String>(matrix.c_str(), matrix.length()).ToLocalChecked()
    };

    callback->Call(2, argv);
  }

 private:
  std::string path;
  std::string matrix;
  Im_processor_api* im_processor_api;
};

NAN_METHOD(GetImageMatrix) {
  v8::String::Utf8Value param1(info[0]->ToString());
  std::string path = std::string(*param1);

  Callback *callback = new Callback(info[1].As<Function>());

  AsyncQueueWorker(new GetImageMatrixWorker(callback, path));
}
