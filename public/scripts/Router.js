define(['Marionette'], function (Marionette) {
    var app,
        Router = Marionette.AppRouter.extend({
            initialize: function (opt) {
                app = opt.app;
            },

            /**
             * Routes, can be accessed via ..router.navigate(route, options)
             */
            routes: {
                '': function () {
                    require(['layouts/ImageNavigationLayout', 'controllers/MarkerController', 'controllers/NavigationController'], function (ImageNavigationLayout, markerController, navigationController) {
                        // Create layout and render to main section
                        var imageNavigationLayout = new ImageNavigationLayout();
                        app.mainRegion.show(imageNavigationLayout);

                        // Load Marker to image
                        markerController.show(imageNavigationLayout.getRegion('image'));

                        // Load Navigation to navigation
                        navigationController.show(imageNavigationLayout.getRegion('navigation'));
                    });
                },

                'overview': function () {
                    console.log('welcome to overview');
                }
            }
        });

    return Router;
});