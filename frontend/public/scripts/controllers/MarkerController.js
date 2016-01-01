define(['Marionette', 'views/MarkerView'], function(Marionette, MarkerView){
    var MarkerController = Marionette.Object.extend({
        initialize: function(app){
            var markerView = new MarkerView();
            app.mainRegion.show(markerView);
        }
    });

    return MarkerController;
});