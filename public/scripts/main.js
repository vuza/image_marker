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
        randomcolor: 'vendor/randomcolor/randomColor'
    },
    shim: {
        underscore: {
            exports: '_'
        },
        d3: {
            deps: ['jquery']
        },
        backbone: {
            deps: ['jquery', 'underscore'],
            exports: 'Backbone'
        },
        jquery: {
            exports: '$'
        },
        Marionette: {
            deps: ['backbone']
        },
        tpl: ['text']
    },
    deps: ['Marionette', 'backbone', 'Router'],
    callback: function(Marionette, Backbone, Router){
        var app = new Marionette.Application();

        app.on('before:start', function(){
            Backbone.history.start({pushState: true, root: '/'});
        });

        app.addRegions({
            mainRegion: "#mainRegion"
        });

        var router = new Router({app: app});

        app.start();
    }
});