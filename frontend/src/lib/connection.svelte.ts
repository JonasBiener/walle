let socket: WebSocket;

let isConnectedState = $state(false);

export function isConnected() {
    return isConnectedState;
}

export function activateConnection() {
    if (isConnectedState) alert("Can't activate. The connection is active.");
    socket = new WebSocket("ws://127.0.0.1:8080");
    socket.onmessage = ({ data }) => {
        console.log(data);
    };
    isConnectedState = true;
}

export function sendControl(controlVar: string, value: string) {
    if (!isConnectedState || socket.readyState !== socket.OPEN) return;
    try { socket.send(controlVar + " " + value); }
    catch (error) {}
}

export function deactivateConnection() {
    if (!isConnectedState || socket.readyState !== socket.OPEN) alert("Can't deactivate. The connection is inactive.");
    socket.send("CLOSE");
    socket.close();
    isConnectedState = false;
}