var express = require('express'),
    server = express();


server.use(function (req, res, next) {
    res.setHeader('Access-Control-Allow-Origin', '*');
    res.setHeader('Access-Control-Allow-Methods', 'GET, POST, OPTIONS, PUT, PATCH, DELETE');

    next();
});

var mylib = require("./im_processor/build/Release/im_processor");
console.log(mylib.hello());

server.listen(3991);