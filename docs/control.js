import * as connection from "./connection.js"

const speedInputUI = document.getElementById("speedInput");
const speedValueUI = document.getElementById("speedValue");

export async function begin() {
    let speedValue = await connection.readCharacteristicBLE(connection.driveSpeedCharacteristic);
    speedInputUI.value = speedValue;
    speedValueUI.innerText = speedValue;
    speedInputUI.oninput = () => {
        let value = Number(speedInputUI.value);
        speedValueUI.innerText = value;
        connection.writeCharacteristicBLE(connection.driveSpeedCharacteristic, value);
    };
    speedInputUI.onchange = speedInputUI.oninput;
}

export function stop() {
    speedInputUI.oninput = null;
}

export function pause() {

}
