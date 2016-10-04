define(['backbone', 'models/Image', 'config', 'underscore', 'controllers/ErrorController'], function(Backbone, Image, config, _, errorController){
    var Images = Backbone.Collection.extend({
        model: Image,

        urlRoot: config.api + '/images',

        url: function(){
            return this.urlRoot;
        },

        err: function (err) {
            errorController.show('An error occurred: ' + JSON.stringify(err));
        },

        parse: function(data){
            if(data.err){
                this.err(data.err);
            }

            var images = [];
            _.each(data.result, function(imageData){
                var image = new Image(imageData);
                images.push(image);
            });

            return images;
        }
    });

    return Images;
});