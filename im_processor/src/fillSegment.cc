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
    FillSegmentWorker(Callback *callback, std::string imgPath, int x, int y, int label, int superpixelsize,
                      double compactness, int thr_col_val)
            : AsyncWorker(callback), imgPath(imgPath), x(x), y(y), label(label), superpixelsize(superpixelsize),
              compactness(compactness), thr_col_val(thr_col_val) {
        im_processor_api = new Im_processor_api();
    }

    ~FillSegmentWorker() { }

    void Execute() {
        imgMatrix = im_processor_api->fillSegment(imgPath, x, y, label, superpixelsize, compactness, thr_col_val);
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
    int x;
    int y;
    int label;
    int superpixelsize;
    double compactness;
    int thr_col_val;
    Im_processor_api *im_processor_api;
};

NAN_METHOD(FillSegment) {
    std::string imgPath(*v8::String::Utf8Value(info[0]->ToString()));
    //std::string imgMatrix(*v8::String::Utf8Value(info[1]->ToString())); //TODO do I need this here?
    int x = info[1]->IntegerValue();
    int y = info[2]->IntegerValue();
    int label = info[3]->IntegerValue();
    int superpixelsize = info[4]->IntegerValue();
    double compactness = info[5]->NumberValue();
    int thr_col_val = info[6]->IntegerValue();


    Callback *callback = new Callback(info[7].As<Function>());

    AsyncQueueWorker(new FillSegmentWorker(callback, imgPath, x, y, label, superpixelsize, compactness, thr_col_val));
}
