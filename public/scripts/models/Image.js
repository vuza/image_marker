define(['models/Model', 'socketio'], function (Model, socketio) {
    var socket,
        Image = Model.extend({
            initialize: function () {
                socket = socketio('http://localhost:3000'); //TODO set in config
                this.on('change:locked', this.updateLockstatus, this);
            },

            defaults: {
                name: '',
                height: 0,
                width: 0,
                locked: false,
                matrix: []
            },

            urlRoot: 'http://localhost:3991/api/v1/image',

            url: function () {
                if (this.get('name') && this.get('name') != '')
                    return this.urlRoot + '/' + this.get('name');

                return this.urlRoot;
            },

            parse: function (data) {
                if (data.err) this.err(data.err);

                return data.result;
            },

            err: function (err) {
                console.log('oh we got an error, see: ' + JSON.stringify(err)); //TODO implement proper error handling
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