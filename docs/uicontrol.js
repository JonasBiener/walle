const speedButton = document.getElementById("btSpeed");
const directionButton = document.getElementById("btDirection");
const connectButton = document.getElementById("btnConnect");

const speedInput = document.getElementById("inSpeed");
const directionInput = document.getElementById("inDirection");

speedButton.onclick = () => sendSpeed();
directionButton.onclick = () => sendDirection();
connectButton.onclick = () => discoverOrDisconnect();


async function sendSpeed() {
    let value = speedInput.value;
    if (value === "") speedInput.value = await readCharacteristicBLE(driveSpeedCharacteristic);
    else writeCharacteristicBLE(driveSpeedCharacteristic, value);
}

async function sendDirection() {
    let value = directionInput.value;
    if (value === "") directionInput.value = await readCharacteristicBLE(driveSpeedCharacteristic);
    else writeCharacteristicBLE(driveSpeedCharacteristic, value);
}