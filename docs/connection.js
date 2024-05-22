const LED_SERVICE = "e5242354-9449-4c07-83aa-55780467604c";
const LED_STATE_CHARACTERISTIC = "b8412da8-7d45-c994-1dfb-c3f48c35f40c";

let isConnected = false;
let isServicesDiscovered = false;

// NOT FITTING IN CONTEXT
function setConnectedStatus(status) {
    const connectionStatus = document.getElementById("status_connected");
    connectionStatus.innerHTML = status;
    const connectButton = document.getElementById("btnConnect");
    connectButton.innerHTML = status ? "Disconnect" : "Connect";
    isConnected = status;
}

// NOT FITTING IN CONTEXT
function setDiscoveredStatus(status) {
    const discoveryStatus = document.getElementById("status_discovered");
    discoveryStatus.innerHTML = status;
    isServicesDiscovered = status;
}

let bluetoothDevice;
let bluetoothServer;

// NOT FITTING IN CONTEXT
function discoverOrDisconnect() {
    if (!isConnected) discover();
    else bluetoothDevice.gatt.disconnect();
}

async function discover() {
    console.log("Discovering Devices");
    try {
        let options = {filters: [
            {services: [LED_SERVICE]}
        ]};
        bluetoothDevice = await navigator.bluetooth.requestDevice(options);
        console.log("> Name: " + bluetoothDevice.name);
        console.log("> ID: " + bluetoothDevice.id);
        console.log("> Connected: " + bluetoothDevice.gatt.connected);
        connect();
    } catch (error) {
        console.warn("ERROR: " + error);
    }
}

async function connect() {
    if (isConnected) return;
    console.log("Connecting");
    try {
        bluetoothServer = await bluetoothDevice.gatt.connect();
        console.log("> Connected to: " + bluetoothServer.device.id);
        console.log("> Connected: " + bluetoothServer.connected);
        bluetoothDevice.addEventListener("gattserverdisconnected", onDisconnect);
        setConnectedStatus(true);
        discoverServicesAndCharacteristics();
    } catch (error) {
        console.warn("ERROR: " + error);
        setConnectedStatus(false);
    }
}

function onDisconnect() {
    console.log("OnDisconnect");
    resetUI();
}

let ledStateCharacteristic;

async function discoverServicesAndCharacteristics() {
    console.log("Discovering Services and Characteristics");
    let primaryServices = await bluetoothServer.getPrimaryServices();
    for (const service of primaryServices) {
        console.log("> Service: " + service.uuid);
        if (service.uuid == LED_SERVICE) {
            let characteristics = await service.getCharacteristics();
            for (const characteristic of characteristics) {
                console.log("> Characteristic: " + characteristic.uuid);
                if (characteristic.uuid == LED_STATE_CHARACTERISTIC) {
                    ledStateCharacteristic = characteristic;
                }
            }
        }
    }
    setDiscoveredStatus(true);
}

// NOT FITTING IN CONTEXT
function resetUI() {
    setConnectedStatus(false);
    setDiscoveredStatus(false);
}

async function setLedStateCharacteristic(value) {
    console.log("Changing LED State");
    try {
        let valueBuffer = new Uint8Array([value]);
        await ledStateCharacteristic.writeValue(valueBuffer.buffer);
        console.log("> LED State: " + value);
    } catch (error) {
        console.warn("ERROR: " + error);
    }
}