var fs = require('fs'),
    sizeOf = require('image-size'),
    merge = require('merge'),
    im_processor = require('./../im_processor/build/Release/im_processor'),
    Image = require('./../models/Image'),
    images = {};

var ImageController = {
    getRandomUnlockedImage: function (req, res) {
        var image = false;

        Object.keys(images).every(function (name) {
            if (!images[name].locked) {
                image = images[name];
                return false;
            }

            return true;
        });

        if (image)
            ImageController.loadMatrix(image, function (err, image) {
                if (err)
                    res.status(200).send({err: {msg: 'Could no load image matrix', code: 1}, result: null});
                else {
                    image.locked = true;
                    res.status(200).send({err: null, result: image});
                }
            });
        else
            res.status(200).send({err: {msg: 'No unlocked image found', code: 0}, result: null});
    },

    getImage: function (req, res) {
        var image = images[req.params['name']];
        if (image)
            ImageController.loadMatrix(image, function (err, image) {
                if (err)
                    res.status(200).send({err: {msg: 'Could no load image matrix', code: 1}, result: null});
                else {
                    image.locked = true;
                    res.status(200).send({err: null, result: image});
                }
            });
        else
            res.status(200).send({err: {msg: 'Image ' + req.params['name'] + ' not found', code: 0}, result: null});
    },

    loadImages: function () {
        var i = 0;
        fs.readdirSync('./public/images').forEach(function (file) {
            if(!fs.lstatSync('./public/images/' + file).isDirectory()){
                var dim = sizeOf('./public/images/' + file);

                images[file] = new Image(file, false, dim['width'], dim['height']);

                i++;
            }
        });
    },

    loadMatrix: function (image, cb) {
        im_processor.getImageMatrix(image.name, function (err, result) {
            if(cb)
                if(err)
                    cb(err);
                else
                    cb(null, merge({matrix: result}, image));
        });
    }
};

module.exports = ImageController;