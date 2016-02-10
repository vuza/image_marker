#include <nan.h>
#include <string>
#include "fillAllUnlabeledSegments.h"
#include "lib/im_processor_api.h"

using v8::Function;
using v8::Local;
using v8::Value;
using v8::Array;
using Nan::AsyncQueueWorker;
using Nan::AsyncWorker;
using Nan::Callback;
using Nan::HandleScope;
using Nan::New;
using Nan::Null;
using Nan::To;

class FillAllUnlabeledSegmentsWorker : public AsyncWorker {
 public:
  FillAllUnlabeledSegmentsWorker(Callback *callback, std::string imgName, std::string imgMatrix, int label)
    : AsyncWorker(callback), imgName(imgName), imgMatrix(imgMatrix), label(label) {
        im_processor_api = new Im_processor_api();
    }

  ~FillAllUnlabeledSegmentsWorker() {}

  void Execute () {
    imgMatrix = im_processor_api->fillAllUnlabeledSegments(imgName, imgMatrix, label);
  }

  void HandleOKCallback () {
    HandleScope scope;

    Local<Value> argv[] = {
        Null(),
        Nan::New<v8::String>(imgMatrix.c_str(), imgMatrix.length()).ToLocalChecked()
    };

    callback->Call(2, argv);
  }

 private:
  std::string imgName;
  std::string imgMatrix;
  int label;
  Im_processor_api* im_processor_api;
};

NAN_METHOD(FillAllUnlabeledSegments) {
  std::string imgName(*v8::String::Utf8Value(info[0]->ToString()));
  std::string imgMatrix(*v8::String::Utf8Value(info[1]->ToString()));
  int label = info[2]->IntegerValue();

  Callback *callback = new Callback(info[3].As<Function>());

  AsyncQueueWorker(new FillAllUnlabeledSegmentsWorker(callback, imgName, imgMatrix, label));
}
