define(['Marionette', 'views/NavigationView'], function(Marionette, NavigationView){
    var NavigationController = Marionette.Object.extend({
        showNavigation: function(region){
            region.show(new NavigationView());
        }
    });

    return NavigationController;
});