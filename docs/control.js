import * as connection from "./connection.js"

let controlStatus = false;

export async function begin() {
    controlStatus = true;
    connection.writeCharacteristicBLE(connection.driveSpeedCharacteristic, 0);
    connection.writeCharacteristicBLE(connection.driveDirectionCharacteristic, 0);
}

export async function updateDriveValues(x, y) {
    if (!controlStatus) return;
    connection.writeCharacteristicBLE(connection.driveSpeedCharacteristic, x);
    connection.writeCharacteristicBLE(connection.driveDirectionCharacteristic, y);
}

export function stop() {
    controlStatus = false;
}

export function pause() {
    controlStatus = false;
}
