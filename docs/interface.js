import * as connection from "./connection.js"
import * as control from "./control.js"

const connectDialog = document.getElementById("connectDialog");
const connectButton = document.getElementById("connectButton");
const connectStatus = document.getElementById("connectStatus");
const favicon = document.getElementById("favicon");

window.addEventListener("load", () => {
    showConnectionDialog();
});
connection.setOnDisconnectBLE(() => {
    showConnectionDialog();
    control.stop();
});


function showConnectionDialog() {
    connectButton.disabled = false;
    connectStatus.classList.remove("error");
    connectStatus.innerText = "Disconnected"
    favicon.setAttribute("href", "walleBox.ico");
    document.title = "WALL-E Inactive - RoCCI e.V.";
    connectDialog.showModal();
}

connectButton.onclick = () => performConnect();
async function performConnect() {
    try {
        connectButton.disabled = true;
        connectStatus.classList.remove("error");
        connectStatus.innerText = "Discovering ..."
        await connection.discoverBLE();
        connectStatus.innerText = "Connecting ..."
        await connection.connectBLE();
        connectStatus.innerText = "Establishing ..."
        await connection.discoverServicesAndCharacteristicsBLE();
        favicon.setAttribute("href", "walleActive.ico");
        document.title = "WALL-E Active - RoCCI e.V.";
        control.begin();
        connectDialog.close();
    } catch (error) {
        connectButton.disabled = false;
        connectStatus.classList.add("error");
        connectStatus.innerText = error;
    }
}

const disconnectButton = document.getElementById("disconnectButton");
disconnectButton.onclick = () => connection.disconnectBLE();

new JoyStick('joyDiv', 
    {
        internalFillColor: "grey",
        internalLineWidth: 2,
        internalStrokeColor: "black",
        externalLineWidth: 2,
        externalStrokeColor: "black",
        autoReturnToCenter: true
    }, (stickData) => control.updateDriveValues(stickData.x, stickData.y)
);