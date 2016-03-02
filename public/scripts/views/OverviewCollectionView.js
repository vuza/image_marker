define(['tpl!templates/imageView.tpl'], function(imageTemplate){
    var ImageView = Marionette.ItemView.extend({
        template: imageTemplate
    });

    var OverviewCollectionView = Marionette.CollectionView.extend({
        childView: ImageView
    });

    return OverviewCollectionView;
});