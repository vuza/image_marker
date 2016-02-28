define(['models/Model', 'socketio', 'config', 'controllers/ErrorController', 'Radio'], function (Model, socketio, config, errorController, Radio) {
    var socket,
        routerChannel = Radio.channel('router'),
        Image = Model.extend({
            initialize: function () {
                socket = socketio(config.socket);
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
                if (this.get('name') && this.get('name') != '')
                    return this.urlRoot + '/' + this.get('name');

                return this.urlRoot;
            },

            parse: function (data) {
                if (data.err) this.err(data.err);

                // Don't save matrix as a attribute, but as a property, so it does not get printed to html
                if(data && data.result && data.result.matrix){
                    this.matrix = data.result.matrix;
                    delete data.result.matrix;
                }

                return data.result;
            },

            err: function (err) {
                if(err.code == 0)
                    routerChannel.trigger('navigate', 'overview'); // "No unlocked image found" ==> load overview!
                else
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