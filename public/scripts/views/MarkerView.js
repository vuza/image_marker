define(['tpl!templates/markerView.tpl', 'Marionette', 'd3', 'randomcolor', 'path', 'config', 'jquery', 'Radio'], function (markerView, Marionette, d3, randomColor, path, config, $, Radio) {
    var settingsChannel = Radio.channel('settingsChannel');

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

            // Request labeling parameter
            var superpixelsize = settingsChannel.request('superpixelsize');
            var compactness = settingsChannel.request('compactness');
            var thr_col_val = settingsChannel.request('thr_col_val');
            var label = settingsChannel.request('label');

            //TODO show loading time

            this.image.markImage(superpixelsize, compactness, thr_col_val, relativeClickPosition.x, relativeClickPosition.y, label, function(){
                var $label = $image.find('defs #label image');
                $label.attr('xlink:href', $label.attr('xlink:href') + '?cachebreaker=' + new Date().getTime());

                console.log('reloaded'); //TODO remove
            });
        }
    });

    return MarkerView;
});