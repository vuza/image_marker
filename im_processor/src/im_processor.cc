#include <node.h>

namespace demo {

using v8::Function;
using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Null;
using v8::Object;
using v8::String;
using v8::Value;

    void getNextImg(const FunctionCallbackInfo<Value>& args){
        Isolate* isolate = args.GetIsolate();
        //TODO String nextImgPath getNextImg(String actualImgName)
        args.GetReturnValue().Set(String::NewFromUtf8(isolate, "todo"));
    }

    void getPrevImg(const FunctionCallbackInfo<Value>& args){
        Isolate* isolate = args.GetIsolate();
        //TODO String prevImgPath getPrevImg(String actualImgName)
        args.GetReturnValue().Set(String::NewFromUtf8(isolate, ""));
    }

    void getImageMatrix(const FunctionCallbackInfo<Value>& args) {
        Isolate* isolate = args.GetIsolate();
        Local<Function> cb = Local<Function>::Cast(args[0]);
        const unsigned argc = 1;
        //TODO Matrix imgMatrix getImageMatrix(String imgName)
        Local<Value> argv[argc] = { String::NewFromUtf8(isolate, "hello world") };
        cb->Call(Null(isolate), argc, argv);
    }

    void fillSegment(const FunctionCallbackInfo<Value>& args) {
        Isolate* isolate = args.GetIsolate();
        Local<Function> cb = Local<Function>::Cast(args[0]);
        const unsigned argc = 1;
        //TODO Matrix imgMatrix fillSegment(String imgName, Matrix imgMatrix, int x, int y, int label)
        Local<Value> argv[argc] = { String::NewFromUtf8(isolate, "hello world") };
        cb->Call(Null(isolate), argc, argv);
    }

    void fillAllUnlabeledSegments(const FunctionCallbackInfo<Value>& args) {
        Isolate* isolate = args.GetIsolate();
        Local<Function> cb = Local<Function>::Cast(args[0]);
        const unsigned argc = 1;
        //TODO Matrix imgMatrix fillAllUnlabeledSegments(String imgName, Matrix imgMatrix, int label)
        Local<Value> argv[argc] = { String::NewFromUtf8(isolate, "hello world") };
        cb->Call(Null(isolate), argc, argv);
    }

    void Init(Local<Object> exports, Local<Object> module) {
        NODE_SET_METHOD(exports, "getNextImg", getNextImg);
        NODE_SET_METHOD(exports, "getPrevImg", getPrevImg);
        NODE_SET_METHOD(exports, "getImageMatrix", getImageMatrix);
        NODE_SET_METHOD(exports, "fillSegment", fillSegment);
        NODE_SET_METHOD(exports, "fillAllUnlabeledSegments", fillAllUnlabeledSegments);
    }

    NODE_MODULE(im_processor, Init)

}