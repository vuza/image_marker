define(['Marionette', 'views/MarkerView', 'models/Image', 'async'], function(Marionette, MarkerView, Image, async){
    var MarkerController = Marionette.Object.extend({
        initialize: function(app){
            var image = new Image({name: 'image1.jpg'});

            async.waterfall([
                function(cb){
                    image.fetch({ success: function(image){
                        cb(null, image);
                    }});
                },
                function(image, cb){
                    app.mainRegion.show(new MarkerView(image));
                    cb();
                }
            ]);
        }
    });

    return MarkerController;
});