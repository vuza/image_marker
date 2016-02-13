define(['Marionette', 'views/MarkerView', 'models/Image', 'async', 'Radio'], function (Marionette, MarkerView, Image, async, Radio) {
    var uiChannel,
        MarkerController = Marionette.Object.extend({
            initialize: function (region) {
                uiChannel = Radio.channel('uiChannel');
                uiChannel.on('click:#nextImage', this.showRandomUnlockedImage);

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

    return MarkerController;
});