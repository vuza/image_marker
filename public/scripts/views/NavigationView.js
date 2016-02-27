define(['tpl!templates/navigationView.tpl', 'Marionette', 'Radio'], function(navigationView, Marionette, Radio) {
    var uiChannel,
        NavigationView = Marionette.ItemView.extend({
            template: navigationView,

            initialize: function(){
                uiChannel = Radio.channel('uiChannel');
            },

            attributes: function () {
                return {
                    'id': 'navigationView'
                }
            },

            ui: {
                nextImage: '#nextImage'
            },

            events: {
                'click @ui.nextImage': function(){ uiChannel.trigger('click:#nextImage'); }
            }
        });

    return NavigationView;
});