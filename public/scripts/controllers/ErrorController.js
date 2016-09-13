define(['Marionette', 'views/ErrorView', 'Radio'], function (Marionette, ErrorView, Radio) {
    var regionsChannel;
    var ErrorController = Marionette.Object.extend({

        initialize: function () {
            // Request region, make sure there is somebody to reply
            regionsChannel = Radio.channel('regionsChannel');
            ErrorController.region = regionsChannel.request('errorRegion');
        },

        show: function(error){
            if(error){
                console.error(error);
            }

            // Show View
            ErrorController.region.show(new ErrorView(error));
        }
    });

    return new ErrorController();
});