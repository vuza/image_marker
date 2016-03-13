define(['tpl!templates/imageView.tpl', 'config', 'path'], function(imageTemplate, config, path){
    var ImageView = Marionette.ItemView.extend({
        template: imageTemplate,

        initialize: function(){
            var This = this;
            this.listenTo(This.model, 'change:locked', function(){
                if(This.model.get('locked'))
                    $(This.$el).setClass('locked');
                else
                    $(This.$el).removeClass('locked');
            });
        },

        attributes: function () {
            return {
                'class': this.model.get('locked')?'locked':''
            }
        },

        templateHelpers: function () {
            return {
                src: path.join(config.imagePath, this.model.get('name')),
                locked: this.model.get('locked')
            }
        }
    });

    var OverviewCollectionView = Marionette.CollectionView.extend({
        childView: ImageView
    });

    return OverviewCollectionView;
});