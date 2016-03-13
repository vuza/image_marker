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
    FillAllUnlabeledSegmentsWorker(Callback *callback, std::string imgPath, int label, int superpixelsize,
                                   double compactness, int thr_col_val)
            : AsyncWorker(callback), imgPath(imgPath), label(label), superpixelsize(superpixelsize),
              compactness(compactness), thr_col_val(thr_col_val) {
        im_processor_api = new Im_processor_api();
    }

    ~FillAllUnlabeledSegmentsWorker() { }

    void Execute() {
        imgMatrix = im_processor_api->fillAllUnlabeledSegments(imgPath, label, superpixelsize, compactness,
                                                               thr_col_val);
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
    int label;
    int superpixelsize;
    double compactness;
    int thr_col_val;

    Im_processor_api *im_processor_api;
};

NAN_METHOD(FillAllUnlabeledSegments) {
    std::string imgPath(*v8::String::Utf8Value(info[0]->ToString()));
    //std::string imgMatrix(*v8::String::Utf8Value(info[1]->ToString())); //TODO do i need this here?
    int label = info[1]->IntegerValue();
    int superpixelsize = info[2]->IntegerValue();
    double compactness = info[3]->NumberValue();
    int thr_col_val = info[4]->IntegerValue();

    Callback *callback = new Callback(info[5].As<Function>());

    AsyncQueueWorker(new FillAllUnlabeledSegmentsWorker(callback, imgPath, label, superpixelsize, compactness, thr_col_val));
}
