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
    url = require('url'),
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

    markImage: function(req, res){
        var superpixelsize = req.params['superpixelsize'];
        var compactness = req.params['compactness'];
        var thr_col_val = req.params['thr_col_val'];
        var name = req.params['name'];
        var x = req.params['x'];
        var y = req.params['y'];
        var label = req.params['label'];
        var imagePath = path.join(config.images.absoluteLocation, name);

        im_processor.fillSegment(imagePath, x, y, label, superpixelsize, compactness, thr_col_val, function(err){
            console.log(err);

            res.status(200).send({err: null});
        });
    },

    loadImages: function (cb) {
        winston.debug('Load images');

        var i = 0;
        try {
            fs.readdirSync(config.images.absoluteLocation).forEach(function (file) {
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
                mkdirp.sync(config.images.absoluteLocation);
            } catch (e) {
                // Could not create image folder, return false

                return cb(e);
            }
        }

        return cb(null);
    },

    createLabelsForLoadedImages: function (cb) {
        if (!fs.existsSync(config.labels.absoluteLocation)) {
            // No labels ordner, create it!

            mkdirp.sync(config.labels.absoluteLocation);
        }

        var tasks = [];
        Object.keys(images).every(function (name) {
            var labelName = 'label_colored.' + ImageController.stripImageFileExtensionAndImagePrefix(images[name].name) + '.png';

            if (!fs.existsSync(path.join(config.images.absoluteLocation, labelName))) {
                tasks.push(function (cb) {
                    im_processor.prepareImg(images[name].path, function () {
                        images[name].label = labelName;

                        cb(null);
                    });
                });
            }

            return true;
        });

        // Run tasks
        async.series(tasks, function (err) {
            cb(err);
        });
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
        async.series(tasks, function (err) {
            cb(err);
        });
    },

    createSvg: function (image, cb) {
        winston.debug('create svg');

        d3.select(document.body).html("");

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
            .attr('xlink:xlink:href', url.resolve(config.images.publicDomain, path.join(config.images.publicRelativeLocation, image.name)))
            .attr('width', image.width)
            .attr('height', image.height);

        defs.append('pattern')
            .attr('id', 'label')
            .attr('patternUnits', 'userSpaceOnUse')
            .attr('width', image.width)
            .attr('height', image.height)
            .append('image')
            .attr('xlink:xlink:href', url.resolve(config.images.publicDomain, path.join(config.images.publicRelativeLocation, 'labels', image.label)))
            .attr('width', image.width)
            .attr('height', image.height);

        svg.append('rect')
            .attr('x', 0)
            .attr('y', 0)
            .attr('width', image.width)
            .attr('height', image.height)
            .attr('fill', 'url(#image)');

        svg.append('rect')
            .attr('x', 0)
            .attr('y', 0)
            .attr('width', image.width)
            .attr('height', image.height)
            .attr('fill', 'url(#label)');

        if (cb) cb(null, d3.select(document.body).html());
    },

    stripPrivateImageInfo: function (image) {
        extend({}, image);
        delete image.matrix;
        delete image.path;

        return image;
    },

    stripImageFileExtensionAndImagePrefix: function (name) {
        var nameSplit = name.split('.');
        nameSplit.shift();
        nameSplit.pop();
        name = nameSplit.join('.');

        return name;
    }
};

module.exports = ImageController;