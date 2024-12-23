const WebSocket = require('ws');
const server = new WebSocket.Server({port: '8080'});

console.log('Server started up');

server.on('connection', (socket) => {
    console.log('New socket opened');
    socket.on('message', (message) => {
        let msg = message.toString();
        console.log(msg); 
        if (msg === 'CLOSE'){
            console.log('Socket closed');
            return;
        }
        let parts = msg.split(' ');
        if (parts.length == 2) {
            let response = `Set ${parts[0]} to ${parts[1]}`;
            socket.send(response);
            return;
        }
        socket.send('UNKNOWN'); 
    });
});