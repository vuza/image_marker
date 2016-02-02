var router = require('./router'),
    imageController = require('./controller/imageController'),
    server = require('express')();

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