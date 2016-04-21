define(['Marionette'], function(Marionette){
    var App = Marionette.Application.extend({
        regions: {
            mainRegion: '#mainRegion',
            errorRegion: '#errorRegion'
        },

        ui: {
            loadingNotification: '#loadingNotification'
        }
    });

    return App;
});