define(['Marionette'], function (Marionette) {
    var app;
    var Router = Marionette.AppRouter.extend({
        initialize: function (opt) {
            app = opt.app;
        },

        /**
         * Routes, can be accessed via ..router.navigate(route, options)
         */
        routes: {
            '': 'showRandomUnlockedImage',
            'overview': 'showImageOverview',
            'image/:imageName': 'showImage'
        },

        showRandomUnlockedImage: function(){
            require(['layouts/ImageNavigationLayout', 'controllers/MarkerController', 'controllers/NavigationController', 'controllers/MarkerSettingsController'], function (ImageNavigationLayout, markerController, navigationController, markerSettingsController) {
                // Create layout
                var imageNavigationLayout = new ImageNavigationLayout();

                // Load Marker to image
                markerController.showRandomUnlockedImage(imageNavigationLayout.getRegion('image'));

                // Render to main section
                app.mainRegion.show(imageNavigationLayout);

                // Load Navigation to navigation
                navigationController.showNavigation(imageNavigationLayout.getRegion('navigation'));

                // Load Settings
                markerSettingsController.showSettings(imageNavigationLayout.getRegion('settings'));
            });
        },

        showImageOverview: function () {
            require(['layouts/ImagesOverviewLayout', 'controllers/OverviewController'], function(ImagesOverviewLayout, overviewController){
                // Create layout and render to main section
                var imagesOverviewLayout = new ImagesOverviewLayout();
                app.mainRegion.show(imagesOverviewLayout);

                // Load images and render to layout
                overviewController.showAllImages(imagesOverviewLayout.getRegion('overview'));

                // Load navigation
                //TODO
            });
        },

        showImage: function(imageName){
            require(['layouts/ImageNavigationLayout', 'controllers/MarkerController', 'controllers/NavigationController', 'controllers/MarkerSettingsController'], function (ImageNavigationLayout, markerController, navigationController, markerSettingsController) {
                // Create layout and render to main section
                var imageNavigationLayout = new ImageNavigationLayout();
                app.mainRegion.show(imageNavigationLayout);

                // Load Marker to image
                markerController.showImage(imageName, imageNavigationLayout.getRegion('image'));

                // Load Navigation to navigation
                navigationController.showNavigation(imageNavigationLayout.getRegion('navigation'));

                // Load Settings
                markerSettingsController.showSettings(imageNavigationLayout.getRegion('settings'));
            });
        }
    });

    return Router;
});