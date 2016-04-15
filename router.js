var router = require('express').Router(),
    imageController = require('./controller/imageController');

// Returns any free picture and sets lock to :lock
router.get('/image/:lock', imageController.getRandomUnlockedImage);

// Returns the picture with the name :name and sets lock to :lock
router.get('/image/:name/:lock', imageController.getImage);

// Mark image with name :name
router.post('/image/:name/mark/:x/:y/:label', imageController.markImage);

// Get all images and set lock to :lock
router.get('/images/:lock', imageController.getImages);

module.exports = router;