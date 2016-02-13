define(['tpl!templates/navigationView.tpl', 'Marionette'], function(navigationView, Marionette) {
    var NavigationView = Marionette.ItemView.extend({
        template: navigationView,

        initialize: function(){console.log(this)},

        onRender: function(){return this;},

        ui: {
            nextImage: '#nextImage'
        },

        attributes: function () {
            return {
                'id': 'navigationView'
            }
        }
    });

    return NavigationView;
});