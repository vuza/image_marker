define(['tpl!templates/markerView.tpl', 'Marionette', 'd3', 'randomcolor', 'path', 'config'], function(markerView, Marionette, d3, randomColor, path, config) {
    var MarkerView = Marionette.ItemView.extend({
        template: markerView,

        initialize: function(image){
            this.image = image;
        },

        templateHelpers: function () {
            return {
                src: path.join(config.imagePath, this.image.get('name')),
                locked: this.image.get('locked')
            }
        },

        onDestroy: function(){
            this.image.set('locked', false);
        },

        attributes: function () {
            return {
                'id': 'markerView'
            }
        }
    });

    return MarkerView;
});