define(['tpl!templates/markerView.tpl', 'Marionette', 'd3', 'randomcolor', 'path', 'config'], function(markerView, Marionette, d3, randomColor, path, config) {
    var MarkerView = Marionette.ItemView.extend({
        template: markerView,

        initialize: function(image){
            this.image = image;
        },

        templateHelpers: function () {
            return {
                svg: this.image.get('svg')
            }
        },

        onDestroy: function(){
            this.image.set('locked', false);
        }
    });

    return MarkerView;
});