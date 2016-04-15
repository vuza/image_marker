define(['tpl!templates/markerView.tpl', 'Marionette', 'd3', 'randomcolor', 'path', 'config', 'jquery'], function (markerView, Marionette, d3, randomColor, path, config, $) {
    var MarkerView = Marionette.ItemView.extend({
        template: markerView,

        initialize: function (image) {
            this.image = image;
        },

        templateHelpers: function () {
            return {
                svg: this.image.get('svg')
            }
        },

        ui: {
            image: 'svg'
        },

        events: {
            'click': 'markImage'
        },

        onDestroy: function () {
            this.image.set('locked', false);
        },

        markImage: function (event) {
            var $image = $(this.ui.image);
            var imageOffset = $image.offset();
            var absoluteClickPosition = {x: event.clientX, y: event.clientY};
            var relativeClickPosition = {
                x: absoluteClickPosition.x - imageOffset.left,
                y: absoluteClickPosition.y - imageOffset.top
            };

            //TODO let user chose label
            var label = 1;

            //TODO show loading time

            this.image.markImage(relativeClickPosition.x, relativeClickPosition.y, label, function(){
                var $label = $image.find('defs #label image');
                $label.attr('xlink:href', $label.attr('xlink:href') + '?cachebreaker=' + new Date().getTime());
            });
        }
    });

    return MarkerView;
});