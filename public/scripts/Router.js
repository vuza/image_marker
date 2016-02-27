define(['Marionette'], function(Marionette){
    var app,
        router = Marionette.AppRouter.extend({
        initialize: function(opt){
            app = opt.app;
        },

        /**
         * Routes, can be accessed via ..router.navigate(route, options)
         */
        routes: {
            '': function(){
                loadDefaultWrapper();

                require(['layouts/ImageNavigationLayout', 'controllers/MarkerController', 'controllers/NavigationController'], function(ImageNavigationLayout, markerController, navigationController){
                    // Create layout and render to main section
                    var imageNavigationLayout = new ImageNavigationLayout();
                    app.mainRegion.show(imageNavigationLayout);

                    // Load Marker to image
                    markerController.show(imageNavigationLayout.getRegion('image'));

                    // Load Navigation to navigation
                    navigationController.show(imageNavigationLayout.getRegion('navigation'));
                });
            }
        }
    });

    /**
     * Load Header, Footer, etc.
     */
    var loadDefaultWrapper = function(){
        //Load header, footer, etc.
    };

    return router;
});