define([], function(){
    return {
        api: process.env.API || 'http://localhost:3991/api/v1',
        socket: process.env.SOCKET || 'http://localhost:3000'
    };
});