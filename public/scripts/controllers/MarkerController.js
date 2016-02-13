define(['Marionette', 'views/MarkerView', 'models/Image', 'async'], function(Marionette, MarkerView, Image, async){
    var MarkerController = Marionette.Object.extend({
        showMarkerView: function(region){
            MarkerController.region = region;
            this.showRandomUnlockedImage();
        },

        showRandomUnlockedImage: function(){
            var image = new Image();

            async.waterfall([
                function(cb){
                    image.fetch({ success: function(image){
                        cb(null, image);
                    }});
                },
                function(image, cb){
                    MarkerController.region.show(new MarkerView(image));
                    cb();
                }
            ]);
        }
    });

    return MarkerController;
});