#include <nan.h>
#include "getImageMatrix.h"

using v8::FunctionTemplate;
using v8::Handle;
using v8::Object;
using v8::String;
using Nan::GetFunction;
using Nan::New;
using Nan::Set;

NAN_MODULE_INIT(InitAll) {
  Set(target, New<String>("test").ToLocalChecked(),
    GetFunction(New<FunctionTemplate>(GetImageMatrix)).ToLocalChecked());
}

NODE_MODULE(im_processor, InitAll)
