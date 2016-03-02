define(['backbone', 'models/Image', 'config'], function(Backbone, Image, config){
    var Images = Backbone.Collection.extend({
        model: Image,

        urlRoot: config.api + '/images',

        url: function(){
            return this.urlRoot + '/false'; // False because we do not want the images to be locked
        },

        parse: function(data){
            if(data.err) this.err(data.err);
            return data.result;
        }
    });

    return Images;
});