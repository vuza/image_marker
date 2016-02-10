define(['models/Model'], function(Model){
    var Image = Model.extend({
        defaults: {
            name: '',
            matrix: []
        },

        urlRoot: 'http://localhost:3991/api/v1/image',

        url: function(){
            if(this.get('name') && this.get('name') != '')
                return this.urlRoot + '/' + this.get('name');

            return this.urlRoot;
        },

        err: function(err){
            console.log('oh we got an error, see: ' + JSON.stringify(err)); //TODO implement proper error handling
        }
    });

    return Image;
});