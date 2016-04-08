var fs = require('fs'),
    sizeOf = require('image-size'),
    im_processor = require('./../im_processor/build/Release/im_processor'),
    Image = require('./../models/Image'),
    mkdirp = require('mkdirp'),
    config = require('./../config'),
    winston = require('winston'),
    async = require('async'),
    d3 = require('d3'),
    path = require('path'),
    document = require('jsdom').jsdom(),
    extend = require('util')._extend,
    images = {};

var ImageController = {
    getRandomUnlockedImage: function (req, res) {
        winston.verbose('Get a random unlocked image');
        var lock = (req.params['lock'] == 'true');

        var image = null;

        Object.keys(images).every(function (name) {
            if (!images[name].locked) {
                image = images[name];

                image.wasLockedBeforeRequested = image.locked || false;

                if (lock)
                    image.locked = true;

                return false;
            }

            return true;
        });

        if (image) {
            res.status(200).send({err: null, result: ImageController.stripPrivateImageInfo(image)});
        } else {
            winston.debug('No unlocked image found');
            res.status(200).send({err: {msg: 'No unlocked image found', code: 0}, result: null});
        }
    },

    getImage: function (req, res) {
        var image = images[req.params['name']],
            lock = (req.params['lock'] == 'true');

        winston.verbose('Get image: ' + image);

        if (image) {
            image.wasLockedBeforeRequested = image.locked || false;

            if (lock)
                image.locked = true;

            res.status(200).send({err: null, result: ImageController.stripPrivateImageInfo(image)});
        } else
            res.status(200).send({err: {msg: 'Image ' + req.params['name'] + ' not found', code: 2}, result: null});
    },

    getImages: function (req, res) {
        winston.verbose('Getting images');

        var lock = (req.params['lock'] == 'true');

        var tmp_images = [];

        Object.keys(images).every(function (name) {
            tmp_images.push(ImageController.stripPrivateImageInfo(images[name]));

            return true;
        });

        if (tmp_images.length > 0) {
            res.status(200).send({err: null, result: tmp_images});
        } else {
            res.status(200).send({err: {msg: 'No images found at all', code: 3}, result: null});
        }
    },

    loadImages: function (cb) {
        winston.debug('Load images');

        var i = 0;
        try {
            fs.readdirSync(config.images.relativeLocation).forEach(function (file) {
                var imagePath = path.join(config.images.absoluteLocation, file);
                if (!fs.lstatSync(imagePath).isDirectory()) {
                    var dim = sizeOf(imagePath);

                    images[file] = new Image(file, false, dim['width'], dim['height'], imagePath);

                    i++;
                }
            });
        } catch (e) {
            // There is no image folder, create it

            try {
                mkdirp.sync(config.images.relativeLocation);
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
        async.series(tasks, function (err) {
            cb(err);
        });
    },

    loadMatrix: function (image, cb) {
        im_processor.getImageMatrix(image.path, 1, 1.0, 1, function (err, result) {
            if (cb)
                if (err)
                    cb(err);
                else {
                    var matrix = JSON.parse(result);
                    matrix = matrix.data;
                    image.matrix = matrix;
                    cb(null, image);
                }
        });
    },

    stripPrivateImageInfo: function (image) {
        extend({}, image);
        delete image.matrix;
        delete image.path;

        return image;
    },

    createAllSvgs: function (cb) {
        // Load svgs

        // Create tasks
        var tasks = [];
        Object.keys(images).every(function (name) {
            tasks.push(
                function (cb) {
                    ImageController.createSvg(images[name], function (err, svg) {
                        // Save image to images
                        images[name].svg = svg;

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

    createSvg: function (image, cb) {
        winston.debug('create svg');

        // create the svg
        var svg = d3.select(document.body).append("svg")
            .attr('width', image.width)
            .attr('height', image.height);

        svg.append('g');

        // add the image
        var defs = svg.append("defs");

        defs.append('pattern')
            .attr('id', 'image')
            .attr('patternUnits', 'userSpaceOnUse')
            .attr('width', image.width)
            .attr('height', image.height)
            .append('image')
            .attr('xlink:href', path.join(config.images.publicRelativeLocation, image.name))
            .attr('width', image.width)
            .attr('height', image.height);

        svg.append('rect')
            .attr('x', 0)
            .attr('y', 0)
            .attr('width', image.width)
            .attr('height', image.height)
            .attr('fill', 'url(#image)');

        winston.debug('create dots at svg');

        /*svg.selectAll('.dot')
            .data(image.matrix)
            .enter()
            .append('circle')
            .attr('class', 'dot')
            .attr('r', 1)
            .attr('cx', function (d) {
                return d.x;
            })
            .attr('cy', function (d) {
                return d.y;
            })
            .style('fill', function (d) {
                console.log('HI');
                if (d.isContour) {
                    return '#000';
                } else if (d.label == 7) {
                    return '#ef8220';
                }

                // Default
                return '#fff';
            })
            .attr('fill-opacity', 0.5);*/

        if (cb) cb(null, d3.select(document.body).html());
    }
};

module.exports = ImageController;