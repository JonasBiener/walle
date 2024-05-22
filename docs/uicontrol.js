const onButton = document.getElementById("btOn");
const offButton = document.getElementById("btOff");

onButton.onclick = () => sendOnControl();
offButton.onclick = () => sendOffControl();


function sendOnControl() {
    setLedStateCharacteristic(1);
}

function sendOffControl() {
    setLedStateCharacteristic(0);
}