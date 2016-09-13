var config = require('./../config');
var winston = require('winston');
var io = require('socket.io')(config.socket.port);

// It is wrapped in a function, so we can use JS new operator
module.exports = function(name, locked, width, height, path){
    /**
     * Private vars
     */
    var setLockedRecently = false;
    var sockets = {};
    var This = this;

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
        sockets[socket.conn.id] = socket;

        socket.on(This.name + 'setLocked', function(data){
            setLockedRecently = This.locked = data.locked;

            winston.verbose('[received] ' + This.name + ', locked: ' + data.locked);
        });

        socket.on('disconnect', function() {
            if(sockets[socket.conn.id]){
                delete sockets[socket.conn.id];
            }
        });
    });

    // Check lock status
    setInterval(function(){
        This.locked = setLockedRecently;
        setLockedRecently = false;

        Object.keys(sockets).forEach(function(id){
            sockets[id].emit(This.name + 'setLocked', {locked: This.locked});
        });

        winston.verbose('[update status] ' + This.name + ', locked: ' + This.locked);
    }, 11000);
};