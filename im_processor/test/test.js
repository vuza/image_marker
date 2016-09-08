describe('im_processor', function(){
    var im_processor = require('./../build/Release/im_processor');

    describe('getImageMatrix', function(){
        var imagePath = '/home/marlon/Documents/Bac/prototype/im_processor/test/image.1.jpg';

        it('should load matrix from image', function(done){
            im_processor.getImageMatrix(imagePath, 1, 1.0, 1, function (err, result) {
                console.log(result); //TODO check result for correctness (?)
                done();
            });
        });
    });
});