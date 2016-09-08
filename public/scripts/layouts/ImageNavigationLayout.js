define(['Marionette', 'tpl!templates/imageNavigationLayout.tpl'], function(Marionette, imageNavigationLayout){
    var ImageNavigationLayout = Marionette.LayoutView.extend({
        template: imageNavigationLayout,

        regions: {
            image: '#image',
            navigation: '#navigation',
            settings: '#settings'
        }
    });

    return ImageNavigationLayout;
});