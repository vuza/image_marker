define(['tpl!templates/errorView.tpl', 'Marionette'], function(errorView, Marionette) {
    var ErrorView = Marionette.ItemView.extend({
            template: errorView,

            attributes: function () {
                return {
                    'id': 'errorView'
                }
            }
        });

    return ErrorView;
});