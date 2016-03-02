define(['Marionette', 'collections/Images'], function (Marionette, Images) {
    var OverviewController = Marionette.Object.extend({
        showAllImages: function (region) {
            OverviewController.region = region;
            OverviewController.images = new Images();

            console.log(OverviewController.images);

            OverviewController.images.fetch();
        }
    });

    return new OverviewController();
});