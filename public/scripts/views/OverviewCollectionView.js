define(['tpl!templates/imageView.tpl', 'config', 'path'], function(imageTemplate, config, path){
    var ImageView = Marionette.ItemView.extend({
        template: imageTemplate,

        initialize: function(){
            var This = this;
            this.listenTo(This.model, 'change:locked', function(){
                if(This.model.get('locked'))
                    $(This.$el).addClass('locked');
                else
                    $(This.$el).removeClass('locked');
            });
        },

        attributes: function () {
            var This = this;
            return {
                'class': function(){
                    var classes = ['imageView'];
                    if(This.model.get('locked'))
                        classes.push('locked');

                    return classes.join(' ');
                }
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