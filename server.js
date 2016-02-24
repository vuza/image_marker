var router = require('./router'),
    imageController = require('./controller/imageController'),
    config = require('./config'),
    winston = require('winston'),
    server = require('express')();

/**
 * Set up logging
 */
winston.level = config.logging.level;
winston.add(winston.transports.File, { filename: config.logging.location + '/' + config.logging.fileName });

/**
 * Load images
 */
imageController.loadImages();

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