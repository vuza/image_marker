var express = require('express'),
    server = express();


server.use(function (req, res, next) {
    res.setHeader('Access-Control-Allow-Origin', '*');
    res.setHeader('Access-Control-Allow-Methods', 'GET, POST, OPTIONS, PUT, PATCH, DELETE');

    next();
});

var im_processor = require('./im_processor/build/Release/im_processor');
im_processor.test(function(r){
    console.log(r);
});

server.listen(3991);