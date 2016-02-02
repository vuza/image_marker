#include <node.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <v8.h>
#include <vector>
#include <uv.h>

using namespace v8;

namespace demo {

using v8::Function;
using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Null;
using v8::Object;
using v8::String;
using v8::Value;

    struct Work {
        uv_work_t  request;
        Persistent<Function> callback;
    };

    static void WorkAsync(uv_work_t *req)
    {
        Work *work = static_cast<Work *>(req->data);

        // this is the worker thread, lets build up the results
        // allocated results from the heap because we'll need
        // to access in the event loop later to send back
    }

    // called by libuv in event loop when async function completes
    static void WorkAsyncComplete(uv_work_t *req, int status)
    {
        Isolate * isolate = Isolate::GetCurrent();
        v8::HandleScope handleScope(isolate); // Required for Node 4.x

        Work *work = static_cast<Work *>(req->data);

        // the work has been done, and now we pack the results
        // vector into a Local array on the event-thread's stack.

        const unsigned argc = 1;
        Local<Value> argv[argc] = { String::NewFromUtf8(isolate, "callback results") };
        Local<Function>::New(isolate, work->callback)->Call(Null(isolate), argc, argv);

        // Free up the persistent function callback
        work->callback.Reset();

        delete work;
    }

    void test(const FunctionCallbackInfo<Value>& args) {
        Isolate* isolate = args.GetIsolate();

        Work * work = new Work();
        work->request.data = work;

        // store the callback from JS in the work package so we can
        // invoke it later
        Local<Function> cb = Local<Function>::Cast(args[0]);
        work->callback.Reset(isolate, cb);

        // kick of the worker thread
        uv_queue_work(uv_default_loop(), &work->request, WorkAsync, WorkAsyncComplete);

        args.GetReturnValue().Set(Undefined(isolate));
    }

    void Init(Local<Object> exports, Local<Object> module) {
        NODE_SET_METHOD(exports, "test", test);
    }

    NODE_MODULE(im_processor, Init)

}