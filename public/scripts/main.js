require.config({
    baseUrl: '/scripts/',
    paths: {
        jquery: 'vendor/jquery/dist/jquery',
        d3: 'vendor/d3/d3',
        backbone: 'vendor/backbone/backbone',
        underscore: 'vendor/underscore/underscore',
        Marionette: 'vendor/backbone.marionette/lib/backbone.marionette',
        tpl: 'vendor/underscore-tpl/underscore-tpl',
        text: 'vendor/text/text',
        randomcolor: 'vendor/randomcolor/randomColor',
        async: 'vendor/async/lib/async',
        socketio: 'vendor/socket.io-client/socket.io',
        Radio: 'vendor/backbone.radio/build/backbone.radio'
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