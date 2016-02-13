var io = require('socket.io')(3000); //TODO set in config

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
            if(data.locked)
                lockImage();
        });
    });

    var lockImage = function(){
        image.locked = true;
        setLockedRecently = true;
    };

    // Check lock status
    var intervalId = setInterval(function(){
        if(!setLockedRecently) {
            image.locked = false;
            clearInterval(intervalId);
        }

        setLockedRecently = false;
    }, 11000);

    return image;
};