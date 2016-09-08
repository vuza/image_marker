define(['tpl!templates/navigationView.tpl', 'Marionette', 'Radio'], function(navigationView, Marionette, Radio) {
    var uiChannel;
    var NavigationView = Marionette.ItemView.extend({
        template: navigationView,

        initialize: function(){
            uiChannel = Radio.channel('uiChannel');
        },

        attributes: function () {
            return {
                'id': 'navigationView'
            };
        },

        ui: {
            nextImage: '#nextImage',
            goToOverview: '#goToOverview'
        },

        events: {
            'click @ui.nextImage': function(){
                uiChannel.trigger('click:#nextImage');
            },
            'click @ui.goToOverview': function(){
                uiChannel.trigger('click:#goToOverview');
            }
        }
    });

    return NavigationView;
});