define(['backbone', 'underscore'], function(Backbone, _){
    var Model = Backbone.Model.extend({
        parse: function (data) {
            if(data.err) this.err(data.err);
            return data.result;
        },

        err: function(err){/*there is no default error handling*/}
    });

    return Model;
});