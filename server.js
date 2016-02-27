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
if(!imageController.loadImages()){
    winston.error('Could not find or create image folder');
    return; // Stop program
}

/**
 * Init and start server
 */
server.use(function (req, res, next) {
    res.setHeader('Access-Control-Allow-Origin', '*');
    res.setHeader('Access-Control-Allow-Methods', 'GET, POST, OPTIONS, PUT, PATCH, DELETE');

    next();
});

server.use('/api/v1/', router);

server.listen(3991);