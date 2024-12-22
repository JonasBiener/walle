/* DEFINITION OF BLE SERVICES */
// Drive Service
const DRIVE_SERVICE_UUID: BluetoothServiceUUID = "6d4d2d45-c51b-4034-bd72-4d134d8d8f9e";
const DRIVE_SPEED_CHARACTERISTIC_UUID: BluetoothCharacteristicUUID = "e92ab9ad-e970-44ca-b78a-0708fe306c3c";
const DRIVE_DIRECTION_CHARACTERISTIC_UUID: BluetoothCharacteristicUUID = "ae21bd14-732c-46dc-a82b-fc0e23e2d36e";
export let driveService: BluetoothRemoteGATTService;
export let driveSpeedCharacteristic: BluetoothRemoteGATTCharacteristic;
export let driveDirectionCharacteristic: BluetoothRemoteGATTCharacteristic;
/* END */

let bluetoothDevice: BluetoothDevice;
let bluetoothServer: BluetoothRemoteGATTServer;
let bluetoothWriteInProgress: boolean = false;

export let onDisconnectBLE: Function;

export async function discoverBLE(): Promise<void> {
    console.info("Discovering Devices");
    try {
        let options = {filters: [
            {services: [DRIVE_SERVICE_UUID]}
        ]};
        bluetoothDevice = await navigator.bluetooth.requestDevice(options);
        console.debug("Name: " + bluetoothDevice.name);
        console.debug("ID: " + bluetoothDevice.id);
        console.debug("Connected: " + bluetoothDevice.gatt?.connected);
    } catch (error) {
        console.warn(error);
        throw Error("Could not discover Bluetooth devices");
    }
}

export async function connectBLE(): Promise<void> {
    console.log("Connecting");
    try {
        if (bluetoothDevice.gatt) {
            bluetoothServer = await bluetoothDevice.gatt.connect();
            bluetoothDevice.addEventListener("gattserverdisconnected", () => onDisconnectBLE());
        }
        console.debug("Connected to: " + bluetoothServer.device.id);
        console.debug("Connected: " + bluetoothServer.connected);
    } catch (error) {
        console.warn(error);
        throw Error("Could not connect to Bluetooth device");
    }
}

export async function disconnectBLE() {
    console.log("Disconnecting");
    if (bluetoothDevice.gatt) {
        bluetoothDevice.gatt.disconnect();
    }
    console.debug("> ID: " + bluetoothDevice.id);
}

export async function discoverServicesAndCharacteristicsBLE(): Promise<void> {
   console.log("Discovering Services and Characteristics");
    try {
        let primaryServices = await bluetoothServer.getPrimaryServices();
        for (const service of primaryServices) {
            console.debug("Service: " + service.uuid);
            let characteristics = await service.getCharacteristics();
            for (const characteristic of characteristics) {
                console.debug("Characteristic: " + characteristic.uuid);
                switch (service.uuid) {
                    case DRIVE_SERVICE_UUID:
                        switch (characteristic.uuid) {
                            case DRIVE_SPEED_CHARACTERISTIC_UUID:
                                driveSpeedCharacteristic = characteristic;
                                break;
                            case DRIVE_DIRECTION_CHARACTERISTIC_UUID:
                                driveDirectionCharacteristic = characteristic;
                                break;
                        }
                        break;
                }
            } 
        }
        console.log("Connection established");
    } catch (error) {
        console.warn(error);
        throw Error("Could not discover WALL-E's specific services and characteristics");
    }    
}

export async function readCharacteristicBLE(characteristic: BluetoothRemoteGATTCharacteristic): Promise<number> {
    console.debug("Reading " + characteristic.uuid);
    try {
        let binary_buffer = await characteristic.readValue();
        let binary_value = new Int16Array(binary_buffer.buffer);
        let value = Number(binary_value);
        console.debug("Value: " + value);
        return value;
    } catch (error) {
        console.debug("ERROR: " + error);
        return Promise.reject(error);
    }
}

export async function writeCharacteristicBLE(characteristic: BluetoothRemoteGATTCharacteristic, value: number): Promise<void> {
    if (bluetoothWriteInProgress) return;
    console.debug("Changing " + characteristic.uuid);
    try {
        bluetoothWriteInProgress = true;
        let binary_buffer = new Int16Array([value]);
        await characteristic.writeValue(binary_buffer.buffer);
        bluetoothWriteInProgress = false;
        console.debug("Value: " + value);
    } catch (error) {
        console.debug("ERROR: " + error);
    }
}