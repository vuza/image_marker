define(['tpl!templates/markerView.tpl', 'Marionette', 'd3', 'randomcolor', 'path', 'config', 'jquery', 'Radio'], function (markerView, Marionette, d3, randomColor, path, config, $, Radio) {
    var settingsChannel = Radio.channel('settingsChannel');
    var notificationChannel = Radio.channel('notificationChannel');

    var MarkerView = Marionette.ItemView.extend({
        template: markerView,

        initialize: function (image) {
            this.image = image;
            MarkerView = this;
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
            // If image is locked, don't let user mark it
            if(!$.contains(this.ui.image[0], event.target) || MarkerView.loading){
                return;
            }

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

            // Lock view and show loading
            notificationChannel.trigger('loading:show');
            MarkerView.loading = true;

            this.image.markImage(superpixelsize, compactness, thr_col_val, relativeClickPosition.x, relativeClickPosition.y, label, function(){
                var $label = $image.find('defs #label image');
                $label.attr('xlink:href', $label.attr('xlink:href') + '?cachebreaker=' + new Date().getTime());

                // Unlock view and hide loading
                notificationChannel.trigger('loading:hide');
                MarkerView.loading = false;
            });
        }
    });

    return MarkerView;
});