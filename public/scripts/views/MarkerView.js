define(['tpl!templates/markerView.tpl', 'Marionette', 'd3', 'randomcolor'], function(markerView, Marionette, d3, randomColor) {
    var MarkerView = Marionette.ItemView.extend({
        template: markerView,

        initialize: function(image){
            this.image = image;
        },

        onRender: function(){
            $(this.el).html('<image src="/images/' + this.image.get('name') + '">');

            return this;
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