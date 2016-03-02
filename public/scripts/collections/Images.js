define(['backbone', 'models/Image', 'config', 'underscore'], function(Backbone, Image, config, _){
    var Images = Backbone.Collection.extend({
        model: Image,

        urlRoot: config.api + '/images',

        url: function(){
            return this.urlRoot + '/false'; // False because we do not want the images to be locked
        },

        parse: function(data){
            if(data.err) this.err(data.err);

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