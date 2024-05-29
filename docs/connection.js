/* BLE UUIDs */
// Drive Service
const DRIVE_SERVICE = "6d4d2d45-c51b-4034-bd72-4d134d8d8f9e";
const DRIVE_SPEED_CHARACTERISTIC = "e92ab9ad-e970-44ca-b78a-0708fe306c3c";
const DRIVE_DIRECTION_CHARACTERISTIC = "ae21bd14-732c-46dc-a82b-fc0e23e2d36e";
/* END */

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

// NOT FITTING IN CONTEXT
function resetUI() {
    setConnectedStatus(false);
    setDiscoveredStatus(false);
}

let bluetoothDevice;
let bluetoothServer;

// NOT FITTING IN CONTEXT
function discoverOrDisconnect() {
    if (!isConnected) discoverBLE();
    else bluetoothDevice.gatt.disconnect();
}

async function discoverBLE() {
    /* DEBUGGING */ console.log("Discovering Devices");
    try {
        let options = {filters: [
            {services: [DRIVE_SERVICE]}
        ]};
        bluetoothDevice = await navigator.bluetooth.requestDevice(options);
        /* DEBUGGING */ console.log("> Name: " + bluetoothDevice.name);
        /* DEBUGGING */ console.log("> ID: " + bluetoothDevice.id);
        /* DEBUGGING */ console.log("> Connected: " + bluetoothDevice.gatt.connected);
        connectBLE();
    } catch (error) {
        /* DEBUGGING */ console.warn("ERROR: " + error);
    }
}

async function connectBLE() {
    if (isConnected) return;
    console.log("Connecting");
    try {
        bluetoothServer = await bluetoothDevice.gatt.connect();
        /* DEBUGGING */ console.log("> Connected to: " + bluetoothServer.device.id);
        /* DEBUGGING */ console.log("> Connected: " + bluetoothServer.connected);
        bluetoothDevice.addEventListener("gattserverdisconnected", onDisconnectBLE);
        setConnectedStatus(true);
        discoverServicesAndCharacteristicsBLE();
    } catch (error) {
        /* DEBUGGING */ console.warn("ERROR: " + error);
        setConnectedStatus(false);
    }
}

function onDisconnectBLE() {
    /* DEBUGGING */ console.log("OnDisconnect");
    alert("BLE-Device disconnected");
    resetUI();
}

/* BLE CHARACTERISTICS */
let driveSpeedCharacteristic;
let driveDirectionCharacteristic;
/* END */

async function discoverServicesAndCharacteristicsBLE() {
    /* DEBUGGING */ console.log("Discovering Services and Characteristics");
    try {
        let primaryServices = await bluetoothServer.getPrimaryServices();
        for (const service of primaryServices) {
            /* DEBUGGING */ console.log("> Service: " + service.uuid);
            let characteristics = await service.getCharacteristics();
            for (const characteristic of characteristics) {
                /* DEBUGGING */ console.log("> Characteristic: " + characteristic.uuid);
                switch (service.uuid) {
                    case DRIVE_SERVICE:
                        switch (characteristic.uuid) {
                            case DRIVE_SPEED_CHARACTERISTIC:
                                driveSpeedCharacteristic = characteristic;
                                break;
                            case DRIVE_DIRECTION_CHARACTERISTIC:
                                driveDirectionCharacteristic = characteristic;
                                break;
                        }
                        break;
                }
            } 
        }
        setDiscoveredStatus(true);
        /* DEBUGGING */ console.log("Connection established");
    } catch (error) {
        /* DEBUGGING */ console.warn("ERROR: " + error);
    }    
}

async function readCharacteristicBLE(characteristic) {
    /* DEBUGGING */ console.log("Reading " + Object.keys(characteristic)[0]);
    try {
        let binary_buffer = await characteristic.readValue();
        let binary_value = new Int16Array(binary_buffer.buffer);
        let value = Number(binary_value);
        /* DEBUGGING */ console.log("> Value: " + value);
        return value;
    } catch (error) {
        /* DEBUGGING */ console.warn("ERROR: " + error);
    }
}

async function writeCharacteristicBLE(characteristic, value) {
    /* DEBUGGING */ console.log("Changing " + Object.keys(characteristic)[0]);
    try {
        let binary_buffer = new Int16Array([value]);
        await characteristic.writeValue(binary_buffer.buffer);
        /* DEBUGGING */ console.log("> Value: " + value);
    } catch (error) {
        /* DEBUGGING */ console.warn("ERROR: " + error);
    }
}