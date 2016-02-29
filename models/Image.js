var config = require('./../config'),
    winston = require('winston'),
    io = require('socket.io')(config.socket.port);

// It is wrapped in a function, so we can use JS new operator
module.exports = function(name, locked, width, height){
    var setLockedRecently = false,
        image = {
            name: name,
            locked: locked,
            width: width,
            height: height
        };

    io.on('connection', function(socket){
        socket.on(image.name + 'setLocked', function(data){
            setLockedRecently = image.locked = data.locked;

            winston.verbose('[received] ' + image.name + ', locked: ' + data.locked);
        });
    });

    // Check lock status
    setInterval(function(){
        image.locked = setLockedRecently;
        setLockedRecently = false;

        winston.verbose('[update status] ' + image.name + ', locked: ' + image.locked);
    }, 11000);

    return image;
};