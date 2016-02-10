var fs = require('fs'),
    sizeOf = require('image-size'),
    merge = require('merge'),
    im_processor = require('./../im_processor/build/Release/addon'),
    files = {};

var ImageController = {
    getRandomUnlockedImage: function (req, res) {
        var file = false;

        Object.keys(files).every(function (name) {
            if (!files[name].lock) {
                file = files[name];
                return false;
            }

            return true;
        });

        if (file)
            ImageController.loadMatrix(file, function (err, file) {
                if (err)
                    res.status(200).send({err: {msg: 'Could no load image matrix', code: 1}, result: null});
                else
                    res.status(200).send({err: null, result: file});
            });
        else
            res.status(200).send({err: {msg: 'No unlocked image found', code: 0}, result: null});
    },

    getImage: function (req, res) {
        var file = files[req.params['name']];
        if (file)
            ImageController.loadMatrix(file, function (err, file) {
                if (err)
                    res.status(200).send({err: {msg: 'Could no load image matrix', code: 1}, result: null});
                else
                    res.status(200).send({err: null, result: file});
            });
        else
            res.status(200).send({err: {msg: 'Image ' + req.params['name'] + ' not found', code: 0}, result: null});
    },

    loadImages: function () {
        var i = 0;
        fs.readdirSync('./public/images').forEach(function (file) {
            var dim = sizeOf('./public/images/' + file);
            files[file] = merge({name: file, lock: false}, dim);
            i++;
        });
    },

    loadMatrix: function (image, cb) {
        im_processor.getImageMatrix(image.name, function (err, result) {
            console.log(result);
            //if(cb) cb(null, merge({matrix: result}, image));
        });

        cb(null, image);
    }
};

module.exports = ImageController;