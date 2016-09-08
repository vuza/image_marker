define(['Marionette', 'views/MarkerView', 'models/Image', 'async', 'Radio'], function (Marionette, MarkerView, Image, async, Radio) {
    var controllerChannel = Radio.channel('controllerChannel'),
        MarkerController = Marionette.Object.extend({
            showRandomUnlockedImage: function (region) {
                MarkerController.region = region;

                var image = new Image({
                    sendLockedStatusToServer: true
                });

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
                    showImage,
                    // Set url
                    function(image, cb){
                        Radio.channel('router').trigger('changeUrl', '/image/' + image.get('name'));
                        cb(null);
                    }
                ]);
            },

            showImage: function(imageName, region){
                MarkerController.region = region;

                var image = new Image({
                    sendLockedStatusToServer: true,
                    name: imageName
                });

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
                    showImage
                ]);
            },

            reloadContours: function(){
                MarkerController.markerView.reloadContours();
            }
        });

    var showImage = function(image, cb){
        MarkerController.markerView = new MarkerView(image);
        MarkerController.region.show(MarkerController.markerView);
        cb(null, image);
    };

    return new MarkerController();
});