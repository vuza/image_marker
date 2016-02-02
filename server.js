var express = require('express');
var im_processor = require('./im_processor/build/Release/im_processor.node')
    server = express();


server.use(function (req, res, next) {
    res.setHeader('Access-Control-Allow-Origin', '*');
    res.setHeader('Access-Control-Allow-Methods', 'GET, POST, OPTIONS, PUT, PATCH, DELETE');

    next();
});

server.get('/', function (req, res) {
    console.log("Incoming request at / ");
    console.log(im_processor.getNextImg());
    res.send('Hello World!');
});

server.listen(3991, function() {
    console.log("Server listening on port 3991!");
});