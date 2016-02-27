define(['Marionette', 'views/NavigationView'], function(Marionette, NavigationView){
    var NavigationController = Marionette.Object.extend({
        show: function(region){
            region.show(new NavigationView());
        }
    });

    return new NavigationController();
});