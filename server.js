var express = require('express'),
    server = express();


server.use(function (req, res, next) {
    res.setHeader('Access-Control-Allow-Origin', '*');
    res.setHeader('Access-Control-Allow-Methods', 'GET, POST, OPTIONS, PUT, PATCH, DELETE');

    next();
});

try{
    var im_processor = require('./im_processor/build/Release/addon');
    im_processor.fillSegment("imageName", "imgMatrix", 1, 2, 3, function(err, res){
        console.log('result: ');
        console.log(res);
    });
} catch(e){
    console.log(e);
}


server.listen(3991);

//https://github.com/cmake-js/cmake-js/wiki/TUTORIAL-01-Creating-a-native-module-by-using-CMake.js-and-NAN