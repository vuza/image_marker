define(['tpl!templates/markerSettingsView.tpl', 'Marionette', 'Radio', 'jquery'], function (markerSettingsView, Marionette, Radio, $) {
    var settingsChannel = Radio.channel('settingsChannel');

    var MarkerView = Marionette.ItemView.extend({
        template: markerSettingsView,

        initialize: function(){
            MarkerView = this;
        },

        ui: {
            superpixelsize: '#superpixelsize',
            compactness: '#compactness',
            thr_col_val: '#thr_col_val',
            label: '#label'
        },

        events: {
            'change @ui.thr_col_val, @ui.compactness, @ui.superpixelsize': function(){
                settingsChannel.trigger('settingsChanged');
            }
        },

        onShow: function(){
            settingsChannel.reply('superpixelsize', function(){
                return $(MarkerView.ui.superpixelsize).val();
            });
            settingsChannel.reply('compactness', function(){
                return $(MarkerView.ui.compactness).val();
            });
            settingsChannel.reply('thr_col_val', function(){
                return $(MarkerView.ui.thr_col_val).val();
            });
            settingsChannel.reply('label', function(){
                return $(MarkerView.ui.label).val();
            });
        }
    });

    return MarkerView;
});