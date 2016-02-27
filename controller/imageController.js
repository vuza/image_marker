var fs = require('fs'),
    sizeOf = require('image-size'),
    merge = require('merge'),
    im_processor = require('./../im_processor/build/Release/im_processor'),
    Image = require('./../models/Image'),
    mkdirp = require('mkdirp'),
    config = require('./../config'),
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
            res.status(200).send({err: {msg: 'Image ' + req.params['name'] + ' not found', code: 2}, result: null});
    },

    loadImages: function () {
        var i = 0;
        try{
            fs.readdirSync(config.imageLocation).forEach(function (file) {
                var image = config.imageLocation + '/' + file;
                if(!fs.lstatSync(image).isDirectory()){
                    var dim = sizeOf(image);

                    images[file] = new Image(file, false, dim['width'], dim['height']);

                    i++;
                }
            });
        } catch(e){
            // There is no image folder, create it

            try{
                mkdirp.sync(config.imageLocation);
            } catch(e){
                // Could not create image folder, return false

                return false;
            }
        }

        return true;
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