/* BLE VARIABLES */
// Drive Service
export const DRIVE_SERVICE = "6d4d2d45-c51b-4034-bd72-4d134d8d8f9e";
export const DRIVE_SPEED_CHARACTERISTIC = "e92ab9ad-e970-44ca-b78a-0708fe306c3c";
export const DRIVE_DIRECTION_CHARACTERISTIC = "ae21bd14-732c-46dc-a82b-fc0e23e2d36e";
export let driveSpeedCharacteristic;
export let driveDirectionCharacteristic;
/* END */

let bluetoothDevice;
let bluetoothServer;

function onDisconnectBLE() {}

export function setOnDisconnectBLE(func) {
    onDisconnectBLE = func;
}

export async function discoverBLE() {
    /* DEBUGGING */ console.log("Discovering Devices");
    try {
        let options = {filters: [
            {services: [DRIVE_SERVICE]}
        ]};
        bluetoothDevice = await navigator.bluetooth.requestDevice(options);
        /* DEBUGGING */ console.log("> Name: " + bluetoothDevice.name);
        /* DEBUGGING */ console.log("> ID: " + bluetoothDevice.id);
        /* DEBUGGING */ console.log("> Connected: " + bluetoothDevice.gatt.connected);
    } catch (error) {
        /* DEBUGGING */ console.warn("ERROR: " + error);
        throw "Could not discover devices";
    }
}

export async function connectBLE() {
    /* DEBUGGING */ console.log("Connecting");
    try {
        bluetoothServer = await bluetoothDevice.gatt.connect();
        bluetoothDevice.addEventListener("gattserverdisconnected", () => onDisconnectBLE());
        /* DEBUGGING */ console.log("> Connected to: " + bluetoothServer.device.id);
        /* DEBUGGING */ console.log("> Connected: " + bluetoothServer.connected);
    } catch (error) {
        /* DEBUGGING */ console.warn("ERROR: " + error);
        throw "Could not connect to device";
    }
}

export function disconnectBLE() {
    /* DEBUGGING */ console.log("Disconnecting");
    bluetoothDevice.gatt.disconnect();
    /* DEBUGGING */ console.log("> ID: " + bluetoothDevice.id);
}

export async function discoverServicesAndCharacteristicsBLE() {
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
        /* DEBUGGING */ console.log("Connection established");
    } catch (error) {
        /* DEBUGGING */ console.warn("ERROR: " + error);
        throw "Could not discover services and characteristics";
    }    
}

export async function readCharacteristicBLE(characteristic) {
    /* DEBUGGING */ console.log("Reading " + characteristic.uuid);
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

export async function writeCharacteristicBLE(characteristic, value) {
    debugger;
    /* DEBUGGING */ console.log("Changing " + characteristic.uuid);
    try {
        let binary_buffer = new Int16Array([value]);
        await characteristic.writeValue(binary_buffer.buffer);
        /* DEBUGGING */ console.log("> Value: " + value);
    } catch (error) {
        /* DEBUGGING */ console.warn("ERROR: " + error);
    }
}