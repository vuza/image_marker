module.exports = {
    listenPort: 3991,
    imageLocation: './public/images',
    logging: {
        level: 'verbose',
        location: '/var/log/image_marker',
        fileName: 'application.log'
    },
    socket: {
        port: 3000
    }
};