require.config({
    baseUrl: '/scripts/',
    paths: {
        lodash: 'vendor/bower/lodash/lodash',
        jquery: 'vendor/bower/jquery/dist/jquery',
        d3: 'vendor/bower/d3/d3',
        backbone: 'vendor/bower/backbone/backbone',
        underscore: 'vendor/bower/underscore/underscore',
        Marionette: 'vendor/bower/backbone.marionette/lib/backbone.marionette',
        tpl: 'vendor/underscore-tpl/underscore-tpl',
        text: 'vendor/bower/text/text',
        randomcolor: 'vendor/bower/randomcolor/randomColor',
        async: 'vendor/bower/async/lib/async',
        socketio: 'vendor/bower/socket.io-client/socket.io',
        Radio: 'vendor/bower/backbone.radio/build/backbone.radio',
        config: 'config'
    },
    deps: ['Marionette', 'backbone', 'Router', 'App'],
    callback: function(Marionette, Backbone, Router, App){
        var app = new App();

        app.on('before:start', function(){
            Backbone.history.start({pushState: true, root: '/'});
        });

        var router = new Router({app: app});

        app.start();
    }
});