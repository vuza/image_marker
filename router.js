var router = require('express').Router(),
    imageController = require('./controller/imageController');

router.get('/image/:lock', imageController.getRandomUnlockedImage);
router.get('/image/:name/:lock', imageController.getImage);
router.get('/images/:lock', imageController.getImages);

module.exports = router;