define(['Marionette', 'views/MarkerView', 'models/Image', 'async', 'Radio'], function (Marionette, MarkerView, Image, async, Radio) {
    var uiChannel,
        markerChannel,
        MarkerController = Marionette.Object.extend({
            initialize: function () {
                uiChannel = Radio.channel('uiChannel');
                markerChannel = Radio.channel('markerChannel');

                uiChannel.on('click:#nextImage', this.showRandomUnlockedImage); //TODO außer wir wechseln dann zur Übersicht --> zentralisieren!
            },

            showRandomUnlockedImage: function (region) {
                MarkerController.region = region;

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