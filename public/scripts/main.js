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
        path: 'vendor/bower/path/path',
        Radio: 'vendor/bower/backbone.radio/build/backbone.radio',
        config: 'config'
    },
    deps: ['Marionette', 'backbone', 'Router', 'App', 'Radio', 'controllers/MarkerController'],
    callback: function (Marionette, Backbone, Router, App, Radio, MarkerController) {
        var app = new App();

        app.on('before:start', function () {
            Backbone.history.start({pushState: true, root: '/'});
        });

        var router = new Router({app: app});

        // Start App
        app.start();

        /** Reply to requests via Radio; Control program from here */
        Radio.channel('regionsChannel')
            .reply('errorRegion', function () {
                return app.getRegion('errorRegion');
            });

        Radio.channel('router')
            .on('navigate', function (to) {
                router.navigate(to, {trigger: true});
            })
            .on('changeUrl', function(to){
                router.navigate(to, {trigger: false});
            });

        Radio.channel('uiChannel')
            .on('click:#nextImage', router.showRandomUnlockedImage)
            .on('click:#goToOverview', function(){
                router.navigate('overview', {trigger: true});
            });

        Radio.channel('controllerChannel')
            .on('noUnlockedImageFound', function(){
                router.navigate('overview', {trigger: true});
            });

        Radio.channel('notificationChannel')
            .on('loading:show', function(){
                $(app.ui.loadingNotification).show();
            })
            .on('loading:hide', function(){
                $(app.ui.loadingNotification).hide();
            });

        Radio.channel('settingsChannel')
            .on('settingsChanged', function(){
                MarkerController.reloadContours();
            });
    }
});