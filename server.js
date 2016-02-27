var router = require('./router'),
    imageController = require('./controller/imageController'),
    config = require('./config'),
    winston = require('winston'),
    server = require('express')();

/**
 * Set up logging
 */
winston.cli();
winston.level = config.logging.level;
winston.add(winston.transports.File, { filename: config.logging.location + '/' + config.logging.fileName });

/**
 * Load images
 */
imageController.loadImages(function(err){
    if(err)
        winston.error('Could not find or create image folder');

    /**
     * Init and start server
     */
    server.use(function (req, res, next) {
        res.setHeader('Access-Control-Allow-Origin', '*');
        res.setHeader('Access-Control-Allow-Methods', 'GET, POST, OPTIONS, PUT, PATCH, DELETE');

        next();
    });

    server.use('/api/v1/', router);

    server.listen(config.listenPort, function(){
        winston.info('Start listening at ' + config.listenPort);
    });
});