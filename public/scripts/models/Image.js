define(['socketio', 'config', 'controllers/ErrorController', 'Radio'], function (socketio, config, errorController, Radio) {
    var socket,
        routerChannel = Radio.channel('router'),
        Image = Backbone.Model.extend({
            initialize: function () {
                socket = socketio(config.socket);
                this.on('change:locked', this.updateLockstatus, this);
            },

            defaults: {
                name: '',
                height: 0,
                width: 0,
                locked: true
            },

            urlRoot: config.api + '/image',

            url: function () {
                if (this.get('name') && this.get('name') != '')
                    return this.urlRoot + '/' + this.get('name') + '/' + this.get('locked');

                return this.urlRoot + '/' + this.get('locked');
            },

            parse: function (data) {
                if (data.err) this.err(data.err);

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