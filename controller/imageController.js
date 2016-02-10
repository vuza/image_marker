var fs = require('fs'),
    sizeOf = require('image-size'),
    merge = require('merge'),
    files = {};

module.exports = {
    getRandomUnlockedImage: function(req, res){
        var file = false;

        Object.keys(files).every(function(name){
            if(!files[name].lock){
                file = files[name];
                return false;
            }

            return true;
        });

        //TODO lock image ?

        if(file)
            res.status(200).send({err: null, result: file});
        else
            res.status(200).send({err: {msg: 'No unlocked image found', code: 0}, result: null});
    },

    getImage: function(req, res){
        if(files[req.params['name']])
            res.status(200).send({err: null, result: files[req.params['name']]});
        else
            res.status(200).send({err: {msg: 'Image ' + req.params['name'] + ' not found', code: 0}, result: null});
    },

    loadImages: function(){
        var i = 0;
        fs.readdirSync('./public/images').forEach(function(file) {
            var dim = sizeOf('./public/images/' + file);
            files[file] = merge({name: file, lock: false}, dim);
            i++;
        });
    }
};