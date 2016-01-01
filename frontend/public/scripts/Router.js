define(['Marionette'], function(Marionette){
    var app,
        router = Marionette.AppRouter.extend({
        initialize: function(opt){
            app = opt.app;
        },

        /**
         * Routes, can be accessed via ..router.navigate(route, options)
         */
        routes: {
            '': function(){
                loadDefaultWrapper();

                require(['controllers/MarkerController'], function(MarkerController){
                    new MarkerController(app);
                });
            }
        }
    });

    /**
     * Load Header, Footer, etc.
     */
    var loadDefaultWrapper = function(){
        //Load header, footer, etc.
    };

    return router;
});