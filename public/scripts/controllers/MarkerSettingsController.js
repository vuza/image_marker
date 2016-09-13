define(['Marionette', 'views/MarkerSettingsView'], function (Marionette, MarkerSettingsView) {
    var MarkerSettingsController = Marionette.Object.extend({
        showSettings: function (region) {
            MarkerSettingsController.region = region;

            MarkerSettingsController.region.show(new MarkerSettingsView());
        }
    });

    return new MarkerSettingsController();
});