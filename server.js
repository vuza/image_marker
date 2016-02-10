var express = require('express'),
    server = express();


server.use(function (req, res, next) {
    res.setHeader('Access-Control-Allow-Origin', '*');
    res.setHeader('Access-Control-Allow-Methods', 'GET, POST, OPTIONS, PUT, PATCH, DELETE');

    next();
});

var im_processor = require('./im_processor/build/Release/addon');
im_processor.fillAllUnlabeledSegments("imageName", "imgMatrix", 3, function(err, res){
    console.log(res);
});

server.listen(3991);