define(['Marionette', 'views/MarkerView', 'models/Image', 'async', 'Radio'], function (Marionette, MarkerView, Image, async, Radio) {
    var controllerChannel = Radio.channel('controllerChannel'),
        MarkerController = Marionette.Object.extend({
            showRandomUnlockedImage: function (region) {
                MarkerController.region = region;

                var image = new Image();

                async.waterfall([
                    // Load image
                    function (cb) {
                        image.fetch({
                            success: function (image) {
                                cb(null, image);
                            }
                        });
                    },
                    // Check if got image from server
                    function(image, cb){
                        if(image.get('name') == '')
                            controllerChannel.trigger('noUnlockedImageFound');

                        cb(null, image);
                    },
                    // Show image
                    function (image, cb) {
                        MarkerController.region.show(new MarkerView(image));
                        cb(null);
                    }
                ]);
            }
        });

    return new MarkerController();
});