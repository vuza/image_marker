var config = require('./../config'),
    winston = require('winston'),
    io = require('socket.io')(config.socket.port);

// It is wrapped in a function, so we can use JS new operator
module.exports = function(name, locked, width, height, path){
    /**
     * Private vars
     */
    var setLockedRecently = false,
        sockets = [],
        This = this;

    /**
     * Public vars
     */
    this.name = name;
    this.locked = locked;
    this.width = width;
    this.height = height;
    this.path = path;

    /**
     * Private logic
     */
    io.on('connection', function(socket){
        sockets.push(socket);

        socket.on(This.name + 'setLocked', function(data){
            setLockedRecently = This.locked = data.locked;

            winston.verbose('[received] ' + This.name + ', locked: ' + data.locked);
        });

        socket.on('disconnect', function() {
            var i = sockets.indexOf(socket);
            if(i > -1)
                sockets.splice(socket, 1);
        });
    });

    // Check lock status
    setInterval(function(){
        var before = This.locked;

        This.locked = setLockedRecently;
        setLockedRecently = false;

        if(before != This.locked && This.locked == false){
            sockets.forEach(function(s){
                s.emit(This.name + 'setLocked', {locked: false});
            });
        }

        winston.verbose('[update status] ' + This.name + ', locked: ' + This.locked);
    }, 11000);
};