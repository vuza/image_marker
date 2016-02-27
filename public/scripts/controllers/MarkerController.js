define(['Marionette', 'views/MarkerView', 'models/Image', 'async', 'Radio'], function (Marionette, MarkerView, Image, async, Radio) {
    var uiChannel,
        MarkerController = Marionette.Object.extend({
            initialize: function () {
                uiChannel = Radio.channel('uiChannel');
                uiChannel.on('click:#nextImage', this.showRandomUnlockedImage);
            },

            show: function(region){
                MarkerController.region = region;
                this.showRandomUnlockedImage();
            },

            showRandomUnlockedImage: function () {
                var image = new Image();

                async.waterfall([
                    function (cb) {
                        image.fetch({
                            success: function (image) {
                                cb(null, image);
                            }
                        });
                    },
                    function (image, cb) {
                        MarkerController.region.show(new MarkerView(image));
                        cb();
                    }
                ]);
            }
        });

    return new MarkerController();
});