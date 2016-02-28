var fs = require('fs'),
    sizeOf = require('image-size'),
    im_processor = require('./../im_processor/build/Release/im_processor'),
    Image = require('./../models/Image'),
    mkdirp = require('mkdirp'),
    config = require('./../config'),
    wiston = require('winston'),
    async = require('async'),
    images = {};

var ImageController = {
    getRandomUnlockedImage: function (req, res) {
        wiston.verbose('Get a random unlocked image');

        var image = null;

        Object.keys(images).every(function (name) {
            if (!images[name].locked) {
                image = images[name];
                image.locked = true;

                return false;
            }

            return true;
        });

        if (image) {
            res.status(200).send({err: null, result: image});
        } else {
            wiston.debug('No unlocked image found');
            res.status(200).send({err: {msg: 'No unlocked image found', code: 0}, result: null});
        }
    },

    getImage: function (req, res) {
        var image = images[req.params['name']];
        wiston.verbose('Get image: ' + image);

        if (image) {
            image.locked = true;
            res.status(200).send({err: null, result: image});
        } else
            res.status(200).send({err: {msg: 'Image ' + req.params['name'] + ' not found', code: 2}, result: null});
    },

    loadImages: function (cb) {
        wiston.debug('Load images');

        var i = 0;
        try {
            fs.readdirSync(config.imageLocation).forEach(function (file) {
                var path = config.imageLocation + '/' + file;
                if (!fs.lstatSync(path).isDirectory()) {
                    var dim = sizeOf(path);

                    images[file] = new Image(file, false, dim['width'], dim['height']);

                    i++;
                }
            });
        } catch (e) {
            // There is no image folder, create it

            try {
                mkdirp.sync(config.imageLocation);
            } catch (e) {
                // Could not create image folder, return false

                cb(true);
            }
        }

        // Load matrices

        // Create tasks
        var tasks = [];
        Object.keys(images).every(function (name) {
            tasks.push(
                function (cb) {
                    ImageController.loadMatrix(images[name], function (err, image) {
                        // Save image to images
                        images[image.name] = image;

                        cb(err);
                    });
                }
            );

            return true;
        });

        // Run tasks
        async.parallel(tasks, function (err) {
            cb(err);
        });
    },

    loadMatrix: function (image, cb) {
        im_processor.getImageMatrix(image.name, function (err, result) {
            if (cb)
                if (err)
                    cb(err);
                else {
                    image.matrix = result;
                    cb(null, image);
                }
        });
    }
};

module.exports = ImageController;