define(['socketio', 'config', 'controllers/ErrorController', 'jquery'], function (socketio, config, errorController, $) {
    var socket;
    var Image = Backbone.Model.extend({
        initialize: function (opt) {
            opt = opt || {};
            if (opt.name){
                this.set('name', opt.name);
            }
            if (opt.height){
                this.set('height', opt.height);
            }
            if (opt.width){
                this.set('width', opt.width);
            }
            if (opt.locked){
                this.set('locked', opt.locked);
            }
            if (opt.sendLockedStatusToServer){
                this.set('sendLockedStatusToServer', opt.sendLockedStatusToServer);
            }

            var This = this;
            socket = socketio(config.socket);
            socket.on(This.get('name') + 'setLocked', function (data) {
                This.set('locked', data.locked);
            });

            this.on('sync', function () {
                if (This.get('sendLockedStatusToServer') && !This.get('wasLockedBeforeRequested')) {
                    This.on('change:locked', This.updateLockstatus, This);

                    This.updateLockstatus();
                }
            }, this);
        },

        defaults: {
            name: '',
            height: 0,
            width: 0,
            locked: false,
            sendLockedStatusToServer: false
        },

        urlRoot: config.api + '/image',

        url: function () {
            // last param true, to get locked image
            if (this.get('name') && this.get('name') != ''){
                return this.urlRoot + '/' + this.get('name') + '/true';
            }

            return this.urlRoot + '/true';
        },

        parse: function (data) {
            if (data.err){
                this.err(data.err);
            }

            return data.result;
        },

        err: function (err) {
            // "No unlocked image found" ==> that is not a error we want to handle here
            if (err.code != 0){
                errorController.show('Error while parsing image response from server, error: ' + JSON.stringify(err));
            }
        },

        updateLockstatus: function () {
            if (this.updateLockstatusIntervalId){
                clearInterval(this.updateLockstatusIntervalId);
            }

            var locked = this.get('locked');
            var name = this.get('name');
            var connect = function () {
                socket.emit(name + 'setLocked', {locked: locked});
            };

            if (locked){
                this.updateLockstatusIntervalId = setInterval(connect, 5000);
            }

            connect();
        },

        markImage: function (superpixelsize, compactness, thr_col_val, x, y, label, cb) {
            $.ajax({
                type: 'POST',
                url: config.api + '/image/' + this.get('name') + '/mark/' + superpixelsize + '/' + compactness + '/' + thr_col_val + '/' + x + '/' + y + '/' + label,
                data: {
                    x: x,
                    y: y,
                    label: label
                },
                success: function (result) {
                    if(result.err){
                        return console.error('error');
                    }

                    if(cb){
                        return cb();
                    }
                }
            });
        },

        reloadContours: function(superpixelsize, compactness, thr_col_val, cb){
            $.ajax({
                type: 'POST',
                url: config.api + '/image/' + this.get('name') + '/reloadContours/' + superpixelsize + '/' + compactness + '/' + thr_col_val,
                success: function(result){
                    if(result.err){
                        return console.error('error');
                    }

                    if(cb){
                        return cb();
                    }
                }
            });
        },

        updateLockstatusIntervalId: null
    });

    return Image;
});