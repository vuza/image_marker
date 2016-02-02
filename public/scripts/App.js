define(['Marionette'], function(Marionette){
    var App = Marionette.Application.extend({
        regions: {
            mainRegion: '#mainRegion'
        }
    });

    return App;
});