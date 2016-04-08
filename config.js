var path = require('path');

module.exports = {
    images: {
        publicRelativeLocation: '/images',
        relativeLocation: './public/images',
        absoluteLocation: path.join(path.dirname(process.mainModule.filename), '/public/images/')
    },
    imageLocation: './public/images',
    logging: {
        level: 'verbose',
        location: '/var/log/image_marker',
        fileName: 'application.log'
    },
    listenPort: 3991,
    socket: {
        port: 3000
    },
    labels: {
        absoluteLocation: path.join(path.dirname(process.mainModule.filename), '/public/images/labels')
    }
};