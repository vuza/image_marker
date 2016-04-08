define(['Marionette', 'tpl!templates/imagesOverviewLayout.tpl'], function(Marionette, imagesOverviewLayout){
    var ImagesOverviewLayout = Marionette.LayoutView.extend({
        template: imagesOverviewLayout,

        regions: {
            overview: '#overview',
            navigation: '#navigation'
        }
    });

    return ImagesOverviewLayout;
});