var router = require('express').Router(),
    imageController = require('./controller/imageController');

router.get('/image', imageController.getRandomUnlockedImage);
router.get('/image/:name', imageController.getImage);

module.exports = router;