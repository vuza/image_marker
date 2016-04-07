define(['socketio', 'config', 'controllers/ErrorController'], function (socketio, config, errorController) {
    var socket,
        Image = Backbone.Model.extend({
            initialize: function () {
                var This = this;
                socket = socketio(config.socket);
                socket.on(This.get('name') + 'setLocked', function(data){
                    This.set('locked', data.locked);
                });

                this.on('change:locked', this.updateLockstatus, this);
            },

            defaults: {
                name: '',
                height: 0,
                width: 0,
                locked: false
            },

            urlRoot: config.api + '/image',

            url: function () {
                // last param true, to get locked image
                if (this.get('name') && this.get('name') != '')
                    return this.urlRoot + '/' + this.get('name') + '/true';

                return this.urlRoot + '/true';
            },

            parse: function (data) {
                if (data.err) this.err(data.err);

                return data.result;
            },

            err: function (err) {
                if(err.code != 0) // "No unlocked image found" ==> that is not a error we want to handle here
                    errorController.show('Error while parsing image response from server, error: ' + JSON.stringify(err));
            },

            updateLockstatus: function () {
                if(this.updateLockstatusIntervalId)
                    clearInterval(this.updateLockstatusIntervalId);

                var locked = this.get('locked'),
                    name = this.get('name'),
                    connect = function () {
                        socket.emit(name + 'setLocked', {locked: locked});
                    };

                if(locked)
                    this.updateLockstatusIntervalId = setInterval(connect, 5000);

                connect();
            },

            updateLockstatusIntervalId: null
        });

    return Image;
});