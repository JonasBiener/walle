const WebSocket = require('ws');
const server = new WebSocket.Server({port: '8080'});

console.log('Server started up');

server.on('connection', (socket) => {
    console.log('New socket opened');
    socket.on('message', (message) => {
        console.log(message.toString());    
        socket.send('Response'); 
    });
});