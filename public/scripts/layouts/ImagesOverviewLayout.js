define(['Marionette', 'tpl!templates/imagesOverviewLayout.tpl'], function(Marionette, imagesOverviewLayout){
    var ImagesOverviewLayout = Marionette.LayoutView.extend({
        template: imagesOverviewLayout,

        regions: {
            images: '#images',
            navigation: '#navigation'
        }
    });

    return ImagesOverviewLayout;
});