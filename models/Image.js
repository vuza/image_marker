var config = require('./../config'),
    winston = require('winston'),
    io = require('socket.io')(config.socket.port);

// It is wrapped in a function, so we can use JS new operator
module.exports = function(name, locked, width, height){
    /**
     * Private vars
     */
    var setLockedRecently = false,
        This = this;

    /**
     * Public vars
     */
    this.name = name;
    this.locked = locked;
    this.width = width;
    this.height = height;

    /**
     * Private logic
     */
    io.on('connection', function(socket){
        socket.on(This.name + 'setLocked', function(data){
            setLockedRecently = This.locked = data.locked;

            winston.verbose('[received] ' + This.name + ', locked: ' + data.locked);
        });
    });

    // Check lock status
    setInterval(function(){
        This.locked = setLockedRecently;
        setLockedRecently = false;

        winston.verbose('[update status] ' + This.name + ', locked: ' + This.locked);
    }, 11000);
};