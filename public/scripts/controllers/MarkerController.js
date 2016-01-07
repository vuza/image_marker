define(['Marionette', 'views/MarkerView'], function(Marionette, MarkerView){
    var MarkerController = Marionette.Object.extend({
        initialize: function(app){
            var opt = {};
            //TODO get data
            opt.image = '/images/landscape.jpg';
            opt.matrix = [];
            for(var i = 0; i < 960; i++){
                for(var y = 0; y < 500; y++){
                    opt.matrix.push({x: i, y: y});
                }
            }
            
            var markerView = new MarkerView(opt);
            app.mainRegion.show(markerView);
        }
    });

    return MarkerController;
});