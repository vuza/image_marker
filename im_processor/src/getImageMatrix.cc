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
    GetImageMatrixWorker(Callback *callback, std::string imgPath, int superpixelsize, double compactness,
                         int thr_col_val)
            : AsyncWorker(callback), imgPath(imgPath), superpixelsize(superpixelsize), compactness(compactness),
              thr_col_val(thr_col_val) {
        im_processor_api = new Im_processor_api();
    }

    ~GetImageMatrixWorker() { }

    void Execute() {
        imgMatrix = im_processor_api->getImageMatrix(imgPath, superpixelsize, compactness, thr_col_val);
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
    int superpixelsize;
    double compactness;
    int thr_col_val;

    Im_processor_api *im_processor_api;
};

NAN_METHOD(GetImageMatrix) {
    std::string imgPath(*v8::String::Utf8Value(info[0]->ToString()));
    int superpixelsize = info[1]->IntegerValue();
    double compactness = info[2]->NumberValue();
    int thr_col_val = info[3]->IntegerValue();

    Callback *callback = new Callback(info[4].As<Function>());

    AsyncQueueWorker(new GetImageMatrixWorker(callback, imgPath, superpixelsize, compactness, thr_col_val));
}
