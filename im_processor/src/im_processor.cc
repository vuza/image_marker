#include <nan.h>
#include "getImageMatrix.h"
#include "fillSegment.h"
#include "fillAllUnlabeledSegments.h"

using v8::FunctionTemplate;
using v8::Handle;
using v8::Object;
using v8::String;
using Nan::GetFunction;
using Nan::New;
using Nan::Set;

NAN_MODULE_INIT(InitAll) {
  Set(target, New<String>("getImageMatrix").ToLocalChecked(),
    GetFunction(New<FunctionTemplate>(GetImageMatrix)).ToLocalChecked());

  Set(target, New<String>("fillSegment").ToLocalChecked(),
    GetFunction(New<FunctionTemplate>(FillSegment)).ToLocalChecked());

  Set(target, New<String>("fillAllUnlabeledSegments").ToLocalChecked(),
    GetFunction(New<FunctionTemplate>(FillAllUnlabeledSegments)).ToLocalChecked());
}

NODE_MODULE(im_processor, InitAll)
