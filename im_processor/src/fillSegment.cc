#include <nan.h>
#include <string>
#include "fillSegment.h"
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

class FillSegmentWorker : public AsyncWorker {
 public:
  FillSegmentWorker(Callback *callback, std::string imgName, std::string imgMatrix, int x, int y, int label)
    : AsyncWorker(callback), imgName(imgName), imgMatrix(imgMatrix), x(x), y(y), label(label) {
        im_processor_api = new Im_processor_api();
    }

  ~FillSegmentWorker() {}

  void Execute () {
    imgMatrix = im_processor_api->fillSegment(imgName, imgMatrix, x, y, label);
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
  int x;
  int y;
  int label;
  Im_processor_api* im_processor_api;
};

NAN_METHOD(FillSegment) {
  std::string imgName(*v8::String::Utf8Value(info[0]->ToString()));
  std::string imgMatrix(*v8::String::Utf8Value(info[1]->ToString()));
  int x = info[2]->IntegerValue();
  int y = info[3]->IntegerValue();
  int label = info[4]->IntegerValue();

  Callback *callback = new Callback(info[5].As<Function>());

  AsyncQueueWorker(new FillSegmentWorker(callback, imgName, imgMatrix, x, y, label));
}
