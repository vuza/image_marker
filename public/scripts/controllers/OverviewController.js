define(['Marionette', 'collections/Images', 'views/OverviewCollectionView'], function (Marionette, Images, OverviewCollectionView) {
    var OverviewController = Marionette.Object.extend({
        showAllImages: function (region) {
            OverviewController.region = region;
            OverviewController.images = new Images();

            OverviewController.images.fetch({
                success: function(){
                    var overviewCollectionView = new OverviewCollectionView({
                        collection: OverviewController.images
                    });
                    OverviewController.region.show(overviewCollectionView);
                }
            });
        }
    });

    return new OverviewController();
});