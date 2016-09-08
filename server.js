var router = require('./router');
var imageController = require('./controller/imageController');
var config = require('./config');
var winston = require('winston');
var async = require('async');
var server = require('express')();

/**
 * Set up logging
 */
winston.cli();
winston.level = config.logging.level;
winston.add(winston.transports.File, { filename: config.logging.location + '/' + config.logging.fileName });

winston.info('Starting server...');

/**
 * Register middlewares
 */
var registerMiddlewares = function(cb){
    server.use(function (req, res, next) {
        res.setHeader('Access-Control-Allow-Origin', '*');
        res.setHeader('Access-Control-Allow-Methods', 'GET, POST, OPTIONS, PUT, PATCH, DELETE');

        next();
    });

    server.use('/api/v1/', router);

    if(cb) {
        cb(null);
    }
};

/**
 * Start server
 */
var startServer = function(cb){
    server.listen(config.listenPort, function(){
        winston.info('Started listening at ' + config.listenPort);

        if(cb){
            cb(null);
        }
    });
};

async.series([
    imageController.loadImages,
    imageController.prepareLoadedImages,
    imageController.createAllSvgs,
    registerMiddlewares,
    startServer
], function(err){
    if(err){
        winston.error('Error while init and starting server: ' + JSON.stringify(err));
    } else{
        winston.info('Finished starting, ready to rock');
    }
});